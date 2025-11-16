#include "PropertyGerberFastFormResource.h"
#include "EditLayerTypeDialog.h"
#include "ui_EditLayerTypeDialog.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "swap.h"
#include "XGerberFastPacket.h"
#include "XDataInLayer.h"
#include "XRememberer.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

extern	const	char	*AlgoRoot;
extern	const	char	*AlgoName;

EditLayerTypeDialog::EditLayerTypeDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditLayerTypeDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	pLibFolder=new GeneralLibFolderForm(-1,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolder,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	ui->tableWidgetLibList->setColumnWidth (0, 48);
	ui->tableWidgetLibList->setColumnWidth (1, 240);

	GerberFastBase	*BBase=GetGerberFastBase();
	TempLib=NULL;
	if(BBase!=NULL){
		pLibFolder->SetLibType(BBase->GetLibType());
		CmdCreateTempGerberFastLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	AlgorithmLibraryContainerForEnum		LibList(GetLayersBase());
	LibIDList.RemoveAll();
	if(BBase!=NULL){
		LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),BBase->GetLibType(),LibIDList);
	}
	ShowList();

	QString	DLLRoot,DLLName;
	if(BBase!=NULL){
		BBase->GetAlgorithmRootName(DLLRoot,DLLName);
	}
	pLibFolder->SetCurrentLibFolder(ControlRememberer::GetInt(DLLName+objectName()+pLibFolder->objectName(),0));

	ShowDataToWindow(NULL);

	InstallOperationLog(this);
}

EditLayerTypeDialog::~EditLayerTypeDialog()
{
    delete ui;
}

GerberFastBase	*EditLayerTypeDialog::GetGerberFastBase(void)
{
	GerberFastBase	*Base=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	return Base;
}

void	EditLayerTypeDialog::SetLibID(int LibID)
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
			ui->pushButtonUpdate	->setEnabled(true);
			ui->pushButtonDelete	->setEnabled(true);
		}
	}
}

void	EditLayerTypeDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;

	GerberFastBase	*BBase=GetGerberFastBase();
	QString	DLLRoot,DLLName;
	BBase->GetAlgorithmRootName(DLLRoot,DLLName);
	ControlRememberer::SetValue(DLLName+objectName()+pLibFolder->objectName() ,LibFolderID);

	ShowList();
}
void	EditLayerTypeDialog::ShowList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmLibraryContainerForEnum		LibList(GetLayersBase());
	LibIDList.RemoveAll();
	GerberFastBase	*BBase=GetGerberFastBase();
	LibList.EnumLibrary(GetLayersBase()->GetDatabase(),BBase->GetLibType(),LibFolderID ,LibIDList);

	int	row=0;
	ui->tableWidgetLibList->setRowCount(LibIDList.GetNumber());
	for(AlgorithmLibraryList *a=LibIDList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		::SetDataToTable(ui->tableWidgetLibList,0,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetLibList,1,row ,a->GetLibName());
	}
}
void	EditLayerTypeDialog::LibNewFunc(void)
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearGerberFastLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	GerberFastBase	*BBase=GetGerberFastBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowDataToWindow(TempLib);
	ui->pushButtonUpdate	->setEnabled(false);
	ui->pushButtonDelete	->setEnabled(false);
}

void EditLayerTypeDialog::on_pushButtonClose_clicked()
{
	close();
}

void EditLayerTypeDialog::on_pushButtonSaveNew_clicked()
{
	GerberFastBase	*GBase=GetGerberFastBase();
	if(GBase==NULL)
		return;

	GetDataFromWindow(TempLib);
	CmdInsertGerberFastLibraryPacket	Cmd(GetLayersBase());
	TempLib->SetLibFolderID(LibFolderID);
	Cmd.Point=TempLib;
	GBase->TransmitDirectly(&Cmd);

	ShowList();
}

void EditLayerTypeDialog::on_pushButtonUpdate_clicked()
{
	int	Row=ui->tableWidgetLibList->currentRow();
	if(Row<0)
		return;
	GerberFastBase	*GBase=GetGerberFastBase();
	if(GBase==NULL)
		return;
	GetDataFromWindow(TempLib);
	CmdUpdateGerberFastLibraryPacket	Cmd(GetLayersBase());
	Cmd.Point=TempLib;
	TempLib->SetLibFolderID(LibFolderID);
	GBase->TransmitDirectly(&Cmd);

	ShowList();
}

