//#include "FlatInspectionResource.h"
#include "HistgramFlatInspectionForm.h"
#include "ui_HistgramFlatInspectionForm.h"
#include "XFlatInspection.h"
#include "XFlatInspectionLibrary.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"
#include "XDrawFunc.h"
#include "swap.h"
#include "XColorSpace.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

inline	int	RoundInt(double d)
{
	return floor(d+0.5);
}

static	bool	DDRet=false;

DisplaySimPanelFlatInspection::DisplaySimPanelFlatInspection(LayersBase *base ,HistgramFlatInspectionForm *parentw ,QWidget *parent)
	:DisplaySimPanel(base ,parent)
{
	ParentWidget=parentw;
	ModeDrawSubtract=true;
}


void	DisplaySimPanelFlatInspection::GetDrawInformation(QByteArray &Something)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Something=Buff.buffer();
}
	
//======================================================================================

RedPanelWidget::RedPanelWidget(HistgramFlatInspectionForm *p,QWidget *parent)
	:QWidget(parent),Parent(p)
{
	setMouseTracking(true);
	RedHighRate			=150;
	RedMinBrightness	=70;
	RedGBMerginRate		=20;
	RedGBMerginOffset	=15;
}
RedPanelWidget::~RedPanelWidget(void)
{
}
void RedPanelWidget::mouseMoveEvent(QMouseEvent *event)
{
	int	X=event->pos().x();
	int	Y=event->pos().y();
	int	W=RedImage.width();
	int	H=RedImage.height();
	if(0<=X && X<W && 0<=Y && Y<H){
		QRgb	*d=(QRgb *)RedImage.scanLine(Y);
		Parent->ShowRedInMouse(X,Y,d[X]);
	}
}
void	RedPanelWidget::Resize(int W,int H)
{
	resize(W,H);
	RedImage=QImage(W,H,QImage::Format_RGB32);
	ShowRed();
}
void RedPanelWidget::resizeEvent(QResizeEvent *event)
{
	int	W=width();
	int	H=height();
	RedImage=QImage(W,H,QImage::Format_RGB32);
	ShowRed();
}

void RedPanelWidget::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	Pnt.drawImage(0,0,RedImage);
}

void	RedPanelWidget::ShowRed( WORD	_RedHighRate
								,BYTE	_RedMinBrightness
								,BYTE	_RedGBMerginRate
								,BYTE	_RedGBMerginOffset)
{
	RedHighRate			=_RedHighRate		;
	RedMinBrightness	=_RedMinBrightness	;
	RedGBMerginRate		=_RedGBMerginRate	;
	RedGBMerginOffset	=_RedGBMerginOffset	;
	ShowRed();
	repaint();
}
void	RedPanelWidget::ShowRed(void)
{
	if(RedHighRate==0)
		return;
	int	W=min(RedImage.width(),width());
	int	H=min(RedImage.height(),height());
	if(W==0 || H==0)
		return;

	RedImage.fill(Qt::black);

	double	ZRedHighRate=100.0/((double)RedHighRate);
	double	ZwRedGBMerginRate=100.0/((double)RedGBMerginRate);
	double	wRedGBMerginRate =((double)RedGBMerginRate)/100.0;
	double	MaxRedGBMerginRate=max(ZwRedGBMerginRate,wRedGBMerginRate);
	double	MinRedGBMerginRate=min(ZwRedGBMerginRate,wRedGBMerginRate);

	int	MaxGB=256*ZRedHighRate;
	int	MinGB=RedMinBrightness*ZRedHighRate;

	BYTE	GTable[256*256];
	BYTE	BTable[256*256];
	double	aH=((double)(256-RedMinBrightness))/((double)H);

	int	WXLen=0;
	for(int g=RedGBMerginOffset;g<MaxGB && g<256;g++){
		for(int b=RedGBMerginOffset;b<256 && b<MaxGB;b++){
			if(g<=b && g>0){
				double	a=((double)b)/((double)g);
				if(MinRedGBMerginRate<=a && a<=MaxRedGBMerginRate){
					WXLen++;
				}
			}
			else if(g>=b && b>0){
				double	a=((double)g)/((double)b);
				if(MinRedGBMerginRate<=a && a<=MaxRedGBMerginRate){
					WXLen++;
				}
			}
		}
	}

	double	aW=((double)WXLen)/((double)W);

	for(int y=0;y<H;y++){
		int	r=Clipping((int)((H-y)*aH+RedMinBrightness),0,255);
		int	MaxG=min((int)(r*ZRedHighRate),256);
		int	MaxB=min((int)(r*ZRedHighRate),256);

		int	Index=0;
		for(int g=RedGBMerginOffset;g<MaxG && g<256;g++){
			for(int b=RedGBMerginOffset;b<MaxB && b<256;b++){
				if(g<=b && g>0){
					double	a=((double)b)/((double)g);
					if(MinRedGBMerginRate<=a && a<=MaxRedGBMerginRate){
						GTable[Index]=g;
						BTable[Index]=b;
						Index++;
					}
				}
				else if(g>=b && b>0){
					double	a=((double)g)/((double)b);
					if(MinRedGBMerginRate<=a && a<=MaxRedGBMerginRate){
						GTable[Index]=g;
						BTable[Index]=b;
						Index++;
					}
				}
			}
		}

		QRgb	*d=(QRgb *)RedImage.scanLine(y);
		for(int x=0;x<W;x++){
			int	k=x*aW;
			if(0<=k && k<Index){
				d[x]=qRgb(r,GTable[k],BTable[k]);
			}
			else{
				d[x]=qRgb(0,0,0);
			}
		}
	}
}


//======================================================================================

