#include "DotColorMatchingResource.h"
#include "HistgramDotColorMatchingForm.h"
#include "ui_HistgramDotColorMatchingForm.h"
#include "XDotColorMatching.h"
#include "XDotColorMatchingLibrary.h"
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

DisplaySimPanelDotColorMatching::DisplaySimPanelDotColorMatching(LayersBase *base ,HistgramDotColorMatchingForm *parentw ,QWidget *parent)
	:DisplaySimPanel(base ,parent)
{
	ParentWidget=parentw;
	ModeDrawSubtract=true;
	SubtractItemID=-1;
}

void	DisplaySimPanelDotColorMatching::DrawOther(QPainter &Pnt)
{
	//if(ParentWidget->ModeShowItem==true && Result!=NULL){
	//	QRgb ItemCol=qRgba(60,180,0,120);
	//	ItemArea.DrawAlpha(Result->GetAlignedX()
	//					,  Result->GetAlignedY()
	//					,ResultImage ,ItemCol
	//					,ZoomRate ,MovX ,MovY);
	//}
	/*
	if(ParentWidget->ModeShowNGMark==true && Result!=NULL){
		QRgb NGMarkCol=qRgba(200,160,0,120);
		for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
			r->NGShape.DrawAlpha(Result->GetAlignedX()+r->Rx
								,Result->GetAlignedY()+r->Ry
								,ResultImage ,NGMarkCol
								,ZoomRate ,MovX ,MovY);
		}
	}
	*/
	if(ParentWidget->ScratchEnable==true){
		int	Cx,Cy;
		ItemArea.GetCenter(Cx,Cy);
		double	R=hypot(ItemArea.GetWidth(),ItemArea.GetHeight())/2;
		double	s=ParentWidget->ScratchResultAngle*M_PI/180.0;
		DrawArrow(Cx,Cy,Cx+R*cos(s),Cy+R*sin(s)
				 ,Pnt ,MovX ,MovY ,ZoomRate ,20);
	}
	ResultInItemRoot	*R=GetResult();
	DotColorMatchingResultPosList	*r=dynamic_cast<DotColorMatchingResultPosList *>(R->GetPosListFirst());
	if(r!=NULL){
		//int	Lx1=(r->X1+R->GetAlignedX()+MovX)*ZoomRate;
		//int	Ly1=(r->Y1+R->GetAlignedY()+MovY)*ZoomRate;
		//int	Lx2=(r->X2+R->GetAlignedX()+MovX)*ZoomRate;
		//int	Ly2=(r->Y2+R->GetAlignedY()+MovY)*ZoomRate;
		int	Lx1=(r->X1+MovX)*ZoomRate;
		int Ly1=(r->Y1+MovY)*ZoomRate;
		int	Lx2=(r->X2+MovX)*ZoomRate;
		int Ly2=(r->Y2+MovY)*ZoomRate;
		Pnt.setPen(Qt::yellow);
		Pnt.drawLine(Lx1,Ly1,Lx2,Ly2);
	}
}

void	DisplaySimPanelDotColorMatching::SetSubtractItem(int ItemID)
{
	SubtractItemID=ItemID;
}
void	DisplaySimPanelDotColorMatching::SetDrawSubtractMode(bool mode)
{
	ModeDrawSubtract=mode;
}

void	DisplaySimPanelDotColorMatching::GetDrawInformation(QByteArray &Something)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	::Save(&Buff,ModeDrawSubtract);
	::Save(&Buff,SubtractItemID);
	Something=Buff.buffer();
}

void	DisplaySimPanelDotColorMatching::mouseMoveEvent ( QMouseEvent * e )
{
	DisplaySimPanel::mouseMoveEvent(e);
	int	px=e->x();
	int	py=e->y();
	int GlobalX	=px/ZoomRate-MovX;
	int GlobalY	=py/ZoomRate-MovY;

	int	LocalX,LocalY;
	//int	GlobalPage=GetLayersBase()->GetLocalMatrixFromGlobal(GlobalX,GlobalY,LocalX,LocalY);

	if(0<=GlobalPage){
		GUICmdReqHSVValue	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.HSVIndexData.LocalX=LocalX;
		RCmd.HSVIndexData.LocalY=LocalY;
		RCmd.HSVIndexData.Phase	=GetLayersBase()->GetCurrentPhase();
		RCmd.HSVIndexData.ItemID=ItemID;
		GUICmdAckHSVValue	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			ParentWidget->SetHSVValue(ACmd.HSVValueData.MasterH
									 ,ACmd.HSVValueData.MasterS
									 ,ACmd.HSVValueData.MasterV
									 ,ACmd.HSVValueData.TargetH
									 ,ACmd.HSVValueData.TargetS
									 ,ACmd.HSVValueData.TargetV);
			ParentWidget->ShowCurrentRGB(ACmd.HSVValueData.CurrentR
										,ACmd.HSVValueData.CurrentG
										,ACmd.HSVValueData.CurrentB);
			ParentWidget->ShowRedRange  (ACmd.HSVValueData.RedRL,ACmd.HSVValueData.RedRH
										,ACmd.HSVValueData.RedGL,ACmd.HSVValueData.RedGH
										,ACmd.HSVValueData.RedBL,ACmd.HSVValueData.RedBH);
		}
	}
}
	
//======================================================================================

RedPanelWidget::RedPanelWidget(HistgramDotColorMatchingForm *p,QWidget *parent)
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

HSVPanelWidget::HSVPanelWidget(HistgramDotColorMatchingForm *p,QWidget *parent)
	:QWidget(parent),Parent(p)
{
	setMouseTracking(true);
	GlobalPage	=0;
	HSVParamData.TrialMode=false;
	EnableRepaint	=true;
}
HSVPanelWidget::~HSVPanelWidget(void)
{
}

void	HSVPanelWidget::SetInitial(int _ItemID ,FlexArea &InitialArea)
{
	HSVParamData.ItemID	=_ItemID;
	ItemArea=InitialArea;

	int	W=InitialArea.GetWidth();
	int	H=InitialArea.GetHeight();
	int	X1=InitialArea.GetMinX()-W/4;
	int	X2=InitialArea.GetMaxX()+W/4;
	int	Y1=InitialArea.GetMinY()-H/4;
	int	Y2=InitialArea.GetMaxY()+H/4;

	int	Cx,Cy;
	InitialArea.GetCenter(Cx,Cy);

	double	Z1=100000000;
	if(X2-X1!=0){
		Z1=((double)width())/((double)(X2-X1));
	}
	double	Z2=100000000;
	if(Y2-Y1!=0){
		Z2=((double)height())/((double)(Y2-Y1));
	}
	HSVParamData.ZoomRate=(Z1<Z2)?Z1:Z2;

	HSVParamData.MovX=-(Cx-width() /HSVParamData.ZoomRate/2);
	HSVParamData.MovY=-(Cy-height()/HSVParamData.ZoomRate/2);
}
void HSVPanelWidget::mouseMoveEvent(QMouseEvent *event)
{
	int	X=event->pos().x();
	int	Y=event->pos().y();
	int	W=Image.width();
	int	H=Image.height();
	if(0<=X && X<W && 0<=Y && Y<H){
		QRgb	*d=(QRgb *)Image.scanLine(Y);
		Parent->ShowRedInMouse(X,Y,d[X]);
	}
}
void	HSVPanelWidget::Resize(int W,int H)
{
	resize(W,H);
	Image=QImage(W,H,QImage::Format_RGB32);
	ShowHSV();
}
void HSVPanelWidget::resizeEvent(QResizeEvent *event)
{
	int	W=width();
	int	H=height();
	Image=QImage(W,H,QImage::Format_RGB32);
	ShowHSV();
}

void HSVPanelWidget::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	Pnt.drawImage(0,0,Image);
}
void	HSVPanelWidget::Repaint(void)
{
	if(EnableRepaint==true){
		ShowHSV();
	}
}

void	HSVPanelWidget::ShowHSV(void)
{
	Parent->SetHSVParam();

	int	W=min(Image.width(),width());
	int	H=min(Image.height(),height());
	if(W==0 || H==0)
		return;

	Image.fill(Qt::black);

	GUICmdReqHSVPanelImage	ReqCmd(Parent->GetLayersBase(),sRoot,sName,GlobalPage);
	GUICmdAckHSVPanelImage	AckCmd(Parent->GetLayersBase(),sRoot,sName,GlobalPage);
	ReqCmd.HSVParamData		=HSVParamData;
	ReqCmd.ImageWidth	=width();
	ReqCmd.ImageHeight	=height();

	if(ReqCmd.Send(GlobalPage,0,AckCmd)==true){
		Image=AckCmd.AckImage;
	}
	repaint();
}
//======================================================================================

