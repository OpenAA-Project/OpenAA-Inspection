#include "PixelInspectionResource.h"
#include "PixelHistogramForm.h"
#include "XPixelInspection.h"
#include "XDataInLayerCommander.h"
#include "GLWidget.h"
#include "XImageProcess.h"

extern	const	char	*sPixelInspectionRoot;
extern	const	char	*sPixelInspectionName;

//#define Debug

inline	BYTE	Clip255(int i)
{
	if(i>255)
		return 255;
	if(i<0)
		return 0;
	return (BYTE)i;
}

PixelHistogramForm::PixelHistogramForm(LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	//OpenGL?p
    glWidget = new GLWidget;
	ui.dwGLWidget->setWidget(glWidget);

    createSlider(ui.vsX);
    createSlider(ui.vsY);
    createSlider(ui.vsZ);

	ui.lbPlusPixelInfo	->setVisible(false);
	ui.lbPlusPixelInfo_2->setVisible(false);

	IData			=NULL;
	PoleTable		=NULL;
	localX			=0;
	localY			=0;
	MasterX			=0;
	MasterY			=0;
	ThresholdRange	=0;

	MasterBrightness[0]		=MasterBrightness[1]	=MasterBrightness[2]	=0;
	MasterBrightness2[0]	=MasterBrightness2[1]	=MasterBrightness2[2]	=0;
	AverageBrightness[0]	=AverageBrightness[1]	=AverageBrightness[2]	=0;
	AverageBrightness2[0]	=AverageBrightness2[1]	=AverageBrightness2[2]	=0;
	LightBrightness[0]		=LightBrightness[1]		=LightBrightness[2]		=0;
	LightBrightness2[0]		=LightBrightness2[1]	=LightBrightness2[2]	=0;
	DarkBrightness[0]		=DarkBrightness[1]		=DarkBrightness[2]		=0;
	DarkBrightness2[0]		=DarkBrightness2[1]		=DarkBrightness2[2]		=0;
	TargetBrightness[0]		=TargetBrightness[1]	=TargetBrightness[2]	=0;
	PL	=PH	=SL	=SH	=RL	=RH	=0;
	PLr	=PHr=SLr=SHr=RLr=RHr=0;
	InspectionLevel			=0;
	SearchAreaForMakeTable	=0;
	SearchDotBase			=0;
	PL1	=PH1=SL1=SH1=RL1=RH1=0;
	PLr1=PHr1=SLr1=SHr1=RLr1=RHr1=0;
	InsTargetBrightness[0]	=InsTargetBrightness[1]	=InsTargetBrightness[2]	=0;
	InsAverageCoordX		=0;
	InsAverageCoordY		=0;
	InsTargetCoordX			=0;
	InsTargetCoordY			=0;
	InsTargetBrightness2[0]	=InsTargetBrightness2[1]=InsTargetBrightness2[2]=0;
	InsAverageCoordX2		=0;
	InsAverageCoordY2		=0;
	InsTargetCoordX2		=0;
	InsTargetCoordY2		=0;
	InspectResult			=0;
//	NGBitmap				=NULL;
	ThresholdDifference		=0;
	XLen=YLen				=0;
	pAlignPage				=NULL;
	pHoleAlignPage			=NULL;
	PixData					=NULL;

	connect(ui.sbRed		,SIGNAL(valueChanged(int)),this,SLOT(sbRedValueChanged(int)));
	connect(ui.sbGreen		,SIGNAL(valueChanged(int)),this,SLOT(sbGreenValueChanged(int)));
	connect(ui.sbBlue		,SIGNAL(valueChanged(int)),this,SLOT(sbBlueValueChanged(int)));
	connect(ui.sbRed_2		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_2ValueChanged(int)));
	connect(ui.sbGreen_2	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_2ValueChanged(int)));
	connect(ui.sbBlue_2		,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_2ValueChanged(int)));
	connect(ui.sbRed_3		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_3ValueChanged(int)));
	connect(ui.sbGreen_3	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_3ValueChanged(int)));
	connect(ui.sbBlue_3		,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_3ValueChanged(int)));
	connect(ui.sbRed_4		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_4ValueChanged(int)));
	connect(ui.sbGreen_4	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_4ValueChanged(int)));
	connect(ui.sbBlue_4		,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_4ValueChanged(int)));
	connect(ui.sbRed_5		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_5ValueChanged(int)));
	connect(ui.sbGreen_5	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_5ValueChanged(int)));
	connect(ui.sbBlue_5		,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_5ValueChanged(int)));
	connect(ui.sbRed_6		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_6ValueChanged(int)));
	connect(ui.sbGreen_6	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_6ValueChanged(int)));
	connect(ui.sbBlue_6		,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_6ValueChanged(int)));
	connect(ui.sbRed_7		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_7ValueChanged(int)));
	connect(ui.sbGreen_7	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_7ValueChanged(int)));
	connect(ui.sbBlue_7		,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_7ValueChanged(int)));
	connect(ui.sbRed_8		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_8ValueChanged(int)));
	connect(ui.sbGreen_8	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_8ValueChanged(int)));
	connect(ui.sbBlue_8		,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_8ValueChanged(int)));
	connect(ui.sbRed_9		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_9ValueChanged(int)));
	connect(ui.sbGreen_9	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_9ValueChanged(int)));
	connect(ui.sbBlue_9		,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_9ValueChanged(int)));
	connect(ui.sbRed_10		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_10ValueChanged(int)));
	connect(ui.sbGreen_10	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_10ValueChanged(int)));
	connect(ui.sbBlue_10	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_10ValueChanged(int)));
	connect(ui.sbRed_11		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_11ValueChanged(int)));
	connect(ui.sbGreen_11	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_11ValueChanged(int)));
	connect(ui.sbBlue_11	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_11ValueChanged(int)));
	connect(ui.sbRed_12		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_12ValueChanged(int)));
	connect(ui.sbGreen_12	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_12ValueChanged(int)));
	connect(ui.sbBlue_12	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_12ValueChanged(int)));

	connect(ui.hsInspectLevel			,SIGNAL(valueChanged(int))	,this,SLOT(hsInspectLevelValueChanged(int)));
	connect(ui.sbInspectLevel			,SIGNAL(valueChanged(int))	,this,SLOT(sbInspectLevelValueChanged(int)));
	connect(ui.sbSearchAreaForMakeTable	,SIGNAL(valueChanged(int))	,this,SLOT(sbSearchAreaForMakeTableValueChanged(int)));
	connect(ui.sbSearchDotBase			,SIGNAL(valueChanged(int))	,this,SLOT(sbSearchDotBaseValueChanged(int)));
	connect(ui.pbCalc					,SIGNAL(clicked())			,this,SLOT(pbCalcClicked()));
	connect(ui.pbClose					,SIGNAL(clicked())			,this,SLOT(pbCloseClicked()));

    connect(ui.vsX	,SIGNAL(valueChanged(int))		,glWidget	,SLOT(setXRotation(int)));
    connect(glWidget,SIGNAL(xRotationChanged(int))	,ui.vsX		,SLOT(setValue(int)));
    connect(ui.vsY	,SIGNAL(valueChanged(int))		,glWidget	,SLOT(setYRotation(int)));
    connect(glWidget,SIGNAL(yRotationChanged(int))	,ui.vsY		,SLOT(setValue(int)));
    connect(ui.vsZ	,SIGNAL(valueChanged(int))		,glWidget	,SLOT(setZRotation(int)));
    connect(glWidget,SIGNAL(zRotationChanged(int))	,ui.vsZ		,SLOT(setValue(int)));

	sbRed[0]	=ui.sbRed;
	sbRed[1]	=ui.sbRed_2;
	sbRed[2]	=ui.sbRed_3;
	sbRed[3]	=ui.sbRed_4;
	sbRed[4]	=ui.sbRed_5;
	sbRed[5]	=ui.sbRed_6;
	sbRed[6]	=ui.sbRed_7;
	sbRed[7]	=ui.sbRed_8;
	sbRed[8]	=ui.sbRed_9;
	sbRed[9]	=ui.sbRed_10;
	sbRed[10]	=ui.sbRed_11;
	sbRed[11]	=ui.sbRed_12;
	sbGreen[0]	=ui.sbGreen;
	sbGreen[1]	=ui.sbGreen_2;
	sbGreen[2]	=ui.sbGreen_3;
	sbGreen[3]	=ui.sbGreen_4;
	sbGreen[4]	=ui.sbGreen_5;
	sbGreen[5]	=ui.sbGreen_6;
	sbGreen[6]	=ui.sbGreen_7;
	sbGreen[7]	=ui.sbGreen_8;
	sbGreen[8]	=ui.sbGreen_9;
	sbGreen[9]	=ui.sbGreen_10;
	sbGreen[10]	=ui.sbGreen_11;
	sbGreen[11]	=ui.sbGreen_12;
	sbBlue[0]	=ui.sbBlue;
	sbBlue[1]	=ui.sbBlue_2;
	sbBlue[2]	=ui.sbBlue_3;
	sbBlue[3]	=ui.sbBlue_4;
	sbBlue[4]	=ui.sbBlue_5;
	sbBlue[5]	=ui.sbBlue_6;
	sbBlue[6]	=ui.sbBlue_7;
	sbBlue[7]	=ui.sbBlue_8;
	sbBlue[8]	=ui.sbBlue_9;
	sbBlue[9]	=ui.sbBlue_10;
	sbBlue[10]	=ui.sbBlue_11;
	sbBlue[11]	=ui.sbBlue_12;
	leP[0]		=ui.leP;
	leP[1]		=ui.leP_2;
	leP[2]		=ui.leP_3;
	leP[3]		=ui.leP_4;
	leP[4]		=ui.leP_5;
	leP[5]		=ui.leP_6;
	leP[6]		=ui.leP_7;
	leP[7]		=ui.leP_8;
	leP[8]		=ui.leP_9;
	leP[9]		=ui.leP_10;
	leP[10]		=ui.leP_11;
	leP[11]		=ui.leP_12;
	leS[0]		=ui.leS;
	leS[1]		=ui.leS_2;
	leS[2]		=ui.leS_3;
	leS[3]		=ui.leS_4;
	leS[4]		=ui.leS_5;
	leS[5]		=ui.leS_6;
	leS[6]		=ui.leS_7;
	leS[7]		=ui.leS_8;
	leS[8]		=ui.leS_9;
	leS[9]		=ui.leS_10;
	leS[10]		=ui.leS_11;
	leS[11]		=ui.leS_12;
	leR[0]		=ui.leR;
	leR[1]		=ui.leR_2;
	leR[2]		=ui.leR_3;
	leR[3]		=ui.leR_4;
	leR[4]		=ui.leR_5;
	leR[5]		=ui.leR_6;
	leR[6]		=ui.leR_7;
	leR[7]		=ui.leR_8;
	leR[8]		=ui.leR_9;
	leR[9]		=ui.leR_10;
	leR[10]		=ui.leR_11;
	leR[11]		=ui.leR_12;
	fmColor[0]	=ui.fmColor;
	fmColor[1]	=ui.fmColor_2;
	fmColor[2]	=ui.fmColor_3;
	fmColor[3]	=ui.fmColor_4;
	fmColor[4]	=ui.fmColor_5;
	fmColor[5]	=ui.lbAroundIns;
	fmColor[6]	=ui.lbAroundIns_2;
	fmColor[7]	=ui.fmColor_6;
	fmColor[8]	=ui.fmColor_7;
	fmColor[9]	=ui.fmColor_8;
	fmColor[10]	=ui.fmColor_9;
	fmColor[11]	=ui.fmColor_10;
}

