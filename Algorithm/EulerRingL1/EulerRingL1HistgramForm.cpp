#include "EulerRingL1Resource.h"
#include "EulerRingL1HistgramForm.h"
#include "ui_EulerRingL1HistgramForm.h"
#include "XEulerRingL1.h"
#include "XEulerRingL1Library.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "swap.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


DisplaySimPanelEulerRingL1::DisplaySimPanelEulerRingL1(LayersBase *base ,EulerRingL1HistgramForm *parentw ,QWidget *parent)
	:DisplaySimPanel(base ,parent)
{
	ParentWidget=parentw;
}


void	DisplaySimPanelEulerRingL1::DrawOther(QPainter &Pnt)
{
	if(ParentWidget->ModeShowRing==true && Result!=NULL){
		QRgb RingCol=qRgba(240,180,0,120);
		for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
			if(r->result==0x1){
				r->NGShape.DrawAlpha(Result->GetAlignedX()+r->Rx
									,Result->GetAlignedY()+r->Ry
						,ResultImage ,RingCol
						,ZoomRate ,MovX ,MovY);
			}
		}
	}
	if(ParentWidget->ModeShowMask==true && Result!=NULL){
		QRgb HoleMaskCol=qRgba(0,220,0,120);
		for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
			if(r->result==0x3){
				r->NGShape.DrawAlpha(Result->GetAlignedX()+r->Rx
									,Result->GetAlignedY()+r->Ry
						,ResultImage ,HoleMaskCol
						,ZoomRate ,MovX ,MovY);
			}
		}
	}
	if(ParentWidget->ModeShowHole==true && Result!=NULL){
		QRgb HoleCol=qRgba(100,0,220,120);
		for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
			if(r->result==0x2){
				r->NGShape.DrawAlpha(Result->GetAlignedX()+r->Rx
									,Result->GetAlignedY()+r->Ry
						,ResultImage ,HoleCol
						,ZoomRate ,MovX ,MovY);
			}
		}
	}
	if(ParentWidget->ModeShowBlock==true && Result!=NULL){
		QRgb ItemCol=qRgba(180,180,0,120);
		ItemArea.DrawAlpha(Result->GetAlignedX()
						,  Result->GetAlignedY()
						,ResultImage ,ItemCol
						,ZoomRate ,MovX ,MovY);
	}
}

