/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\TrueColorHistgramForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTrueColorBlockResource.h"
#include "TrueColorHistgramForm.h"
#include "XTrueColorBlock.h"
#include "XTrueColorBlockLibrary.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

TrueColorHistgramForm::TrueColorHistgramForm(ShowAndSetItemsBaseClass *Something ,LayersBase *Base, QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
	,ColorSamples(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	IData=NULL;

	ui.labelResultNDark	->setText(/**/"");
	ui.labelResultBDark	->setText(/**/"");

	ColorRaw		.setParent(ui.frameCurrentItem);
	ColorThre		.setParent(ui.frameThreshold);

	ColorRaw		.Fit(ui.frameCurrentItem);
	ColorThre		.Fit(ui.frameThreshold);

	connect(&ColorThre,SIGNAL(AddEliminated(void)),this,SLOT(SlotAddEliminated(void)));
	connect(&ColorThre,SIGNAL(DelEliminated(void)),this,SLOT(SlotDelEliminated(void)));

	ColorSamples.setParent(ui.frameColorSample);
	ColorSamples.move(0,0);
	GUIFormBase	*GProp=NULL;
	if(Something==NULL)
		GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,/**/"");
	else{
		ShowAndSetItemsTrueColor	*k=dynamic_cast<ShowAndSetItemsTrueColor *>(Something);
		if(k!=NULL){
			GProp=k->Form;
		}
	}
	if(GProp!=NULL){
		DisplayImage	*Display=dynamic_cast<DisplayImage *>(GProp);
		PickupColor=Display->GetPickedColor();
		PickupColorFrame.setParent(ui.framePickupColor);
		PickupColorFrame.move(0,0);
		PickupColorFrame.resize(ui.framePickupColor->width(),ui.framePickupColor->height());
		PickupColorFrame.SetColor(PickupColor);
	}

	connect(&ColorSamples,SIGNAL(SignalBeforeSave ()),this,SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples,SIGNAL(SignalSelectCData()),this,SLOT(SlotColorSampleSelectOne()));
	ui.tabWidgetInspect->setCurrentIndex(0);
	CurrentTabIndex=ui.tabWidgetInspect->currentIndex ();

	SetupPassword();

	InstallOperationLog(this);
}

void	TrueColorHistgramForm::SlotAddEliminated(void)
{
	ShowThresholdList();
	if(CurrentTabIndex==0){
		AbsNInsColor	=ColorThre.Cube;
		NInsColor=AbsNInsColor;
		NInsColor.Multiply(1.0/Multiplier);
	}
	else if(CurrentTabIndex==1){
		AbsBInsColor	=ColorThre.Cube;
		BInsColor=AbsBInsColor;
		BInsColor.Multiply(1.0/Multiplier);
	}
}
void	TrueColorHistgramForm::SlotDelEliminated(void)
{
	ShowThresholdList();
	if(CurrentTabIndex==0){
		AbsNInsColor	=ColorThre.Cube;
		NInsColor=AbsNInsColor;
		NInsColor.Multiply(1.0/Multiplier);
	}
	else if(CurrentTabIndex==1){
		AbsBInsColor	=ColorThre.Cube;
		BInsColor=AbsBInsColor;
		BInsColor.Multiply(1.0/Multiplier);
	}
}

TrueColorHistgramForm::~TrueColorHistgramForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void	TrueColorHistgramForm::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorThre.Cube);
}
void	TrueColorHistgramForm::SlotColorSampleSelectOne()
{
	if(ColorSamples.CData.GetColorLogic()==NULL)
		return;
	ColorThre.Cube=*ColorSamples.CData.GetColorLogic();
	ColorThre.InitializedDoneCube();
	ColorThre.Repaint();
	if(ui.tabWidgetInspect->currentIndex ()==0){
		NInsColor	=ColorThre.Cube;
	}
	else if(ui.tabWidgetInspect->currentIndex ()==1){
		BInsColor	=ColorThre.Cube;
	}
}
void	TrueColorHistgramForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	CreateThreshld();
}