HistgramDotColorMatchingForm::HistgramDotColorMatchingForm(LayersBase *Base,QWidget *parent) :
    AlgorithmComponentWindow(parent),ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
	,ui(new Ui::HistgramDotColorMatchingForm)
	,SimPanel(Base,this,parent)
	,LGraphBR(parent)
	,LGraphBG(parent)
	,LGraphBB(parent)
	,LGraphNR(parent)
	,LGraphNG(parent)
	,LGraphNB(parent)
	,RedPanel(this,this)
	,HSVMasterImage(this,this)
	,HSVTrialImage (this,this)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	Preparing			=true;
	OnChanging			=false;
	ScratchResultAngle	=0;
	ScratchEnable		=false;
	HistgramPage		=-1;

	ui->tabWidgetGraph			->setCurrentIndex(0);
	ui->tabWidgetRotationImage	->setCurrentIndex(0);

	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(sRoot,sName);
	SimPanel.SetGUI(/**/"Button",/**/"PropertyDotColorMatching");
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

	ScrGraphMaster.setParent(ui->frameScratchMaster);
	ScrGraphMaster.SetScaleTypeY(mtLineGraph::mtConstant);
	ScrGraphMaster.move(0,0);
	ScrGraphMaster.resize(ui->frameScratchMaster->width(),ui->frameScratchMaster->height());

	ScrGraphTarget.setParent(ui->frameScratchTarget);
	ScrGraphTarget.SetScaleTypeY(mtLineGraph::mtConstant);
	ScrGraphTarget.move(0,0);
	ScrGraphTarget.resize(ui->frameScratchTarget->width(),ui->frameScratchTarget->height());

	ScrGraphCoef.setParent(ui->frameScratchCoef);
	ScrGraphCoef.SetScaleTypeY(mtLineGraph::mtConstant);
	ScrGraphCoef.move(0,0);
	ScrGraphCoef.resize(ui->frameScratchCoef->width(),ui->frameScratchCoef->height());

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

	ScrGraphMaster.AddGraph(&GraphScrMaster);
	ScrGraphTarget.AddGraph(&GraphScrTarget);
	ScrGraphCoef  .AddGraph(&GraphScrCoef);

	DDRet=(connect(ui->EditOKDotB			,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditOKDotN			,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditAdjustBlack		,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditAdjustWhite		,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
	DDRet=(connect(ui->EditAdjustContribute	,SIGNAL(valueChanged(int i)),this,SLOT(SlotValueChanged(int i))))?true:false;
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

	HSVMasterImage.setParent(ui->frameHSVMaster);
	HSVMasterImage.move(0,0);
	HSVMasterImage.Resize(ui->frameHSVMaster->width(),ui->frameHSVMaster->height());
	HSVTrialImage .setParent(ui->frameHSVTrial);
	HSVTrialImage .HSVParamData.TrialMode=true;
	HSVTrialImage .move(0,0);
	HSVTrialImage .Resize(ui->frameHSVTrial->width(),ui->frameHSVTrial->height());

	::SetColumnWidthInTable(ui->tableWidgetSubBlockList,0, 20);
	::SetColumnWidthInTable(ui->tableWidgetSubBlockList,1, 20);
	::SetColumnWidthInTable(ui->tableWidgetSubBlockList,2, 60);

	RegisterComponent((int)ID_BroadBrightWidthRL,ui->EditBrightWidthBRL);
	RegisterComponent((int)ID_BroadBrightWidthRH,ui->EditBrightWidthBRH);
	RegisterComponent((int)ID_BroadBrightWidthGL,ui->EditBrightWidthBGL);
	RegisterComponent((int)ID_BroadBrightWidthGH,ui->EditBrightWidthBGH);
	RegisterComponent((int)ID_BroadBrightWidthBL,ui->EditBrightWidthBBL);
	RegisterComponent((int)ID_BroadBrightWidthBH,ui->EditBrightWidthBBH);

	RegisterComponent((int)ID_BroadRThrOffsetL,ui->EditRThrOffsetBL);
	RegisterComponent((int)ID_BroadRThrOffsetH,ui->EditRThrOffsetBH);
	RegisterComponent((int)ID_BroadGThrOffsetL,ui->EditGThrOffsetBL);
	RegisterComponent((int)ID_BroadGThrOffsetH,ui->EditGThrOffsetBH);
	RegisterComponent((int)ID_BroadBThrOffsetL,ui->EditBThrOffsetBL);
	RegisterComponent((int)ID_BroadBThrOffsetH,ui->EditBThrOffsetBH);

	RegisterComponent((int)ID_BroadOKDot			,ui->EditOKDotB);
	RegisterComponent((int)ID_BroadOKLength			,ui->EditOKLengthB);

	RegisterComponent((int)ID_NarrowBrightWidthRL,ui->EditBrightWidthNRL);
	RegisterComponent((int)ID_NarrowBrightWidthRH,ui->EditBrightWidthNRH);
	RegisterComponent((int)ID_NarrowBrightWidthGL,ui->EditBrightWidthNGL);
	RegisterComponent((int)ID_NarrowBrightWidthGH,ui->EditBrightWidthNGH);
	RegisterComponent((int)ID_NarrowBrightWidthBL,ui->EditBrightWidthNBL);
	RegisterComponent((int)ID_NarrowBrightWidthBH,ui->EditBrightWidthNBH);

	RegisterComponent((int)ID_NarrowRThrOffsetL,ui->EditRThrOffsetNL);
	RegisterComponent((int)ID_NarrowRThrOffsetH,ui->EditRThrOffsetNH);
	RegisterComponent((int)ID_NarrowGThrOffsetL,ui->EditGThrOffsetNL);
	RegisterComponent((int)ID_NarrowGThrOffsetH,ui->EditGThrOffsetNH);
	RegisterComponent((int)ID_NarrowBThrOffsetL,ui->EditBThrOffsetNL);
	RegisterComponent((int)ID_NarrowBThrOffsetH,ui->EditBThrOffsetNH);

	RegisterComponent((int)ID_NarrowOKDot			,ui->EditOKDotN);
	RegisterComponent((int)ID_NarrowOKLength		,ui->EditOKLengthN);

	RegisterComponent((int)ID_AdjustBlack		,ui->EditAdjustBlack);
	RegisterComponent((int)ID_AdjustWhite		,ui->EditAdjustWhite);
	RegisterComponent((int)ID_AdjustContribute	,ui->EditAdjustContribute);
	RegisterComponent((int)ID_BackGroundOKDot	,ui->EditBackGroundOKDot);
	RegisterComponent((int)ID_BackGroundOKLength,ui->EditBackGroundOKLength);
	RegisterComponent((int)ID_UseBackGround		,ui->checkBoxUseBackGround);

	RegisterComponent((int)ID_UseOneLayer	,ui->comboBoxUseOneLayer);
	RegisterComponent((int)ID_VarietySigma	,ui->doubleSpinBoxVarietySigma);
	RegisterComponent((int)ID_AreaSearchX	,ui->EditAreaSearchX);
	RegisterComponent((int)ID_AreaSearchY	,ui->EditAreaSearchY);
	RegisterComponent((int)ID_SelfSearch	,ui->EditSelfSearch);
	RegisterComponent((int)ID_MaxAreaSearch	,ui->EditMaxAreaSearch);
	RegisterComponent((int)ID_MaxSelfSearch	,ui->EditMaxSelfSearch);

	RegisterComponent((int)ID_PreciseSearch	,ui->checkBoxPreciseSearch);
	RegisterComponent((int)ID_Clusterize	,ui->checkBoxClusterize);
	RegisterComponent((int)ID_EnableM2T		,ui->checkBoxEnableM2T);
	RegisterComponent((int)ID_EnableT2M		,ui->checkBoxEnableT2M);

	RegisterComponent((int)ID_MultiSpotDot	,ui->EditMultiSpotDot);
	RegisterComponent((int)ID_MultiSpotCount,ui->EditMultiSpotCount);
	RegisterComponent((int)ID_MultiSpotDotGathered		,ui->EditMultiSpotDotGathered);
	RegisterComponent((int)ID_MultiSpotCountGathered	,ui->EditMultiSpotCountGathered);
	RegisterComponent((int)ID_MultiSpotLengthGathered	,ui->EditMultiSpotLengthGathered);

	RegisterComponent((int)ID_ScratchEnable			,ui->checkBoxScratchEnable);
	RegisterComponent((int)ID_ScratchStartDirection	,ui->doubleSpinBoxScratchStartDirection);
	RegisterComponent((int)ID_ScratchRotationAngle	,ui->doubleSpinBoxScratchRotationAngle);
	RegisterComponent((int)ID_ScratchDiff			,ui->doubleSpinBoxScratchDiff);
	RegisterComponent((int)ID_ScratchDetectLevelH	,ui->EditScratchDetectLevelH);
	RegisterComponent((int)ID_ScratchDetectLevelL	,ui->EditScratchDetectLevelL);
	RegisterComponent((int)ID_ScratchMaxWidth		,ui->EditScratchMaxWidth);
	RegisterComponent((int)ID_ScratchVariety		,ui->doubleSpinBoxScratchVariety);
	RegisterComponent((int)ID_ScratchUseMaster		,ui->checkBoxScratchUseMaster);
	RegisterComponent((int)ID_ScratchVOffset		,ui->doubleSpinBoxScratchVOffset);

	RegisterComponent((int)ID_RedCheckMode			,ui->checkBoxRedCheckMode);
	RegisterComponent((int)ID_RedHighRate			,ui->EditRedHighRate);
	RegisterComponent((int)ID_RedMinBrightness		,ui->EditRedMinBrightness);
	RegisterComponent((int)ID_RedGBMerginRate		,ui->EditRedGBMerginRate);
	RegisterComponent((int)ID_RedGBMerginOffset		,ui->EditRedGBMerginOffset);
	RegisterComponent((int)ID_RedOKDot				,ui->EditRedOKDot);
	RegisterComponent((int)ID_RedShrink				,ui->EditRedShrink);

	RegisterComponent((int)ID_MatchBrightnessByLayerH	,ui->EditMatchBrightnessByLayerH);
	RegisterComponent((int)ID_MatchBrightnessByLayerL	,ui->EditMatchBrightnessByLayerL);

	RegisterComponent((int)ID_HsvCheckMode			,ui->checkBoxHsvCheckMode		);
	RegisterComponent((int)ID_HsvFixedColorMode		,ui->checkBoxHsvFixedColorMode	);
	RegisterComponent((int)ID_HsvH					,ui->EditHsvH		);
	RegisterComponent((int)ID_HsvS					,ui->EditHsvS		);
	RegisterComponent((int)ID_HsvV					,ui->EditHsvV		);
	RegisterComponent((int)ID_HsvPHL				,ui->EditHsvPHL		);
	RegisterComponent((int)ID_HsvPHH				,ui->EditHsvPHH		);
	RegisterComponent((int)ID_HsvPSL				,ui->EditHsvPSL		);
	RegisterComponent((int)ID_HsvPSH				,ui->EditHsvPSH		);
	RegisterComponent((int)ID_HsvPVL				,ui->EditHsvPVL		);
	RegisterComponent((int)ID_HsvPVH				,ui->EditHsvPVH		);
	RegisterComponent((int)ID_HsvDHL				,ui->EditHsvDHL		);
	RegisterComponent((int)ID_HsvDHH				,ui->EditHsvDHH		);
	RegisterComponent((int)ID_HsvDSL				,ui->EditHsvDSL		);
	RegisterComponent((int)ID_HsvDSH				,ui->EditHsvDSH		);
	RegisterComponent((int)ID_HsvDVL				,ui->EditHsvDVL		);
	RegisterComponent((int)ID_HsvDVH				,ui->EditHsvDVH		);
	RegisterComponent((int)ID_HsvOKDot				,ui->EditHsvOKDot	);
	RegisterComponent((int)ID_HsvOKLength			,ui->EditHsvOKLength);

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

	RegisterComponent((int)ID_PitMode				,ui->checkBoxPitMode		);
	RegisterComponent((int)ID_PitBrightWidthRL		,ui->EditPitBrightWidthRL	);
	RegisterComponent((int)ID_PitBrightWidthRH		,ui->EditPitBrightWidthRH	);
	RegisterComponent((int)ID_PitBrightWidthGL		,ui->EditPitBrightWidthGL	);
	RegisterComponent((int)ID_PitBrightWidthGH		,ui->EditPitBrightWidthGH	);
	RegisterComponent((int)ID_PitBrightWidthBL		,ui->EditPitBrightWidthBL	);
	RegisterComponent((int)ID_PitBrightWidthBH		,ui->EditPitBrightWidthBH	);

	RegisterComponent((int)ID_LineMode				,ui->checkBoxLineMode			);
	RegisterComponent((int)ID_LineOKMinLength		,ui->EditLineOKMinLength		);
	RegisterComponent((int)ID_LineMaxWidth			,ui->EditLineMaxWidth			);
	RegisterComponent((int)ID_LineMinDensityPercent	,ui->EditLineMinDensityPercent	);
	RegisterComponent((int)ID_LineMinCluster		,ui->EditLineMinCluster			);

	on_toolButtonBroad_clicked();
	SetupPassword();
	InstallOperationLog(this);
}
HistgramDotColorMatchingForm::~HistgramDotColorMatchingForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	delete	[]LButtonList;
	LButtonList=NULL;
	Preparing=true;
}
void	HistgramDotColorMatchingForm::showEvent ( QShowEvent * event )
{
	Preparing=false;
	on_ButtonCalc_clicked();
}
void	HistgramDotColorMatchingForm::GetActiveLayerList(IntList &LayerList)
{
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int Layer=0;Layer<LayerNumb;Layer++){
		if(LButtonList[Layer]->isChecked()==true){
			LayerList.Add(Layer);
		}
	}
}

void	HistgramDotColorMatchingForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
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
			DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
			if(BData!=NULL){
				HistgramPage	=D->GlobalPage;
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock		(ui->toolButtonSimShowItem ->isChecked());
				ModeShowItem	=ui->toolButtonSimShowItem ->isChecked();

				HSVMasterImage.SetInitial(BData->GetID(),BData->GetArea());
				HSVTrialImage .SetInitial(BData->GetID(),BData->GetArea());
				ShowSubBlockList(BData->GetSubBlock());
			}
		}
	}
	if(IData->Items.GetCount()>1){
		ui->ButtonReflectAllDotColorMatchings->setVisible(false);
	}
	else{
		ui->ButtonReflectAllDotColorMatchings->setVisible(true);
	}

	SetEnableChangeMode(false);

	CreateThreshld();
	ShowHistgramList();
	on_ButtonCalc_clicked();
	ShowRed();
	ui->tabWidgetRotationImage->setCurrentIndex(0);
	ui->doubleSpinBoxOKDotBMM	 ->setValue(TransformPixelToUnitSquare	(HistgramPage,ui->EditOKDotB		->value()));
	ui->doubleSpinBoxOKLengthBMM		->setValue(TransformPixelToUnit	(HistgramPage,ui->EditOKLengthB		->value()));
	ui->doubleSpinBoxOKDotNMM	 ->setValue(TransformPixelToUnitSquare	(HistgramPage,ui->EditOKDotN		->value()));
	ui->doubleSpinBoxOKLengthNMM		->setValue(TransformPixelToUnit	(HistgramPage,ui->EditOKLengthN		->value()));
	ui->doubleSpinBoxAreaSearchXMM	->setValue(TransformPixelToUnit		(HistgramPage,ui->EditAreaSearchX	->value()));
	ui->doubleSpinBoxAreaSearchYMM	->setValue(TransformPixelToUnit		(HistgramPage,ui->EditAreaSearchY	->value()));
	ui->doubleSpinBoxSelfSearchMM	->setValue(TransformPixelToUnit		(HistgramPage,ui->EditSelfSearch	->value()));
	ui->doubleSpinBoxBackGroundOKDotMM	 ->setValue(TransformPixelToUnitSquare	(HistgramPage,ui->EditBackGroundOKDot->value()));
	ui->doubleSpinBoxBackGroundOKLengthMM->setValue(TransformPixelToUnit		(HistgramPage,ui->EditBackGroundOKLength->value()));
	ui->doubleSpinBoxHsvOKDotMM		->setValue(TransformPixelToUnitSquare		(HistgramPage,ui->EditHsvOKDot	->value()));
	ui->doubleSpinBoxHsvOKLengthMM	->setValue(TransformPixelToUnit				(HistgramPage,ui->EditHsvOKLength->value()));
	SetEnableChangeMode(true);
}

void	HistgramDotColorMatchingForm::ShowHistgramList(void)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			continue;
		
		BData->TF_EnumHistList(HContainer);
		for(HistgramTypeListInAlgo *a=HContainer.GetFirst();a!=NULL;a=a->GetNext()){
			ui->listWidgetHistList->addItem(a->HistName);
		}
		return;
	}
}

