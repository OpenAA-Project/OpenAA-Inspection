/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\HistogramForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include<QMessageBox>
#include "BlockFormResource.h"
#include "HistogramForm.h"
#include "XBlockInspection.h"
#include "XBlockLibrary.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "swap.h"
#include "XBlockManualExecuter.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

HistogramForm::HistogramForm(LayersBase *Base,QWidget *parent)
	: AlgorithmComponentWindow(parent)
	,ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
	,SimPanel(Base,parent)
	,LGraph(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	OnChanging	=false;
	InstBase	=NULL;
	LButtonList	=NULL;
	Page		=-1;

	SimPanel.setParent(ui.frame_SimImage);
	SimPanel.SetAlgo(/**/"Basic",/**/"BlockInspection");
	SimPanel.SetGUI(/**/"Button",/**/"PropertyBlockForm");
	SimPanel.setGeometry(0,0,ui.frame_SimImage->width(),ui.frame_SimImage->height());
	connect(this,SIGNAL(SignalStartCalc()),this,SLOT(SlotStartCalc()),Qt::QueuedConnection);

	LGraph.setParent(ui.frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.move(0,0);
	LGraph.resize(ui.frameLineGraph->width(),ui.frameLineGraph->height());
	LayerBar.setParent(ui.frameLayer);
	LayerBar.move(0,0);
	LayerBar.resize(ui.frameLayer->width(),ui.frameLayer->height());

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

	ui.labelResultNDark		->setText(/**/"");
	ui.labelResultNLight	->setText(/**/"");
	ui.labelResultBDark		->setText(/**/"");
	ui.labelResultBLight	->setText(/**/"");
	ui.labelResultNDarkUnit	->setText(/**/"");
	ui.labelResultNLightUnit->setText(/**/"");
	ui.labelResultBDarkUnit	->setText(/**/"");
	ui.labelResultBLightUnit->setText(/**/"");

	RegisterComponent((int)ID_ModeBindBWBroad,ui.checkBModeBindBWBroad);
	RegisterComponent((int)ID_BBrightWidthL	,ui.EditBBrightWidthL);
	RegisterComponent((int)ID_BBrightWidthH	,ui.EditBBrightWidthH);
	RegisterComponent((int)ID_BOKDotL		,ui.EditBOKDotL		);
	RegisterComponent((int)ID_BOKDotH		,ui.EditBOKDotH		);
	RegisterComponent((int)ID_BOKLengthL	,ui.EditBOKLengthL  );
	RegisterComponent((int)ID_BOKLengthH	,ui.EditBOKLengthH  );
	RegisterComponent((int)ID_BMaxNGDotL	,ui.EditBMaxNGDotL  );
	RegisterComponent((int)ID_BMaxNGDotH	,ui.EditBMaxNGDotH  );
	RegisterComponent((int)ID_BMinNGCountL	,ui.EditBMinNGCountL);
	RegisterComponent((int)ID_BMinNGCountH	,ui.EditBMinNGCountH);
	RegisterComponent((int)ID_BConnectLen	,ui.EditBConnectLen );

	RegisterComponent((int)ID_ModeBindBWNarrow,ui.checkBModeBindBWNarrow);
	RegisterComponent((int)ID_NBrightWidthL	,ui.EditNBrightWidthL);
	RegisterComponent((int)ID_NBrightWidthH	,ui.EditNBrightWidthH);
	RegisterComponent((int)ID_NOKDotL		,ui.EditNOKDotL		);
	RegisterComponent((int)ID_NOKDotH		,ui.EditNOKDotH		);
	RegisterComponent((int)ID_NOKLengthL	,ui.EditNOKLengthL  );
	RegisterComponent((int)ID_NOKLengthH	,ui.EditNOKLengthH  );
	RegisterComponent((int)ID_NMaxNGDotL	,ui.EditNMaxNGDotL  );
	RegisterComponent((int)ID_NMaxNGDotH	,ui.EditNMaxNGDotH  );
	RegisterComponent((int)ID_NMinNGCountL	,ui.EditNMinNGCountL);
	RegisterComponent((int)ID_NMinNGCountH	,ui.EditNMinNGCountH);
	RegisterComponent((int)ID_NConnectLen	,ui.EditNConnectLen );

	RegisterComponent((int)ID_ModeEnabled			,ui.checkBModeEnabled					);
	RegisterComponent((int)ID_ModeAbsoluteBright	,ui.checkBModeAbsoluteBright			);
	RegisterComponent((int)ID_ModeNGCluster			,ui.checkBModeNGCluster					);
	RegisterComponent((int)ID_ModeDiffer			,ui.checkBModeDiffer					);
	RegisterComponent((int)ID_ModePermitInverted	,ui.checkBPermitInverted				);
	RegisterComponent((int)ID_ModeAdoptBiggest		,ui.checkBModeAdoptBiggest				);
	RegisterComponent((int)ID_ModeOnlyMatching		,ui.checkBModeOnlyMatching				);
	RegisterComponent((int)ID_ModeWhiteMask			,ui.checkBModeWhiteMask					);
	RegisterComponent((int)ID_ModeBlackMask			,ui.checkBModeBlackMask					);
	RegisterComponent((int)ID_ModeCenterBrightFromParts	,ui.checkBModeCenterBrightFromParts	);
	RegisterComponent((int)ID_ModeInvertLogic		,ui.checkBModeInvertLogic				);
	RegisterComponent((int)ID_ModeOppositeRange		,ui.checkBModeOppositeRange				);
	RegisterComponent((int)ID_ModeSearchDetail		,ui.checkBModeSearchDetail				);
	RegisterComponent((int)ID_ModeDynamicMask		,ui.checkBModeDynamicMask				);
	RegisterComponent((int)ID_ModeUseMasterImage	,ui.checkBModeUseMasterImage			);
	RegisterComponent((int)ID_ModeCalcBothBN		,ui.checkModeCalcBothBN					);

	RegisterComponent((int)ID_SpaceToOutline		,ui.comboBoxMatchPosition	);
	RegisterComponent((int)ID_ModeUseGlobalLine		,ui.checkBModeUseGlobalLine	);
	RegisterComponent((int)ID_ExpandForGenMask		,ui.EditExpandForGenMask	);

	RegisterComponent((int)ID_ModeAdjustable		,ui.checkBModeAdjustable	);
	RegisterComponent((int)ID_AdjustBlack			,ui.EditAdjustBlack			);
	RegisterComponent((int)ID_AdjustWhite			,ui.EditAdjustWhite			);

	RegisterComponent((int)ID_ModeCommonMovable		,ui.checkBModeCommonMovable	);
	RegisterComponent((int)ID_SelfSearch			,ui.EditSelfSearch			);
	RegisterComponent((int)ID_CommonMoveDot			,ui.EditCommonMoveDot		);
	RegisterComponent((int)ID_FollowLineLayer		,ui.EditFollowLineLayer		);

	RegisterComponent((int)ID_DiffBrightWidthL		,ui.EditDiffBrightWidthL	);
	RegisterComponent((int)ID_DiffBrightWidthH		,ui.EditDiffBrightWidthH	);

	RegisterComponent((int)ID_ModeUseRegularBrightness	,ui.checkBoxUseRegularBrightness	);
	RegisterComponent((int)ID_RegularCenterBright	,ui.EditCenterBrightMaster	);

	SetupPassword();

	InstallOperationLog(this);
}

HistogramForm::~HistogramForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	if(LButtonList!=NULL){
		delete	[]LButtonList;
		LButtonList=NULL;
	}
}