PixelHistogramForm::~PixelHistogramForm()
{
	delete glWidget;

	if(IData!=NULL){
		for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
			AlgorithmItemRoot	*DA=D->Data;
			if(DA==NULL){
				continue;
			}
			PixelInspectionItem	*PData=dynamic_cast<PixelInspectionItem *>(DA);
			if(PData!=NULL){
				delete PData;
			}
		}
		delete	IData;
	}
}

void PixelHistogramForm::sbRedValueChanged(int value)
{
	Update(0);
}

void PixelHistogramForm::sbGreenValueChanged(int value)
{
	Update(0);
}

void PixelHistogramForm::sbBlueValueChanged(int value)
{
	Update(0);
}

void PixelHistogramForm::sbRed_2ValueChanged(int value)
{
	Update(1);
}

void PixelHistogramForm::sbGreen_2ValueChanged(int value)
{
	Update(1);
}

void PixelHistogramForm::sbBlue_2ValueChanged(int value)
{
	Update(1);
}

void PixelHistogramForm::sbRed_3ValueChanged(int value)
{
	Update(2);
}

void PixelHistogramForm::sbGreen_3ValueChanged(int value)
{
	Update(2);
}

void PixelHistogramForm::sbBlue_3ValueChanged(int value)
{
	Update(2);
}

void PixelHistogramForm::sbRed_4ValueChanged(int value)
{
	Update(3);
}

void PixelHistogramForm::sbGreen_4ValueChanged(int value)
{
	Update(3);
}

void PixelHistogramForm::sbBlue_4ValueChanged(int value)
{
	Update(3);
}

void PixelHistogramForm::sbRed_5ValueChanged(int value)
{
	Update(4);
}

void PixelHistogramForm::sbGreen_5ValueChanged(int value)
{
	Update(4);
}

void PixelHistogramForm::sbBlue_5ValueChanged(int value)
{
	Update(4);
}

void PixelHistogramForm::sbRed_6ValueChanged(int value)
{
	Update(5);
}

void PixelHistogramForm::sbGreen_6ValueChanged(int value)
{
	Update(5);
}

void PixelHistogramForm::sbBlue_6ValueChanged(int value)
{
	Update(5);
}

void PixelHistogramForm::sbRed_7ValueChanged(int value)
{
	Update(6);
}

void PixelHistogramForm::sbGreen_7ValueChanged(int value)
{
	Update(6);
}

void PixelHistogramForm::sbBlue_7ValueChanged(int value)
{
	Update(6);
}

void PixelHistogramForm::sbRed_8ValueChanged(int value)
{
	Update(7);
}

void PixelHistogramForm::sbGreen_8ValueChanged(int value)
{
	Update(7);
}

void PixelHistogramForm::sbBlue_8ValueChanged(int value)
{
	Update(7);
}

void PixelHistogramForm::sbRed_9ValueChanged(int value)
{
	Update(8);
}

void PixelHistogramForm::sbGreen_9ValueChanged(int value)
{
	Update(8);
}

void PixelHistogramForm::sbBlue_9ValueChanged(int value)
{
	Update(8);
}

void PixelHistogramForm::sbRed_10ValueChanged(int value)
{
	Update(9);
}

void PixelHistogramForm::sbGreen_10ValueChanged(int value)
{
	Update(9);
}

void PixelHistogramForm::sbBlue_10ValueChanged(int value)
{
	Update(9);
}

void PixelHistogramForm::sbRed_11ValueChanged(int value)
{
	Update(10);
}

void PixelHistogramForm::sbGreen_11ValueChanged(int value)
{
	Update(10);
}

void PixelHistogramForm::sbBlue_11ValueChanged(int value)
{
	Update(10);
}

void PixelHistogramForm::sbRed_12ValueChanged(int value)
{
	Update(11);
}

void PixelHistogramForm::sbGreen_12ValueChanged(int value)
{
	Update(11);
}

void PixelHistogramForm::sbBlue_12ValueChanged(int value)
{
	Update(11);
}

void PixelHistogramForm::hsInspectLevelValueChanged(int value)
{
	ui.sbInspectLevel->setValue(value);
}

void PixelHistogramForm::sbInspectLevelValueChanged(int value)
{
	InspectionLevel=value;
	ui.hsInspectLevel	->setValue(InspectionLevel);

	int ValuePlusMinus	=256-InspectionLevel;
	ui.lbPlus			->setText(QString::number(ValuePlusMinus));

	int ValuePLMinus	=PL-ValuePlusMinus;
	int ValuePHPlus		=PH+ValuePlusMinus;
	ui.lbPLMinus		->setText(QString::number(Clip255(ValuePLMinus)));
	ui.lbPHPlus			->setText(QString::number(Clip255(ValuePHPlus)));
	int ValueSLMinus	=SL-ValuePlusMinus;
	int ValueSHPlus		=SH+ValuePlusMinus;
	ui.lbSLMinus		->setText(QString::number(Clip255(ValueSLMinus)));
	ui.lbSHPlus			->setText(QString::number(Clip255(ValueSHPlus)));
	int ValueRLMinus	=RL-ValuePlusMinus;
	int ValueRHPlus		=RH+ValuePlusMinus;
	ui.lbRLMinus		->setText(QString::number(Clip255(ValueRLMinus)));
	ui.lbRHPlus			->setText(QString::number(Clip255(ValueRHPlus)));

//	//OpenGL?`?a?w?|
//	UpdateDraw();
}

void PixelHistogramForm::sbSearchAreaForMakeTableValueChanged(int value)
{
	SearchAreaForMakeTable=value;
}

void PixelHistogramForm::sbSearchDotBaseValueChanged(int value)
{
	SearchDotBase=value;
}

void PixelHistogramForm::pbCalcClicked()
{
	//?Y?e?3?e??e??l?A?A?v?Z
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL){
			continue;
		}
		PixelInspectionItem	*PData=dynamic_cast<PixelInspectionItem *>(DA);
		if(PData==NULL){
			continue;
		}
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sPixelInspectionRoot,sPixelInspectionName,PixelReqTryThresholdCommand ,PixelSendTryThresholdCommand);
		((PixelTryThresholdReq *)PacketReq.Data)->GlobalPage			=D->GlobalPage;
		((PixelTryThresholdReq *)PacketReq.Data)->PixelItemID			=DA->GetID();
		((PixelTryThresholdReq *)PacketReq.Data)->SearchAreaForMakeTable=SearchAreaForMakeTable;
		((PixelTryThresholdReq *)PacketReq.Data)->SearchDotBase			=SearchDotBase;
		((PixelTryThresholdReq *)PacketReq.Data)->PoleTable				=PoleTable;
		((PixelTryThresholdReq *)PacketReq.Data)->InspectionLevel		=InspectionLevel;
		((PixelTryThresholdReq *)PacketReq.Data)->localX				=localX;
		((PixelTryThresholdReq *)PacketReq.Data)->localY				=localY;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		PixelTryThresholdSend	*ThrePoint=(PixelTryThresholdSend *)PacketSend.GetData();

		PL							=ThrePoint->PL[0];
		PH							=ThrePoint->PH[0];
		SL							=ThrePoint->SL[0];
		SH							=ThrePoint->SH[0];
		RL							=ThrePoint->RL[0];
		RH							=ThrePoint->RH[0];
		PL1							=ThrePoint->PL1;
		PH1							=ThrePoint->PH1;
		SL1							=ThrePoint->SL1;
		SH1							=ThrePoint->SH1;
		RL1							=ThrePoint->RL1;
		RH1							=ThrePoint->RH1;
		memcpy(InsTargetBrightness	,ThrePoint->InsTargetBrightness	,sizeof(InsTargetBrightness)/sizeof(InsTargetBrightness[0]));
		InsAverageCoordX			=ThrePoint->InsAverageCoordX;
		InsAverageCoordY			=ThrePoint->InsAverageCoordY;
		InsTargetCoordX				=ThrePoint->InsTargetCoordX;
		InsTargetCoordY				=ThrePoint->InsTargetCoordY;
		InspectResult				=ThrePoint->InspectResult;

		break;
	}	
	ShowThreshold();
}

void PixelHistogramForm::pbCloseClicked()
{
	close();
}