void	HistgramDotColorMatchingForm::CreateThreshld(void)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,DotColorMatchingReqThresholdReqCommand ,DotColorMatchingReqThresholdSendCommand);
		((DotColorMatchingThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((DotColorMatchingThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((DotColorMatchingThresholdReq *)PacketReq.Data)->DotColorMatchingItemID	=DA->GetID();
		((DotColorMatchingThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			DotColorMatchingThresholdSend	*ThrePoint=(DotColorMatchingThresholdSend *)PacketSend.GetData();
			CenterBrightR		=ThrePoint->ThresholdValues.CenterBrightR;
			CenterTargetBrightR	=ThrePoint->ThresholdValues.CenterTargetBrightR;
			CenterBrightG		=ThrePoint->ThresholdValues.CenterBrightG;
			CenterTargetBrightG	=ThrePoint->ThresholdValues.CenterTargetBrightG;
			CenterBrightB		=ThrePoint->ThresholdValues.CenterBrightB;
			CenterTargetBrightB	=ThrePoint->ThresholdValues.CenterTargetBrightB;

			BrightWidthBRL		=ThrePoint->ThresholdValues.BrightWidthBRL;		
			BrightWidthBRH		=ThrePoint->ThresholdValues.BrightWidthBRH;		
			BrightWidthBGL		=ThrePoint->ThresholdValues.BrightWidthBGL;		
			BrightWidthBGH		=ThrePoint->ThresholdValues.BrightWidthBGH;		
			BrightWidthBBL		=ThrePoint->ThresholdValues.BrightWidthBBL;		
			BrightWidthBBH		=ThrePoint->ThresholdValues.BrightWidthBBH;		
			AbsBrightWidthBRL	=ThrePoint->ThresholdValues.AbsBrightWidthBRL;	
			AbsBrightWidthBRH	=ThrePoint->ThresholdValues.AbsBrightWidthBRH;	
			AbsBrightWidthBGL	=ThrePoint->ThresholdValues.AbsBrightWidthBGL;	
			AbsBrightWidthBGH	=ThrePoint->ThresholdValues.AbsBrightWidthBGH;	
			AbsBrightWidthBBL	=ThrePoint->ThresholdValues.AbsBrightWidthBBL;	
			AbsBrightWidthBBH	=ThrePoint->ThresholdValues.AbsBrightWidthBBH;	

			OrgBrightWidthBRL	=ThrePoint->ThresholdValues.OrgBrightWidthBRL;	
			OrgBrightWidthBRH	=ThrePoint->ThresholdValues.OrgBrightWidthBRH;	
			OrgBrightWidthBGL	=ThrePoint->ThresholdValues.OrgBrightWidthBGL;	
			OrgBrightWidthBGH	=ThrePoint->ThresholdValues.OrgBrightWidthBGH;	
			OrgBrightWidthBBL	=ThrePoint->ThresholdValues.OrgBrightWidthBBL;	
			OrgBrightWidthBBH	=ThrePoint->ThresholdValues.OrgBrightWidthBBH;	

			BrightWidthNRL		=ThrePoint->ThresholdValues.BrightWidthNRL;		
			BrightWidthNRH		=ThrePoint->ThresholdValues.BrightWidthNRH;		
			BrightWidthNGL		=ThrePoint->ThresholdValues.BrightWidthNGL;		
			BrightWidthNGH		=ThrePoint->ThresholdValues.BrightWidthNGH;		
			BrightWidthNBL		=ThrePoint->ThresholdValues.BrightWidthNBL;		
			BrightWidthNBH		=ThrePoint->ThresholdValues.BrightWidthNBH;		
			AbsBrightWidthNRL	=ThrePoint->ThresholdValues.AbsBrightWidthNRL;	
			AbsBrightWidthNRH	=ThrePoint->ThresholdValues.AbsBrightWidthNRH;	
			AbsBrightWidthNGL	=ThrePoint->ThresholdValues.AbsBrightWidthNGL;	
			AbsBrightWidthNGH	=ThrePoint->ThresholdValues.AbsBrightWidthNGH;	
			AbsBrightWidthNBL	=ThrePoint->ThresholdValues.AbsBrightWidthNBL;	
			AbsBrightWidthNBH	=ThrePoint->ThresholdValues.AbsBrightWidthNBH;	

			OrgBrightWidthNRL	=ThrePoint->ThresholdValues.OrgBrightWidthNRL;	
			OrgBrightWidthNRH	=ThrePoint->ThresholdValues.OrgBrightWidthNRH;	
			OrgBrightWidthNGL	=ThrePoint->ThresholdValues.OrgBrightWidthNGL;	
			OrgBrightWidthNGH	=ThrePoint->ThresholdValues.OrgBrightWidthNGH;	
			OrgBrightWidthNBL	=ThrePoint->ThresholdValues.OrgBrightWidthNBL;	
			OrgBrightWidthNBH	=ThrePoint->ThresholdValues.OrgBrightWidthNBH;	
			break;
		}
	}
	HSVTrialImage.EnableRepaint=false;
	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
	LGraphBR.repaint();
	LGraphBG.repaint();
	LGraphBB.repaint();
	LGraphNR.repaint();
	LGraphNG.repaint();
	LGraphNB.repaint();
	HSVTrialImage.EnableRepaint=true;

	HSVTrialImage.Repaint();
}

void HistgramDotColorMatchingForm::GetHistogramData(void)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,DotColorMatchingHistogramListReqCommand ,DotColorMatchingHistogramListSendCommand);
		((DotColorMatchingHistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((DotColorMatchingHistogramListReq *)PacketReq.Data)->Layer=D->Layer;
		((DotColorMatchingHistogramListReq *)PacketReq.Data)->DotColorMatchingItemID	=DA->GetID();
		((DotColorMatchingHistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			DotColorMatchingHistogramListSend	*L=(DotColorMatchingHistogramListSend *)PacketSend.GetData();
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


void	HistgramDotColorMatchingForm::ShowLibrary(void)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
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

		const	DotColorMatchingThreshold	*RThr=BData->GetThresholdR(GetLayersBase());
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

void	HistgramDotColorMatchingForm::ShowLibrary(const	DotColorMatchingThreshold *RThr)
{
	ui->EditBrightWidthBRL	->setValue	(RThr->Broad.BrightWidthRL);
	ui->EditBrightWidthBRH	->setValue	(RThr->Broad.BrightWidthRH);
	ui->EditBrightWidthBGL	->setValue	(RThr->Broad.BrightWidthGL);
	ui->EditBrightWidthBGH	->setValue	(RThr->Broad.BrightWidthGH);
	ui->EditBrightWidthBBL	->setValue	(RThr->Broad.BrightWidthBL);
	ui->EditBrightWidthBBH	->setValue	(RThr->Broad.BrightWidthBH);
	ui->EditOKDotB			->setValue	(RThr->Broad.OKDot);
	ui->EditOKLengthB		->setValue	(RThr->Broad.OKLength);
	ui->EditRThrOffsetBL	->setValue	(RThr->Broad.RThrOffsetL);
	ui->EditRThrOffsetBH	->setValue	(RThr->Broad.RThrOffsetH);
	ui->EditGThrOffsetBL	->setValue	(RThr->Broad.GThrOffsetL);
	ui->EditGThrOffsetBH	->setValue	(RThr->Broad.GThrOffsetH);
	ui->EditBThrOffsetBL	->setValue	(RThr->Broad.BThrOffsetL);
	ui->EditBThrOffsetBH	->setValue	(RThr->Broad.BThrOffsetH);


	ui->EditBrightWidthNRL	->setValue	(RThr->Narrow.BrightWidthRL);
	ui->EditBrightWidthNRH	->setValue	(RThr->Narrow.BrightWidthRH);
	ui->EditBrightWidthNGL	->setValue	(RThr->Narrow.BrightWidthGL);
	ui->EditBrightWidthNGH	->setValue	(RThr->Narrow.BrightWidthGH);
	ui->EditBrightWidthNBL	->setValue	(RThr->Narrow.BrightWidthBL);
	ui->EditBrightWidthNBH	->setValue	(RThr->Narrow.BrightWidthBH);
	ui->EditOKDotN			->setValue	(RThr->Narrow.OKDot);
	ui->EditOKLengthN		->setValue	(RThr->Narrow.OKLength);
	ui->EditRThrOffsetNL	->setValue	(RThr->Narrow.RThrOffsetL);
	ui->EditRThrOffsetNH	->setValue	(RThr->Narrow.RThrOffsetH);
	ui->EditGThrOffsetNL	->setValue	(RThr->Narrow.GThrOffsetL);
	ui->EditGThrOffsetNH	->setValue	(RThr->Narrow.GThrOffsetH);
	ui->EditBThrOffsetNL	->setValue	(RThr->Narrow.BThrOffsetL);
	ui->EditBThrOffsetNH	->setValue	(RThr->Narrow.BThrOffsetH);


	ui->doubleSpinBoxVarietySigma->setValue	(RThr->VarietySigma);
	ui->EditBackGroundOKDot		->setValue	(RThr->BackGroundOKDot);
	ui->EditBackGroundOKLength	->setValue	(RThr->BackGroundOKLength);
	ui->checkBoxUseBackGround	->setChecked(RThr->UseBackGround);

	ui->EditAdjustBlack		->setValue	(RThr->AdjustBlack);
	ui->EditAdjustWhite		->setValue	(RThr->AdjustWhite);
	ui->EditAdjustContribute->setValue	(RThr->AdjustContribute);
	ui->EditSelfSearch		->setValue	(RThr->SelfSearch);
	ui->EditAreaSearchX		->setValue	(RThr->AreaSearchX);
	ui->EditAreaSearchY		->setValue	(RThr->AreaSearchY);
	ui->EditMaxSelfSearch	->setValue	(RThr->MaxSelfSearch);
	ui->EditMaxAreaSearch	->setValue	(RThr->MaxAreaSearch);
	ui->checkBoxPreciseSearch->setChecked(RThr->PreciseSearch);
	ui->checkBoxClusterize	->setChecked(RThr->Clusterize);
	ui->EditMultiSpotDot	->setValue	(RThr->MultiSpotDot	);
	ui->EditMultiSpotCount	->setValue	(RThr->MultiSpotCount);
	ui->EditMultiSpotDotGathered	->setValue(RThr->MultiSpotDotGathered	);
	ui->EditMultiSpotCountGathered	->setValue(RThr->MultiSpotCountGathered);
	ui->EditMultiSpotLengthGathered	->setValue(RThr->MultiSpotLengthGathered);
	ui->checkBoxEnableT2M	->setChecked(RThr->EnableT2M);
	ui->checkBoxEnableM2T	->setChecked(RThr->EnableM2T);

	ui->doubleSpinBoxScratchStartDirection	->setValue	(RThr->ScratchStartDirection	);
	ui->doubleSpinBoxScratchRotationAngle	->setValue	(RThr->ScratchRotationAngle	);
	ui->doubleSpinBoxScratchVariety			->setValue	(RThr->ScratchVariety			);
	ui->EditScratchDetectLevelH				->setValue	(RThr->ScratchDetectLevelH	);
	ui->EditScratchDetectLevelL				->setValue	(RThr->ScratchDetectLevelL	);
	ui->EditScratchMaxWidth					->setValue	(RThr->ScratchMaxWidth		);
	ui->checkBoxScratchEnable				->setChecked(RThr->ScratchEnable		);
	ui->checkBoxScratchUseMaster			->setChecked(RThr->ScratchUseMaster	);
	ui->doubleSpinBoxScratchVOffset			->setValue	(RThr->ScratchVOffset		);
	ui->doubleSpinBoxScratchDiff			->setValue	(RThr->ScratchDiff			);
	
	ui->comboBoxUseOneLayer	->clear();
	ui->comboBoxUseOneLayer	->addItem(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_61)/*"Color"*/);
	
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int layer=0;layer<LayerNumb;layer++){
		ui->comboBoxUseOneLayer	->addItem(QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_62)/*"Layer"*/)+QString::number(layer));
	}
	ui->comboBoxUseOneLayer	->setCurrentIndex((RThr->UseOneLayer==0xFF)?0:RThr->UseOneLayer+1);

	ui->checkBoxRedCheckMode			->setChecked(RThr->RedCheckMode			);
	ui->EditRedHighRate					->setValue	(RThr->RedHighRate			);
	ui->EditRedMinBrightness			->setValue	(RThr->RedMinBrightness		);
	ui->EditRedGBMerginRate				->setValue	(RThr->RedGBMerginRate		);
	ui->EditRedGBMerginOffset			->setValue	(RThr->RedGBMerginOffset	);
	ui->EditRedOKDot					->setValue	(RThr->RedOKDot				);
	ui->EditRedShrink					->setValue	(RThr->RedShrink			);
	ui->EditMatchBrightnessByLayerH		->setValue	(RThr->MatchBrightnessByLayerH	);
	ui->EditMatchBrightnessByLayerL		->setValue	(RThr->MatchBrightnessByLayerL	);

	ui->checkBoxHsvCheckMode		->setChecked(RThr->HsvCheckMode);
	ui->checkBoxHsvFixedColorMode	->setChecked(RThr->HsvFixedColorMode);

	ui->EditHsvPHL	->setValue(RThr->HsvPHL);
	ui->EditHsvPHH	->setValue(RThr->HsvPHH);
	ui->EditHsvPSL	->setValue(RThr->HsvPSL);
	ui->EditHsvPSH	->setValue(RThr->HsvPSH);
	ui->EditHsvPVL	->setValue(RThr->HsvPVL);
	ui->EditHsvPVH	->setValue(RThr->HsvPVH);

	ui->EditHsvDHL	->setValue(RThr->HsvDHL);
	ui->EditHsvDHH	->setValue(RThr->HsvDHH);
	ui->EditHsvDSL	->setValue(RThr->HsvDSL);
	ui->EditHsvDSH	->setValue(RThr->HsvDSH);
	ui->EditHsvDVL	->setValue(RThr->HsvDVL);
	ui->EditHsvDVH	->setValue(RThr->HsvDVH);

	ui->EditHsvH	->setValue(RThr->HsvH);
	ui->EditHsvS	->setValue(RThr->HsvS);
	ui->EditHsvV	->setValue(RThr->HsvV);

	ui->EditHsvOKDot	->setValue(RThr->HsvOKDot);
	ui->EditHsvOKLength	->setValue(RThr->HsvOKLength);

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

	ui->checkBoxPitMode				->setChecked(RThr->PitMode);
	ui->EditPitBrightWidthRL		->setValue(RThr->PitBrightWidthRL);
	ui->EditPitBrightWidthRH		->setValue(RThr->PitBrightWidthRH);
	ui->EditPitBrightWidthGL		->setValue(RThr->PitBrightWidthGL);
	ui->EditPitBrightWidthGH		->setValue(RThr->PitBrightWidthGH);
	ui->EditPitBrightWidthBL		->setValue(RThr->PitBrightWidthBL);
	ui->EditPitBrightWidthBH		->setValue(RThr->PitBrightWidthBH);

	ui->checkBoxLineMode			->setChecked(RThr->LineMode				);
	ui->EditLineOKMinLength			->setValue(RThr->LineOKMinLength		);
	ui->EditLineMaxWidth			->setValue(RThr->LineMaxWidth			);
	ui->EditLineMinDensityPercent	->setValue(RThr->LineMinDensityPercent	);
	ui->EditLineMinCluster			->setValue(RThr->LineMinCluster			);

	on_checkBoxHsvCheckMode_toggled(true);
	on_checkBoxHsvFixedColorMode_toggled(true);
}

void HistgramDotColorMatchingForm::ShowThreshold(void)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
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
		GraphThreshBR.AddXY(CenterBrightR+CDiffR-(BData->GetThresholdR(GetLayersBase())->Broad.BrightWidthRL*CenterBrightR/100)	,YMaxR);
		GraphThreshBR.AddXY(CenterBrightR+CDiffR+(BData->GetThresholdR(GetLayersBase())->Broad.BrightWidthRH*CenterBrightR/100)	,YMaxR);
		GraphThreshBG.AddXY(CenterBrightG+CDiffG-(BData->GetThresholdR(GetLayersBase())->Broad.BrightWidthGL*CenterBrightG/100)	,YMaxG);
		GraphThreshBG.AddXY(CenterBrightG+CDiffG+(BData->GetThresholdR(GetLayersBase())->Broad.BrightWidthGH*CenterBrightG/100)	,YMaxG);
		GraphThreshBB.AddXY(CenterBrightB+CDiffB-(BData->GetThresholdR(GetLayersBase())->Broad.BrightWidthBL*CenterBrightB/100)	,YMaxB);
		GraphThreshBB.AddXY(CenterBrightB+CDiffB+(BData->GetThresholdR(GetLayersBase())->Broad.BrightWidthBH*CenterBrightB/100)	,YMaxB);

		GraphThreshNR.AddXY(CenterBrightR+CDiffR-(BData->GetThresholdR(GetLayersBase())->Narrow.BrightWidthRL*CenterBrightR/100),YMaxR);
		GraphThreshNR.AddXY(CenterBrightR+CDiffR+(BData->GetThresholdR(GetLayersBase())->Narrow.BrightWidthRH*CenterBrightR/100),YMaxR);
		GraphThreshNG.AddXY(CenterBrightG+CDiffG-(BData->GetThresholdR(GetLayersBase())->Narrow.BrightWidthGL*CenterBrightG/100),YMaxG);
		GraphThreshNG.AddXY(CenterBrightG+CDiffG+(BData->GetThresholdR(GetLayersBase())->Narrow.BrightWidthGH*CenterBrightG/100),YMaxG);
		GraphThreshNB.AddXY(CenterBrightB+CDiffB-(BData->GetThresholdR(GetLayersBase())->Narrow.BrightWidthBL*CenterBrightB/100),YMaxB);
		GraphThreshNB.AddXY(CenterBrightB+CDiffB+(BData->GetThresholdR(GetLayersBase())->Narrow.BrightWidthBH*CenterBrightB/100),YMaxB);

		return;
	}
}
void	HistgramDotColorMatchingForm::GetDataFromWindow(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GetDataFromWindowFromNo(LayerList.GetFirst()->GetValue());
}
void	HistgramDotColorMatchingForm::GetDataFromWindowFromNo(int LayerNo)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerNo!=D->Layer)
			continue;
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			continue;

		BData->SetItemName(ui->EditItemName	->text());
		DotColorMatchingThreshold	*DThr=BData->GetThresholdW(GetLayersBase());
		DThr->Broad.BrightWidthRL		=ui->EditBrightWidthBRL	->value();
		DThr->Broad.BrightWidthRH		=ui->EditBrightWidthBRH	->value();
		DThr->Broad.BrightWidthGL		=ui->EditBrightWidthBGL	->value();
		DThr->Broad.BrightWidthGH		=ui->EditBrightWidthBGH	->value();
		DThr->Broad.BrightWidthBL		=ui->EditBrightWidthBBL	->value();
		DThr->Broad.BrightWidthBH		=ui->EditBrightWidthBBH	->value();
		DThr->Broad.OrgBrightWidthRL	=OrgBrightWidthBRL;
		DThr->Broad.OrgBrightWidthRH	=OrgBrightWidthBRH;
		DThr->Broad.OrgBrightWidthGL	=OrgBrightWidthBGL;
		DThr->Broad.OrgBrightWidthGH	=OrgBrightWidthBGH;
		DThr->Broad.OrgBrightWidthBL	=OrgBrightWidthBBL;
		DThr->Broad.OrgBrightWidthBH	=OrgBrightWidthBBH;
		DThr->Broad.OKDot				=ui->EditOKDotB				->value();
		DThr->Broad.OKLength			=ui->EditOKLengthB			->value();
		DThr->Broad.RThrOffsetL			=ui->EditRThrOffsetBL	->value();
		DThr->Broad.RThrOffsetH			=ui->EditRThrOffsetBH	->value();
		DThr->Broad.GThrOffsetL			=ui->EditGThrOffsetBL	->value();
		DThr->Broad.GThrOffsetH			=ui->EditGThrOffsetBH	->value();
		DThr->Broad.BThrOffsetL			=ui->EditBThrOffsetBL	->value();
		DThr->Broad.BThrOffsetH			=ui->EditBThrOffsetBH	->value();


		DThr->Narrow.BrightWidthRL		=ui->EditBrightWidthNRL	->value();
		DThr->Narrow.BrightWidthRH		=ui->EditBrightWidthNRH	->value();
		DThr->Narrow.BrightWidthGL		=ui->EditBrightWidthNGL	->value();
		DThr->Narrow.BrightWidthGH		=ui->EditBrightWidthNGH	->value();
		DThr->Narrow.BrightWidthBL		=ui->EditBrightWidthNBL	->value();
		DThr->Narrow.BrightWidthBH		=ui->EditBrightWidthNBH	->value();
		DThr->Narrow.OrgBrightWidthRL	=OrgBrightWidthNRL;
		DThr->Narrow.OrgBrightWidthRH	=OrgBrightWidthNRH;
		DThr->Narrow.OrgBrightWidthGL	=OrgBrightWidthNGL;
		DThr->Narrow.OrgBrightWidthGH	=OrgBrightWidthNGH;
		DThr->Narrow.OrgBrightWidthBL	=OrgBrightWidthNBL;
		DThr->Narrow.OrgBrightWidthBH	=OrgBrightWidthNBH;
		DThr->Narrow.OKDot				=ui->EditOKDotN			->value();
		DThr->Narrow.OKLength			=ui->EditOKLengthN		->value();
		DThr->Narrow.RThrOffsetL		=ui->EditRThrOffsetNL	->value();
		DThr->Narrow.RThrOffsetH		=ui->EditRThrOffsetNH	->value();
		DThr->Narrow.GThrOffsetL		=ui->EditGThrOffsetNL	->value();
		DThr->Narrow.GThrOffsetH		=ui->EditGThrOffsetNH	->value();
		DThr->Narrow.BThrOffsetL		=ui->EditBThrOffsetNL	->value();
		DThr->Narrow.BThrOffsetH		=ui->EditBThrOffsetNH	->value();

		DThr->VarietySigma		=ui->doubleSpinBoxVarietySigma	->value();
		DThr->BackGroundOKDot	=ui->EditBackGroundOKDot	->value();
		DThr->BackGroundOKLength=ui->EditBackGroundOKLength	->value();
		DThr->UseBackGround		=ui->checkBoxUseBackGround	->isChecked();

		DThr->AdjustBlack		=ui->EditAdjustBlack	->value();
		DThr->AdjustWhite		=ui->EditAdjustWhite	->value();
		DThr->AdjustContribute	=ui->EditAdjustContribute->value();
		DThr->AreaSearchX		=ui->EditAreaSearchX	->value();
		DThr->AreaSearchY		=ui->EditAreaSearchY	->value();
		DThr->SelfSearch		=ui->EditSelfSearch		->value();
		DThr->MaxAreaSearch		=ui->EditMaxAreaSearch	->value();
		DThr->MaxSelfSearch		=ui->EditMaxSelfSearch	->value();
		DThr->PreciseSearch		=ui->checkBoxPreciseSearch	->isChecked();
		DThr->Clusterize		=ui->checkBoxClusterize	->isChecked();
		DThr->MultiSpotDot		=ui->EditMultiSpotDot	->value();
		DThr->MultiSpotCount	=ui->EditMultiSpotCount	->value();
		DThr->MultiSpotDotGathered		=ui->EditMultiSpotDotGathered	->value();
		DThr->MultiSpotCountGathered	=ui->EditMultiSpotCountGathered	->value();
		DThr->MultiSpotLengthGathered	=ui->EditMultiSpotLengthGathered->value();
		DThr->EnableT2M			=ui->checkBoxEnableT2M	->isChecked();
		DThr->EnableM2T			=ui->checkBoxEnableM2T	->isChecked();

		DThr->ScratchStartDirection	=ui->doubleSpinBoxScratchStartDirection	->value();
		DThr->ScratchRotationAngle	=ui->doubleSpinBoxScratchRotationAngle	->value();
		DThr->ScratchVariety		=ui->doubleSpinBoxScratchVariety		->value();
		DThr->ScratchDetectLevelH	=ui->EditScratchDetectLevelH			->value();
		DThr->ScratchDetectLevelL	=ui->EditScratchDetectLevelL			->value();
		DThr->ScratchMaxWidth		=ui->EditScratchMaxWidth				->value();
		DThr->ScratchEnable			=ui->checkBoxScratchEnable				->isChecked();
		DThr->ScratchUseMaster		=ui->checkBoxScratchUseMaster			->isChecked();
		DThr->ScratchVOffset		=ui->doubleSpinBoxScratchVOffset		->value();
		DThr->ScratchDiff			=ui->doubleSpinBoxScratchDiff			->value();
		
		DThr->RedCheckMode			=ui->checkBoxRedCheckMode				->isChecked();
		DThr->RedHighRate			=ui->EditRedHighRate					->value	();
		DThr->RedMinBrightness		=ui->EditRedMinBrightness				->value	();
		DThr->RedGBMerginRate		=ui->EditRedGBMerginRate				->value	();
		DThr->RedGBMerginOffset		=ui->EditRedGBMerginOffset				->value	();
		DThr->RedOKDot				=ui->EditRedOKDot						->value	();
		DThr->RedShrink				=ui->EditRedShrink						->value	();

		DThr->MatchBrightnessByLayerH=ui->EditMatchBrightnessByLayerH		->value	();
		DThr->MatchBrightnessByLayerL=ui->EditMatchBrightnessByLayerL		->value	();

		int	L=ui->comboBoxUseOneLayer	->currentIndex();
		if(L==0){
			DThr->UseOneLayer=0xFF;
		}
		else{
			DThr->UseOneLayer=L-1;
		}

		DThr->HsvCheckMode		=ui->checkBoxHsvCheckMode		->isChecked();
		DThr->HsvFixedColorMode	=ui->checkBoxHsvFixedColorMode	->isChecked();

		DThr->HsvPHL	=ui->EditHsvPHL	->value();
		DThr->HsvPHH	=ui->EditHsvPHH	->value();
		DThr->HsvPSL	=ui->EditHsvPSL	->value();
		DThr->HsvPSH	=ui->EditHsvPSH	->value();
		DThr->HsvPVL	=ui->EditHsvPVL	->value();
		DThr->HsvPVH	=ui->EditHsvPVH	->value();

		DThr->HsvDHL	=ui->EditHsvDHL	->value();
		DThr->HsvDHH	=ui->EditHsvDHH	->value();
		DThr->HsvDSL	=ui->EditHsvDSL	->value();
		DThr->HsvDSH	=ui->EditHsvDSH	->value();
		DThr->HsvDVL	=ui->EditHsvDVL	->value();
		DThr->HsvDVH	=ui->EditHsvDVH	->value();

		DThr->HsvH		=ui->EditHsvH	->value();
		DThr->HsvS		=ui->EditHsvS	->value();
		DThr->HsvV		=ui->EditHsvV	->value();

		DThr->HsvOKDot		=ui->EditHsvOKDot	->value();
		DThr->HsvOKLength	=ui->EditHsvOKLength->value();

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

		DThr->PitMode			=ui->checkBoxPitMode			->isChecked();
		DThr->PitBrightWidthRL	=ui->EditPitBrightWidthRL		->value();
		DThr->PitBrightWidthRH	=ui->EditPitBrightWidthRH		->value();
		DThr->PitBrightWidthGL	=ui->EditPitBrightWidthGL		->value();
		DThr->PitBrightWidthGH	=ui->EditPitBrightWidthGH		->value();
		DThr->PitBrightWidthBL	=ui->EditPitBrightWidthBL		->value();
		DThr->PitBrightWidthBH	=ui->EditPitBrightWidthBH		->value();

		DThr->LineMode				=ui->checkBoxLineMode			->isChecked();
		DThr->LineOKMinLength		=ui->EditLineOKMinLength		->value();
		DThr->LineMaxWidth			=ui->EditLineMaxWidth			->value();
		DThr->LineMinDensityPercent	=ui->EditLineMinDensityPercent	->value();
		DThr->LineMinCluster		=ui->EditLineMinCluster			->value();
	}
}

