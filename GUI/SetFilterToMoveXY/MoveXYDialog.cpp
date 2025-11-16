#include "SetFilterToMoveXYFromResource.h"
#include "MoveXYDialog.h"
#include "XGeneralFunc.h"
#include "ui_MoveXYDialog.h"
#include "XDataInLayer.h"
#include "SetFilterToMoveXYFrom.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

MoveXYDialog::MoveXYDialog(LayersBase *pbase,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(pbase)
    ,ui(new Ui::MoveXYDialog)
{
    ui->setupUi(this);

	ui->tableWidgetValues->setColumnWidth(0,40);
	ui->tableWidgetValues->setColumnWidth(1,40);
	ui->tableWidgetValues->setColumnWidth(2,40);
	InstallOperationLog(this);
}

MoveXYDialog::~MoveXYDialog()
{
    delete ui;
}

void	MoveXYDialog::Init(void)
{
	SavedMoveXYListContainer.RemoveAll();
	ui->tableWidgetValues->setRowCount(MoveXYListContainer.GetCount());
	int	Row=0;
	for(MoveXYList *a=MoveXYListContainer.GetFirst();a!=NULL;a=a->GetNext()){
		MoveXYList *b=new MoveXYList();
		*b=*a;
		SavedMoveXYListContainer.AppendList(b);

		::SetDataToTable(ui->tableWidgetValues ,0,Row,QString::number(a->GlobalPage),Qt::NoItemFlags);
		::SetDataToTable(ui->tableWidgetValues ,1,Row,QString::number(a->Dx)		,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetValues ,2,Row,QString::number(a->Dy)		,Qt::ItemIsEditable);
		Row++;
	}
}

void MoveXYDialog::on_pushButtonOK_clicked()
{
	//close(true);
	close();
}

void MoveXYDialog::on_pushButtonCancel_clicked()
{
	//close(false);

	MoveXYList	*a=SavedMoveXYListContainer.GetFirst();
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++ ,a=a->GetNext()){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetShiftMove	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.MovX	=a->Dx;
		RCmd.MovY	=a->Dy;
		RCmd.Send(NULL,GlobalPage,0);
	}
	close();
}

void MoveXYDialog::on_pushButtonSet_clicked()
{
	int	Row=0;
	for(MoveXYList *a=MoveXYListContainer.GetFirst();a!=NULL;a=a->GetNext()){
		QString	sx=::GetDataToTable(ui->tableWidgetValues,1,Row);
		QString	sy=::GetDataToTable(ui->tableWidgetValues,2,Row);
		bool	ok;
		int	dx=sx.toInt(&ok);
		if(ok==true){
			a->Dx=dx;
		}
		int	dy=sy.toInt(&ok);
		if(ok==true){
			a->Dy=dy;
		}
		Row++;
	}

	MoveXYList	*a=MoveXYListContainer.GetFirst();
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++ ,a=a->GetNext()){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetShiftMove	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.MovX	=a->Dx;
		RCmd.MovY	=a->Dy;
		RCmd.Send(NULL,GlobalPage,0);
	}
}

MoveXYList	&MoveXYList::operator=(MoveXYList &src)
{
	GlobalPage	=src.GlobalPage;
	Dx			=src.Dx;
	Dy			=src.Dy;
	return *this;
}
