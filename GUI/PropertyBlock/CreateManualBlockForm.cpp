/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\CreateManualBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyBlockFormResource.h"
#include "CreateManualBlockForm.h"
#include "XDLLOnly.h"
#include<QMessageBox>
#include "XGeneralDialog.h"

CreateManualBlockForm::CreateManualBlockForm(LayersBase *base ,int Layer,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	SelectedLibID=-1;
	BlockLibID	 =-1;
	PastedLayer	 =Layer;

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempBlockItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(BlockItem *)ItemPacket.Point;
		CmdCreateTempBlockLibraryPacket	LibPacket(GetLayersBase());
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
	ui.ButtonOK->setEnabled(false);

	InstallOperationLog(this);
}

CreateManualBlockForm::~CreateManualBlockForm()
{
	if(BItem!=NULL)
		delete	BItem;
	BItem=NULL;
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}

void	CreateManualBlockForm::Reflect(void)
{
	ui.EditLibID				->setText(QString::number(BItem->GetLibID()));
	BlockLibID=BItem->GetLibID();
	CmdGetLibName	LibPacket(GetLayersBase());
	LibPacket.LibID=BItem->GetLibID();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&LibPacket);
	}
	ui.EditLibName				->setText(LibPacket.LibName);
	ui.EditNBrightWidthL		->setValue(BItem->GetThresholdR()->ThreshouldBag.NBrightWidthL);
	ui.EditNBrightWidthH		->setValue(BItem->GetThresholdR()->ThreshouldBag.NBrightWidthH);
	ui.EditNOKDotL				->setValue(BItem->GetThresholdR()->ThreshouldBag.NOKDotL);
	ui.EditNOKDotH				->setValue(BItem->GetThresholdR()->ThreshouldBag.NOKDotH);
	ui.EditNOKLengthL			->setValue(BItem->GetThresholdR()->ThreshouldBag.NOKLengthL);
	ui.EditNOKLengthH			->setValue(BItem->GetThresholdR()->ThreshouldBag.NOKLengthH);
	ui.EditBBrightWidthL		->setValue(BItem->GetThresholdR()->ThreshouldBag.BBrightWidthL);
	ui.EditBBrightWidthH		->setValue(BItem->GetThresholdR()->ThreshouldBag.BBrightWidthH);
	ui.EditBOKDotL				->setValue(BItem->GetThresholdR()->ThreshouldBag.BOKDotL);
	ui.EditBOKDotH				->setValue(BItem->GetThresholdR()->ThreshouldBag.BOKDotH);
	ui.EditBOKLengthL			->setValue(BItem->GetThresholdR()->ThreshouldBag.BOKLengthL);
	ui.EditBOKLengthH			->setValue(BItem->GetThresholdR()->ThreshouldBag.BOKLengthH);
	ui.checkBModeEnabled		->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeEnabled);
	ui.checkBModeAbsoluteBright	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeAbsoluteBright);
	ui.checkBModeNGCluster		->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeNGCluster);
	ui.checkBModeDiffer			->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeDiffer);
	ui.checkBModeOnlyMatching	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeOnlyMatching);
	ui.checkBModeWhiteMask		->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeWhiteMask);
	ui.checkBModeBlackMask		->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeBlackMask);
	ui.checkBModeInvertLogic	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeInvertLogic);
	//ui.checkBMatchPosition		->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeMatchPosition);
	if(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeMatchPosition==false
	&& BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeMatchPositionBW==false)
		ui.comboBoxMatchPosition	->setCurrentIndex(0);
	else
	if(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeMatchPosition==true
	&& BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeMatchPositionBW==false)
		ui.comboBoxMatchPosition	->setCurrentIndex(1);
	else
	if(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeMatchPosition==false
	&& BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeMatchPositionBW==true)
		ui.comboBoxMatchPosition	->setCurrentIndex(2);
	else
	if(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeMatchPosition==true
	&& BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeMatchPositionBW==true)
		ui.comboBoxMatchPosition	->setCurrentIndex(3);

	ui.checkBModeSearchDetail	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeSearchDetail);
	ui.checkBModeDynamicMask	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeDynamicMask);
	ui.checkBModeBindBWBroad	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeBindBWBroad);
	ui.checkBModeBindBWNarrow	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeBindBWNarrow);
	ui.checkBModeAdoptBiggest	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeAdoptBiggest);
	ui.checkBModeUseMasterImage	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeUseMasterImage);
	ui.checkBModeOppositeRange	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeOppositeRange);
	ui.checkBModeUseGlobalLine	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeUseGlobalLine);

	ui.checkBModeCenterBrightFromParts	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeCenterBrightFromParts);
	ui.checkBModeAdjustable		->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeAdjustable);
	ui.EditAdjustBlack			->setValue(BItem->GetThresholdR()->ThreshouldBag.AdjustBlack);
	ui.EditAdjustWhite			->setValue(BItem->GetThresholdR()->ThreshouldBag.AdjustWhite);
	ui.checkBModeCommonMovable	->setChecked(BItem->GetThresholdR()->ThreshouldBag.PointMove.ModeCommonMovable);
	ui.EditSelfSearch			->setValue(BItem->GetThresholdR()->ThreshouldBag.SelfSearch);
	ui.EditCommonMoveDot		->setValue(BItem->GetThresholdR()->ThreshouldBag.CommonMoveDot);

	ui.EditNMinNGCountL			->setValue(BItem->GetThresholdR()->ThreshouldBag.NMinNGCountL);
	ui.EditNMinNGCountH			->setValue(BItem->GetThresholdR()->ThreshouldBag.NMinNGCountH);
	ui.EditBMinNGCountL			->setValue(BItem->GetThresholdR()->ThreshouldBag.BMinNGCountL);
	ui.EditBMinNGCountH			->setValue(BItem->GetThresholdR()->ThreshouldBag.BMinNGCountH);
	ui.EditNConnectLen			->setValue(BItem->GetThresholdR()->ThreshouldBag.NConnectLen);
	ui.EditBConnectLen			->setValue(BItem->GetThresholdR()->ThreshouldBag.BConnectLen);
	ui.EditItemName->setText(BItem->GetItemName());
}