void	HistgramDotColorMatchingForm::SlotLineGraphDClickBR(int X,int Y)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
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

		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		if(ui->radioButtonDarkSide1->isChecked()==true){
			if(CenterBrightR!=0 && (CenterBrightR+CDiffR-X)>=0){
				Thr->Broad.BrightWidthRL=(CenterBrightR+CDiffR-X)*100/CenterBrightR;
				ui->EditBrightWidthBRL->setValue(Thr->Broad.BrightWidthRL);
				ShowThreshold();
			}
		}
		else{
			if(CenterBrightR!=0 && (X-(CenterBrightR+CDiffR))>=0){
				Thr->Broad.BrightWidthRH=(X-(CenterBrightR+CDiffR))*100/CenterBrightR;
				ui->EditBrightWidthBRH->setValue(Thr->Broad.BrightWidthRH);
				ShowThreshold();
			}
		}
		on_ButtonCalc_clicked();
		LGraphBR.repaint();
		return;
	}
}

void	HistgramDotColorMatchingForm::SlotLineGraphDClickBG(int X,int Y)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			continue;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

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

		if(ui->radioButtonDarkSide1->isChecked()==true){
			if(CenterBrightG!=0 && (CenterBrightG+CDiffG-X)>=0){
				Thr->Broad.BrightWidthGL=(CenterBrightG+CDiffG-X)*100/CenterBrightG;
				ui->EditBrightWidthBGL->setValue(Thr->Broad.BrightWidthGL);
				ShowThreshold();
			}
		}
		else{
			if(CenterBrightG!=0 && (X-(CenterBrightG+CDiffG))>=0){
				Thr->Broad.BrightWidthGH=(X-(CenterBrightG+CDiffG))*100/CenterBrightG;
				ui->EditBrightWidthBGH->setValue(Thr->Broad.BrightWidthGH);
				ShowThreshold();
			}
		}
		on_ButtonCalc_clicked();
		LGraphBG.repaint();
		return;
	}
}