HistgramFlatInspectionForm::HistgramFlatInspectionForm(LayersBase *Base,QWidget *parent) :
    AlgorithmComponentWindow(parent),ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
	,ui(new Ui::HistgramFlatInspectionForm)
	,SimPanel(Base,this,parent)
	,LGraphBR(parent)
	,LGraphBG(parent)
	,LGraphBB(parent)
	,LGraphNR(parent)
	,LGraphNG(parent)
	,LGraphNB(parent)
	,RedPanel(this,this)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	Preparing			=true;
	OnChanging			=false;

	HistgramPage		=-1;

	ui->tabWidgetGraph			->setCurrentIndex(0);

	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(sRoot,sName);
	SimPanel.SetGUI(/**/"Button",/**/"PropertyFlatInspection");
	SimPanel.setGeometry(0,0,ui->frame_SimImage->width(),ui->frame_SimImage->height());

	//LangSolver.SetUI(this);
	LGraphBR.setParent(ui->frameLineGraphBR);
	LGraphBR.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphBR.move(0,0);
	LGraphBR.resize(ui->frameLineGraphBR->width(),ui->frameLineGraphBR->height());

	LGraphBG.setParent(ui->frameLineGraphBG);
	LGraphBG.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphBG.move(0,0);
	LGraphBG.resize(ui->frameLineGraphBG->width(),ui->frameLineGraphBG->height());

	LGraphBB.setParent(ui->frameLineGraphBB);
	LGraphBB.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphBB.move(0,0);
	LGraphBB.resize(ui->frameLineGraphBB->width(),ui->frameLineGraphBB->height());

	LGraphNR.setParent(ui->frameLineGraphNR);
	LGraphNR.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphNR.move(0,0);
	LGraphNR.resize(ui->frameLineGraphNR->width(),ui->frameLineGraphNR->height());

	LGraphNG.setParent(ui->frameLineGraphNG);
	LGraphNG.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphNG.move(0,0);
	LGraphNG.resize(ui->frameLineGraphNG->width(),ui->frameLineGraphNG->height());

	LGraphNB.setParent(ui->frameLineGraphNB);
	LGraphNB.SetScaleTypeY(mtLineGraph::mtLog);
	LGraphNB.move(0,0);
	LGraphNB.resize(ui->frameLineGraphNB->width(),ui->frameLineGraphNB->height());

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	if(LayerNumb==1) {
		ui->frameColor->setVisible(false);
	}

	LayerBar.setParent(ui->frameLayer);
	LayerBar.move(0,0);
	LayerBar.resize(ui->frameLayer->width(),ui->frameLayer->height());
	LButtonList=new QToolButton*[LayerNumb];
	LastLayer=0;
	for(int Layer=0;Layer<LayerNumb;Layer++){
		LButtonList[Layer]=new QToolButton();
		LButtonList[Layer]->setText(QString(/**/"Ly")+QString::number(Layer));
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

	GraphColMasterBR	.SetLineColor(MasterColor);
	GraphColMasterBR	.SetLineWidth(1);
	GraphColMasterBR	.SetOffsetX(0);
	GraphColTargetBR	.SetLineColor(TargetColor);
	GraphColTargetBR	.SetLineWidth(1);
	GraphColTargetBR	.SetOffsetX(1);
	GraphThreshBR	.SetLineColor(ThreshColor);	
	GraphThreshBR	.SetLineWidth(1);
	GraphThreshBR	.SetOffsetX(2);

	GraphColMasterBG	.SetLineColor(MasterColor);
	GraphColMasterBG	.SetLineWidth(1);
	GraphColMasterBG	.SetOffsetX(0);
	GraphColTargetBG	.SetLineColor(TargetColor);
	GraphColTargetBG	.SetLineWidth(1);
	GraphColTargetBG	.SetOffsetX(1);
	GraphThreshBG	.SetLineColor(ThreshColor);	
	GraphThreshBG	.SetLineWidth(1);
	GraphThreshBG	.SetOffsetX(2);

	GraphColMasterBB	.SetLineColor(MasterColor);
	GraphColMasterBB	.SetLineWidth(1);
	GraphColMasterBB	.SetOffsetX(0);
	GraphColTargetBB	.SetLineColor(TargetColor);
	GraphColTargetBB	.SetLineWidth(1);
	GraphColTargetBB	.SetOffsetX(1);
	GraphThreshBB	.SetLineColor(ThreshColor);	
	GraphThreshBB	.SetLineWidth(1);
	GraphThreshBB	.SetOffsetX(2);

	LGraphBR.AddGraph(&GraphColMasterBR);
	LGraphBR.AddGraph(&GraphColTargetBR);
	LGraphBR.AddGraph(&GraphThreshBR);
	connect(&LGraphBR,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickBR(int ,int )));

	LGraphBG.AddGraph(&GraphColMasterBG);
	LGraphBG.AddGraph(&GraphColTargetBG);
	LGraphBG.AddGraph(&GraphThreshBG);
	connect(&LGraphBG,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickBG(int ,int )));

	LGraphBB.AddGraph(&GraphColMasterBB);
	LGraphBB.AddGraph(&GraphColTargetBB);
	LGraphBB.AddGraph(&GraphThreshBB);
	connect(&LGraphBB,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickBB(int ,int )));

	GraphColMasterNR	.SetLineColor(MasterColor);
	GraphColMasterNR	.SetLineWidth(1);
	GraphColMasterNR	.SetOffsetX(0);
	GraphColTargetNR	.SetLineColor(TargetColor);
	GraphColTargetNR	.SetLineWidth(1);
	GraphColTargetNR	.SetOffsetX(1);
	GraphThreshNR	.SetLineColor(ThreshColor);	
	GraphThreshNR	.SetLineWidth(1);
	GraphThreshNR	.SetOffsetX(2);

	GraphColMasterNG	.SetLineColor(MasterColor);
	GraphColMasterNG	.SetLineWidth(1);
	GraphColMasterNG	.SetOffsetX(0);
	GraphColTargetNG	.SetLineColor(TargetColor);
	GraphColTargetNG	.SetLineWidth(1);
	GraphColTargetNG	.SetOffsetX(1);
	GraphThreshNG	.SetLineColor(ThreshColor);	
	GraphThreshNG	.SetLineWidth(1);
	GraphThreshNG	.SetOffsetX(2);

	GraphColMasterNB	.SetLineColor(MasterColor);
	GraphColMasterNB	.SetLineWidth(1);
	GraphColMasterNB	.SetOffsetX(0);
	GraphColTargetNB	.SetLineColor(TargetColor);
	GraphColTargetNB	.SetLineWidth(1);
	GraphColTargetNB	.SetOffsetX(1);
	GraphThreshNB	.SetLineColor(ThreshColor);	
	GraphThreshNB	.SetLineWidth(1);
	GraphThreshNB	.SetOffsetX(2);

	LGraphNR.AddGraph(&GraphColMasterNR);
	LGraphNR.AddGraph(&GraphColTargetNR);
	LGraphNR.AddGraph(&GraphThreshNR);
	connect(&LGraphNR,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickNR(int ,int )));

	LGraphNG.AddGraph(&GraphColMasterNG);
	LGraphNG.AddGraph(&GraphColTargetNG);
	LGraphNG.AddGraph(&GraphThreshNG);
	connect(&LGraphNG,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickNG(int ,int )));

	LGraphNB.AddGraph(&GraphColMasterNB);
	LGraphNB.AddGraph(&GraphColTargetNB);
	LGraphNB.AddGraph(&GraphThreshNB);
	connect(&LGraphNB,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClickNB(int ,int )));


	DDRet=(connect(ui->EditOKDotB			,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditOKDotN			,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditAdjustBlack		,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditAdjustWhite		,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditSelfSearch		,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditAreaSearchX		,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditAreaSearchY		,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditMaxSelfSearch	,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditMaxAreaSearch	,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;

	IData=NULL;

	MasterPanelB	=new mtColorFrame();
	MasterPanelB->setParent(ui->frameMasterB);
	MasterPanelB->SetColor(MasterColor);
	TargetPanelB	=new mtColorFrame();
	TargetPanelB->setParent(ui->frameTargetB);
	TargetPanelB->SetColor(TargetColor);
	ThresholdPanelB	=new mtColorFrame();
	ThresholdPanelB->setParent(ui->frameThresholdB);
	ThresholdPanelB->SetColor(ThreshColor);

	MasterPanelN	=new mtColorFrame();
	MasterPanelN->setParent(ui->frameMasterN);
	MasterPanelN->SetColor(MasterColor);
	TargetPanelN	=new mtColorFrame();
	TargetPanelN->setParent(ui->frameTargetN);
	TargetPanelN->SetColor(TargetColor);
	ThresholdPanelN	=new mtColorFrame();
	ThresholdPanelN->setParent(ui->frameThresholdN);
	ThresholdPanelN->SetColor(ThreshColor);


	ui->labelResult	->setText(/**/"");

	ui->tabWidget		->setCurrentIndex(0);
	ui->tabWidgetGraph	->setCurrentIndex(0);

	RedPanel.setParent(ui->frameRedRange);
	RedPanel.move(0,0);
	RedPanel.Resize(ui->frameRedRange->width(),ui->frameRedRange->height());

	RegisterComponent((int)ID_BroadRThrOffsetL,ui->EditRThrOffsetBL);
	RegisterComponent((int)ID_BroadRThrOffsetH,ui->EditRThrOffsetBH);
	RegisterComponent((int)ID_BroadGThrOffsetL,ui->EditGThrOffsetBL);
	RegisterComponent((int)ID_BroadGThrOffsetH,ui->EditGThrOffsetBH);
	RegisterComponent((int)ID_BroadBThrOffsetL,ui->EditBThrOffsetBL);
	RegisterComponent((int)ID_BroadBThrOffsetH,ui->EditBThrOffsetBH);

	RegisterComponent((int)ID_BroadOKDot			,ui->EditOKDotB);
	RegisterComponent((int)ID_BroadOKLength			,ui->EditOKLengthB);

	RegisterComponent((int)ID_NarrowRThrOffsetL,ui->EditRThrOffsetNL);
	RegisterComponent((int)ID_NarrowRThrOffsetH,ui->EditRThrOffsetNH);
	RegisterComponent((int)ID_NarrowGThrOffsetL,ui->EditGThrOffsetNL);
	RegisterComponent((int)ID_NarrowGThrOffsetH,ui->EditGThrOffsetNH);
	RegisterComponent((int)ID_NarrowBThrOffsetL,ui->EditBThrOffsetNL);
	RegisterComponent((int)ID_NarrowBThrOffsetH,ui->EditBThrOffsetNH);

	RegisterComponent((int)ID_NarrowOKDot			,ui->EditOKDotN);
	RegisterComponent((int)ID_NarrowOKLength		,ui->EditOKLengthN);

	RegisterComponent((int)ID_SpaceToOutline	,ui->EditSpaceToOutline);
	RegisterComponent((int)ID_ExpansionRange	,ui->doubleSpinBoxExpansionRange);
	RegisterComponent((int)ID_MerginForSpecial	,ui->EditMerginForSpecial);

	RegisterComponent((int)ID_AdjustBlack		,ui->EditAdjustBlack);
	RegisterComponent((int)ID_AdjustWhite		,ui->EditAdjustWhite);
	RegisterComponent((int)ID_BackGroundOKDot	,ui->EditBackGroundOKDot);
	RegisterComponent((int)ID_BackGroundOKLength,ui->EditBackGroundOKLength);
	RegisterComponent((int)ID_UseBackGround		,ui->checkBoxUseBackGround);
	RegisterComponent((int)ID_DivLenX			,ui->EditDivLenX);
	RegisterComponent((int)ID_DivLenY			,ui->EditDivLenY);

	RegisterComponent((int)ID_AreaSearchX	,ui->EditAreaSearchX);
	RegisterComponent((int)ID_AreaSearchY	,ui->EditAreaSearchY);
	RegisterComponent((int)ID_SelfSearch	,ui->EditSelfSearch);
	RegisterComponent((int)ID_MaxAreaSearch	,ui->EditMaxAreaSearch);
	RegisterComponent((int)ID_MaxSelfSearch	,ui->EditMaxSelfSearch);

	RegisterComponent((int)ID_MultiSpotDot	,ui->EditMultiSpotDot);
	RegisterComponent((int)ID_MultiSpotCount,ui->EditMultiSpotCount);
	RegisterComponent((int)ID_MultiSpotDotGathered		,ui->EditMultiSpotDotGathered);
	RegisterComponent((int)ID_MultiSpotCountGathered	,ui->EditMultiSpotCountGathered);
	RegisterComponent((int)ID_MultiSpotLengthGathered	,ui->EditMultiSpotLengthGathered);

	RegisterComponent((int)ID_RedCheckMode			,ui->checkBoxRedCheckMode);
	RegisterComponent((int)ID_RedHighRate			,ui->EditRedHighRate);
	RegisterComponent((int)ID_RedMinBrightness		,ui->EditRedMinBrightness);
	RegisterComponent((int)ID_RedGBMerginRate		,ui->EditRedGBMerginRate);
	RegisterComponent((int)ID_RedGBMerginOffset		,ui->EditRedGBMerginOffset);
	RegisterComponent((int)ID_RedOKDot				,ui->EditRedOKDot);
	RegisterComponent((int)ID_RedShrink				,ui->EditRedShrink);

	RegisterComponent((int)ID_VariationMode			,ui->checkBoxVariationMode		);
	RegisterComponent((int)ID_VariationRL			,ui->doubleSpinBoxVariationRL	);
	RegisterComponent((int)ID_VariationRH			,ui->doubleSpinBoxVariationRH	);
	RegisterComponent((int)ID_VariationGL			,ui->doubleSpinBoxVariationGL	);
	RegisterComponent((int)ID_VariationGH			,ui->doubleSpinBoxVariationGH	);
	RegisterComponent((int)ID_VariationBL			,ui->doubleSpinBoxVariationBL	);
	RegisterComponent((int)ID_VariationBH			,ui->doubleSpinBoxVariationBH	);
	RegisterComponent((int)ID_VariationAdaptMinSize	,ui->EditVariationAdaptMinSize	);
	RegisterComponent((int)ID_VariationMultiplyMaster,ui->doubleSpinBoxVariationMultiplyMaster	);
	RegisterComponent((int)ID_VariationDifMaster	,ui->checkBoxVariationDifMaster	);
	RegisterComponent((int)ID_VariationAndLogic		,ui->checkBoxVariationAndLogic	);
	RegisterComponent((int)ID_VariationSubMasterVari,ui->doubleSpinBoxVariationSubMasterVari	);

	RegisterComponent((int)ID_LineMode				,ui->checkBoxLineMode			);
	RegisterComponent((int)ID_LineOKMinLength		,ui->EditLineOKMinLength		);
	RegisterComponent((int)ID_LineMaxWidth			,ui->EditLineMaxWidth			);
	RegisterComponent((int)ID_LineMinDensityPercent	,ui->EditLineMinDensityPercent	);
	RegisterComponent((int)ID_LineMinCluster		,ui->EditLineMinCluster			);

	on_toolButtonBroad_clicked();
	SetupPassword();
	InstallOperationLog(this);
}
HistgramFlatInspectionForm::~HistgramFlatInspectionForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	delete	[]LButtonList;
	LButtonList=NULL;
	Preparing=true;
}
void	HistgramFlatInspectionForm::showEvent ( QShowEvent * event )
{
	Preparing=false;
	on_ButtonCalc_clicked();
}
void	HistgramFlatInspectionForm::GetActiveLayerList(IntList &LayerList)
{
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int Layer=0;Layer<LayerNumb;Layer++){
		if(LButtonList[Layer]->isChecked()==true){
			LayerList.Add(Layer);
		}
	}
}