void	TrueColorHistgramForm::CreateThreshld(void)
{
	if(IData==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		TrueColorBlockItem	*BData=dynamic_cast<TrueColorBlockItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,TrueColorBlockReqThresholdReqCommand ,TrueColorBlockReqThresholdSendCommand);
		((TrueColorBlockThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((TrueColorBlockThresholdReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((TrueColorBlockThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			TrueColorBlockThresholdSend	*ThrePoint=(TrueColorBlockThresholdSend *)PacketSend.GetData();
			CenterBright		=ThrePoint->CenterBright;
			NInsColor			=ThrePoint->NInsColor;
			BInsColor			=ThrePoint->BInsColor;
			AbsNInsColor		=ThrePoint->AbsNInsColor;
			AbsBInsColor		=ThrePoint->AbsBInsColor;
			Multiplier			=ThrePoint->Multiplier;
			NMinNGCount			=ThrePoint->NMinNGCount;
			BMinNGCount			=ThrePoint->BMinNGCount;
			BOKLength			=ThrePoint->BOKLength;
			NOKLength			=ThrePoint->NOKLength;

			break;
		}
	}
	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
}

void TrueColorHistgramForm::GetHistogramData(void)
{
	if(IData==NULL)
		return;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		TrueColorBlockItem	*BData=dynamic_cast<TrueColorBlockItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,TrueColorBlockHistogramListReqCommand ,TrueColorBlockHistogramListSendCommand);
		((TrueColorBlockHistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((TrueColorBlockHistogramListReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((TrueColorBlockHistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			TrueColorBlockHistogramListSend	*L=(TrueColorBlockHistogramListSend *)PacketSend.GetData();
			ColorRaw.Cube	=L->TargetColor;
			ColorRaw.InitializedDoneCube();
			MasterColor		=L->MasterColor;
			TargetColor		=L->TargetColor;

			return;
		}
	}
}

void TrueColorHistgramForm::on_ButtonClose_clicked()
{
	close();
}

void	TrueColorHistgramForm::ShowLibrary(void)
{
	if(IData==NULL)
		return;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		TrueColorBlockItem	*BData=dynamic_cast<TrueColorBlockItem *>(DA);
		if(BData==NULL)
			continue;

		if(DA->GetLibID()<0){
			ui.EditLibID->setText(/**/"");
			ui.EditLibName->setText(/**/"");
		}
		else{
			ui.EditLibID	->setText(QString::number(DA->GetLibID()));
			ui.EditLibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui.EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}


		ui.EditNMergin				->setValue(BData->GetThresholdR(GetLayersBase())->NMergin);
		ui.EditNOKDot				->setValue(BData->GetThresholdR(GetLayersBase())->NOKDot);
		ui.EditBMergin				->setValue(BData->GetThresholdR(GetLayersBase())->BMergin);
		ui.EditBOKDot				->setValue(BData->GetThresholdR(GetLayersBase())->BOKDot);
		ui.EditNMinNGCount			->setValue(BData->GetThresholdR(GetLayersBase())->NMinNGCount);
		ui.EditBMinNGCount			->setValue(BData->GetThresholdR(GetLayersBase())->BMinNGCount);
		ui.EditNOKLength			->setValue(BData->GetThresholdR(GetLayersBase())->NOKLength);
		ui.EditBOKLength			->setValue(BData->GetThresholdR(GetLayersBase())->BOKLength);

		ui.checkBModeEnabled		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeEnabled);
		ui.checkBModeNGCluster		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeNGCluster);
		ui.checkBModeOnlyMatching	->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeOnlyMatching);
		ui.checkBModeCenterBrightFromParts	->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeCenterBrightFromParts);
		ui.checkBModeAdjustable		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeAdjustable);
		ui.checkBModeInvertLogic	->setChecked(BData->GetInvertLogic());
		ui.EditAdjustBlack			->setValue(BData->GetThresholdR(GetLayersBase())->AdjustBlack);
		ui.EditAdjustWhite			->setValue(BData->GetThresholdR(GetLayersBase())->AdjustWhite);
		ui.checkBModeCommonMovable	->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeCommonMovable);
		ui.EditSelfSearch			->setValue(BData->GetThresholdR(GetLayersBase())->SelfSearch);
		ui.EditCommonMoveDot		->setValue(BData->GetThresholdR(GetLayersBase())->CommonMoveDot);
		if(BData->IsOriginParts()==true){
			ui.stackedWidgetParts->setCurrentIndex(1);
		}
		else{
			ui.stackedWidgetParts->setCurrentIndex(0);
		}		
		return;
	}
}