void	HistgramDotColorMatchingForm::SlotLineGraphDClickBB(int X,int Y)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			continue;

		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
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

		if(ui->radioButtonDarkSide1->isChecked()==true){
			if(CenterBrightB!=0 && (CenterBrightB+CDiffB-X)>=0){
				Thr->Broad.BrightWidthBL=(CenterBrightB+CDiffB-X)*100/CenterBrightB;
				ui->EditBrightWidthBBL->setValue(Thr->Broad.BrightWidthBL);
				ShowThreshold();
			}
		}
		else{
			if(CenterBrightB!=0 && (X-(CenterBrightB+CDiffB))>=0){
				Thr->Broad.BrightWidthBH=(X-(CenterBrightB+CDiffB))*100/CenterBrightB;
				ui->EditBrightWidthBBH->setValue(Thr->Broad.BrightWidthBH);
				ShowThreshold();
			}
		}
		on_ButtonCalc_clicked();
		LGraphBB.repaint();
		return;
	}
}

void	HistgramDotColorMatchingForm::SlotLineGraphDClickNR(int X,int Y)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
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

		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		if(ui->radioButtonDarkSide1->isChecked()==true){
			if(CenterBrightR!=0 && (CenterBrightR+CDiffR-X)>=0){
				Thr->Narrow.BrightWidthRL=(CenterBrightR+CDiffR-X)*100/CenterBrightR;
				ui->EditBrightWidthNRL->setValue(Thr->Narrow.BrightWidthRL);
				ShowThreshold();
			}
		}
		else{
			if(CenterBrightR!=0 && (X-(CenterBrightR+CDiffR))>=0){
				Thr->Narrow.BrightWidthRH=(X-(CenterBrightR+CDiffR))*100/CenterBrightR;
				ui->EditBrightWidthNRH->setValue(Thr->Narrow.BrightWidthRH);
				ShowThreshold();
			}
		}
		on_ButtonCalc_clicked();
		LGraphNR.repaint();
		return;
	}
}

void	HistgramDotColorMatchingForm::SlotLineGraphDClickNG(int X,int Y)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			continue;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

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

		if(ui->radioButtonDarkSide1->isChecked()==true){
			if(CenterBrightG!=0 && (CenterBrightG+CDiffG-X)>=0){
				Thr->Narrow.BrightWidthGL=(CenterBrightG+CDiffG-X)*100/CenterBrightG;
				ui->EditBrightWidthNGL->setValue(Thr->Narrow.BrightWidthGL);
				ShowThreshold();
			}
		}
		else{
			if(CenterBrightG!=0 && (X-(CenterBrightG+CDiffG))>=0){
				Thr->Narrow.BrightWidthGH=(X-(CenterBrightG+CDiffG))*100/CenterBrightG;
				ui->EditBrightWidthNGH->setValue(Thr->Narrow.BrightWidthGH);
				ShowThreshold();
			}
		}
		on_ButtonCalc_clicked();
		LGraphNG.repaint();
		return;
	}
}

void	HistgramDotColorMatchingForm::SlotLineGraphDClickNB(int X,int Y)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			continue;

		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
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

		if(ui->radioButtonDarkSide1->isChecked()==true){
			if(CenterBrightB!=0 && (CenterBrightB+CDiffB-X)>=0){
				Thr->Narrow.BrightWidthBL=(CenterBrightB+CDiffB-X)*100/CenterBrightB;
				ui->EditBrightWidthNBL->setValue(Thr->Narrow.BrightWidthBL);
				ShowThreshold();
			}
		}
		else{
			if(CenterBrightB!=0 && (X-(CenterBrightB+CDiffB))>=0){
				Thr->Narrow.BrightWidthBH=(X-(CenterBrightB+CDiffB))*100/CenterBrightB;
				ui->EditBrightWidthNBH->setValue(Thr->Narrow.BrightWidthBH);
				ShowThreshold();
			}
		}
		on_ButtonCalc_clicked();
		LGraphNB.repaint();
		return;
	}
}
void	HistgramDotColorMatchingForm::SlotLayerClicked()
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
void HistgramDotColorMatchingForm::on_ButtonRelrectOnlyDotColorMatching_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_17)/*"Reflecting ONE DotColorMatching threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one DotColorMatching threshold");
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

void HistgramDotColorMatchingForm::on_ButtonReflectAllDotColorMatchings_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_18)/*"Reflecting ALL DotColorMatchings\' threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all DotColorMatchings threshold");
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

void HistgramDotColorMatchingForm::on_ButtonSaveToLibrary_clicked()
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			continue;
		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	LLib(Container);
		if(Container->GetLibrary(LibID ,LLib)==true){
			DotColorMatchingLibrary	*ALib=dynamic_cast<DotColorMatchingLibrary *>(LLib.GetLibrary(ThresholdLevel));
			DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			Container->Update(LLib);
			return;
		}
	}
}

void HistgramDotColorMatchingForm::on_ButtonLoadFromLibrary_clicked()
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	LLib(Container);
		if(Container->GetLibrary(LibID ,LLib)==true){
			DotColorMatchingLibrary	*ALib=dynamic_cast<DotColorMatchingLibrary *>(LLib.GetLibrary(ThresholdLevel));
			DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			return;
		}
	}
}

void HistgramDotColorMatchingForm::on_ButtonClose_clicked()
{
	close();
}

void HistgramDotColorMatchingForm::on_pushButtonChangeLib_clicked()
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
			DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
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

void HistgramDotColorMatchingForm::on_ButtonCalc_clicked()
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
			DotColorMatchingItem	*nBData=dynamic_cast<DotColorMatchingItem *>(DA);
			if(nBData==NULL)
				continue;

			GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
			PacketReq.BuildData(sRoot,sName,DotColorMatchingReqTryThresholdCommand ,DotColorMatchingSendTryThresholdCommand);
			DotColorMatchingItem	*BData=&((DotColorMatchingReqTryThreshold *)PacketReq.Data)->Threshold;
			((DotColorMatchingReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
			((DotColorMatchingReqTryThreshold *)PacketReq.Data)->Layer			=D->Layer;
			((DotColorMatchingReqTryThreshold *)PacketReq.Data)->DotColorMatchingItemID	=DA->GetID();

			DotColorMatchingThreshold	*DThr=BData->GetThresholdW(GetLayersBase());
			DThr->Broad.BrightWidthRL		=ui->EditBrightWidthBRL	->value();
			DThr->Broad.BrightWidthRH		=ui->EditBrightWidthBRH	->value();
			DThr->Broad.BrightWidthGL		=ui->EditBrightWidthBGL	->value();
			DThr->Broad.BrightWidthGH		=ui->EditBrightWidthBGH	->value();
			DThr->Broad.BrightWidthBL		=ui->EditBrightWidthBBL	->value();
			DThr->Broad.BrightWidthBH		=ui->EditBrightWidthBBH	->value();

			DThr->Broad.OrgBrightWidthRL	=OrgBrightWidthBRL;
			DThr->Broad.OrgBrightWidthRH	=OrgBrightWidthBRH;
			DThr->Broad.OrgBrightWidthGL	=OrgBrightWidthBGL;
			DThr->Broad.OrgBrightWidthGH	=OrgBrightWidthBGH;
			DThr->Broad.OrgBrightWidthBL	=OrgBrightWidthBBL;
			DThr->Broad.OrgBrightWidthBH	=OrgBrightWidthBBH;
			DThr->Broad.OKDot				=ui->EditOKDotB				->value();
			DThr->Broad.OKLength			=ui->EditOKLengthB			->value();

			DThr->Broad.RThrOffsetL			=ui->EditRThrOffsetBL	->value();
			DThr->Broad.RThrOffsetH			=ui->EditRThrOffsetBH	->value();
			DThr->Broad.GThrOffsetL			=ui->EditGThrOffsetBL	->value();
			DThr->Broad.GThrOffsetH			=ui->EditGThrOffsetBH	->value();
			DThr->Broad.BThrOffsetL			=ui->EditBThrOffsetBL	->value();
			DThr->Broad.BThrOffsetH			=ui->EditBThrOffsetBH	->value();

			DThr->Narrow.BrightWidthRL		=ui->EditBrightWidthNRL	->value();
			DThr->Narrow.BrightWidthRH		=ui->EditBrightWidthNRH	->value();
			DThr->Narrow.BrightWidthGL		=ui->EditBrightWidthNGL	->value();
			DThr->Narrow.BrightWidthGH		=ui->EditBrightWidthNGH	->value();
			DThr->Narrow.BrightWidthBL		=ui->EditBrightWidthNBL	->value();
			DThr->Narrow.BrightWidthBH		=ui->EditBrightWidthNBH	->value();

			DThr->Narrow.OrgBrightWidthRL	=OrgBrightWidthNRL;
			DThr->Narrow.OrgBrightWidthRH	=OrgBrightWidthNRH;
			DThr->Narrow.OrgBrightWidthGL	=OrgBrightWidthNGL;
			DThr->Narrow.OrgBrightWidthGH	=OrgBrightWidthNGH;
			DThr->Narrow.OrgBrightWidthBL	=OrgBrightWidthNBL;
			DThr->Narrow.OrgBrightWidthBH	=OrgBrightWidthNBH;
			DThr->Narrow.OKDot				=ui->EditOKDotN				->value();
			DThr->Narrow.OKLength			=ui->EditOKLengthN			->value();

			DThr->Narrow.RThrOffsetL			=ui->EditRThrOffsetNL	->value();
			DThr->Narrow.RThrOffsetH			=ui->EditRThrOffsetNH	->value();
			DThr->Narrow.GThrOffsetL			=ui->EditGThrOffsetNL	->value();
			DThr->Narrow.GThrOffsetH			=ui->EditGThrOffsetNH	->value();
			DThr->Narrow.BThrOffsetL			=ui->EditBThrOffsetNL	->value();
			DThr->Narrow.BThrOffsetH			=ui->EditBThrOffsetNH	->value();


			DThr->VarietySigma		=ui->doubleSpinBoxVarietySigma	->value();
			DThr->BackGroundOKDot	=ui->EditBackGroundOKDot	->value();
			DThr->BackGroundOKLength=ui->EditBackGroundOKLength	->value();
			DThr->UseBackGround		=ui->checkBoxUseBackGround	->isChecked();

			DThr->AdjustBlack			=ui->EditAdjustBlack	->value();
			DThr->AdjustWhite			=ui->EditAdjustWhite	->value();
			DThr->AdjustContribute		=ui->EditAdjustContribute->value();
			DThr->AreaSearchX			=ui->EditAreaSearchX	->value();
			DThr->AreaSearchY			=ui->EditAreaSearchY	->value();
			DThr->SelfSearch			=ui->EditSelfSearch		->value();
			DThr->MaxAreaSearch			=ui->EditMaxAreaSearch	->value();
			DThr->MaxSelfSearch			=ui->EditMaxSelfSearch	->value();
			DThr->PreciseSearch			=ui->checkBoxPreciseSearch	->isChecked();
			DThr->Clusterize			=ui->checkBoxClusterize	->isChecked();
			DThr->MultiSpotDot			=ui->EditMultiSpotDot	->value();
			DThr->MultiSpotCount		=ui->EditMultiSpotCount	->value();
			DThr->MultiSpotDotGathered		=ui->EditMultiSpotDotGathered	->value();
			DThr->MultiSpotCountGathered	=ui->EditMultiSpotCountGathered	->value();
			DThr->MultiSpotLengthGathered	=ui->EditMultiSpotLengthGathered->value();
			DThr->EnableT2M				=ui->checkBoxEnableT2M	->isChecked();
			DThr->EnableM2T				=ui->checkBoxEnableM2T	->isChecked();

			DThr->ScratchStartDirection	=ui->doubleSpinBoxScratchStartDirection	->value();
			DThr->ScratchRotationAngle	=ui->doubleSpinBoxScratchRotationAngle	->value();
			DThr->ScratchVariety		=ui->doubleSpinBoxScratchVariety		->value();
			DThr->ScratchDetectLevelH	=ui->EditScratchDetectLevelH			->value();
			DThr->ScratchDetectLevelL	=ui->EditScratchDetectLevelL			->value();
			DThr->ScratchMaxWidth		=ui->EditScratchMaxWidth				->value();
			DThr->ScratchEnable			=ui->checkBoxScratchEnable				->isChecked();
			DThr->ScratchUseMaster		=ui->checkBoxScratchUseMaster			->isChecked();
			DThr->ScratchVOffset		=ui->doubleSpinBoxScratchVOffset		->value();
			DThr->ScratchDiff			=ui->doubleSpinBoxScratchDiff			->value();
		
			DThr->RedCheckMode			=ui->checkBoxRedCheckMode				->isChecked();
			DThr->RedHighRate			=ui->EditRedHighRate					->value	();
			DThr->RedMinBrightness		=ui->EditRedMinBrightness				->value	();
			DThr->RedGBMerginRate		=ui->EditRedGBMerginRate				->value	();
			DThr->RedGBMerginOffset		=ui->EditRedGBMerginOffset				->value	();
			DThr->RedOKDot				=ui->EditRedOKDot						->value	();
			DThr->RedShrink				=ui->EditRedShrink						->value	();

			DThr->MatchBrightnessByLayerH=ui->EditMatchBrightnessByLayerH		->value	();
			DThr->MatchBrightnessByLayerL=ui->EditMatchBrightnessByLayerL		->value	();

			DThr->HsvCheckMode		=ui->checkBoxHsvCheckMode		->isChecked();
			DThr->HsvFixedColorMode	=ui->checkBoxHsvFixedColorMode	->isChecked();

			DThr->HsvPHL	=ui->EditHsvPHL	->value();
			DThr->HsvPHH	=ui->EditHsvPHH	->value();
			DThr->HsvPSL	=ui->EditHsvPSL	->value();
			DThr->HsvPSH	=ui->EditHsvPSH	->value();
			DThr->HsvPVL	=ui->EditHsvPVL	->value();
			DThr->HsvPVH	=ui->EditHsvPVH	->value();

			DThr->HsvDHL	=ui->EditHsvDHL	->value();
			DThr->HsvDHH	=ui->EditHsvDHH	->value();
			DThr->HsvDSL	=ui->EditHsvDSL	->value();
			DThr->HsvDSH	=ui->EditHsvDSH	->value();
			DThr->HsvDVL	=ui->EditHsvDVL	->value();
			DThr->HsvDVH	=ui->EditHsvDVH	->value();

			DThr->HsvH		=ui->EditHsvH	->value();
			DThr->HsvS		=ui->EditHsvS	->value();
			DThr->HsvV		=ui->EditHsvV	->value();

			DThr->HsvOKDot		=ui->EditHsvOKDot	->value();
			DThr->HsvOKLength	=ui->EditHsvOKLength->value();

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

			DThr->PitMode			=ui->checkBoxPitMode		->isChecked();
			DThr->PitBrightWidthRL	=ui->EditPitBrightWidthRL	->value();
			DThr->PitBrightWidthRH	=ui->EditPitBrightWidthRH	->value();
			DThr->PitBrightWidthGL	=ui->EditPitBrightWidthGL	->value();
			DThr->PitBrightWidthGH	=ui->EditPitBrightWidthGH	->value();
			DThr->PitBrightWidthBL	=ui->EditPitBrightWidthBL	->value();
			DThr->PitBrightWidthBH	=ui->EditPitBrightWidthBH	->value();

			DThr->LineMode				=ui->checkBoxLineMode			->isChecked();
			DThr->LineOKMinLength		=ui->EditLineOKMinLength		->value();
			DThr->LineMaxWidth			=ui->EditLineMaxWidth			->value();
			DThr->LineMinDensityPercent	=ui->EditLineMinDensityPercent	->value();
			DThr->LineMinCluster		=ui->EditLineMinCluster			->value();

			int	L=ui->comboBoxUseOneLayer	->currentIndex();
			if(L==0){
				DThr->UseOneLayer=0xFF;
			}
			else{
				DThr->UseOneLayer=L-1;
			}

			GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
			if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

				DotColorMatchingSendTryThreshold	*R=((DotColorMatchingSendTryThreshold *)PacketSend.Data);
				ui->labelResult		->setText(QString::number(R->NGDot	 ));
				ui->labelResultLen	->setText(QString::number(R->NGLength,'f',1));
					
				ui->EditShowShiftXY->setText(QString::number(R->Result->GetTotalShiftedX())
											+QString(/**/",")
											+QString::number(R->Result->GetTotalShiftedY()));
				ui->spinBoxCurrentRotationPatternNo->setValue(R->CurrentRotationPatternNo);
				
				ScratchEnable		=ui->checkBoxScratchEnable				->isChecked();
				ScratchResultAngle	=R->ScratchResultAngle;
				GraphScrMaster.DeleteXY();
				GraphScrTarget.DeleteXY();
				GraphScrCoef  .DeleteXY();
				for(int i=max(0,R->ScratchResultStartDim);i<R->ScratchTableDimLen && i<R->ScratchResultEndDim;i++){
					GraphScrTarget.AddXY(i,R->ScratchTableDim[i].Brightness);
					GraphScrCoef  .AddXY(i,R->ScratchTableDim[i].CoefD);
				}
				for(int i=max(0,R->ScratchResultStartDim);i<R->ScratchTableDimLen && i<R->ScratchResultEndDim;i++){
					GraphScrMaster.AddXY(i,R->ScratchTableMasterDim[i].Brightness);
				}
				ScrGraphMaster.repaint();
				ScrGraphTarget.repaint();
				ScrGraphCoef  .repaint();

				ui->labelScratchResultAngle	->setText(QString::number(R->ScratchResultAngle,'f',2));
				ui->labelScratchResultWidth	->setText(QString::number(R->ScratchResultWidth));
				ui->labelScratchResultPeakH	->setText(QString::number(R->ScratchResultPeakH,'f',2));
				ui->labelScratchResultPeakL	->setText(QString::number(R->ScratchResultPeakL,'f',2));
				ui->labelScratchResultVariety->setText(QString::number((double)R->ScratchResultVariety,'f',3));
				
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

