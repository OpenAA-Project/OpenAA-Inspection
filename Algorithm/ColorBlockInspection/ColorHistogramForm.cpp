/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\ColorHistogramForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ColorBlockFormResource.h"
#include "ColorHistogramForm.h"
#include "XColorBlockInspection.h"
#include "XColorBlockLibrary.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "mtToolButtonColored.h"
#include "swap.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

ColorHistogramForm::ColorHistogramForm(LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
	,SimPanel(Base,parent)
	,LGraph(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	SimPanel.setParent(ui.frame_SimImage);
	SimPanel.SetAlgo(/**/"Basic",/**/"ColorBlockInspection");
	SimPanel.SetGUI(/**/"Button",/**/"PropertyColorBlockForm");
	SimPanel.setGeometry(0,0,ui.frame_SimImage->width(),ui.frame_SimImage->height());
	connect(this,SIGNAL(SignalStartCalc()),this,SLOT(SlotStartCalc()),Qt::QueuedConnection);

	Page=0;
	LGraph.setParent(ui.frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.move(0,0);
	LGraph.resize(ui.frameLineGraph->width(),ui.frameLineGraph->height());
	LayerBar.setParent(ui.frameLayer);
	LayerBar.move(0,0);
	LayerBar.resize(ui.frameLayer->width(),ui.frameLayer->height());
	LButtonList=new mtToolButtonColored*[GetLayerNumb(0)];
	LastLayer=0;
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
		LButtonList[Layer]=new mtToolButtonColored(false);
		LButtonList[Layer]->setText(GetParamGlobal()->GetLayerName(Layer));
		LButtonList[Layer]->setColor(GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LButtonList[Layer]->setAutoExclusive(true);
		LButtonList[Layer]->setCheckable(true);
		LButtonList[Layer]->setAutoRaise(true);
		if(Layer==0)
			LButtonList[Layer]->setChecked(true);
		else
			LButtonList[Layer]->setChecked(false);
		LButtonList[Layer]->resize(48,32);
		LayerBar.addWidget(LButtonList[Layer]);
		connect(LButtonList[Layer],SIGNAL(clicked()),this,SLOT(SlotLayerClicked()));
	}

	QColor	MasterColor=Qt::green;
	QColor	TargetColor=Qt::yellow;
	QColor	ThreshColor=Qt::red;

	GraphColMaster	.SetLineColor(MasterColor);
	GraphColMaster	.SetLineWidth(1);
	GraphColMaster	.SetOffsetX(0);
	GraphColTarget	.SetLineColor(TargetColor);
	GraphColTarget	.SetLineWidth(1);
	GraphColTarget	.SetOffsetX(1);
	GraphThresh		.SetLineColor(ThreshColor);	
	GraphThresh		.SetLineWidth(1);
	GraphThresh		.SetOffsetX(2);
	LGraph.AddGraph(&GraphColMaster);
	LGraph.AddGraph(&GraphColTarget);
	LGraph.AddGraph(&GraphThresh);
	connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));

	IData=NULL;

	MasterPanel	=new mtColorFrame();
	MasterPanel->setParent(ui.frameMaster);
	MasterPanel->SetColor(MasterColor);
	TargetPanel	=new mtColorFrame();
	TargetPanel->setParent(ui.frameTarget);
	TargetPanel->SetColor(TargetColor);
	ThresholdPanel	=new mtColorFrame();
	ThresholdPanel->setParent(ui.frameThreshold);
	ThresholdPanel->SetColor(ThreshColor);

	ui.labelResultNDark	->setText(/**/"");
	ui.labelResultNLight->setText(/**/"");
	ui.labelResultBDark	->setText(/**/"");
	ui.labelResultBLight->setText(/**/"");

	SetupPassword();

	InstallOperationLog(this);
}

ColorHistogramForm::~ColorHistogramForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	delete	[]LButtonList;
	LButtonList=NULL;
}

void	ColorHistogramForm::GetActiveLayerList(IntList &LayerList)
{
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
		if(LButtonList[Layer]->isChecked()==true){
			LayerList.Add(Layer);
		}
	}
}
void	ColorHistogramForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	CreateThreshld();

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		SimPanel.SetLayer(-1);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
			if(BData!=NULL){
				Page	=D->GlobalPage;
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock		(ui.toolButtonSimShowBlock ->isChecked());
				SimPanel.SetModeShowBrightnessNG(ui.toolButtonSimShowBright->isChecked());
			}
		}
	}
}