void TrueColorHistgramForm::ShowThreshold(void)
{
	if(IData==NULL)
		return;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		TrueColorBlockItem	*BData=dynamic_cast<TrueColorBlockItem *>(DA);
		if(BData==NULL)
			continue;

		if(ui.tabWidgetInspect->currentIndex ()==0){
			ColorThre.Cube=AbsNInsColor;
			ColorThre.InitializedDoneCube();
			ColorThre.Repaint();
			ui.framePicked		->setVisible(true);
			ui.frameCurrentPos	->setVisible(true);
			ui.frameTarget		->setVisible(true);
		}
		else if(ui.tabWidgetInspect->currentIndex ()==1){
			ColorThre.Cube=AbsBInsColor;
			ColorThre.InitializedDoneCube();
			ColorThre.Repaint();
			ui.framePicked		->setVisible(true);
			ui.frameCurrentPos	->setVisible(true);
			ui.frameTarget		->setVisible(true);
		}
		else{
			ui.framePicked		->setVisible(false);
			ui.frameCurrentPos	->setVisible(false);
			ui.frameTarget		->setVisible(false);
		}
		ShowThresholdList();
		return;
	}
}
void TrueColorHistgramForm::ShowThresholdList(void)
{
	ui.listWidgetBaseColor->clear();
	ui.listWidgetEliminatedColor->clear();
	int	N=1;
	for(ColorSpace *c=ColorThre.Cube.GetFirstBase();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetBaseColor->addItem(QString::number(N));
	}
	N=1;
	for(ColorSpace *c=ColorThre.Cube.GetFirstEliminated();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetEliminatedColor->addItem(QString::number(N));
	}
}

void	TrueColorHistgramForm::GetDataFromWindow(void)
{
	if(CurrentTabIndex==0){
		AbsNInsColor	=ColorThre.Cube;
		NInsColor=AbsNInsColor;
		NInsColor.Multiply(1.0/Multiplier);
	}
	else if(CurrentTabIndex==1){
		AbsBInsColor	=ColorThre.Cube;
		BInsColor=AbsBInsColor;
		BInsColor.Multiply(1.0/Multiplier);
	}

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		TrueColorBlockItem	*BData=dynamic_cast<TrueColorBlockItem *>(DA);
		if(BData==NULL)
			continue;
		TrueColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->NInsColor					=NInsColor;
		Thr->NMergin					=ui.EditNMergin			->value();
		Thr->NOKDot						=ui.EditNOKDot			->value();
		Thr->BInsColor					=BInsColor;
		Thr->BMergin					=ui.EditBMergin			->value();
		Thr->BOKDot						=ui.EditBOKDot			->value();
		Thr->PointMove.ModeEnabled		=ui.checkBModeEnabled			->isChecked();
		Thr->PointMove.ModeNGCluster	=ui.checkBModeNGCluster			->isChecked();
		Thr->PointMove.ModeOnlyMatching	=ui.checkBModeOnlyMatching		->isChecked();
		Thr->PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
		Thr->PointMove.ModeAdjustable	=ui.checkBModeAdjustable		->isChecked();
		Thr->AdjustBlack				=ui.EditAdjustBlack		->value();
		Thr->AdjustWhite				=ui.EditAdjustWhite		->value();
		Thr->PointMove.ModeCommonMovable=ui.checkBModeCommonMovable	->isChecked();
		Thr->SelfSearch					=ui.EditSelfSearch		->value();
		Thr->CommonMoveDot				=ui.EditCommonMoveDot	->value();
		Thr->NMinNGCount				=ui.EditNMinNGCount		->value();
		Thr->BMinNGCount				=ui.EditBMinNGCount		->value();
		Thr->NOKLength					=ui.EditNOKLength		->value();
		Thr->BOKLength					=ui.EditBOKLength		->value();

		BData->SetInvertLogic(ui.checkBModeInvertLogic->isChecked());

		//return;
	}
}