void	HistgramFlatInspectionForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		LButtonList[D->Layer]->setChecked(true);
		//SimPanel.SetLayer(D->Layer);
		SimPanel.SetLayer(-1);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
			if(BData!=NULL){
				HistgramPage	=D->GlobalPage;
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock		(ui->toolButtonSimShowItem ->isChecked());
				ModeShowItem	=ui->toolButtonSimShowItem ->isChecked();
			}
		}
	}
	if(IData->Items.GetCount()>1){
		ui->ButtonReflectAllFlatInspections->setVisible(false);
	}
	else{
		ui->ButtonReflectAllFlatInspections->setVisible(true);
	}

	SimPanel.SetZoomRate(2.0);
	SimPanel.SetCenter(Data.LocalX,Data.LocalY);

	SetEnableChangeMode(false);

	CreateThreshld();
	ShowHistgramList();
	on_ButtonCalc_clicked();
	ShowRed();
	ui->doubleSpinBoxOKDotBMM	 ->setValue(TransformPixelToUnitSquare	(HistgramPage,ui->EditOKDotB		->value()));
	ui->doubleSpinBoxOKLengthBMM		->setValue(TransformPixelToUnit	(HistgramPage,ui->EditOKLengthB		->value()));
	ui->doubleSpinBoxOKDotNMM	 ->setValue(TransformPixelToUnitSquare	(HistgramPage,ui->EditOKDotN		->value()));
	ui->doubleSpinBoxOKLengthNMM		->setValue(TransformPixelToUnit	(HistgramPage,ui->EditOKLengthN		->value()));
	ui->doubleSpinBoxAreaSearchXMM	->setValue(TransformPixelToUnit		(HistgramPage,ui->EditAreaSearchX	->value()));
	ui->doubleSpinBoxAreaSearchYMM	->setValue(TransformPixelToUnit		(HistgramPage,ui->EditAreaSearchY	->value()));
	ui->doubleSpinBoxSelfSearchMM	->setValue(TransformPixelToUnit		(HistgramPage,ui->EditSelfSearch	->value()));
	ui->doubleSpinBoxBackGroundOKDotMM	 ->setValue(TransformPixelToUnitSquare	(HistgramPage,ui->EditBackGroundOKDot->value()));
	ui->doubleSpinBoxBackGroundOKLengthMM->setValue(TransformPixelToUnit		(HistgramPage,ui->EditBackGroundOKLength->value()));
	SetEnableChangeMode(true);
}

void	HistgramFlatInspectionForm::ShowHistgramList(void)
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		
		BData->TF_EnumHistList(HContainer);
		for(HistgramTypeListInAlgo *a=HContainer.GetFirst();a!=NULL;a=a->GetNext()){
			ui->listWidgetHistList->addItem(a->HistName);
		}
		return;
	}
}

