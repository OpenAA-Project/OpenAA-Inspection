/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\TrueColorChangeCreateBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTrueColorBlockResource.h"
#include "TrueColorChangeCreateBlockForm.h"
#include "XTrueColorBlockLibrary.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XGeneralDialog.h"

TrueColorChangeCreateBlockForm::TrueColorChangeCreateBlockForm(TrueColorBlockBase *base ,QWidget *parent)
: QDialog(parent),ServiceForLayers(base->GetLayersBase())
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	Base=base;
	LibFolderID =-1;
	pLibFolderForm=new GeneralLibFolderForm(base->GetLibType(),GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);

	CmdCreateTempTrueColorBlockLibraryPacket	Packet(GetLayersBase());
	Base->TransmitDirectly(&Packet);
	TempLib=Packet.Point;

	ColorNarrow		.setParent(ui.frameNarrow);
	ColorBroad		.setParent(ui.frameBroad);

	ColorNarrow		.Fit(ui.frameNarrow);
	ColorBroad		.Fit(ui.frameBroad);

	InstallOperationLog(this);
}

TrueColorChangeCreateBlockForm::~TrueColorChangeCreateBlockForm()
{

}

void	TrueColorChangeCreateBlockForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);

	CmdGetTrueColorBlockLibraryListPacket	Packet(GetLayersBase());
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


void TrueColorChangeCreateBlockForm::on_ButtonOK_clicked()
{
	GetItemFromWindow(ResultBlock);
	done(true);
}

void TrueColorChangeCreateBlockForm::on_ButtonCancel_clicked()
{
	done(false);
}
void	TrueColorChangeCreateBlockForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(data.GetLibrary());
	ui.EditNMergin			->setValue(ALib->NMergin);
	ui.EditNOKDot			->setValue(ALib->NOKDot);
	ColorNarrow.Cube		=ALib->NInsColor;
	ColorNarrow.InitializedDoneCube();
	ColorNarrow.Repaint();

	ui.EditBMergin			->setValue(ALib->BMergin);
	ui.EditBOKDot			->setValue(ALib->BOKDot);
	ColorBroad.Cube		=ALib->BInsColor;
	ColorBroad.InitializedDoneCube();
	ColorBroad.Repaint();

	ui.checkBModeEnabled		->setChecked(ALib->PointMove.ModeEnabled);
	ui.checkBModeNGCluster		->setChecked(ALib->PointMove.ModeNGCluster);
	ui.checkBModeOnlyMatching	->setChecked(ALib->PointMove.ModeOnlyMatching);
	ui.checkBModeCenterBrightFromParts	->setChecked(ALib->PointMove.ModeCenterBrightFromParts);
	ui.checkBModeAdjustable		->setChecked(ALib->PointMove.ModeAdjustable);
	ui.checkBModeInvertLogic	->setChecked(ALib->PointMove.ModeInvertLogic);

	ui.EditAdjustBlack			->setValue	(ALib->AdjustBlack);
	ui.EditAdjustWhite			->setValue	(ALib->AdjustWhite);
	ui.checkBModeCommonMovable	->setChecked(ALib->PointMove.ModeCommonMovable);
	ui.EditSelfSearch			->setValue	(ALib->SelfSearch);
	ui.EditCommonMoveDot		->setValue	(ALib->CommonMoveDot);

	ui.EditNMinNGCount			->setValue	(ALib->NMinNGCount);
	ui.EditBMinNGCount			->setValue	(ALib->BMinNGCount);
}


void TrueColorChangeCreateBlockForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;

		Base->TransmitDirectly(&Packet);
		ShowLibrary(*TempLib);
	}
}

void	TrueColorChangeCreateBlockForm::GetItemFromWindow(TrueColorBlockItem &data)
{
	data.SetLibID(TempLib->GetLibID());

	data.GetThresholdW()->NMergin							=ui.EditNMergin			->value();
	data.GetThresholdW()->NOKDot							=ui.EditNOKDot			->value();
	data.GetThresholdW()->NInsColor							=ColorNarrow.Cube;
	data.GetThresholdW()->BMergin							=ui.EditBMergin			->value();
	data.GetThresholdW()->BOKDot							=ui.EditBOKDot			->value();
	data.GetThresholdW()->BInsColor							=ColorBroad.Cube;

	data.GetThresholdW()->PointMove.ModeEnabled				=ui.checkBModeEnabled			->isChecked();
	data.GetThresholdW()->PointMove.ModeNGCluster			=ui.checkBModeNGCluster			->isChecked();
	data.GetThresholdW()->PointMove.ModeOnlyMatching		=ui.checkBModeOnlyMatching		->isChecked();
	data.GetThresholdW()->PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
	data.GetThresholdW()->PointMove.ModeAdjustable			=ui.checkBModeAdjustable		->isChecked();
	data.GetThresholdW()->AdjustBlack						=ui.EditAdjustBlack				->value();
	data.GetThresholdW()->AdjustWhite						=ui.EditAdjustWhite				->value();
	data.GetThresholdW()->PointMove.ModeCommonMovable		=ui.checkBModeCommonMovable		->isChecked();
	data.GetThresholdW()->SelfSearch						=ui.EditSelfSearch				->value();
	data.GetThresholdW()->CommonMoveDot						=ui.EditCommonMoveDot			->value();

	data.GetThresholdW()->NMinNGCount						=ui.EditNMinNGCount	->value();
	data.GetThresholdW()->BMinNGCount						=ui.EditBMinNGCount	->value();

	data.SetInvertLogic(ui.checkBModeInvertLogic);
}


