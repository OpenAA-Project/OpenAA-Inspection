/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\ColorChangeCreateBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ColorBlockFormResource.h"
#include "ColorChangeCreateBlockForm.h"
#include "XDLLOnly.h"
#include "ColorSelectBlockLibraryForm.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XGeneralDialog.h"

ColorChangeCreateBlockForm::ColorChangeCreateBlockForm(ColorBlockBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base->GetLayersBase())
	,ButtonR(false),ButtonG(false),ButtonB(false)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	Base=base;
	LibFolderID =-1;
	pLibFolderForm=new GeneralLibFolderForm(base->GetLibType(),GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);

	CmdCreateTempColorBlockLibraryPacket	Packet(GetLayersBase());
	Base->TransmitDirectly(&Packet);
	TempLib=Packet.Point;

	ButtonR.setParent(ui.frame_5);
	ButtonG.setParent(ui.frame_5);
	ButtonB.setParent(ui.frame_5);

	ButtonR.setGeometry(ui.toolButtonR->geometry());
	ButtonG.setGeometry(ui.toolButtonG->geometry());
	ButtonB.setGeometry(ui.toolButtonB->geometry());

	ButtonR.setAutoExclusive(true);
	ButtonG.setAutoExclusive(true);
	ButtonB.setAutoExclusive(true);

	CurrentColor=0;
	ButtonR.setChecked(true);
	delete	ui.toolButtonR;
	ui.toolButtonR=NULL;
	delete	ui.toolButtonG;
	ui.toolButtonG=NULL;
	delete	ui.toolButtonB;
	ui.toolButtonB=NULL;

	ButtonR.setColor(GetParamGlobal()->GetOneGraphLayerColor(0));
	ButtonG.setColor(GetParamGlobal()->GetOneGraphLayerColor(1));
	ButtonB.setColor(GetParamGlobal()->GetOneGraphLayerColor(2));

	ButtonR.setText(GetParamGlobal()->GetLayerName(0));
	ButtonG.setText(GetParamGlobal()->GetLayerName(1));
	ButtonB.setText(GetParamGlobal()->GetLayerName(2));

	connect(&ButtonR,SIGNAL(clicked()),this,SLOT(on_ToolButton_clicked()));
	connect(&ButtonG,SIGNAL(clicked()),this,SLOT(on_ToolButton_clicked()));
	connect(&ButtonB,SIGNAL(clicked()),this,SLOT(on_ToolButton_clicked()));

	InstallOperationLog(this);
}

ColorChangeCreateBlockForm::~ColorChangeCreateBlockForm()
{

}

void	ColorChangeCreateBlockForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);

	CmdGetColorBlockLibraryListPacket	Packet(GetLayersBase());
	Packet.LibFolderID=LibFolderID;
	Base->TransmitDirectly(&Packet);
	LibList	=Packet.AList;
	int	row=0;
	ui.tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
	for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui.tableWidgetLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetLibList->setItem ( row, 0,W);
		}
		W->setText(QString::number(a->GetLibID()));
		W=ui.tableWidgetLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetLibList->setItem ( row, 1,W);
		}
		W->setText(a->GetLibName());		
	}
}

void ColorChangeCreateBlockForm::on_ButtonOK_clicked()
{
	GetItemFromWindow(ResultBlock);
	done(true);
}

void ColorChangeCreateBlockForm::on_ButtonCancel_clicked()
{
	done(false);
}

void	ColorChangeCreateBlockForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(data.GetLibrary());
	ColorBlockLibrary::InspectionData	*Ins=NULL;
	if(ButtonR.isChecked()==true){
		Ins=&ALib->InsR;
		CurrentColor=0;
	}
	else if(ButtonG.isChecked()==true){
		Ins=&ALib->InsG;
		CurrentColor=1;
	}
	else if(ButtonB.isChecked()==true){
		Ins=&ALib->InsB;
		CurrentColor=2;
	}
	if(Ins!=NULL){
		ui.EditNBrightWidthL		->setValue(Ins->NBrightWidthL);
		ui.EditNBrightWidthH		->setValue(Ins->NBrightWidthH);
		ui.EditNOKDotL				->setValue(Ins->NOKDotL);
		ui.EditNOKDotH				->setValue(Ins->NOKDotH);
		ui.EditBBrightWidthL		->setValue(Ins->BBrightWidthL);
		ui.EditBBrightWidthH		->setValue(Ins->BBrightWidthH);
		ui.EditBOKDotL				->setValue(Ins->BOKDotL);
		ui.EditBOKDotH				->setValue(Ins->BOKDotH);
		ui.EditAdjustBlack			->setValue(Ins->AdjustBlack);
		ui.EditAdjustWhite			->setValue(Ins->AdjustWhite);

		ui.EditNMinNGCountL			->setValue(Ins->NMinNGCountL);
		ui.EditNMinNGCountH			->setValue(Ins->NMinNGCountH);
		ui.EditBMinNGCountL			->setValue(Ins->BMinNGCountL);
		ui.EditBMinNGCountH			->setValue(Ins->BMinNGCountH);

		ui.EditNOKLengthL			->setValue(Ins->NOKLengthL);
		ui.EditNOKLengthH			->setValue(Ins->NOKLengthH);
		ui.EditBOKLengthL			->setValue(Ins->BOKLengthL);
		ui.EditBOKLengthH			->setValue(Ins->BOKLengthH);
	}

	ui.checkBModeEnabled				->setChecked(ALib->PointMove.ModeEnabled);
	ui.checkBModeAbsoluteBright			->setChecked(ALib->PointMove.ModeAbsoluteBright);
	ui.checkBModeNGCluster				->setChecked(ALib->PointMove.ModeNGCluster);
	ui.checkBModeDiffer					->setChecked(ALib->PointMove.ModeDiffer);
	ui.checkBModeOnlyMatching			->setChecked(ALib->PointMove.ModeOnlyMatching);
	ui.checkBModeWhiteMask				->setChecked(ALib->PointMove.ModeWhiteMask);
	ui.checkBModeBlackMask				->setChecked(ALib->PointMove.ModeBlackMask);
	ui.checkBModeCenterBrightFromParts	->setChecked(ALib->PointMove.ModeCenterBrightFromParts);
	ui.checkBModeAdjustable				->setChecked(ALib->PointMove.ModeAdjustable);
	ui.checkBModeCommonMovable			->setChecked(ALib->PointMove.ModeCommonMovable);
	ui.EditSelfSearch					->setValue	(ALib->SelfSearch);
	ui.EditCommonMoveDot				->setValue	(ALib->CommonMoveDot);
}


void ColorChangeCreateBlockForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;

		Base->TransmitDirectly(&Packet);
		ShowLibrary(*TempLib);
	}
}

void ColorChangeCreateBlockForm::on_ToolButton_clicked()
{
	ShowLibrary(*TempLib);
}

void	ColorChangeCreateBlockForm::GetItemFromWindow(ColorBlockItem &data)
{
	data.SetLibID(TempLib->GetLibID());

	ColorBlockThreshold::ThresholdByLayer	*Ins=NULL;
	if(CurrentColor==0){
		Ins=&data.GetThresholdW()->InsR;
	}
	else if(CurrentColor==1){
		Ins=&data.GetThresholdW()->InsG;
	}
	else if(CurrentColor==2){
		Ins=&data.GetThresholdW()->InsB;
	}
	Ins->NBrightWidthL	=ui.EditNBrightWidthL	->value();
	Ins->NBrightWidthH	=ui.EditNBrightWidthH	->value();
	Ins->NOKDotL		=ui.EditNOKDotL			->value();
	Ins->NOKDotH		=ui.EditNOKDotH			->value();
	Ins->BBrightWidthL	=ui.EditBBrightWidthL	->value();
	Ins->BBrightWidthH	=ui.EditBBrightWidthH	->value();
	Ins->BOKDotL		=ui.EditBOKDotL			->value();
	Ins->BOKDotH		=ui.EditBOKDotH			->value();
	Ins->AdjustBlack	=ui.EditAdjustBlack		->value();
	Ins->AdjustWhite	=ui.EditAdjustWhite		->value();

	Ins->NMinNGCountL	=ui.EditNMinNGCountL	->value();
	Ins->NMinNGCountH	=ui.EditNMinNGCountH	->value();
	Ins->BMinNGCountL	=ui.EditBMinNGCountL	->value();
	Ins->BMinNGCountH	=ui.EditBMinNGCountH	->value();

	Ins->NOKLengthL		=ui.EditNOKLengthL		->value();
	Ins->NOKLengthH		=ui.EditNOKLengthH		->value();
	Ins->BOKLengthL		=ui.EditBOKLengthL		->value();
	Ins->BOKLengthH		=ui.EditBOKLengthH		->value();

	data.GetThresholdW()->PointMove.ModeEnabled				=ui.checkBModeEnabled			->isChecked();
	data.GetThresholdW()->PointMove.ModeAbsoluteBright		=ui.checkBModeAbsoluteBright	->isChecked();
	data.GetThresholdW()->PointMove.ModeNGCluster			=ui.checkBModeNGCluster			->isChecked();
	data.GetThresholdW()->PointMove.ModeDiffer				=ui.checkBModeDiffer			->isChecked();
	data.GetThresholdW()->PointMove.ModeOnlyMatching		=ui.checkBModeOnlyMatching		->isChecked();
	data.GetThresholdW()->PointMove.ModeWhiteMask			=ui.checkBModeWhiteMask			->isChecked();
	data.GetThresholdW()->PointMove.ModeBlackMask			=ui.checkBModeBlackMask			->isChecked();
	data.GetThresholdW()->PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
	data.GetThresholdW()->PointMove.ModeAdjustable			=ui.checkBModeAdjustable		->isChecked();
	data.GetThresholdW()->PointMove.ModeCommonMovable		=ui.checkBModeCommonMovable		->isChecked();
	data.GetThresholdW()->SelfSearch						=ui.EditSelfSearch				->value();
	data.GetThresholdW()->CommonMoveDot						=ui.EditCommonMoveDot			->value();
}

