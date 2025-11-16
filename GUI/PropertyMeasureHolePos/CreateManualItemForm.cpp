#include "CreateManualItemFormResource.h"
#include "CreateManualItemForm.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

CreateManualItemForm::CreateManualItemForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),ColorSamples(Base)
{
	ui.setupUi(this);

	SelectedLibID=-1;
	LibID		=-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempMeasureHolePosItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(MeasureHolePosItem *)ItemPacket.Point;
		CmdCreateTempMeasureHolePosLibraryPacket	LibPacket(GetLayersBase());
		Ab->TransmitDirectly(&LibPacket);
		TempLib=LibPacket.Point;
		LibType=Ab->GetLibType();
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetLibList->setRowCount(0);

	ColorGenerator		.setParent(ui.frameColorCube);
	ColorGenerator		.Fit(ui.frameColorCube);

	//ColorSamples.setParent(ui.frameColorSample);
	//ColorSamples.move(0,0);

	ui.ButtonOK->setEnabled(false);
	InstallOperationLog(this);
}

CreateManualItemForm::~CreateManualItemForm()
{

}

void	CreateManualItemForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
	if(Ab!=NULL){
		CmdGetMeasureHolePosLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		Ab->TransmitDirectly(&Packet);
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

void CreateManualItemForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());
	CmdLoadMeasureHolePosLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);
		if(Packet.Success==true){
			LibID					=TempLib->GetLibID();
			ui.EditLibID			->setText(QString::number(TempLib->GetLibID()));
			ui.EditLibName			->setText(a->GetLibName());

			MeasureHolePosLibrary	*ALib=dynamic_cast<MeasureHolePosLibrary *>(TempLib->GetLibrary());
			ui.doubleSpinBoxDiaPrecision	->setValue(ALib->DiaPrecision);
			ui.doubleSpinBoxPosPrecision	->setValue(ALib->PosPrecision);
			ui.spinBoxNoiseSize				->setValue(ALib->NoiseSize);
			ui.spinBoxBandWidth				->setValue(ALib->BandWidth);
			ui.EditSearchDot				->setValue(ALib->SearchDot);
			ui.comboBoxCalcMode				->setCurrentIndex(ALib->CalcMode);
			if(GetLayerNumb(0)>=3){
				ColorGenerator.Cube			=ALib->HoleColor;
				ColorGenerator.InitializedDoneCube();
				ColorGenerator.Repaint();
			}
			else{
				int	ColL,ColH;
				ALib->HoleColor.GetMonoColorRange(ColL,ColH);
				ui.EditPickupL	->setValue(ColL);
				ui.EditPickupH	->setValue(ColH);
			}

			ui.ButtonOK->setEnabled(true);
		}
		else{
			QMessageBox::critical(NULL, LangSolver.GetString(CreateManualItemForm_LS,LID_0)/*"Library error"*/, LangSolver.GetString(CreateManualItemForm_LS,LID_1)/*"Not loaded this library record"*/);
		}
	}
}

void	CreateManualItemForm::GetDataFromWindow(MeasureHolePosItem &data)
{
	data.SetLibID(LibID);

	if(GetLayerNumb(0)>=3){
		data.GetThresholdW()->HoleColor					=ColorGenerator.Cube;
	}
	else{
		int	ColL	=ui.EditPickupL	->value();
		int	ColH	=ui.EditPickupH	->value();
		data.GetThresholdW()->HoleColor.SetMonoColorRange(ColL,ColH,ColL,ColH,ColL,ColH);
	}
	data.GetThresholdW()->DiaPrecision		=ui.doubleSpinBoxDiaPrecision	->value();
	data.GetThresholdW()->PosPrecision		=ui.doubleSpinBoxPosPrecision	->value();
	data.GetThresholdW()->NoiseSize			=ui.spinBoxNoiseSize	->value();
	data.GetThresholdW()->BandWidth			=ui.spinBoxBandWidth	->value();
	data.GetThresholdW()->SearchDot			=ui.EditSearchDot		->value();
	data.GetThresholdW()->CalcMode			=ui.comboBoxCalcMode	->currentIndex();
}

void CreateManualItemForm::on_pushButtonNColor_clicked()
{

}

void CreateManualItemForm::on_ButtonOK_clicked()
{
	GetDataFromWindow(*BItem);
	done(true);
}

void CreateManualItemForm::on_ButtonCancel_clicked()
{
	done(false);
}