void	HistogramForm::GetActiveLayerList(IntList &LayerList)
{
	if(0<=Page && LButtonList!=NULL){
		for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
			if(LButtonList[Layer]->isChecked()==true){
				LayerList.Add(Layer);
			}
		}
	}
}
void	HistogramForm::Initial(AlgorithmBase *_InstBase ,AlgorithmItemIndependentPack &Data)
{
	InstBase	=_InstBase;
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	ui.pushButtonRestore->setEnabled(false);

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		SimPanel.SetLayer(D->Layer);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
			if(BData!=NULL){
				Page=D->GlobalPage;
				if(LButtonList!=NULL){
					delete	[]LButtonList;
					LButtonList=NULL;
				}
				LButtonList=new QToolButton*[GetLayerNumb(Page)];
				LastLayer=0;
				for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
					LButtonList[Layer]=new QToolButton();
					LButtonList[Layer]->setText(LangSolver.GetString(HistogramForm_LS,LID_1)/*"Ly"*/+QString::number(Layer));
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
				LButtonList[D->Layer]->setChecked(true);


				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock		(ui.toolButtonSimShowBlock ->isChecked());
				SimPanel.SetModeShowBrightnessNG(ui.toolButtonSimShowBright->isChecked());

				OldLibID		=DA->GetLibID();
				OldCenterBright	=BData->GetThresholdR(GetLayersBase())->ThreshouldBag.RegularCenterBright;
				OldNBrightWidthL=BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NBrightWidthL;		
				OldNBrightWidthH=BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NBrightWidthH;		
				OldBBrightWidthL=BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BBrightWidthL;		
				OldBBrightWidthH=BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BBrightWidthH;	

				NewLibID		=OldLibID			;
				NewCenterBright	=OldCenterBright	;
				NewNBrightWidthL=OldNBrightWidthL	;
				NewNBrightWidthH=OldNBrightWidthH	;
				NewBBrightWidthL=OldBBrightWidthL	;
				NewBBrightWidthH=OldBBrightWidthH	;

				int	LibID=BData->GetLibID();
				AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
				AlgorithmLibraryLevelContainer	LLib(Container);
				if(BData->GetLibraryContainer()->GetLibrary(LibID ,LLib)==true){
					BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(LLib.GetLibrary());
					if(ALib->GetSourceID()>0){
						ui.pushButtonRestore->setEnabled(true);
					}
				}
			}
		}
	}
	SetEnableChangeMode(false);

	CreateThreshld();
	ShowHistgramList();

	ui.doubleSpinBoxBOKDotL		->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui.doubleSpinBoxBOKDotH		->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui.doubleSpinBoxBOKLengthL	->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui.doubleSpinBoxBOKLengthH	->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui.doubleSpinBoxBMaxNGDotL	->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui.doubleSpinBoxBMaxNGDotH	->setDecimals(GetParamGlobal()->SmallNumberFigure);

	ui.doubleSpinBoxNOKDotL		->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui.doubleSpinBoxNOKDotH		->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui.doubleSpinBoxNOKLengthL	->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui.doubleSpinBoxNOKLengthH	->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui.doubleSpinBoxNMaxNGDotL	->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui.doubleSpinBoxNMaxNGDotH	->setDecimals(GetParamGlobal()->SmallNumberFigure);

	ui.labelUnitName	->setText(GetParamGlobal()->UnitSquareName);
	ui.labelUnitName_2	->setText(GetParamGlobal()->UnitName);
	ui.labelUnitName_3	->setText(GetParamGlobal()->UnitSquareName);
	ui.labelUnitName_4	->setText(GetParamGlobal()->UnitSquareName);
	ui.labelUnitName_5	->setText(GetParamGlobal()->UnitName);
	ui.labelUnitName_6	->setText(GetParamGlobal()->UnitSquareName);
	ui.labelUnitName_7	->setText(GetParamGlobal()->UnitName);
	ui.labelUnitName_8	->setText(GetParamGlobal()->UnitName);
	ui.labelUnitName_9	->setText(GetParamGlobal()->UnitSquareName);
	ui.labelUnitName_10	->setText(GetParamGlobal()->UnitSquareName);

	SetColoriseByManual();

	SetEnableChangeMode(true);
}

void	HistogramForm::ShowHistgramList(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	ui.listWidgetHistList->clear();
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			continue;
		
		BData->TF_EnumHistList(HContainer);
		for(HistgramTypeListInAlgo *a=HContainer.GetFirst();a!=NULL;a=a->GetNext()){
			ui.listWidgetHistList->addItem(a->HistName);
		}
		return;
	}
}

