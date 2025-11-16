#include "PropertyMeasureLineMoveFormResource.h"
#include "SelectLibraryDialog.h"
#include "ui_SelectLibraryDialog.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include <QMessageBox>

SelectLibraryDialog::SelectLibraryDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::SelectLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SelectedID=-1;
	LibFolderID =-1;
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempMeasureLineMoveLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui->tableWidgetLibList->setColumnWidth ( 0, 32);
	ui->tableWidgetLibList->setColumnWidth ( 1, 160);

	ui->pushButtonSelect->setEnabled(false);
	InstallOperationLog(this);
}

SelectLibraryDialog::~SelectLibraryDialog()
{
    delete ui;
}



MeasureLineMoveBase	*SelectLibraryDialog::GetMeasureLineMoveBase(void)
{
	return (MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
}

void	SelectLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
	if(BBase!=NULL){
		CmdGetMeasureLineMoveLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibIDList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=LibIDList.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
	AlgorithmLibraryList	*a=LibIDList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		SelectedID	=a->GetLibID();

		CmdLoadMeasureLineMoveLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
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

void	SelectLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	MeasureLineMoveLibrary	*d=dynamic_cast<MeasureLineMoveLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->EditSearchDot			->setValue(d->SearchDot);
	ui->doubleSpinBoxThresholdM	->setValue(d->ThresholdM);
	ui->doubleSpinBoxThresholdP	->setValue(d->ThresholdP);
	ui->EditEdgeWidth			->setValue(d->EdgeWidth);
}

void SelectLibraryDialog::on_pushButtonSelect_clicked()
{
	ItemName	=ui->EditItemName->text();
	done(true);
}

void SelectLibraryDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