void TrueColorHistgramForm::on_ButtonRefrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE TrueColorBlock threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one TrueColorBlock threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}

	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void TrueColorHistgramForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL TrueColorBlocks\' threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all TrueColorBlock threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}

	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void TrueColorHistgramForm::on_ButtonCalc_clicked()
{
	if(IData==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		TrueColorBlockItem	*nBData=dynamic_cast<TrueColorBlockItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,TrueColorBlockReqTryThresholdCommand ,TrueColorBlockSendTryThresholdCommand);
		TrueColorBlockItem	*BData=&((TrueColorBlockReqTryThreshold *)PacketReq.Data)->Threshold;
		((TrueColorBlockReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((TrueColorBlockReqTryThreshold *)PacketReq.Data)->BlockItemID	=DA->GetID();
		TrueColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		Thr->NInsColor					=NInsColor;
		Thr->NMergin					=ui.EditNMergin			->value();
		Thr->NOKDot						=ui.EditNOKDot			->value();
		Thr->BInsColor					=BInsColor;
		Thr->BMergin					=ui.EditBMergin			->value();
		Thr->BOKDot						=ui.EditBOKDot			->value();
		Thr->PointMove.ModeEnabled		=ui.checkBModeEnabled			->isChecked();
		Thr->PointMove.ModeNGCluster	=ui.checkBModeNGCluster			->isChecked();
		Thr->PointMove.ModeOnlyMatching	=ui.checkBModeOnlyMatching		->isChecked();
		Thr->PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
		Thr->PointMove.ModeAdjustable	=ui.checkBModeAdjustable		->isChecked();
		Thr->AdjustBlack				=ui.EditAdjustBlack		->value();
		Thr->AdjustWhite				=ui.EditAdjustWhite		->value();
		Thr->PointMove.ModeCommonMovable=ui.checkBModeCommonMovable	->isChecked();
		Thr->SelfSearch					=ui.EditSelfSearch		->value();
		Thr->CommonMoveDot				=ui.EditCommonMoveDot	->value();
		Thr->NMinNGCount				=ui.EditNMinNGCount		->value();
		Thr->BMinNGCount				=ui.EditBMinNGCount		->value();
		Thr->NOKLength					=ui.EditNOKLength		->value();
		Thr->BOKLength					=ui.EditBOKLength		->value();
		BData->SetInvertLogic(ui.checkBModeInvertLogic->isChecked());

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			TrueColorBlockSendTryThreshold	*R=((TrueColorBlockSendTryThreshold *)PacketSend.Data);
			ui.labelResultNDark	->setText(QString::number(R->NGDotInN	));
			ui.labelResultBDark	->setText(QString::number(R->NGDotInB	));
			break;
		}
	}
}