void	HistgramFlatInspectionForm::CreateThreshld(void)
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,FlatInspectionReqThresholdReqCommand ,FlatInspectionReqThresholdSendCommand);
		((FlatInspectionThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((FlatInspectionThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((FlatInspectionThresholdReq *)PacketReq.Data)->FlatInspectionItemID	=DA->GetID();
		((FlatInspectionThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			FlatInspectionThresholdSend	*ThrePoint=(FlatInspectionThresholdSend *)PacketSend.GetData();
			CenterBrightR		=ThrePoint->ThresholdValues.CenterBrightR;
			CenterTargetBrightR	=ThrePoint->ThresholdValues.CenterTargetBrightR;
			CenterBrightG		=ThrePoint->ThresholdValues.CenterBrightG;
			CenterTargetBrightG	=ThrePoint->ThresholdValues.CenterTargetBrightG;
			CenterBrightB		=ThrePoint->ThresholdValues.CenterBrightB;
			CenterTargetBrightB	=ThrePoint->ThresholdValues.CenterTargetBrightB;

			break;
		}
	}

	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
	LGraphBR.repaint();
	LGraphBG.repaint();
	LGraphBB.repaint();
	LGraphNR.repaint();
	LGraphNG.repaint();
	LGraphNB.repaint();
}

void HistgramFlatInspectionForm::GetHistogramData(void)
{
	GraphColMasterBR.DeleteXY();
	GraphColMasterBG.DeleteXY();
	GraphColMasterBB.DeleteXY();
	GraphColTargetBR.DeleteXY();
	GraphColTargetBG.DeleteXY();
	GraphColTargetBB.DeleteXY();

	GraphColMasterNR.DeleteXY();
	GraphColMasterNG.DeleteXY();
	GraphColMasterNB.DeleteXY();
	GraphColTargetNR.DeleteXY();
	GraphColTargetNG.DeleteXY();
	GraphColTargetNB.DeleteXY();

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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,FlatInspectionHistogramListReqCommand ,FlatInspectionHistogramListSendCommand);
		((FlatInspectionHistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((FlatInspectionHistogramListReq *)PacketReq.Data)->Layer=D->Layer;
		((FlatInspectionHistogramListReq *)PacketReq.Data)->FlatInspectionItemID	=DA->GetID();
		((FlatInspectionHistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			FlatInspectionHistogramListSend	*L=(FlatInspectionHistogramListSend *)PacketSend.GetData();
			YMaxR=0;
			for(int i=0;i<256;i++){
				YMaxR=max(YMaxR,L->ListMasterR[i]);
				YMaxR=max(YMaxR,L->ListTargetR[i]);
				GraphColMasterBR.AddXY(i		,L->ListMasterR[i]);
				GraphColTargetBR.AddXY(i+0.5	,L->ListTargetR[i]);
				GraphColMasterNR.AddXY(i		,L->ListMasterR[i]);
				GraphColTargetNR.AddXY(i+0.5	,L->ListTargetR[i]);
			}
			YMaxG=0;
			for(int i=0;i<256;i++){
				YMaxG=max(YMaxG,L->ListMasterG[i]);
				YMaxG=max(YMaxG,L->ListTargetG[i]);
				GraphColMasterBG.AddXY(i		,L->ListMasterG[i]);
				GraphColTargetBG.AddXY(i+0.5	,L->ListTargetG[i]);
				GraphColMasterNG.AddXY(i		,L->ListMasterG[i]);
				GraphColTargetNG.AddXY(i+0.5	,L->ListTargetG[i]);
			}
			YMaxB=0;
			for(int i=0;i<256;i++){
				YMaxB=max(YMaxB,L->ListMasterB[i]);
				YMaxB=max(YMaxB,L->ListTargetB[i]);
				GraphColMasterBB.AddXY(i		,L->ListMasterB[i]);
				GraphColTargetBB.AddXY(i+0.5	,L->ListTargetB[i]);
				GraphColMasterNB.AddXY(i		,L->ListMasterB[i]);
				GraphColTargetNB.AddXY(i+0.5	,L->ListTargetB[i]);
			}
			ui->EditCenterBrightMasterBR	->setText(QString::number(L->CenterBrightR));
			ui->EditCenterBrightMasterBG	->setText(QString::number(L->CenterBrightG));
			ui->EditCenterBrightMasterBB	->setText(QString::number(L->CenterBrightB));
			ui->EditCenterBrightTargetBR	->setText(QString::number(L->CenterTargetBrightR));
			ui->EditCenterBrightTargetBG	->setText(QString::number(L->CenterTargetBrightG));
			ui->EditCenterBrightTargetBB	->setText(QString::number(L->CenterTargetBrightB));

			ui->EditCenterBrightMasterNR	->setText(QString::number(L->CenterBrightR));
			ui->EditCenterBrightMasterNG	->setText(QString::number(L->CenterBrightG));
			ui->EditCenterBrightMasterNB	->setText(QString::number(L->CenterBrightB));
			ui->EditCenterBrightTargetNR	->setText(QString::number(L->CenterTargetBrightR));
			ui->EditCenterBrightTargetNG	->setText(QString::number(L->CenterTargetBrightG));
			ui->EditCenterBrightTargetNB	->setText(QString::number(L->CenterTargetBrightB));
			return;
		}
	}
}


void	HistgramFlatInspectionForm::ShowLibrary(void)
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
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
		//OnChanging=true;
		ui->EditItemName		->setText(BData->GetItemName());

		const	FlatInspectionThreshold	*RThr=BData->GetThresholdR(GetLayersBase());
		ShowLibrary(RThr);

		if(BData->IsOriginParts()==true){
			ui->stackedWidgetParts->setCurrentIndex(1);
		}
		else{
			ui->stackedWidgetParts->setCurrentIndex(0);
		}
		on_ButtonCalc_clicked();
	}
}

void	HistgramFlatInspectionForm::ShowLibrary(const	FlatInspectionThreshold *RThr)
{
	ui->EditOKDotB			->setValue	(RThr->Broad.OKDot);
	ui->EditOKLengthB		->setValue	(RThr->Broad.OKLength);
	ui->EditRThrOffsetBL	->setValue	(RThr->Broad.RThrOffsetL);
	ui->EditRThrOffsetBH	->setValue	(RThr->Broad.RThrOffsetH);
	ui->EditGThrOffsetBL	->setValue	(RThr->Broad.GThrOffsetL);
	ui->EditGThrOffsetBH	->setValue	(RThr->Broad.GThrOffsetH);
	ui->EditBThrOffsetBL	->setValue	(RThr->Broad.BThrOffsetL);
	ui->EditBThrOffsetBH	->setValue	(RThr->Broad.BThrOffsetH);

	ui->EditOKDotN			->setValue	(RThr->Narrow.OKDot);
	ui->EditOKLengthN		->setValue	(RThr->Narrow.OKLength);
	ui->EditRThrOffsetNL	->setValue	(RThr->Narrow.RThrOffsetL);
	ui->EditRThrOffsetNH	->setValue	(RThr->Narrow.RThrOffsetH);
	ui->EditGThrOffsetNL	->setValue	(RThr->Narrow.GThrOffsetL);
	ui->EditGThrOffsetNH	->setValue	(RThr->Narrow.GThrOffsetH);
	ui->EditBThrOffsetNL	->setValue	(RThr->Narrow.BThrOffsetL);
	ui->EditBThrOffsetNH	->setValue	(RThr->Narrow.BThrOffsetH);

	ui->EditSpaceToOutline	->setValue	(RThr->SpaceToOutline);
	ui->doubleSpinBoxExpansionRange	->setValue(RThr->ExpansionRange);
	ui->EditMerginForSpecial->setValue	(RThr->MerginForSpecial);

	ui->EditBackGroundOKDot		->setValue	(RThr->BackGroundOKDot);
	ui->EditBackGroundOKLength	->setValue	(RThr->BackGroundOKLength);
	ui->checkBoxUseBackGround	->setChecked(RThr->UseBackGround);
	ui->EditDivLenX		->setValue	(RThr->DivLenX);
	ui->EditDivLenY		->setValue	(RThr->DivLenY);

	ui->EditAdjustBlack		->setValue	(RThr->AdjustBlack);
	ui->EditAdjustWhite		->setValue	(RThr->AdjustWhite);
	ui->EditSelfSearch		->setValue	(RThr->SelfSearch);
	ui->EditAreaSearchX		->setValue	(RThr->AreaSearchX);
	ui->EditAreaSearchY		->setValue	(RThr->AreaSearchY);
	ui->EditMaxSelfSearch	->setValue	(RThr->MaxSelfSearch);
	ui->EditMaxAreaSearch	->setValue	(RThr->MaxAreaSearch);
	ui->EditMultiSpotDot	->setValue	(RThr->MultiSpotDot	);
	ui->EditMultiSpotCount	->setValue	(RThr->MultiSpotCount);
	ui->EditMultiSpotDotGathered	->setValue(RThr->MultiSpotDotGathered	);
	ui->EditMultiSpotCountGathered	->setValue(RThr->MultiSpotCountGathered);
	ui->EditMultiSpotLengthGathered	->setValue(RThr->MultiSpotLengthGathered);

	ui->checkBoxRedCheckMode			->setChecked(RThr->RedCheckMode			);
	ui->EditRedHighRate					->setValue	(RThr->RedHighRate			);
	ui->EditRedMinBrightness			->setValue	(RThr->RedMinBrightness		);
	ui->EditRedGBMerginRate				->setValue	(RThr->RedGBMerginRate		);
	ui->EditRedGBMerginOffset			->setValue	(RThr->RedGBMerginOffset	);
	ui->EditRedOKDot					->setValue	(RThr->RedOKDot				);
	ui->EditRedShrink					->setValue	(RThr->RedShrink			);

	ui->checkBoxVariationMode		->setChecked(RThr->VariationMode);
	ui->doubleSpinBoxVariationRL	->setValue(RThr->VariationRL);
	ui->doubleSpinBoxVariationRH	->setValue(RThr->VariationRH);
	ui->doubleSpinBoxVariationGL	->setValue(RThr->VariationGL);
	ui->doubleSpinBoxVariationGH	->setValue(RThr->VariationGH);
	ui->doubleSpinBoxVariationBL	->setValue(RThr->VariationBL);
	ui->doubleSpinBoxVariationBH	->setValue(RThr->VariationBH);
	ui->EditVariationAdaptMinSize	->setValue(RThr->VariationAdaptMinSize);
	ui->doubleSpinBoxVariationMultiplyMaster->setValue(RThr->VariationMultiplyMaster);
	ui->checkBoxVariationDifMaster	->setChecked(RThr->VariationDifMaster);
	ui->checkBoxVariationAndLogic	->setChecked(RThr->VariationAndLogic);
	ui->doubleSpinBoxVariationSubMasterVari->setValue(RThr->VariationSubMasterVari);

	ui->checkBoxLineMode			->setChecked(RThr->LineMode				);
	ui->EditLineOKMinLength			->setValue(RThr->LineOKMinLength		);
	ui->EditLineMaxWidth			->setValue(RThr->LineMaxWidth			);
	ui->EditLineMinDensityPercent	->setValue(RThr->LineMinDensityPercent	);
	ui->EditLineMinCluster			->setValue(RThr->LineMinCluster			);
}

void HistgramFlatInspectionForm::ShowThreshold(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GraphThreshBR.DeleteXY();
	GraphThreshBG.DeleteXY();
	GraphThreshBB.DeleteXY();
	GraphThreshNR.DeleteXY();
	GraphThreshNG.DeleteXY();
	GraphThreshNB.DeleteXY();


	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			return;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		int	CDiffR=CenterTargetBrightR-CenterBrightR;
		if(CDiffR>0){
			if(CDiffR>BData->GetThresholdR(GetLayersBase())->AdjustWhite){
				CDiffR=BData->GetThresholdR(GetLayersBase())->AdjustWhite;
			}
		}
		else if(CDiffR<0){
			if(-CDiffR>BData->GetThresholdR(GetLayersBase())->AdjustBlack){
				CDiffR=-BData->GetThresholdR(GetLayersBase())->AdjustBlack;
			}
		}

		int	CDiffG=CenterTargetBrightG-CenterBrightG;
		if(CDiffG>0){
			if(CDiffG>BData->GetThresholdR(GetLayersBase())->AdjustWhite){
				CDiffG=BData->GetThresholdR(GetLayersBase())->AdjustWhite;
			}
		}
		else if(CDiffG<0){
			if(-CDiffG>BData->GetThresholdR(GetLayersBase())->AdjustBlack){
				CDiffG=-BData->GetThresholdR(GetLayersBase())->AdjustBlack;
			}
		}

		int	CDiffB=CenterTargetBrightB-CenterBrightB;
		if(CDiffB>0){
			if(CDiffB>BData->GetThresholdR(GetLayersBase())->AdjustWhite){
				CDiffB=BData->GetThresholdR(GetLayersBase())->AdjustWhite;
			}
		}
		else if(CDiffB<0){
			if(-CDiffB>BData->GetThresholdR(GetLayersBase())->AdjustBlack){
				CDiffB=-BData->GetThresholdR(GetLayersBase())->AdjustBlack;
			}
		}
		const	FlatInspectionThreshold	*RThr=BData->GetThresholdR(GetLayersBase());
		GraphThreshBR.AddXY(CenterBrightR+CDiffR-RThr->Broad.RThrOffsetL,YMaxR);
		GraphThreshBR.AddXY(CenterBrightR+CDiffR+RThr->Broad.RThrOffsetH,YMaxR);
		GraphThreshBG.AddXY(CenterBrightG+CDiffG-RThr->Broad.GThrOffsetL,YMaxG);
		GraphThreshBG.AddXY(CenterBrightG+CDiffG+RThr->Broad.GThrOffsetH,YMaxG);
		GraphThreshBB.AddXY(CenterBrightB+CDiffB-RThr->Broad.BThrOffsetL,YMaxB);
		GraphThreshBB.AddXY(CenterBrightB+CDiffB+RThr->Broad.BThrOffsetH,YMaxB);

		GraphThreshNR.AddXY(CenterBrightR+CDiffR-RThr->Narrow.RThrOffsetL,YMaxR);
		GraphThreshNR.AddXY(CenterBrightR+CDiffR+RThr->Narrow.RThrOffsetH,YMaxR);
		GraphThreshNG.AddXY(CenterBrightG+CDiffG-RThr->Narrow.GThrOffsetL,YMaxG);
		GraphThreshNG.AddXY(CenterBrightG+CDiffG+RThr->Narrow.GThrOffsetH,YMaxG);
		GraphThreshNB.AddXY(CenterBrightB+CDiffB-RThr->Narrow.BThrOffsetL,YMaxB);
		GraphThreshNB.AddXY(CenterBrightB+CDiffB+RThr->Narrow.BThrOffsetH,YMaxB);

		return;
	}
}
void	HistgramFlatInspectionForm::GetDataFromWindow(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GetDataFromWindowFromNo(LayerList.GetFirst()->GetValue());
}
void	HistgramFlatInspectionForm::GetDataFromWindowFromNo(int LayerNo)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerNo!=D->Layer)
			continue;
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		BData->SetItemName(ui->EditItemName	->text());
		FlatInspectionThreshold	*DThr=BData->GetThresholdW(GetLayersBase());
		DThr->Broad.OKDot				=ui->EditOKDotB				->value();
		DThr->Broad.OKLength			=ui->EditOKLengthB			->value();
		DThr->Broad.RThrOffsetL			=ui->EditRThrOffsetBL	->value();
		DThr->Broad.RThrOffsetH			=ui->EditRThrOffsetBH	->value();
		DThr->Broad.GThrOffsetL			=ui->EditGThrOffsetBL	->value();
		DThr->Broad.GThrOffsetH			=ui->EditGThrOffsetBH	->value();
		DThr->Broad.BThrOffsetL			=ui->EditBThrOffsetBL	->value();
		DThr->Broad.BThrOffsetH			=ui->EditBThrOffsetBH	->value();

		DThr->Narrow.OKDot				=ui->EditOKDotN			->value();
		DThr->Narrow.OKLength			=ui->EditOKLengthN		->value();
		DThr->Narrow.RThrOffsetL		=ui->EditRThrOffsetNL	->value();
		DThr->Narrow.RThrOffsetH		=ui->EditRThrOffsetNH	->value();
		DThr->Narrow.GThrOffsetL		=ui->EditGThrOffsetNL	->value();
		DThr->Narrow.GThrOffsetH		=ui->EditGThrOffsetNH	->value();
		DThr->Narrow.BThrOffsetL		=ui->EditBThrOffsetNL	->value();
		DThr->Narrow.BThrOffsetH		=ui->EditBThrOffsetNH	->value();

		DThr->SpaceToOutline	=ui->EditSpaceToOutline			->value();
		DThr->ExpansionRange	=ui->doubleSpinBoxExpansionRange->value();
		DThr->MerginForSpecial	=ui->EditMerginForSpecial	->value();

		DThr->BackGroundOKDot	=ui->EditBackGroundOKDot	->value();
		DThr->BackGroundOKLength=ui->EditBackGroundOKLength	->value();
		DThr->UseBackGround		=ui->checkBoxUseBackGround	->isChecked();
		DThr->DivLenX			=ui->EditDivLenX		->value	();
		DThr->DivLenY			=ui->EditDivLenY		->value	();

		DThr->AdjustBlack		=ui->EditAdjustBlack	->value();
		DThr->AdjustWhite		=ui->EditAdjustWhite	->value();
		DThr->AreaSearchX		=ui->EditAreaSearchX	->value();
		DThr->AreaSearchY		=ui->EditAreaSearchY	->value();
		DThr->SelfSearch		=ui->EditSelfSearch		->value();
		DThr->MaxAreaSearch		=ui->EditMaxAreaSearch	->value();
		DThr->MaxSelfSearch		=ui->EditMaxSelfSearch	->value();
		DThr->MultiSpotDot		=ui->EditMultiSpotDot	->value();
		DThr->MultiSpotCount	=ui->EditMultiSpotCount	->value();
		DThr->MultiSpotDotGathered		=ui->EditMultiSpotDotGathered	->value();
		DThr->MultiSpotCountGathered	=ui->EditMultiSpotCountGathered	->value();
		DThr->MultiSpotLengthGathered	=ui->EditMultiSpotLengthGathered->value();
		
		DThr->RedCheckMode			=ui->checkBoxRedCheckMode				->isChecked();
		DThr->RedHighRate			=ui->EditRedHighRate					->value	();
		DThr->RedMinBrightness		=ui->EditRedMinBrightness				->value	();
		DThr->RedGBMerginRate		=ui->EditRedGBMerginRate				->value	();
		DThr->RedGBMerginOffset		=ui->EditRedGBMerginOffset				->value	();
		DThr->RedOKDot				=ui->EditRedOKDot						->value	();
		DThr->RedShrink				=ui->EditRedShrink						->value	();

		DThr->VariationMode	=ui->checkBoxVariationMode		->isChecked();
		DThr->VariationRL	=ui->doubleSpinBoxVariationRL	->value();
		DThr->VariationRH	=ui->doubleSpinBoxVariationRH	->value();
		DThr->VariationGL	=ui->doubleSpinBoxVariationGL	->value();
		DThr->VariationGH	=ui->doubleSpinBoxVariationGH	->value();
		DThr->VariationBL	=ui->doubleSpinBoxVariationBL	->value();
		DThr->VariationBH	=ui->doubleSpinBoxVariationBH	->value();
		DThr->VariationAdaptMinSize		=ui->EditVariationAdaptMinSize->value();
		DThr->VariationMultiplyMaster	=ui->doubleSpinBoxVariationMultiplyMaster->value();
		DThr->VariationDifMaster		=ui->checkBoxVariationDifMaster	->isChecked();
		DThr->VariationAndLogic			=ui->checkBoxVariationAndLogic	->isChecked();
		DThr->VariationSubMasterVari	=ui->doubleSpinBoxVariationSubMasterVari->value();

		DThr->LineMode				=ui->checkBoxLineMode			->isChecked();
		DThr->LineOKMinLength		=ui->EditLineOKMinLength		->value();
		DThr->LineMaxWidth			=ui->EditLineMaxWidth			->value();
		DThr->LineMinDensityPercent	=ui->EditLineMinDensityPercent	->value();
		DThr->LineMinCluster		=ui->EditLineMinCluster			->value();
	}
}