void	ColorHistogramForm::CreateThreshld(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,BlockReqThresholdReqCommand ,BlockReqThresholdSendCommand);
		((ColorBlockThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((ColorBlockThresholdReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((ColorBlockThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			ColorBlockThresholdSend	*ThrePoint=(ColorBlockThresholdSend *)PacketSend.GetData();
			CenterBrightR		=ThrePoint->RRes.CenterBright;
			NBrightWidthRL		=ThrePoint->RRes.NBrightWidthL;		
			NBrightWidthRH		=ThrePoint->RRes.NBrightWidthH;		
			BBrightWidthRL		=ThrePoint->RRes.BBrightWidthL;		
			BBrightWidthRH		=ThrePoint->RRes.BBrightWidthH;		
			AbsNBrightWidthRL	=ThrePoint->RRes.AbsNBrightWidthL;	
			AbsNBrightWidthRH	=ThrePoint->RRes.AbsNBrightWidthH;	
			AbsBBrightWidthRL	=ThrePoint->RRes.AbsBBrightWidthL;	
			AbsBBrightWidthRH	=ThrePoint->RRes.AbsBBrightWidthH;	

			CenterBrightG		=ThrePoint->GRes.CenterBright;
			NBrightWidthGL		=ThrePoint->GRes.NBrightWidthL;		
			NBrightWidthGH		=ThrePoint->GRes.NBrightWidthH;		
			BBrightWidthGL		=ThrePoint->GRes.BBrightWidthL;		
			BBrightWidthGH		=ThrePoint->GRes.BBrightWidthH;		
			AbsNBrightWidthGL	=ThrePoint->GRes.AbsNBrightWidthL;	
			AbsNBrightWidthGH	=ThrePoint->GRes.AbsNBrightWidthH;	
			AbsBBrightWidthGL	=ThrePoint->GRes.AbsBBrightWidthL;	
			AbsBBrightWidthGH	=ThrePoint->GRes.AbsBBrightWidthH;	

			CenterBrightB		=ThrePoint->BRes.CenterBright;
			NBrightWidthBL		=ThrePoint->BRes.NBrightWidthL;		
			NBrightWidthBH		=ThrePoint->BRes.NBrightWidthH;		
			BBrightWidthBL		=ThrePoint->BRes.BBrightWidthL;		
			BBrightWidthBH		=ThrePoint->BRes.BBrightWidthH;		
			AbsNBrightWidthBL	=ThrePoint->BRes.AbsNBrightWidthL;	
			AbsNBrightWidthBH	=ThrePoint->BRes.AbsNBrightWidthH;	
			AbsBBrightWidthBL	=ThrePoint->BRes.AbsBBrightWidthL;	
			AbsBBrightWidthBH	=ThrePoint->BRes.AbsBBrightWidthH;	

			RNMinNGCountL		=ThrePoint->RRes.NMinNGCountL;
			RNMinNGCountH		=ThrePoint->RRes.NMinNGCountH;
			RBMinNGCountL		=ThrePoint->RRes.BMinNGCountL;
			RBMinNGCountH		=ThrePoint->RRes.BMinNGCountH;

			GNMinNGCountL		=ThrePoint->GRes.NMinNGCountL;
			GNMinNGCountH		=ThrePoint->GRes.NMinNGCountH;
			GBMinNGCountL		=ThrePoint->GRes.BMinNGCountL;
			GBMinNGCountH		=ThrePoint->GRes.BMinNGCountH;

			BNMinNGCountL		=ThrePoint->BRes.NMinNGCountL;
			BNMinNGCountH		=ThrePoint->BRes.NMinNGCountH;
			BBMinNGCountL		=ThrePoint->BRes.BMinNGCountL;
			BBMinNGCountH		=ThrePoint->BRes.BMinNGCountH;

			RBOKLengthL			=ThrePoint->RRes.BOKLengthL;
			RBOKLengthH			=ThrePoint->RRes.BOKLengthH;
			RNOKLengthL			=ThrePoint->RRes.NOKLengthL;
			RNOKLengthH			=ThrePoint->RRes.NOKLengthH;

			GBOKLengthL			=ThrePoint->GRes.BOKLengthL;
			GBOKLengthH			=ThrePoint->GRes.BOKLengthH;
			GNOKLengthL			=ThrePoint->GRes.NOKLengthL;
			GNOKLengthH			=ThrePoint->GRes.NOKLengthH;

			BBOKLengthL			=ThrePoint->BRes.BOKLengthL;
			BBOKLengthH			=ThrePoint->BRes.BOKLengthH;
			BNOKLengthL			=ThrePoint->BRes.NOKLengthL;
			BNOKLengthH			=ThrePoint->BRes.NOKLengthH;

			break;
		}
	}
	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
	LGraph.repaint();
}

void ColorHistogramForm::GetHistogramData(void)
{
	GraphColMaster.DeleteXY();
	GraphColTarget.DeleteXY();

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,BlockHistogramListReqCommand ,BlockHistogramListSendCommand);
		((ColorBlockHistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((ColorBlockHistogramListReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((ColorBlockHistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			ColorBlockHistogramListSend	*L=(ColorBlockHistogramListSend *)PacketSend.GetData();
			YMax=0;
			if(GetLayerNumb(0)>=1 && LButtonList[0]->isChecked()==true){
				for(int i=0;i<256;i++){
					YMax=max(YMax,L->ListMasterR[i]);
					YMax=max(YMax,L->ListTargetR[i]);
					GraphColMaster.AddXY(i		,L->ListMasterR[i]);
					GraphColTarget.AddXY(i+0.5	,L->ListTargetR[i]);
				}
			}
			else if(GetLayerNumb(0)>=2 && LButtonList[1]->isChecked()==true){
				for(int i=0;i<256;i++){
					YMax=max(YMax,L->ListMasterG[i]);
					YMax=max(YMax,L->ListTargetG[i]);
					GraphColMaster.AddXY(i		,L->ListMasterG[i]);
					GraphColTarget.AddXY(i+0.5	,L->ListTargetG[i]);
				}
			}
			else if(GetLayerNumb(0)>=3 && LButtonList[2]->isChecked()==true){
				for(int i=0;i<256;i++){
					YMax=max(YMax,L->ListMasterB[i]);
					YMax=max(YMax,L->ListTargetB[i]);
					GraphColMaster.AddXY(i		,L->ListMasterB[i]);
					GraphColTarget.AddXY(i+0.5	,L->ListTargetB[i]);
				}
			}
			return;
		}
	}
}

void ColorHistogramForm::on_ButtonClose_clicked()
{
	close();
}

void	ColorHistogramForm::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
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

		if(GetLayerNumb(0)>=1 && LButtonList[0]->isChecked()==true){
			ui.EditNBrightWidthL		->setValue(BData->GetThresholdR(GetLayersBase())->InsR.NBrightWidthL);
			ui.EditNBrightWidthH		->setValue(BData->GetThresholdR(GetLayersBase())->InsR.NBrightWidthH);
			ui.EditNOKDotL				->setValue(BData->GetThresholdR(GetLayersBase())->InsR.NOKDotL);
			ui.EditNOKDotH				->setValue(BData->GetThresholdR(GetLayersBase())->InsR.NOKDotH);
			ui.EditBBrightWidthL		->setValue(BData->GetThresholdR(GetLayersBase())->InsR.BBrightWidthL);
			ui.EditBBrightWidthH		->setValue(BData->GetThresholdR(GetLayersBase())->InsR.BBrightWidthH);
			ui.EditBOKDotL				->setValue(BData->GetThresholdR(GetLayersBase())->InsR.BOKDotL);
			ui.EditBOKDotH				->setValue(BData->GetThresholdR(GetLayersBase())->InsR.BOKDotH);
			ui.EditAdjustBlack			->setValue(BData->GetThresholdR(GetLayersBase())->InsR.AdjustBlack);
			ui.EditAdjustWhite			->setValue(BData->GetThresholdR(GetLayersBase())->InsR.AdjustWhite);
			ui.EditNMinNGCountL			->setValue(BData->GetThresholdR(GetLayersBase())->InsR.NMinNGCountL);
			ui.EditNMinNGCountH			->setValue(BData->GetThresholdR(GetLayersBase())->InsR.NMinNGCountH);
			ui.EditBMinNGCountL			->setValue(BData->GetThresholdR(GetLayersBase())->InsR.BMinNGCountL);
			ui.EditBMinNGCountH			->setValue(BData->GetThresholdR(GetLayersBase())->InsR.BMinNGCountH);
			ui.EditNOKLengthL			->setValue(BData->GetThresholdR(GetLayersBase())->InsR.NOKLengthL);
			ui.EditNOKLengthH			->setValue(BData->GetThresholdR(GetLayersBase())->InsR.NOKLengthH);
			ui.EditBOKLengthL			->setValue(BData->GetThresholdR(GetLayersBase())->InsR.BOKLengthL);
			ui.EditBOKLengthH			->setValue(BData->GetThresholdR(GetLayersBase())->InsR.BOKLengthH);
		}
		else if(GetLayerNumb(0)>=2 && LButtonList[1]->isChecked()==true){
			ui.EditNBrightWidthL		->setValue(BData->GetThresholdR(GetLayersBase())->InsG.NBrightWidthL);
			ui.EditNBrightWidthH		->setValue(BData->GetThresholdR(GetLayersBase())->InsG.NBrightWidthH);
			ui.EditNOKDotL				->setValue(BData->GetThresholdR(GetLayersBase())->InsG.NOKDotL);
			ui.EditNOKDotH				->setValue(BData->GetThresholdR(GetLayersBase())->InsG.NOKDotH);
			ui.EditBBrightWidthL		->setValue(BData->GetThresholdR(GetLayersBase())->InsG.BBrightWidthL);
			ui.EditBBrightWidthH		->setValue(BData->GetThresholdR(GetLayersBase())->InsG.BBrightWidthH);
			ui.EditBOKDotL				->setValue(BData->GetThresholdR(GetLayersBase())->InsG.BOKDotL);
			ui.EditBOKDotH				->setValue(BData->GetThresholdR(GetLayersBase())->InsG.BOKDotH);
			ui.EditAdjustBlack			->setValue(BData->GetThresholdR(GetLayersBase())->InsG.AdjustBlack);
			ui.EditAdjustWhite			->setValue(BData->GetThresholdR(GetLayersBase())->InsG.AdjustWhite);
			ui.EditNMinNGCountL			->setValue(BData->GetThresholdR(GetLayersBase())->InsG.NMinNGCountL);
			ui.EditNMinNGCountH			->setValue(BData->GetThresholdR(GetLayersBase())->InsG.NMinNGCountH);
			ui.EditBMinNGCountL			->setValue(BData->GetThresholdR(GetLayersBase())->InsG.BMinNGCountL);
			ui.EditBMinNGCountH			->setValue(BData->GetThresholdR(GetLayersBase())->InsG.BMinNGCountH);
			ui.EditNOKLengthL			->setValue(BData->GetThresholdR(GetLayersBase())->InsG.NOKLengthL);
			ui.EditNOKLengthH			->setValue(BData->GetThresholdR(GetLayersBase())->InsG.NOKLengthH);
			ui.EditBOKLengthL			->setValue(BData->GetThresholdR(GetLayersBase())->InsG.BOKLengthL);
			ui.EditBOKLengthH			->setValue(BData->GetThresholdR(GetLayersBase())->InsG.BOKLengthH);
		}
		else if(GetLayerNumb(0)>=3 && LButtonList[2]->isChecked()==true){
			ui.EditNBrightWidthL		->setValue(BData->GetThresholdR(GetLayersBase())->InsB.NBrightWidthL);
			ui.EditNBrightWidthH		->setValue(BData->GetThresholdR(GetLayersBase())->InsB.NBrightWidthH);
			ui.EditNOKDotL				->setValue(BData->GetThresholdR(GetLayersBase())->InsB.NOKDotL);
			ui.EditNOKDotH				->setValue(BData->GetThresholdR(GetLayersBase())->InsB.NOKDotH);
			ui.EditBBrightWidthL		->setValue(BData->GetThresholdR(GetLayersBase())->InsB.BBrightWidthL);
			ui.EditBBrightWidthH		->setValue(BData->GetThresholdR(GetLayersBase())->InsB.BBrightWidthH);
			ui.EditBOKDotL				->setValue(BData->GetThresholdR(GetLayersBase())->InsB.BOKDotL);
			ui.EditBOKDotH				->setValue(BData->GetThresholdR(GetLayersBase())->InsB.BOKDotH);
			ui.EditAdjustBlack			->setValue(BData->GetThresholdR(GetLayersBase())->InsB.AdjustBlack);
			ui.EditAdjustWhite			->setValue(BData->GetThresholdR(GetLayersBase())->InsB.AdjustWhite);
			ui.EditNMinNGCountL			->setValue(BData->GetThresholdR(GetLayersBase())->InsB.NMinNGCountL);
			ui.EditNMinNGCountH			->setValue(BData->GetThresholdR(GetLayersBase())->InsB.NMinNGCountH);
			ui.EditBMinNGCountL			->setValue(BData->GetThresholdR(GetLayersBase())->InsB.BMinNGCountL);
			ui.EditBMinNGCountH			->setValue(BData->GetThresholdR(GetLayersBase())->InsB.BMinNGCountH);
			ui.EditNOKLengthL			->setValue(BData->GetThresholdR(GetLayersBase())->InsB.NOKLengthL);
			ui.EditNOKLengthH			->setValue(BData->GetThresholdR(GetLayersBase())->InsB.NOKLengthH);
			ui.EditBOKLengthL			->setValue(BData->GetThresholdR(GetLayersBase())->InsB.BOKLengthL);
			ui.EditBOKLengthH			->setValue(BData->GetThresholdR(GetLayersBase())->InsB.BOKLengthH);
		}
		ui.checkBModeEnabled		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeEnabled);
		ui.checkBModeAbsoluteBright	->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeAbsoluteBright);
		ui.checkBModeNGCluster		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeNGCluster);
		ui.checkBModeDiffer			->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeDiffer);
		ui.checkBModeOnlyMatching	->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeOnlyMatching);
		ui.checkBModeWhiteMask		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeWhiteMask);
		ui.checkBModeBlackMask		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeBlackMask);
		ui.checkBModeCenterBrightFromParts	->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeCenterBrightFromParts);
		ui.checkBModeAdjustable		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeAdjustable);
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

