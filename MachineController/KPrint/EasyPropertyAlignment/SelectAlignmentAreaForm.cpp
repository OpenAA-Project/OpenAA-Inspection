#include "EasyPropertyAlignmentResource.h"
#include "SelectAlignmentAreaForm.h"
#include "ui_SelectAlignmentAreaForm.h"
#include "EasyPropertyAlignmentForm.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XIntClass.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

SelectAlignmentAreaForm::SelectAlignmentAreaForm(LayersBase *base
                                                ,EasyPropertyAlignmentForm *P
                                                ,QWidget *parent) :
    QWidget(parent),ServiceForLayers(base),Parent(P),
    ui(new Ui::SelectAlignmentAreaForm)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);
	setWindowFlag(Qt::WindowStaysOnTopHint);

	::SetColumnWidthInTable(ui->tableWidget,0, 20);
	::SetColumnWidthInTable(ui->tableWidget,1, 80);
	SelectedAreaID=-1;
}

void    SelectAlignmentAreaForm::Initial(void)
{
    IntList	AreaPriority=Parent->GetCurrentAreaPriority();

	AreaID.RemoveAll();
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationCmdReqAlignmentAreaID	RCmd(GetLayersBase(),sRoot,sName,Parent->SlaveNo);
			IntegrationCmdAckAlignmentAreaID	ACmd(GetLayersBase(),sRoot,sName,Parent->SlaveNo);
			RCmd.Phase=m->GetCurrentPhase();
			RCmd.AreaPriority=AreaPriority;
			if(RCmd.Send(Parent->SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
				AreaID+=ACmd.AreaID;
			}
		}
	}
	AreaIDList.RemoveAll();
	for(ListPhasePageLayerItem *a=AreaID.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Data.Layer==0){
			AreaIDList.Add(a->Data.ItemID);
		}
	}
	ui->tableWidget->setRowCount(AreaIDList.GetCount());
	int	Row=0;
	for(IntClass *c=AreaIDList.GetFirst();c!=NULL;c=c->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget, 0, Row, QString::number(c->GetValue()));
		::SetDataToTable(ui->tableWidget, 1, Row,QString(LangSolver.GetString(SelectAlignmentAreaForm_LS,LID_14)/*"Area-"*/) +QString::number(c->GetValue()));
	}
	SelectedAreaID=-1;
}

SelectAlignmentAreaForm::~SelectAlignmentAreaForm()
{
    delete ui;
}

void SelectAlignmentAreaForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	on_toolButtonSelect_clicked();
}


void SelectAlignmentAreaForm::on_toolButtonSelect_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row>=0){
		SelectedAreaID=AreaIDList[Row];
		Parent->SetByAreaID(SelectedAreaID);
		close();
	}
}


void SelectAlignmentAreaForm::on_toolButtonCancel_clicked()
{
	close();
}


void SelectAlignmentAreaForm::on_tableWidget_itemSelectionChanged()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row>=0){
		int	AreaID=AreaIDList[Row];
		Parent->ShowByAreaID(AreaID);
	}
}


void SelectAlignmentAreaForm::on_tableWidget_clicked(const QModelIndex &index)
{
	on_tableWidget_itemSelectionChanged();
}

