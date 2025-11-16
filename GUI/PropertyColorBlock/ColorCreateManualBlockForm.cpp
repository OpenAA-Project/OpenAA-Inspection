/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\ColorCreateManualBlockForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyColorBlockFormResource.h"
#include "ColorCreateManualBlockForm.h"
#include "XDLLOnly.h"
#include "XColorBlockLibrary.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

ColorCreateManualBlockForm::ColorCreateManualBlockForm(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base),ButtonR(false),ButtonG(false),ButtonB(false)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	SelectedLibID=-1;
	BlockLibID	 =-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempColorBlockItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(ColorBlockItem *)ItemPacket.Point;

		CmdCreateTempColorBlockLibraryPacket	LibPacket(GetLayersBase());
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

	ButtonR.setParent(this);
	ButtonG.setParent(this);
	ButtonB.setParent(this);

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

ColorCreateManualBlockForm::~ColorCreateManualBlockForm()
{
	if(BItem!=NULL)
		delete	BItem;
	BItem=NULL;
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}

void	ColorCreateManualBlockForm::Reflect(void)
{
	ui.EditLibID				->setText(QString::number(BItem->GetLibID()));
	BlockLibID=BItem->GetLibID();
	CmdGetLibName	LibPacket(GetLayersBase());
	LibPacket.LibID=BItem->GetLibID();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&LibPacket);
	}
	ui.EditLibName				->setText(LibPacket.LibName);
	if(ButtonR.isChecked()==true){
		ui.EditNBrightWidthL		->setValue(BItem->GetThresholdR()->InsR.NBrightWidthL);
		ui.EditNBrightWidthH		->setValue(BItem->GetThresholdR()->InsR.NBrightWidthH);
		ui.EditNOKDotL				->setValue(BItem->GetThresholdR()->InsR.NOKDotL);
		ui.EditNOKDotH				->setValue(BItem->GetThresholdR()->InsR.NOKDotH);
		ui.EditBBrightWidthL		->setValue(BItem->GetThresholdR()->InsR.BBrightWidthL);
		ui.EditBBrightWidthH		->setValue(BItem->GetThresholdR()->InsR.BBrightWidthH);
		ui.EditBOKDotL				->setValue(BItem->GetThresholdR()->InsR.BOKDotL);
		ui.EditBOKDotH				->setValue(BItem->GetThresholdR()->InsR.BOKDotH);
		ui.EditAdjustBlack			->setValue(BItem->GetThresholdR()->InsR.AdjustBlack);
		ui.EditAdjustWhite			->setValue(BItem->GetThresholdR()->InsR.AdjustWhite);
		ui.EditNMinNGCountL			->setValue(BItem->GetThresholdR()->InsR.NMinNGCountL);
		ui.EditNMinNGCountH			->setValue(BItem->GetThresholdR()->InsR.NMinNGCountH);
		ui.EditBMinNGCountL			->setValue(BItem->GetThresholdR()->InsR.BMinNGCountL);
		ui.EditBMinNGCountH			->setValue(BItem->GetThresholdR()->InsR.BMinNGCountH);
		ui.EditNOKLengthL			->setValue(BItem->GetThresholdR()->InsR.NOKLengthL);
		ui.EditNOKLengthH			->setValue(BItem->GetThresholdR()->InsR.NOKLengthH);
		ui.EditBOKLengthL			->setValue(BItem->GetThresholdR()->InsR.BOKLengthL);
		ui.EditBOKLengthH			->setValue(BItem->GetThresholdR()->InsR.BOKLengthH);
	}
	else if(ButtonG.isChecked()==true){
		ui.EditNBrightWidthL		->setValue(BItem->GetThresholdR()->InsG.NBrightWidthL);
		ui.EditNBrightWidthH		->setValue(BItem->GetThresholdR()->InsG.NBrightWidthH);
		ui.EditNOKDotL				->setValue(BItem->GetThresholdR()->InsG.NOKDotL);
		ui.EditNOKDotH				->setValue(BItem->GetThresholdR()->InsG.NOKDotH);
		ui.EditBBrightWidthL		->setValue(BItem->GetThresholdR()->InsG.BBrightWidthL);
		ui.EditBBrightWidthH		->setValue(BItem->GetThresholdR()->InsG.BBrightWidthH);
		ui.EditBOKDotL				->setValue(BItem->GetThresholdR()->InsG.BOKDotL);
		ui.EditBOKDotH				->setValue(BItem->GetThresholdR()->InsG.BOKDotH);
		ui.EditAdjustBlack			->setValue(BItem->GetThresholdR()->InsG.AdjustBlack);
		ui.EditAdjustWhite			->setValue(BItem->GetThresholdR()->InsG.AdjustWhite);
		ui.EditNMinNGCountL			->setValue(BItem->GetThresholdR()->InsG.NMinNGCountL);
		ui.EditNMinNGCountH			->setValue(BItem->GetThresholdR()->InsG.NMinNGCountH);
		ui.EditBMinNGCountL			->setValue(BItem->GetThresholdR()->InsG.BMinNGCountL);
		ui.EditBMinNGCountH			->setValue(BItem->GetThresholdR()->InsG.BMinNGCountH);
		ui.EditNOKLengthL			->setValue(BItem->GetThresholdR()->InsG.NOKLengthL);
		ui.EditNOKLengthH			->setValue(BItem->GetThresholdR()->InsG.NOKLengthH);
		ui.EditBOKLengthL			->setValue(BItem->GetThresholdR()->InsG.BOKLengthL);
		ui.EditBOKLengthH			->setValue(BItem->GetThresholdR()->InsG.BOKLengthH);
	}
	else if(ButtonB.isChecked()==true){
		ui.EditNBrightWidthL		->setValue(BItem->GetThresholdR()->InsB.NBrightWidthL);
		ui.EditNBrightWidthH		->setValue(BItem->GetThresholdR()->InsB.NBrightWidthH);
		ui.EditNOKDotL				->setValue(BItem->GetThresholdR()->InsB.NOKDotL);
		ui.EditNOKDotH				->setValue(BItem->GetThresholdR()->InsB.NOKDotH);
		ui.EditBBrightWidthL		->setValue(BItem->GetThresholdR()->InsB.BBrightWidthL);
		ui.EditBBrightWidthH		->setValue(BItem->GetThresholdR()->InsB.BBrightWidthH);
		ui.EditBOKDotL				->setValue(BItem->GetThresholdR()->InsB.BOKDotL);
		ui.EditBOKDotH				->setValue(BItem->GetThresholdR()->InsB.BOKDotH);
		ui.EditAdjustBlack			->setValue(BItem->GetThresholdR()->InsB.AdjustBlack);
		ui.EditAdjustWhite			->setValue(BItem->GetThresholdR()->InsB.AdjustWhite);
		ui.EditNMinNGCountL			->setValue(BItem->GetThresholdR()->InsB.NMinNGCountL);
		ui.EditNMinNGCountH			->setValue(BItem->GetThresholdR()->InsB.NMinNGCountH);
		ui.EditBMinNGCountL			->setValue(BItem->GetThresholdR()->InsB.BMinNGCountL);
		ui.EditBMinNGCountH			->setValue(BItem->GetThresholdR()->InsB.BMinNGCountH);
		ui.EditNOKLengthL			->setValue(BItem->GetThresholdR()->InsB.NOKLengthL);
		ui.EditNOKLengthH			->setValue(BItem->GetThresholdR()->InsB.NOKLengthH);
		ui.EditBOKLengthL			->setValue(BItem->GetThresholdR()->InsB.BOKLengthL);
		ui.EditBOKLengthH			->setValue(BItem->GetThresholdR()->InsB.BOKLengthH);
	}
	ui.checkBModeEnabled		->setChecked(BItem->GetThresholdR()->PointMove.ModeEnabled);
	ui.checkBModeAbsoluteBright	->setChecked(BItem->GetThresholdR()->PointMove.ModeAbsoluteBright);
	ui.checkBModeNGCluster		->setChecked(BItem->GetThresholdR()->PointMove.ModeNGCluster);
	ui.checkBModeDiffer			->setChecked(BItem->GetThresholdR()->PointMove.ModeDiffer);
	ui.checkBModeOnlyMatching	->setChecked(BItem->GetThresholdR()->PointMove.ModeOnlyMatching);
	ui.checkBModeWhiteMask		->setChecked(BItem->GetThresholdR()->PointMove.ModeWhiteMask);
	ui.checkBModeBlackMask		->setChecked(BItem->GetThresholdR()->PointMove.ModeBlackMask);
	ui.checkBModeCenterBrightFromParts	->setChecked(BItem->GetThresholdR()->PointMove.ModeCenterBrightFromParts);
	ui.checkBModeAdjustable		->setChecked(BItem->GetThresholdR()->PointMove.ModeAdjustable);
	ui.checkBModeCommonMovable	->setChecked(BItem->GetThresholdR()->PointMove.ModeCommonMovable);
	ui.EditSelfSearch			->setValue(BItem->GetThresholdR()->SelfSearch);
	ui.EditCommonMoveDot		->setValue(BItem->GetThresholdR()->CommonMoveDot);
}