void	HistgramFlatInspectionForm::SlotLineGraphDClickBR(int X,int Y)
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		int	CDiffR=CenterTargetBrightR-CenterBrightR;
		if(CDiffR>0){
			if(CDiffR>BData->GetThresholdR(GetLayersBase())->AdjustWhite){
				CDiffR=BData->GetThresholdR(GetLayersBase())->AdjustWhite;
			}
		}
		else if(CDiffR<0){
			if(-CDiffR>BData->GetThresholdR(GetLayersBase())->AdjustBlack){
				CDiffR=-BData->GetThresholdR(GetLayersBase())->AdjustBlack;
			}
		}

		//FlatInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		//if(ui->radioButtonDarkSide1->isChecked()==true){
		//	if(CenterBrightR!=0 && (CenterBrightR+CDiffR-X)>=0){
		//		Thr->Broad.BrightWidthRL=(CenterBrightR+CDiffR-X)*100/CenterBrightR;
		//		ui->EditBrightWidthBRL->setValue(Thr->Broad.BrightWidthRL);
		//		ShowThreshold();
		//	}
		//}
		//else{
		//	if(CenterBrightR!=0 && (X-(CenterBrightR+CDiffR))>=0){
		//		Thr->Broad.BrightWidthRH=(X-(CenterBrightR+CDiffR))*100/CenterBrightR;
		//		ui->EditBrightWidthBRH->setValue(Thr->Broad.BrightWidthRH);
		//		ShowThreshold();
		//	}
		//}
		on_ButtonCalc_clicked();
		LGraphBR.repaint();
		return;
	}
}