void	PixelHistogramForm::Update(int Index)
{
	int Red		=sbRed[Index]	->value();
	int Green	=sbGreen[Index]	->value();
	int Blue	=sbBlue[Index]	->value();
	struct	PixelPoleMatrixStruct	*PT=&PoleTable[(Red<<16)+(Green<<8)+Blue];
	leP[Index]->setText(QString::number(PT->P));
	leS[Index]->setText(QString::number(PT->S));
	leR[Index]->setText(QString::number(PT->R));

	//?F?I?Y?e
	QPalette P;
	P.setColor(QPalette::Background,QColor(Red,Green,Blue));

	if(Index==4){
		QPalette P1;
		if(qGray(Red,Green,Blue)<50){
			P1.setColor(QPalette::WindowText,QColor(255,255,255));
			ui.lbInsTitle	->setPalette(P1);
			ui.lbInsRed		->setPalette(P1);
			ui.lbInsGreen	->setPalette(P1);
			ui.lbInsBlue	->setPalette(P1);
			ui.lbInsP		->setPalette(P1);
			ui.lbInsS		->setPalette(P1);
			ui.lbInsR		->setPalette(P1);
		}
		else{
			P1.setColor(QPalette::WindowText,QColor(0,0,0));
			ui.lbInsTitle	->setPalette(P1);
			ui.lbInsRed		->setPalette(P1);
			ui.lbInsGreen	->setPalette(P1);
			ui.lbInsBlue	->setPalette(P1);
			ui.lbInsP		->setPalette(P1);
			ui.lbInsS		->setPalette(P1);
			ui.lbInsR		->setPalette(P1);
		}
	}
	else if(Index==5){
		QPalette P1;
		if(qGray(Red,Green,Blue)<50){
			P1.setColor(QPalette::WindowText,QColor(255,255,255));
			ui.lbAroundInsTitle	->setPalette(P1);
			ui.lbAroundInsRed	->setPalette(P1);
			ui.lbAroundInsGreen	->setPalette(P1);
			ui.lbAroundInsBlue	->setPalette(P1);
			ui.lbAroundInsP		->setPalette(P1);
			ui.lbAroundInsS		->setPalette(P1);
			ui.lbAroundInsR		->setPalette(P1);
			ui.lbInsX			->setPalette(P1);
			ui.lbInsY			->setPalette(P1);
			ui.lbPixelInfo_2	->setPalette(P1);
			ui.lbPlusPixelInfo_2->setPalette(P1);
		}
		else{
			P1.setColor(QPalette::WindowText,QColor(0,0,0));
			ui.lbAroundInsTitle	->setPalette(P1);
			ui.lbAroundInsRed	->setPalette(P1);
			ui.lbAroundInsGreen	->setPalette(P1);
			ui.lbAroundInsBlue	->setPalette(P1);
			ui.lbAroundInsP		->setPalette(P1);
			ui.lbAroundInsS		->setPalette(P1);
			ui.lbAroundInsR		->setPalette(P1);
			ui.lbInsX			->setPalette(P1);
			ui.lbInsY			->setPalette(P1);
			ui.lbPixelInfo_2	->setPalette(P1);
			ui.lbPlusPixelInfo_2->setPalette(P1);
		}
		//?F?I?Y?e
		lbAroundInsPalette.setColor(QPalette::Background,QColor(Red,Green,Blue));
		return;
	}
	else if(Index==6){
		QPalette P1;
		if(qGray(Red,Green,Blue)<50){
			P1.setColor(QPalette::WindowText,QColor(255,255,255));
			ui.lbAroundInsTitle_2	->setPalette(P1);
			ui.lbAroundInsRed_2		->setPalette(P1);
			ui.lbAroundInsGreen_2	->setPalette(P1);
			ui.lbAroundInsBlue_2	->setPalette(P1);
			ui.lbAroundInsP_2		->setPalette(P1);
			ui.lbAroundInsS_2		->setPalette(P1);
			ui.lbAroundInsR_2		->setPalette(P1);
			ui.lbInsX_2				->setPalette(P1);
			ui.lbInsY_2				->setPalette(P1);
			ui.lbPixelInfo_4		->setPalette(P1);
			ui.lbPlusPixelInfo_4	->setPalette(P1);
		}
		else{
			P1.setColor(QPalette::WindowText,QColor(0,0,0));
			ui.lbAroundInsTitle_2	->setPalette(P1);
			ui.lbAroundInsRed_2		->setPalette(P1);
			ui.lbAroundInsGreen_2	->setPalette(P1);
			ui.lbAroundInsBlue_2	->setPalette(P1);
			ui.lbAroundInsP_2		->setPalette(P1);
			ui.lbAroundInsS_2		->setPalette(P1);
			ui.lbAroundInsR_2		->setPalette(P1);
			ui.lbInsX_2				->setPalette(P1);
			ui.lbInsY_2				->setPalette(P1);
			ui.lbPixelInfo_4		->setPalette(P1);
			ui.lbPlusPixelInfo_4	->setPalette(P1);
		}
		//?F?I?Y?e
		lbAroundInsPalette.setColor(QPalette::Background,QColor(Red,Green,Blue));
		return;
	}
	else if(Index==11){
		QPalette P1;
		if(qGray(Red,Green,Blue)<50){
			P1.setColor(QPalette::WindowText,QColor(255,255,255));
			ui.lbInsTitle_2	->setPalette(P1);
			ui.lbInsRed_2	->setPalette(P1);
			ui.lbInsGreen_2	->setPalette(P1);
			ui.lbInsBlue_2	->setPalette(P1);
			ui.lbInsP_2		->setPalette(P1);
			ui.lbInsS_2		->setPalette(P1);
			ui.lbInsR_2		->setPalette(P1);
		}
		else{
			P1.setColor(QPalette::WindowText,QColor(0,0,0));
			ui.lbInsTitle_2	->setPalette(P1);
			ui.lbInsRed_2	->setPalette(P1);
			ui.lbInsGreen_2	->setPalette(P1);
			ui.lbInsBlue_2	->setPalette(P1);
			ui.lbInsP_2		->setPalette(P1);
			ui.lbInsS_2		->setPalette(P1);
			ui.lbInsR_2		->setPalette(P1);
		}
	}
	fmColor[Index]->setPalette(P);
}

void	PixelHistogramForm::Update(int Index,BYTE Brightness[])
{
	if(Index==0){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRedValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreenValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlueValueChanged(int)));
	}
	else if(Index==1){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_2ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_2ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_2ValueChanged(int)));
	}
	else if(Index==2){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_3ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_3ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_3ValueChanged(int)));
	}
	else if(Index==3){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_4ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_4ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_4ValueChanged(int)));
	}
	else if(Index==4){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_5ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_5ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_5ValueChanged(int)));
	}
	else if(Index==5){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_6ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_6ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_6ValueChanged(int)));
	}
	else if(Index==6){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_7ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_7ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_7ValueChanged(int)));
	}
	else if(Index==7){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_8ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_8ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_8ValueChanged(int)));
	}
	else if(Index==8){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_9ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_9ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_9ValueChanged(int)));
	}
	else if(Index==9){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_10ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_10ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_10ValueChanged(int)));
	}
	else if(Index==10){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_11ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_11ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_11ValueChanged(int)));
	}
	else if(Index==11){
		disconnect(sbRed[Index]		,SIGNAL(valueChanged(int)),this,SLOT(sbRed_12ValueChanged(int)));
		disconnect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_12ValueChanged(int)));
		disconnect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_12ValueChanged(int)));
	}

	sbRed[Index]	->setValue(Brightness[0]);
	sbGreen[Index]	->setValue(Brightness[1]);
	sbBlue[Index]	->setValue(Brightness[2]);
	Update(Index);

	if(Index==0){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRedValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreenValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlueValueChanged(int)));
	}
	else if(Index==1){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_2ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_2ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_2ValueChanged(int)));
	}
	else if(Index==2){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_3ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_3ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_3ValueChanged(int)));
	}
	else if(Index==3){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_4ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_4ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_4ValueChanged(int)));
	}
	else if(Index==4){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_5ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_5ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_5ValueChanged(int)));
	}
	else if(Index==5){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_6ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_6ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_6ValueChanged(int)));
	}
	else if(Index==6){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_7ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_7ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_7ValueChanged(int)));
	}
	else if(Index==7){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_8ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_8ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_8ValueChanged(int)));
	}
	else if(Index==8){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_9ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_9ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_9ValueChanged(int)));
	}
	else if(Index==9){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_10ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_10ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_10ValueChanged(int)));
	}
	else if(Index==10){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_11ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_11ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_11ValueChanged(int)));
	}
	else if(Index==11){
		connect(sbRed[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbRed_12ValueChanged(int)));
		connect(sbGreen[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbGreen_12ValueChanged(int)));
		connect(sbBlue[Index]	,SIGNAL(valueChanged(int)),this,SLOT(sbBlue_12ValueChanged(int)));
	}
}