EulerRingL1HistgramForm::EulerRingL1HistgramForm(LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
    ,ui(new Ui::EulerRingL1HistgramForm)
	,SimPanel(Base,this,parent)
	,LGraph(parent)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ModeShowHole	=true;
	ModeShowRing	=true;
	ModeShowBlock	=true;
	ModeShowMask	=true;
	OnChanging	=false;
	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(/**/"Basic",/**/"EulerRingL1");
	SimPanel.SetGUI(/**/"Button",/**/"PropertyEulerRingL1");
	SimPanel.setGeometry(0,0,ui->frame_SimImage->width(),ui->frame_SimImage->height());
	connect(this,SIGNAL(SignalStartCalc()),this,SLOT(SlotStartCalc()),Qt::QueuedConnection);

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	LGraph.setParent(ui->frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.move(0,0);
	LGraph.resize(ui->frameLineGraph->width(),ui->frameLineGraph->height());
	LayerBar.setParent(ui->frameLayer);
	LayerBar.move(0,0);
	LayerBar.resize(ui->frameLayer->width(),ui->frameLayer->height());
	LButtonList=new QToolButton*[LayerNumb];
	LastLayer=0;
	for(int Layer=0;Layer<LayerNumb;Layer++){
		LButtonList[Layer]=new QToolButton();
		LButtonList[Layer]->setText(LangSolver.GetString(EulerRingL1HistgramForm_LS,LID_0)/*"Ly"*/+QString::number(Layer));
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
	MasterPanel->setParent(ui->frameMaster);
	MasterPanel->SetColor(MasterColor);
	TargetPanel	=new mtColorFrame();
	TargetPanel->setParent(ui->frameTarget);
	TargetPanel->SetColor(TargetColor);
	ThresholdPanel	=new mtColorFrame();
	ThresholdPanel->setParent(ui->frameThreshold);
	ThresholdPanel->SetColor(ThreshColor);

	ui->labelMasterHoleDiameter		->setText(/**/"");
	ui->labelResultHoleDiameter		->setText(/**/"");
	ui->labelResultHoleShift		->setText(/**/"");
	ui->labelResultRing				->setText(/**/"");

	ui->labelMasterHoleDiameterUnit	->setText(/**/"");
	ui->labelResultHoleDiameterUnit	->setText(/**/"");
	ui->labelResultHoleShiftUnit	->setText(/**/"");

	SetupPassword();

	InstallOperationLog(this);
}

EulerRingL1HistgramForm::~EulerRingL1HistgramForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	delete	[]LButtonList;
	LButtonList=NULL;
}

void	EulerRingL1HistgramForm::GetActiveLayerList(IntList &LayerList)
{
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int Layer=0;Layer<LayerNumb;Layer++){
		if(LButtonList[Layer]->isChecked()==true){
			LayerList.Add(Layer);
		}
	}
}
void	EulerRingL1HistgramForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	ui->pushButtonRestore->setEnabled(false);
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		LButtonList[D->Layer]->setChecked(true);
		SimPanel.SetLayer(D->Layer);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
			if(BData!=NULL){
				GlobalPage	=D->GlobalPage;
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock		(ui->toolButtonSimShowBlock ->isChecked());

				int	LibID=BData->GetLibID();
				AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
				AlgorithmLibraryLevelContainer	SrcLib(Container);
				if(Container->GetLibrary(LibID ,SrcLib)==true){
					EulerRingL1Library	*ALib=dynamic_cast<EulerRingL1Library *>(SrcLib.GetLibrary());
					if(SrcLib.GetSourceID()>0){
						ui->pushButtonRestore->setEnabled(true);
					}
				}
			}
		}
	}

	CreateThreshld();
	ShowHistgramList();

	ui->doubleSpinBoxConnectLenMM			->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui->doubleSpinBoxMinHoleDiameterMM		->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui->doubleSpinBoxMaxHoleDiameterMM		->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui->doubleSpinBoxMaxShiftHoleMM			->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui->doubleSpinBoxExpandForDynamicMaskMM	->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui->doubleSpinBoxSearchDotMM			->setDecimals(GetParamGlobal()->SmallNumberFigure);

	ui->labelUnitName_2	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_3	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_8	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_9	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_10->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_4	->setText(GetParamGlobal()->UnitName);
}

void	EulerRingL1HistgramForm::ShowHistgramList(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	ui->listWidgetHistList->clear();
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;
		
		BData->TF_EnumHistList(HContainer);
		for(HistgramTypeListInAlgo *a=HContainer.GetFirst();a!=NULL;a=a->GetNext()){
			ui->listWidgetHistList->addItem(a->HistName);
		}
		return;
	}
}