void	ColorCreateManualBlockForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	if(Ab!=NULL){
		CmdGetColorBlockLibraryListPacket	Packet(GetLayersBase());
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


void ColorCreateManualBlockForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadColorBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);
		if(Packet.Success==true){
			ShowLibrary(TempLib);
				
			ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(TempLib->GetLibrary());
	
			BItem->GetThresholdW()->InsR.NBrightWidthL	=ALib->InsR.NBrightWidthL;
			BItem->GetThresholdW()->InsR.NBrightWidthH	=ALib->InsR.NBrightWidthH;
			BItem->GetThresholdW()->InsR.NOKDotL		=ALib->InsR.NOKDotL;
			BItem->GetThresholdW()->InsR.NOKDotH		=ALib->InsR.NOKDotH;
			BItem->GetThresholdW()->InsR.BBrightWidthL	=ALib->InsR.BBrightWidthL;
			BItem->GetThresholdW()->InsR.BBrightWidthH	=ALib->InsR.BBrightWidthH;
			BItem->GetThresholdW()->InsR.BOKDotL		=ALib->InsR.BOKDotL;
			BItem->GetThresholdW()->InsR.BOKDotH		=ALib->InsR.BOKDotH;
			BItem->GetThresholdW()->InsR.AdjustBlack	=ALib->InsR.AdjustBlack;
			BItem->GetThresholdW()->InsR.AdjustWhite	=ALib->InsR.AdjustWhite;
			BItem->GetThresholdW()->InsR.NMinNGCountL	=ALib->InsR.NMinNGCountL;
			BItem->GetThresholdW()->InsR.NMinNGCountH	=ALib->InsR.NMinNGCountH;
			BItem->GetThresholdW()->InsR.BMinNGCountL	=ALib->InsR.BMinNGCountL;
			BItem->GetThresholdW()->InsR.BMinNGCountH	=ALib->InsR.BMinNGCountH;
			BItem->GetThresholdW()->InsR.NOKLengthL		=ALib->InsR.NOKLengthL;
			BItem->GetThresholdW()->InsR.NOKLengthH		=ALib->InsR.NOKLengthH;
			BItem->GetThresholdW()->InsR.BOKLengthL		=ALib->InsR.BOKLengthL;
			BItem->GetThresholdW()->InsR.BOKLengthH		=ALib->InsR.BOKLengthH;

			BItem->GetThresholdW()->InsG.NBrightWidthL	=ALib->InsG.NBrightWidthL;
			BItem->GetThresholdW()->InsG.NBrightWidthH	=ALib->InsG.NBrightWidthH;
			BItem->GetThresholdW()->InsG.NOKDotL		=ALib->InsG.NOKDotL;
			BItem->GetThresholdW()->InsG.NOKDotH		=ALib->InsG.NOKDotH;
			BItem->GetThresholdW()->InsG.BBrightWidthL	=ALib->InsG.BBrightWidthL;
			BItem->GetThresholdW()->InsG.BBrightWidthH	=ALib->InsG.BBrightWidthH;
			BItem->GetThresholdW()->InsG.BOKDotL		=ALib->InsG.BOKDotL;
			BItem->GetThresholdW()->InsG.BOKDotH		=ALib->InsG.BOKDotH;
			BItem->GetThresholdW()->InsG.AdjustBlack	=ALib->InsG.AdjustBlack;
			BItem->GetThresholdW()->InsG.AdjustWhite	=ALib->InsG.AdjustWhite;
			BItem->GetThresholdW()->InsG.NMinNGCountL	=ALib->InsG.NMinNGCountL;
			BItem->GetThresholdW()->InsG.NMinNGCountH	=ALib->InsG.NMinNGCountH;
			BItem->GetThresholdW()->InsG.BMinNGCountL	=ALib->InsG.BMinNGCountL;
			BItem->GetThresholdW()->InsG.BMinNGCountH	=ALib->InsG.BMinNGCountH;
			BItem->GetThresholdW()->InsG.NOKLengthL		=ALib->InsG.NOKLengthL;
			BItem->GetThresholdW()->InsG.NOKLengthH		=ALib->InsG.NOKLengthH;
			BItem->GetThresholdW()->InsG.BOKLengthL		=ALib->InsG.BOKLengthL;
			BItem->GetThresholdW()->InsG.BOKLengthH		=ALib->InsG.BOKLengthH;

			BItem->GetThresholdW()->InsB.NBrightWidthL	=ALib->InsB.NBrightWidthL;
			BItem->GetThresholdW()->InsB.NBrightWidthH	=ALib->InsB.NBrightWidthH;
			BItem->GetThresholdW()->InsB.NOKDotL		=ALib->InsB.NOKDotL;
			BItem->GetThresholdW()->InsB.NOKDotH		=ALib->InsB.NOKDotH;
			BItem->GetThresholdW()->InsB.BBrightWidthL	=ALib->InsB.BBrightWidthL;
			BItem->GetThresholdW()->InsB.BBrightWidthH	=ALib->InsB.BBrightWidthH;
			BItem->GetThresholdW()->InsB.BOKDotL		=ALib->InsB.BOKDotL;
			BItem->GetThresholdW()->InsB.BOKDotH		=ALib->InsB.BOKDotH;
			BItem->GetThresholdW()->InsB.AdjustBlack	=ALib->InsB.AdjustBlack;
			BItem->GetThresholdW()->InsB.AdjustWhite	=ALib->InsB.AdjustWhite;
			BItem->GetThresholdW()->InsB.NMinNGCountL	=ALib->InsB.NMinNGCountL;
			BItem->GetThresholdW()->InsB.NMinNGCountH	=ALib->InsB.NMinNGCountH;
			BItem->GetThresholdW()->InsB.BMinNGCountL	=ALib->InsB.BMinNGCountL;
			BItem->GetThresholdW()->InsB.BMinNGCountH	=ALib->InsB.BMinNGCountH;
			BItem->GetThresholdW()->InsB.NOKLengthL		=ALib->InsB.NOKLengthL;
			BItem->GetThresholdW()->InsB.NOKLengthH		=ALib->InsB.NOKLengthH;
			BItem->GetThresholdW()->InsB.BOKLengthL		=ALib->InsB.BOKLengthL;
			BItem->GetThresholdW()->InsB.BOKLengthH		=ALib->InsB.BOKLengthH;

			ui.ButtonOK->setEnabled(true);
		}
		else{
			QMessageBox::critical(NULL, LangSolver.GetString(ColorCreateManualBlockForm_LS,LID_44)/*"Library error"*/, LangSolver.GetString(ColorCreateManualBlockForm_LS,LID_45)/*"Not loaded this library record"*/);
		}
	}
}