void	HistogramForm::CreateThreshld(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,BlockReqThresholdReqCommand ,BlockReqThresholdSendCommand);
		((BlockThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((BlockThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((BlockThresholdReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((BlockThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			BlockThresholdSend	*ThrePoint=(BlockThresholdSend *)PacketSend.GetData();
			CenterBright		=ThrePoint->CenterBright;
			NBrightWidthL		=ThrePoint->NBrightWidthL;		
			NBrightWidthH		=ThrePoint->NBrightWidthH;		
			BBrightWidthL		=ThrePoint->BBrightWidthL;		
			BBrightWidthH		=ThrePoint->BBrightWidthH;		
			AbsNBrightWidthL	=ThrePoint->AbsNBrightWidthL;	
			AbsNBrightWidthH	=ThrePoint->AbsNBrightWidthH;	
			AbsBBrightWidthL	=ThrePoint->AbsBBrightWidthL;	
			AbsBBrightWidthH	=ThrePoint->AbsBBrightWidthH;	

			NMinNGCountL		=ThrePoint->NMinNGCountL;
			NMinNGCountH		=ThrePoint->NMinNGCountH;
			BMinNGCountL		=ThrePoint->BMinNGCountL;
			BMinNGCountH		=ThrePoint->BMinNGCountH;
			NConnectLen			=ThrePoint->NConnectLen;
			BConnectLen			=ThrePoint->BConnectLen;
		}
		break;
	}
	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
	LGraph.repaint();
}

void HistogramForm::GetHistogramData(void)
{
	GraphColMaster.DeleteXY();
	GraphColTarget.DeleteXY();
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,BlockHistogramListReqCommand ,BlockHistogramListSendCommand);
		((BlockHistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((BlockHistogramListReq *)PacketReq.Data)->Layer=D->Layer;
		((BlockHistogramListReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((BlockHistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			BlockHistogramListSend	*L=(BlockHistogramListSend *)PacketSend.GetData();
			YMax=0;
			for(int i=0;i<256;i++){
				YMax=max(YMax,L->ListMaster[i]);
				YMax=max(YMax,L->ListTarget[i]);
				GraphColMaster.AddXY(i		,L->ListMaster[i]);
				GraphColTarget.AddXY(i+0.5	,L->ListTarget[i]);
			}
			if(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeUseRegularBrightness==true){
				ui.EditCenterBrightMaster	->setText(QString::number(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.RegularCenterBright));
			}
			else{
				ui.EditCenterBrightMaster	->setText(QString::number(L->CenterBright));
			}
			ui.EditCenterBrightTarget	->setText(QString::number(L->CenterTargetBright));

			::SetDataToTable(ui.tableWidgetShift ,0 ,0 ,QString::number(L->ShiftByAlignmentX));
			::SetDataToTable(ui.tableWidgetShift ,1 ,0 ,QString::number(L->ShiftByAlignmentY));
			::SetDataToTable(ui.tableWidgetShift ,0 ,1 ,QString::number(L->ShiftByCommonX));
			::SetDataToTable(ui.tableWidgetShift ,1 ,1 ,QString::number(L->ShiftByCommonY));
			::SetDataToTable(ui.tableWidgetShift ,0 ,2 ,QString::number(L->ShiftBySelfX));
			::SetDataToTable(ui.tableWidgetShift ,1 ,2 ,QString::number(L->ShiftBySelfY));
			return;
		}
	}
}

void HistogramForm::on_ButtonClose_clicked()
{
	close();
}

void	HistogramForm::ShowLibrary(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
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
		OnChanging=true;

		ui.EditItemName				->setText(BData->GetItemName());

		ui.EditNBrightWidthL			->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NBrightWidthL);
		ui.EditNBrightWidthH			->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NBrightWidthH);
		ui.EditNOKDotL					->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NOKDotL);
		ui.EditNOKDotH					->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NOKDotH);
		ui.EditNMaxNGDotL				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NMaxNGDotL);
		ui.EditNMaxNGDotH				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NMaxNGDotH);
		ui.EditNOKLengthL				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NOKLengthL);
		ui.EditNOKLengthH				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NOKLengthH);
		ui.EditBBrightWidthL			->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BBrightWidthL);
		ui.EditBBrightWidthH			->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BBrightWidthH);
		ui.EditBOKDotL					->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BOKDotL);
		ui.EditBOKDotH					->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BOKDotH);
		ui.EditBMaxNGDotL				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BMaxNGDotL);
		ui.EditBMaxNGDotH				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BMaxNGDotH);
		ui.EditBOKLengthL				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BOKLengthL);
		ui.EditBOKLengthH				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BOKLengthH);
		ui.EditDiffBrightWidthL			->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.DiffBrightWidthL);
		ui.EditDiffBrightWidthH			->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.DiffBrightWidthH);
		ui.EditNMinNGCountL				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NMinNGCountL);
		ui.EditNMinNGCountH				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NMinNGCountH);
		ui.EditBMinNGCountL				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BMinNGCountL);
		ui.EditBMinNGCountH				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BMinNGCountH);
		ui.EditNConnectLen				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NConnectLen);
		ui.EditBConnectLen				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BConnectLen);
		ui.checkBModeEnabled			->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeEnabled);
		ui.checkBModeAbsoluteBright		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeAbsoluteBright);
		ui.checkBModeNGCluster			->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeNGCluster);
		ui.checkBModeDiffer				->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeDiffer);
		ui.checkModeCalcBothBN			->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeCalcBothBN);
		//ui.checkBMatchPosition			->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeMatchPosition);
		if(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeMatchPosition==false
		&& BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeMatchPositionBW==false)
			ui.comboBoxMatchPosition	->setCurrentIndex(0);
		else
		if(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeMatchPosition==true
		&& BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeMatchPositionBW==false)
			ui.comboBoxMatchPosition	->setCurrentIndex(1);
		else
		if(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeMatchPosition==false
		&& BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeMatchPositionBW==true)
			ui.comboBoxMatchPosition	->setCurrentIndex(2);
		else
		if(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeMatchPosition==true
		&& BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeMatchPositionBW==true)
			ui.comboBoxMatchPosition	->setCurrentIndex(3);

		ui.checkBModeSearchDetail		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeSearchDetail);
		ui.checkBModeDynamicMask		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeDynamicMask);
		ui.checkBModeBindBWBroad		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeBindBWBroad);
		ui.checkBModeBindBWNarrow		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeBindBWNarrow);
		ui.checkBModeAdoptBiggest		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeAdoptBiggest);
		ui.checkBModeUseMasterImage		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeUseMasterImage);
		ui.checkBoxUseRegularBrightness	->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeUseRegularBrightness);
		ui.EditCenterBrightMaster->setText(QString::number(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.RegularCenterBright));
		on_checkBoxUseRegularBrightness_clicked();

		ui.checkBModeOnlyMatching		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeOnlyMatching);
		ui.checkBModeWhiteMask			->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeWhiteMask);
		ui.checkBModeBlackMask			->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeBlackMask);
		ui.checkBModeCenterBrightFromParts	->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeCenterBrightFromParts);
		ui.checkBModeAdjustable			->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeAdjustable);
		ui.checkBModeInvertLogic		->setChecked(BData->GetInvertLogic());
		ui.EditAdjustBlack				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.AdjustBlack);
		ui.EditAdjustWhite				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.AdjustWhite);
		ui.checkBModeCommonMovable		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeCommonMovable);
		ui.EditSelfSearch				->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.SelfSearch);
		ui.EditCommonMoveDot			->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.CommonMoveDot);
		ui.EditFollowLineLayer			->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.FollowLineLayer);
		ui.checkBPermitInverted			->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModePermitInverted);
		ui.checkBModeOppositeRange		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeOppositeRange);
		ui.checkBModeUseGlobalLine		->setChecked(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeUseGlobalLine);
		ui.EditExpandForGenMask			->setValue(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.ExpandForGenMask);
		if(BData->IsOriginParts()==true){
			ui.stackedWidgetParts->setCurrentIndex(1);
		}
		else{
			ui.stackedWidgetParts->setCurrentIndex(0);
		}
		OnChanging=false;

		ShowThreshold();
		LGraph.repaint();
		emit	SignalStartCalc();
		return;
	}
}