void ColorHistogramForm::ShowThreshold(void)
{
	GraphThresh.DeleteXY();
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			return;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			continue;

		if(ui.checkBModeAbsoluteBright	->isChecked()==false){
			if(ui.tabWidgetInspect->currentIndex ()==0){
				if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
					GraphThresh.AddXY(AbsNBrightWidthRL-(BData->GetThresholdR(GetLayersBase())->InsR.NBrightWidthL-NBrightWidthRL)	,YMax);
					GraphThresh.AddXY(AbsNBrightWidthRH+(BData->GetThresholdR(GetLayersBase())->InsR.NBrightWidthH-NBrightWidthRH)	,YMax);
				}
				else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
					GraphThresh.AddXY(AbsNBrightWidthGL-(BData->GetThresholdR(GetLayersBase())->InsG.NBrightWidthL-NBrightWidthGL)	,YMax);
					GraphThresh.AddXY(AbsNBrightWidthGH+(BData->GetThresholdR(GetLayersBase())->InsG.NBrightWidthH-NBrightWidthGH)	,YMax);
				}
				else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
					GraphThresh.AddXY(AbsNBrightWidthBL-(BData->GetThresholdR(GetLayersBase())->InsB.NBrightWidthL-NBrightWidthBL)	,YMax);
					GraphThresh.AddXY(AbsNBrightWidthBH+(BData->GetThresholdR(GetLayersBase())->InsB.NBrightWidthH-NBrightWidthBH)	,YMax);
				}
			}
			else if(ui.tabWidgetInspect->currentIndex ()==1){
				if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
					GraphThresh.AddXY(AbsBBrightWidthRL-(BData->GetThresholdR(GetLayersBase())->InsR.BBrightWidthL-BBrightWidthRL)	,YMax);
					GraphThresh.AddXY(AbsBBrightWidthRH+(BData->GetThresholdR(GetLayersBase())->InsR.BBrightWidthH-BBrightWidthRH)	,YMax);
				}
				else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
					GraphThresh.AddXY(AbsBBrightWidthGL-(BData->GetThresholdR(GetLayersBase())->InsG.BBrightWidthL-BBrightWidthGL)	,YMax);
					GraphThresh.AddXY(AbsBBrightWidthGH+(BData->GetThresholdR(GetLayersBase())->InsG.BBrightWidthH-BBrightWidthGH)	,YMax);
				}
				else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
					GraphThresh.AddXY(AbsBBrightWidthBL-(BData->GetThresholdR(GetLayersBase())->InsB.BBrightWidthL-BBrightWidthBL)	,YMax);
					GraphThresh.AddXY(AbsBBrightWidthBH+(BData->GetThresholdR(GetLayersBase())->InsB.BBrightWidthH-BBrightWidthBH)	,YMax);
				}
			}
		}
		else{
			if(ui.tabWidgetInspect->currentIndex ()==0){
				if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsR.NBrightWidthL,YMax);
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsR.NBrightWidthH,YMax);
				}
				else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsG.NBrightWidthL,YMax);
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsG.NBrightWidthH,YMax);
				}
				else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsB.NBrightWidthL,YMax);
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsB.NBrightWidthH,YMax);
				}
			}
			else if(ui.tabWidgetInspect->currentIndex ()==1){
				if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsR.BBrightWidthL,YMax);
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsR.BBrightWidthH,YMax);
				}
				else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsG.BBrightWidthL,YMax);
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsG.BBrightWidthH,YMax);
				}
				else if(GetLayerNumb(Page)>=2 && LButtonList[2]->isChecked()==true){
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsB.BBrightWidthL,YMax);
					GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->InsB.BBrightWidthH,YMax);
				}
			}
		}
		return;
	}
}
void	ColorHistogramForm::GetDataFromWindow(void)
{
	if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
		GetDataFromWindowFromNo(0);
	}
	else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
		GetDataFromWindowFromNo(1);
	}
	else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
		GetDataFromWindowFromNo(2);
	}
}