void	HistgramFlatInspectionForm::SlotLineGraphDClickBG(int X,int Y)
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		FlatInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		int	CDiffG=CenterTargetBrightG-CenterBrightG;
		if(CDiffG>0){
			if(CDiffG>BData->GetThresholdR(GetLayersBase())->AdjustWhite){
				CDiffG=BData->GetThresholdR(GetLayersBase())->AdjustWhite;
			}
		}
		else if(CDiffG<0){
			if(-CDiffG>BData->GetThresholdR(GetLayersBase())->AdjustBlack){
				CDiffG=-BData->GetThresholdR(GetLayersBase())->AdjustBlack;
			}
		}

		//if(ui->radioButtonDarkSide1->isChecked()==true){
		//	if(CenterBrightG!=0 && (CenterBrightG+CDiffG-X)>=0){
		//		Thr->Broad.BrightWidthGL=(CenterBrightG+CDiffG-X)*100/CenterBrightG;
		//		ui->EditBrightWidthBGL->setValue(Thr->Broad.BrightWidthGL);
		//		ShowThreshold();
		//	}
		//}
		//else{
		//	if(CenterBrightG!=0 && (X-(CenterBrightG+CDiffG))>=0){
		//		Thr->Broad.BrightWidthGH=(X-(CenterBrightG+CDiffG))*100/CenterBrightG;
		//		ui->EditBrightWidthBGH->setValue(Thr->Broad.BrightWidthGH);
		//		ShowThreshold();
		//	}
		//}
		on_ButtonCalc_clicked();
		LGraphBG.repaint();
		return;
	}
}

void	HistgramFlatInspectionForm::SlotLineGraphDClickBB(int X,int Y)
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		FlatInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		int	CDiffB=CenterTargetBrightB-CenterBrightB;
		if(CDiffB>0){
			if(CDiffB>BData->GetThresholdR(GetLayersBase())->AdjustWhite){
				CDiffB=BData->GetThresholdR(GetLayersBase())->AdjustWhite;
			}
		}
		else if(CDiffB<0){
			if(-CDiffB>BData->GetThresholdR(GetLayersBase())->AdjustBlack){
				CDiffB=-BData->GetThresholdR(GetLayersBase())->AdjustBlack;
			}
		}		

		//if(ui->radioButtonDarkSide1->isChecked()==true){
		//	if(CenterBrightB!=0 && (CenterBrightB+CDiffB-X)>=0){
		//		Thr->Broad.BrightWidthBL=(CenterBrightB+CDiffB-X)*100/CenterBrightB;
		//		ui->EditBrightWidthBBL->setValue(Thr->Broad.BrightWidthBL);
		//		ShowThreshold();
		//	}
		//}
		//else{
		//	if(CenterBrightB!=0 && (X-(CenterBrightB+CDiffB))>=0){
		//		Thr->Broad.BrightWidthBH=(X-(CenterBrightB+CDiffB))*100/CenterBrightB;
		//		ui->EditBrightWidthBBH->setValue(Thr->Broad.BrightWidthBH);
		//		ShowThreshold();
		//	}
		//}
		on_ButtonCalc_clicked();
		LGraphBB.repaint();
		return;
	}
}

void	HistgramFlatInspectionForm::SlotLineGraphDClickNR(int X,int Y)
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		int	CDiffR=CenterTargetBrightR-CenterBrightR;
		if(CDiffR>0){
			if(CDiffR>BData->GetThresholdR(GetLayersBase())->AdjustWhite){
				CDiffR=BData->GetThresholdR(GetLayersBase())->AdjustWhite;
			}
		}
		else if(CDiffR<0){
			if(-CDiffR>BData->GetThresholdR(GetLayersBase())->AdjustBlack){
				CDiffR=-BData->GetThresholdR(GetLayersBase())->AdjustBlack;
			}
		}

		//FlatInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		//if(ui->radioButtonDarkSide1->isChecked()==true){
		//	if(CenterBrightR!=0 && (CenterBrightR+CDiffR-X)>=0){
		//		Thr->Narrow.BrightWidthRL=(CenterBrightR+CDiffR-X)*100/CenterBrightR;
		//		ui->EditBrightWidthNRL->setValue(Thr->Narrow.BrightWidthRL);
		//		ShowThreshold();
		//	}
		//}
		//else{
		//	if(CenterBrightR!=0 && (X-(CenterBrightR+CDiffR))>=0){
		//		Thr->Narrow.BrightWidthRH=(X-(CenterBrightR+CDiffR))*100/CenterBrightR;
		//		ui->EditBrightWidthNRH->setValue(Thr->Narrow.BrightWidthRH);
		//		ShowThreshold();
		//	}
		//}
		on_ButtonCalc_clicked();
		LGraphNR.repaint();
		return;
	}
}

void	HistgramFlatInspectionForm::SlotLineGraphDClickNG(int X,int Y)
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		FlatInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		int	CDiffG=CenterTargetBrightG-CenterBrightG;
		if(CDiffG>0){
			if(CDiffG>BData->GetThresholdR(GetLayersBase())->AdjustWhite){
				CDiffG=BData->GetThresholdR(GetLayersBase())->AdjustWhite;
			}
		}
		else if(CDiffG<0){
			if(-CDiffG>BData->GetThresholdR(GetLayersBase())->AdjustBlack){
				CDiffG=-BData->GetThresholdR(GetLayersBase())->AdjustBlack;
			}
		}

		//if(ui->radioButtonDarkSide1->isChecked()==true){
		//	if(CenterBrightG!=0 && (CenterBrightG+CDiffG-X)>=0){
		//		Thr->Narrow.BrightWidthGL=(CenterBrightG+CDiffG-X)*100/CenterBrightG;
		//		ui->EditBrightWidthNGL->setValue(Thr->Narrow.BrightWidthGL);
		//		ShowThreshold();
		//	}
		//}
		//else{
		//	if(CenterBrightG!=0 && (X-(CenterBrightG+CDiffG))>=0){
		//		Thr->Narrow.BrightWidthGH=(X-(CenterBrightG+CDiffG))*100/CenterBrightG;
		//		ui->EditBrightWidthNGH->setValue(Thr->Narrow.BrightWidthGH);
		//		ShowThreshold();
		//	}
		//}
		on_ButtonCalc_clicked();
		LGraphNG.repaint();
		return;
	}
}