void	EulerRingL1HistgramForm::CreateThreshld(void)
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
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,EulerRingL1ReqThresholdReqCommand ,EulerRingL1ReqThresholdSendCommand);
		((EulerRingL1ThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((EulerRingL1ThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((EulerRingL1ThresholdReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((EulerRingL1ThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			EulerRingL1ThresholdSend	*ThrePoint=(EulerRingL1ThresholdSend *)PacketSend.GetData();
			CenterBright		=ThrePoint->CenterBright;
			DarkWidth			=ThrePoint->DarkWidth;		
			LightWidth			=ThrePoint->LightWidth;		
			MinHoleDiameter		=ThrePoint->MinHoleDiameter;		
			MaxHoleDiameter		=ThrePoint->MaxHoleDiameter;		
			MaxShiftHole		=ThrePoint->MaxShiftHole;	
			ConnectLen			=ThrePoint->ConnectLen;	
			ExpandForDynamicMask=ThrePoint->ExpandForDynamicMask;
			AdjustBlack			=ThrePoint->AdjustBlack;	
			AdjustWhite			=ThrePoint->AdjustWhite;
			SearchDot			=ThrePoint->SearchDot;

			BrightWidthL		=ThrePoint->BrightWidthL;		
			BrightWidthH		=ThrePoint->BrightWidthH;		
			AbsBrightWidthL		=ThrePoint->AbsBrightWidthL;	
			AbsBrightWidthH		=ThrePoint->AbsBrightWidthH;	

			break;
		}
	}
	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
	LGraph.repaint();
}

void EulerRingL1HistgramForm::GetHistogramData(void)
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
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,EulerRingL1HistogramListReqCommand ,EulerRingL1HistogramListSendCommand);
		((EulerRingL1HistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((EulerRingL1HistogramListReq *)PacketReq.Data)->Layer=D->Layer;
		((EulerRingL1HistogramListReq *)PacketReq.Data)->BlockItemID	=DA->GetID();
		((EulerRingL1HistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			EulerRingL1HistogramListSend	*L=(EulerRingL1HistogramListSend *)PacketSend.GetData();
			YMax=0;
			for(int i=0;i<256;i++){
				YMax=max(YMax,L->ListMaster[i]);
				YMax=max(YMax,L->ListTarget[i]);
				GraphColMaster.AddXY(i		,L->ListMaster[i]);
				GraphColTarget.AddXY(i+0.5	,L->ListTarget[i]);
			}
			ui->EditCenterBrightMaster	->setText(QString::number(L->CenterBright));
			ui->EditCenterBrightTarget	->setText(QString::number(L->CenterTargetBright));
			return;
		}
	}
}

void	EulerRingL1HistgramForm::ShowLibrary(void)
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
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;

		if(DA->GetLibID()<0){
			ui->EditLibID->setText(/**/"");
			ui->EditLibName->setText(/**/"");
		}
		else{
			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			ui->EditLibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui->EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
		ui->EditItemName					->setText(BData->GetItemName());
		ui->EditDarkWidth					->setValue(BData->GetThresholdR(GetLayersBase())->DarkWidth);
		ui->EditLightWidth					->setValue(BData->GetThresholdR(GetLayersBase())->LightWidth);
		ui->EditConnectLen					->setValue(BData->GetThresholdR(GetLayersBase())->ConnectLen);
		ui->EditExpandForDynamicMask		->setValue(BData->GetThresholdR(GetLayersBase())->ExpandForDynamicMask);
		ui->EditMinHoleDiameter				->setValue(BData->GetThresholdR(GetLayersBase())->MinHoleDiameter);
		ui->EditMaxHoleDiameter				->setValue(BData->GetThresholdR(GetLayersBase())->MaxHoleDiameter);
		ui->EditMaxShiftHole				->setValue(BData->GetThresholdR(GetLayersBase())->MaxShiftHole);
		ui->EditHoleBrightnessAsReference	->setValue(BData->GetThresholdR(GetLayersBase())->HoleBrightnessAsReference);

		ui->checkModeEnabled				->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeEnabled);
		ui->checkModeAbsoluteBright			->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeAbsoluteBright);
		ui->checkModeDynamicMask			->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeMakeDynamicMask);
		ui->checkModeEnableHoleCheck		->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeEnableHoleCheck);
		ui->checkModeCenterBrightFromParts	->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeCenterBrightFromParts);
		ui->checkModeEnableOpenRingCheck	->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeEnableOpenRingCheck);
		ui->checkModeEnableInRound			->setChecked(BData->GetThresholdR(GetLayersBase())->PointMove.ModeEnableInRound);

		ui->EditAdjustBlack				->setValue(BData->GetThresholdR(GetLayersBase())->AdjustBlack);
		ui->EditAdjustWhite				->setValue(BData->GetThresholdR(GetLayersBase())->AdjustWhite);
		ui->EditSearchDot				->setValue(BData->GetThresholdR(GetLayersBase())->SearchDot);

		if(BData->IsOriginParts()==true){
			ui->stackedWidgetParts->setCurrentIndex(1);
		}
		else{
			ui->stackedWidgetParts->setCurrentIndex(0);
		}
		return;
	}
}

