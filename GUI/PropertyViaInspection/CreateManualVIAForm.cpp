#include "PropertyVIAInspectionFormResource.h"
#include "CreateManualVIAForm.h"
#include "ui_CreateManualVIAForm.h"
#include "XDLLOnly.h"
#include "XViaInspectionLibrary.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

CreateManualVIAForm::CreateManualVIAForm(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::CreateManualVIAForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);
	SelectedLibID=-1;
	VIALibID	 =-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempVIAItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(VIAItem *)ItemPacket.Point;
		CmdCreateTempVIALibraryPacket	LibPacket(GetLayersBase());
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

CreateManualVIAForm::~CreateManualVIAForm()
{
    delete ui;
	if(BItem!=NULL)
		delete	BItem;
	BItem=NULL;
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}

void	CreateManualVIAForm::Reflect(void)
{
	ui->EditLibID				->setText(QString::number(BItem->GetLibID()));
	VIALibID=BItem->GetLibID();
	CmdGetLibName	LibPacket(GetLayersBase());
	LibPacket.LibID=BItem->GetLibID();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&LibPacket);
	}
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

void	CreateManualVIAForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(Ab!=NULL){
		CmdGetVIALibraryListPacket	Packet(GetLayersBase());
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

void CreateManualVIAForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadVIALibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);

		if(Packet.Success==true){
			VIALibID				=TempLib->GetLibID();
	
			VIALibrary	*ALib=dynamic_cast<VIALibrary *>(TempLib->GetLibrary());
			ui->EditLibID			->setText(QString::number(ALib->GetLibID()));
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
								, LangSolver.GetString(CreateManualVIAForm_LS,LID_6)/*"Library error"*/
								, LangSolver.GetString(CreateManualVIAForm_LS,LID_7)/*"Not loaded this library record"*/);
		}
	}
}

void	CreateManualVIAForm::GetDataFromWindow(VIAItem &data)
{
	data.SetLibID(VIALibID);
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
}
void CreateManualVIAForm::on_ButtonOK_clicked()
{
	GetDataFromWindow(*BItem);
	done(true);
}

void CreateManualVIAForm::on_ButtonCancel_clicked()
{
	done(false);
}