void	PixelHistogramForm::UpdateDraw()
{
	//glWidget?E?l?d?n?・
//	glWidget->SetRedValue	(TargetBrightness[0]);
//	glWidget->SetGreenValue	(TargetBrightness[1]);
//	glWidget->SetBlueValue	(TargetBrightness[2]);
	glWidget->SetPValue		(leP[4]->text().toInt());	//leP[11]
	glWidget->SetSValue		(leS[4]->text().toInt());	//leS[11]
	glWidget->SetRValue		(leR[4]->text().toInt());	//leR[11]
//	glWidget->SetPLValue	(Clip255(PL-(256-InspectionLevel)));
//	glWidget->SetPHValue	(Clip255(PH+(256-InspectionLevel)));
//	glWidget->SetSLValue	(Clip255(SL-(256-InspectionLevel)));
//	glWidget->SetSHValue	(Clip255(SH+(256-InspectionLevel)));
//	glWidget->SetRLValue	(Clip255(RL-(256-InspectionLevel)));
//	glWidget->SetRHValue	(Clip255(RH+(256-InspectionLevel)));
	glWidget->SetPLValue	(Clip255(PL-ThresholdRange));
	glWidget->SetPHValue	(Clip255(PH+ThresholdRange));
	glWidget->SetSLValue	(Clip255(SL-ThresholdRange));
	glWidget->SetSHValue	(Clip255(SH+ThresholdRange));
	glWidget->SetRLValue	(Clip255(RL-ThresholdRange));
	glWidget->SetRHValue	(Clip255(RH+ThresholdRange));
	glWidget->UpdateObject	();
    glWidget->updateGL		();
/*
	//???W?X?g
	glWidget->SetPValue		(leP[4]->text().toInt());	//leP[11]
	glWidget->SetSValue		(leS[4]->text().toInt());	//leS[11]
	glWidget->SetRValue		(leR[4]->text().toInt());	//leR[11]
	glWidget->SetPLValue	(Clip255(PL-(256-InspectionLevel)));
	glWidget->SetPHValue	(Clip255(PH+(256-InspectionLevel)));
	glWidget->SetSLValue	(Clip255(SL-(256-InspectionLevel)));
	glWidget->SetSHValue	(Clip255(SH+(256-InspectionLevel)));
	glWidget->SetRLValue	(Clip255(RL-(256-InspectionLevel)));
	glWidget->SetRHValue	(Clip255(RH+(256-InspectionLevel)));
	glWidget->UpdateObject	();
    glWidget->updateGL		();
*/
}

void	PixelHistogramForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
//	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
//	LibIDList.RemoveAll();
//	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL){
		delete	IData;
	}
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	CreateThreshold();
}

void	PixelHistogramForm::CreateThreshold(void)
{
#ifdef Debug
	PixelThresholdSend	*ThrePoint;
#endif

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL){
			continue;
		}
		PixelInspectionItem	*PData=dynamic_cast<PixelInspectionItem *>(DA);
		if(PData==NULL){
			continue;
		}
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sPixelInspectionRoot,sPixelInspectionName,PixelReqThresholdReqCommand ,PixelReqThresholdSendCommand);
		((PixelThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((PixelThresholdReq *)PacketReq.Data)->PixelItemID	=DA->GetID();
//		((PixelThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

#ifdef Debug
		ThrePoint=(PixelThresholdSend *)PacketSend.GetData();
#else
		PixelThresholdSend	*ThrePoint=(PixelThresholdSend *)PacketSend.GetData();
#endif

		PoleTable		=ThrePoint->PoleTable;
		localX			=ThrePoint->localX;
		localY			=ThrePoint->localY;
		MasterX			=ThrePoint->MasterX;
		MasterY			=ThrePoint->MasterY;
		ThresholdRange	=ThrePoint->ThresholdRange;

		memcpy(MasterBrightness		,ThrePoint->MasterBrightness	,sizeof(MasterBrightness)/sizeof(MasterBrightness[0]));
		memcpy(MasterBrightness2	,ThrePoint->MasterBrightness2	,sizeof(MasterBrightness2)/sizeof(MasterBrightness2[0]));
//		memcpy(AverageBrightness	,ThrePoint->AverageBrightness	,sizeof(AverageBrightness)/sizeof(AverageBrightness[0]));
		if(ThrePoint->AverageBrightness[0]!=NULL){
			AverageBrightness[0]		=ThrePoint->AverageBrightness[0][0];
			AverageBrightness[1]		=ThrePoint->AverageBrightness[1][0];
			AverageBrightness[2]		=ThrePoint->AverageBrightness[2][0];
		}
		if(ThrePoint->AverageBrightness2[0]!=NULL){
			AverageBrightness2[0]		=ThrePoint->AverageBrightness2[0][0];
			AverageBrightness2[1]		=ThrePoint->AverageBrightness2[1][0];
			AverageBrightness2[2]		=ThrePoint->AverageBrightness2[2][0];
		}
		memcpy(LightBrightness		,ThrePoint->LightBrightness		,sizeof(LightBrightness)/sizeof(LightBrightness[0]));
		memcpy(LightBrightness2		,ThrePoint->LightBrightness2	,sizeof(LightBrightness2)/sizeof(LightBrightness2[0]));
		memcpy(DarkBrightness		,ThrePoint->DarkBrightness		,sizeof(DarkBrightness)/sizeof(DarkBrightness[0]));
		memcpy(DarkBrightness2		,ThrePoint->DarkBrightness2		,sizeof(DarkBrightness2)/sizeof(DarkBrightness2[0]));
//		memcpy(TargetBrightness		,ThrePoint->TargetBrightness	,sizeof(TargetBrightness)/sizeof(TargetBrightness[0]));
		TargetBrightness[0]			=*(ThrePoint->TargetImageList[0]->GetY(localY)+localX);
		TargetBrightness[1]			=*(ThrePoint->TargetImageList[1]->GetY(localY)+localX);
		TargetBrightness[2]			=*(ThrePoint->TargetImageList[2]->GetY(localY)+localX);;
//		DisorderValue				=ThrePoint->DisorderValue;
		PL							=ThrePoint->PL;
		PH							=ThrePoint->PH;
		SL							=ThrePoint->SL;
		SH							=ThrePoint->SH;
		RL							=ThrePoint->RL;
		RH							=ThrePoint->RH;
		PLr							=ThrePoint->PLr;
		PHr							=ThrePoint->PHr;
		SLr							=ThrePoint->SLr;
		SHr							=ThrePoint->SHr;
		RLr							=ThrePoint->RLr;
		RHr							=ThrePoint->RHr;
		InspectionLevel				=ThrePoint->InspectionLevel;
		SearchAreaForMakeTable		=ThrePoint->SearchAreaForMakeTable;
		SearchDotBase				=ThrePoint->SearchDotBase;
		PL1							=ThrePoint->PL1;
		PH1							=ThrePoint->PH1;
		SL1							=ThrePoint->SL1;
		SH1							=ThrePoint->SH1;
		RL1							=ThrePoint->RL1;
		RH1							=ThrePoint->RH1;
		PLr1						=ThrePoint->PLr1;
		PHr1						=ThrePoint->PHr1;
		SLr1						=ThrePoint->SLr1;
		SHr1						=ThrePoint->SHr1;
		RLr1						=ThrePoint->RLr1;
		RHr1						=ThrePoint->RHr1;
		memcpy(InsTargetBrightness	,ThrePoint->InsTargetBrightness	,sizeof(InsTargetBrightness)/sizeof(InsTargetBrightness[0]));
		InsAverageCoordX			=ThrePoint->InsAverageCoordX;
		InsAverageCoordY			=ThrePoint->InsAverageCoordY;
		InsTargetCoordX				=ThrePoint->InsTargetCoordX;
		InsTargetCoordY				=ThrePoint->InsTargetCoordY;
		memcpy(InsTargetBrightness2	,ThrePoint->InsTargetBrightness2,sizeof(InsTargetBrightness2)/sizeof(InsTargetBrightness2[0]));
		InsAverageCoordX2			=ThrePoint->InsAverageCoordX2;
		InsAverageCoordY2			=ThrePoint->InsAverageCoordY2;
		InsTargetCoordX2			=ThrePoint->InsTargetCoordX2;
		InsTargetCoordY2			=ThrePoint->InsTargetCoordY2;
		InspectResult				=ThrePoint->InspectResult;
//		NGBitmap					=ThrePoint->NGBitmap;
		FPack						=ThrePoint->FPack;
//		ThresholdDifferencemap		=ThrePoint->ThresholdDifferencemap;
		XLen						=ThrePoint->XLen;
		YLen						=ThrePoint->YLen;
		pAlignPage					=ThrePoint->pAlignPage;
		pHoleAlignPage				=ThrePoint->pHoleAlignPage;
		PixData						=ThrePoint->PixData;

		break;
	}
	ShowThreshold();
}