void ColorCreateManualBlockForm::ShowLibrary(AlgorithmLibraryLevelContainer	*tempLib)
{
	BlockLibID					=tempLib->GetLibID();
	ui.EditLibID				->setText(QString::number(tempLib->GetLibID()));
	ui.EditLibName				->setText(tempLib->GetLibName());

	ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(tempLib->GetLibrary());
	if(ButtonR.isChecked()==true){
		ui.EditNBrightWidthL	->setValue(ALib->InsR.NBrightWidthL);
		ui.EditNBrightWidthH	->setValue(ALib->InsR.NBrightWidthH);
		ui.EditNOKDotL			->setValue(ALib->InsR.NOKDotL);
		ui.EditNOKDotH			->setValue(ALib->InsR.NOKDotH);
		ui.EditBBrightWidthL	->setValue(ALib->InsR.BBrightWidthL);
		ui.EditBBrightWidthH	->setValue(ALib->InsR.BBrightWidthH);
		ui.EditBOKDotL			->setValue(ALib->InsR.BOKDotL);
		ui.EditBOKDotH			->setValue(ALib->InsR.BOKDotH);
		ui.EditAdjustBlack		->setValue(ALib->InsR.AdjustBlack);
		ui.EditAdjustWhite		->setValue(ALib->InsR.AdjustWhite);
		ui.EditNMinNGCountL		->setValue(ALib->InsR.NMinNGCountL);
		ui.EditNMinNGCountH		->setValue(ALib->InsR.NMinNGCountH);
		ui.EditBMinNGCountL		->setValue(ALib->InsR.BMinNGCountL);
		ui.EditBMinNGCountH		->setValue(ALib->InsR.BMinNGCountH);
		ui.EditNOKLengthL		->setValue(ALib->InsR.NOKLengthL);
		ui.EditNOKLengthH		->setValue(ALib->InsR.NOKLengthH);
		ui.EditBOKLengthL		->setValue(ALib->InsR.BOKLengthL);
		ui.EditBOKLengthH		->setValue(ALib->InsR.BOKLengthH);
	}
	else if(ButtonG.isChecked()==true){
		ui.EditNBrightWidthL	->setValue(ALib->InsG.NBrightWidthL);
		ui.EditNBrightWidthH	->setValue(ALib->InsG.NBrightWidthH);
		ui.EditNOKDotL			->setValue(ALib->InsG.NOKDotL);
		ui.EditNOKDotH			->setValue(ALib->InsG.NOKDotH);
		ui.EditBBrightWidthL	->setValue(ALib->InsG.BBrightWidthL);
		ui.EditBBrightWidthH	->setValue(ALib->InsG.BBrightWidthH);
		ui.EditBOKDotL			->setValue(ALib->InsG.BOKDotL);
		ui.EditBOKDotH			->setValue(ALib->InsG.BOKDotH);
		ui.EditAdjustBlack		->setValue(ALib->InsG.AdjustBlack);
		ui.EditAdjustWhite		->setValue(ALib->InsG.AdjustWhite);
		ui.EditNMinNGCountL		->setValue(ALib->InsG.NMinNGCountL);
		ui.EditNMinNGCountH		->setValue(ALib->InsG.NMinNGCountH);
		ui.EditBMinNGCountL		->setValue(ALib->InsG.BMinNGCountL);
		ui.EditBMinNGCountH		->setValue(ALib->InsG.BMinNGCountH);
		ui.EditNOKLengthL		->setValue(ALib->InsG.NOKLengthL);
		ui.EditNOKLengthH		->setValue(ALib->InsG.NOKLengthH);
		ui.EditBOKLengthL		->setValue(ALib->InsG.BOKLengthL);
		ui.EditBOKLengthH		->setValue(ALib->InsG.BOKLengthH);
	}
	else if(ButtonB.isChecked()==true){
		ui.EditNBrightWidthL	->setValue(ALib->InsB.NBrightWidthL);
		ui.EditNBrightWidthH	->setValue(ALib->InsB.NBrightWidthH);
		ui.EditNOKDotL			->setValue(ALib->InsB.NOKDotL);
		ui.EditNOKDotH			->setValue(ALib->InsB.NOKDotH);
		ui.EditBBrightWidthL	->setValue(ALib->InsB.BBrightWidthL);
		ui.EditBBrightWidthH	->setValue(ALib->InsB.BBrightWidthH);
		ui.EditBOKDotL			->setValue(ALib->InsB.BOKDotL);
		ui.EditBOKDotH			->setValue(ALib->InsB.BOKDotH);
		ui.EditAdjustBlack		->setValue(ALib->InsB.AdjustBlack);
		ui.EditAdjustWhite		->setValue(ALib->InsB.AdjustWhite);
		ui.EditNMinNGCountL		->setValue(ALib->InsB.NMinNGCountL);
		ui.EditNMinNGCountH		->setValue(ALib->InsB.NMinNGCountH);
		ui.EditBMinNGCountL		->setValue(ALib->InsB.BMinNGCountL);
		ui.EditBMinNGCountH		->setValue(ALib->InsB.BMinNGCountH);
		ui.EditNOKLengthL		->setValue(ALib->InsB.NOKLengthL);
		ui.EditNOKLengthH		->setValue(ALib->InsB.NOKLengthH);
		ui.EditBOKLengthL		->setValue(ALib->InsB.BOKLengthL);
		ui.EditBOKLengthH		->setValue(ALib->InsB.BOKLengthH);
	}
	ui.checkBModeEnabled		->setChecked(ALib->PointMove.ModeEnabled);
	ui.checkBModeAbsoluteBright	->setChecked(ALib->PointMove.ModeAbsoluteBright);
	ui.checkBModeNGCluster		->setChecked(ALib->PointMove.ModeNGCluster);
	ui.checkBModeDiffer			->setChecked(ALib->PointMove.ModeDiffer);
	ui.checkBModeOnlyMatching	->setChecked(ALib->PointMove.ModeOnlyMatching);
	ui.checkBModeWhiteMask		->setChecked(ALib->PointMove.ModeWhiteMask);
	ui.checkBModeBlackMask		->setChecked(ALib->PointMove.ModeBlackMask);
	ui.checkBModeCenterBrightFromParts	->setChecked(ALib->PointMove.ModeCenterBrightFromParts);
	ui.checkBModeAdjustable		->setChecked(ALib->PointMove.ModeAdjustable);
	ui.checkBModeCommonMovable	->setChecked(ALib->PointMove.ModeCommonMovable);
	ui.EditSelfSearch			->setValue	(ALib->SelfSearch);
	ui.EditCommonMoveDot		->setValue	(ALib->CommonMoveDot);
}

