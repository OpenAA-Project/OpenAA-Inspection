#include "CreateManualDotColorMatchingDialog.h"
#include "ui_CreateManualDotColorMatchingDialog.h"
#include "XDLLOnly.h"
#include <QMessageBox>
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"

CreateManualDotColorMatchingDialog::CreateManualDotColorMatchingDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::CreateManualDotColorMatchingDialog)
{
    ui->setupUi(this);

	SelectedLibID=-1;
	DotColorMatchingLibID	 =-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	int	LibType=-1;
	LLib=new AlgorithmLibraryLevelContainer(Ab);
	if(Ab!=NULL){
		CmdCreateTempDotColorMatchingItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(DotColorMatchingItem *)ItemPacket.Point;
		CmdCreateTempDotColorMatchingLibraryPacket	LibPacket(GetLayersBase());
		Ab->TransmitDirectly(&LibPacket);
		LLib=LibPacket.Point;
		LibType=Ab->GetLibType();
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetLibList->setRowCount(0);
	ui->ButtonOK->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(0);

	InstallOperationLog(this);
}

CreateManualDotColorMatchingDialog::~CreateManualDotColorMatchingDialog()
{
    delete ui;
	if(BItem!=NULL)
		delete	BItem;
	BItem=NULL;
	if(LLib!=NULL)
		delete	LLib;
	LLib=NULL;
}

void	CreateManualDotColorMatchingDialog::Reflect(void)
{
	ui->EditLibID				->setText(QString::number(BItem->GetLibID()));
	DotColorMatchingLibID=BItem->GetLibID();
	CmdGetDotColorMatchingLibName	LibPacket(GetLayersBase());
	LibPacket.LibID=BItem->GetLibID();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&LibPacket);
	}
	ui->EditLibName			->setText(LibPacket.LibName);
	ui->EditBrightWidthBRL	->setValue(BItem->GetThresholdR()->Broad.BrightWidthRL);
	ui->EditBrightWidthBRH	->setValue(BItem->GetThresholdR()->Broad.BrightWidthRH);
	ui->EditBrightWidthBGL	->setValue(BItem->GetThresholdR()->Broad.BrightWidthGL);
	ui->EditBrightWidthBGH	->setValue(BItem->GetThresholdR()->Broad.BrightWidthGH);
	ui->EditBrightWidthBBL	->setValue(BItem->GetThresholdR()->Broad.BrightWidthBL);
	ui->EditBrightWidthBBH	->setValue(BItem->GetThresholdR()->Broad.BrightWidthBH);
	ui->EditOKDotB			->setValue(BItem->GetThresholdR()->Broad.OKDot);

	ui->EditBrightWidthNRL	->setValue(BItem->GetThresholdR()->Narrow.BrightWidthRL);
	ui->EditBrightWidthNRH	->setValue(BItem->GetThresholdR()->Narrow.BrightWidthRH);
	ui->EditBrightWidthNGL	->setValue(BItem->GetThresholdR()->Narrow.BrightWidthGL);
	ui->EditBrightWidthNGH	->setValue(BItem->GetThresholdR()->Narrow.BrightWidthGH);
	ui->EditBrightWidthNBL	->setValue(BItem->GetThresholdR()->Narrow.BrightWidthBL);
	ui->EditBrightWidthNBH	->setValue(BItem->GetThresholdR()->Narrow.BrightWidthBH);
	ui->EditOKDotN			->setValue(BItem->GetThresholdR()->Narrow.OKDot);

	ui->EditAdjustBlack		->setValue(BItem->GetThresholdR()->AdjustBlack);
	ui->EditAdjustWhite		->setValue(BItem->GetThresholdR()->AdjustWhite);
	ui->EditSelfSearch		->setValue(BItem->GetThresholdR()->SelfSearch);
}

void	CreateManualDotColorMatchingDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(Ab!=NULL){
		CmdGetDotColorMatchingLibraryListPacket	Packet(GetLayersBase());
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

void CreateManualDotColorMatchingDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(Ab!=NULL){
		CmdLoadDotColorMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		LLib->SetLibID(a->GetLibID());
		Ab->TransmitDirectly(&Packet);
		DotColorMatchingLibrary	*TempLib	=dynamic_cast<DotColorMatchingLibrary *>(LLib->GetLibrary());

		if(Packet.Success==true){
			DotColorMatchingLibID	=TempLib->GetLibID();
			ui->EditLibID			->setText(QString::number(TempLib->GetLibID()));
			ui->EditLibName			->setText(a->GetLibName());

			ui->EditBrightWidthBRL	->setValue(TempLib->Broad.BrightWidthRL);
			ui->EditBrightWidthBRH	->setValue(TempLib->Broad.BrightWidthRH);
			ui->EditBrightWidthBGL	->setValue(TempLib->Broad.BrightWidthGL);
			ui->EditBrightWidthBGH	->setValue(TempLib->Broad.BrightWidthGH);
			ui->EditBrightWidthBBL	->setValue(TempLib->Broad.BrightWidthBL);
			ui->EditBrightWidthBBH	->setValue(TempLib->Broad.BrightWidthBH);
			ui->EditOKDotB			->setValue(TempLib->Broad.OKDot);

			ui->EditBrightWidthNRL	->setValue(TempLib->Narrow.BrightWidthRL);
			ui->EditBrightWidthNRH	->setValue(TempLib->Narrow.BrightWidthRH);
			ui->EditBrightWidthNGL	->setValue(TempLib->Narrow.BrightWidthGL);
			ui->EditBrightWidthNGH	->setValue(TempLib->Narrow.BrightWidthGH);
			ui->EditBrightWidthNBL	->setValue(TempLib->Narrow.BrightWidthBL);
			ui->EditBrightWidthNBH	->setValue(TempLib->Narrow.BrightWidthBH);
			ui->EditOKDotN			->setValue(TempLib->Narrow.OKDot);

			ui->EditAdjustBlack		->setValue(TempLib->AdjustBlack);
			ui->EditAdjustWhite		->setValue(TempLib->AdjustWhite);
			ui->EditSelfSearch		->setValue(TempLib->SelfSearch);

			ui->ButtonOK->setEnabled(true);
		}
		else{
			QMessageBox::critical(NULL, "Library error"
									, "Not loaded this library record");
		}
	}
}

void	CreateManualDotColorMatchingDialog::GetDataFromWindow(DotColorMatchingItem &data)
{
	data.SetLibID(DotColorMatchingLibID);
	data.GetThresholdW()->Broad.BrightWidthRL	=ui->EditBrightWidthBRL	->value();
	data.GetThresholdW()->Broad.BrightWidthRH	=ui->EditBrightWidthBRH	->value();
	data.GetThresholdW()->Broad.BrightWidthGL	=ui->EditBrightWidthBGL	->value();
	data.GetThresholdW()->Broad.BrightWidthGH	=ui->EditBrightWidthBGH	->value();
	data.GetThresholdW()->Broad.BrightWidthBL	=ui->EditBrightWidthBBL	->value();
	data.GetThresholdW()->Broad.BrightWidthBH	=ui->EditBrightWidthBBH	->value();
	data.GetThresholdW()->Broad.OKDot			=ui->EditOKDotB			->value();

	data.GetThresholdW()->Narrow.BrightWidthRL	=ui->EditBrightWidthNRL	->value();
	data.GetThresholdW()->Narrow.BrightWidthRH	=ui->EditBrightWidthNRH	->value();
	data.GetThresholdW()->Narrow.BrightWidthGL	=ui->EditBrightWidthNGL	->value();
	data.GetThresholdW()->Narrow.BrightWidthGH	=ui->EditBrightWidthNGH	->value();
	data.GetThresholdW()->Narrow.BrightWidthBL	=ui->EditBrightWidthNBL	->value();
	data.GetThresholdW()->Narrow.BrightWidthBH	=ui->EditBrightWidthNBH	->value();
	data.GetThresholdW()->Narrow.OKDot			=ui->EditOKDotN			->value();

	data.GetThresholdW()->AdjustBlack	=ui->EditAdjustBlack		->value();
	data.GetThresholdW()->AdjustWhite	=ui->EditAdjustWhite		->value();
	data.GetThresholdW()->SelfSearch	=ui->EditSelfSearch		->value();
}

void CreateManualDotColorMatchingDialog::on_ButtonOK_clicked()
{
	BItem->CopyThresholdFromLibrary(LLib);
	GetDataFromWindow(*BItem);
	done(true);
}

void CreateManualDotColorMatchingDialog::on_ButtonCancel_clicked()
{
	done(false);
}

void CreateManualDotColorMatchingDialog::on_toolButtonBroad_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void CreateManualDotColorMatchingDialog::on_toolButtonNarrow_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

