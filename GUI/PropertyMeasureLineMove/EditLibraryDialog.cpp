#include "PropertyMeasureLineMoveFormResource.h"
#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include <QMessageBox>

EditLibraryDialog::EditLibraryDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::EditLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

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


	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
	InstallOperationLog(this);
}

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
}


MeasureLineMoveBase	*EditLibraryDialog::GetMeasureLineMoveBase(void)
{
	return (MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
}

void	EditLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
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

void	EditLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void EditLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibIDList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadMeasureLineMoveLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
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

void EditLibraryDialog::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearMeasureLineMoveLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
}

void EditLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=QString(/**/"Delete OK?");
	int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteMeasureLineMoveLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertMeasureLineMoveLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertMeasureLineMoveLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateMeasureLineMoveLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_pushButton_clicked()
{
	close();
}

void	EditLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	MeasureLineMoveLibrary	*d=dynamic_cast<MeasureLineMoveLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->EditSearchDot					->setValue	(d->SearchDot	);
	ui->doubleSpinBoxThresholdM			->setValue	(d->ThresholdM	);
	ui->doubleSpinBoxThresholdP			->setValue	(d->ThresholdP	);
	ui->EditEdgeWidth					->setValue	(d->EdgeWidth	);
	ui->checkBoxPrevailLeft				->setChecked(d->PrevailLeft	);
	ui->checkBoxPrevailRight			->setChecked(d->PrevailRight	);
	ui->checkBoxModeToSetInInitial		->setChecked(d->ModeToSetInInitial);
	ui->doubleSpinBoxOKRangeInInitial	->setValue	(d->OKRangeInInitial	);
	ui->comboBoxOutputType				->setCurrentIndex(d->OutputType);
	ui->comboBoxSearchType				->setCurrentIndex(d->SearchType);
	ui->doubleSpinBoxThresholdRate		->setValue	(d->ThresholdRate	);
}

void	EditLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	MeasureLineMoveLibrary	*d=dynamic_cast<MeasureLineMoveLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->SearchDot			=ui->EditSearchDot					->value();
	d->ThresholdM			=ui->doubleSpinBoxThresholdM		->value();
	d->ThresholdP			=ui->doubleSpinBoxThresholdP		->value();
	d->EdgeWidth			=ui->EditEdgeWidth					->value();
	d->PrevailLeft			=ui->checkBoxPrevailLeft			->isChecked();
	d->PrevailRight			=ui->checkBoxPrevailRight			->isChecked();
	d->ModeToSetInInitial	=ui->checkBoxModeToSetInInitial		->isChecked();
	d->OKRangeInInitial		=ui->doubleSpinBoxOKRangeInInitial	->value();
	d->OutputType			=ui->comboBoxOutputType				->currentIndex();
	d->SearchType			=ui->comboBoxSearchType				->currentIndex();
	d->ThresholdRate		=ui->doubleSpinBoxThresholdRate		->value();
}
