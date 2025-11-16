#include "CreateManualItemFormResource.h"
#include "EditLibraryForm.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditLibraryForm::EditLibraryForm(LayersBase *Base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LibFolderID =-1;
	MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempMeasureHolePosLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.tableWidgetLibList->setColumnWidth ( 0, 32);
	ui.tableWidgetLibList->setColumnWidth ( 1, 160);

	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
	InstallOperationLog(this);
}

EditLibraryForm::~EditLibraryForm()
{

}

MeasureHolePosBase	*EditLibraryForm::GetMeasureHolePosBase(void)
{
	return (MeasureHolePosBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
}

void	EditLibraryForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
	if(BBase!=NULL){
		CmdGetMeasureHolePosLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui.tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui.tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui.tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void	EditLibraryForm::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}
void EditLibraryForm::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearMeasureHolePosLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditLibraryForm::on_ButtonLibDelete_clicked()
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
		CmdDeleteMeasureHolePosLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibraryForm::on_ButtonLibSaveNew_clicked()
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
	CmdInsertMeasureHolePosLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryForm::on_ButtonLibSave_clicked()
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

		CmdInsertMeasureHolePosLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateMeasureHolePosLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryForm::on_pushButton_clicked()
{
	close();
}

void EditLibraryForm::on_pushButtonNColor_clicked()
{

}

void EditLibraryForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadMeasureHolePosLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}


void	EditLibraryForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	MeasureHolePosLibrary	*ALib=dynamic_cast<MeasureHolePosLibrary *>(data.GetLibrary());
	if(GetLayerNumb(0)>=3){
		HoleColor.Cube=ALib->HoleColor;
		HoleColor.InitializedDoneCube();
		HoleColor.Repaint();
	}
	else{
		int	ColL,ColH;
		ALib->HoleColor.GetMonoColorRange(ColL,ColH);
		ui.EditPickupL	->setValue(ColL);
		ui.EditPickupH	->setValue(ColH);
	}

	ui.doubleSpinBoxDiaPrecision	->setValue(ALib->DiaPrecision);
	ui.doubleSpinBoxPosPrecision	->setValue(ALib->PosPrecision);
	ui.spinBoxNoiseSize				->setValue(ALib->NoiseSize);
	ui.spinBoxBandWidth				->setValue(ALib->BandWidth);
	ui.EditSearchDot				->setValue(ALib->SearchDot);
	ui.comboBoxCalcMode				->setCurrentIndex(ALib->CalcMode);
}

void	EditLibraryForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	MeasureHolePosLibrary	*ALib=dynamic_cast<MeasureHolePosLibrary *>(data.GetLibrary());
	ALib->DiaPrecision	=ui.doubleSpinBoxDiaPrecision	->value();
	ALib->PosPrecision	=ui.doubleSpinBoxPosPrecision	->value();
	ALib->NoiseSize		=ui.spinBoxNoiseSize	->value();
	ALib->BandWidth		=ui.spinBoxBandWidth	->value();
	ALib->SearchDot		=ui.EditSearchDot		->value();
	ALib->CalcMode		=ui.comboBoxCalcMode	->currentIndex();

	if(GetLayerNumb(0)>=3){
		ALib->HoleColor	=HoleColor.Cube;
	}
	else{
		int	ColL=ui.EditPickupL	->value();
		int	ColH=ui.EditPickupH	->value();
		ALib->HoleColor.SetMonoColorRange(ColL,ColH,ColL,ColH,ColL,ColH);
	}
}

