#include "EditMultiSpectralLibraryDialog.h"
#include "ui_EditMultiSpectralLibraryDialog.h"
#include "XMultiSpectral.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include "XAlgorithmLibrary.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditMultiSpectralLibraryDialog::EditMultiSpectralLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::EditMultiSpectralLibraryDialog)
{
    ui->setupUi(this);
	LibFolderID =-1;
	MultiSpectralBase	*BBase=GetMultiSpectralBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	if(BBase!=NULL){
		CmdCreateTempMultiSpectralLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	else{
		LLib=new AlgorithmLibraryLevelContainer(BBase);
	}

	ui->tableWidgetLibList	->setColumnWidth(0,56);
	ui->tableWidgetLibList	->setColumnWidth(1,110);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	InstallOperationLog(this);
}

EditMultiSpectralLibraryDialog::~EditMultiSpectralLibraryDialog()
{
    delete ui;
}

MultiSpectralBase	*EditMultiSpectralLibraryDialog::GetMultiSpectralBase(void)
{
	return (MultiSpectralBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MultiSpectral");
}

void	EditMultiSpectralLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	MultiSpectralBase	*BBase=GetMultiSpectralBase();
	if(BBase!=NULL){
		CmdGetMultiSpectralLibraryListPacket	Packet(GetLayersBase());
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

void	EditMultiSpectralLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}
void EditMultiSpectralLibraryDialog::on_tableWidgetLibList_itemSelectionChanged()
{
	int	r=ui->tableWidgetLibList->currentRow();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadMultiSpectralLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		MultiSpectralBase	*BBase=GetMultiSpectralBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
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


void EditMultiSpectralLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearMultiSpectralLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	MultiSpectralBase	*BBase=GetMultiSpectralBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}


void EditMultiSpectralLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(LLib==NULL)
		return;
	if(LLib->GetLibID()<0)
		return;
	QString  msg=QString(/**/"Delete OK?");
	int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteMultiSpectralLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=LLib;
		MultiSpectralBase	*BBase=GetMultiSpectralBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}


void EditMultiSpectralLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);

	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	LLib->SetLibFolderID(LibFolderID);
	CmdInsertMultiSpectralLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	MultiSpectralBase	*BBase=GetMultiSpectralBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}


void EditMultiSpectralLibraryDialog::on_ButtonLibSave_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()<0){
		LLib->SetLibFolderID(LibFolderID);

		CmdInsertMultiSpectralLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		MultiSpectralBase	*BBase=GetMultiSpectralBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateMultiSpectralLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		MultiSpectralBase	*BBase=GetMultiSpectralBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}


void EditMultiSpectralLibraryDialog::on_pushButton_clicked()
{
	close();
}


void	EditMultiSpectralLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	MultiSpectralLibrary	*d=dynamic_cast<MultiSpectralLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->spinBoxSearchDot			->setValue(d->SearchDot);
	ui->doubleSpinBoxThresholdLength->setValue(d->ThresholdLength);
	ui->spinBoxOKDot				->setValue(d->OKDot);
}

void	EditMultiSpectralLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	MultiSpectralLibrary	*d=dynamic_cast<MultiSpectralLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->SearchDot		=ui->spinBoxSearchDot				->value();
	d->ThresholdLength	=ui->doubleSpinBoxThresholdLength	->value();
	d->OKDot			=ui->spinBoxOKDot					->value();
}