void	HistogramForm::SetColoriseByManual(void)
{
	int	LibID=ui.EditLibID->text().toInt();
	AlgorithmBase	*ABase=IData->Base->GetAlgorithmBase(sRoot,sName);
	QPalette	P=ui.EditBBrightWidthL->palette();
	P.setColor(QPalette::Base,(ABase->GetManualExecuter().IsExist(1,LibID)==true)?Qt::green:Qt::white);
	ui.EditBBrightWidthL	->setPalette(P);
	P.setColor(QPalette::Base,(ABase->GetManualExecuter().IsExist(2,LibID)==true)?Qt::green:Qt::white);
	ui.EditBBrightWidthH	->setPalette(P);
	P.setColor(QPalette::Base,(ABase->GetManualExecuter().IsExist(3,LibID)==true)?Qt::green:Qt::white);
	ui.EditNBrightWidthH	->setPalette(P);
	P.setColor(QPalette::Base,(ABase->GetManualExecuter().IsExist(4,LibID)==true)?Qt::green:Qt::white);
	ui.EditNBrightWidthH	->setPalette(P);
}

void HistogramForm::ShowThreshold(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GraphThresh.DeleteXY();
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			return;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			continue;

		if(ui.checkBModeAbsoluteBright	->isChecked()==false){
			if(ui.tabWidgetInspect->currentIndex ()==1){
				GraphThresh.AddXY(AbsNBrightWidthL-(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NBrightWidthL-NBrightWidthL)	,YMax);
				GraphThresh.AddXY(AbsNBrightWidthH+(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NBrightWidthH-NBrightWidthH)	,YMax);
			}
			else if(ui.tabWidgetInspect->currentIndex ()==0){
				GraphThresh.AddXY(AbsBBrightWidthL-(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BBrightWidthL-BBrightWidthL)	,YMax);
				GraphThresh.AddXY(AbsBBrightWidthH+(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BBrightWidthH-BBrightWidthH)	,YMax);
			}
		}
		else{
			if(ui.tabWidgetInspect->currentIndex ()==1){
				GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NBrightWidthL,YMax);
				GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.NBrightWidthH,YMax);
			}
			else if(ui.tabWidgetInspect->currentIndex ()==0){
				GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BBrightWidthL,YMax);
				GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->ThreshouldBag.BBrightWidthH,YMax);
			}
		}
		return;
	}
}
void	HistogramForm::GetDataFromWindow(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GetDataFromWindowFromNo(LayerList.GetFirst()->GetValue());
}
void	HistogramForm::GetDataFromWindowFromNo(int LayerNo)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerNo!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			continue;

		BData->SetItemName(ui.EditItemName	->text());
		BlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->ThreshouldBag.NBrightWidthL			=ui.EditNBrightWidthL	->value();
		Thr->ThreshouldBag.NBrightWidthH			=ui.EditNBrightWidthH	->value();
		Thr->ThreshouldBag.NOKDotL					=ui.EditNOKDotL			->value();
		Thr->ThreshouldBag.NOKDotH					=ui.EditNOKDotH			->value();
		Thr->ThreshouldBag.NMaxNGDotL				=ui.EditNMaxNGDotL		->value();
		Thr->ThreshouldBag.NMaxNGDotH				=ui.EditNMaxNGDotH		->value();
		Thr->ThreshouldBag.NOKLengthL				=ui.EditNOKLengthL		->value();
		Thr->ThreshouldBag.NOKLengthH				=ui.EditNOKLengthH		->value();
		Thr->ThreshouldBag.BBrightWidthL			=ui.EditBBrightWidthL	->value();
		Thr->ThreshouldBag.BBrightWidthH			=ui.EditBBrightWidthH	->value();
		Thr->ThreshouldBag.BOKDotL					=ui.EditBOKDotL			->value();
		Thr->ThreshouldBag.BOKDotH					=ui.EditBOKDotH			->value();
		Thr->ThreshouldBag.BMaxNGDotL				=ui.EditBMaxNGDotL		->value();
		Thr->ThreshouldBag.BMaxNGDotH				=ui.EditBMaxNGDotH		->value();
		Thr->ThreshouldBag.BOKLengthL				=ui.EditBOKLengthL		->value();
		Thr->ThreshouldBag.BOKLengthH				=ui.EditBOKLengthH		->value();
		Thr->ThreshouldBag.DiffBrightWidthL			=ui.EditDiffBrightWidthL->value();
		Thr->ThreshouldBag.DiffBrightWidthH			=ui.EditDiffBrightWidthH->value();
		Thr->ThreshouldBag.NMinNGCountL				=ui.EditNMinNGCountL	->value();
		Thr->ThreshouldBag.NMinNGCountH				=ui.EditNMinNGCountH	->value();
		Thr->ThreshouldBag.BMinNGCountL				=ui.EditBMinNGCountL	->value();
		Thr->ThreshouldBag.BMinNGCountH				=ui.EditBMinNGCountH	->value();
		Thr->ThreshouldBag.NConnectLen				=ui.EditNConnectLen		->value();
		Thr->ThreshouldBag.BConnectLen				=ui.EditBConnectLen		->value();

		Thr->ThreshouldBag.PointMove.ModeEnabled		=ui.checkBModeEnabled			->isChecked();
		Thr->ThreshouldBag.PointMove.ModeAbsoluteBright	=ui.checkBModeAbsoluteBright	->isChecked();
		Thr->ThreshouldBag.PointMove.ModeNGCluster		=ui.checkBModeNGCluster			->isChecked();
		//Thr->ThreshouldBag.PointMove.ModeMatchPosition		=ui.checkBMatchPosition			->isChecked();
		if(ui.comboBoxMatchPosition	->currentIndex()==0){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=false;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=false;
		}
		else
		if(ui.comboBoxMatchPosition	->currentIndex()==1){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=true;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=false;
		}
		else
		if(ui.comboBoxMatchPosition	->currentIndex()==2){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=false;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=true;
		}
		else
		if(ui.comboBoxMatchPosition	->currentIndex()==3){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=true;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=true;
		}
		Thr->ThreshouldBag.PointMove.ModeSearchDetail		=ui.checkBModeSearchDetail		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeDynamicMask		=ui.checkBModeDynamicMask		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeBindBWBroad		=ui.checkBModeBindBWBroad		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeBindBWNarrow		=ui.checkBModeBindBWNarrow		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeAdoptBiggest		=ui.checkBModeAdoptBiggest		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeUseMasterImage		=ui.checkBModeUseMasterImage	->isChecked();
		Thr->ThreshouldBag.PointMove.ModeUseRegularBrightness=ui.checkBoxUseRegularBrightness->isChecked();
		if(ui.checkBoxUseRegularBrightness->isChecked()==true){
			Thr->ThreshouldBag.RegularCenterBright=ui.EditCenterBrightMaster->text().toInt();
			BData->CenterBright	=ui.EditCenterBrightMaster->text().toInt();
		}

		Thr->ThreshouldBag.PointMove.ModeDiffer			=ui.checkBModeDiffer			->isChecked();
		Thr->ThreshouldBag.PointMove.ModeOnlyMatching	=ui.checkBModeOnlyMatching		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeWhiteMask		=ui.checkBModeWhiteMask			->isChecked();
		Thr->ThreshouldBag.PointMove.ModeBlackMask		=ui.checkBModeBlackMask			->isChecked();
		Thr->ThreshouldBag.PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
		Thr->ThreshouldBag.PointMove.ModeAdjustable		=ui.checkBModeAdjustable		->isChecked();
		Thr->ThreshouldBag.AdjustBlack					=ui.EditAdjustBlack			->value();
		Thr->ThreshouldBag.AdjustWhite					=ui.EditAdjustWhite			->value();
		Thr->ThreshouldBag.PointMove.ModeCommonMovable	=ui.checkBModeCommonMovable	->isChecked();
		Thr->ThreshouldBag.SelfSearch					=ui.EditSelfSearch			->value();
		Thr->ThreshouldBag.CommonMoveDot				=ui.EditCommonMoveDot		->value();
		Thr->ThreshouldBag.FollowLineLayer				=ui.EditFollowLineLayer			->value();
		Thr->ThreshouldBag.PointMove.ModePermitInverted	=ui.checkBPermitInverted		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeOppositeRange	=ui.checkBModeOppositeRange		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeUseGlobalLine	=ui.checkBModeUseGlobalLine		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeCalcBothBN		=ui.checkModeCalcBothBN			->isChecked();
		
		Thr->ThreshouldBag.ExpandForGenMask				=ui.EditExpandForGenMask		->value();

		BData->SetInvertLogic(ui.checkBModeInvertLogic->isChecked());

		NewCenterBright	=Thr->ThreshouldBag.RegularCenterBright;
		NewNBrightWidthL=Thr->ThreshouldBag.NBrightWidthL;		
		NewNBrightWidthH=Thr->ThreshouldBag.NBrightWidthH;		
		NewBBrightWidthL=Thr->ThreshouldBag.BBrightWidthL;		
		NewBBrightWidthH=Thr->ThreshouldBag.BBrightWidthH;			//return;
	}
}



void HistogramForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(HistogramForm_LS,LID_6)/*"Reflecting ONE block threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one block threshold");
	GetDataFromWindow();
	IntList EdittedMemberID;
	GetEdittedList(EdittedMemberID);

	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	Packet.IData.EdittedMemberID=EdittedMemberID;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void HistogramForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(HistogramForm_LS,LID_7)/*"Reflecting ALL blocks\' threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all blocks threshold");
	GetDataFromWindow();
	IntList EdittedMemberID;
	GetEdittedList(EdittedMemberID);

	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	Packet.IData.EdittedMemberID=EdittedMemberID;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	if(NewNBrightWidthL!=OldNBrightWidthL){
		ManualExecuterBlockNBrightL	*L=new ManualExecuterBlockNBrightL(NewNBrightWidthL);
		L->LibID	=NewLibID;
		InstBase->GetManualExecuter().AppendCommand(L);
	}
	if(NewNBrightWidthH!=OldNBrightWidthH){
		ManualExecuterBlockNBrightH	*L=new ManualExecuterBlockNBrightH(NewNBrightWidthH);
		L->LibID	=NewLibID;
		InstBase->GetManualExecuter().AppendCommand(L);
	}
	if(NewBBrightWidthL!=OldBBrightWidthL){
		ManualExecuterBlockBBrightL	*L=new ManualExecuterBlockBBrightL(NewBBrightWidthL);
		L->LibID	=NewLibID;
		InstBase->GetManualExecuter().AppendCommand(L);
	}
	if(NewBBrightWidthH!=OldBBrightWidthH){
		ManualExecuterBlockBBrightH	*L=new ManualExecuterBlockBBrightH(NewBBrightWidthH);
		L->LibID	=NewLibID;
		InstBase->GetManualExecuter().AppendCommand(L);
	}
	InstBase->GetManualExecuter().DeliverToSlave(InstBase);
	SetColoriseByManual();

	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}
/*
void HistogramForm::TestedData()
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

void	HistogramForm::SlotLineGraphDClick(int X,int Y)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			continue;
		BlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		if(ui.checkBModeAbsoluteBright	->isChecked()==false){
			if(ui.tabWidgetInspect->currentIndex ()==1){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if((NBrightWidthL+AbsNBrightWidthL-X)>=0){
						Thr->ThreshouldBag.NBrightWidthL=NBrightWidthL+AbsNBrightWidthL-X;
						ui.EditNBrightWidthL->setValue(Thr->ThreshouldBag.NBrightWidthL);
						ShowThreshold();
					}
				}
				else{
					if(NBrightWidthH+X-AbsNBrightWidthH>=0){
						Thr->ThreshouldBag.NBrightWidthH=NBrightWidthH+X-AbsNBrightWidthH;
						ui.EditNBrightWidthH->setValue(Thr->ThreshouldBag.NBrightWidthH);
						ShowThreshold();
					}
				}
			}
			else if(ui.tabWidgetInspect->currentIndex ()==0){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if(BBrightWidthL+AbsBBrightWidthL-X>=0){
						Thr->ThreshouldBag.BBrightWidthL=BBrightWidthL+AbsBBrightWidthL-X;
						ui.EditBBrightWidthL->setValue(Thr->ThreshouldBag.BBrightWidthL);
						ShowThreshold();
					}
				}
				else{
					if(BBrightWidthH+X-AbsBBrightWidthH>=0){
						Thr->ThreshouldBag.BBrightWidthH=BBrightWidthH+X-AbsBBrightWidthH;
						ui.EditBBrightWidthH->setValue(Thr->ThreshouldBag.BBrightWidthH);
						ShowThreshold();
					}
				}
			}
		}
		else{
			if(ui.tabWidgetInspect->currentIndex ()==1){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if(Thr->ThreshouldBag.NBrightWidthH>=X){
						Thr->ThreshouldBag.NBrightWidthL=X;
						ui.EditNBrightWidthL->setValue(Thr->ThreshouldBag.NBrightWidthL);
						ShowThreshold();
					}
				}
				else{
					if(Thr->ThreshouldBag.NBrightWidthL<=X){
						Thr->ThreshouldBag.NBrightWidthH=X;
						ui.EditNBrightWidthH->setValue(Thr->ThreshouldBag.NBrightWidthH);
						ShowThreshold();
					}
				}
			}
			else if(ui.tabWidgetInspect->currentIndex ()==0){
				if(ui.radioButtonDarkSide1->isChecked()==true){
					if(Thr->ThreshouldBag.BBrightWidthH>=X){
						Thr->ThreshouldBag.BBrightWidthL=X;
						ui.EditBBrightWidthL->setValue(Thr->ThreshouldBag.BBrightWidthL);
						ShowThreshold();
					}
				}
				else{
					if(Thr->ThreshouldBag.BBrightWidthL<=X){
						Thr->ThreshouldBag.BBrightWidthH=X;
						ui.EditBBrightWidthH->setValue(Thr->ThreshouldBag.BBrightWidthH);
						ShowThreshold();
					}
				}
			}
		}
		LGraph.repaint();
		if(OnChanging==false){
			emit	SignalStartCalc();
		}
		return;
	}
}


void HistogramForm::on_tabWidgetInspect_currentChanged(int)
{
	ShowThreshold();
	LGraph.repaint();
	emit	SignalStartCalc();
}

void HistogramForm::on_EditNBrightWidthL_valueChanged(int X)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			return;
		BlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->ThreshouldBag.NBrightWidthL=X;
		ShowThreshold();
		LGraph.repaint();
		if(OnChanging==false){
			emit	SignalStartCalc();
		}
		return;
	}
}

void HistogramForm::on_EditNBrightWidthH_valueChanged(int X)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			return;
		BlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->ThreshouldBag.NBrightWidthH=X;
		ShowThreshold();
		LGraph.repaint();
		if(OnChanging==false){
			emit	SignalStartCalc();
		}
		return;
	}
}

void HistogramForm::on_EditBBrightWidthL_valueChanged(int X)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			return;
		BlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->ThreshouldBag.BBrightWidthL=X;
		ShowThreshold();
		LGraph.repaint();
		if(OnChanging==false){
			emit	SignalStartCalc();
		}
		return;
	}
}

void HistogramForm::on_EditBBrightWidthH_valueChanged(int X)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			return;
		BlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->ThreshouldBag.BBrightWidthH=X;
		ShowThreshold();
		LGraph.repaint();
		if(OnChanging==false){
			emit	SignalStartCalc();
		}
		return;
	}
}

void	HistogramForm::SlotLayerClicked()
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
	emit	SignalStartCalc();
}


void HistogramForm::on_ButtonCalc_clicked()
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*nBData=dynamic_cast<BlockItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,BlockReqTryThresholdCommand ,BlockSendTryThresholdCommand);
		BlockItem	*BData=&((BlockReqTryThreshold *)PacketReq.Data)->Threshold;
		((BlockReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((BlockReqTryThreshold *)PacketReq.Data)->Layer			=D->Layer;
		((BlockReqTryThreshold *)PacketReq.Data)->BlockItemID	=DA->GetID();

		BlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->CalculatedInfo	=nBData->GetThresholdR(GetLayersBase())->CalculatedInfo;
		Thr->ThreshouldBag.NBrightWidthL				=ui.EditNBrightWidthL	->value();
		Thr->ThreshouldBag.NBrightWidthH				=ui.EditNBrightWidthH	->value();
		Thr->ThreshouldBag.NOKDotL						=ui.EditNOKDotL			->value();
		Thr->ThreshouldBag.NOKDotH						=ui.EditNOKDotH			->value();
		Thr->ThreshouldBag.NMaxNGDotL					=ui.EditNMaxNGDotL		->value();
		Thr->ThreshouldBag.NMaxNGDotH					=ui.EditNMaxNGDotH		->value();
		Thr->ThreshouldBag.NOKLengthL					=ui.EditNOKLengthL		->value();
		Thr->ThreshouldBag.NOKLengthH					=ui.EditNOKLengthH		->value();
		Thr->ThreshouldBag.BBrightWidthL				=ui.EditBBrightWidthL	->value();
		Thr->ThreshouldBag.BBrightWidthH				=ui.EditBBrightWidthH	->value();
		Thr->ThreshouldBag.BOKDotL						=ui.EditBOKDotL			->value();
		Thr->ThreshouldBag.BOKDotH						=ui.EditBOKDotH			->value();
		Thr->ThreshouldBag.BMaxNGDotL					=ui.EditBMaxNGDotL		->value();
		Thr->ThreshouldBag.BMaxNGDotH					=ui.EditBMaxNGDotH		->value();
		Thr->ThreshouldBag.BOKLengthL					=ui.EditBOKLengthL		->value();
		Thr->ThreshouldBag.BOKLengthH					=ui.EditBOKLengthH		->value();
		Thr->ThreshouldBag.DiffBrightWidthL				=ui.EditDiffBrightWidthL->value();
		Thr->ThreshouldBag.DiffBrightWidthH				=ui.EditDiffBrightWidthH->value();
		Thr->ThreshouldBag.NMinNGCountL					=ui.EditNMinNGCountL	->value();
		Thr->ThreshouldBag.NMinNGCountH					=ui.EditNMinNGCountH	->value();
		Thr->ThreshouldBag.BMinNGCountL					=ui.EditBMinNGCountL	->value();
		Thr->ThreshouldBag.BMinNGCountH					=ui.EditBMinNGCountH	->value();
		Thr->ThreshouldBag.NConnectLen					=ui.EditNConnectLen		->value();
		Thr->ThreshouldBag.BConnectLen					=ui.EditBConnectLen		->value();

		Thr->ThreshouldBag.PointMove.ModeEnabled			=ui.checkBModeEnabled			->isChecked();
		Thr->ThreshouldBag.PointMove.ModeAbsoluteBright		=ui.checkBModeAbsoluteBright	->isChecked();
		Thr->ThreshouldBag.PointMove.ModeNGCluster			=ui.checkBModeNGCluster			->isChecked();
		Thr->ThreshouldBag.PointMove.ModeDiffer				=ui.checkBModeDiffer			->isChecked();
		//Thr->ThreshouldBag.PointMove.ModeMatchPosition		=ui.checkBMatchPosition			->isChecked();
		if(ui.comboBoxMatchPosition	->currentIndex()==0){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=false;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=false;
		}
		else
		if(ui.comboBoxMatchPosition	->currentIndex()==1){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=true;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=false;
		}
		else
		if(ui.comboBoxMatchPosition	->currentIndex()==2){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=false;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=true;
		}
		else
		if(ui.comboBoxMatchPosition	->currentIndex()==3){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=true;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=true;
		}
		Thr->ThreshouldBag.PointMove.ModeSearchDetail		=ui.checkBModeSearchDetail		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeDynamicMask		=ui.checkBModeDynamicMask		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeBindBWBroad		=ui.checkBModeBindBWBroad		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeBindBWNarrow		=ui.checkBModeBindBWNarrow		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeAdoptBiggest		=ui.checkBModeAdoptBiggest		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeUseMasterImage		=ui.checkBModeUseMasterImage	->isChecked();
		Thr->ThreshouldBag.PointMove.ModeUseRegularBrightness=ui.checkBoxUseRegularBrightness->isChecked();
		if(ui.checkBoxUseRegularBrightness->isChecked()==true){
			Thr->ThreshouldBag.RegularCenterBright	=ui.EditCenterBrightMaster->text().toInt();
			BData->CenterBright	=ui.EditCenterBrightMaster->text().toInt();
		}
		Thr->ThreshouldBag.PointMove.ModeOnlyMatching	=ui.checkBModeOnlyMatching		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeWhiteMask		=ui.checkBModeWhiteMask			->isChecked();
		Thr->ThreshouldBag.PointMove.ModeBlackMask		=ui.checkBModeBlackMask			->isChecked();
		Thr->ThreshouldBag.PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
		Thr->ThreshouldBag.PointMove.ModeAdjustable		=ui.checkBModeAdjustable		->isChecked();
		Thr->ThreshouldBag.PointMove.ModeCalcBothBN		=ui.checkModeCalcBothBN			->isChecked();
		//Thr->ThreshouldBag.PointMove.ModeMatchPosition	=nBData->GetThresholdR(GetLayersBase())->ThreshouldBag.PointMove.ModeMatchPosition;
		if(ui.comboBoxMatchPosition	->currentIndex()==0){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=false;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=false;
		}
		else
		if(ui.comboBoxMatchPosition	->currentIndex()==1){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=true;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=false;
		}
		else
		if(ui.comboBoxMatchPosition	->currentIndex()==2){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=false;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=true;
		}
		else
		if(ui.comboBoxMatchPosition	->currentIndex()==3){
			Thr->ThreshouldBag.PointMove.ModeMatchPosition	=true;
			Thr->ThreshouldBag.PointMove.ModeMatchPositionBW=true;
		}
		Thr->ThreshouldBag.PointMove.ModeSearchDetail	=ui.checkBModeSearchDetail	->isChecked();
		Thr->ThreshouldBag.AdjustBlack					=ui.EditAdjustBlack			->value();
		Thr->ThreshouldBag.AdjustWhite					=ui.EditAdjustWhite			->value();
		Thr->ThreshouldBag.PointMove.ModeCommonMovable	=ui.checkBModeCommonMovable	->isChecked();
		Thr->ThreshouldBag.SelfSearch					=ui.EditSelfSearch			->value();
		Thr->ThreshouldBag.CommonMoveDot				=ui.EditCommonMoveDot		->value();
		Thr->ThreshouldBag.FollowLineLayer				=ui.EditFollowLineLayer		->value();
		Thr->ThreshouldBag.PointMove.ModePermitInverted	=ui.checkBPermitInverted	->isChecked();
		Thr->ThreshouldBag.PointMove.ModeOppositeRange	=ui.checkBModeOppositeRange	->isChecked();
		Thr->ThreshouldBag.PointMove.ModeUseGlobalLine	=ui.checkBModeUseGlobalLine	->isChecked();
		Thr->ThreshouldBag.ExpandForGenMask				=ui.EditExpandForGenMask	->value();
		BData->SetInvertLogic(ui.checkBModeInvertLogic->isChecked());

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			BlockSendTryThreshold	*R=((BlockSendTryThreshold *)PacketSend.Data);
			ui.labelResultNDark	->setText(QString::number(R->NGDotInNDark	));
			ui.labelResultNLight->setText(QString::number(R->NGDotInNBright	));
			ui.labelResultBDark	->setText(QString::number(R->NGDotInBDark	));
			ui.labelResultBLight->setText(QString::number(R->NGDotInBBright	));

			ui.labelResultNDarkUnit	->setText(TransformPixelToUnitSquareStr(Page,R->NGDotInNDark		));
			ui.labelResultNLightUnit->setText(TransformPixelToUnitSquareStr(Page,R->NGDotInNBright	));
			ui.labelResultBDarkUnit	->setText(TransformPixelToUnitSquareStr(Page,R->NGDotInBDark		));
			ui.labelResultBLightUnit->setText(TransformPixelToUnitSquareStr(Page,R->NGDotInBBright	));

			SimPanel.SetResult(R->Result);

			::SetDataToTable(ui.tableWidgetShift ,0 ,1 ,QString::number(R->ShiftByCommonX));
			::SetDataToTable(ui.tableWidgetShift ,1 ,1 ,QString::number(R->ShiftByCommonY));
			::SetDataToTable(ui.tableWidgetShift ,0 ,2 ,QString::number(R->ShiftBySelfX));
			::SetDataToTable(ui.tableWidgetShift ,1 ,2 ,QString::number(R->ShiftBySelfY));
			break;
		}
	}	
}

void HistogramForm::on_ButtonRelrectSaveParts_clicked()
{
	GetDataFromWindow();

	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	BlockItem	*BData;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BData=dynamic_cast<BlockItem *>(DA);
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
			QMessageBox::warning (NULL
						, LangSolver.GetString(HistogramForm_LS,LID_25)/*"Error"*/
						, LangSolver.GetString(HistogramForm_LS,LID_26)/*"Error occurs in saving algorithm data of parts"*/ );
		while(Ack.IsReceived()==false);
		if(Ack.Ret==false){
			QMessageBox::warning (NULL
						, LangSolver.GetString(HistogramForm_LS,LID_27)/*"Error"*/
						, LangSolver.GetString(HistogramForm_LS,LID_28)/*"Error occurs in saving algorithm data of parts"*/ );
		}
	}
}

void HistogramForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();

	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			BlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			if(Thr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true){
				ALib->RegularBrightness	=Thr->ThreshouldBag.RegularCenterBright;
			}
			else{
				ALib->RegularBrightness	=-1;
			}
			Container->Update(DestLib);
			return;
		}
	}
}

void HistogramForm::on_ButtonLoadFromLibrary_clicked()
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			BlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			return;
		}
	}
}

void HistogramForm::on_pushButtonChangeLib_clicked()
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
			BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
			if(BData==NULL)
				continue;
			//int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui.EditLibID	->setText(QString::number(DA->GetLibID()));
			/*
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==OldID){
					L->SetLibID(s->SelectedLibID);
					ABase->GetLibraryContainer()->GetLibraryNames(LibIDList);
					ui.EditLibName	->setText(L->GetLibName());
					break;
				}
			}
			*/
		}
	}
}
void HistogramForm::on_listWidgetHistList_doubleClicked(const QModelIndex &index)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	int	Row=ui.listWidgetHistList->currentRow();
	if(Row<0)
		return;
	HistgramTypeListInAlgo	*H=HContainer[Row];
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			continue;
		
		BData->TF_ShowHistgramGraph(H->HistID);
		return;
	}
}

void HistogramForm::on_toolButtonSimShowBlock_clicked()
{
	SimPanel.SetModeShowBlock		(ui.toolButtonSimShowBlock ->isChecked());
	SimPanel.repaint();
}