void EulerRingL1HistgramForm::ShowThreshold(void)
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
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;

		if(ui->checkModeAbsoluteBright	->isChecked()==false){
			GraphThresh.AddXY(AbsBrightWidthL-(BData->GetThresholdR(GetLayersBase())->DarkWidth -BrightWidthL)	,YMax);
			GraphThresh.AddXY(AbsBrightWidthH+(BData->GetThresholdR(GetLayersBase())->LightWidth-BrightWidthH)	,YMax);
		}
		else{
			GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->DarkWidth ,YMax);
			GraphThresh.AddXY(BData->GetThresholdR(GetLayersBase())->LightWidth,YMax);
		}
		return;
	}
}
void	EulerRingL1HistgramForm::GetDataFromWindow(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GetDataFromWindowFromNo(LayerList.GetFirst()->GetValue());
}
void	EulerRingL1HistgramForm::GetDataFromWindowFromNo(int LayerNo)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerNo!=D->Layer)
			continue;
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;

		BData->SetItemName(ui->EditItemName	->text());

		EulerRingL1Threshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->DarkWidth							=ui->EditDarkWidth					->value();
		Thr->LightWidth							=ui->EditLightWidth					->value();
		Thr->ConnectLen							=ui->EditConnectLen					->value();
		Thr->ExpandForDynamicMask				=ui->EditExpandForDynamicMask		->value();
		Thr->MinHoleDiameter					=ui->EditMinHoleDiameter			->value();
		Thr->MaxHoleDiameter					=ui->EditMaxHoleDiameter			->value();
		Thr->MaxShiftHole						=ui->EditMaxShiftHole				->value();
		Thr->HoleBrightnessAsReference			=ui->EditHoleBrightnessAsReference	->value();

		Thr->PointMove.ModeEnabled				=ui->checkModeEnabled				->isChecked();
		Thr->PointMove.ModeAbsoluteBright		=ui->checkModeAbsoluteBright		->isChecked();
		Thr->PointMove.ModeMakeDynamicMask		=ui->checkModeDynamicMask			->isChecked();
		Thr->PointMove.ModeEnableHoleCheck		=ui->checkModeEnableHoleCheck		->isChecked();
		Thr->PointMove.ModeCenterBrightFromParts=ui->checkModeCenterBrightFromParts	->isChecked();
		Thr->PointMove.ModeEnableOpenRingCheck	=ui->checkModeEnableOpenRingCheck	->isChecked();
		Thr->PointMove.ModeEnableInRound		=ui->checkModeEnableInRound			->isChecked();

		Thr->AdjustBlack						=ui->EditAdjustBlack				->value();
		Thr->AdjustWhite						=ui->EditAdjustWhite				->value();
		Thr->SearchDot							=ui->EditSearchDot					->value();
		//return;
	}
}

void EulerRingL1HistgramForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE EulerBlock threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one block threshold");
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

void EulerRingL1HistgramForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting All EulerBlocks\' threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all blocks threshold");
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

void	EulerRingL1HistgramForm::SlotLineGraphDClick(int X,int Y)
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
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;
		EulerRingL1Threshold	*Thr=BData->GetThresholdW(GetLayersBase());

		if(ui->checkModeAbsoluteBright	->isChecked()==false){
			if(ui->radioButtonDarkSide1->isChecked()==true){
				if((BrightWidthL+AbsBrightWidthL-X)>=0){
					Thr->DarkWidth=BrightWidthL+AbsBrightWidthL-X;
					ui->EditDarkWidth->setValue(Thr->DarkWidth);
					ShowThreshold();
				}
			}
			else{
				if(BrightWidthH+X-AbsBrightWidthH>=0){
					Thr->LightWidth=BrightWidthH+X-AbsBrightWidthH;
					ui->EditLightWidth->setValue(Thr->LightWidth);
					ShowThreshold();
				}
			}
		}
		else{
			if(ui->radioButtonDarkSide1->isChecked()==true){
				if(Thr->LightWidth>=X){
					Thr->DarkWidth=X;
					ui->EditDarkWidth->setValue(Thr->DarkWidth);
					ShowThreshold();
				}
			}
			else{
				if(Thr->DarkWidth<=X){
					Thr->LightWidth=X;
					ui->EditLightWidth->setValue(Thr->LightWidth);
					ShowThreshold();
				}
			}
		}
		LGraph.repaint();
		emit	SignalStartCalc();
		return;
	}
}

void	EulerRingL1HistgramForm::SlotLayerClicked()
{
	if(LastLayer>=0)
		GetDataFromWindowFromNo(LastLayer);
	CreateThreshld();
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();

	if(LayerNumb>=1 && LButtonList[0]->isChecked()==true){
		LastLayer=0;
	}
	else if(LayerNumb>=2 && LButtonList[1]->isChecked()==true){
		LastLayer=1;
	}
	else if(LayerNumb>=3 && LButtonList[2]->isChecked()==true){
		LastLayer=2;
	}
	ShowLibrary();
	emit	SignalStartCalc();
}
void EulerRingL1HistgramForm::on_ButtonSaveToLibrary_clicked()
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
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			EulerRingL1Library	*ALib=dynamic_cast<EulerRingL1Library *>(DestLib.GetLibrary(ThresholdLevel));
			EulerRingL1Threshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			Container->Update(DestLib);
			return;
		}
	}
}