void	ColorCreateManualBlockForm::GetDataFromWindow(ColorBlockItem &data)
{
	data.SetLibID(BlockLibID);
	if(CurrentColor==0){
		data.GetThresholdW()->InsR.NBrightWidthL	=ui.EditNBrightWidthL	->value();
		data.GetThresholdW()->InsR.NBrightWidthH	=ui.EditNBrightWidthH	->value();
		data.GetThresholdW()->InsR.NOKDotL			=ui.EditNOKDotL			->value();
		data.GetThresholdW()->InsR.NOKDotH			=ui.EditNOKDotH			->value();
		data.GetThresholdW()->InsR.BBrightWidthL	=ui.EditBBrightWidthL	->value();
		data.GetThresholdW()->InsR.BBrightWidthH	=ui.EditBBrightWidthH	->value();
		data.GetThresholdW()->InsR.BOKDotL			=ui.EditBOKDotL			->value();
		data.GetThresholdW()->InsR.BOKDotH			=ui.EditBOKDotH			->value();
		data.GetThresholdW()->InsR.AdjustBlack		=ui.EditAdjustBlack		->value();
		data.GetThresholdW()->InsR.AdjustWhite		=ui.EditAdjustWhite		->value();
		data.GetThresholdW()->InsR.NMinNGCountL		=ui.EditNMinNGCountL	->value();
		data.GetThresholdW()->InsR.NMinNGCountH		=ui.EditNMinNGCountH	->value();
		data.GetThresholdW()->InsR.BMinNGCountL		=ui.EditBMinNGCountL	->value();
		data.GetThresholdW()->InsR.BMinNGCountH		=ui.EditBMinNGCountH	->value();
		data.GetThresholdW()->InsR.NOKLengthL		=ui.EditNOKLengthL		->value();
		data.GetThresholdW()->InsR.NOKLengthH		=ui.EditNOKLengthH		->value();
		data.GetThresholdW()->InsR.BOKLengthL		=ui.EditBOKLengthL		->value();
		data.GetThresholdW()->InsR.BOKLengthH		=ui.EditBOKLengthH		->value();
	}
	else if(CurrentColor==1){
		data.GetThresholdW()->InsG.NBrightWidthL	=ui.EditNBrightWidthL	->value();
		data.GetThresholdW()->InsG.NBrightWidthH	=ui.EditNBrightWidthH	->value();
		data.GetThresholdW()->InsG.NOKDotL			=ui.EditNOKDotL			->value();
		data.GetThresholdW()->InsG.NOKDotH			=ui.EditNOKDotH			->value();
		data.GetThresholdW()->InsG.BBrightWidthL	=ui.EditBBrightWidthL	->value();
		data.GetThresholdW()->InsG.BBrightWidthH	=ui.EditBBrightWidthH	->value();
		data.GetThresholdW()->InsG.BOKDotL			=ui.EditBOKDotL			->value();
		data.GetThresholdW()->InsG.BOKDotH			=ui.EditBOKDotH			->value();
		data.GetThresholdW()->InsG.AdjustBlack		=ui.EditAdjustBlack		->value();
		data.GetThresholdW()->InsG.AdjustWhite		=ui.EditAdjustWhite		->value();
		data.GetThresholdW()->InsG.NMinNGCountL		=ui.EditNMinNGCountL	->value();
		data.GetThresholdW()->InsG.NMinNGCountH		=ui.EditNMinNGCountH	->value();
		data.GetThresholdW()->InsG.BMinNGCountL		=ui.EditBMinNGCountL	->value();
		data.GetThresholdW()->InsG.BMinNGCountH		=ui.EditBMinNGCountH	->value();
		data.GetThresholdW()->InsG.NOKLengthL		=ui.EditNOKLengthL		->value();
		data.GetThresholdW()->InsG.NOKLengthH		=ui.EditNOKLengthH		->value();
		data.GetThresholdW()->InsG.BOKLengthL		=ui.EditBOKLengthL		->value();
		data.GetThresholdW()->InsG.BOKLengthH		=ui.EditBOKLengthH		->value();
	}
	else if(CurrentColor==2){
		data.GetThresholdW()->InsB.NBrightWidthL	=ui.EditNBrightWidthL	->value();
		data.GetThresholdW()->InsB.NBrightWidthH	=ui.EditNBrightWidthH	->value();
		data.GetThresholdW()->InsB.NOKDotL			=ui.EditNOKDotL			->value();
		data.GetThresholdW()->InsB.NOKDotH			=ui.EditNOKDotH			->value();
		data.GetThresholdW()->InsB.BBrightWidthL	=ui.EditBBrightWidthL	->value();
		data.GetThresholdW()->InsB.BBrightWidthH	=ui.EditBBrightWidthH	->value();
		data.GetThresholdW()->InsB.BOKDotL			=ui.EditBOKDotL			->value();
		data.GetThresholdW()->InsB.BOKDotH			=ui.EditBOKDotH			->value();
		data.GetThresholdW()->InsB.AdjustBlack		=ui.EditAdjustBlack		->value();
		data.GetThresholdW()->InsB.AdjustWhite		=ui.EditAdjustWhite		->value();
		data.GetThresholdW()->InsB.NMinNGCountL		=ui.EditNMinNGCountL	->value();
		data.GetThresholdW()->InsB.NMinNGCountH		=ui.EditNMinNGCountH	->value();
		data.GetThresholdW()->InsB.BMinNGCountL		=ui.EditBMinNGCountL	->value();
		data.GetThresholdW()->InsB.BMinNGCountH		=ui.EditBMinNGCountH	->value();
		data.GetThresholdW()->InsB.NOKLengthL		=ui.EditNOKLengthL		->value();
		data.GetThresholdW()->InsB.NOKLengthH		=ui.EditNOKLengthH		->value();
		data.GetThresholdW()->InsB.BOKLengthL		=ui.EditBOKLengthL		->value();
		data.GetThresholdW()->InsB.BOKLengthH		=ui.EditBOKLengthH		->value();
	}
	data.GetThresholdW()->PointMove.ModeEnabled					=ui.checkBModeEnabled			->isChecked();
	data.GetThresholdW()->PointMove.ModeAbsoluteBright			=ui.checkBModeAbsoluteBright	->isChecked();
	data.GetThresholdW()->PointMove.ModeNGCluster				=ui.checkBModeNGCluster			->isChecked();
	data.GetThresholdW()->PointMove.ModeDiffer					=ui.checkBModeDiffer			->isChecked();
	data.GetThresholdW()->PointMove.ModeOnlyMatching			=ui.checkBModeOnlyMatching		->isChecked();
	data.GetThresholdW()->PointMove.ModeWhiteMask				=ui.checkBModeWhiteMask			->isChecked();
	data.GetThresholdW()->PointMove.ModeBlackMask				=ui.checkBModeBlackMask			->isChecked();
	data.GetThresholdW()->PointMove.ModeCenterBrightFromParts	=ui.checkBModeCenterBrightFromParts	->isChecked();
	data.GetThresholdW()->PointMove.ModeAdjustable				=ui.checkBModeAdjustable		->isChecked();
	data.GetThresholdW()->PointMove.ModeCommonMovable			=ui.checkBModeCommonMovable	->isChecked();
	data.GetThresholdW()->SelfSearch	=ui.EditSelfSearch		->value();
	data.GetThresholdW()->CommonMoveDot	=ui.EditCommonMoveDot	->value();
}



void ColorCreateManualBlockForm::on_ButtonOK_clicked()
{
	GetDataFromWindow(*BItem);
	done(true);
}

void ColorCreateManualBlockForm::on_ButtonCancel_clicked()
{
	done(false);
}


void ColorCreateManualBlockForm::on_ToolButton_clicked()
{
	GetDataFromWindow(*BItem);

	if(ButtonR.isChecked()==true)
		CurrentColor=0;
	else if(ButtonG.isChecked()==true)
		CurrentColor=1;
	else if(ButtonB.isChecked()==true)
		CurrentColor=2;

	//Reflect();
	ShowLibrary(TempLib);
}