void HistogramForm::on_toolButtonSimShowBright_clicked()
{
	SimPanel.SetModeShowBrightnessNG(ui.toolButtonSimShowBright->isChecked());
	SimPanel.repaint();
}

void HistogramForm::on_pushButtonSimShowCenterPos_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.repaint();
			}
		}
	}
}

void	HistogramForm::SlotStartCalc()
{
	SimPanel.SetModeShowBlock		(ui.toolButtonSimShowBlock ->isChecked());
	SimPanel.SetModeShowBrightnessNG(ui.toolButtonSimShowBright->isChecked());
	on_ButtonCalc_clicked();
	SimPanel.repaint();
}
void HistogramForm::on_EditBOKDotL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.doubleSpinBoxBOKDotL	->setValue(TransformPixelToUnitSquare(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditBOKDotH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.doubleSpinBoxBOKDotH	->setValue(TransformPixelToUnitSquare(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditBOKLengthL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.doubleSpinBoxBOKLengthL	->setValue(TransformPixelToUnit(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditBOKLengthH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.doubleSpinBoxBOKLengthH	->setValue(TransformPixelToUnit(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditNOKDotL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.doubleSpinBoxNOKDotL	->setValue(TransformPixelToUnitSquare(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditNOKDotH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.doubleSpinBoxNOKDotH	->setValue(TransformPixelToUnitSquare(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditNOKLengthL_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.doubleSpinBoxNOKLengthL	->setValue(TransformPixelToUnit(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditNOKLengthH_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui.doubleSpinBoxNOKLengthH	->setValue(TransformPixelToUnit(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditAdjustBlack_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_checkBModeAdjustable_clicked(bool checked)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_EditAdjustWhite_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_EditSelfSearch_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.doubleSpinBoxSelfSearch	->setValue(TransformPixelToUnit(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditCommonMoveDot_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.doubleSpinBoxCommonMoveDot	->setValue(TransformPixelToUnit(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_checkBModeWhiteMask_clicked(bool checked)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_checkBModeBlackMask_clicked(bool checked)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_EditNMaxNGDotL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.doubleSpinBoxNMaxNGDotL	->setValue(TransformPixelToUnitSquare(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditNMaxNGDotH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.doubleSpinBoxNMaxNGDotH	->setValue(TransformPixelToUnitSquare(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditBMaxNGDotL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.doubleSpinBoxBMaxNGDotL	->setValue(TransformPixelToUnitSquare(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_EditBMaxNGDotH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.doubleSpinBoxBMaxNGDotH	->setValue(TransformPixelToUnitSquare(Page,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void HistogramForm::on_checkBModeInvertLogic_clicked()
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_checkBModeSearchDetail_clicked()
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_pushButtonTransmitItemNameAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(HistogramForm_LS,LID_8)/*"Transmiting ItemName all"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Transmit ItemName all");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemNameDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void HistogramForm::on_EditBConnectLen_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_EditBMinNGCountL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_EditBMinNGCountH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_checkBModeBindBWBroad_clicked()
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_EditNMinNGCountL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_EditNMinNGCountH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_EditNConnectLen_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_checkBModeBindBWNarrow_clicked()
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_checkBModeAdoptBiggest_clicked()
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_doubleSpinBoxBOKDotL_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditBOKDotL->setValue(TransformUnitToPixelSquare(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxBOKDotH_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditBOKDotH->setValue(TransformUnitToPixelSquare(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxBOKLengthL_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditBOKLengthL->setValue(TransformUnitToPixel(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxBOKLengthH_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditBOKLengthH->setValue(TransformUnitToPixel(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxBMaxNGDotL_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditBMaxNGDotL->setValue(TransformUnitToPixelSquare(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxBMaxNGDotH_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditBMaxNGDotH->setValue(TransformUnitToPixelSquare(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxNOKDotL_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditNOKDotL->setValue(TransformUnitToPixelSquare(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxNOKDotH_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditNOKDotH->setValue(TransformUnitToPixelSquare(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxNOKLengthL_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditNOKLengthL->setValue(TransformUnitToPixel(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxNOKLengthH_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditNOKLengthH->setValue(TransformUnitToPixel(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxNMaxNGDotL_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditNMaxNGDotL->setValue(TransformUnitToPixelSquare(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxNMaxNGDotH_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditNMaxNGDotH->setValue(TransformUnitToPixelSquare(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxSelfSearch_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditSelfSearch->setValue(TransformUnitToPixel(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_doubleSpinBoxCommonMoveDot_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui.EditCommonMoveDot->setValue(TransformUnitToPixel(Page,arg1));
	OnChanging=false;
}

void HistogramForm::on_checkBoxUseRegularBrightness_clicked()
{
	QPalette	P=ui.EditCenterBrightMaster->palette();
	if(ui.checkBoxUseRegularBrightness->isChecked()==true){
		P.setColor(QPalette::Base,Qt::white);
	}
	else{
		P.setColor(QPalette::Base,Qt::cyan);
	}
	ui.EditCenterBrightMaster->setPalette(P);
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_checkBPermitInverted_clicked()
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_pushButtonClearManualChange_clicked()
{
	InstBase->GetManualExecuter().ClearCommandAll();
	InstBase->GetManualExecuter().DeliverToSlave(InstBase);
	SetColoriseByManual();
}

void HistogramForm::on_checkBModeOppositeRange_clicked()
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_checkBModeUseGlobalLine_clicked()
{
	if(OnChanging==true){
		return;
	}
	emit	SignalStartCalc();
}

void HistogramForm::on_pushButtonRestore_clicked()
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL){
		return;
	}
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL){
			continue;
		}
		if(LayerList.GetFirst()->GetValue()!=D->Layer){
			continue;
		}
		BlockItem	*BData=dynamic_cast<BlockItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	BLib(Container);
		if(Container->GetLibrary(LibID ,BLib)==true){
			BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(BLib.GetLibrary());
			AlgorithmLibraryLevelContainer	SrcLib(Container);
			if(Container->GetLibrary(ALib->GetSourceID() ,SrcLib)==true){
				BlockLibrary	*BLib=dynamic_cast<BlockLibrary *>(SrcLib.GetLibrary());
				BlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
				Thr->FromLibrary(BLib);
				ShowLibrary();
				ShowThreshold();
				emit	SignalStartCalc();
				return;
			}
		}
	}
}
