#include "XVIAInspectionResource.h"
#include "ChangeCreateVIAForm.h"
#include "ui_ChangeCreateVIAForm.h"
//#include "VIAFormResource.h"
#include "XViaInspectionLibrary.h"
#include "ChangeCreateVIAForm.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XGeneralDialog.h"

ChangeCreateVIAForm::ChangeCreateVIAForm(VIABase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base->GetLayersBase()),
    ui(new Ui::ChangeCreateVIAForm)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);
	Base=base;
	LibFolderID =-1;
	pLibFolderForm=new GeneralLibFolderForm(base->GetLibType(),GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);

	CmdCreateTempVIALibraryPacket	Packet(GetLayersBase());
	Base->TransmitDirectly(&Packet);
	TempLib=Packet.Point;

	InstallOperationLog(this);
}

ChangeCreateVIAForm::~ChangeCreateVIAForm()
{
    delete ui;
}

void	ChangeCreateVIAForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);

	CmdGetVIALibraryListPacket	Packet(GetLayersBase());
	Packet.LibFolderID=LibFolderID;
	Base->TransmitDirectly(&Packet);
	LibList	=Packet.AList;
	int	row=0;
	ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
	for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui->tableWidgetLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetLibList->setItem ( row, 0,W);
		}
		W->setText(QString::number(a->GetLibID()));
		W=ui->tableWidgetLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetLibList->setItem ( row, 1,W);
		}
		W->setText(a->GetLibName());		
	}
}

void	ChangeCreateVIAForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	VIALibrary	*ALib=dynamic_cast<VIALibrary *>(data.GetLibrary());

	ui->EditBrightWidthL		->setValue(ALib->BrightWidthL);
	ui->EditBrightWidthH		->setValue(ALib->BrightWidthH);
	ui->EditOKDotL				->setValue(ALib->OKDotL);
	ui->EditOKDotH				->setValue(ALib->OKDotH);
	ui->EditOKLengthL			->setValue(ALib->OKLengthL);
	ui->EditOKLengthH			->setValue(ALib->OKLengthH);
	ui->EditMaxNGDotL			->setValue(ALib->MaxNGDotL);
	ui->EditMaxNGDotH			->setValue(ALib->MaxNGDotH);
	ui->EditShrinkDot			->setValue(ALib->ShrinkDot);
	ui->EditEnlargeDot			->setValue(ALib->EnlargeDot);
}


void	ChangeCreateVIAForm::GetItemFromWindow(VIAItem &data)
{
	data.SetLibID(TempLib->GetLibID());

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

void ChangeCreateVIAForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadVIALibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;

		Base->TransmitDirectly(&Packet);
		ShowLibrary(*TempLib);
	}
}

void ChangeCreateVIAForm::on_ButtonOK_clicked()
{
	GetItemFromWindow(ResultVIA);
	done(true);
}

void ChangeCreateVIAForm::on_ButtonCancel_clicked()
{
	done(false);
}