void	ColorHistogramForm::GetDataFromWindowFromNo(int LayerNo)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			continue;

		ColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		if(GetLayerNumb(Page)>=1 && LayerNo==0){
			Thr->InsR.NBrightWidthL	=ui.EditNBrightWidthL	->value();
			Thr->InsR.NBrightWidthH	=ui.EditNBrightWidthH	->value();
			Thr->InsR.NOKDotL		=ui.EditNOKDotL			->value();
			Thr->InsR.NOKDotH		=ui.EditNOKDotH			->value();
			Thr->InsR.BBrightWidthL	=ui.EditBBrightWidthL	->value();
			Thr->InsR.BBrightWidthH	=ui.EditBBrightWidthH	->value();
			Thr->InsR.BOKDotL		=ui.EditBOKDotL			->value();
			Thr->InsR.BOKDotH		=ui.EditBOKDotH			->value();
			Thr->InsR.AdjustBlack	=ui.EditAdjustBlack		->value();
			Thr->InsR.AdjustWhite	=ui.EditAdjustWhite		->value();
			Thr->InsR.NMinNGCountL	=ui.EditNMinNGCountL	->value();
			Thr->InsR.NMinNGCountH	=ui.EditNMinNGCountH	->value();
			Thr->InsR.BMinNGCountL	=ui.EditBMinNGCountL	->value();
			Thr->InsR.BMinNGCountH	=ui.EditBMinNGCountH	->value();
			Thr->InsR.NOKLengthL	=ui.EditNOKLengthL		->value();
			Thr->InsR.NOKLengthH	=ui.EditNOKLengthH		->value();
			Thr->InsR.BOKLengthL	=ui.EditBOKLengthL		->value();
			Thr->InsR.BOKLengthH	=ui.EditBOKLengthH		->value();
		}
		else if(GetLayerNumb(Page)>=2 && LayerNo==1){
			Thr->InsG.NBrightWidthL	=ui.EditNBrightWidthL	->value();
			Thr->InsG.NBrightWidthH	=ui.EditNBrightWidthH	->value();
			Thr->InsG.NOKDotL		=ui.EditNOKDotL			->value();
			Thr->InsG.NOKDotH		=ui.EditNOKDotH			->value();
			Thr->InsG.BBrightWidthL	=ui.EditBBrightWidthL	->value();
			Thr->InsG.BBrightWidthH	=ui.EditBBrightWidthH	->value();
			Thr->InsG.BOKDotL		=ui.EditBOKDotL			->value();
			Thr->InsG.BOKDotH		=ui.EditBOKDotH			->value();
			Thr->InsG.AdjustBlack	=ui.EditAdjustBlack		->value();
			Thr->InsG.AdjustWhite	=ui.EditAdjustWhite		->value();
			Thr->InsG.NMinNGCountL	=ui.EditNMinNGCountL	->value();
			Thr->InsG.NMinNGCountH	=ui.EditNMinNGCountH	->value();
			Thr->InsG.BMinNGCountL	=ui.EditBMinNGCountL	->value();
			Thr->InsG.BMinNGCountH	=ui.EditBMinNGCountH	->value();
			Thr->InsG.NOKLengthL	=ui.EditNOKLengthL		->value();
			Thr->InsG.NOKLengthH	=ui.EditNOKLengthH		->value();
			Thr->InsG.BOKLengthL	=ui.EditBOKLengthL		->value();
			Thr->InsG.BOKLengthH	=ui.EditBOKLengthH		->value();
		}
		else if(GetLayerNumb(Page)>=3 && LayerNo==2){
			Thr->InsB.NBrightWidthL	=ui.EditNBrightWidthL	->value();
			Thr->InsB.NBrightWidthH	=ui.EditNBrightWidthH	->value();
			Thr->InsB.NOKDotL		=ui.EditNOKDotL			->value();
			Thr->InsB.NOKDotH		=ui.EditNOKDotH			->value();
			Thr->InsB.BBrightWidthL	=ui.EditBBrightWidthL	->value();
			Thr->InsB.BBrightWidthH	=ui.EditBBrightWidthH	->value();
			Thr->InsB.BOKDotL		=ui.EditBOKDotL			->value();
			Thr->InsB.BOKDotH		=ui.EditBOKDotH			->value();
			Thr->InsB.AdjustBlack	=ui.EditAdjustBlack		->value();
			Thr->InsB.AdjustWhite	=ui.EditAdjustWhite		->value();
			Thr->InsB.NMinNGCountL	=ui.EditNMinNGCountL	->value();
			Thr->InsB.NMinNGCountH	=ui.EditNMinNGCountH	->value();
			Thr->InsB.BMinNGCountL	=ui.EditBMinNGCountL	->value();
			Thr->InsB.BMinNGCountH	=ui.EditBMinNGCountH	->value();
			Thr->InsB.NOKLengthL	=ui.EditNOKLengthL		->value();
			Thr->InsB.NOKLengthH	=ui.EditNOKLengthH		->value();
			Thr->InsB.BOKLengthL	=ui.EditBOKLengthL		->value();
			Thr->InsB.BOKLengthH	=ui.EditBOKLengthH		->value();
		}
		Thr->PointMove.ModeEnabled			=ui.checkBModeEnabled			->isChecked();
		Thr->PointMove.ModeAbsoluteBright	=ui.checkBModeAbsoluteBright	->isChecked();
		Thr->PointMove.ModeNGCluster		=ui.checkBModeNGCluster			->isChecked();
		Thr->PointMove.ModeDiffer			=ui.checkBModeDiffer			->isChecked();
		Thr->PointMove.ModeOnlyMatching		=ui.checkBModeOnlyMatching		->isChecked();
		Thr->PointMove.ModeWhiteMask		=ui.checkBModeWhiteMask			->isChecked();
		Thr->PointMove.ModeBlackMask		=ui.checkBModeBlackMask			->isChecked();
		Thr->PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
		Thr->PointMove.ModeAdjustable		=ui.checkBModeAdjustable		->isChecked();
		Thr->PointMove.ModeCommonMovable	=ui.checkBModeCommonMovable	->isChecked();
		Thr->SelfSearch						=ui.EditSelfSearch		->value();
		Thr->CommonMoveDot					=ui.EditCommonMoveDot	->value();
		//return;
	}
}


void ColorHistogramForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE ColorBlock threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one ColorBlock threshold");
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

void ColorHistogramForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting All ColorBlocks\' threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all ColorBlock threshold");
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
/*
void ColorHistogramForm::TestedData()
{
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString("ANY"),QString("ANY"));
	GUICmdSendAlgorithmItemIndependentPack	Reply(IData->Base,QString("ANY"),QString("ANY"));
	Packet.Command=GetIndependentItemDataCommand_TestNow;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(page,0,Reply);
	}
}
*/

void	ColorHistogramForm::SlotLineGraphDClick(int X,int Y)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			continue;
					
		ColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		if(ui.checkBModeAbsoluteBright	->isChecked()==false){
			if(ui.tabWidgetInspect->currentIndex ()==0){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
						if(NBrightWidthRL+AbsNBrightWidthRL-X>=0){
							Thr->InsR.NBrightWidthL=NBrightWidthRL+AbsNBrightWidthRL-X;
							ui.EditNBrightWidthL->setValue(Thr->InsR.NBrightWidthL);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
						if(NBrightWidthGL+AbsNBrightWidthGL-X>=0){
							Thr->InsG.NBrightWidthL=NBrightWidthGL+AbsNBrightWidthGL-X;
							ui.EditNBrightWidthL->setValue(Thr->InsG.NBrightWidthL);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
						if(NBrightWidthBL+AbsNBrightWidthBL-X>=0){
							Thr->InsB.NBrightWidthL=NBrightWidthBL+AbsNBrightWidthBL-X;
							ui.EditNBrightWidthL->setValue(Thr->InsB.NBrightWidthL);
							ShowThreshold();
						}
					}
				}
				else{
					if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
						if(NBrightWidthRH+X-AbsNBrightWidthRH>=0){
							Thr->InsR.NBrightWidthH=NBrightWidthRH+X-AbsNBrightWidthRH;
							ui.EditNBrightWidthH->setValue(Thr->InsR.NBrightWidthH);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
						if(NBrightWidthGH+X-AbsNBrightWidthGH>=0){
							Thr->InsG.NBrightWidthH=NBrightWidthGH+X-AbsNBrightWidthGH;
							ui.EditNBrightWidthH->setValue(Thr->InsG.NBrightWidthH);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
						if(NBrightWidthBH+X-AbsNBrightWidthBH>=0){
							Thr->InsB.NBrightWidthH=NBrightWidthBH+X-AbsNBrightWidthBH;
							ui.EditNBrightWidthH->setValue(Thr->InsB.NBrightWidthH);
							ShowThreshold();
						}
					}
				}
			}
			else if(ui.tabWidgetInspect->currentIndex ()==1){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
						if(BBrightWidthRL+AbsBBrightWidthRL-X>=0){
							Thr->InsR.BBrightWidthL=BBrightWidthRL+AbsBBrightWidthRL-X;
							ui.EditBBrightWidthL->setValue(Thr->InsR.BBrightWidthL);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
						if(BBrightWidthGL+AbsBBrightWidthGL-X>=0){
							Thr->InsG.BBrightWidthL=BBrightWidthGL+AbsBBrightWidthGL-X;
							ui.EditBBrightWidthL->setValue(Thr->InsG.BBrightWidthL);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
						if(BBrightWidthBL+AbsBBrightWidthBL-X>=0){
							Thr->InsB.BBrightWidthL=BBrightWidthBL+AbsBBrightWidthBL-X;
							ui.EditBBrightWidthL->setValue(Thr->InsB.BBrightWidthL);
							ShowThreshold();
						}
					}
				}
				else{
					if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
						if(BBrightWidthRH+X-AbsBBrightWidthRH>=0){
							Thr->InsR.BBrightWidthH=BBrightWidthRH+X-AbsBBrightWidthRH;
							ui.EditBBrightWidthH->setValue(Thr->InsR.BBrightWidthH);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
						if(BBrightWidthGH+X-AbsBBrightWidthGH>=0){
							Thr->InsG.BBrightWidthH=BBrightWidthGH+X-AbsBBrightWidthGH;
							ui.EditBBrightWidthH->setValue(Thr->InsG.BBrightWidthH);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
						if(BBrightWidthBH+X-AbsBBrightWidthBH>=0){
							Thr->InsB.BBrightWidthH=BBrightWidthBH+X-AbsBBrightWidthBH;
							ui.EditBBrightWidthH->setValue(Thr->InsB.BBrightWidthH);
							ShowThreshold();
						}
					}
				}
			}
		}
		else{
			if(ui.tabWidgetInspect->currentIndex ()==0){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
						if(Thr->InsR.NBrightWidthH>=X){
							Thr->InsR.NBrightWidthL=X;
							ui.EditNBrightWidthL->setValue(Thr->InsR.NBrightWidthL);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
						if(Thr->InsG.NBrightWidthH>=X){
							Thr->InsG.NBrightWidthL=X;
							ui.EditNBrightWidthL->setValue(Thr->InsG.NBrightWidthL);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
						if(Thr->InsB.NBrightWidthH>=X){
							Thr->InsB.NBrightWidthL=X;
							ui.EditNBrightWidthL->setValue(Thr->InsB.NBrightWidthL);
							ShowThreshold();
						}
					}
				}
				else{
					if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
						if(Thr->InsR.NBrightWidthL<=X){
							Thr->InsR.NBrightWidthH=X;
							ui.EditNBrightWidthH->setValue(Thr->InsR.NBrightWidthH);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
						if(Thr->InsG.NBrightWidthL<=X){
							Thr->InsG.NBrightWidthH=X;
							ui.EditNBrightWidthH->setValue(Thr->InsG.NBrightWidthH);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
						if(Thr->InsB.NBrightWidthL<=X){
							Thr->InsB.NBrightWidthH=X;
							ui.EditNBrightWidthH->setValue(Thr->InsB.NBrightWidthH);
							ShowThreshold();
						}
					}
				}
			}
			else if(ui.tabWidgetInspect->currentIndex ()==1){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
						if(Thr->InsR.BBrightWidthH>=X){
							Thr->InsR.BBrightWidthL=X;
							ui.EditBBrightWidthL->setValue(Thr->InsR.BBrightWidthL);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
						if(Thr->InsG.BBrightWidthH>=X){
							Thr->InsG.BBrightWidthL=X;
							ui.EditBBrightWidthL->setValue(Thr->InsG.BBrightWidthL);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
						if(Thr->InsB.BBrightWidthH>=X){
							Thr->InsB.BBrightWidthL=X;
							ui.EditBBrightWidthL->setValue(Thr->InsB.BBrightWidthL);
							ShowThreshold();
						}
					}
				}
				else{
					if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
						if(Thr->InsR.BBrightWidthL<=X){
							Thr->InsR.BBrightWidthH=X;
							ui.EditBBrightWidthH->setValue(Thr->InsR.BBrightWidthH);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
						if(Thr->InsG.BBrightWidthL<=X){
							Thr->InsG.BBrightWidthH=X;
							ui.EditBBrightWidthH->setValue(Thr->InsG.BBrightWidthH);
							ShowThreshold();
						}
					}
					else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
						if(Thr->InsB.BBrightWidthL<=X){
							Thr->InsB.BBrightWidthH=X;
							ui.EditBBrightWidthH->setValue(Thr->InsB.BBrightWidthH);
							ShowThreshold();
						}
					}
				}
			}
		}
		LGraph.repaint();
		emit	SignalStartCalc();
		return;
	}
}


