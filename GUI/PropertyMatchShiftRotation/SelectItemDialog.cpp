#include "SelectItemDialog.h"
#include "ui_SelectItemDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

SelectItemDialog::SelectItemDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::SelectItemDialog)
{
    ui->setupUi(this);
	SelectedLibID=-1;
	MatchShiftRotationLibID	 =-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MatchShiftRotation");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempMatchShiftRotationItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		CmdCreateTempMatchShiftRotationLibraryPacket	LibPacket(GetLayersBase());
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
	ui->ButtonOK	->setEnabled(false);
	ui->ButtonDelete->setEnabled(false);

	InstallOperationLog(this);
}

SelectItemDialog::~SelectItemDialog()
{
    delete ui;
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}

void	SelectItemDialog::Reflect(void)
{
	ui->EditLibID		->setText(QString::number(MatchShiftRotationLibID));

	CmdGetLibName	LibPacket(GetLayersBase());
	LibPacket.LibID=MatchShiftRotationLibID;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MatchShiftRotation");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&LibPacket);
	}
	ui->EditLibName		->setText(LibPacket.LibName);
	ui->EditItemName	->setText(ItemName);

	ui->ButtonDelete->setEnabled(true);
}

void	SelectItemDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MatchShiftRotation");
	if(Ab!=NULL){
		CmdGetMatchShiftRotationLibraryListPacket	Packet(GetLayersBase());
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
void SelectItemDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadMatchShiftRotationLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MatchShiftRotation");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);

		if(Packet.Success==true){
			MatchShiftRotationLibrary	*ALib=dynamic_cast<MatchShiftRotationLibrary *>(TempLib->GetLibrary());
			MatchShiftRotationLibID		=TempLib->GetLibID();
			ui->EditLibID				->setText(QString::number(TempLib->GetLibID()));
			ui->EditLibName				->setText(a->GetLibName());

			ui->ButtonOK->setEnabled(true);
			ui->spinBoxSearchLittleInItem	->setValue(ALib->SearchLittleInItem);
			ui->doubleSpinBox				->setValue(ALib->MatchingRate);
		}
		else{
			QMessageBox::critical(NULL	, "Library error"
										, "Not loaded this library record");
		}
	}
}

void SelectItemDialog::on_ButtonOK_clicked()
{
	ItemName	=ui->EditItemName	->text();
	done(true);
}

void SelectItemDialog::on_ButtonCancel_clicked()
{
	done(false);
}

void SelectItemDialog::on_ButtonDelete_clicked()
{
	done(10);
}