void PixelHistogramForm::ShowThreshold(void)
{
	//NULL?I??
	if(PoleTable==NULL){
		return;
	}

	//?a?E?I?l?d?X?V
	Update(0,MasterBrightness);
	Update(1,AverageBrightness);
	Update(2,LightBrightness);
	Update(3,DarkBrightness);
	Update(4,TargetBrightness);
	Update(5,InsTargetBrightness);
	Update(6,InsTargetBrightness);
	Update(7,MasterBrightness2);
	Update(8,AverageBrightness2);
	Update(9,LightBrightness2);
	Update(10,DarkBrightness2);
	Update(11,TargetBrightness);

	int Mdx,Mdy,Tdx,Tdy;
	int Mdx2,Mdy2,Tdx2,Tdy2;
	if(pAlignPage==NULL){
		Mdx=Mdy=Tdx=Tdy=0;
		Mdx2=Mdy2=Tdx2=Tdy2=0;
	}
	else{
		Mdx	=pAlignPage->GetShiftXFromMaster(localX,localY);
		Mdy	=pAlignPage->GetShiftYFromMaster(localX,localY);
		Tdx	=pAlignPage->GetShiftXFromTarget(localX,localY);
		Tdy	=pAlignPage->GetShiftYFromTarget(localX,localY);
		Mdx2=pAlignPage->GetShiftXFromMaster(MasterX,MasterY);
		Mdy2=pAlignPage->GetShiftYFromMaster(MasterX,MasterY);
		Tdx2=pAlignPage->GetShiftXFromTarget(MasterX,MasterY);
		Tdy2=pAlignPage->GetShiftYFromTarget(MasterX,MasterY);
	}

	ui.leCoordX					->setText(QString::number(localX));
	ui.leCoordY					->setText(QString::number(localY));
//	ui.leDisorder				->setText(QString::number(DisorderValue));
	ui.leDisorder				->setText(QString::number(PixData[localY+Tdy][localX+Tdx].StdDisorder));
	ui.leAlignmentMasterX		->setText(QString::number(Mdx));
	ui.leAlignmentMasterY		->setText(QString::number(Mdy));
	ui.leAlignmentTargetX		->setText(QString::number(Tdx));
	ui.leAlignmentTargetY		->setText(QString::number(Tdy));
	ui.leCoordX_2				->setText(QString::number(MasterX));
	ui.leCoordY_2				->setText(QString::number(MasterY));
	ui.leDisorder_2				->setText(QString::number(PixData[MasterY][MasterX].StdDisorder));
	ui.leAlignmentMasterX_2		->setText(QString::number(Mdx2));
	ui.leAlignmentMasterY_2		->setText(QString::number(Mdy2));
	ui.leAlignmentTargetX_2		->setText(QString::number(Tdx2));
	ui.leAlignmentTargetY_2		->setText(QString::number(Tdy2));
	ui.lePL						->setText(QString::number(PL));
	ui.lePH						->setText(QString::number(PH));
	ui.leSL						->setText(QString::number(SL));
	ui.leSH						->setText(QString::number(SH));
	ui.leRL						->setText(QString::number(RL));
	ui.leRH						->setText(QString::number(RH));
	ui.lePL_2					->setText(QString::number(PL1));
	ui.lePH_2					->setText(QString::number(PH1));
	ui.leSL_2					->setText(QString::number(SL1));
	ui.leSH_2					->setText(QString::number(SH1));
	ui.leRL_2					->setText(QString::number(RL1));
	ui.leRH_2					->setText(QString::number(RH1));
	ui.lePL_3					->setText(QString::number(PLr));
	ui.lePH_3					->setText(QString::number(PHr));
	ui.leSL_3					->setText(QString::number(SLr));
	ui.leSH_3					->setText(QString::number(SHr));
	ui.leRL_3					->setText(QString::number(RLr));
	ui.leRH_3					->setText(QString::number(RHr));
	ui.lePL_4					->setText(QString::number(PLr1));
	ui.lePH_4					->setText(QString::number(PHr1));
	ui.leSL_4					->setText(QString::number(SLr1));
	ui.leSH_4					->setText(QString::number(SHr1));
	ui.leRL_4					->setText(QString::number(RLr1));
	ui.leRH_4					->setText(QString::number(RHr1));
	ui.sbInspectLevel			->setValue(InspectionLevel);
	ui.sbSearchAreaForMakeTable	->setValue(SearchAreaForMakeTable);
	ui.sbSearchDotBase			->setValue(SearchDotBase);
	ui.lbPlus					->setText(QString::number(ThresholdRange));
	ui.lbMasX					->setText(QString::number(InsAverageCoordX));
	ui.lbMasY					->setText(QString::number(InsAverageCoordY));
	ui.lbInsX					->setText(QString::number(InsTargetCoordX));
	ui.lbInsY					->setText(QString::number(InsTargetCoordY));
	ui.lbPlus_2					->setText(QString::number(256-1));
	ui.lbMasX_2					->setText(QString::number(InsAverageCoordX2));
	ui.lbMasY_2					->setText(QString::number(InsAverageCoordY2));
	ui.lbInsX_2					->setText(QString::number(InsTargetCoordX2));
	ui.lbInsY_2					->setText(QString::number(InsTargetCoordY2));

	//e??lOver?d?F?A?\?|
	ShowCalcThreshold();

	//NG?T?C?Y?I?`?a
	ShowNGSize();

	//OpenGL?`?a?w?|
	UpdateDraw();
}