void ColorHistogramForm::on_tabWidgetInspect_currentChanged(int)
{
	ShowThreshold();
	LGraph.repaint();
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditNBrightWidthL_valueChanged(int X)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			return;
		ColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true)
			Thr->InsR.NBrightWidthL=X;
		else
		if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true)
			Thr->InsG.NBrightWidthL=X;
		else
		if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true)
			Thr->InsB.NBrightWidthL=X;
		ShowThreshold();
		LGraph.repaint();
		emit	SignalStartCalc();
		return;
	}
}

void ColorHistogramForm::on_EditNBrightWidthH_valueChanged(int X)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			return;
		ColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true)
			Thr->InsR.NBrightWidthH=X;
		else
		if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true)
			Thr->InsG.NBrightWidthH=X;
		else
		if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true)
			Thr->InsB.NBrightWidthH=X;
		ShowThreshold();
		LGraph.repaint();
		emit	SignalStartCalc();
		return;
	}
}

void ColorHistogramForm::on_EditBBrightWidthL_valueChanged(int X)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			return;
		ColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true)
			Thr->InsR.BBrightWidthL=X;
		else
		if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true)
			Thr->InsG.BBrightWidthL=X;
		else
		if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true)
			Thr->InsB.BBrightWidthL=X;
		ShowThreshold();
		LGraph.repaint();
		emit	SignalStartCalc();
		return;
	}
}