void TrueColorHistgramForm::on_ButtonRelrectSaveParts_clicked()
{
	GetDataFromWindow();
	if(IData==NULL)
		return;

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		TrueColorBlockItem	*BData=dynamic_cast<TrueColorBlockItem *>(DA);
		if(BData==NULL)
			continue;

		int	Page=D->GlobalPage;
		GUICmdReqUpdateAlgorithmOnPiece	Req(GetLayersBase() ,/**/"ANY",/**/"ANY",Page);
		Req.PieceCode=BData->GetPartsID();
		Req.DLLRoot=sRoot;
		Req.DLLName=sName;
		Req.IData=*IData;
		Req.Command=SetIndependentItemDataCommand_All;
		GUICmdAckUpdateAlgorithmOnPiece	Ack(GetLayersBase() ,/**/"ANY",/**/"ANY",Page);
		if(Req.Send(Page ,0,Ack)==false)
			QMessageBox::warning (NULL, LangSolver.GetString(TrueColorHistgramForm_LS,LID_26)/*"Error"*/, LangSolver.GetString(TrueColorHistgramForm_LS,LID_27)/*"Error occurs in saving algorithm data of parts"*/ );
		while(Ack.IsReceived()==false);
		if(Ack.Ret==false){
			QMessageBox::warning (NULL, LangSolver.GetString(TrueColorHistgramForm_LS,LID_28)/*"Error"*/, LangSolver.GetString(TrueColorHistgramForm_LS,LID_29)/*"Error occurs in saving algorithm data of parts"*/ );
		}
	}
}

void TrueColorHistgramForm::on_pushButtonAddColor_clicked()
{
	if(ColorSamples.CData.GetColorLogic()==NULL)
		return;
	ColorThre.Cube.Add(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	if(ui.tabWidgetInspect->currentIndex ()==0){
		NInsColor	=ColorThre.Cube;
	}
	else if(ui.tabWidgetInspect->currentIndex ()==1){
		BInsColor	=ColorThre.Cube;
	}
	ShowThresholdList();
}

void TrueColorHistgramForm::on_pushButtonEliminateColor_clicked()
{
	if(ColorSamples.CData.GetColorLogic()==NULL)
		return;
	ColorThre.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	if(ui.tabWidgetInspect->currentIndex ()==0){
		NInsColor	=ColorThre.Cube;
	}
	else if(ui.tabWidgetInspect->currentIndex ()==1){
		BInsColor	=ColorThre.Cube;
	}
	ShowThresholdList();
}

void TrueColorHistgramForm::on_pushButtonAdd_clicked()
{
	ColorThre.Cube.Add(ColorRaw.Cube,ui.spinBoxMerginAdd->value());
	ColorThre.Repaint();
	if(ui.tabWidgetInspect->currentIndex ()==0){
		NInsColor	=ColorThre.Cube;
	}
	else if(ui.tabWidgetInspect->currentIndex ()==1){
		BInsColor	=ColorThre.Cube;
	}
	ShowThresholdList();
}

void TrueColorHistgramForm::on_pushButtonSub_clicked()
{
	ColorThre.Cube.Eliminate(ColorRaw.Cube,ui.spinBoxMerginSub->value());
	ColorThre.Repaint();
	if(ui.tabWidgetInspect->currentIndex ()==0){
		NInsColor	=ColorThre.Cube;
	}
	else if(ui.tabWidgetInspect->currentIndex ()==1){
		BInsColor	=ColorThre.Cube;
	}
	ShowThresholdList();
}

void TrueColorHistgramForm::on_pushButtonAddPickupColor_clicked()
{
	ColorThre.Cube.Add(PickupColor.rgb(),ui.spinBoxMerginAddPickupColor->value());
	ColorThre.Repaint();
	if(ui.tabWidgetInspect->currentIndex ()==0){
		NInsColor	=ColorThre.Cube;
	}
	else if(ui.tabWidgetInspect->currentIndex ()==1){
		BInsColor	=ColorThre.Cube;
	}
	ShowThresholdList();
}

void TrueColorHistgramForm::on_pushButtonSubPickupColor_clicked()
{
	ColorThre.Cube.Eliminame(PickupColor.rgb(),ui.spinBoxMerginSubPickupColor->value());
	ColorThre.Repaint();
	if(ui.tabWidgetInspect->currentIndex ()==0){
		NInsColor	=ColorThre.Cube;
	}
	else if(ui.tabWidgetInspect->currentIndex ()==1){
		BInsColor	=ColorThre.Cube;
	}
	ShowThresholdList();
}

void TrueColorHistgramForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	if(IData==NULL)
		return;
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		TrueColorBlockItem	*BData=dynamic_cast<TrueColorBlockItem *>(DA);
		if(BData==NULL)
			continue;
		TrueColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void TrueColorHistgramForm::on_ButtonLoadFromLibrary_clicked()
{
	if(IData==NULL)
		return;
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		TrueColorBlockItem	*BData=dynamic_cast<TrueColorBlockItem *>(DA);
		if(BData==NULL)
			continue;
		TrueColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			ShowThresholdList();
			return;
		}
	}
}

