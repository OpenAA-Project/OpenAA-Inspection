#include "PropertyThinMetalFormResource.h"
#include "CreateManualThinMetalForm.h"
#include "ui_CreateManualThinMetalForm.h"
#include "XDLLOnly.h"
#include "XGeneralDialog.h"
#include "XThinMetalLibrary.h"
#include <QMessageBox>

CreateManualThinMetalForm::CreateManualThinMetalForm(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::CreateManualThinMetalForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);
	SelectedLibID=-1;
	ThinMetalLibID	 =-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempThinMetalItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(ThinMetalItem *)ItemPacket.Point;
		CmdCreateTempThinMetalLibraryPacket	LibPacket(GetLayersBase());
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

	InstallOperationLog(this);
}

CreateManualThinMetalForm::~CreateManualThinMetalForm()
{
    delete ui;
	if(BItem!=NULL)
		delete	BItem;
	BItem=NULL;
	if(LLib!=NULL)
		delete	LLib;
	LLib=NULL;
}

void	CreateManualThinMetalForm::Reflect(void)
{
	ui->EditLibID				->setText(QString::number(BItem->GetLibID()));
	ThinMetalLibID=BItem->GetLibID();
	CmdGetLibName	LibPacket(GetLayersBase());
	LibPacket.LibID=BItem->GetLibID();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&LibPacket);
	}
	ui->EditItemName		->setText(BItem->GetItemName());
	ui->EditLibName			->setText(LibPacket.LibName);
	ui->EditBrightWidthL	->setValue(BItem->GetThresholdR()->BrightWidthL);
	ui->EditBrightWidthH	->setValue(BItem->GetThresholdR()->BrightWidthH);
	ui->EditOKDotL			->setValue(BItem->GetThresholdR()->OKDotL);
	ui->EditOKDotH			->setValue(BItem->GetThresholdR()->OKDotH);
	ui->EditOKLengthL		->setValue(BItem->GetThresholdR()->OKLengthL);
	ui->EditOKLengthH		->setValue(BItem->GetThresholdR()->OKLengthH);
	ui->EditMaxNGDotL		->setValue(BItem->GetThresholdR()->MaxNGDotL);
	ui->EditMaxNGDotH		->setValue(BItem->GetThresholdR()->MaxNGDotH);
	ui->EditShrinkDot		->setValue(BItem->GetThresholdR()->ShrinkDot);
	ui->EditEnlargeDot		->setValue(BItem->GetThresholdR()->EnlargeDot);
}

void	CreateManualThinMetalForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(Ab!=NULL){
		CmdGetThinMetalLibraryListPacket	Packet(GetLayersBase());
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

void CreateManualThinMetalForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	LLib->SetLibID(a->GetLibID());

	CmdLoadThinMetalLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);

		if(Packet.Success==true){
			ThinMetalLibrary	*ALib=dynamic_cast<ThinMetalLibrary *>(LLib->GetLibrary());
			ThinMetalLibID				=LLib->GetLibID();
			ui->EditLibID			->setText(QString::number(LLib->GetLibID()));
			ui->EditLibName			->setText(a->GetLibName());

			ui->EditBrightWidthL	->setValue(ALib->BrightWidthL);
			ui->EditBrightWidthH	->setValue(ALib->BrightWidthH);
			ui->EditOKDotL			->setValue(ALib->OKDotL);
			ui->EditOKDotH			->setValue(ALib->OKDotH);
			ui->EditOKLengthL		->setValue(ALib->OKLengthL);
			ui->EditOKLengthH		->setValue(ALib->OKLengthH);

			ui->EditMaxNGDotL		->setValue(ALib->MaxNGDotL);
			ui->EditMaxNGDotH		->setValue(ALib->MaxNGDotH);
			ui->EditShrinkDot		->setValue(ALib->ShrinkDot);
			ui->EditEnlargeDot		->setValue(ALib->EnlargeDot);
			ui->ButtonOK->setEnabled(true);
		}
		else{
			QMessageBox::critical(NULL
								, LangSolver.GetString(CreateManualThinMetalForm_LS,LID_6)/*"Library error"*/
								, LangSolver.GetString(CreateManualThinMetalForm_LS,LID_7)/*"Not loaded this library record"*/);
		}
	}
}

void	CreateManualThinMetalForm::GetDataFromWindow(ThinMetalItem &data)
{
	data.SetLibID(ThinMetalLibID);
	data.GetThresholdW()->BrightWidthL	=ui->EditBrightWidthL	->value();
	data.GetThresholdW()->BrightWidthH	=ui->EditBrightWidthH	->value();
	data.GetThresholdW()->OKDotL		=ui->EditOKDotL			->value();
	data.GetThresholdW()->OKDotH		=ui->EditOKDotH			->value();
	data.GetThresholdW()->OKLengthL		=ui->EditOKLengthL		->value();
	data.GetThresholdW()->OKLengthH		=ui->EditOKLengthH		->value();

	data.GetThresholdW()->MaxNGDotL		=ui->EditMaxNGDotL		->value();
	data.GetThresholdW()->MaxNGDotH		=ui->EditMaxNGDotH		->value();
	data.GetThresholdW()->ShrinkDot		=ui->EditShrinkDot		->value();
	data.GetThresholdW()->EnlargeDot	=ui->EditEnlargeDot		->value();
	data.SetItemName(ui->EditItemName->text());
}
void CreateManualThinMetalForm::on_ButtonOK_clicked()
{
	GetDataFromWindow(*BItem);
	done(true);
}

void CreateManualThinMetalForm::on_ButtonCancel_clicked()
{
	done(false);
}
