#include "CreateManualDotMatchingFormResource.h"
#include "CreateManualDotMatchingForm.h"
#include "ui_CreateManualDotMatchingForm.h"
#include "XDLLOnly.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

CreateManualDotMatchingForm::CreateManualDotMatchingForm(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::CreateManualDotMatchingForm)
{
    ui->setupUi(this);

	SelectedLibID=-1;
	DotMatchingLibID	 =-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotMatching");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempDotMatchingItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(DotMatchingItem *)ItemPacket.Point;
		CmdCreateTempDotMatchingLibraryPacket	LibPacket(GetLayersBase());
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

CreateManualDotMatchingForm::~CreateManualDotMatchingForm()
{
    delete ui;
	if(BItem!=NULL)
		delete	BItem;
	BItem=NULL;
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}

void	CreateManualDotMatchingForm::Reflect(void)
{
	ui->EditLibID				->setText(QString::number(BItem->GetLibID()));
	DotMatchingLibID=BItem->GetLibID();
	CmdGetLibName	LibPacket(GetLayersBase());
	LibPacket.LibID=BItem->GetLibID();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotMatching");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&LibPacket);
	}
	ui->EditLibName				->setText(LibPacket.LibName);
	ui->EditBrightWidthL		->setValue(BItem->GetThresholdR()->BrightWidthL);
	ui->EditBrightWidthH		->setValue(BItem->GetThresholdR()->BrightWidthH);
	ui->EditOKDot				->setValue(BItem->GetThresholdR()->OKDot);

	ui->EditAdjustBlack			->setValue(BItem->GetThresholdR()->AdjustBlack);
	ui->EditAdjustWhite			->setValue(BItem->GetThresholdR()->AdjustWhite);
	ui->EditSelfSearch			->setValue(BItem->GetThresholdR()->SelfSearch);
}

void	CreateManualDotMatchingForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotMatching");
	if(Ab!=NULL){
		CmdGetDotMatchingLibraryListPacket	Packet(GetLayersBase());
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


void CreateManualDotMatchingForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadDotMatchingLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotMatching");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);

		if(Packet.Success==true){
			DotMatchingLibID					=TempLib->GetLibID();
			DotMatchingLibrary	*ALib=dynamic_cast<DotMatchingLibrary *>(TempLib->GetLibrary());

			ui->EditLibID			->setText(QString::number(ALib->GetLibID()));
			ui->EditLibName			->setText(a->GetLibName());

			ui->EditBrightWidthL	->setValue(ALib->BrightWidthL);
			ui->EditBrightWidthH	->setValue(ALib->BrightWidthH);
			ui->EditOKDot			->setValue(ALib->OKDot);

			ui->EditAdjustBlack		->setValue(ALib->AdjustBlack);
			ui->EditAdjustWhite		->setValue(ALib->AdjustWhite);
			ui->EditSelfSearch		->setValue(ALib->SelfSearch);

			ui->ButtonOK->setEnabled(true);
		}
		else{
			QMessageBox::critical(NULL, LangSolver.GetString(CreateManualDotMatchingForm_LS,LID_0)/*"Library error"*/
									, LangSolver.GetString(CreateManualDotMatchingForm_LS,LID_1)/*"Not loaded this library record"*/);
		}
	}
}

void	CreateManualDotMatchingForm::GetDataFromWindow(DotMatchingItem &data)
{
	data.SetLibID(DotMatchingLibID);
	data.GetThresholdW()->BrightWidthL	=ui->EditBrightWidthL	->value();
	data.GetThresholdW()->BrightWidthH	=ui->EditBrightWidthH	->value();
	data.GetThresholdW()->OKDot			=ui->EditOKDot			->value();

	data.GetThresholdW()->AdjustBlack	=ui->EditAdjustBlack		->value();
	data.GetThresholdW()->AdjustWhite	=ui->EditAdjustWhite		->value();
	data.GetThresholdW()->SelfSearch	=ui->EditSelfSearch		->value();
}

void CreateManualDotMatchingForm::on_ButtonOK_clicked()
{
	GetDataFromWindow(*BItem);
	done(true);
}

void CreateManualDotMatchingForm::on_ButtonCancel_clicked()
{
	done(false);
}
