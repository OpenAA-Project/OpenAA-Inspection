#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
//#include "XPropertyColorDifferencePacket.h"
#include "XRasterInspectionLibrary.h"
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
	RasterInspectionBase	*BBase=GetRasterInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	if(BBase!=NULL){
		CmdCreateTempRasterInspectionLibraryPacket	Packet(GetLayersBase());
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

RasterInspectionBase	*EditLibraryDialog::GetRasterInspectionBase(void)
{
	return (RasterInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RasterInspection");
}

void	EditLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibList->setRowCount(0);
	RasterInspectionBase	*BBase=GetRasterInspectionBase();
	if(BBase!=NULL){
		CmdGetRasterInspectionLibraryListPacket	Packet(GetLayersBase());
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
void EditLibraryDialog::on_tableWidgetLibList_itemSelectionChanged()
{
	int	r=ui->tableWidgetLibList->currentRow();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadRasterInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		RasterInspectionBase	*BBase=GetRasterInspectionBase();
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
	RasterInspectionLibrary	*d=dynamic_cast<RasterInspectionLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->spinBoxGenColorDistance		->setValue(d->GenColorDistance);
	ui->spinBoxPriority				->setValue(d->Priority);
	ui->checkBoxEnableOverlap		->setChecked(d->EnableOverlap);
	ui->spinBoxLimitSize			->setValue(d->LimitSize);

	ui->spinBoxSearchAreaDot		->setValue(d->SearchAreaDot);
	ui->doubleSpinBoxSearchWaveDiv	->setValue(d->SearchWaveDiv);
	ui->doubleSpinBoxWaveDistance	->setValue(d->WaveDistance);
	ui->spinBoxOKDot				->setValue(d->OKDot);
}

void	EditLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	RasterInspectionLibrary	*d=dynamic_cast<RasterInspectionLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->GenColorDistance	=ui->spinBoxGenColorDistance	->value();
	d->Priority			=ui->spinBoxPriority			->value();
	d->EnableOverlap	=ui->checkBoxEnableOverlap		->isChecked();
	d->LimitSize		=ui->spinBoxLimitSize			->value();

	d->SearchAreaDot	=ui->spinBoxSearchAreaDot		->value();
	d->SearchWaveDiv	=ui->doubleSpinBoxSearchWaveDiv	->value();
	d->WaveDistance		=ui->doubleSpinBoxWaveDistance	->value();
	d->OKDot			=ui->spinBoxOKDot				->value();
}
void EditLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearRasterInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	RasterInspectionBase	*BBase=GetRasterInspectionBase();
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
		CmdDeleteRasterInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		RasterInspectionBase	*BBase=GetRasterInspectionBase();
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
	CmdInsertRasterInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	RasterInspectionBase	*BBase=GetRasterInspectionBase();
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

		CmdInsertRasterInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		RasterInspectionBase	*BBase=GetRasterInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateRasterInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		RasterInspectionBase	*BBase=GetRasterInspectionBase();
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