void EulerRingL1HistgramForm::on_ButtonLoadFromLibrary_clicked()
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
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			EulerRingL1Library	*ALib=dynamic_cast<EulerRingL1Library *>(SrcLib.GetLibrary(ThresholdLevel));
			EulerRingL1Threshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			CreateThreshld();
			return;
		}
	}
}

void EulerRingL1HistgramForm::on_ButtonClose_clicked()
{
	close();
}

void EulerRingL1HistgramForm::on_ButtonCalc_clicked()
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
		EulerRingL1Item	*nBData=dynamic_cast<EulerRingL1Item *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,EulerRingL1ReqTryThresholdCommand ,EulerRingL1SendTryThresholdCommand);
		EulerRingL1Item	*BData=&((EulerRingL1ReqTryThreshold *)PacketReq.Data)->Threshold;
		((EulerRingL1ReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((EulerRingL1ReqTryThreshold *)PacketReq.Data)->Layer			=D->Layer;
		((EulerRingL1ReqTryThreshold *)PacketReq.Data)->BlockItemID	=DA->GetID();

		EulerRingL1Threshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->DarkWidth							=ui->EditDarkWidth					->value();
		Thr->LightWidth							=ui->EditLightWidth					->value();
		Thr->ConnectLen							=ui->EditConnectLen					->value();
		Thr->ExpandForDynamicMask				=ui->EditExpandForDynamicMask		->value();
		Thr->MinHoleDiameter					=ui->EditMinHoleDiameter			->value();
		Thr->MaxHoleDiameter					=ui->EditMaxHoleDiameter			->value();
		Thr->MaxShiftHole						=ui->EditMaxShiftHole				->value();
		Thr->HoleBrightnessAsReference			=ui->EditHoleBrightnessAsReference	->value();

		Thr->PointMove.ModeEnabled				=ui->checkModeEnabled				->isChecked();
		Thr->PointMove.ModeAbsoluteBright		=ui->checkModeAbsoluteBright		->isChecked();
		Thr->PointMove.ModeMakeDynamicMask		=ui->checkModeDynamicMask			->isChecked();
		Thr->PointMove.ModeEnableHoleCheck		=ui->checkModeEnableHoleCheck		->isChecked();
		Thr->PointMove.ModeCenterBrightFromParts=ui->checkModeCenterBrightFromParts	->isChecked();
		Thr->PointMove.ModeEnableOpenRingCheck	=ui->checkModeEnableOpenRingCheck	->isChecked();
		Thr->PointMove.ModeEnableInRound		=ui->checkModeEnableInRound			->isChecked();

		Thr->AdjustBlack						=ui->EditAdjustBlack				->value();
		Thr->AdjustWhite						=ui->EditAdjustWhite				->value();
		Thr->SearchDot							=ui->EditSearchDot					->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			EulerRingL1SendTryThreshold	*R=((EulerRingL1SendTryThreshold *)PacketSend.Data);

			ui->labelMasterHoleDiameter	->setText(QString::number(R->MasterHoleDiameter));
			ui->labelResultHoleDiameter	->setText(QString::number(R->HoleDiameter	));
			ui->labelResultHoleShift	->setText(QString::number(R->HoleShift	));
			switch(R->Ring){
			case 0:
				ui->labelResultRing			->setText(/**/"None");
				break;
			case 1:
				ui->labelResultRing			->setText(/**/"OK");
				break;
			case 2:
				ui->labelResultRing			->setText(/**/"NG");
				break;
			case 3:
				ui->labelResultRing			->setText(/**/"Hole NG");
				break;
			case 4:
				ui->labelResultRing			->setText(/**/"HoleSize");
				break;
			case 5:
				ui->labelResultRing			->setText(/**/"HoleShift");
				break;
			case 6:
				ui->labelResultRing			->setText(/**/"No hole");
				break;
			}
			ui->labelMasterHoleDiameterUnit	->setText(TransformPixelToUnitStr(GlobalPage,R->MasterHoleDiameter));
			ui->labelResultHoleDiameterUnit	->setText(TransformPixelToUnitStr(GlobalPage,R->HoleDiameter	));
			ui->labelResultHoleShiftUnit	->setText(TransformPixelToUnitStr(GlobalPage,R->HoleShift	));

			SimPanel.SetResult(R->Result);
			SimPanel.repaint();
			break;
		}
	}	
}