void ColorHistogramForm::on_EditBBrightWidthH_valueChanged(int X)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			return;
		ColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true)
			Thr->InsR.BBrightWidthH=X;
		else
		if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true)
			Thr->InsG.BBrightWidthH=X;
		else
		if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true)
			Thr->InsB.BBrightWidthH=X;
		ShowThreshold();
		LGraph.repaint();
		emit	SignalStartCalc();
		return;
	}
}

void	ColorHistogramForm::SlotLayerClicked()
{
	if(LastLayer>=0)
		GetDataFromWindowFromNo(LastLayer);
	CreateThreshld();

	if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
		LastLayer=0;
	}
	else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
		LastLayer=1;
	}
	else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
		LastLayer=2;
	}
	ShowLibrary();
}


void ColorHistogramForm::on_ButtonCalc_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*nBData=dynamic_cast<ColorBlockItem *>(DA);
		if(nBData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,BlockReqTryThresholdCommand ,BlockSendTryThresholdCommand);
		ColorBlockItem	*BData=&((ColorBlockReqTryThreshold *)PacketReq.Data)->Threshold;
		((ColorBlockReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((ColorBlockReqTryThreshold *)PacketReq.Data)->BlockItemID	=DA->GetID();

		ColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->InsR=((ColorBlockThreshold *)nBData->GetThresholdR(GetLayersBase()))->InsR;
		Thr->InsG=((ColorBlockThreshold *)nBData->GetThresholdR(GetLayersBase()))->InsG;
		Thr->InsB=((ColorBlockThreshold *)nBData->GetThresholdR(GetLayersBase()))->InsB;

		Thr->PointMove.ModeEnabled			=ui.checkBModeEnabled			->isChecked();
		Thr->PointMove.ModeAbsoluteBright	=ui.checkBModeAbsoluteBright	->isChecked();
		Thr->PointMove.ModeNGCluster		=ui.checkBModeNGCluster			->isChecked();
		Thr->PointMove.ModeDiffer			=ui.checkBModeDiffer			->isChecked();
		Thr->PointMove.ModeOnlyMatching		=ui.checkBModeOnlyMatching		->isChecked();
		Thr->PointMove.ModeWhiteMask		=ui.checkBModeWhiteMask			->isChecked();
		Thr->PointMove.ModeBlackMask		=ui.checkBModeBlackMask			->isChecked();
		Thr->PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
		Thr->PointMove.ModeAdjustable		=ui.checkBModeAdjustable		->isChecked();
		Thr->PointMove.ModeCommonMovable	=ui.checkBModeCommonMovable	->isChecked();
		Thr->SelfSearch						=ui.EditSelfSearch		->value();
		Thr->CommonMoveDot					=ui.EditCommonMoveDot	->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			ColorBlockSendTryThreshold	*R=((ColorBlockSendTryThreshold *)PacketSend.Data);
			ui.labelResultNDark	->setText(QString::number(R->NGDotInNDark	));
			ui.labelResultNLight->setText(QString::number(R->NGDotInNBright	));
			ui.labelResultBDark	->setText(QString::number(R->NGDotInBDark	));
			ui.labelResultBLight->setText(QString::number(R->NGDotInBBright	));

			SimPanel.SetResult(R->Result);
			break;
		}
	}	
}