void PixelHistogramForm::ShowCalcThreshold(void)
{
	//e??lOver?d?F?A?\?|
//	int ValuePlusMinus	=256-InspectionLevel;ThresholdRange
	int ValuePlusMinus	=ThresholdRange;
	QPalette DefaultP,P,PP;
	DefaultP.setColor(QPalette::Base,QColor(Qt::white));
	P		.setColor(QPalette::Base,QColor(Qt::yellow));
	PP		.setColor(QPalette::Base,QColor(Qt::red));
	int ValueP		=leP[4]	->text().toInt();
	int ValuePLMinus=PL-ValuePlusMinus;
	int ValuePHPlus	=PH+ValuePlusMinus;
	ui.lbPLMinus	->setText(QString::number(Clip255(ValuePLMinus)));
	ui.lbPHPlus		->setText(QString::number(Clip255(ValuePHPlus)));
	ThresholdDifference=0;
	if(ValueP<ValuePLMinus){
		leP[4]	->setPalette(PP);	//ui.leP_5
		leP[11]	->setPalette(PP);	//ui.leP_12
		ThresholdDifference=ValuePLMinus-ValueP;
	}
	else if(ValueP<PL){
		leP[4]	->setPalette(P);
		leP[11]	->setPalette(P);
		ThresholdDifference=PL-ValueP;
	}
	else if(ValueP>ValuePHPlus){
		leP[4]	->setPalette(PP);
		leP[11]	->setPalette(PP);
		ThresholdDifference=ValueP-ValuePHPlus;
	}
	else if(ValueP>PH){
		leP[4]	->setPalette(P);
		leP[11]	->setPalette(P);
		ThresholdDifference=ValueP-PH;
	}
	else{
		leP[4]	->setPalette(DefaultP);
		leP[11]	->setPalette(DefaultP);
	}
	int ValueS		=leS[4]	->text().toInt();
	int ValueSLMinus=SL-ValuePlusMinus;
	int ValueSHPlus	=SH+ValuePlusMinus;
	ui.lbSLMinus	->setText(QString::number(Clip255(ValueSLMinus)));
	ui.lbSHPlus		->setText(QString::number(Clip255(ValueSHPlus)));
	if(ValueS<ValueSLMinus){
		leS[4]	->setPalette(PP);	//ui.leS_5
		leS[11]	->setPalette(PP);	//ui.leS_12
		if(ValueSLMinus-ValueS>ThresholdDifference){
			ThresholdDifference=ValueSLMinus-ValueS;
		}
	}
	else if(ValueS<SL){
		leS[4]	->setPalette(P);
		leS[11]	->setPalette(P);
		if(SL-ValueS>ThresholdDifference){
			ThresholdDifference=SL-ValueS;
		}
	}
	else if(ValueS>ValueSHPlus){
		leS[4]	->setPalette(PP);
		leS[11]	->setPalette(PP);
		if(ValueS-ValueSHPlus>ThresholdDifference){
			ThresholdDifference=ValueS-ValueSHPlus;
		}
	}
	else if(ValueS>SH){
		leS[4]	->setPalette(P);
		leS[11]	->setPalette(P);
		if(ValueS-SH>ThresholdDifference){
			ThresholdDifference=ValueS-SH;
		}
	}
	else{
		leS[4]	->setPalette(DefaultP);
		leS[11]	->setPalette(DefaultP);
	}
	int ValueR		=leR[4]	->text().toInt();
	int ValueRLMinus=RL-ValuePlusMinus;
	int ValueRHPlus	=RH+ValuePlusMinus;
	ui.lbRLMinus	->setText(QString::number(Clip255(ValueRLMinus)));
	ui.lbRHPlus		->setText(QString::number(Clip255(ValueRHPlus)));
	if(ValueR<ValueRLMinus){
		leR[4]	->setPalette(PP);	//ui.leR_5
		leR[11]	->setPalette(PP);	//ui.leR_12
		if(ValueRLMinus-ValueR>ThresholdDifference){
			ThresholdDifference=ValueRLMinus-ValueR;
		}
	}
	else if(ValueR<RL){
		leR[4]	->setPalette(P);
		leR[11]	->setPalette(P);
		if(RL-ValueR>ThresholdDifference){
			ThresholdDifference=RL-ValueR;
		}
	}
	else if(ValueR>ValueRHPlus){
		leR[4]	->setPalette(PP);
		leR[11]	->setPalette(PP);
		if(ValueR-ValueRHPlus>ThresholdDifference){
			ThresholdDifference=ValueR-ValueRHPlus;
		}
	}
	else if(ValueR>RH){
		leR[4]	->setPalette(P);
		leR[11]	->setPalette(P);
		if(ValueR-RH>ThresholdDifference){
			ThresholdDifference=ValueR-RH;
		}
	}
	else{
		leR[4]	->setPalette(DefaultP);
		leR[11]	->setPalette(DefaultP);
	}

	//?u?I?I?μ?≪?￠?l
	ValuePLMinus	=PL1-ValuePlusMinus;
	ValuePHPlus		=PH1+ValuePlusMinus;
	ui.lbPLMinus_2	->setText(QString::number(Clip255(ValuePLMinus)));
	ui.lbPHPlus_2	->setText(QString::number(Clip255(ValuePHPlus)));
	if(ValueP<ValuePLMinus){
		ui.lePL_2->setPalette(PP);
		if(ValuePLMinus-ValueP>ThresholdDifference){
			ThresholdDifference=ValuePLMinus-ValueP;
		}
	}
	else if(ValueP<PL1){
		ui.lePL_2->setPalette(P);
	}
	else if(ValueP>ValuePHPlus){
		ui.lePH_2->setPalette(PP);
	}
	else if(ValueP>PH1){
		ui.lePH_2->setPalette(P);
	}
	else{
		ui.lePL_2->setPalette(DefaultP);
		ui.lePH_2->setPalette(DefaultP);
	}
	ValueSLMinus	=SL1-ValuePlusMinus;
	ValueSHPlus		=SH1+ValuePlusMinus;
	ui.lbSLMinus_2	->setText(QString::number(Clip255(ValueSLMinus)));
	ui.lbSHPlus_2	->setText(QString::number(Clip255(ValueSHPlus)));
	if(ValueS<ValueSLMinus){
		ui.leSL_2->setPalette(PP);
	}
	else if(ValueS<SL1){
		ui.leSL_2->setPalette(P);
	}
	else if(ValueS>ValueSHPlus){
		ui.leSH_2->setPalette(PP);
	}
	else if(ValueS>SH1){
		ui.leSH_2->setPalette(P);
	}
	else{
		ui.leSL_2->setPalette(DefaultP);
		ui.leSH_2->setPalette(DefaultP);
	}
	ValueRLMinus	=RL1-ValuePlusMinus;
	ValueRHPlus		=RH1+ValuePlusMinus;
	ui.lbRLMinus_2	->setText(QString::number(Clip255(ValueRLMinus)));
	ui.lbRHPlus_2	->setText(QString::number(Clip255(ValueRHPlus)));
	if(ValueR<ValueRLMinus){
		ui.leRL_2->setPalette(PP);
	}
	else if(ValueR<RL1){
		ui.leRL_2->setPalette(P);
	}
	else if(ValueR>ValueRHPlus){
		ui.leRH_2->setPalette(PP);
	}
	else if(ValueR>RH1){
		ui.leRH_2->setPalette(P);
	}
	else{
		ui.leRL_2->setPalette(DefaultP);
		ui.leRH_2->setPalette(DefaultP);
	}

	//?u?I?I???，?a??
	ValueP		=leP[5]->text().toInt();
	ValuePLMinus=PL-ValuePlusMinus;
	ValuePHPlus	=PH+ValuePlusMinus;
	if(ValueP<ValuePLMinus){
		leP[5]->setPalette(PP);
	}
	else if(ValueP<PL){
		leP[5]->setPalette(P);
	}
	else if(ValueP>ValuePHPlus){
		leP[5]->setPalette(PP);
	}
	else if(ValueP>PH){
		leP[5]->setPalette(P);
	}
	else{
		leP[5]->setPalette(DefaultP);
	}
	ValueS		=leS[5]->text().toInt();
	ValueSLMinus=SL-ValuePlusMinus;
	ValueSHPlus	=SH+ValuePlusMinus;
	if(ValueS<ValueSLMinus){
		leS[5]->setPalette(PP);
	}
	else if(ValueS<SL){
		leS[5]->setPalette(P);
	}
	else if(ValueS>ValueSHPlus){
		leS[5]->setPalette(PP);
	}
	else if(ValueS>SH){
		leS[5]->setPalette(P);
	}
	else{
		leS[5]->setPalette(DefaultP);
	}
	ValueR		=leR[5]->text().toInt();
	ValueRLMinus=RL-ValuePlusMinus;
	ValueRHPlus	=RH+ValuePlusMinus;
	if(ValueR<ValueRLMinus){
		leR[5]->setPalette(PP);
	}
	else if(ValueR<RL){
		leR[5]->setPalette(P);
	}
	else if(ValueR>ValueRHPlus){
		leR[5]->setPalette(PP);
	}
	else if(ValueR>RH){
		leR[5]->setPalette(P);
	}
	else{
		leR[5]->setPalette(DefaultP);
	}
/*
	//???W?X?g
	//e??lOver?d?F?A?\?|
	ValuePlusMinus	=256-1;
	ValueP		=leP[11]->text().toInt();
	ValuePLMinus=PLr-ValuePlusMinus;
	ValuePHPlus	=PHr+ValuePlusMinus;
	ui.lbPLMinus_3	->setText(QString::number(Clip255(ValuePLMinus)));
	ui.lbPHPlus_3	->setText(QString::number(Clip255(ValuePHPlus)));
	if(ValueP<ValuePLMinus){
		leP[11]->setPalette(PP);	//ui.leP_12
	}
	else if(ValueP<PLr){
		leP[11]->setPalette(P);
	}
	else if(ValueP>ValuePHPlus){
		leP[11]->setPalette(PP);
	}
	else if(ValueP>PHr){
		leP[11]->setPalette(P);
	}
	else{
		leP[11]->setPalette(DefaultP);
	}
	ValueS		=leS[11]->text().toInt();
	ValueSLMinus=SLr-ValuePlusMinus;
	ValueSHPlus	=SHr+ValuePlusMinus;
	ui.lbSLMinus_3	->setText(QString::number(Clip255(ValueSLMinus)));
	ui.lbSHPlus_3	->setText(QString::number(Clip255(ValueSHPlus)));
	if(ValueS<ValueSLMinus){
		leS[11]->setPalette(PP);	//ui.leS_5
	}
	else if(ValueS<SLr){
		leS[11]->setPalette(P);
	}
	else if(ValueS>ValueSHPlus){
		leS[11]->setPalette(PP);
	}
	else if(ValueS>SHr){
		leS[11]->setPalette(P);
	}
	else{
		leS[11]->setPalette(DefaultP);
	}
	ValueR		=leR[11]->text().toInt();
	ValueRLMinus=RL-ValuePlusMinus;
	ValueRHPlus	=RH+ValuePlusMinus;
	ui.lbRLMinus_3	->setText(QString::number(Clip255(ValueRLMinus)));
	ui.lbRHPlus_3	->setText(QString::number(Clip255(ValueRHPlus)));
	if(ValueR<ValueRLMinus){
		leR[11]->setPalette(PP);	//ui.leR_5
	}
	else if(ValueR<RLr){
		leR[11]->setPalette(P);
	}
	else if(ValueR>ValueRHPlus){
		leR[11]->setPalette(PP);
	}
	else if(ValueR>RHr){
		leR[11]->setPalette(P);
	}
	else{
		leR[11]->setPalette(DefaultP);
	}
*/
	//?u?I?I?μ?≪?￠?l
	ValuePLMinus	=PLr1-ValuePlusMinus;
	ValuePHPlus		=PHr1+ValuePlusMinus;
	ui.lbPLMinus_4	->setText(QString::number(Clip255(ValuePLMinus)));
	ui.lbPHPlus_4	->setText(QString::number(Clip255(ValuePHPlus)));
	if(ValueP<ValuePLMinus){
		ui.lePL_4->setPalette(PP);
	}
	else if(ValueP<PLr1){
		ui.lePL_4->setPalette(P);
	}
	else if(ValueP>ValuePHPlus){
		ui.lePH_4->setPalette(PP);
	}
	else if(ValueP>PHr1){
		ui.lePH_4->setPalette(P);
	}
	else{
		ui.lePL_4->setPalette(DefaultP);
		ui.lePH_4->setPalette(DefaultP);
	}
	ValueSLMinus	=SLr1-ValuePlusMinus;
	ValueSHPlus		=SHr1+ValuePlusMinus;
	ui.lbSLMinus_4	->setText(QString::number(Clip255(ValueSLMinus)));
	ui.lbSHPlus_4	->setText(QString::number(Clip255(ValueSHPlus)));
	if(ValueS<ValueSLMinus){
		ui.leSL_4->setPalette(PP);
	}
	else if(ValueS<SLr1){
		ui.leSL_4->setPalette(P);
	}
	else if(ValueS>ValueSHPlus){
		ui.leSH_4->setPalette(PP);
	}
	else if(ValueS>SHr1){
		ui.leSH_4->setPalette(P);
	}
	else{
		ui.leSL_4->setPalette(DefaultP);
		ui.leSH_4->setPalette(DefaultP);
	}
	ValueRLMinus	=RLr1-ValuePlusMinus;
	ValueRHPlus		=RHr1+ValuePlusMinus;
	ui.lbRLMinus_4	->setText(QString::number(Clip255(ValueRLMinus)));
	ui.lbRHPlus_4	->setText(QString::number(Clip255(ValueRHPlus)));
	if(ValueR<ValueRLMinus){
		ui.leRL_4->setPalette(PP);
	}
	else if(ValueR<RLr1){
		ui.leRL_4->setPalette(P);
	}
	else if(ValueR>ValueRHPlus){
		ui.leRH_4->setPalette(PP);
	}
	else if(ValueR>RHr1){
		ui.leRH_4->setPalette(P);
	}
	else{
		ui.leRL_4->setPalette(DefaultP);
		ui.leRH_4->setPalette(DefaultP);
	}

	//?u?I?I???，?a??
	ValueP		=leP[6]->text().toInt();
	ValuePLMinus=PLr-ValuePlusMinus;
	ValuePHPlus	=PHr+ValuePlusMinus;
	if(ValueP<ValuePLMinus){
		leP[6]->setPalette(PP);
	}
	else if(ValueP<PLr){
		leP[6]->setPalette(P);
	}
	else if(ValueP>ValuePHPlus){
		leP[6]->setPalette(PP);
	}
	else if(ValueP>PHr){
		leP[6]->setPalette(P);
	}
	else{
		leP[6]->setPalette(DefaultP);
	}
	ValueS		=leS[6]->text().toInt();
	ValueSLMinus=SLr-ValuePlusMinus;
	ValueSHPlus	=SHr+ValuePlusMinus;
	if(ValueS<ValueSLMinus){
		leS[6]->setPalette(PP);
	}
	else if(ValueS<SLr){
		leS[6]->setPalette(P);
	}
	else if(ValueS>ValueSHPlus){
		leS[6]->setPalette(PP);
	}
	else if(ValueS>SHr){
		leS[6]->setPalette(P);
	}
	else{
		leS[6]->setPalette(DefaultP);
	}
	ValueR		=leR[6]->text().toInt();
	ValueRLMinus=RLr-ValuePlusMinus;
	ValueRHPlus	=RHr+ValuePlusMinus;
	if(ValueR<ValueRLMinus){
		leR[6]->setPalette(PP);
	}
	else if(ValueR<RLr){
		leR[6]->setPalette(P);
	}
	else if(ValueR>ValueRHPlus){
		leR[6]->setPalette(PP);
	}
	else if(ValueR>RHr){
		leR[6]->setPalette(P);
	}
	else{
		leR[6]->setPalette(DefaultP);
	}

	//???，???E?I?i?n?d?\?|
	QString ResultMsg=/**/"";
//////////////////////////////////////////////////////
//					?E?i?I???，						//
//////////////////////////////////////////////////////
	//Master?a???c?cTarget?a???O?I?I?・?A?I???，
	//?u?I?I?μ?≪?￠?l?A?I???，//
	if((InspectResult&0x01)!=0){		//?u?I?I?μ?≪?￠?l?A?E?iNG
		ui.lbPixelInfo				->setVisible(true);
		ui.lbPlusPixelInfo			->setVisible(false);
		ui.lbAroundThreshold		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_66)/*"NG"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::red));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_67)/*"?y?u?I?I?μ?≪?￠?l?z?E?i?m?f?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x02)!=0){	//?u?I?I?μ?≪?￠?l?A?E?iOK
		ui.lbPixelInfo				->setVisible(true);
		ui.lbPlusPixelInfo			->setVisible(false);
		ui.lbAroundThreshold		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_68)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_69)/*"?y?u?I?I?μ?≪?￠?l?z?￣?e?_?I?μ?≪?￠?l?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x04)!=0){	//?u?I?I?μ?≪?￠?l?A?u?e?I?μ?≪?￠?l?AOK
		ui.lbPixelInfo				->setVisible(false);
		ui.lbPlusPixelInfo			->setVisible(true);
		ui.lbAroundThreshold		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_70)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_71)/*"?y?u?I?I?μ?≪?￠?l?z?u?e?I?μ?≪?￠?l?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x08)!=0){	//?u?I?I?μ?≪?￠?l?A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo				->setVisible(false);
		ui.lbPlusPixelInfo			->setVisible(true);
		ui.lbAroundThreshold		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_72)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_73)/*"?y?u?I?I?μ?≪?￠?l?z?μ?≪?￠?l???￢?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x10)!=0){	//?u?I?I?μ?≪?￠?l?ANG?X???b?V???z?[???h?AOK
		ui.lbPixelInfo				->setVisible(true);
		ui.lbPlusPixelInfo			->setVisible(false);
		ui.lbAroundThreshold		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_74)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_75)/*"?y?u?I?I?μ?≪?￠?l?zNG?X???b?V???z?[???h?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	ui.lbAroundThreshold->setPalette(lbAroundInsPalette);

	//?u?I?I???，?a???A?I???，//
	if((InspectResult&0x0100)!=0){		//?u?I?I???，?a???A?E?iNG
		ui.lbPixelInfo_2	->setVisible(true);
		ui.lbPlusPixelInfo_2->setVisible(false);
		ui.lbAroundIns		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_76)/*"NG"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::red));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_77)/*"?y?u?I?I???，?a???z?E?i?m?f?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x0200)!=0){	//?u?I?I???，?a???A?E?iOK
		ui.lbPixelInfo_2	->setVisible(true);
		ui.lbPlusPixelInfo_2->setVisible(false);
		ui.lbAroundIns		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_78)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_79)/*"?y?u?I?I???，?a???z?￣?e?_?I???，?a???A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x0400)!=0){	//?u?I?I???，?a???A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo_2	->setVisible(false);
		ui.lbPlusPixelInfo_2->setVisible(true);
		ui.lbAroundIns		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_80)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_81)/*"?y?u?I?I???，?a???z?u?e?I???，?a???A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x0800)!=0){	//?u?I?I???，?a???A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo_2	->setVisible(false);
		ui.lbPlusPixelInfo_2->setVisible(true);
		ui.lbAroundIns		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_82)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_83)/*"?y?u?I?I???，?a???z?u?e?I???，?a?????￢?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x1000)!=0){	//?u?I?I???，?a???A?μ?≪?￠?lOK
		ui.lbPixelInfo_2	->setVisible(true);
		ui.lbPlusPixelInfo_2->setVisible(false);
		ui.lbAroundIns		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_84)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_85)/*"?y?u?I?I???，?a???zNG?X???b?V???z?[???h?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	ui.lbAroundIns->setPalette(lbAroundInsPalette);

	//???u?\?|?^?u?I?Y?e
	if((InspectResult&0xFFFF)!=0){
		ui.tabWidget->setCurrentIndex(1);
	}

	//Target?a???c?cMaster?a???O?I?I?・?A?I???，
	//?u?I?I?μ?≪?￠?l?A?I???，//
	if((InspectResult&0x010000)!=0){		//?u?I?I?μ?≪?￠?l?A?E?iNG
		ui.lbPixelInfo				->setVisible(true);
		ui.lbPlusPixelInfo			->setVisible(false);
		ui.lbAroundThreshold		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_86)/*"NG"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::red));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_87)/*"?y?u?I?I?μ?≪?￠?l?z?E?i?m?f?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x020000)!=0){	//?u?I?I?μ?≪?￠?l?A?E?iOK
		ui.lbPixelInfo				->setVisible(true);
		ui.lbPlusPixelInfo			->setVisible(false);
		ui.lbAroundThreshold		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_88)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_89)/*"?y?u?I?I?μ?≪?￠?l?z?￣?e?_?I?μ?≪?￠?l?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x040000)!=0){	//?u?I?I?μ?≪?￠?l?A?u?e?I?μ?≪?￠?l?AOK
		ui.lbPixelInfo				->setVisible(false);
		ui.lbPlusPixelInfo			->setVisible(true);
		ui.lbAroundThreshold		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_90)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_91)/*"?y?u?I?I?μ?≪?￠?l?z?u?e?I?μ?≪?￠?l?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x080000)!=0){	//?u?I?I?μ?≪?￠?l?A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo				->setVisible(false);
		ui.lbPlusPixelInfo			->setVisible(true);
		ui.lbAroundThreshold		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_92)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_93)/*"?y?u?I?I?μ?≪?￠?l?z?μ?≪?￠?l???￢?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x100000)!=0){	//?u?I?I?μ?≪?￠?l?ANG?X???b?V???z?[???h?AOK
		ui.lbPixelInfo				->setVisible(true);
		ui.lbPlusPixelInfo			->setVisible(false);
		ui.lbAroundThreshold		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_94)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_95)/*"?y?u?I?I?μ?≪?￠?l?zNG?X???b?V???z?[???h?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	ui.lbAroundThreshold->setPalette(lbAroundInsPalette);

	//?u?I?I???，?a???A?I???，//
	if((InspectResult&0x01000000)!=0){		//?u?I?I???，?a???A?E?iNG
		ui.lbPixelInfo_2	->setVisible(true);
		ui.lbPlusPixelInfo_2->setVisible(false);
		ui.lbAroundIns		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_96)/*"NG"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::red));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_97)/*"?y?u?I?I???，?a???z?E?i?m?f?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x02000000)!=0){	//?u?I?I???，?a???A?E?iOK
		ui.lbPixelInfo_2	->setVisible(true);
		ui.lbPlusPixelInfo_2->setVisible(false);
		ui.lbAroundIns		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_98)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_99)/*"?y?u?I?I???，?a???z?￣?e?_?I???，?a???A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x04000000)!=0){	//?u?I?I???，?a???A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo_2	->setVisible(false);
		ui.lbPlusPixelInfo_2->setVisible(true);
		ui.lbAroundIns		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_100)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_101)/*"?y?u?I?I???，?a???z?u?e?I???，?a???A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x08000000)!=0){	//?u?I?I???，?a???A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo_2	->setVisible(false);
		ui.lbPlusPixelInfo_2->setVisible(true);
		ui.lbAroundIns		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_102)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_103)/*"?y?u?I?I???，?a???z?u?e?I???，?a?????￢?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x10000000)!=0){	//?u?I?I???，?a???A?μ?≪?￠?lOK
		ui.lbPixelInfo_2	->setVisible(true);
		ui.lbPlusPixelInfo_2->setVisible(false);
		ui.lbAroundIns		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_104)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_105)/*"?y?u?I?I???，?a???zNG?X???b?V???z?[???h?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	ui.lbAroundIns->setPalette(lbAroundInsPalette);

	//???u?\?|?^?u?I?Y?e
	if((InspectResult&0xFFFF0000)!=0){
		ui.tabWidget->setCurrentIndex(0);
	}

//////////////////////////////////////////////////////
//		???W?X?g?i?p?b?h?A?V???N?E?O?j?I???，		//
//////////////////////////////////////////////////////
	//Master?a???c?cTarget?a???O?I?I?・?A?I???，
	//?u?I?I?μ?≪?￠?l?A?I???，//
	if((InspectResult&0x0100000000)!=0){		//?u?I?I?μ?≪?￠?l?A?E?iNG
		ui.lbPixelInfo_3			->setVisible(true);
		ui.lbPlusPixelInfo_3		->setVisible(false);
		ui.lbAroundThreshold_2		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_106)/*"NG"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::red));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_107)/*"???W?X?g?y?u?I?I?μ?≪?￠?l?z?E?i?m?f?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x0200000000)!=0){	//?u?I?I?μ?≪?￠?l?A?E?iOK
		ui.lbPixelInfo_3			->setVisible(true);
		ui.lbPlusPixelInfo_3		->setVisible(false);
		ui.lbAroundThreshold_2		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_108)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_109)/*"???W?X?g?y?u?I?I?μ?≪?￠?l?z?￣?e?_?I?μ?≪?￠?l?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x0400000000)!=0){	//?u?I?I?μ?≪?￠?l?A?u?e?I?μ?≪?￠?l?AOK
		ui.lbPixelInfo_3			->setVisible(false);
		ui.lbPlusPixelInfo_3		->setVisible(true);
		ui.lbAroundThreshold_2		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_110)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_111)/*"???W?X?g?y?u?I?I?μ?≪?￠?l?z?u?e?I?μ?≪?￠?l?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x0800000000)!=0){	//?u?I?I?μ?≪?￠?l?A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo_3			->setVisible(false);
		ui.lbPlusPixelInfo_3		->setVisible(true);
		ui.lbAroundThreshold_2		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_112)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_113)/*"???W?X?g?y?u?I?I?μ?≪?￠?l?z?μ?≪?￠?l???￢?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x1000000000)!=0){	//?u?I?I?μ?≪?￠?l?ANG?X???b?V???z?[???h?AOK
		ui.lbPixelInfo_3			->setVisible(true);
		ui.lbPlusPixelInfo_3		->setVisible(false);
		ui.lbAroundThreshold_2		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_114)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_115)/*"???W?X?g?y?u?I?I?μ?≪?￠?l?zNG?X???b?V???z?[???h?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	ui.lbAroundThreshold_2->setPalette(lbAroundInsPalette);

	//?u?I?I???，?a???A?I???，//
	if((InspectResult&0x010000000000)!=0){		//?u?I?I???，?a???A?E?iNG
		ui.lbPixelInfo_4	->setVisible(true);
		ui.lbPlusPixelInfo_4->setVisible(false);
		ui.lbAroundIns_2	->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_116)/*"NG"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::red));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_117)/*"???W?X?g?y?u?I?I???，?a???z?E?i?m?f?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x020000000000)!=0){	//?u?I?I???，?a???A?E?iOK
		ui.lbPixelInfo_4	->setVisible(true);
		ui.lbPlusPixelInfo_4->setVisible(false);
		ui.lbAroundIns_2	->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_118)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_119)/*"???W?X?g?y?u?I?I???，?a???z?￣?e?_?I???，?a???A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x040000000000)!=0){	//?u?I?I???，?a???A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo_4	->setVisible(false);
		ui.lbPlusPixelInfo_4->setVisible(true);
		ui.lbAroundIns_2	->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_120)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_121)/*"???W?X?g?y?u?I?I???，?a???z?u?e?I???，?a???A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x080000000000)!=0){	//?u?I?I???，?a???A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo_4	->setVisible(false);
		ui.lbPlusPixelInfo_4->setVisible(true);
		ui.lbAroundIns_2	->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_122)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_123)/*"???W?X?g?y?u?I?I???，?a???z?u?e?I???，?a?????￢?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x100000000000)!=0){	//?u?I?I???，?a???A?μ?≪?￠?lOK
		ui.lbPixelInfo_4	->setVisible(true);
		ui.lbPlusPixelInfo_4->setVisible(false);
		ui.lbAroundIns_2	->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_124)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_125)/*"???W?X?g?y?u?I?I???，?a???zNG?X???b?V???z?[???h?A?n?j?i?}?X?^?[?a???c?c?I?I?・?j"*/;
	}
	ui.lbAroundIns_2->setPalette(lbAroundInsPalette);

	//???u?\?|?^?u?I?Y?e
	if((InspectResult&0xFFFF)!=0){
		ui.tabWidget->setCurrentIndex(1);
	}

	//Target?a???c?cMaster?a???O?I?I?・?A?I???，
	//?u?I?I?μ?≪?￠?l?A?I???，//
	if((InspectResult&0x01000000000000)!=0){		//?u?I?I?μ?≪?￠?l?A?E?iNG
		ui.lbPixelInfo_3			->setVisible(true);
		ui.lbPlusPixelInfo_3		->setVisible(false);
		ui.lbAroundThreshold_2		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_126)/*"NG"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::red));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_127)/*"???W?X?g?y?u?I?I?μ?≪?￠?l?z?E?i?m?f?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x02000000000000)!=0){	//?u?I?I?μ?≪?￠?l?A?E?iOK
		ui.lbPixelInfo_3			->setVisible(true);
		ui.lbPlusPixelInfo_3		->setVisible(false);
		ui.lbAroundThreshold_2		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_128)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_129)/*"???W?X?g?y?u?I?I?μ?≪?￠?l?z?￣?e?_?I?μ?≪?￠?l?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x04000000000000)!=0){	//?u?I?I?μ?≪?￠?l?A?u?e?I?μ?≪?￠?l?AOK
		ui.lbPixelInfo_3			->setVisible(false);
		ui.lbPlusPixelInfo_3		->setVisible(true);
		ui.lbAroundThreshold_2		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_130)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_131)/*"???W?X?g?y?u?I?I?μ?≪?￠?l?z?u?e?I?μ?≪?￠?l?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x08000000000000)!=0){	//?u?I?I?μ?≪?￠?l?A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo_3			->setVisible(false);
		ui.lbPlusPixelInfo_3		->setVisible(true);
		ui.lbAroundThreshold_2		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_132)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_133)/*"???W?X?g?y?u?I?I?μ?≪?￠?l?z?μ?≪?￠?l???￢?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x10000000000000)!=0){	//?u?I?I?μ?≪?￠?l?ANG?X???b?V???z?[???h?AOK
		ui.lbPixelInfo_3			->setVisible(true);
		ui.lbPlusPixelInfo_3		->setVisible(false);
		ui.lbAroundThreshold_2		->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_134)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_135)/*"???W?X?g?y?u?I?I?μ?≪?￠?l?zNG?X???b?V???z?[???h?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	ui.lbAroundThreshold_2->setPalette(lbAroundInsPalette);

	//?u?I?I???，?a???A?I???，//
	if((InspectResult&0x0100000000000000)!=0){		//?u?I?I???，?a???A?E?iNG
		ui.lbPixelInfo_4	->setVisible(true);
		ui.lbPlusPixelInfo_4->setVisible(false);
		ui.lbAroundIns_2	->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_136)/*"NG"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::red));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_137)/*"???W?X?g?y?u?I?I???，?a???z?E?i?m?f?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x0200000000000000)!=0){	//?u?I?I???，?a???A?E?iOK
		ui.lbPixelInfo_4	->setVisible(true);
		ui.lbPlusPixelInfo_4->setVisible(false);
		ui.lbAroundIns_2	->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_138)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_139)/*"???W?X?g?y?u?I?I???，?a???z?￣?e?_?I???，?a???A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x0400000000000000)!=0){	//?u?I?I???，?a???A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo_4	->setVisible(false);
		ui.lbPlusPixelInfo_4->setVisible(true);
		ui.lbAroundIns_2	->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_140)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_141)/*"???W?X?g?y?u?I?I???，?a???z?u?e?I???，?a???A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x0800000000000000)!=0){	//?u?I?I???，?a???A?μ?≪?￠?l???￢OK
		ui.lbPixelInfo_4	->setVisible(false);
		ui.lbPlusPixelInfo_4->setVisible(true);
		ui.lbAroundIns_2	->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_142)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_143)/*"???W?X?g?y?u?I?I???，?a???z?u?e?I???，?a?????￢?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	else if((InspectResult&0x1000000000000000)!=0){	//?u?I?I???，?a???A?μ?≪?￠?lOK
		ui.lbPixelInfo_4	->setVisible(true);
		ui.lbPlusPixelInfo_4->setVisible(false);
		ui.lbAroundIns_2	->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_144)/*"OK"*/);
		lbAroundInsPalette.setColor(QPalette::WindowText,QColor(Qt::green));
		ResultMsg+=LangSolver.GetString(PixelHistogramForm_LS,LID_145)/*"???W?X?g?y?u?I?I???，?a???zNG?X???b?V???z?[???h?A?n?j?i???，?a???c?c?I?I?・?j"*/;
	}
	ui.lbAroundIns_2->setPalette(lbAroundInsPalette);
	ui.leResultMsg->setText(ResultMsg);

	//???u?\?|?^?u?I?Y?e
	if((InspectResult&0xFFFF0000)!=0){
		ui.tabWidget->setCurrentIndex(0);
	}
}

