#include "CreateManualMeasureHoleFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureHole\CreateManualMeasureHoleForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "CreateManualMeasureHoleForm.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

CreateManualMeasureHoleForm::CreateManualMeasureHoleForm(LayersBase *Base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),ColorSamples(Base)
{
	ui.setupUi(this);

	SelectedLibID=-1;
	LibID		=-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHole");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempMeasureHoleItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(MeasureHoleItem *)ItemPacket.Point;
		CmdCreateTempMeasureHoleLibraryPacket	LibPacket(GetLayersBase());
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

	ColorSamples.setParent(ui.frameColorSample);
	ColorSamples.move(0,0);
	//connect(&ColorSamples,SIGNAL(SignalBeforeSave ()),this,SLOT(SlotColorSampleBeforeSave()));
	//connect(&ColorSamples,SIGNAL(SignalSelectCData()),this,SLOT(SlotColorSampleSelectOne()));

	ui.pushButtonOK->setEnabled(false);
	InstallOperationLog(this);
}

CreateManualMeasureHoleForm::~CreateManualMeasureHoleForm()
{

}

void	CreateManualMeasureHoleForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHole");
	if(Ab!=NULL){
		CmdGetMeasureHoleLibraryListPacket	Packet(GetLayersBase());
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

void CreateManualMeasureHoleForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());
	CmdLoadMeasureHoleLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHole");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);
		if(Packet.Success==true){
			LibID					=TempLib->GetLibID();
			ui.EditLibID			->setText(QString::number(TempLib->GetLibID()));
			ui.EditLibName			->setText(a->GetLibName());

			MeasureHoleLibrary	*ALib=dynamic_cast<MeasureHoleLibrary *>(TempLib->GetLibrary());
			ui.EditMinDiameter		->setValue(ALib->MinDiameter);
			ui.EditMaxDiameter		->setValue(ALib->MaxDiameter);
			ui.EditNoiseSize		->setValue(ALib->NoiseSize);
			ui.EditSearchDot		->setValue(ALib->SearchDot);
			ColorGenerator.Cube		=ALib->CupperColor;
			ColorGenerator.InitializedDoneCube();
			ColorGenerator.Repaint();

			ui.pushButtonOK->setEnabled(true);
		}
		else{
			QMessageBox::critical(NULL, LangSolver.GetString(CreateManualMeasureHoleForm_LS,LID_0)/*"Library error"*/, LangSolver.GetString(CreateManualMeasureHoleForm_LS,LID_1)/*"Not loaded this library record"*/);
		}
	}
}

void	CreateManualMeasureHoleForm::GetDataFromWindow(MeasureHoleItem &data)
{
	data.SetLibID(LibID);

	if(GetLayerNumb(0)>=3){
		data.GetThresholdW()->CupperColor					=ColorGenerator.Cube;
	}
	else{
		int	ColL=0;//	=ui.EditPickupL	->value();
		int	ColH=0;//	=ui.EditPickupH	->value();
		data.GetThresholdW()->CupperColor.SetMonoColorRange(ColL,ColH,ColL,ColH,ColL,ColH);
	}
	data.GetThresholdW()->MinDiameter					=ui.EditMinDiameter		->value();
	data.GetThresholdW()->MaxDiameter					=ui.EditMaxDiameter		->value();
	data.GetThresholdW()->NoiseSize						=ui.EditNoiseSize		->value();
	data.GetThresholdW()->SearchDot						=ui.EditSearchDot		->value();
}


void CreateManualMeasureHoleForm::on_pushButtonAddColor_clicked()
{
	ColorGenerator.Cube.Add(*ColorSamples.CData.GetColorLogic());
	ColorGenerator.Repaint();
}

void CreateManualMeasureHoleForm::on_pushButtonEliminateColor_clicked()
{
	ColorGenerator.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
	ColorGenerator.Repaint();
}

void CreateManualMeasureHoleForm::on_pushButtonOK_clicked()
{
	GetDataFromWindow(*BItem);
	done(true);
}

void CreateManualMeasureHoleForm::on_pushButtonCancel_clicked()
{
	done(false);
}