void TrueColorHistgramForm::on_tabWidgetInspect_currentChanged(int)
{
	if(CurrentTabIndex==0){
		AbsNInsColor	=ColorThre.Cube;
		NInsColor=AbsNInsColor;
		NInsColor.Multiply(1.0/Multiplier);
	}
	else if(CurrentTabIndex==1){
		AbsBInsColor	=ColorThre.Cube;
		BInsColor=AbsBInsColor;
		BInsColor.Multiply(1.0/Multiplier);
	}
	CurrentTabIndex=ui.tabWidgetInspect->currentIndex ();
	ShowThreshold();
	ShowThresholdList();
}

void TrueColorHistgramForm::on_listWidgetBaseColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetBaseColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetBase(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveBase(c);
		delete	c;
	}
	if(CurrentTabIndex==0){
		AbsNInsColor	=ColorThre.Cube;
	}
	else if(CurrentTabIndex==1){
		AbsBInsColor	=ColorThre.Cube;
	}
	ShowThreshold();
	ShowThresholdList();
}

void TrueColorHistgramForm::on_listWidgetEliminatedColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetEliminatedColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetEliminated(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveEliminated(c);
		delete	c;
	}
	if(CurrentTabIndex==0){
		AbsNInsColor	=ColorThre.Cube;
	}
	else if(CurrentTabIndex==1){
		AbsBInsColor	=ColorThre.Cube;
	}
	ShowThreshold();
	ShowThresholdList();
}

void TrueColorHistgramForm::on_listWidgetBaseColor_clicked(const QModelIndex &)
{
}

void TrueColorHistgramForm::on_listWidgetEliminatedColor_clicked(const QModelIndex &)
{

}

void TrueColorHistgramForm::on_pushButtonChangeLib_clicked()
{
	if(IData==NULL)
		return;

	AlgorithmBase	*ABase=IData->Base->GetAlgorithmBase(sRoot,sName);
	int		RetSelectedLibID;
	QString RetSelectedLibName;
	ExeSelectLibraryForm(ABase->GetLibType(),IData->Base, this
						,RetSelectedLibID
						,RetSelectedLibName);
	if(RetSelectedLibID>=0){
		for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
			AlgorithmItemRoot	*DA=D->Data;
			if(DA==NULL)
				continue;
			TrueColorBlockItem	*BData=dynamic_cast<TrueColorBlockItem *>(DA);
			if(BData==NULL)
				continue;

			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui.EditLibID	->setText(QString::number(DA->GetLibID()));
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==OldID){
					L->SetLibID(RetSelectedLibID);
					ABase->GetLibraryContainer()->GetLibraryNames(LibIDList);
					ui.EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
	}
}

void TrueColorHistgramForm::on_pushButtonAdd_2_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Add in PlaceColor");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemAddInPlaceColor;
	AlgorithmItemIndependent	*p=new AlgorithmItemIndependent(GetLayersBase(),sRoot,sName);
	QBuffer	Buff;
	Buff.open(QIODevice::WriteOnly);
	int	Mergin=ui.spinBoxMerginAdd_2->value();
	::Save(&Buff,Mergin);
	p->Something=Buff.buffer();
	Packet.IData.Items.AppendList(p);
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}

	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void TrueColorHistgramForm::on_pushButtonSub_2_clicked()
{

}