void PixelHistogramForm::ShowNGSize(void)
{
	//???I?a???A?I?P?x?・
//	ui.leRGBDifference->setText(QString::number(ThresholdDifferencemap[localY][localX]));
	ui.leRGBDifference->setText(QString::number(ThresholdDifference));

	//?A??NG?s?N?Z????
	bool MachFlag=false;
	PureFlexAreaList *c;
	for(c=FPack->GetFirst();c!=NULL;c=c->GetNext()){
		if(c->IsInclude(localX,localY)==true){
			MachFlag=true;
			break;
		}
	}
	int NGPixelNumb=0;
	if(MachFlag==true){
		NGPixelNumb=c->GetPatternByte();
	}

	//???W?X?g
	if((InspectResult&0x0100000000)!=0			/*?u?I?I?μ?≪?￠?l?A?E?iNG?iMaster?a???c?cTarget?a???O?I?I?・?j*/
	|| (InspectResult&0x010000000000)!=0		/*?u?I?I???，?a???A?E?iNG?iMaster?a???c?cTarget?a???O?I?I?・?j*/
	|| (InspectResult&0x01000000000000)!=0		/*?u?I?I?μ?≪?￠?l?A?E?iNG?iTarget?a???c?cMaster?a???O?I?I?・?j*/
	|| (InspectResult&0x0100000000000000)!=0){	/*?u?I?I???，?a???A?E?iNG?iTarget?a???c?cMaster?a???O?I?I?・?j*/
		ui.leNGPixelNumb_2->setText(QString::number(NGPixelNumb));
		//Display
		QPalette P;
		if(MachFlag==true){
			P.setColor(QPalette::WindowText,QColor(Qt::red));
			ui.lbNGSize_2->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_146)/*"NG"*/);
		}
		else{
			P.setColor(QPalette::WindowText,QColor(Qt::green));
			ui.lbNGSize_2->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_147)/*"OK"*/);
		}
		ui.lbNGSize_2->setPalette(P);
	}
	else{
		ui.leNGPixelNumb->setText(QString::number(NGPixelNumb));
		//Display
		QPalette P;
		if(MachFlag==true){
			P.setColor(QPalette::WindowText,QColor(Qt::red));
			ui.lbNGSize->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_148)/*"NG"*/);
		}
		else{
			P.setColor(QPalette::WindowText,QColor(Qt::green));
			ui.lbNGSize->setText(LangSolver.GetString(PixelHistogramForm_LS,LID_149)/*"OK"*/);
		}
		ui.lbNGSize->setPalette(P);
	}

///	//NG?T?C?Ye??l?Z?o?l
///	ui.leCalcNGSize->setText(QString::number(D).left(6));
}

void PixelHistogramForm::createSlider(QSlider *slider)
{
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
}
