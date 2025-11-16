#include "EditLibraryDialogResource.h"
#include "ManualInputProjectedInspectionDialog.h"
#include "ui_ManualInputProjectedInspectionDialog.h"
#include "XPropertyProjectedInspectionPacket.h"
#include "XProjectedInspectionLibrary.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

ManualInputProjectedInspectionDialog::ManualInputProjectedInspectionDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::ManualInputProjectedInspectionDialog)
{
    ui->setupUi(this);

	SelectedLibID=-1;
	ProjectedInspectionLibID	 =-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempProjectedInspectionItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(ProjectedInspectionItem *)ItemPacket.Point;
		CmdCreateTempProjectedInspectionLibraryPacket	LibPacket(GetLayersBase());
		Ab->TransmitDirectly(&LibPacket);
		TempLib=LibPacket.Point;
	LibType=Ab->GetLibType();
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetLibList->setRowCount(0);
	ui->ButtonOK->setEnabled(false);

	InstallOperationLog(this);
}

ManualInputProjectedInspectionDialog::~ManualInputProjectedInspectionDialog()
{
    delete ui;
	if(BItem!=NULL)
		delete	BItem;
	BItem=NULL;
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}

void	ManualInputProjectedInspectionDialog::Reflect(void)
{
	ui->EditLibID			->setText(QString::number(BItem->GetLibID()));
	ProjectedInspectionLibID=BItem->GetLibID();
	CmdGetLibName	LibPacket(GetLayersBase());
	LibPacket.LibID=BItem->GetLibID();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&LibPacket);
	}
	ui->EditLibName				->setText(LibPacket.LibName);

}

void	ManualInputProjectedInspectionDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
	if(Ab!=NULL){
		CmdGetProjectedInspectionLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		Ab->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui->tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}
void ManualInputProjectedInspectionDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadProjectedInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);

		if(Packet.Success==true){
			ProjectedInspectionLibID			=TempLib->GetLibID();
			ui->EditLibID				->setText(QString::number(TempLib->GetLibID()));
			ui->EditLibName				->setText(a->GetLibName());

			ui->ButtonOK->setEnabled(true);
			if(BItem!=NULL){
				BItem->SetLibID(TempLib->GetLibID());
			}
		}
		else{
			QMessageBox::critical(NULL, LangSolver.GetString(ManualInputProjectedInspectionDialog_LS,LID_0)/*"Library error"*/
									, LangSolver.GetString(ManualInputProjectedInspectionDialog_LS,LID_1)/*"Not loaded this library record"*/);
		}
	}
}

void ManualInputProjectedInspectionDialog::on_ButtonOK_clicked()
{
	done(true);
}

void ManualInputProjectedInspectionDialog::on_ButtonCancel_clicked()
{
	done(false);
}