void	CreateManualBlockForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(Ab!=NULL){
		CmdGetBlockLibraryListInPasteLayerPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		Packet.Layer		=PastedLayer;
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


void CreateManualBlockForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);

		if(Packet.Success==true){
			BlockLibID					=TempLib->GetLibID();
			BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(TempLib->GetLibrary());
			ui.EditLibID				->setText(QString::number(TempLib->GetLibID()));
			ui.EditLibName				->setText(a->GetLibName());

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
			ui.ButtonOK->setEnabled(true);
			ui.checkBModeInvertLogic	->setChecked(ALib->PointMove.ModeInvertLogic);
			//ui.checkBMatchPosition		->setChecked(TempLib->PointMove.ModeMatchPosition);
			if(ALib->PointMove.ModeMatchPosition==false
			&& ALib->PointMove.ModeMatchPositionBW==false)
				ui.comboBoxMatchPosition	->setCurrentIndex(0);
			else
			if(ALib->PointMove.ModeMatchPosition==true
			&& ALib->PointMove.ModeMatchPositionBW==false)
				ui.comboBoxMatchPosition	->setCurrentIndex(1);
			else
			if(ALib->PointMove.ModeMatchPosition==false
			&& ALib->PointMove.ModeMatchPositionBW==true)
				ui.comboBoxMatchPosition	->setCurrentIndex(2);
			else
			if(ALib->PointMove.ModeMatchPosition==true
			&& ALib->PointMove.ModeMatchPositionBW==true)
				ui.comboBoxMatchPosition	->setCurrentIndex(3);
	
			ui.checkBModeSearchDetail	->setChecked(ALib->PointMove.ModeSearchDetail);
			ui.checkBModeDynamicMask	->setChecked(ALib->PointMove.ModeDynamicMask);
			ui.checkBModeBindBWBroad	->setChecked(ALib->PointMove.ModeBindBWBroad);
			ui.checkBModeBindBWNarrow	->setChecked(ALib->PointMove.ModeBindBWNarrow);
			ui.checkBModeAdoptBiggest	->setChecked(ALib->PointMove.ModeAdoptBiggest);
			ui.checkBModeUseMasterImage	->setChecked(ALib->PointMove.ModeUseMasterImage);
			ui.checkBModeOppositeRange	->setChecked(ALib->PointMove.ModeOppositeRange);
			ui.checkBModeUseGlobalLine	->setChecked(ALib->PointMove.ModeUseGlobalLine);
			ui.EditRegularBrightness	->setValue	(ALib->RegularBrightness);
		}
		else{
			QMessageBox::critical(NULL	, LangSolver.GetString(CreateManualBlockForm_LS,LID_47)/*"Library error"*/
										, LangSolver.GetString(CreateManualBlockForm_LS,LID_48)/*"Not loaded this library record"*/);
		}
	}

}