void EulerRingL1HistgramForm::on_pushButtonSimShowCenterPos_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
			if(BData!=NULL){
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.repaint();
			}
		}
	}
}
void	EulerRingL1HistgramForm::SlotStartCalc()
{
	on_ButtonCalc_clicked();
	SimPanel.repaint();
}
void EulerRingL1HistgramForm::on_pushButtonTransmitItemNameAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Transmit ItemName all");

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

void EulerRingL1HistgramForm::on_pushButtonChangeLib_clicked()
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
			EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
		}
	}
}

void EulerRingL1HistgramForm::on_toolButtonSimShowBlock_clicked()
{
	ModeShowBlock=ui->toolButtonSimShowBlock ->isChecked();
	SimPanel.repaint();
}

void EulerRingL1HistgramForm::on_toolButtonSimShowHole_clicked()
{
	ModeShowHole=ui->toolButtonSimShowHole ->isChecked();
	SimPanel.repaint();
}

void EulerRingL1HistgramForm::on_toolButtonSimShowRing_clicked()
{
	ModeShowRing=ui->toolButtonSimShowRing ->isChecked();
	SimPanel.repaint();
}

void EulerRingL1HistgramForm::on_toolButtonSimShowMask_clicked()
{
	ModeShowMask=ui->toolButtonSimShowMask ->isChecked();
	SimPanel.repaint();
}

void EulerRingL1HistgramForm::on_toolButtonSimShowNGMark_clicked()
{
	SimPanel.SetModeShowBlock		(ui->toolButtonSimShowNGMark ->isChecked());
	SimPanel.repaint();
}

void EulerRingL1HistgramForm::on_EditDarkWidth_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_EditLightWidth_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_EditConnectLen_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxConnectLenMM	->setValue(TransformPixelToUnitSquare(GlobalPage,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_EditMinHoleDiameter_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxMinHoleDiameterMM	->setValue(TransformPixelToUnitSquare(GlobalPage,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_EditMaxHoleDiameter_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxMaxHoleDiameterMM	->setValue(TransformPixelToUnitSquare(GlobalPage,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_EditMaxShiftHole_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxMaxShiftHoleMM	->setValue(TransformPixelToUnitSquare(GlobalPage,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_checkModeAbsoluteBright_clicked()
{
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_checkModeDynamicMask_clicked()
{
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_checkModeEnableHoleCheck_clicked()
{
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_EditAdjustBlack_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_EditAdjustWhite_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_EditExpandForDynamicMask_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxExpandForDynamicMaskMM	->setValue(TransformPixelToUnitSquare(GlobalPage,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_listWidgetHistList_doubleClicked(const QModelIndex &index)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	int	Row=ui->listWidgetHistList->currentRow();
	if(Row<0)
		return;
	HistgramTypeListInAlgo	*H=HContainer[Row];
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;
		
		BData->TF_ShowHistgramGraph(H->HistID);
		return;
	}
}

void EulerRingL1HistgramForm::on_EditSearchDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxSearchDotMM	->setValue(TransformPixelToUnitSquare(GlobalPage,arg1));
	OnChanging=false;
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_checkModeEnableOpenRingCheck_clicked()
{
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_EditHoleBrightnessAsReference_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void EulerRingL1HistgramForm::on_ButtonLoadRestore_clicked()
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
		EulerRingL1Item	*BData=dynamic_cast<EulerRingL1Item *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	BLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,BLib)==true){
			AlgorithmLibraryLevelContainer	SrcLib(Container);

			if(BData->GetLibraryContainer()->GetLibrary(BLib.GetSourceID() ,SrcLib)==true){
				EulerRingL1Library	*ALib=dynamic_cast<EulerRingL1Library *>(SrcLib.GetLibrary());
				EulerRingL1Threshold	*Thr=BData->GetThresholdW(GetLayersBase());
				Thr->FromLibrary(ALib);
				ShowLibrary();
				ShowThreshold();
				emit	SignalStartCalc();
				return;
			}
		}
	}
}