void	HistgramFlatInspectionForm::SlotLineGraphDClickNB(int X,int Y)
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		FlatInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		int	CDiffB=CenterTargetBrightB-CenterBrightB;
		if(CDiffB>0){
			if(CDiffB>BData->GetThresholdR(GetLayersBase())->AdjustWhite){
				CDiffB=BData->GetThresholdR(GetLayersBase())->AdjustWhite;
			}
		}
		else if(CDiffB<0){
			if(-CDiffB>BData->GetThresholdR(GetLayersBase())->AdjustBlack){
				CDiffB=-BData->GetThresholdR(GetLayersBase())->AdjustBlack;
			}
		}		

		//if(ui->radioButtonDarkSide1->isChecked()==true){
		//	if(CenterBrightB!=0 && (CenterBrightB+CDiffB-X)>=0){
		//		Thr->Narrow.BrightWidthBL=(CenterBrightB+CDiffB-X)*100/CenterBrightB;
		//		ui->EditBrightWidthNBL->setValue(Thr->Narrow.BrightWidthBL);
		//		ShowThreshold();
		//	}
		//}
		//else{
		//	if(CenterBrightB!=0 && (X-(CenterBrightB+CDiffB))>=0){
		//		Thr->Narrow.BrightWidthBH=(X-(CenterBrightB+CDiffB))*100/CenterBrightB;
		//		ui->EditBrightWidthNBH->setValue(Thr->Narrow.BrightWidthBH);
		//		ShowThreshold();
		//	}
		//}
		on_ButtonCalc_clicked();
		LGraphNB.repaint();
		return;
	}
}
void	HistgramFlatInspectionForm::SlotLayerClicked()
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
}
void HistgramFlatInspectionForm::on_ButtonRelrectOnlyFlatInspection_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE FlatInspection threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one FlatInspection threshold");
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

void HistgramFlatInspectionForm::on_ButtonReflectAllFlatInspections_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL FlatInspections\' threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all FlatInspections threshold");
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
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void HistgramFlatInspectionForm::on_ButtonSaveToLibrary_clicked()
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	LLib(Container);
		if(Container->GetLibrary(LibID ,LLib)==true){
			FlatInspectionLibrary	*ALib=dynamic_cast<FlatInspectionLibrary *>(LLib.GetLibrary(ThresholdLevel));
			FlatInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			Container->Update(LLib);
			return;
		}
	}
}

void HistgramFlatInspectionForm::on_ButtonLoadFromLibrary_clicked()
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	LLib(Container);
		if(Container->GetLibrary(LibID ,LLib)==true){
			FlatInspectionLibrary	*ALib=dynamic_cast<FlatInspectionLibrary *>(LLib.GetLibrary(ThresholdLevel));
			FlatInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			return;
		}
	}
}

void HistgramFlatInspectionForm::on_ButtonClose_clicked()
{
	close();
}

void HistgramFlatInspectionForm::on_pushButtonChangeLib_clicked()
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
			FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==OldID){
					L->SetLibID(RetSelectedLibID);
					ABase->GetLibraryContainer()->GetLibraryNames(LibIDList);
					ui->EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
	}
}

void HistgramFlatInspectionForm::on_ButtonCalc_clicked()
{
	if(Preparing==false){
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
			FlatInspectionItem	*nBData=dynamic_cast<FlatInspectionItem *>(DA);
			if(nBData==NULL)
				continue;

			GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
			PacketReq.BuildData(sRoot,sName,FlatInspectionReqTryThresholdCommand ,FlatInspectionSendTryThresholdCommand);
			FlatInspectionItem	*BData=&((FlatInspectionReqTryThreshold *)PacketReq.Data)->Threshold;
			((FlatInspectionReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
			((FlatInspectionReqTryThreshold *)PacketReq.Data)->Layer			=D->Layer;
			((FlatInspectionReqTryThreshold *)PacketReq.Data)->FlatInspectionItemID	=DA->GetID();

			FlatInspectionThreshold	*DThr=BData->GetThresholdW(GetLayersBase());

			DThr->Broad.OKDot				=ui->EditOKDotB				->value();
			DThr->Broad.OKLength			=ui->EditOKLengthB			->value();

			DThr->Broad.RThrOffsetL			=ui->EditRThrOffsetBL	->value();
			DThr->Broad.RThrOffsetH			=ui->EditRThrOffsetBH	->value();
			DThr->Broad.GThrOffsetL			=ui->EditGThrOffsetBL	->value();
			DThr->Broad.GThrOffsetH			=ui->EditGThrOffsetBH	->value();
			DThr->Broad.BThrOffsetL			=ui->EditBThrOffsetBL	->value();
			DThr->Broad.BThrOffsetH			=ui->EditBThrOffsetBH	->value();

			DThr->Narrow.OKDot				=ui->EditOKDotN				->value();
			DThr->Narrow.OKLength			=ui->EditOKLengthN			->value();

			DThr->Narrow.RThrOffsetL			=ui->EditRThrOffsetNL	->value();
			DThr->Narrow.RThrOffsetH			=ui->EditRThrOffsetNH	->value();
			DThr->Narrow.GThrOffsetL			=ui->EditGThrOffsetNL	->value();
			DThr->Narrow.GThrOffsetH			=ui->EditGThrOffsetNH	->value();
			DThr->Narrow.BThrOffsetL			=ui->EditBThrOffsetNL	->value();
			DThr->Narrow.BThrOffsetH			=ui->EditBThrOffsetNH	->value();

			DThr->SpaceToOutline	=ui->EditSpaceToOutline	->value();
			DThr->ExpansionRange	=ui->doubleSpinBoxExpansionRange->value();
			DThr->MerginForSpecial	=ui->EditMerginForSpecial	->value();
			DThr->DivLenX			=ui->EditDivLenX		->value	();
			DThr->DivLenY			=ui->EditDivLenY		->value	();

			DThr->BackGroundOKDot	=ui->EditBackGroundOKDot	->value();
			DThr->BackGroundOKLength=ui->EditBackGroundOKLength	->value();
			DThr->UseBackGround		=ui->checkBoxUseBackGround	->isChecked();

			DThr->AdjustBlack			=ui->EditAdjustBlack	->value();
			DThr->AdjustWhite			=ui->EditAdjustWhite	->value();
			DThr->AreaSearchX			=ui->EditAreaSearchX	->value();
			DThr->AreaSearchY			=ui->EditAreaSearchY	->value();
			DThr->SelfSearch			=ui->EditSelfSearch		->value();
			DThr->MaxAreaSearch			=ui->EditMaxAreaSearch	->value();
			DThr->MaxSelfSearch			=ui->EditMaxSelfSearch	->value();
			DThr->MultiSpotDot			=ui->EditMultiSpotDot	->value();
			DThr->MultiSpotCount		=ui->EditMultiSpotCount	->value();
			DThr->MultiSpotDotGathered		=ui->EditMultiSpotDotGathered	->value();
			DThr->MultiSpotCountGathered	=ui->EditMultiSpotCountGathered	->value();
			DThr->MultiSpotLengthGathered	=ui->EditMultiSpotLengthGathered->value();
		
			DThr->RedCheckMode			=ui->checkBoxRedCheckMode				->isChecked();
			DThr->RedHighRate			=ui->EditRedHighRate					->value	();
			DThr->RedMinBrightness		=ui->EditRedMinBrightness				->value	();
			DThr->RedGBMerginRate		=ui->EditRedGBMerginRate				->value	();
			DThr->RedGBMerginOffset		=ui->EditRedGBMerginOffset				->value	();
			DThr->RedOKDot				=ui->EditRedOKDot						->value	();
			DThr->RedShrink				=ui->EditRedShrink						->value	();

			DThr->VariationMode	=ui->checkBoxVariationMode		->isChecked();
			DThr->VariationRL	=ui->doubleSpinBoxVariationRL	->value();
			DThr->VariationRH	=ui->doubleSpinBoxVariationRH	->value();
			DThr->VariationGL	=ui->doubleSpinBoxVariationGL	->value();
			DThr->VariationGH	=ui->doubleSpinBoxVariationGH	->value();
			DThr->VariationBL	=ui->doubleSpinBoxVariationBL	->value();
			DThr->VariationBH	=ui->doubleSpinBoxVariationBH	->value();
			DThr->VariationAdaptMinSize		=ui->EditVariationAdaptMinSize->value();
			DThr->VariationMultiplyMaster	=ui->doubleSpinBoxVariationMultiplyMaster->value();
			DThr->VariationDifMaster		=ui->checkBoxVariationDifMaster	->isChecked();
			DThr->VariationAndLogic			=ui->checkBoxVariationAndLogic	->isChecked();
			DThr->VariationSubMasterVari	=ui->doubleSpinBoxVariationSubMasterVari->value();

			DThr->LineMode				=ui->checkBoxLineMode			->isChecked();
			DThr->LineOKMinLength		=ui->EditLineOKMinLength		->value();
			DThr->LineMaxWidth			=ui->EditLineMaxWidth			->value();
			DThr->LineMinDensityPercent	=ui->EditLineMinDensityPercent	->value();
			DThr->LineMinCluster		=ui->EditLineMinCluster			->value();

			GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
			if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

				FlatInspectionSendTryThreshold	*R=((FlatInspectionSendTryThreshold *)PacketSend.Data);
				ui->labelResult		->setText(QString::number(R->NGDot	 ));
				ui->labelResultLen	->setText(QString::number(R->NGLength,'f',1));
					
				ui->doubleSpinBoxDeviationResultR	->setValue(R->DeviationResultR);
				ui->doubleSpinBoxDeviationResultG	->setValue(R->DeviationResultG);
				ui->doubleSpinBoxDeviationResultB	->setValue(R->DeviationResultB);

				SimPanel.SetResult(R->Result);
				SimPanel.repaint();
				break;
			}
		}
	}
}