void	HistgramDotColorMatchingForm::SlotValueChanged(int n)
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}
void HistgramDotColorMatchingForm::on_toolButtonSimShowItem_clicked()
{
	ModeShowItem=ui->toolButtonSimShowItem ->isChecked();
	SimPanel.SetModeShowBlock(ModeShowItem);
	SimPanel.repaint();
}

void HistgramDotColorMatchingForm::on_toolButtonSimShowNGMark_clicked()
{
	SimPanel.SetModeShowBrightnessNG(ui->toolButtonSimShowNGMark ->isChecked());
	SimPanel.repaint();
}

void HistgramDotColorMatchingForm::on_pushButtonSimShowCenterPos_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.repaint();
			}
		}
	}
}


void HistgramDotColorMatchingForm::on_EditAdjustBlack_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditAdjustWhite_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxClusterize_clicked()
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxPreciseSearch_stateChanged(int arg1)
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditBrightWidthBRL_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		Thr->Broad.BrightWidthRL=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphBR.repaint();
		return;
	}
}

void HistgramDotColorMatchingForm::on_EditBrightWidthBRH_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->Broad.BrightWidthRH=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphBR.repaint();
		return;
	}
}

void HistgramDotColorMatchingForm::on_EditBrightWidthBGL_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->Broad.BrightWidthGL=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphBG.repaint();
		return;
	}

}

void HistgramDotColorMatchingForm::on_EditBrightWidthBGH_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->Broad.BrightWidthGH=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphBG.repaint();
		return;
	}
}

void HistgramDotColorMatchingForm::on_EditBrightWidthBBL_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->Broad.BrightWidthBL=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphBB.repaint();
		return;
	}

}

void HistgramDotColorMatchingForm::on_EditBrightWidthBBH_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->Broad.BrightWidthBH=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphBB.repaint();
		return;
	}
}


void HistgramDotColorMatchingForm::on_EditBrightWidthNRL_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		Thr->Narrow.BrightWidthRL=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphNR.repaint();
		return;
	}
}

void HistgramDotColorMatchingForm::on_EditBrightWidthNRH_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->Narrow.BrightWidthRH=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphNR.repaint();
		return;
	}
}

void HistgramDotColorMatchingForm::on_EditBrightWidthNGL_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->Narrow.BrightWidthGL=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphNG.repaint();
		return;
	}

}

void HistgramDotColorMatchingForm::on_EditBrightWidthNGH_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->Narrow.BrightWidthGH=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphNG.repaint();
		return;
	}
}

void HistgramDotColorMatchingForm::on_EditBrightWidthNBL_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->Narrow.BrightWidthBL=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphNB.repaint();
		return;
	}

}

void HistgramDotColorMatchingForm::on_EditBrightWidthNBH_valueChanged(int X)
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->Narrow.BrightWidthBH=X;
		ShowThreshold();
		if(OnChanging==false){
			on_ButtonCalc_clicked();
		}
		LGraphNB.repaint();
		return;
	}
}


