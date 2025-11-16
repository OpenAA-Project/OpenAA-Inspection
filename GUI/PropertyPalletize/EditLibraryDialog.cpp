#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
//#include "XPropertyColorDifferencePacket.h"
#include "XPalletizeLibrary.h"
#include <QMessageBox>
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"

EditLibraryDialog::EditLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditLibraryDialog)
{
    ui->setupUi(this);

	OnChanging	=false;
	LibFolderID =-1;
	PalletizeBase	*BBase=GetPalletizeBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	if(BBase!=NULL){
		CmdCreateTempPalletizeLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	else{
		LLib=new AlgorithmLibraryLevelContainer(BBase);
	}
	ui->tableWidgetLibList	->setColumnWidth(0,48);
	ui->tableWidgetLibList	->setColumnWidth(1,120);

	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	InstallOperationLog(this);
}

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
	if(LLib!=NULL){
		delete	LLib;
		LLib=NULL;
	}
}

PalletizeBase	*EditLibraryDialog::GetPalletizeBase(void)
{
	return (PalletizeBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Palletize");
}

void	EditLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibList->setRowCount(0);
	PalletizeBase	*BBase=GetPalletizeBase();
	if(BBase!=NULL){
		CmdGetPalletizeLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
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
void EditLibraryDialog::on_tableWidgetLibList_itemClicked(QTableWidgetItem *item)
{
	int	r=ui->tableWidgetLibList->currentRow();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadPalletizeLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		PalletizeBase	*BBase=GetPalletizeBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL
									, "Library error"
									, "Not loaded this library record");
			}
		}
	}
}


void	EditLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	PalletizeLibrary	*d=dynamic_cast<PalletizeLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->doubleSpinBoxAngleRange	->setValue(d->AngleRange);
	ui->doubleSpinBoxMinZoomSize->setValue(d->MinZoomSize);
	ui->doubleSpinBoxMaxZoomSize->setValue(d->MaxZoomSize);
	ui->spinBoxPieceSize		->setValue(d->PieceSize);
	ui->spinBoxSearchDotPiece	->setValue(d->SearchDotPiece);
	ui->doubleSpinBoxThresholdV	->setValue(d->ThresholdV);
	ui->spinBoxMaxCountOfPiece	->setValue(d->MaxCountOfPiece);
	ui->doubleSpinBoxThreshCoeff->setValue(d->ThreshCoeff);
	ui->spinBoxSearchNearBy		->setValue(d->SearchNearBy);
}

void	EditLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	PalletizeLibrary	*d=dynamic_cast<PalletizeLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->AngleRange		=ui->doubleSpinBoxAngleRange	->value();
	d->MinZoomSize		=ui->doubleSpinBoxMinZoomSize	->value();
	d->MaxZoomSize		=ui->doubleSpinBoxMaxZoomSize	->value();
	d->PieceSize		=ui->spinBoxPieceSize			->value();
	d->SearchDotPiece	=ui->spinBoxSearchDotPiece		->value();
	d->ThresholdV		=ui->doubleSpinBoxThresholdV	->value();
	d->MaxCountOfPiece	=ui->spinBoxMaxCountOfPiece		->value();
	d->ThreshCoeff		=ui->doubleSpinBoxThreshCoeff	->value();
	d->SearchNearBy		=ui->spinBoxSearchNearBy		->value();
}
void EditLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearPalletizeLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	PalletizeBase	*BBase=GetPalletizeBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}


void EditLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(LLib==NULL)
		return;
	if(LLib->GetLibID()<0)
		return;
	QString  msg=QString("Delete OK?");
	int	ret=QMessageBox::question(NULL, "Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeletePalletizeLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		PalletizeBase	*BBase=GetPalletizeBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}


void EditLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);

	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, "Warning"
																, "No Library Name"
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	LLib->SetLibFolderID(LibFolderID);
	CmdInsertPalletizeLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	PalletizeBase	*BBase=GetPalletizeBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}


void EditLibraryDialog::on_ButtonLibSave_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, "Warning"
																, "No Library Name"
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()<0){
		LLib->SetLibFolderID(LibFolderID);

		CmdInsertPalletizeLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		PalletizeBase	*BBase=GetPalletizeBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdatePalletizeLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		PalletizeBase	*BBase=GetPalletizeBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}


void EditLibraryDialog::on_pushButton_clicked()
{
	close();
}