void	CreateManualBlockForm::GetDataFromWindow(BlockItem &data)
{
	data.SetLibID(BlockLibID);
	data.GetThresholdW()->ThreshouldBag.NBrightWidthL	=ui.EditNBrightWidthL	->value();
	data.GetThresholdW()->ThreshouldBag.NBrightWidthH	=ui.EditNBrightWidthH	->value();
	data.GetThresholdW()->ThreshouldBag.NOKDotL			=ui.EditNOKDotL			->value();
	data.GetThresholdW()->ThreshouldBag.NOKDotH			=ui.EditNOKDotH			->value();
	data.GetThresholdW()->ThreshouldBag.NOKLengthL		=ui.EditNOKLengthL		->value();
	data.GetThresholdW()->ThreshouldBag.NOKLengthH		=ui.EditNOKLengthH		->value();
	data.GetThresholdW()->ThreshouldBag.BBrightWidthL	=ui.EditBBrightWidthL	->value();
	data.GetThresholdW()->ThreshouldBag.BBrightWidthH	=ui.EditBBrightWidthH	->value();
	data.GetThresholdW()->ThreshouldBag.BOKDotL			=ui.EditBOKDotL			->value();
	data.GetThresholdW()->ThreshouldBag.BOKDotH			=ui.EditBOKDotH			->value();
	data.GetThresholdW()->ThreshouldBag.BOKLengthL		=ui.EditBOKLengthL		->value();
	data.GetThresholdW()->ThreshouldBag.BOKLengthH		=ui.EditBOKLengthH		->value();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeEnabled				=ui.checkBModeEnabled			->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeAbsoluteBright		=ui.checkBModeAbsoluteBright	->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeNGCluster				=ui.checkBModeNGCluster			->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeDiffer				=ui.checkBModeDiffer			->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeOnlyMatching			=ui.checkBModeOnlyMatching		->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeWhiteMask				=ui.checkBModeWhiteMask			->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeBlackMask				=ui.checkBModeBlackMask			->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeCenterBrightFromParts	=ui.checkBModeCenterBrightFromParts	->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeAdjustable			=ui.checkBModeAdjustable		->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeInvertLogic			=ui.checkBModeInvertLogic		->isChecked();
	//data.GetThresholdW()->ThreshouldBag.PointMove.ModeMatchPosition			=ui.checkBMatchPosition			->isChecked();
	if(ui.comboBoxMatchPosition	->currentIndex()==0){
		data.GetThresholdW()->ThreshouldBag.PointMove.ModeMatchPosition	=false;
		data.GetThresholdW()->ThreshouldBag.PointMove.ModeMatchPositionBW	=false;
	}
	else
	if(ui.comboBoxMatchPosition	->currentIndex()==1){
		data.GetThresholdW()->ThreshouldBag.PointMove.ModeMatchPosition	=true;
		data.GetThresholdW()->ThreshouldBag.PointMove.ModeMatchPositionBW	=false;
	}
	else
	if(ui.comboBoxMatchPosition	->currentIndex()==2){
		data.GetThresholdW()->ThreshouldBag.PointMove.ModeMatchPosition	=false;
		data.GetThresholdW()->ThreshouldBag.PointMove.ModeMatchPositionBW	=true;
	}
	else
	if(ui.comboBoxMatchPosition	->currentIndex()==3){
		data.GetThresholdW()->ThreshouldBag.PointMove.ModeMatchPosition	=true;
		data.GetThresholdW()->ThreshouldBag.PointMove.ModeMatchPositionBW	=true;
	}
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeSearchDetail	=ui.checkBModeSearchDetail	->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeDynamicMask	=ui.checkBModeDynamicMask	->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeBindBWBroad	=ui.checkBModeBindBWBroad	->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeBindBWNarrow	=ui.checkBModeBindBWNarrow	->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeAdoptBiggest	=ui.checkBModeAdoptBiggest	->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeUseMasterImage=ui.checkBModeUseMasterImage->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeOppositeRange	=ui.checkBModeOppositeRange	->isChecked();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeUseGlobalLine	=ui.checkBModeUseGlobalLine	->isChecked();

	if(ui.EditRegularBrightness	->value()>=0){
		data.GetThresholdW()->ThreshouldBag.PointMove.ModeUseRegularBrightness=true;
		data.GetThresholdW()->ThreshouldBag.RegularCenterBright	=ui.EditRegularBrightness	->value();
	}
	else{
		data.GetThresholdW()->ThreshouldBag.PointMove.ModeUseRegularBrightness=false;
	}
	data.GetThresholdW()->ThreshouldBag.AdjustBlack	=ui.EditAdjustBlack	->value();
	data.GetThresholdW()->ThreshouldBag.AdjustWhite	=ui.EditAdjustWhite	->value();
	data.GetThresholdW()->ThreshouldBag.PointMove.ModeCommonMovable		=ui.checkBModeCommonMovable	->isChecked();
	data.GetThresholdW()->ThreshouldBag.SelfSearch	=ui.EditSelfSearch	->value();
	data.GetThresholdW()->ThreshouldBag.CommonMoveDot	=ui.EditCommonMoveDot	->value();

	data.GetThresholdW()->ThreshouldBag.NMinNGCountL	=ui.EditNMinNGCountL->value();
	data.GetThresholdW()->ThreshouldBag.NMinNGCountH	=ui.EditNMinNGCountH->value();
	data.GetThresholdW()->ThreshouldBag.BMinNGCountL	=ui.EditBMinNGCountL->value();
	data.GetThresholdW()->ThreshouldBag.BMinNGCountH	=ui.EditBMinNGCountH->value();
	data.GetThresholdW()->ThreshouldBag.NConnectLen	=ui.EditNConnectLen		->value();
	data.GetThresholdW()->ThreshouldBag.BConnectLen	=ui.EditBConnectLen		->value();
	data.SetItemName(ui.EditItemName->text());
}

void CreateManualBlockForm::on_ButtonOK_clicked()
{
	GetDataFromWindow(*BItem);
	done(true);
}

void CreateManualBlockForm::on_ButtonCancel_clicked()
{
	done(false);
}

void CreateManualBlockForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_ButtonOK_clicked();
}