void ColorHistogramForm::on_ButtonRelrectSaveParts_clicked()
{
	GetDataFromWindow();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
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
			QMessageBox::warning (NULL, LangSolver.GetString(ColorHistogramForm_LS,LID_50)/*"Error"*/, LangSolver.GetString(ColorHistogramForm_LS,LID_51)/*"Error occurs in saving algorithm data of parts"*/ );
		while(Ack.IsReceived()==false);
		if(Ack.Ret==false){
			QMessageBox::warning (NULL, LangSolver.GetString(ColorHistogramForm_LS,LID_52)/*"Error"*/, LangSolver.GetString(ColorHistogramForm_LS,LID_53)/*"Error occurs in saving algorithm data of parts"*/ );
		}
	}
}

void ColorHistogramForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			ColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			Container->Update(DestLib);
			return;
		}
	}
}

void ColorHistogramForm::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			ColorBlockLibrary	*ALib=dynamic_cast<ColorBlockLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			ColorBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			return;
		}
	}
}

void ColorHistogramForm::on_pushButtonChangeLib_clicked()
{
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
			ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
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
void ColorHistogramForm::on_toolButtonSimShowBlock_clicked()
{
	SimPanel.SetModeShowBlock		(ui.toolButtonSimShowBlock ->isChecked());
	SimPanel.repaint();
}

void ColorHistogramForm::on_toolButtonSimShowBright_clicked()
{
	SimPanel.SetModeShowBrightnessNG(ui.toolButtonSimShowBright->isChecked());
	SimPanel.repaint();
}

void ColorHistogramForm::on_pushButtonSimShowCenterPos_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			ColorBlockItem	*BData=dynamic_cast<ColorBlockItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.repaint();
			}
		}
	}
}
void	ColorHistogramForm::SlotStartCalc()
{
	SimPanel.SetModeShowBlock		(ui.toolButtonSimShowBlock ->isChecked());
	SimPanel.SetModeShowBrightnessNG(ui.toolButtonSimShowBright->isChecked());
	on_ButtonCalc_clicked();
	SimPanel.repaint();
}
void ColorHistogramForm::on_EditNOKDotL_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditNOKDotH_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditNOKLengthL_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditNOKLengthH_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditBOKDotL_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditBOKDotH_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditBOKLengthL_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditBOKLengthH_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_checkBModeWhiteMask_clicked(bool checked)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_checkBModeBlackMask_clicked(bool checked)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_checkBModeAdjustable_clicked(bool checked)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditAdjustBlack_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditAdjustWhite_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditSelfSearch_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_checkBModeCommonMovable_clicked(bool checked)
{
	emit	SignalStartCalc();
}

void ColorHistogramForm::on_EditCommonMoveDot_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}
