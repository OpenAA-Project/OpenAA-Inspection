/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTrueColorBlock\TrueColorCreateManualBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "TrueColorFormResource.h"
#include "TrueColorCreateManualBlockForm.h"
#include "XDLLOnly.h"
#include "XTrueColorBlock.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

TrueColorCreateManualBlockForm::TrueColorCreateManualBlockForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	SelectedLibID=-1;
	BlockLibID	 =-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempTrueColorBlockItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(TrueColorBlockItem *)ItemPacket.Point;
		CmdCreateTempTrueColorBlockLibraryPacket	LibPacket(GetLayersBase());
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

	ColorNarrow		.setParent(ui.frameNarrowPanel);
	ColorBroad		.setParent(ui.frameBroadPanel);

	ColorNarrow		.Fit(ui.frameNarrowPanel);
	ColorBroad		.Fit(ui.frameBroadPanel);
	ui.pushButtonOK->setEnabled(false);

	InstallOperationLog(this);
}

TrueColorCreateManualBlockForm::~TrueColorCreateManualBlockForm()
{

}

void	TrueColorCreateManualBlockForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
	if(Ab!=NULL){
		CmdGetTrueColorBlockLibraryListPacket	Packet(GetLayersBase());
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

void TrueColorCreateManualBlockForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadTrueColorBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);
		if(Packet.Success==true){
			BlockLibID					=TempLib->GetLibID();
			TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(TempLib->GetLibrary());

			ui.EditLibID				->setText(QString::number(ALib->GetLibID()));
			ui.EditLibName				->setText(a->GetLibName());

			ui.EditBMergin				->setValue(ALib->BMergin);
			ui.EditBOKDot				->setValue(ALib->BOKDot);
			ColorBroad.Cube				=ALib->BInsColor;
			ColorBroad.InitializedDoneCube();
			ColorBroad.Repaint();

			ui.EditNMergin				->setValue(ALib->NMergin);
			ui.EditNOKDot				->setValue(ALib->NOKDot);
			ColorNarrow.Cube			=ALib->NInsColor;
			ColorNarrow.InitializedDoneCube();
			ColorNarrow.Repaint();

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

			ui.EditNMinNGCount			->setValue(ALib->NMinNGCount);
			ui.EditBMinNGCount			->setValue(ALib->BMinNGCount);
			ui.EditNOKLength			->setValue(ALib->NOKLength);
			ui.EditBOKLength			->setValue(ALib->BOKLength);

			ui.pushButtonOK->setEnabled(true);
		}
		else{
			QMessageBox::critical(NULL, LangSolver.GetString(TrueColorCreateManualBlockForm_LS,LID_17)/*"Library error"*/, LangSolver.GetString(TrueColorCreateManualBlockForm_LS,LID_18)/*"Not loaded this library record"*/);
		}
	}
}

void	TrueColorCreateManualBlockForm::GetDataFromWindow(TrueColorBlockItem &data)
{
	data.SetLibID(BlockLibID);

	data.GetThresholdW()->NInsColor						=ColorNarrow.Cube;
	data.GetThresholdW()->NMergin						=ui.EditNMergin			->value();
	data.GetThresholdW()->NOKDot						=ui.EditNOKDot			->value();
	data.GetThresholdW()->BInsColor						=ColorBroad.Cube;
	data.GetThresholdW()->BMergin						=ui.EditBMergin			->value();
	data.GetThresholdW()->BOKDot						=ui.EditBOKDot			->value();
	data.GetThresholdW()->PointMove.ModeEnabled			=ui.checkBModeEnabled			->isChecked();
	data.GetThresholdW()->PointMove.ModeNGCluster		=ui.checkBModeNGCluster			->isChecked();
	data.GetThresholdW()->PointMove.ModeOnlyMatching	=ui.checkBModeOnlyMatching		->isChecked();
	data.GetThresholdW()->PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
	data.GetThresholdW()->PointMove.ModeAdjustable		=ui.checkBModeAdjustable		->isChecked();
	data.GetThresholdW()->AdjustBlack					=ui.EditAdjustBlack		->value();
	data.GetThresholdW()->AdjustWhite					=ui.EditAdjustWhite		->value();
	data.GetThresholdW()->PointMove.ModeCommonMovable	=ui.checkBModeCommonMovable	->isChecked();
	data.GetThresholdW()->SelfSearch					=ui.EditSelfSearch		->value();
	data.GetThresholdW()->CommonMoveDot					=ui.EditCommonMoveDot	->value();

	data.GetThresholdW()->NMinNGCount					=ui.EditNMinNGCount		->value();
	data.GetThresholdW()->BMinNGCount					=ui.EditBMinNGCount		->value();
	data.GetThresholdW()->NOKLength						=ui.EditNOKLength		->value();
	data.GetThresholdW()->BOKLength						=ui.EditBOKLength		->value();

	data.SetInvertLogic(ui.checkBModeInvertLogic	->isChecked());
}


void TrueColorCreateManualBlockForm::on_pushButtonOK_clicked()
{
	GetDataFromWindow(*BItem);
	done(true);
}

void TrueColorCreateManualBlockForm::on_pushButtonCancel_clicked()
{
	done(false);
}

