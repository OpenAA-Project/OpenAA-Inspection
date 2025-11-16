#include "PropertyGerberFastFormResource.h"
#include "SelectLibraryDialog.h"
#include "ui_SelectLibraryDialog.h"
#include <QTableWidgetItem>
#include "XDataAlgorithm.h"
#include "XGerberFastPacket.h"
#include "XGerberFast.h"
#include "EditLayerTypeDialog.h"
#include "XRememberer.h"
#include "XLibraryType.h"
#include "XGeneralDialog.h"

extern	const	char	*AlgoRoot;
extern	const	char	*AlgoName;


SelectLibraryDialog::SelectLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SelectLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SelectedLibID=-1;
	AlgorithmBase	*Ab=GetGerberFastBase();
	int	LibType=-1;
	if(Ab!=NULL){
		LibType=Ab->GetLibType();
		CmdCreateTempGerberFastLibraryPacket	LibPacket(GetLayersBase());
		Ab->TransmitDirectly(&LibPacket);
		TempLib=LibPacket.Point;
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui->tableWidgetLibList->setColumnWidth (0, 64);
	ui->tableWidgetLibList->setColumnWidth (1, 150);

	QString	DLLRoot,DLLName;
	GerberFastBase	*BBase=GetGerberFastBase();
	BBase->GetAlgorithmRootName(DLLRoot,DLLName);
	//pLibFolderForm->SetCurrentLibFolder(ControlRememberer::GetInt(DLLName+objectName()+pLibFolderForm->objectName(),0));

	InstallOperationLog(this);
}

SelectLibraryDialog::~SelectLibraryDialog()
{
    delete ui;
	delete	TempLib;
	TempLib=NULL;
}
GerberFastBase	*SelectLibraryDialog::GetGerberFastBase(void)
{
	GerberFastBase	*Base=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	return Base;
}
void	SelectLibraryDialog::SetLibID(int LibID)
{
	TempLib->SetLibID(LibID);

	CmdLoadGerberFastLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	GerberFastBase	*BBase=GetGerberFastBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
		if(Packet.Success==true){
			LibFolderID	=TempLib->GetLibFolderID();
			ShowDataToWindow(TempLib);
		}
	}
}
void	SelectLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;

	GerberFastBase	*BBase=GetGerberFastBase();
	QString	DLLRoot,DLLName;
	BBase->GetAlgorithmRootName(DLLRoot,DLLName);
	ControlRememberer::SetValue(DLLName+objectName()+pLibFolderForm->objectName() ,LibFolderID);

	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetGerberFastBase();
	if(Ab!=NULL){
		CmdGetGerberFastLibraryListPacket	Packet(GetLayersBase());
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

void SelectLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &index)
{
	QModelIndex	RIndex=ui->tableWidgetLibList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	AlgorithmBase	*Ab=GetGerberFastBase();
	if(Ab!=NULL){
		AlgorithmLibraryList	*a=LibList.GetItem(R);
		if(a!=NULL){
			TempLib->SetLibID(a->GetLibID());
			CmdLoadGerberFastLibraryPacket	Packet(GetLayersBase());
			Packet.Point=TempLib;
			Ab->TransmitDirectly(&Packet);
		}
		ShowDataToWindow(TempLib);
	}
}

void SelectLibraryDialog::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_ButtonSelect_clicked();
}

void SelectLibraryDialog::on_ButtonSelect_clicked()
{
	QModelIndex	RIndex=ui->tableWidgetLibList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	AlgorithmLibraryList	*a=LibList.GetItem(R);
	if(a!=NULL){
		SelectedLibID=a->GetLibID();
		done(QDialog::Accepted);
	}
}

void SelectLibraryDialog::on_ButtonCancel_clicked()
{
	done(QDialog::Rejected);
}
void SelectLibraryDialog::ShowDataToWindow(AlgorithmLibraryLevelContainer *Attr)
{
	GerberFastLibrary	*ALib=NULL;
	if(Attr!=NULL){
		ALib=dynamic_cast<GerberFastLibrary *>(Attr->GetLibrary());
	}
	if(Attr!=NULL && Attr->GetLibID()>=0 && ALib!=NULL){
		ui->lineEditLayerTypeLibID		->setText(QString::number(Attr->GetLibID()));
		ui->lineEditLayerTypeName		->setText (Attr->GetLibName());
		ui->spinBoxMaxEnlargeDot		->setValue(ALib->MaxEnlargeDot);
		ui->spinBoxMaxShrinkageDot		->setValue(ALib->MaxShrinkDot);
		ui->spinBoxMaxShiftDot			->setValue(ALib->MaxShiftDot);
		ui->doubleSpinBoxMaxAngleRadius	->setValue(ALib->MaxAngleRadius);
		ui->doubleSpinBoxMaxUnstableZone->setValue(ALib->UnstableZone);
	}
	else{
		ui->lineEditLayerTypeLibID		->setText(/**/"");
		ui->lineEditLayerTypeName		->setText(/**/"");
		ui->spinBoxMaxEnlargeDot		->setValue(1);
		ui->spinBoxMaxShrinkageDot		->setValue(1);
		ui->spinBoxMaxShiftDot			->setValue(1);
		ui->doubleSpinBoxMaxAngleRadius	->setValue(1);
		ui->doubleSpinBoxMaxUnstableZone->setValue(1);
	}
}
void SelectLibraryDialog::on_ButtonClear_clicked()
{
	done(3);
}

void SelectLibraryDialog::on_pushButtonEditLibrary_clicked()
{
	EditLayerTypeDialog	D(GetLayersBase());
	D.exec();
	SlotSelectLibFolder(LibFolderID ,/**/"");
}