void HistgramDotColorMatchingForm::on_EditOKDotB_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxOKDotBMM->setValue(TransformPixelToUnitSquare(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditOKDotN_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxOKDotNMM->setValue(TransformPixelToUnitSquare(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxOKDotBMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditOKDotB->setValue(RoundInt(TransformUnitToPixelSquare(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxOKDotNMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditOKDotN->setValue(RoundInt(TransformUnitToPixelSquare(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditAreaSearchX_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxAreaSearchXMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxAreaSearchXMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditAreaSearchX->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();

}


void HistgramDotColorMatchingForm::on_EditAreaSearchY_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxAreaSearchYMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxAreaSearchYMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditAreaSearchY->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();

}


void HistgramDotColorMatchingForm::on_EditSelfSearch_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxSelfSearchMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxSelfSearchMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditSelfSearch->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_pushButtonReqMasterImage_clicked()
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
		DotColorMatchingItem	*nBData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,DotColorMatchingReqRotationMasterImageCommand ,DotColorMatchingSendRotationMasterImageCommand);
		((DotColorMatchingReqRotationMasterImage *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((DotColorMatchingReqRotationMasterImage *)PacketReq.Data)->DotColorMatchingItemID	=DA->GetID();
		((DotColorMatchingReqRotationMasterImage *)PacketReq.Data)->CurrentRotationPatternNo=ui->spinBoxCurrentRotationPatternNo->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			DotColorMatchingSendRotationMasterImage	*R=((DotColorMatchingSendRotationMasterImage *)PacketSend.Data);
			ui->labelRotationMasterImage	->setPixmap(QPixmap::fromImage(R->MasterImage));
			ui->labelRotationMasterImageSub	->setPixmap(QPixmap::fromImage(R->MasterImageSub));
			break;
		}
	}	
}

void HistgramDotColorMatchingForm::on_ButtonSetToOrigin_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_17)/*"Reflecting ONE DotColorMatching threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one DotColorMatching threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_SetToOrigin;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void HistgramDotColorMatchingForm::on_EditMultiSpotDot_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditMultiSpotCount_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditRThrOffsetBL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditRThrOffsetBH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditGThrOffsetBL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditGThrOffsetBH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditBThrOffsetBL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditBThrOffsetBH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditRThrOffsetNL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditRThrOffsetNH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditGThrOffsetNL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditGThrOffsetNH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditBThrOffsetNL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditBThrOffsetNH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxEnableM2T_clicked()
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxEnableT2M_clicked()
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditOKLengthB_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxOKLengthBMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxOKLengthBMM_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditOKLengthB->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditOKLengthN_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxOKLengthNMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxOKLengthNMM_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditOKLengthN->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxScratchEnable_clicked()
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditScratchDetectLevelH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditScratchDetectLevelL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditScratchMaxWidth_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_comboBoxUseOneLayer_currentIndexChanged(int index)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}
void HistgramDotColorMatchingForm::on_doubleSpinBoxScratchStartDirection_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxScratchRotationAngle_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxScratchVariety_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxScratchUseMaster_clicked()
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxScratchVOffset_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxRedCheckMode_clicked()
{
	if(OnChanging==true){
		return;
	}
	ShowRed();
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditRedHighRate_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	ShowRed();
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditRedMinBrightness_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	ShowRed();
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditRedGBMerginRate_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	ShowRed();
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditRedGBMerginOffset_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	ShowRed();
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditRedOKDot_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditMaxAreaSearch_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditMaxSelfSearch_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}


void	HistgramDotColorMatchingForm::ShowRed(void)
{
	RedPanel.ShowRed(ui->EditRedHighRate		->value()
					,ui->EditRedMinBrightness	->value()
					,ui->EditRedGBMerginRate	->value()
					,ui->EditRedGBMerginOffset	->value());
}

void	HistgramDotColorMatchingForm::ShowRedInMouse(int X,int Y,QRgb d)
{
	QPalette	P=ui->frameRedColor->palette();
	P.setColor(QPalette::Window,d);
	ui->frameRedColor->setPalette(P);
}
void HistgramDotColorMatchingForm::on_tabWidget_currentChanged(int index)
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

void HistgramDotColorMatchingForm::on_spinBoxCurrentRotationPatternNo_valueChanged(int arg1)
{
    on_pushButtonReqMasterImage_clicked();
}

void HistgramDotColorMatchingForm::on_EditMatchBrightnessByLayerH_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditMatchBrightnessByLayerL_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxScratchDiff_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditRedShrink_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditBackGroundOKDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxBackGroundOKDotMM->setValue(TransformPixelToUnitSquare(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditBackGroundOKLength_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxBackGroundOKLengthMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxBackGroundOKDotMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditBackGroundOKDot->setValue(RoundInt(TransformUnitToPixelSquare(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxBackGroundOKLengthMM_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditBackGroundOKLength->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxUseBackGround_clicked()
{
	if(OnChanging==true)
		return;
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditHsvPHL_valueChanged(int arg1)
{
	ui->horizontalSliderHsvPH->setMinimum(-ui->EditHsvPHL->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvPHH_valueChanged(int arg1)
{
	ui->horizontalSliderHsvPH->setMaximum(ui->EditHsvPHH->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvDHL_valueChanged(int arg1)
{
	ui->horizontalSliderHsvDH->setMinimum(-ui->EditHsvDHL->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvDHH_valueChanged(int arg1)
{
	ui->horizontalSliderHsvDH->setMaximum(ui->EditHsvDHH->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvH_valueChanged(int arg1)
{
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvPSL_valueChanged(int arg1)
{
	ui->horizontalSliderHsvPS->setMinimum(-ui->EditHsvPSL->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvPSH_valueChanged(int arg1)
{
	ui->horizontalSliderHsvPS->setMaximum(ui->EditHsvPSH->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvDSL_valueChanged(int arg1)
{
	ui->horizontalSliderHsvDS->setMinimum(-ui->EditHsvDSL->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvDSH_valueChanged(int arg1)
{
	ui->horizontalSliderHsvDS->setMaximum(ui->EditHsvDSH->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvS_valueChanged(int arg1)
{
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvPVL_valueChanged(int arg1)
{
	ui->horizontalSliderHsvPV->setMinimum(-ui->EditHsvPVL->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvPVH_valueChanged(int arg1)
{
	ui->horizontalSliderHsvPV->setMaximum(ui->EditHsvPVH->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvDVL_valueChanged(int arg1)
{
	ui->horizontalSliderHsvDV->setMinimum(-ui->EditHsvDVL->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvDVH_valueChanged(int arg1)
{
	ui->horizontalSliderHsvDV->setMaximum(ui->EditHsvDVH->value());
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditHsvV_valueChanged(int arg1)
{
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditHsvOKDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxHsvOKDotMM->setValue(TransformPixelToUnitSquare(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxHsvOKDotMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditHsvOKDot->setValue(RoundInt(TransformUnitToPixelSquare(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_EditHsvOKLength_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxHsvOKLengthMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxHsvOKLengthMM_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditHsvOKLength->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
	OnChanging=false;

	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxHsvCheckMode_toggled(bool checked)
{
	bool	b=ui->checkBoxHsvCheckMode->isChecked();
	ui->EditHsvOKDot				->setEnabled(b);
	ui->doubleSpinBoxHsvOKDotMM		->setEnabled(b);
	ui->EditHsvOKLength				->setEnabled(b);
	ui->doubleSpinBoxHsvOKLengthMM	->setEnabled(b);
	ui->checkBoxHsvFixedColorMode	->setEnabled(b);
	ui->widgetHsvControl			->setEnabled(b);
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxHsvFixedColorMode_toggled(bool checked)
{
	bool	b=ui->checkBoxHsvFixedColorMode->isChecked();
	ui->EditHsvH->setEnabled(b);
	ui->EditHsvS->setEnabled(b);
	ui->EditHsvV->setEnabled(b);
	HSVTrialImage.Repaint();
	if(OnChanging==true){
		return;
	}
	on_ButtonCalc_clicked();
}

void	HistgramDotColorMatchingForm::SetHSVParam(void)
{
	HSVTrialImage.HSVParamData.HsvFixedColorMode=ui->checkBoxHsvFixedColorMode->isChecked();
	HSVTrialImage.HSVParamData.HsvPH=ui->horizontalSliderHsvPH->value();
	HSVTrialImage.HSVParamData.HsvDH=ui->horizontalSliderHsvDH->value();
	HSVTrialImage.HSVParamData.HsvPS=ui->horizontalSliderHsvPS->value();
	HSVTrialImage.HSVParamData.HsvDS=ui->horizontalSliderHsvDS->value();
	HSVTrialImage.HSVParamData.HsvPV=ui->horizontalSliderHsvPV->value();
	HSVTrialImage.HSVParamData.HsvDV=ui->horizontalSliderHsvDV->value();
	HSVTrialImage.HSVParamData.HsvH	=ui->EditHsvH->value();
	HSVTrialImage.HSVParamData.HsvS	=ui->EditHsvS->value();
	HSVTrialImage.HSVParamData.HsvV	=ui->EditHsvV->value();
}

void HistgramDotColorMatchingForm::on_horizontalSliderHsvPH_valueChanged(int value)
{
	HSVTrialImage.Repaint();
}

void HistgramDotColorMatchingForm::on_horizontalSliderHsvDH_valueChanged(int value)
{
	HSVTrialImage.Repaint();
}

void HistgramDotColorMatchingForm::on_horizontalSliderHsvPS_valueChanged(int value)
{
	HSVTrialImage.Repaint();
}

void HistgramDotColorMatchingForm::on_horizontalSliderHsvDS_valueChanged(int value)
{
	HSVTrialImage.Repaint();
}

void HistgramDotColorMatchingForm::on_horizontalSliderHsvPV_valueChanged(int value)
{
	HSVTrialImage.Repaint();
}

void HistgramDotColorMatchingForm::on_horizontalSliderHsvDV_valueChanged(int value)
{
	HSVTrialImage.Repaint();
}
void HistgramDotColorMatchingForm::SetHSVValue(int MasterH
											  ,int MasterS
											  ,int MasterV
											  ,int TargetH
											  ,int TargetS
											  ,int TargetV)
{
	QString	MasterStr	=QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_70)/*" H: "*/)+QString::number(MasterH)
						+QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_71)/*" S: "*/)+QString::number(MasterS)
						+QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_72)/*" V: "*/)+QString::number(MasterV);
	ui->labelMasterHSVValue->setText(MasterStr);

	QString	TargetStr	=QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_73)/*" H: "*/)+QString::number(TargetH)
						+QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_74)/*" S: "*/)+QString::number(TargetS)
						+QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_75)/*" V: "*/)+QString::number(TargetV);
	ui->labelTargetHSVValue->setText(TargetStr);

	int	HsvPHL	=ui->EditHsvPHL	->value();
	int	HsvPHH	=ui->EditHsvPHH	->value();
	int	HsvPSL	=ui->EditHsvPSL	->value();
	int	HsvPSH	=ui->EditHsvPSH	->value();
	int	HsvPVL	=ui->EditHsvPVL	->value();
	int	HsvPVH	=ui->EditHsvPVH	->value();
	int	HsvDHL	=ui->EditHsvDHL	->value();
	int	HsvDHH	=ui->EditHsvDHH	->value();
	int	HsvDSL	=ui->EditHsvDSL	->value();
	int	HsvDSH	=ui->EditHsvDSH	->value();
	int	HsvDVL	=ui->EditHsvDVL	->value();
	int	HsvDVH	=ui->EditHsvDVH	->value();
	
	int	MHL=(MasterH*(-HsvPHL+100)*0.01)-HsvDHL;
	int	MHH=(MasterH*( HsvPHH+100)*0.01)+HsvDHH;
	int	MSL=(MasterS*(-HsvPSL+100)*0.01)-HsvDSL;
	int	MSH=(MasterS*( HsvPSH+100)*0.01)+HsvDSH;
	int	MVL=(MasterV*(-HsvPVL+100)*0.01)-HsvDVL;
	int	MVH=(MasterV*( HsvPVH+100)*0.01)+HsvDVH;

	if(MHH-MHL>=360){
		MHL=0;
		MHH=360;
	}
	else{
		while(MHL<0)
		MHL+=360;
		while(MHL>=360)
			MHL-=360;
		
		while(MHH<0)
			MHH+=360;
		while(MHH>=360)
			MHH-=360;
	}

	QString	RangeStr=QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_76)/*" H: "*/)+QString::number(MHL)+QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_77)/*" �ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ"*/)+QString::number(MHH)
					+QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_78)/*" S: "*/)+QString::number(MSL)+QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_79)/*" �ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ"*/)+QString::number(MSH)
					+QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_80)/*" V: "*/)+QString::number(MVL)+QString(LangSolver.GetString(HistgramDotColorMatchingForm_LS,LID_81)/*" �ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ"*/)+QString::number(MVH);
	ui->labelHSVRange->setText(RangeStr);

}

void HistgramDotColorMatchingForm::ShowCurrentRGB(int R ,int G, int B)
{
	ui->EditCurrentR->setValue(R);
	ui->EditCurrentG->setValue(G);
	ui->EditCurrentB->setValue(B);
}
void HistgramDotColorMatchingForm::ShowRedRange( int RL,int RH
												,int GL,int GH
												,int BL,int BH)
{
	ui->EditRedRL->setValue(RL);
	ui->EditRedRH->setValue(RH);
	ui->EditRedGL->setValue(GL);
	ui->EditRedGH->setValue(GH);
	ui->EditRedBL->setValue(BL);
	ui->EditRedBH->setValue(BH);
}


void HistgramDotColorMatchingForm::on_pushButtonCopy_clicked()
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		GetLayersBase()->CopyThresholdToClipboard(Thr);
		return;
	}
}


void HistgramDotColorMatchingForm::on_pushButtonPaste_clicked()
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
		DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
		if(BData==NULL)
			return;
		DotColorMatchingThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		if(GetLayersBase()->PasteThresholdFromClipboard(Thr)==true){
			ShowLibrary(Thr);
		}
		return;
	}
	
}

void HistgramDotColorMatchingForm::on_listWidgetHistList_doubleClicked(const QModelIndex &index)
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



void HistgramDotColorMatchingForm::on_EditMultiSpotDotGathered_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
    on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditMultiSpotCountGathered_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
    on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditMultiSpotLengthGathered_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
    OnChanging=true;
    ui->doubleSpinBoxMultiSpotLengthGatheredMM->setValue(TransformPixelToUnit(HistgramPage,arg1));
    OnChanging=false;

    on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_doubleSpinBoxMultiSpotLengthGatheredMM_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
    OnChanging=true;
    ui->EditMultiSpotLengthGathered->setValue(RoundInt(TransformUnitToPixel(HistgramPage,arg1)));
    OnChanging=false;
    on_ButtonCalc_clicked();
}

void	HistgramDotColorMatchingForm::ShowSubBlockList(const SubtractItemContainer &src)
{
	ui->tableWidgetSubBlockList->setRowCount(src.GetCount());
	int	Row=0;
	for(SubtractItem *s=src.GetFirst();s!=NULL;s=s->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetSubBlockList, 0, Row,QString::number(s->ItemID));
		::SetDataToTable(ui->tableWidgetSubBlockList, 1, Row,QString::number(s->LibID));
		QString	LibName=GetLayersBase()->GetLibraryName(DefLibTypeDotColorMatchingInspect
														,s->LibID);
		::SetDataToTable(ui->tableWidgetSubBlockList, 2, Row,LibName);
	}
}

void HistgramDotColorMatchingForm::on_tableWidgetSubBlockList_itemSelectionChanged()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		LButtonList[D->Layer]->setChecked(true);
		//SimPanel.SetLayer(D->Layer);
		SimPanel.SetLayer(-1);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			DotColorMatchingItem	*BData=dynamic_cast<DotColorMatchingItem *>(DA);
			if(BData!=NULL){
				int	Row=ui->tableWidgetSubBlockList->currentRow();
				if(Row>=0){
					SubtractItem *s=BData->GetSubBlock().GetItem(Row);
					if(s!=NULL){
						SimPanel.SetSubtractItem(s->ItemID);
						SimPanel.repaint();
					}
				}
			}
		}
	}
}

void HistgramDotColorMatchingForm::on_tableWidgetSubBlockList_clicked(const QModelIndex &index)
{
	on_tableWidgetSubBlockList_itemSelectionChanged();
}


void HistgramDotColorMatchingForm::on_toolButtonSimShowSubtract_clicked()
{
	SimPanel.SetDrawSubtractMode(ui->toolButtonSimShowSubtract->isChecked());
	SimPanel.repaint();
}


void HistgramDotColorMatchingForm::on_checkBoxVariationMode_clicked()
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxVariationRL_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxVariationRH_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxVariationGL_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxVariationGL_2_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxVariationBL_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxVariationBH_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditVariationAdaptMinSize_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditPitBrightWidthRL_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditPitBrightWidthRH_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();	
}


void HistgramDotColorMatchingForm::on_EditPitBrightWidthGL_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditPitBrightWidthGH_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditPitBrightWidthBL_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditPitBrightWidthBH_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}

