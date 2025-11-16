#include "PropertyHoughInspectionFormResource.h"
#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"
#include "XHoughInspectionPacket.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditLibraryDialog::EditLibraryDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::EditLibraryDialog)
{
    ui->setupUi(this);

	LibFolderID =-1;
	HoughBase	*BBase=GetHoughBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempHoughLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui->tableWidgetLibList->setColumnWidth ( 0, 32);
	ui->tableWidgetLibList->setColumnWidth ( 1, 160);

	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	InstallOperationLog(this);
}

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
}
HoughBase	*EditLibraryDialog::GetHoughBase(void)
{
	return (HoughBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Hough");
}
void	EditLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	HoughBase	*BBase=GetHoughBase();
	if(BBase!=NULL){
		CmdGetHoughLibraryListPacket	Packet(GetLayersBase());
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
void	EditLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}
void EditLibraryDialog::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearHoughLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	HoughBase	*BBase=GetHoughBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=QString(/**/"Delete OK?");
	int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteHoughLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		HoughBase	*BBase=GetHoughBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertHoughLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	HoughBase	*BBase=GetHoughBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertHoughLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		HoughBase	*BBase=GetHoughBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateHoughLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		HoughBase	*BBase=GetHoughBase();
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

void EditLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadHoughLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		HoughBase	*BBase=GetHoughBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void	EditLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	HoughLibrary	*ALib=dynamic_cast<HoughLibrary *>(data.GetLibrary());
	ui->EditZoneWidth			->setValue(ALib->ZoneWidth);
	ui->EditMaxIsolation		->setValue(ALib->MaxIsolation);
	ui->EditBinarizedLength		->setValue(ALib->BinarizedLength);
	ui->EditMinPixels			->setValue(ALib->MinPixels);
	ui->EditNGLength			->setValue(ALib->NGLength);
	ui->EditPickupL				->setValue(ALib->PickupL);
	ui->EditPickupH				->setValue(ALib->PickupH);
	ui->checkBoxRemoveDynamicMask	->setChecked(ALib->RemoveDynamicMask);
	ui->EditReducedSize			->setValue(ALib->ReducedSize);
	ui->EditMaxLineCount		->setValue(ALib->MaxLineCount);
	ui->EditMinNGWidth			->setValue(ALib->MinNGWidth);
	ui->EditMaxNGWidth			->setValue(ALib->MaxNGWidth);
	ui->EditMinAverageContinuous->setValue(ALib->MinAverageContinuous);
	ui->checkBoxDynamicBinarize	->setChecked(ALib->DynamicBinarize);
}

void	EditLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	HoughLibrary	*ALib=dynamic_cast<HoughLibrary *>(data.GetLibrary());
	ALib->ZoneWidth			=ui->EditZoneWidth		->value();
	ALib->MaxIsolation		=ui->EditMaxIsolation	->value();
	ALib->BinarizedLength	=ui->EditBinarizedLength->value();
	ALib->MinPixels			=ui->EditMinPixels		->value();
	ALib->NGLength			=ui->EditNGLength		->value();
	ALib->PickupL			=ui->EditPickupL		->value();
	ALib->PickupH			=ui->EditPickupH		->value();
	ALib->RemoveDynamicMask	=ui->checkBoxRemoveDynamicMask	->isChecked();
	ALib->ReducedSize		=ui->EditReducedSize	->value();
	ALib->MaxLineCount		=ui->EditMaxLineCount	->value();
	ALib->MinNGWidth		=ui->EditMinNGWidth		->value();
	ALib->MaxNGWidth		=ui->EditMaxNGWidth		->value();
	ALib->MinAverageContinuous=ui->EditMinAverageContinuous	->value();
	ALib->DynamicBinarize	=ui->checkBoxDynamicBinarize	->isChecked();
}