void	HistgramFlatInspectionForm::SlotValueChanged(int n)
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}
void HistgramFlatInspectionForm::on_toolButtonSimShowItem_clicked()
{
	ModeShowItem=ui->toolButtonSimShowItem ->isChecked();
	SimPanel.SetModeShowBlock(ModeShowItem);
	SimPanel.repaint();
}

void HistgramFlatInspectionForm::on_toolButtonSimShowNGMark_clicked()
{
	SimPanel.SetModeShowBrightnessNG(ui->toolButtonSimShowNGMark ->isChecked());
	SimPanel.repaint();
}

void HistgramFlatInspectionForm::on_pushButtonSimShowCenterPos_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.repaint();
			}
		}
	}
}


void HistgramFlatInspectionForm::on_EditAdjustBlack_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditAdjustWhite_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_checkBoxClusterize_clicked()
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditOKDotB_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxOKDotBMM->setValue(TransformPixelToUnitSquare(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditOKDotN_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxOKDotNMM->setValue(TransformPixelToUnitSquare(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_doubleSpinBoxOKDotBMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditOKDotB->setValue(RoundInt(TransformUnitToPixelSquare(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_doubleSpinBoxOKDotNMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditOKDotN->setValue(RoundInt(TransformUnitToPixelSquare(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditAreaSearchX_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxAreaSearchXMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_doubleSpinBoxAreaSearchXMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditAreaSearchX->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();

}


void HistgramFlatInspectionForm::on_EditAreaSearchY_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxAreaSearchYMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_doubleSpinBoxAreaSearchYMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditAreaSearchY->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();

}


void HistgramFlatInspectionForm::on_EditSelfSearch_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxSelfSearchMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_doubleSpinBoxSelfSearchMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditSelfSearch->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_pushButtonReqMasterImage_clicked()
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
		FlatInspectionItem	*nBData=dynamic_cast<FlatInspectionItem *>(DA);
		if(nBData==NULL)
			continue;
	}	
}

void HistgramFlatInspectionForm::on_EditMultiSpotDot_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditMultiSpotCount_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditRThrOffsetBL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditRThrOffsetBH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditGThrOffsetBL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditGThrOffsetBH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditBThrOffsetBL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditBThrOffsetBH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditRThrOffsetNL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditRThrOffsetNH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditGThrOffsetNL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditGThrOffsetNH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditBThrOffsetNL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditBThrOffsetNH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditOKLengthB_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxOKLengthBMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_doubleSpinBoxOKLengthBMM_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditOKLengthB->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditOKLengthN_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxOKLengthNMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_doubleSpinBoxOKLengthNMM_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditOKLengthN->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_checkBoxRedCheckMode_clicked()
{
	if(OnChanging==true){
		return;
	}
	ShowRed();
    on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditRedHighRate_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	ShowRed();
    on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditRedMinBrightness_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	ShowRed();
    on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditRedGBMerginRate_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	ShowRed();
    on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditRedGBMerginOffset_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	ShowRed();
    on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditRedOKDot_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditMaxAreaSearch_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditMaxSelfSearch_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}


void	HistgramFlatInspectionForm::ShowRed(void)
{
	RedPanel.ShowRed(ui->EditRedHighRate		->value()
					,ui->EditRedMinBrightness	->value()
					,ui->EditRedGBMerginRate	->value()
					,ui->EditRedGBMerginOffset	->value());
}

void	HistgramFlatInspectionForm::ShowRedInMouse(int X,int Y,QRgb d)
{
	QPalette	P=ui->frameRedColor->palette();
	P.setColor(QPalette::Window,d);
	ui->frameRedColor->setPalette(P);
}
void HistgramFlatInspectionForm::on_tabWidget_currentChanged(int index)
{
    if(index==6){
		ui->tabWidgetGraph	->setCurrentIndex(1);
	}
    else if(index==7){
		ui->tabWidgetGraph	->setCurrentIndex(2);
	}
    else if(index==5){
        ui->tabWidgetGraph	->setCurrentIndex(3);
    }
    else{
		ui->tabWidgetGraph	->setCurrentIndex(0);
	}
}

void HistgramFlatInspectionForm::on_EditRedShrink_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditBackGroundOKDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxBackGroundOKDotMM->setValue(TransformPixelToUnitSquare(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_EditBackGroundOKLength_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxBackGroundOKLengthMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_doubleSpinBoxBackGroundOKDotMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditBackGroundOKDot->setValue(RoundInt(TransformUnitToPixelSquare(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_doubleSpinBoxBackGroundOKLengthMM_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditBackGroundOKLength->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_checkBoxUseBackGround_clicked()
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_pushButtonCopy_clicked()
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			return;
		FlatInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		GetLayersBase()->CopyThresholdToClipboard(Thr);
		return;
	}
}


void HistgramFlatInspectionForm::on_pushButtonPaste_clicked()
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
		FlatInspectionItem	*BData=dynamic_cast<FlatInspectionItem *>(DA);
		if(BData==NULL)
			return;
		FlatInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		if(GetLayersBase()->PasteThresholdFromClipboard(Thr)==true){
			ShowLibrary(Thr);
		}
		return;
	}
	
}

void HistgramFlatInspectionForm::on_listWidgetHistList_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->listWidgetHistList->currentRow();
	if(Row<0)
		return;
	HistgramTypeListInAlgo *H=HContainer.GetItem(Row);
	if(H!=NULL){
		for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
			AlgorithmItemRoot	*DA=D->Data;
			if(DA==NULL)
				continue;
			DA->TF_ShowHistgramGraph(H->HistID);
			return;
		}
	}
}



void HistgramFlatInspectionForm::on_EditMultiSpotDotGathered_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
    on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditMultiSpotCountGathered_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
    on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditMultiSpotLengthGathered_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
    OnChanging=true;
    ui->doubleSpinBoxMultiSpotLengthGatheredMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
    OnChanging=false;

    on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_doubleSpinBoxMultiSpotLengthGatheredMM_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
    OnChanging=true;
    ui->EditMultiSpotLengthGathered->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
    OnChanging=false;
    on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_checkBoxVariationMode_clicked()
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_doubleSpinBoxVariationRL_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_doubleSpinBoxVariationRH_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_doubleSpinBoxVariationGL_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_doubleSpinBoxVariationGL_2_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_doubleSpinBoxVariationBL_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_doubleSpinBoxVariationBH_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditVariationAdaptMinSize_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_doubleSpinBoxVariationMultiplyMaster_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}

void HistgramFlatInspectionForm::on_doubleSpinBoxVarietySigma_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_checkBoxVariationDifMaster_clicked()
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_checkBoxVariationAndLogic_clicked()
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_doubleSpinBoxVariationSubMasterVari_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_checkBoxLineMode_stateChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditLineOKMinLength_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditLineMaxWidth_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditLineMinDensityPercent_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditLineMinCluster_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}



void HistgramFlatInspectionForm::on_EditSpaceToOutline_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_toolButtonBroad_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}


void HistgramFlatInspectionForm::on_toolButtonNarrow_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}


void HistgramFlatInspectionForm::on_EditDivLenX_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramFlatInspectionForm::on_EditDivLenY_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}