void HistgramDotColorMatchingForm::on_checkBoxPitMode_clicked()
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxVariationMultiplyMaster_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditAdjustContribute_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxVarietySigma_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_checkBoxVariationDifMaster_clicked()
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_checkBoxVariationAndLogic_clicked()
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_doubleSpinBoxVariationSubMasterVari_valueChanged(double arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_checkBoxLineMode_stateChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditLineOKMinLength_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditLineMaxWidth_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditLineMinDensityPercent_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


void HistgramDotColorMatchingForm::on_EditLineMinCluster_valueChanged(int arg1)
{
    if(OnChanging==true){
        return;
    }
	on_ButtonCalc_clicked();
}


//======================================================================================
GUICmdReqHSVPanelImage::GUICmdReqHSVPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName ,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ImageWidth	=0;
	ImageHeight	=0;
	HSVParamData.MovX		=0;
	HSVParamData.MovY		=0;
	HSVParamData.ZoomRate	=1.0;
}
bool	GUICmdReqHSVPanelImage::Load(QIODevice *f)
{
	if(::Load(f,ImageWidth)==false)
		return false;
	if(::Load(f,ImageHeight)==false)
		return false;
	if(f->read((char *)&HSVParamData,sizeof(HSVParamData))!=sizeof(HSVParamData))
		return false;
	return true;
}
bool	GUICmdReqHSVPanelImage::Save(QIODevice *f)
{
	if(::Save(f,ImageWidth)==false)
		return false;
	if(::Save(f,ImageHeight)==false)
		return false;
	if(f->write((const char *)&HSVParamData,sizeof(HSVParamData))!=sizeof(HSVParamData))
		return false;
	return true;
}

void	GUICmdReqHSVPanelImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckHSVPanelImage	*SendBack=GetSendBack(GUICmdAckHSVPanelImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	QImage	RetImage(ImageWidth,ImageHeight,QImage::Format_ARGB32);
	SendBack->AckImage=RetImage;
	SendBack->MakeImage(localPage,HSVParamData);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckHSVPanelImage::GUICmdAckHSVPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckHSVPanelImage::Load(QIODevice *f)
{
	if(::Load(f,AckImage)==false)
		return false;
	return true;
}
bool	GUICmdAckHSVPanelImage::Save(QIODevice *f)
{
	if(::Save(f,AckImage)==false)
		return false;
	return true;
}

void	GUICmdAckHSVPanelImage::MakeImage(int LocalPage,HSVPanelWidget::HSVParam &HSVParamData)
{
	int	W=AckImage.width();
	int	H=AckImage.height();

	double	Z=1.0/HSVParamData.ZoomRate;
	int	LayerNumb=GetLayersBase()->GetLayerNumb(LocalPage);
	DataInPage	*Pg=GetLayersBase()->GetPageData(LocalPage);
	if(LayerNumb>=3){
		if(HSVParamData.HsvFixedColorMode==false
		&& HSVParamData.TrialMode==false){
			//#pragma omp parallel
			{
			//	#pragma omp for
				for(int y=0;y<H;y++){
					BYTE	*d=AckImage.scanLine(y);
					int	Y=y*Z-HSVParamData.MovY;
					if(0<=Y && Y<Pg->GetMaxLines()){
						BYTE	*sR=Pg->GetLayerData(0)->GetMasterBuff().GetY(Y);
						BYTE	*sG=Pg->GetLayerData(1)->GetMasterBuff().GetY(Y);
						BYTE	*sB=Pg->GetLayerData(2)->GetMasterBuff().GetY(Y);
						double	fX=-HSVParamData.MovX;
						for(int x=0;x<W;x++){
							int	X=fX;
							if(0<=X && X<Pg->GetDotPerLine()){
								*((int32 *)d)=0xFF000000+((*(sR+X))<<16)+((*(sG+X))<<8)+((*(sB+X)));
							}
							else{
								*((int32 *)d)=0xFF000000;
							}
							fX+=Z;
							d+=4;
						}
					}
					else{
						for(int x=0;x<W;x++){
							*((int32 *)d)=0xFF000000;
							d+=4;
						}
					}
				}
			}
		}
		else if(HSVParamData.HsvFixedColorMode==false
		&& HSVParamData.TrialMode==true){
			//#pragma omp parallel
			{
			//	#pragma omp for
				for(int y=0;y<H;y++){
					BYTE	*d=AckImage.scanLine(y);
					int	Y=y*Z-HSVParamData.MovY;
					if(0<=Y && Y<Pg->GetMaxLines()){
						BYTE	*sR=Pg->GetLayerData(0)->GetMasterBuff().GetY(Y);
						BYTE	*sG=Pg->GetLayerData(1)->GetMasterBuff().GetY(Y);
						BYTE	*sB=Pg->GetLayerData(2)->GetMasterBuff().GetY(Y);
						double	fX=-HSVParamData.MovX;
						for(int x=0;x<W;x++){
							int	X=fX;
							if(0<=X && X<Pg->GetDotPerLine()){
								double	h,s ,v;
								::RGB2HSV(h,s ,v ,*(sR+X) ,*(sG+X) ,*(sB+X));

								int	th=(h*(HSVParamData.HsvPH+100)*0.01)+HSVParamData.HsvDH;
								int	ts=(s*(HSVParamData.HsvPS+100)*0.01)+HSVParamData.HsvDS;
								int	tv=(v*(HSVParamData.HsvPV+100)*0.01)+HSVParamData.HsvDV;
								while(th<0)
									th+=360;
								while(th>=360)
									th-=360;
								ts=Clipping(ts,0,255);
								tv=Clipping(tv,0,255);
								int	R ,G ,B;
								::HSV2RGB(th,ts,tv ,R ,G ,B);
								*((int32 *)d)=0xFF000000+(R<<16)+(G<<8)+(B);
							}
							else{
								*((int32 *)d)=0xFF000000;
							}
							fX+=Z;
							d+=4;
						}
					}
					else{
						for(int x=0;x<W;x++){
							*((int32 *)d)=0xFF000000;
							d+=4;
						}
					}
				}
			}
		}
		else if(HSVParamData.HsvFixedColorMode==true
		&& HSVParamData.TrialMode==false){
			int	R,G,B;
			HSV2RGB(HSVParamData.HsvH,HSVParamData.HsvS,HSVParamData.HsvV,R ,G ,B);
			//#pragma omp parallel
			{
			//	#pragma omp for
				for(int y=0;y<H;y++){
					BYTE	*d=AckImage.scanLine(y);
					int	Y=y*Z-HSVParamData.MovY;
					if(0<=Y && Y<Pg->GetMaxLines()){
						double	fX=-HSVParamData.MovX;
						for(int x=0;x<W;x++){
							int	X=fX;
							if(0<=X && X<Pg->GetDotPerLine()){
								
								*((int32 *)d)=0xFF000000+(R<<16)+(G<<8)+(B);
							}
							else{
								*((int32 *)d)=0xFF000000;
							}
							fX+=Z;
							d+=4;
						}
					}
					else{
						for(int x=0;x<W;x++){
							*((int32 *)d)=0xFF000000;
							d+=4;
						}
					}
				}
			}
		}
		else if(HSVParamData.HsvFixedColorMode==true
		&& HSVParamData.TrialMode==true){
			int	th=(HSVParamData.HsvH*(HSVParamData.HsvPH+100)*0.01)+HSVParamData.HsvDH;
			int	ts=(HSVParamData.HsvS*(HSVParamData.HsvPS+100)*0.01)+HSVParamData.HsvDS;
			int	tv=(HSVParamData.HsvV*(HSVParamData.HsvPV+100)*0.01)+HSVParamData.HsvDV;
			while(th<0)
				th+=360;
			while(th>=360)
				th-=360;
			ts=Clipping(ts,0,255);
			tv=Clipping(tv,0,255);
			int	R ,G ,B;
			::HSV2RGB(th,ts,tv ,R ,G ,B);
			//#pragma omp parallel
			{
			//	#pragma omp for
				for(int y=0;y<H;y++){
					BYTE	*d=AckImage.scanLine(y);
					int	Y=y*Z-HSVParamData.MovY;
					if(0<=Y && Y<Pg->GetMaxLines()){
						double	fX=-HSVParamData.MovX;
						for(int x=0;x<W;x++){
							int	X=fX;
							if(0<=X && X<Pg->GetDotPerLine()){
								*((int32 *)d)=0xFF000000+(R<<16)+(G<<8)+(B);
							}
							else{
								*((int32 *)d)=0xFF000000;
							}
							fX+=Z;
							d+=4;
						}
					}
					else{
						for(int x=0;x<W;x++){
							*((int32 *)d)=0xFF000000;
							d+=4;
						}
					}
				}
			}
		}
	}
}

//======================================================================================
GUICmdReqHSVValue::GUICmdReqHSVValue(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName ,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqHSVValue::Load(QIODevice *f)
{
	if(f->read((char *)&HSVIndexData,sizeof(HSVIndexData))!=sizeof(HSVIndexData))
		return false;
	return true;
}
bool	GUICmdReqHSVValue::Save(QIODevice *f)
{
	if(f->write((const char *)&HSVIndexData,sizeof(HSVIndexData))!=sizeof(HSVIndexData))
		return false;
	return true;
}

void	GUICmdReqHSVValue::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckHSVValue	*SendBack=GetSendBack(GUICmdAckHSVValue,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	int	Tr=0;
	int	Tg=0;
	int	Tb=0;
	int	Mr=0;
	int	Mg=0;
	int	Mb=0;
	int	LayerNumb=GetLayersBase()->GetLayerNumb(localPage);
	DataInPage	*Pg=GetLayersBase()->GetPageData(localPage);
	if(LayerNumb>=3){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeDotColorMatchingInspect);
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(HSVIndexData.Phase);
		AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
		DotColorMatchingItem	*Item=(DotColorMatchingItem *)Ap->SearchIDItem(HSVIndexData.ItemID);
		if(Item!=NULL){
			ResultInItemRoot	*R=Item->GetCurrentResult();
			int	Rx=0;
			int	Ry=0;
			if(R!=NULL){
				Rx=R->GetTotalShiftedX();
				Ry=R->GetTotalShiftedY();
			}
			ImageBuffer *TargetImages[3];
			Pg->GetTargetImages	(TargetImages,3);
			int	Tx=HSVIndexData.LocalX+Rx;
			int	Ty=HSVIndexData.LocalY+Ry;
			if(0<=Ty && Ty<TargetImages[0]->GetHeight()
			&& 0<=Tx && Tx<TargetImages[0]->GetWidth()){
				Tr=TargetImages[0]->GetY(HSVIndexData.LocalY+Ry)[HSVIndexData.LocalX+Rx];
				Tg=TargetImages[1]->GetY(HSVIndexData.LocalY+Ry)[HSVIndexData.LocalX+Rx];
				Tb=TargetImages[2]->GetY(HSVIndexData.LocalY+Ry)[HSVIndexData.LocalX+Rx];
				Mr=Tr;
				Mg=Tg;
				Mb=Tb;

				SendBack->HSVValueData.CurrentR=Tr;
				SendBack->HSVValueData.CurrentG=Tg;
				SendBack->HSVValueData.CurrentB=Tb;
				Item->GetDetectRedRange(Tr,Tg,Tb
										,SendBack->HSVValueData.RedRL,SendBack->HSVValueData.RedRH
										,SendBack->HSVValueData.RedGL,SendBack->HSVValueData.RedGH
										,SendBack->HSVValueData.RedBL,SendBack->HSVValueData.RedBH);

				int	Mx,My;
				Item->GetAlignmentShift(Mx,My);
				int	Wx=Tx-Mx;
				int	Wy=Ty-My;

				ImageBuffer *MasterImages[3];
				Pg->GetMasterImages	(MasterImages,3);
				if(0<=Wy && Wy<MasterImages[0]->GetHeight()
				&& 0<=Wx && Wx<MasterImages[0]->GetWidth()){
					Mr=MasterImages[0]->GetY(Wy)[Wx];
					Mg=MasterImages[1]->GetY(Wy)[Wx];
					Mb=MasterImages[2]->GetY(Wy)[Wx];
				}
			}
		}
		double	Th,Ts ,Tv;
		::RGB2HSV(Th,Ts ,Tv ,Tr ,Tg ,Tb);
		double	Mh,Ms ,Mv;
		::RGB2HSV(Mh,Ms ,Mv ,Mr ,Mg ,Mb);

		SendBack->HSVValueData.MasterH=Mh;
		SendBack->HSVValueData.MasterS=Ms;
		SendBack->HSVValueData.MasterV=Mv;
		SendBack->HSVValueData.TargetH=Th;
		SendBack->HSVValueData.TargetS=Ts;
		SendBack->HSVValueData.TargetV=Tv;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckHSVValue::GUICmdAckHSVValue(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckHSVValue::Load(QIODevice *f)
{
	if(f->read((char *)&HSVValueData,sizeof(HSVValueData))!=sizeof(HSVValueData))
		return false;
	return true;
}
bool	GUICmdAckHSVValue::Save(QIODevice *f)
{
	if(f->write((const char *)&HSVValueData,sizeof(HSVValueData))!=sizeof(HSVValueData))
		return false;
	return true;
}


void HistgramDotColorMatchingForm::on_toolButtonBroad_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}


void HistgramDotColorMatchingForm::on_toolButtonNarrow_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

