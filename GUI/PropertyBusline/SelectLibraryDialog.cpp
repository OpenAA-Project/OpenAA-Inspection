#include "PropertyBuslineFormResource.h"
#include "SelectLibraryDialog.h"
#include "ui_SelectLibraryDialog.h"
#include "XLibraryType.h"
#include <QMessageBox>
#include "XGeneralFunc.h"
#include "XGeneralDialog.h"

SelectLibraryDialog::SelectLibraryDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::SelectLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SelectedID	=-1;
	LibFolderID =-1;
	BuslineBase	*BBase=GetBuslineBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempBuslineLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui->tableWidgetLibList->setColumnWidth ( 0, 32);
	ui->tableWidgetLibList->setColumnWidth ( 1, 160);

	ui->pushButtonSelect	->setEnabled(false);
	InstallOperationLog(this);
}

SelectLibraryDialog::~SelectLibraryDialog()
{
    delete ui;
}
BuslineBase	*SelectLibraryDialog::GetBuslineBase(void)
{
	return (BuslineBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Busline");
}

void	SelectLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	BuslineBase	*BBase=GetBuslineBase();
	if(BBase!=NULL){
		CmdGetBuslineLibraryListPacket	Packet(GetLayersBase());
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
void	SelectLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}
void SelectLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		SelectedID	=a->GetLibID();

		CmdLoadBuslineLibraryPacket		Packet(GetLayersBase());
		Packet.Point=TempLib;
		BuslineBase	*BBase=GetBuslineBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui->pushButtonSelect->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void SelectLibraryDialog::on_pushButtonSelect_clicked()
{
	done(true);
}

void SelectLibraryDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
void	SelectLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	BuslineLibrary	*ALib=dynamic_cast<BuslineLibrary *>(data.GetLibrary());
	ui->EditMinWidth				->setValue(ALib->MinWidth);
	ui->EditMinGap					->setValue(ALib->MinGap);
	ui->lineEditMinArea				->setText(QString::number(ALib->MinArea));
	ui->lineEditMaxArea				->setText(QString::number(ALib->MaxArea));
	ui->EditMinSize					->setValue	(ALib->MinSize);
	ui->checkBoxDarkside			->setChecked(ALib->Darkside);
	ui->checkBoxCompareToMaster		->setChecked(ALib->CompareToMaster);
	ui->checkBoxAutoBinarize		->setChecked(ALib->AutoBinarize);
	ui->checkBoxReduceNoise			->setChecked(ALib->ReduceNoise);
	ui->EditBinarizedLength			->setValue	(ALib->BinarizedLength);
	ui->EditReferredBrightness		->setValue	(ALib->ReferredBrightness);
	ui->EditSearchDotToMaster		->setValue	(ALib->SearchDotToMaster);
	ui->EditBrightnessWidthInsideL 	->setValue	(ALib->BrightnessWidthInsideL );
	ui->EditBrightnessWidthInsideH 	->setValue	(ALib->BrightnessWidthInsideH );
	ui->EditBrightnessWidthOutsideL	->setValue	(ALib->BrightnessWidthOutsideL);
	ui->EditBrightnessWidthOutsideH	->setValue	(ALib->BrightnessWidthOutsideH);
}