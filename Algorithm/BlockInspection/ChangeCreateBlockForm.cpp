/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\ChangeCreateBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "BlockFormResource.h"
#include "XBlockLibrary.h"
#include "ChangeCreateBlockForm.h"
#include "XDLLOnly.h"
#include "SelectBlockLibraryForm.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XGeneralDialog.h"

ChangeCreateBlockForm::ChangeCreateBlockForm(BlockBase *base ,int Layer ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base->GetLayersBase())
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	Base=base;
	LibFolderID =-1;
	PastedLayer	=Layer;

	pLibFolderForm=new GeneralLibFolderForm(base->GetLibType(),GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);

	CmdCreateTempBlockLibraryPacket	Packet(GetLayersBase());
	Base->TransmitDirectly(&Packet);
	TempLib=Packet.Point;

	InstallOperationLog(this);
}

ChangeCreateBlockForm::~ChangeCreateBlockForm()
{

}

void	ChangeCreateBlockForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);

	CmdGetBlockLibraryListInPasteLayerPacket	Packet(GetLayersBase());
	Packet.LibFolderID	=LibFolderID;
	Packet.Layer		=PastedLayer;
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

void ChangeCreateBlockForm::on_ButtonOK_clicked()
{
	GetItemFromWindow(ResultBlock);
	done(true);
}

void ChangeCreateBlockForm::on_ButtonCancel_clicked()
{
	done(false);
}

void	ChangeCreateBlockForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(data.GetLibrary());

	ui.EditNBrightWidthL		->setValue	(ALib->NBrightWidthL);
	ui.EditNBrightWidthH		->setValue	(ALib->NBrightWidthH);
	ui.EditNOKDotL				->setValue	(ALib->NOKDotL);
	ui.EditNOKDotH				->setValue	(ALib->NOKDotH);
	ui.EditNOKLengthL			->setValue	(ALib->NOKLengthL);
	ui.EditNOKLengthH			->setValue	(ALib->NOKLengthH);
	ui.EditBBrightWidthL		->setValue	(ALib->BBrightWidthL);
	ui.EditBBrightWidthH		->setValue	(ALib->BBrightWidthH);
	ui.EditBOKDotL				->setValue	(ALib->BOKDotL);
	ui.EditBOKDotH				->setValue	(ALib->BOKDotH);
	ui.EditBOKLengthL			->setValue	(ALib->BOKLengthL);
	ui.EditBOKLengthH			->setValue	(ALib->BOKLengthH);
	ui.checkBModeEnabled		->setChecked(ALib->PointMove.ModeEnabled);
	ui.checkBModeAbsoluteBright	->setChecked(ALib->PointMove.ModeAbsoluteBright);
	ui.checkBModeNGCluster		->setChecked(ALib->PointMove.ModeNGCluster);
	ui.checkBModeDiffer			->setChecked(ALib->PointMove.ModeDiffer);
	ui.checkBModeOnlyMatching	->setChecked(ALib->PointMove.ModeOnlyMatching);
	ui.checkBModeWhiteMask		->setChecked(ALib->PointMove.ModeWhiteMask);
	ui.checkBModeBlackMask		->setChecked(ALib->PointMove.ModeBlackMask);
	ui.checkBModeCenterBrightFromParts	->setChecked(ALib->PointMove.ModeCenterBrightFromParts);
	ui.checkBModeAdjustable		->setChecked(ALib->PointMove.ModeAdjustable);
	ui.checkBModeOppositeRange	->setChecked(ALib->PointMove.ModeOppositeRange);

	ui.EditAdjustBlack			->setValue	(ALib->AdjustBlack);
	ui.EditAdjustWhite			->setValue	(ALib->AdjustWhite);
	ui.checkBModeCommonMovable	->setChecked(ALib->PointMove.ModeCommonMovable);
	ui.EditSelfSearch			->setValue	(ALib->SelfSearch);
	ui.EditCommonMoveDot		->setValue	(ALib->CommonMoveDot);
	ui.EditNMinNGCountL			->setValue	(ALib->NMinNGCountL);
	ui.EditNMinNGCountH			->setValue	(ALib->NMinNGCountH);
	ui.EditBMinNGCountL			->setValue	(ALib->BMinNGCountL);
	ui.EditBMinNGCountH			->setValue	(ALib->BMinNGCountH);
	ui.EditNConnectLen			->setValue	(ALib->NConnectLen);
	ui.EditBConnectLen			->setValue	(ALib->BConnectLen);
}

void ChangeCreateBlockForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;

		Base->TransmitDirectly(&Packet);
		ShowLibrary(*TempLib);
	}
}

void	ChangeCreateBlockForm::GetItemFromWindow(BlockItem &data)
{
	data.SetLibID(TempLib->GetLibID());

	data.GetThresholdW()->ThreshouldBag.NBrightWidthL	=ui.EditNBrightWidthL	->value();
	data.GetThresholdW()->ThreshouldBag.NBrightWidthH	=ui.EditNBrightWidthH	->value();
	data.GetThresholdW()->ThreshouldBag.NOKDotL		=ui.EditNOKDotL			->value();
	data.GetThresholdW()->ThreshouldBag.NOKDotH		=ui.EditNOKDotH			->value();
	data.GetThresholdW()->ThreshouldBag.NOKLengthL	=ui.EditNOKLengthL		->value();
	data.GetThresholdW()->ThreshouldBag.NOKLengthH	=ui.EditNOKLengthH		->value();
	data.GetThresholdW()->ThreshouldBag.BBrightWidthL	=ui.EditBBrightWidthL	->value();
	data.GetThresholdW()->ThreshouldBag.BBrightWidthH	=ui.EditBBrightWidthH	->value();
	data.GetThresholdW()->ThreshouldBag.BOKDotL		=ui.EditBOKDotL			->value();
	data.GetThresholdW()->ThreshouldBag.BOKDotH		=ui.EditBOKDotH			->value();
	data.GetThresholdW()->ThreshouldBag.BOKLengthL	=ui.EditBOKLengthL		->value();
	data.GetThresholdW()->ThreshouldBag.BOKLengthH	=ui.EditBOKLengthH		->value();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeEnabled				=ui.checkBModeEnabled			->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeAbsoluteBright		=ui.checkBModeAbsoluteBright	->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeNGCluster				=ui.checkBModeNGCluster			->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeDiffer				=ui.checkBModeDiffer			->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeOnlyMatching			=ui.checkBModeOnlyMatching		->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeWhiteMask				=ui.checkBModeWhiteMask			->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeBlackMask				=ui.checkBModeBlackMask			->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeCenterBrightFromParts	=ui.checkBModeCenterBrightFromParts	->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeAdjustable			=ui.checkBModeAdjustable		->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeOppositeRange			=ui.checkBModeOppositeRange		->isChecked();

	data.GetThresholdW()->ThreshouldBag.AdjustBlack						=ui.EditAdjustBlack		->value();
	data.GetThresholdW()->ThreshouldBag.AdjustWhite						=ui.EditAdjustWhite		->value();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeCommonMovable		=ui.checkBModeCommonMovable	->isChecked();
	data.GetThresholdW()->ThreshouldBag.SelfSearch						=ui.EditSelfSearch		->value();
	data.GetThresholdW()->ThreshouldBag.CommonMoveDot						=ui.EditCommonMoveDot	->value();

	data.GetThresholdW()->ThreshouldBag.NMinNGCountL	=ui.EditNMinNGCountL	->value();
	data.GetThresholdW()->ThreshouldBag.NMinNGCountH	=ui.EditNMinNGCountH	->value();
	data.GetThresholdW()->ThreshouldBag.BMinNGCountL	=ui.EditBMinNGCountL	->value();
	data.GetThresholdW()->ThreshouldBag.BMinNGCountH	=ui.EditBMinNGCountH	->value();
	data.GetThresholdW()->ThreshouldBag.NConnectLen	=ui.EditNConnectLen		->value();
	data.GetThresholdW()->ThreshouldBag.BConnectLen	=ui.EditBConnectLen		->value();
}