void EditLayerTypeDialog::on_pushButtonDelete_clicked()
{
	int	Row=ui->tableWidgetLibList->currentRow();
	if(Row<0)
		return;
	GerberFastBase	*GBase=GetGerberFastBase();
	if(GBase==NULL)
		return;
	CmdDeleteGerberFastLibraryPacket	Cmd(GetLayersBase());
	Cmd.Point=TempLib;
	GBase->TransmitDirectly(&Cmd);

	ShowList();
}

void EditLayerTypeDialog::ShowDataToWindow(AlgorithmLibraryLevelContainer *Attr)
{
	if(Attr!=NULL && Attr->GetLibID()>=0){
		GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(Attr->GetLibrary());
		ui->lineEditLibID				->setText (QString::number(Attr->GetLibID()));
		ui->lineEditLibName				->setText (ALib->GetLibName());
		ui->spinBoxMaxEnlargeDot		->setValue(ALib->MaxEnlargeDot);
		ui->spinBoxMaxShrinkageDot		->setValue(ALib->MaxShrinkDot);
		ui->spinBoxMaxShiftDot			->setValue(ALib->MaxShiftDot);
		ui->doubleSpinBoxMaxAngleRadius	->setValue(ALib->MaxAngleRadius);
		ui->doubleSpinBoxMaxUnstableZone->setValue(ALib->UnstableZone);
	}
	else{
		ui->lineEditLibID				->setText(/**/"");
		ui->lineEditLibName				->setText(/**/"");
		ui->spinBoxMaxEnlargeDot		->setValue(1);
		ui->spinBoxMaxShrinkageDot		->setValue(1);
		ui->spinBoxMaxShiftDot			->setValue(1);
		ui->doubleSpinBoxMaxAngleRadius	->setValue(1);
		ui->doubleSpinBoxMaxUnstableZone->setValue(1);
	}
}
void EditLayerTypeDialog::GetDataFromWindow(AlgorithmLibraryLevelContainer *Attr)
{
	if(Attr!=NULL){
		GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(Attr->GetLibrary());
		if(ALib!=NULL){
			Attr->SetLibName		(ui->lineEditLibName			->text());
			ALib->MaxEnlargeDot		=ui->spinBoxMaxEnlargeDot		->value();
			ALib->MaxShrinkDot		=ui->spinBoxMaxShrinkageDot		->value();
			ALib->MaxShiftDot		=ui->spinBoxMaxShiftDot			->value();
			ALib->MaxAngleRadius	=ui->doubleSpinBoxMaxAngleRadius->value();
			ALib->UnstableZone		=ui->doubleSpinBoxMaxUnstableZone->value();
		}
	}
}

void EditLayerTypeDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibIDList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadGerberFastLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		GerberFastBase	*BBase=GetGerberFastBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowDataToWindow(TempLib);
				ui->pushButtonUpdate	->setEnabled(true);
				ui->pushButtonDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void EditLayerTypeDialog::on_tableWidgetLibList_doubleClicked(const QModelIndex &Index)
{
	int	r=Index.row();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibIDList.GetItem(r);
	if(a!=NULL){
		GerberFastBase	*GBase=GetGerberFastBase();
		AlgorithmLibraryContainer	*ALib=GBase->GetLibraryContainer();
		if(ALib!=NULL){
			int		RetSelectedLibFolderID;
			QString RetSelectedFolderName;
			if(ExeSelectLibFolderDialog(ALib->GetLibType(),GetLayersBase(),NULL
									,RetSelectedLibFolderID
									,RetSelectedFolderName)==true){
				CmdUpdateGerberFastLibraryPacket	Cmd(GetLayersBase());
				Cmd.Point=TempLib;
				TempLib->SetLibFolderID(RetSelectedLibFolderID);
				GBase->TransmitDirectly(&Cmd);
				pLibFolder->Show();
			}
		}
	}
}
