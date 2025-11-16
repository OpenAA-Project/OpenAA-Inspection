#include "AddSourceItemDialogResource.h"
#include "EditItemDialog.h"
#include "ui_EditItemDialog.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

EditItemDialog::EditItemDialog(bool _AdditionalMode ,LayersBase *Base,int globalPage ,int _Layer ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::EditItemDialog)
{
    ui->setupUi(this);
	AdditionalMode	=_AdditionalMode;
	GlobalPage		=globalPage;
	Layer			=_Layer;
	if(AdditionalMode==true){
		ui->pushButtonCreateNew	->setEnabled(true);
		ui->pushButtonModify	->setEnabled(false);
	}
	else{
		ui->pushButtonCreateNew	->setEnabled(false);
		ui->pushButtonModify	->setEnabled(true);
	}

	ui->comboBox->clear();
	GetLayersBase()->GetAlgorithmByType(AlgoBases ,AlgorithmBit_TypeManageResult);
	for(AlgorithmBasePointerList *a=AlgoBases.GetFirst();a!=NULL;a=a->GetNext()){
		QString	DLLRoot,DLLName;
		a->GetAlgorithmBase()->GetAlgorithmRootName(DLLRoot,DLLName);
		ui->comboBox->addItem(DLLRoot+QString(/**/":")+DLLName);
	}
	if(AlgoBases.IsEmpty()==false){
		ui->comboBox->setCurrentIndex(0);
	}
	InstallOperationLog(this);
}

EditItemDialog::~EditItemDialog()
{
    delete ui;
}

void	EditItemDialog::Reflect(void)
{
	if(AdditionalMode==true){
		ShowList();
	}
	else{
		int		Row=0;
		for(AlgorithmBasePointerList *a=AlgoBases.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			QString	DLLRoot,DLLName;
			a->GetAlgorithmBase()->GetAlgorithmRootName(DLLRoot,DLLName);
			if(DLLRoot==NamingDLLRoot && DLLName==NamingDLLName)
				break;
		}
		if(Row<AlgoBases.GetCount()){
			ui->comboBox->setCurrentIndex(Row);
		}
		ShowList();
		int	N=0;
		for(NamingInfoList *r=NamingContainer.GetFirst();r!=NULL;r=r->GetNext(),N++){
			if(r->ItemID==NamingID)
				break;
		}
		if(N<NamingContainer.GetCount()){
			IntList	Rows;
			Rows.Add(N);
			::SetSelectedRows(ui->tableWidget ,Rows);
		}
		ui->lineEditItemName	->setText(ItemName);
	}
}

void EditItemDialog::ShowList(void)
{
	int	Row=ui->comboBox->currentIndex();
	if(Row<0)
		return;
	AlgorithmBasePointerList *a=AlgoBases[Row];
	if(a==NULL)
		return;

	GUICmdReqNamingList		Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	GUICmdSendNamingList	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	Cmd.Layer=Layer;
	a->GetAlgorithmBase()->GetAlgorithmRootName(Cmd.NamingDLLRoot,Cmd.NamingDLLName);
	if(Cmd.Send(GlobalPage,0,ACmd)==true){
		NamingContainer	=ACmd.NamingContainer;
		int	N=0;
		ui->tableWidget->setRowCount(NamingContainer.GetCount());
		for(NamingInfoList *r=NamingContainer.GetFirst();r!=NULL;r=r->GetNext(),N++){
			::SetDataToTable(ui->tableWidget ,0,N,r->ItemName);
			::SetDataToTable(ui->tableWidget ,1,N,QString::number(r->ItemID));

			QString	s=QString(/**/"(")
					+ QString::number(r->x1)+QString(/**/",")+QString::number(r->y1)
					+ QString(/**/")-(")
					+ QString::number(r->x2)+QString(/**/",")+QString::number(r->y2)
					+ QString(/**/")");
			::SetDataToTable(ui->tableWidget ,2,N,s);
		}
	}
}

void EditItemDialog::on_pushButtonCreateNew_clicked()
{
	int	Row=ui->comboBox->currentIndex();
	if(Row<0)
		return;
	AlgorithmBasePointerList *a=AlgoBases[Row];
	if(a==NULL)
		return;
	a->GetAlgorithmBase()->GetAlgorithmRootName(NamingDLLRoot,NamingDLLName);
	int	N=ui->tableWidget->currentRow();
	if(N<0)
		return;
	if(NamingContainer[N]==NULL)
		return;
	NamingID	=NamingContainer[N]->ItemID;
	ItemName	=ui->lineEditItemName->text();
	done(1);
}

void EditItemDialog::on_pushButtonModify_clicked()
{
	int	Row=ui->comboBox->currentIndex();
	if(Row<0)
		return;
	AlgorithmBasePointerList *a=AlgoBases[Row];
	if(a==NULL)
		return;
	a->GetAlgorithmBase()->GetAlgorithmRootName(NamingDLLRoot,NamingDLLName);
	int	N=ui->tableWidget->currentRow();
	if(N<0)
		return;
	if(NamingContainer[N]==NULL)
		return;
	NamingID	=NamingContainer[N]->ItemID;
	ItemName	=ui->lineEditItemName->text();
	done(2);	
}

void EditItemDialog::on_pushButtonCancel_clicked()
{
	done(-1);
}
