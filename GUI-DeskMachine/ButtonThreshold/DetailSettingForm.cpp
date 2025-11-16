#include "ButtonThresholdResource.h"
#include "DetailSettingForm.h"
#include "ButtonThreshold.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QMessageBox>

DetailSettingForm::DetailSettingForm(QWidget *parent,GUIFormBase *Base,PixelInspectionBase *PBase)
	: QDialog(parent),LayoutHeight(75)//101->26
{
	ui.setupUi(this);

	setAutoFillBackground(false);

	ParentWidget=(ThresholdSettingForm *)parent;
	GUIBase		=Base;
	PixelBase	=PBase;
	if(ParentWidget->getChosenPhase()!=NULL)
		PBase->GetLayersBase()->TF_SetCurrentScanPhaseNumber(ParentWidget->getChosenPhase()->getPhaseNumber()); // phase function
	//Initial
	InspectionLevel			=PixelBase->getInspectionLevel();
	SearchAreaForMakeTable	=PixelBase->getSearchAreaForMakeTable();
	SearchDotBase			=PixelBase->getSearchDotBase();
	Colored					=PixelBase->getColored();
	DefaultLibraryID		=PixelBase->getDefaultLibraryID();
	BrightnessRange			=PixelBase->getBrightnessRange();

	//画面表示
	SetNGThresholdP_B			(PixelBase->getNGThresholdP_B());
	SetNGThresholdP_D			(PixelBase->getNGThresholdP_D());
	SetNGThresholdS_B			(PixelBase->getNGThresholdS_B());
	SetNGThresholdS_D			(PixelBase->getNGThresholdS_D());
	SetNGThresholdR_B			(PixelBase->getNGThresholdR_B());
	SetNGThresholdR_D			(PixelBase->getNGThresholdR_D());
	SetNGThresholdH_B			(PixelBase->getNGThresholdH_B());
	SetNGThresholdH_D			(PixelBase->getNGThresholdH_D());
	SetMinimumNGSizeP			(PixelBase->getMinimumNGSizeP());
	SetMinimumNGSizeS			(PixelBase->getMinimumNGSizeS());
	SetMinimumNGSizeR			(PixelBase->getMinimumNGSizeR());
	SetMinimumNGSizeH			(PixelBase->getMinimumNGSizeH());
	SetDonePadIns				(PixelBase->getDonePadIns());
	SetDoneSilkIns				(PixelBase->getDoneSilkIns());
	SetDoneResistIns			(PixelBase->getDoneResistIns());
	SetDoneHoleIns				(PixelBase->getDoneHoleIns());
	SetNGThresholdForPad_B		(PixelBase->getNGThresholdForPad_B());
	SetNGThresholdForPad_D		(PixelBase->getNGThresholdForPad_D());
	SetMinimumNGSizeForPad		(PixelBase->getMinimumNGSizeForPad());
	SetNGThresholdForSilk_B		(PixelBase->getNGThresholdForSilk_B());
	SetNGThresholdForSilk_D		(PixelBase->getNGThresholdForSilk_D());
	SetMinimumNGSizeForSilk		(PixelBase->getMinimumNGSizeForSilk());
	SetNGThresholdForResist_B	(PixelBase->getNGThresholdForResist_B());
	SetNGThresholdForResist_D	(PixelBase->getNGThresholdForResist_D());
	SetMinimumNGSizeForResist	(PixelBase->getMinimumNGSizeForResist());
	SetNGThresholdForHole_B		(PixelBase->getNGThresholdForHole_B());
	SetNGThresholdForHole_D		(PixelBase->getNGThresholdForHole_D());
	SetMinimumNGSizeForHole		(PixelBase->getMinimumNGSizeForHole());
	SetIsCalcPixelInterPoration	(PixelBase->getIsCalcPixelInterPoration());

	//レイアウト
	gbDetailSettingPY			=ui.gbDetailSettingP		->y();
	gbDetailSettingPH			=ui.gbDetailSettingP		->height();
	gbDetailSettingSY			=ui.gbDetailSettingS		->y();
	gbDetailSettingSH			=ui.gbDetailSettingS		->height();
	gbDetailSettingRY			=ui.gbDetailSettingR		->y();
	gbDetailSettingRH			=ui.gbDetailSettingR		->height();
	gbDetailSettingHY			=ui.gbDetailSettingH		->y();
	gbDetailSettingHH			=ui.gbDetailSettingH		->height();
	gbDetailSettingForPadY		=ui.gbDetailSettingForPad	->y();
	gbDetailSettingForPadH		=ui.gbDetailSettingForPad	->height();
	gbDetailSettingForSilkY		=ui.gbDetailSettingForSilk	->y();
	gbDetailSettingForSilkH		=ui.gbDetailSettingForSilk	->height();
	gbDetailSettingForResistY	=ui.gbDetailSettingForResist->y();
	gbDetailSettingForResistH	=ui.gbDetailSettingForResist->height();
	gbDetailSettingForHoleY		=ui.gbDetailSettingForHole	->y();
	gbDetailSettingForHoleH		=ui.gbDetailSettingForHole	->height();
	chbIsCalcPixelInterPorationY=ui.chbIsCalcPixelInterPoration	->y();
	gbDetailSettingY			=ui.gbDetailSetting				->y();
	gbDetailSettingH			=ui.gbDetailSetting				->height();
	lbDecisionY					=ui.lbDecision					->y();
	lbCancelY					=ui.lbCancel					->y();
///	chSettingForPadY			=ui.chSettingForPad				->y();
	chSettingForSilkY			=ui.chSettingForSilk			->y();
	chSettingForResistY			=ui.chSettingForResist			->y();
	chSettingForHoleY			=ui.chSettingForHole			->y();
	H							=height();
	SetLayout();

	//ボタン
	QImage DecisionImage(ParentWidget->DecisionImageBmpFile[((ButtonThreshold *)GUIBase)->LanguageCode]);
	BtnDecision=new mtImageToolButton(ui.lbDecision,false);
	BtnDecision->setImageBmp(DecisionImage);
	BtnDecision->setIconSize(QSize(DecisionImage.width(),DecisionImage.height()));
	connect(BtnDecision,SIGNAL(SignalClicked()),this,SLOT(SlotBtnDecisionClicked()));

	QImage CancelImage(ParentWidget->CancelImageBmpFile[((ButtonThreshold *)GUIBase)->LanguageCode]);
	BtnCancel=new mtImageToolButton(ui.lbCancel,false);
	BtnCancel->setImageBmp(CancelImage);
	BtnCancel->setIconSize(QSize(CancelImage.width(),CancelImage.height()));
	connect(BtnCancel,SIGNAL(SignalClicked()),this,SLOT(SlotBtnCancelClicked()));

	connect(ui.hsNGThresholdP_B	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdP_BValueChanged(int)));
	connect(ui.hsNGThresholdP_D	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdP_DValueChanged(int)));
	connect(ui.dsbNGThresholdP_B,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdP_BValueChanged(double)));
	connect(ui.dsbNGThresholdP_D,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdP_DValueChanged(double)));
	connect(ui.hsNGThresholdS_B	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdS_BValueChanged(int)));
	connect(ui.hsNGThresholdS_D	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdS_DValueChanged(int)));
	connect(ui.dsbNGThresholdS_B,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdS_BValueChanged(double)));
	connect(ui.dsbNGThresholdS_D,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdS_DValueChanged(double)));
	connect(ui.hsNGThresholdR_B	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdR_BValueChanged(int)));
	connect(ui.hsNGThresholdR_D	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdR_DValueChanged(int)));
	connect(ui.dsbNGThresholdR_B,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdR_BValueChanged(double)));
	connect(ui.dsbNGThresholdR_D,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdR_DValueChanged(double)));
	connect(ui.hsNGThresholdH_B	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdH_BValueChanged(int)));
	connect(ui.hsNGThresholdH_D	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdH_DValueChanged(int)));
	connect(ui.dsbNGThresholdH_B,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdH_BValueChanged(double)));
	connect(ui.dsbNGThresholdH_D,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdH_DValueChanged(double)));
	connect(ui.diMinimumNGSizeP	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizePValueChanged(int)));
	connect(ui.sbMinimumNGSizeP	,SIGNAL(valueChanged(int))	 ,this,SLOT(sbMinimumNGSizePValueChanged(int)));
	connect(ui.diMinimumNGSizeS	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeSValueChanged(int)));
	connect(ui.sbMinimumNGSizeS	,SIGNAL(valueChanged(int))	 ,this,SLOT(sbMinimumNGSizeSValueChanged(int)));
	connect(ui.diMinimumNGSizeR	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeRValueChanged(int)));
	connect(ui.sbMinimumNGSizeR	,SIGNAL(valueChanged(int))	 ,this,SLOT(sbMinimumNGSizeRValueChanged(int)));
	connect(ui.diMinimumNGSizeH	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeHValueChanged(int)));
	connect(ui.sbMinimumNGSizeH	,SIGNAL(valueChanged(int))	 ,this,SLOT(sbMinimumNGSizeHValueChanged(int)));

	connect(ui.hsNGThresholdForPad_B	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForPad_BValueChanged(int)));
	connect(ui.hsNGThresholdForPad_D	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForPad_DValueChanged(int)));
	connect(ui.sbNGThresholdForPad_B	,SIGNAL(valueChanged(int)),this,SLOT(sbNGThresholdForPad_BValueChanged(int)));
	connect(ui.sbNGThresholdForPad_D	,SIGNAL(valueChanged(int)),this,SLOT(sbNGThresholdForPad_DValueChanged(int)));
	connect(ui.diMinimumNGSizeForPad	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForPadValueChanged(int)));
	connect(ui.sbMinimumNGSizeForPad	,SIGNAL(valueChanged(int)),this,SLOT(sbMinimumNGSizeForPadValueChanged(int)));
	connect(ui.hsNGThresholdForSilk_B	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForSilk_BValueChanged(int)));
	connect(ui.hsNGThresholdForSilk_D	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForSilk_DValueChanged(int)));
	connect(ui.sbNGThresholdForSilk_B	,SIGNAL(valueChanged(int)),this,SLOT(sbNGThresholdForSilk_BValueChanged(int)));
	connect(ui.sbNGThresholdForSilk_D	,SIGNAL(valueChanged(int)),this,SLOT(sbNGThresholdForSilk_DValueChanged(int)));
	connect(ui.diMinimumNGSizeForSilk	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForSilkValueChanged(int)));
	connect(ui.sbMinimumNGSizeForSilk	,SIGNAL(valueChanged(int)),this,SLOT(sbMinimumNGSizeForSilkValueChanged(int)));
	connect(ui.hsNGThresholdForResist_B	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForResist_BValueChanged(int)));
	connect(ui.hsNGThresholdForResist_D	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForResist_DValueChanged(int)));
	connect(ui.sbNGThresholdForResist_B	,SIGNAL(valueChanged(int)),this,SLOT(sbNGThresholdForResist_BValueChanged(int)));
	connect(ui.sbNGThresholdForResist_D	,SIGNAL(valueChanged(int)),this,SLOT(sbNGThresholdForResist_DValueChanged(int)));
	connect(ui.diMinimumNGSizeForResist ,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForResistValueChanged(int)));
	connect(ui.sbMinimumNGSizeForResist	,SIGNAL(valueChanged(int)),this,SLOT(sbMinimumNGSizeForResistValueChanged(int)));
	connect(ui.hsNGThresholdForHole_B	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForHole_BValueChanged(int)));
	connect(ui.hsNGThresholdForHole_D	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForHole_DValueChanged(int)));
	connect(ui.sbNGThresholdForHole_B	,SIGNAL(valueChanged(int)),this,SLOT(sbNGThresholdForHole_BValueChanged(int)));
	connect(ui.sbNGThresholdForHole_D	,SIGNAL(valueChanged(int)),this,SLOT(sbNGThresholdForHole_DValueChanged(int)));
	connect(ui.diMinimumNGSizeForHole	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForHoleValueChanged(int)));
	connect(ui.sbMinimumNGSizeForHole	,SIGNAL(valueChanged(int)),this,SLOT(sbMinimumNGSizeForHoleValueChanged(int)));

	connect(ui.gbDetailSettingForPad	,SIGNAL(toggled(bool)),this,SLOT(gbDetailSettingForPadToggled(bool)));
	connect(ui.gbDetailSettingForSilk	,SIGNAL(toggled(bool)),this,SLOT(gbDetailSettingForSilkToggled(bool)));
	connect(ui.gbDetailSettingForResist	,SIGNAL(toggled(bool)),this,SLOT(gbDetailSettingForResistToggled(bool)));
	connect(ui.gbDetailSettingForHole	,SIGNAL(toggled(bool)),this,SLOT(gbDetailSettingForHoleToggled(bool)));

	connect(ui.chSettingForPad		,SIGNAL(toggled(bool)),this,SLOT(chSettingForPadToggled(bool)));
	connect(ui.chSettingForSilk		,SIGNAL(toggled(bool)),this,SLOT(chSettingForSilkToggled(bool)));
	connect(ui.chSettingForResist	,SIGNAL(toggled(bool)),this,SLOT(chSettingForResistToggled(bool)));
	connect(ui.chSettingForHole		,SIGNAL(toggled(bool)),this,SLOT(chSettingForHoleToggled(bool)));

	connect(ui.pbSaveInsParam	,SIGNAL(clicked()),this,SLOT(pbSaveInsParamClicked()));
	connect(ui.pbLoadInsParam	,SIGNAL(clicked()),this,SLOT(pbLoadInsParamClicked()));

	//画面表示（シグナルが飛ぶようにconnectの後に設定）
	SetCheckPadIns				(PixelBase->getCheckPadIns());
	SetCheckSilkIns				(PixelBase->getCheckSilkIns());
	SetCheckResistIns			(PixelBase->getCheckResistIns());
	SetCheckHoleIns				(PixelBase->getCheckHoleIns());

	//透過処理
///	setWindowOpacity(0.5);
/*
	//パレットを設定しautoFillBackgroundを利用して透明色で塗りつぶす
	QPalette palette;
	palette.setColor(QPalette::Window, QColor(255, 255, 255, 128));
	setPalette(palette);
	setAutoFillBackground(true);
*/
	//setAttribute
///	setAttribute(Qt::WA_TransparentForMouseEvents);

	//画面表示部の言語対応
	LangSolver.SetUI(this);
/*
	//スタイルシート
//	ui.gbDetailSetting	->setStyleSheet("border-style: dot-dot-dash;font-size: 12pt;");
	ui.gbDetailSetting	->setStyleSheet(QGroupBox().styleSheet());
	ui.pbSaveInsParam	->setStyleSheet(QPushButton().styleSheet());
	ui.pbLoadInsParam	->setStyleSheet("border-style: dotted;font-size: 9pt;");
*/
}

DetailSettingForm::~DetailSettingForm()
{
}
/*
void DetailSettingForm::paintEvent(QPaintEvent	*event)
{
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(255,255,255,128));
	painter.drawEllipse(0,0,width(),height());
}
*/
void DetailSettingForm::hsNGThresholdP_BValueChanged(int Value)
{
	ui.dsbNGThresholdP_B->setValue(-Value/10.0);
}

void DetailSettingForm::hsNGThresholdP_DValueChanged(int Value)
{
	ui.dsbNGThresholdP_D->setValue(Value/10.0);
}

void DetailSettingForm::dsbNGThresholdP_BValueChanged(double Value)
{
	ui.hsNGThresholdP_B->setValue(-Value*10);
}

void DetailSettingForm::dsbNGThresholdP_DValueChanged(double Value)
{
	ui.hsNGThresholdP_D->setValue(Value*10);
}

void DetailSettingForm::hsNGThresholdS_BValueChanged(int Value)
{
	ui.dsbNGThresholdS_B->setValue(-Value/10.0);
}

void DetailSettingForm::hsNGThresholdS_DValueChanged(int Value)
{
	ui.dsbNGThresholdS_D->setValue(Value/10.0);
}

void DetailSettingForm::dsbNGThresholdS_BValueChanged(double Value)
{
	ui.hsNGThresholdS_B->setValue(-Value*10);
}

void DetailSettingForm::dsbNGThresholdS_DValueChanged(double Value)
{
	ui.hsNGThresholdS_D->setValue(Value*10);
}

void DetailSettingForm::hsNGThresholdR_BValueChanged(int Value)
{
	ui.dsbNGThresholdR_B->setValue(-Value/10.0);
}

void DetailSettingForm::hsNGThresholdR_DValueChanged(int Value)
{
	ui.dsbNGThresholdR_D->setValue(Value/10.0);
}

void DetailSettingForm::dsbNGThresholdR_BValueChanged(double Value)
{
	ui.hsNGThresholdR_B->setValue(-Value*10);
}

void DetailSettingForm::dsbNGThresholdR_DValueChanged(double Value)
{
	ui.hsNGThresholdR_D->setValue(Value*10);
}

void DetailSettingForm::hsNGThresholdH_BValueChanged(int Value)
{
	ui.dsbNGThresholdH_B->setValue(-Value/10.0);
}

void DetailSettingForm::hsNGThresholdH_DValueChanged(int Value)
{
	ui.dsbNGThresholdH_D->setValue(Value/10.0);
}

void DetailSettingForm::dsbNGThresholdH_BValueChanged(double Value)
{
	ui.hsNGThresholdH_B->setValue(-Value*10);
}

void DetailSettingForm::dsbNGThresholdH_DValueChanged(double Value)
{
	ui.hsNGThresholdH_D->setValue(Value*10);
}

void DetailSettingForm::diMinimumNGSizePValueChanged(int Value)
{
	ui.sbMinimumNGSizeP->setValue(Value);
}

void DetailSettingForm::sbMinimumNGSizePValueChanged(int Value)
{
	if(Value>ui.diMinimumNGSizeP->maximum()){
		disconnect(ui.diMinimumNGSizeP	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizePValueChanged(int)));
	}
	ui.diMinimumNGSizeP->setValue(Value);

	if(Value>ui.diMinimumNGSizeP->maximum()){
		connect(ui.diMinimumNGSizeP	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizePValueChanged(int)));
	}
}

void DetailSettingForm::diMinimumNGSizeSValueChanged(int Value)
{
	ui.sbMinimumNGSizeS->setValue(Value);
}

void DetailSettingForm::sbMinimumNGSizeSValueChanged(int Value)
{
	if(Value>ui.diMinimumNGSizeS->maximum()){
		disconnect(ui.diMinimumNGSizeS	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeSValueChanged(int)));
	}
	ui.diMinimumNGSizeS->setValue(Value);

	if(Value>ui.diMinimumNGSizeS->maximum()){
		connect(ui.diMinimumNGSizeS	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeSValueChanged(int)));
	}
}

void DetailSettingForm::diMinimumNGSizeRValueChanged(int Value)
{
	ui.sbMinimumNGSizeR->setValue(Value);
}

void DetailSettingForm::sbMinimumNGSizeRValueChanged(int Value)
{
	if(Value>ui.diMinimumNGSizeR->maximum()){
		disconnect(ui.diMinimumNGSizeR	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeRValueChanged(int)));
	}
	ui.diMinimumNGSizeR->setValue(Value);

	if(Value>ui.diMinimumNGSizeR->maximum()){
		connect(ui.diMinimumNGSizeR	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeRValueChanged(int)));
	}
}

void DetailSettingForm::diMinimumNGSizeHValueChanged(int Value)
{
	ui.sbMinimumNGSizeH->setValue(Value);
}

void DetailSettingForm::sbMinimumNGSizeHValueChanged(int Value)
{
	if(Value>ui.diMinimumNGSizeH->maximum()){
		disconnect(ui.diMinimumNGSizeH	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeHValueChanged(int)));
	}
	ui.diMinimumNGSizeH->setValue(Value);

	if(Value>ui.diMinimumNGSizeH->maximum()){
		connect(ui.diMinimumNGSizeH	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeHValueChanged(int)));
	}
}

void DetailSettingForm::hsNGThresholdForPad_BValueChanged(int Value)
{
	ui.sbNGThresholdForPad_B->setValue(ui.hsNGThresholdForPad_B->maximum()-Value+1);
}

void DetailSettingForm::hsNGThresholdForPad_DValueChanged(int Value)
{
	ui.sbNGThresholdForPad_D->setValue(Value);
}

void DetailSettingForm::sbNGThresholdForPad_BValueChanged(int Value)
{
	if(Value>ui.hsNGThresholdForPad_B->maximum()){
		disconnect(ui.hsNGThresholdForPad_B		,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForPad_BValueChanged(int)));
	}
	ui.hsNGThresholdForPad_B->setValue(ui.hsNGThresholdForPad_B->maximum()-Value+1);

	if(Value>ui.hsNGThresholdForPad_B->maximum()){
		connect(ui.hsNGThresholdForPad_B	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForPad_BValueChanged(int)));
	}
}

void DetailSettingForm::sbNGThresholdForPad_DValueChanged(int Value)
{
	if(Value>ui.hsNGThresholdForPad_D->maximum()){
		disconnect(ui.hsNGThresholdForPad_D		,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForPad_DValueChanged(int)));
	}
	ui.hsNGThresholdForPad_D->setValue(Value);

	if(Value>ui.hsNGThresholdForPad_D->maximum()){
		connect(ui.hsNGThresholdForPad_D	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForPad_DValueChanged(int)));
	}
}

void DetailSettingForm::diMinimumNGSizeForPadValueChanged(int Value)
{
	ui.sbMinimumNGSizeForPad->setValue(Value);
}

void DetailSettingForm::sbMinimumNGSizeForPadValueChanged(int Value)
{
	if(Value>ui.diMinimumNGSizeForPad->maximum()){
		disconnect(ui.diMinimumNGSizeForPad	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForPadValueChanged(int)));
	}
	ui.diMinimumNGSizeForPad->setValue(Value);

	if(Value>ui.diMinimumNGSizeForPad->maximum()){
		connect(ui.diMinimumNGSizeForPad	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForPadValueChanged(int)));
	}
}

void DetailSettingForm::hsNGThresholdForSilk_BValueChanged(int Value)
{
	ui.sbNGThresholdForSilk_B->setValue(ui.hsNGThresholdForSilk_B->maximum()-Value+1);
}

void DetailSettingForm::hsNGThresholdForSilk_DValueChanged(int Value)
{
	ui.sbNGThresholdForSilk_D->setValue(Value);
}

void DetailSettingForm::sbNGThresholdForSilk_BValueChanged(int Value)
{
	if(Value>ui.hsNGThresholdForSilk_B->maximum()){
		disconnect(ui.hsNGThresholdForSilk_B	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForSilk_BValueChanged(int)));
	}
	ui.hsNGThresholdForSilk_B->setValue(ui.hsNGThresholdForSilk_B->maximum()-Value+1);

	if(Value>ui.hsNGThresholdForSilk_B->maximum()){
		connect(ui.hsNGThresholdForSilk_B	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForSilk_BValueChanged(int)));
	}
}

void DetailSettingForm::sbNGThresholdForSilk_DValueChanged(int Value)
{
	if(Value>ui.hsNGThresholdForSilk_D->maximum()){
		disconnect(ui.hsNGThresholdForSilk_D	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForSilk_DValueChanged(int)));
	}
	ui.hsNGThresholdForSilk_D->setValue(Value);

	if(Value>ui.hsNGThresholdForSilk_D->maximum()){
		connect(ui.hsNGThresholdForSilk_D	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForSilk_DValueChanged(int)));
	}
}

void DetailSettingForm::diMinimumNGSizeForSilkValueChanged(int Value)
{
	ui.sbMinimumNGSizeForSilk->setValue(Value);
}

void DetailSettingForm::sbMinimumNGSizeForSilkValueChanged(int Value)
{
	if(Value>ui.diMinimumNGSizeForSilk->maximum()){
		disconnect(ui.diMinimumNGSizeForSilk	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForSilkValueChanged(int)));
	}
	ui.diMinimumNGSizeForSilk->setValue(Value);

	if(Value>ui.diMinimumNGSizeForSilk->maximum()){
		connect(ui.diMinimumNGSizeForSilk	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForSilkValueChanged(int)));
	}
}

void DetailSettingForm::hsNGThresholdForResist_BValueChanged(int Value)
{
	ui.sbNGThresholdForResist_B->setValue(ui.hsNGThresholdForResist_B->maximum()-Value+1);
}

void DetailSettingForm::hsNGThresholdForResist_DValueChanged(int Value)
{
	ui.sbNGThresholdForResist_D->setValue(Value);
}

void DetailSettingForm::sbNGThresholdForResist_BValueChanged(int Value)
{
	if(Value>ui.hsNGThresholdForResist_B->maximum()){
		disconnect(ui.hsNGThresholdForResist_B		,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForResist_BValueChanged(int)));
	}
	ui.hsNGThresholdForResist_B->setValue(ui.hsNGThresholdForResist_B->maximum()-Value+1);

	if(Value>ui.hsNGThresholdForResist_B->maximum()){
		connect(ui.hsNGThresholdForResist_B		,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForResist_BValueChanged(int)));
	}
}

void DetailSettingForm::sbNGThresholdForResist_DValueChanged(int Value)
{
	if(Value>ui.hsNGThresholdForResist_D->maximum()){
		disconnect(ui.hsNGThresholdForResist_D		,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForResist_DValueChanged(int)));
	}
	ui.hsNGThresholdForResist_D->setValue(Value);

	if(Value>ui.hsNGThresholdForResist_D->maximum()){
		connect(ui.hsNGThresholdForResist_D		,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForResist_DValueChanged(int)));
	}
}

void DetailSettingForm::diMinimumNGSizeForResistValueChanged(int Value)
{
	ui.sbMinimumNGSizeForResist->setValue(Value);
}

void DetailSettingForm::sbMinimumNGSizeForResistValueChanged(int Value)
{
	if(Value>ui.diMinimumNGSizeForResist->maximum()){
		disconnect(ui.diMinimumNGSizeForResist	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForResistValueChanged(int)));
	}
	ui.diMinimumNGSizeForResist->setValue(Value);

	if(Value>ui.diMinimumNGSizeForResist->maximum()){
		connect(ui.diMinimumNGSizeForResist	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForResistValueChanged(int)));
	}
}

void DetailSettingForm::hsNGThresholdForHole_BValueChanged(int Value)
{
	ui.sbNGThresholdForHole_B->setValue(ui.hsNGThresholdForHole_B->maximum()-Value+1);
}

void DetailSettingForm::hsNGThresholdForHole_DValueChanged(int Value)
{
	ui.sbNGThresholdForHole_D->setValue(Value);
}

void DetailSettingForm::sbNGThresholdForHole_BValueChanged(int Value)
{
	if(Value>ui.hsNGThresholdForHole_B->maximum()){
		disconnect(ui.hsNGThresholdForHole_B	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForHole_BValueChanged(int)));
	}
	ui.hsNGThresholdForHole_B->setValue(ui.hsNGThresholdForHole_B->maximum()-Value+1);

	if(Value>ui.hsNGThresholdForHole_B->maximum()){
		connect(ui.hsNGThresholdForHole_B	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForHole_BValueChanged(int)));
	}
}

void DetailSettingForm::sbNGThresholdForHole_DValueChanged(int Value)
{
	if(Value>ui.hsNGThresholdForHole_D->maximum()){
		disconnect(ui.hsNGThresholdForHole_D	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForHole_DValueChanged(int)));
	}
	ui.hsNGThresholdForHole_D->setValue(Value);

	if(Value>ui.hsNGThresholdForHole_D->maximum()){
		connect(ui.hsNGThresholdForHole_D	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForHole_DValueChanged(int)));
	}
}

void DetailSettingForm::diMinimumNGSizeForHoleValueChanged(int Value)
{
	ui.sbMinimumNGSizeForHole->setValue(Value);
}

void DetailSettingForm::sbMinimumNGSizeForHoleValueChanged(int Value)
{
	if(Value>ui.diMinimumNGSizeForHole->maximum()){
		disconnect(ui.diMinimumNGSizeForHole	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForHoleValueChanged(int)));
	}
	ui.diMinimumNGSizeForHole->setValue(Value);

	if(Value>ui.diMinimumNGSizeForHole->maximum()){
		connect(ui.diMinimumNGSizeForHole	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForHoleValueChanged(int)));
	}
}

void DetailSettingForm::pbSaveInsParamClicked()
{
	//AutoSelectFile
	QString DefaultFileName;
	if(((ButtonThreshold *)ParentWidget->GUIBase)->GetLoadParamFilePath().isEmpty()==true){
		if(((ButtonThreshold *)GUIBase)->AutoSelectFile==true){
			DefaultFileName=PixelBase->GetLayersBase()->GetMasterName();
		}
		if(((ButtonThreshold *)GUIBase)->DefaultDirectory.isEmpty()==false){
			DefaultFileName=((ButtonThreshold *)GUIBase)->DefaultDirectory + QDir::separator() + DefaultFileName;
		}
	}
	else{
		DefaultFileName=((ButtonThreshold *)ParentWidget->GUIBase)->GetLoadParamFilePath();
	}

	//検査パラメータの保存
	QString InsParamFilePath=QFileDialog::getSaveFileName(
							this,LangSolver.GetString(DetailSettingForm_LS,LID_0)/*"Please save a Inspection setting parameter file."*/,DefaultFileName,/**/"Inspection setting parameter file (*.dat)");
	if(InsParamFilePath.isEmpty()){
		return;
	}
	QFile	File(InsParamFilePath);
	if(File.open(QIODevice::WriteOnly)==true){
		QTextStream mystream(&File);

		mystream << /**/"InspectionLevel         :" << QString::number(ParentWidget					 ->GetInspectionLevel())	<< endl;
		mystream << /**/"SearchAreaForMakeTable  :" << QString::number(PixelBase					 ->getSearchAreaForMakeTable())	<< endl;
		mystream << /**/"SearchDotBase           :" << QString::number(PixelBase					 ->getSearchDotBase())		<< endl;
		mystream << /**/"Colored                 :" << QString::number(PixelBase					 ->getColored())			<< endl;
		mystream << /**/"DefaultLibraryID        :" << QString::number(PixelBase					 ->getDefaultLibraryID())	<< endl;
		mystream << /**/"NGThresholdP            :" << QString::number(ui.dsbNGThresholdP_B			 ->value())					<< endl;
		mystream << /**/"NGThresholdR            :" << QString::number(ui.dsbNGThresholdR_B			 ->value())					<< endl;
		mystream << /**/"MinimumNGSizeP          :" << QString::number(ui.sbMinimumNGSizeP			 ->value())					<< endl;
		mystream << /**/"DoneResistIns           :" << QString::number(ui.gbDetailSettingForResist	 ->isChecked())				<< endl;
		mystream << /**/"NGThresholdForResist    :" << QString::number(ui.sbNGThresholdForResist_B	 ->value())					<< endl;
		mystream << /**/"MinimumNGSizeForResist  :" << QString::number(ui.sbMinimumNGSizeForResist	 ->value())					<< endl;
		mystream << /**/"BrightnessRange         :" << QString::number(PixelBase					 ->getBrightnessRange())	<< endl;
		mystream << /**/"IsCalcPixelInterPoration:" << QString::number(ui.chbIsCalcPixelInterPoration->isChecked())				<< endl;
		mystream <<	/**/"DonePadIns              :" << QString::number(ui.gbDetailSettingForPad		 ->isChecked())				<< endl;
		mystream << /**/"NGThresholdForPad       :" << QString::number(ui.sbNGThresholdForPad_B		 ->value())					<< endl;
		mystream << /**/"MinimumNGSizeForPad     :" << QString::number(ui.sbMinimumNGSizeForPad		 ->value())					<< endl;
		mystream << /**/"MinimumNGSizeR          :" << QString::number(ui.sbMinimumNGSizeR			 ->value())					<< endl;
		mystream << /**/"NGThresholdS            :" << QString::number(ui.dsbNGThresholdS_B			 ->value())					<< endl;
		mystream << /**/"MinimumNGSizeS          :" << QString::number(ui.sbMinimumNGSizeS			 ->value())					<< endl;
		mystream << /**/"DoneSilkIns             :" << QString::number(ui.gbDetailSettingForSilk	 ->isChecked())				<< endl;
		mystream << /**/"NGThresholdForSilk      :" << QString::number(ui.sbNGThresholdForSilk_B	 ->value())					<< endl;
		mystream << /**/"MinimumNGSizeForSilk    :" << QString::number(ui.sbMinimumNGSizeForSilk	 ->value())					<< endl;
		mystream << /**/"NGThresholdH            :" << QString::number(ui.dsbNGThresholdH_B			 ->value())					<< endl;
		mystream << /**/"MinimumNGSizeH          :" << QString::number(ui.sbMinimumNGSizeH			 ->value())					<< endl;
		mystream << /**/"DoneHoleIns             :" << QString::number(ui.gbDetailSettingForHole	 ->isChecked())				<< endl;
		mystream << /**/"NGThresholdForHole      :" << QString::number(ui.sbNGThresholdForHole_B	 ->value())					<< endl;
		mystream << /**/"MinimumNGSizeForHole    :" << QString::number(ui.sbMinimumNGSizeForHole	 ->value())					<< endl;
		mystream << /**/"CheckPadIns             :" << QString::number(ui.chSettingForPad			 ->isChecked())				<< endl;
		mystream << /**/"CheckSilkIns            :" << QString::number(ui.chSettingForSilk			 ->isChecked())				<< endl;
		mystream << /**/"CheckResistIns          :" << QString::number(ui.chSettingForResist		 ->isChecked())				<< endl;
		mystream << /**/"CheckHoleIns            :" << QString::number(ui.chSettingForHole			 ->isChecked())				<< endl;

		mystream << /**/"NGThresholdP_D          :" << QString::number(ui.dsbNGThresholdP_D			 ->value())					<< endl;
		mystream << /**/"NGThresholdForPad_D     :" << QString::number(ui.sbNGThresholdForPad_D		 ->value())					<< endl;
		mystream << /**/"NGThresholdS_D          :" << QString::number(ui.dsbNGThresholdS_D			 ->value())					<< endl;
		mystream << /**/"NGThresholdForSilk_D    :" << QString::number(ui.sbNGThresholdForSilk_D	 ->value())					<< endl;
		mystream << /**/"NGThresholdR_D          :" << QString::number(ui.dsbNGThresholdR_D			 ->value())					<< endl;
		mystream << /**/"NGThresholdForResist_D  :" << QString::number(ui.sbNGThresholdForResist_D	 ->value())					<< endl;
		mystream << /**/"NGThresholdH_D          :" << QString::number(ui.dsbNGThresholdH_D			 ->value())					<< endl;
		mystream << /**/"NGThresholdForHole_D    :" << QString::number(ui.sbNGThresholdForHole_D	 ->value())					<< endl;

		((ButtonThreshold *)ParentWidget->GUIBase)->wInspectionLevel			=ParentWidget->GetInspectionLevel();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdP_B				=ui.dsbNGThresholdP_B->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdP_D				=ui.dsbNGThresholdP_D->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_B				=ui.dsbNGThresholdS_B->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_D				=ui.dsbNGThresholdS_D->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_B				=ui.dsbNGThresholdR_B->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_D				=ui.dsbNGThresholdR_D->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_B				=ui.dsbNGThresholdH_B->value();;
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_D				=ui.dsbNGThresholdH_D->value();;
		((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeP				=ui.sbMinimumNGSizeP->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeS				=ui.sbMinimumNGSizeS->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeR				=ui.sbMinimumNGSizeR->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeH				=ui.sbMinimumNGSizeH->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wCheckPadIns				=ui.chSettingForPad->isChecked();
		((ButtonThreshold *)ParentWidget->GUIBase)->wCheckSilkIns				=ui.chSettingForSilk->isChecked();
		((ButtonThreshold *)ParentWidget->GUIBase)->wCheckResistIns				=ui.chSettingForResist->isChecked();
		((ButtonThreshold *)ParentWidget->GUIBase)->wCheckHoleIns				=ui.chSettingForHole->isChecked();
		((ButtonThreshold *)ParentWidget->GUIBase)->wDonePadIns					=ui.gbDetailSettingForPad->isChecked();
		((ButtonThreshold *)ParentWidget->GUIBase)->wDoneSilkIns				=ui.gbDetailSettingForSilk->isChecked();
		((ButtonThreshold *)ParentWidget->GUIBase)->wDoneResistIns				=ui.gbDetailSettingForResist->isChecked();
		((ButtonThreshold *)ParentWidget->GUIBase)->wDoneHoleIns				=ui.gbDetailSettingForHole->isChecked();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForPad_B		=ui.sbNGThresholdForPad_B->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForPad_D		=ui.sbNGThresholdForPad_D->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForPad		=ui.sbMinimumNGSizeForPad->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_B		=ui.sbNGThresholdForSilk_B->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_D		=ui.sbNGThresholdForSilk_D->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForSilk		=ui.sbMinimumNGSizeForSilk->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_B		=ui.sbNGThresholdForResist_B->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_D		=ui.sbNGThresholdForResist_D->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForResist		=ui.sbMinimumNGSizeForResist->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_B		=ui.sbNGThresholdForHole_B->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_D		=ui.sbNGThresholdForHole_D->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForHole		=ui.sbMinimumNGSizeForHole->value();
		((ButtonThreshold *)ParentWidget->GUIBase)->wIsCalcPixelInterPoration	=ui.chbIsCalcPixelInterPoration->isChecked();

		((ButtonThreshold *)ParentWidget->GUIBase)->SetLoadParamFilePath(InsParamFilePath);
		((ButtonThreshold *)ParentWidget->GUIBase)->ExecCmdShowThresholdFileName();
		((ButtonThreshold *)ParentWidget->GUIBase)->SetFlgLoadParamFilePath(true);

		File.close();
	}
}

void DetailSettingForm::pbLoadInsParamClicked()
{
	//AutoSelectFile
	QString DefaultFileName;
	if(((ButtonThreshold *)GUIBase)->AutoSelectFile==true){
		DefaultFileName=PixelBase->GetLayersBase()->GetMasterName() + /**/".dat";
	}
	QString DefaultDirectory;
	if(((ButtonThreshold *)GUIBase)->DefaultDirectory.isEmpty()==false){
		DefaultDirectory=((ButtonThreshold *)GUIBase)->DefaultDirectory;
	}
	else{
		DefaultDirectory=QDir::currentPath();
	}
	//Check
	QString DefaultFilePath=DefaultDirectory;
	if(((ButtonThreshold *)GUIBase)->AutoSelectFile==true){
		QStringList SearchStrs(DefaultFileName);
		QStringList FilePathList;
		SearchThresholdFile(DefaultDirectory,SearchStrs,FilePathList);
		if(FilePathList.count()>0){
			if(FilePathList.count()>1){
				//Message
				QString FilePathText=/**/"\n";
				for(int i=FilePathList.count()-1;i>=0;i--){
					FilePathText+=/**/"\n " + FilePathList.at(i);
				}
				QMessageBox MsgBox;
//				MsgBox.setFont	(font1[LanguageCode]);
				MsgBox.setText	("Found more than one file."
								+ FilePathText);
				MsgBox.addButton(/**/"OK",QMessageBox::AcceptRole);
				MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
				MsgBox.exec();
			}
			DefaultFilePath=FilePathList.last();
		}
		else{
			//Message
			QMessageBox MsgBox;
//			MsgBox.setFont	(font1[LanguageCode]);
			MsgBox.setText	("File not found.");
			MsgBox.addButton(/**/"OK",QMessageBox::AcceptRole);
			MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
			MsgBox.exec();
		}
	}

	//検査パラメータの読込
	QString InsParamFilePath=QFileDialog::getOpenFileName(
							this,LangSolver.GetString(DetailSettingForm_LS,LID_2)/*"Please choose a Inspection setting parameter file."*/,DefaultFilePath,/**/"Inspection setting parameter file (*.dat)");
	if(InsParamFilePath.isEmpty()){
		return;
	}

	//Check
	if(((ButtonThreshold *)GUIBase)->AutoSelectFile==true){
		if(InsParamFilePath.split(/**/"/").last()!=DefaultFilePath.split(/**/"/").last()){
			//Message
			QMessageBox MsgBox;
//			MsgBox.setFont	(font1[LanguageCode]);
			MsgBox.setText	("File is wrong.");
			MsgBox.addButton(/**/"OK",QMessageBox::AcceptRole);
			MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
			MsgBox.exec();
		}
	}

	QFile	File(InsParamFilePath);
	if(File.open(QIODevice::ReadOnly)==true){
		uint64	CheckBit=0;
		QTextStream mystream(&File);
		QString myString;
		while (!mystream.atEnd()){
			myString=mystream.readLine();
			int SplitIndex=myString.indexOf(/**/":");
			QString Param=myString.mid(SplitIndex+1);
			QString ParamName=myString.left(SplitIndex).remove(' ');
			if(ParamName==/**/"InspectionLevel"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wInspectionLevel=Param.toInt();
				CheckBit|=0x01;
			}
			else if(ParamName==/**/"SearchAreaForMakeTable"){
				SearchAreaForMakeTable=Param.toInt();
				CheckBit|=0x02;
			}
			else if(ParamName==/**/"SearchDotBase"){
				SearchDotBase=Param.toInt();
				CheckBit|=0x04;
			}
			else if(ParamName==/**/"Colored"){
				Colored=Param.toInt();
				CheckBit|=0x08;
			}
			else if(ParamName==/**/"DefaultLibraryID"){
				DefaultLibraryID=Param.toInt();
				CheckBit|=0x10;
			}
			else if(ParamName==/**/"NGThresholdP" || ParamName==/**/"NGThreshold"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdP_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdP_D=Param.toDouble();
				CheckBit|=0x20;
			}
			else if(ParamName==/**/"NGThresholdR"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_D=Param.toDouble();
				CheckBit|=0x40;
			}
			else if(ParamName==/**/"MinimumNGSizeP"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeP=Param.toInt();
				CheckBit|=0x80;
			}
			///////////↓旧バージョン閾値対応↓///////////
			else if(ParamName==/**/"NGThreshold2"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_D=Param.toDouble();
				CheckBit|=0x40;
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_D=Param.toDouble();
				CheckBit|=0x20000;
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_D=Param.toDouble();
				CheckBit|=0x400000;
			}
			else if(ParamName==/**/"MinimumNGSize"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeP=Param.toInt();
				CheckBit|=0x80;
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeR=Param.toInt();
				CheckBit|=0x10000;
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeS=Param.toInt();
				CheckBit|=0x40000;
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeH=Param.toInt();
				CheckBit|=0x800000;
			}
			///////////↑旧バージョン閾値対応↑///////////
			else if(ParamName==/**/"DoneResistIns"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wDoneResistIns=Param.toInt();
				CheckBit|=0x100;
			}
			else if(ParamName==/**/"NGThresholdForResist"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_D=Param.toInt();
				CheckBit|=0x200;
			}
			else if(ParamName==/**/"MinimumNGSizeForResist"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForResist=Param.toInt();
				CheckBit|=0x400;
			}
			else if(ParamName==/**/"BrightnessRange"){
				BrightnessRange=Param.toInt();
				CheckBit|=0x800;
			}
			else if(ParamName==/**/"IsCalcPixelInterPoration"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wIsCalcPixelInterPoration=Param.toInt();
				CheckBit|=0x1000;
			}
			else if(ParamName==/**/"DonePadIns"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wDonePadIns=Param.toInt();
				CheckBit|=0x2000;
			}
			else if(ParamName==/**/"NGThresholdForPad"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForPad_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForPad_D=Param.toInt();
				CheckBit|=0x4000;
			}
			else if(ParamName==/**/"MinimumNGSizeForPad"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForPad=Param.toInt();
				CheckBit|=0x8000;
			}
			else if(ParamName==/**/"MinimumNGSizeR"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeR=Param.toInt();
				CheckBit|=0x10000;
			}
			else if(ParamName==/**/"NGThresholdS"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_D=Param.toDouble();
				CheckBit|=0x20000;
			}
			else if(ParamName==/**/"MinimumNGSizeS"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeS=Param.toInt();
				CheckBit|=0x40000;
			}
			else if(ParamName==/**/"DoneSilkIns"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wDoneSilkIns=Param.toInt();
				CheckBit|=0x80000;
			}
			else if(ParamName==/**/"NGThresholdForSilk"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_D=Param.toInt();
				CheckBit|=0x100000;
			}
			else if(ParamName==/**/"MinimumNGSizeForSilk"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForSilk=Param.toInt();
				CheckBit|=0x200000;
			}
			else if(ParamName==/**/"NGThresholdH"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_D=Param.toDouble();
				CheckBit|=0x400000;
			}
			else if(ParamName==/**/"MinimumNGSizeH"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeH=Param.toInt();
				CheckBit|=0x800000;
			}
			else if(ParamName==/**/"DoneHoleIns"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wDoneHoleIns=Param.toInt();
				CheckBit|=0x1000000;
			}
			else if(ParamName==/**/"NGThresholdForHole"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_B=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_D=Param.toInt();
				CheckBit|=0x2000000;
			}
			else if(ParamName==/**/"MinimumNGSizeForHole"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForHole=Param.toInt();
				CheckBit|=0x4000000;
			}
			else if(ParamName==/**/"CheckPadIns"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wCheckPadIns=Param.toInt();
				CheckBit|=0x8000000;
			}
			else if(ParamName==/**/"CheckSilkIns"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wCheckSilkIns=Param.toInt();
				CheckBit|=0x10000000;
			}
			else if(ParamName==/**/"CheckResistIns"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wCheckResistIns=Param.toInt();
				CheckBit|=0x20000000;
			}
			else if(ParamName==/**/"CheckHoleIns"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wCheckHoleIns=Param.toInt();
				CheckBit|=0x40000000;
			}

			else if(ParamName==/**/"NGThresholdP_D"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdP_D=Param.toDouble();
			}
			else if(ParamName==/**/"NGThresholdForPad_D"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForPad_D=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdS_D"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_D=Param.toDouble();
			}
			else if(ParamName==/**/"NGThresholdForSilk_D"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_D=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdR_D"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_D=Param.toDouble();
			}
			else if(ParamName==/**/"NGThresholdForResist_D"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_D=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdH_D"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_D=Param.toDouble();
			}
			else if(ParamName==/**/"NGThresholdForHole_D"){
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_D=Param.toInt();
			}
		}
		File.close();

		//CheckBitのチェック
		if((CheckBit&0x01)==0){
			QMessageBox MsgBox;
//			MsgBox.setFont	(font1[LanguageCode]);
			MsgBox.setText	("File is wrong.");
			MsgBox.addButton(/**/"OK",QMessageBox::AcceptRole);
			MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
			MsgBox.exec();
			return;
		}
		//DoneResistIns
		if((CheckBit&0x100)!=0){
			//DoneSilkIns
			if((CheckBit&0x80000)==0){
				((ButtonThreshold *)ParentWidget->GUIBase)->wDoneSilkIns			=((ButtonThreshold *)ParentWidget->GUIBase)->wDoneResistIns;
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_B	=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_B;
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_D	=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_D;
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForSilk	=((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForResist;
			}
			//DoneHoleIns
			if((CheckBit&0x1000000)==0){
				((ButtonThreshold *)ParentWidget->GUIBase)->wDoneHoleIns			=((ButtonThreshold *)ParentWidget->GUIBase)->wDoneResistIns;
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_B	=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_B;
				((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_D	=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_D;
				((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForHole	=((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForResist;
			}
			//デフォルトから変更されている場合もあるので、デフォルトに強制的に設定する
			if((CheckBit&0x80000)==0 || (CheckBit&0x1000000)==0){
				((ButtonThreshold *)ParentWidget->GUIBase)->wCheckPadIns	=true;
				((ButtonThreshold *)ParentWidget->GUIBase)->wCheckSilkIns	=true;
				((ButtonThreshold *)ParentWidget->GUIBase)->wCheckResistIns	=true;
				((ButtonThreshold *)ParentWidget->GUIBase)->wCheckHoleIns	=true;
				if(((ButtonThreshold *)ParentWidget->GUIBase)->wInspectionLevel>10){
					ParentWidget->SetInspectionLevel(((ButtonThreshold *)ParentWidget->GUIBase)->wInspectionLevel);	//検査レベルの設定
				}
				else{
					ParentWidget->SetImageSlider(((ButtonThreshold *)ParentWidget->GUIBase)->wInspectionLevel);		//検査レベルの設定
				}
			}
			else{
				ParentWidget->SetImageSlider(((ButtonThreshold *)ParentWidget->GUIBase)->wInspectionLevel);			//検査レベルの設定
			}
		}

		//画面設定
		ui.dsbNGThresholdP_B			->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdP_B);
		ui.dsbNGThresholdP_D			->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdP_D);
		ui.dsbNGThresholdS_B			->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_B);
		ui.dsbNGThresholdS_D			->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_D);
		ui.dsbNGThresholdR_B			->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_B);
		ui.dsbNGThresholdR_D			->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_D);
		ui.dsbNGThresholdH_B			->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_B);
		ui.dsbNGThresholdH_D			->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_D);
		ui.sbMinimumNGSizeP				->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeP);
		ui.sbMinimumNGSizeS				->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeS);
		ui.sbMinimumNGSizeR				->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeR);
		ui.sbMinimumNGSizeH				->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeH);
		ui.chSettingForPad				->setChecked(((ButtonThreshold *)ParentWidget->GUIBase)->wCheckPadIns);
		ui.chSettingForSilk				->setChecked(((ButtonThreshold *)ParentWidget->GUIBase)->wCheckSilkIns);
		ui.chSettingForResist			->setChecked(((ButtonThreshold *)ParentWidget->GUIBase)->wCheckResistIns);
		ui.chSettingForHole				->setChecked(((ButtonThreshold *)ParentWidget->GUIBase)->wCheckHoleIns);
		ui.gbDetailSettingForPad		->setChecked(((ButtonThreshold *)ParentWidget->GUIBase)->wDonePadIns);
		ui.gbDetailSettingForSilk		->setChecked(((ButtonThreshold *)ParentWidget->GUIBase)->wDoneSilkIns);
		ui.gbDetailSettingForResist		->setChecked(((ButtonThreshold *)ParentWidget->GUIBase)->wDoneResistIns);
		ui.gbDetailSettingForHole		->setChecked(((ButtonThreshold *)ParentWidget->GUIBase)->wDoneHoleIns);
		ui.sbNGThresholdForPad_B		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForPad_B);
		ui.sbNGThresholdForPad_D		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForPad_D);
		ui.sbMinimumNGSizeForPad		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForPad);
		ui.sbNGThresholdForSilk_B		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_B);
		ui.sbNGThresholdForSilk_D		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_D);
		ui.sbMinimumNGSizeForSilk		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForSilk);
		ui.sbNGThresholdForResist_B		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_B);
		ui.sbNGThresholdForResist_D		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_D);
		ui.sbMinimumNGSizeForResist		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForResist);
		ui.sbNGThresholdForHole_B		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_B);
		ui.sbNGThresholdForHole_D		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_D);
		ui.sbMinimumNGSizeForHole		->setValue	(((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeForHole);
		ui.chbIsCalcPixelInterPoration	->setChecked(((ButtonThreshold *)ParentWidget->GUIBase)->wIsCalcPixelInterPoration);
	}
	((ButtonThreshold *)ParentWidget->GUIBase)->SetLoadParamFilePath(InsParamFilePath);
	((ButtonThreshold *)ParentWidget->GUIBase)->ExecCmdShowThresholdFileName();
	((ButtonThreshold *)ParentWidget->GUIBase)->SetFlgLoadParamFilePath(true);
}

void DetailSettingForm::SlotBtnDecisionClicked()
{
	if(ParentWidget->getChosenPhase()!=NULL)
		PixelBase->GetLayersBase()->TF_SetCurrentScanPhaseNumber(ParentWidget->getChosenPhase()->getPhaseNumber());

	PixelBase->setNGThresholdP_B			(ui.dsbNGThresholdP_B			->value());
	PixelBase->setNGThresholdP_D			(ui.dsbNGThresholdP_D			->value());
	PixelBase->setNGThresholdS_B			(ui.dsbNGThresholdS_B			->value());
	PixelBase->setNGThresholdS_D			(ui.dsbNGThresholdS_D			->value());
	PixelBase->setNGThresholdR_B			(ui.dsbNGThresholdR_B			->value());
	PixelBase->setNGThresholdR_D			(ui.dsbNGThresholdR_D			->value());
	PixelBase->setNGThresholdH_B			(ui.dsbNGThresholdH_B			->value());
	PixelBase->setNGThresholdH_D			(ui.dsbNGThresholdH_D			->value());
	PixelBase->setMinimumNGSizeP			(ui.sbMinimumNGSizeP			->value());
	PixelBase->setMinimumNGSizeS			(ui.sbMinimumNGSizeS			->value());
	PixelBase->setMinimumNGSizeR			(ui.sbMinimumNGSizeR			->value());
	PixelBase->setMinimumNGSizeH			(ui.sbMinimumNGSizeH			->value());
	PixelBase->setCheckPadIns				(ui.chSettingForPad				->isChecked());
	PixelBase->setCheckSilkIns				(ui.chSettingForSilk			->isChecked());
	PixelBase->setCheckResistIns			(ui.chSettingForResist			->isChecked());
	PixelBase->setCheckHoleIns				(ui.chSettingForHole			->isChecked());
	PixelBase->setDonePadIns				(ui.gbDetailSettingForPad		->isChecked());
	PixelBase->setDoneSilkIns				(ui.gbDetailSettingForSilk		->isChecked());
	PixelBase->setDoneResistIns				(ui.gbDetailSettingForResist	->isChecked());
	PixelBase->setDoneHoleIns				(ui.gbDetailSettingForHole		->isChecked());
	PixelBase->setNGThresholdForPad_B		(ui.sbNGThresholdForPad_B		->value());
	PixelBase->setNGThresholdForPad_D		(ui.sbNGThresholdForPad_D		->value());
	PixelBase->setMinimumNGSizeForPad		(ui.sbMinimumNGSizeForPad		->value());
	PixelBase->setNGThresholdForSilk_B		(ui.sbNGThresholdForSilk_B		->value());
	PixelBase->setNGThresholdForSilk_D		(ui.sbNGThresholdForSilk_D		->value());
	PixelBase->setMinimumNGSizeForSilk		(ui.sbMinimumNGSizeForSilk		->value());
	PixelBase->setNGThresholdForResist_B	(ui.sbNGThresholdForResist_B	->value());
	PixelBase->setNGThresholdForResist_D	(ui.sbNGThresholdForResist_D	->value());
	PixelBase->setMinimumNGSizeForResist	(ui.sbMinimumNGSizeForResist	->value());
	PixelBase->setNGThresholdForHole_B		(ui.sbNGThresholdForHole_B		->value());
	PixelBase->setNGThresholdForHole_D		(ui.sbNGThresholdForHole_D		->value());
	PixelBase->setMinimumNGSizeForHole		(ui.sbMinimumNGSizeForHole		->value());
	PixelBase->setIsCalcPixelInterPoration	(ui.chbIsCalcPixelInterPoration	->isChecked());

	//パラメータに保存
	GUIBase->GetLayersBase()->WriteAllSettingFiles();

	//Check
	if(((ButtonThreshold *)ParentWidget->GUIBase)->GetLoadParamFilePath().isEmpty()==false){
		if(CheckLoadParam()==false){
			((ButtonThreshold *)ParentWidget->GUIBase)->SetLoadParamFilePath(/**/"");
			((ButtonThreshold *)ParentWidget->GUIBase)->ExecCmdShowThresholdFileName();
			((ButtonThreshold *)ParentWidget->GUIBase)->SetFlgLoadParamFilePath(false);
		}
	}

	accept();
}

void DetailSettingForm::SlotBtnCancelClicked()
{
	//Check
	if(((ButtonThreshold *)ParentWidget->GUIBase)->GetFlgLoadParamFilePath()==true){
		((ButtonThreshold *)ParentWidget->GUIBase)->SetLoadParamFilePath(/**/"");
		((ButtonThreshold *)ParentWidget->GUIBase)->ExecCmdShowThresholdFileName();
		((ButtonThreshold *)ParentWidget->GUIBase)->SetFlgLoadParamFilePath(false);
	}

	reject();
}

void DetailSettingForm::SetLayout()
{
	//setUpdatesEnabled
	setUpdatesEnabled(false);

	if(ui.gbDetailSettingForPad->isChecked()==true){
		ui.gbDetailSettingP				->setGeometry	(ui.gbDetailSettingP			->x(),gbDetailSettingPY				,ui.gbDetailSettingP			->width(),gbDetailSettingPH);
		ui.gbDetailSettingS				->setGeometry	(ui.gbDetailSettingS			->x(),gbDetailSettingSY				,ui.gbDetailSettingS			->width(),gbDetailSettingSH);
		ui.gbDetailSettingR				->setGeometry	(ui.gbDetailSettingR			->x(),gbDetailSettingRY				,ui.gbDetailSettingR			->width(),gbDetailSettingRH);
		ui.gbDetailSettingH				->setGeometry	(ui.gbDetailSettingH			->x(),gbDetailSettingHY				,ui.gbDetailSettingH			->width(),gbDetailSettingHH);
		ui.gbDetailSettingForPad		->setGeometry	(ui.gbDetailSettingForPad		->x(),gbDetailSettingForPadY		,ui.gbDetailSettingForPad		->width(),gbDetailSettingForPadH);
		ui.gbDetailSettingForSilk		->setGeometry	(ui.gbDetailSettingForSilk		->x(),gbDetailSettingForSilkY		,ui.gbDetailSettingForSilk		->width(),gbDetailSettingForSilkH);
		ui.gbDetailSettingForResist		->setGeometry	(ui.gbDetailSettingForResist	->x(),gbDetailSettingForResistY		,ui.gbDetailSettingForResist	->width(),gbDetailSettingForResistH);
		ui.gbDetailSettingForHole		->setGeometry	(ui.gbDetailSettingForHole		->x(),gbDetailSettingForHoleY		,ui.gbDetailSettingForHole		->width(),gbDetailSettingForHoleH);
		ui.chbIsCalcPixelInterPoration	->move			(ui.chbIsCalcPixelInterPoration	->x(),chbIsCalcPixelInterPorationY);
		ui.gbDetailSetting				->setGeometry	(ui.gbDetailSetting				->x(),gbDetailSettingY				,ui.gbDetailSetting				->width(),gbDetailSettingH);
		ui.lbDecision					->move			(ui.lbDecision					->x(),lbDecisionY);
		ui.lbCancel						->move			(ui.lbCancel					->x(),lbCancelY);
		ui.chSettingForSilk				->move			(ui.chSettingForSilk	->x(),chSettingForSilkY);
		ui.chSettingForResist			->move			(ui.chSettingForResist->x(),chSettingForResistY);
		ui.chSettingForHole				->move			(ui.chSettingForHole	->x(),chSettingForHoleY);
		resize(width(),H);
	}
	else{
		ui.gbDetailSettingP				->setGeometry	(ui.gbDetailSettingP			->x(),gbDetailSettingPY								,ui.gbDetailSettingP			->width(),gbDetailSettingPH		-LayoutHeight);
		ui.gbDetailSettingS				->setGeometry	(ui.gbDetailSettingS			->x(),gbDetailSettingSY				-LayoutHeight	,ui.gbDetailSettingS			->width(),gbDetailSettingSH);
		ui.gbDetailSettingR				->setGeometry	(ui.gbDetailSettingR			->x(),gbDetailSettingRY				-LayoutHeight	,ui.gbDetailSettingR			->width(),gbDetailSettingRH);
		ui.gbDetailSettingH				->setGeometry	(ui.gbDetailSettingH			->x(),gbDetailSettingHY				-LayoutHeight	,ui.gbDetailSettingH			->width(),gbDetailSettingHH);
		ui.gbDetailSettingForPad		->setGeometry	(ui.gbDetailSettingForPad		->x(),gbDetailSettingForPadY						,ui.gbDetailSettingForPad		->width(),gbDetailSettingForPadH-LayoutHeight);
		ui.gbDetailSettingForSilk		->setGeometry	(ui.gbDetailSettingForSilk		->x(),gbDetailSettingForSilkY						,ui.gbDetailSettingForSilk		->width(),gbDetailSettingForSilkH);
		ui.gbDetailSettingForResist		->setGeometry	(ui.gbDetailSettingForResist	->x(),gbDetailSettingForResistY						,ui.gbDetailSettingForResist	->width(),gbDetailSettingForResistH);
		ui.gbDetailSettingForHole		->setGeometry	(ui.gbDetailSettingForHole		->x(),gbDetailSettingForHoleY						,ui.gbDetailSettingForHole		->width(),gbDetailSettingForHoleH);
		ui.chbIsCalcPixelInterPoration	->move			(ui.chbIsCalcPixelInterPoration	->x(),chbIsCalcPixelInterPorationY	-LayoutHeight);
		ui.gbDetailSetting				->setGeometry	(ui.gbDetailSetting				->x(),gbDetailSettingY								,ui.gbDetailSetting				->width(),gbDetailSettingH		-LayoutHeight);
		ui.lbDecision					->move			(ui.lbDecision					->x(),lbDecisionY					-LayoutHeight);
		ui.lbCancel						->move			(ui.lbCancel					->x(),lbCancelY						-LayoutHeight);
		ui.chSettingForSilk				->move			(ui.chSettingForSilk			->x(),chSettingForSilkY				-LayoutHeight);
		ui.chSettingForResist			->move			(ui.chSettingForResist			->x(),chSettingForResistY			-LayoutHeight);
		ui.chSettingForHole				->move			(ui.chSettingForHole			->x(),chSettingForHoleY				-LayoutHeight);
		resize(width(),H-LayoutHeight);
	}

	if(ui.gbDetailSettingForSilk->isChecked()==false){
		ui.gbDetailSettingS				->resize(ui.gbDetailSettingS			->width()	,gbDetailSettingSH							-LayoutHeight);
		ui.gbDetailSettingR				->move	(ui.gbDetailSettingR			->x()		,ui.gbDetailSettingR			->y()		-LayoutHeight);
		ui.gbDetailSettingH				->move	(ui.gbDetailSettingH			->x()		,ui.gbDetailSettingH			->y()		-LayoutHeight);
		ui.gbDetailSettingForSilk		->resize(ui.gbDetailSettingForSilk		->width()	,gbDetailSettingForSilkH					-LayoutHeight);
///		ui.gbDetailSettingForResist		->resize(ui.gbDetailSettingForResist	->width()	,gbDetailSettingForResistH);
///		ui.gbDetailSettingForHole		->resize(ui.gbDetailSettingForHole		->width()	,gbDetailSettingForHoleH);
		ui.chbIsCalcPixelInterPoration	->move	(ui.chbIsCalcPixelInterPoration	->x()		,ui.chbIsCalcPixelInterPoration	->y()		-LayoutHeight);
		ui.gbDetailSetting				->resize(ui.gbDetailSetting				->width()	,ui.gbDetailSetting				->height()	-LayoutHeight);
		ui.lbDecision					->move	(ui.lbDecision					->x()		,ui.lbDecision					->y()		-LayoutHeight);
		ui.lbCancel						->move	(ui.lbCancel					->x()		,ui.lbCancel					->y()		-LayoutHeight);
		ui.chSettingForResist			->move	(ui.chSettingForResist			->x()		,ui.chSettingForResist			->y()		-LayoutHeight);
		ui.chSettingForHole				->move	(ui.chSettingForHole			->x()		,ui.chSettingForHole			->y()		-LayoutHeight);
		resize(width(),height()-LayoutHeight);
	}

	if(ui.gbDetailSettingForResist->isChecked()==false){
		ui.gbDetailSettingR				->resize(ui.gbDetailSettingR			->width()	,gbDetailSettingRH							-LayoutHeight);
		ui.gbDetailSettingH				->move	(ui.gbDetailSettingH			->x()		,ui.gbDetailSettingH			->y()		-LayoutHeight);
		ui.gbDetailSettingForResist		->resize(ui.gbDetailSettingForResist	->width()	,gbDetailSettingForResistH					-LayoutHeight);
///		ui.gbDetailSettingForHole		->resize(ui.gbDetailSettingForHole		->width()	,gbDetailSettingForHoleH);
		ui.chbIsCalcPixelInterPoration	->move	(ui.chbIsCalcPixelInterPoration	->x()		,ui.chbIsCalcPixelInterPoration	->y()		-LayoutHeight);
		ui.gbDetailSetting				->resize(ui.gbDetailSetting				->width()	,ui.gbDetailSetting				->height()	-LayoutHeight);
		ui.lbDecision					->move	(ui.lbDecision					->x()		,ui.lbDecision					->y()		-LayoutHeight);
		ui.lbCancel						->move	(ui.lbCancel					->x()		,ui.lbCancel					->y()		-LayoutHeight);
		ui.chSettingForHole				->move	(ui.chSettingForHole			->x()		,ui.chSettingForHole			->y()		-LayoutHeight);
		resize(width(),height()-LayoutHeight);
	}

	if(ui.gbDetailSettingForHole->isChecked()==false){
		ui.gbDetailSettingH				->resize(ui.gbDetailSettingH			->width()	,gbDetailSettingHH							-LayoutHeight);
		ui.gbDetailSettingForHole		->resize(ui.gbDetailSettingForHole		->width()	,gbDetailSettingForHoleH					-LayoutHeight);
		ui.chbIsCalcPixelInterPoration	->move	(ui.chbIsCalcPixelInterPoration	->x()		,ui.chbIsCalcPixelInterPoration	->y()		-LayoutHeight);
		ui.gbDetailSetting				->resize(ui.gbDetailSetting				->width()	,ui.gbDetailSetting				->height()	-LayoutHeight);
		ui.lbDecision					->move	(ui.lbDecision					->x()		,ui.lbDecision					->y()		-LayoutHeight);
		ui.lbCancel						->move	(ui.lbCancel					->x()		,ui.lbCancel					->y()		-LayoutHeight);
		resize(width(),height()-LayoutHeight);
	}

	//setUpdatesEnabled
	setUpdatesEnabled(true);
}

void	DetailSettingForm::SetEnabledForPad(bool checked)
{
	ui.lbStrongP		->setEnabled(checked);
	ui.hsNGThresholdP_B	->setEnabled(checked);
	ui.hsNGThresholdP_D	->setEnabled(checked);
	ui.lbWeakP_B		->setEnabled(checked);
	ui.lbWeakP_D		->setEnabled(checked);
	ui.dsbNGThresholdP_B->setEnabled(checked);
	ui.dsbNGThresholdP_D->setEnabled(checked);
	ui.diMinimumNGSizeP	->setEnabled(checked);
	ui.lbMinimumNGSizeP	->setEnabled(checked);
	ui.sbMinimumNGSizeP	->setEnabled(checked);
}

void	DetailSettingForm::SetEnabledForSilk(bool checked)
{
	ui.lbStrongS		->setEnabled(checked);
	ui.hsNGThresholdS_B	->setEnabled(checked);
	ui.hsNGThresholdS_D	->setEnabled(checked);
	ui.lbWeakS_B		->setEnabled(checked);
	ui.lbWeakS_D		->setEnabled(checked);
	ui.dsbNGThresholdS_B->setEnabled(checked);
	ui.dsbNGThresholdS_D->setEnabled(checked);
	ui.diMinimumNGSizeS	->setEnabled(checked);
	ui.lbMinimumNGSizeS	->setEnabled(checked);
	ui.sbMinimumNGSizeS	->setEnabled(checked);
}

void	DetailSettingForm::SetEnabledForResist(bool checked)
{
	ui.lbStrongR		->setEnabled(checked);
	ui.hsNGThresholdR_B	->setEnabled(checked);
	ui.hsNGThresholdR_D	->setEnabled(checked);
	ui.lbWeakR_B		->setEnabled(checked);
	ui.lbWeakR_D		->setEnabled(checked);
	ui.dsbNGThresholdR_B->setEnabled(checked);
	ui.dsbNGThresholdR_D->setEnabled(checked);
	ui.diMinimumNGSizeR	->setEnabled(checked);
	ui.lbMinimumNGSizeR	->setEnabled(checked);
	ui.sbMinimumNGSizeR	->setEnabled(checked);
}

void	DetailSettingForm::SetEnabledForHole(bool checked)
{
	ui.lbStrongH		->setEnabled(checked);
	ui.hsNGThresholdH_B	->setEnabled(checked);
	ui.hsNGThresholdH_D	->setEnabled(checked);
	ui.lbWeakH_B		->setEnabled(checked);
	ui.lbWeakH_D		->setEnabled(checked);
	ui.dsbNGThresholdH_B->setEnabled(checked);
	ui.dsbNGThresholdH_D->setEnabled(checked);
	ui.diMinimumNGSizeH	->setEnabled(checked);
	ui.lbMinimumNGSizeH	->setEnabled(checked);
	ui.sbMinimumNGSizeH	->setEnabled(checked);
}

void	DetailSettingForm::SearchThresholdFile(QString SearchDir,QStringList SearchStrs,QStringList &FilePathList)
{
	QStringList SList=QDir(SearchDir).entryList(SearchStrs,QDir::AllDirs | QDir::NoDotAndDotDot);
	for(int i=0;i<SList.count();i++){
		QString wSearchDir=SearchDir + QDir::separator() + SList.at(i);
		SearchThresholdFile(wSearchDir,SearchStrs,FilePathList);
	}
	QFileInfoList FIList=QDir(SearchDir).entryInfoList(SearchStrs);
	if(FIList.count()>0){
		FilePathList.append(FIList.at(0).filePath());
	}
}

bool	DetailSettingForm::CheckLoadParam()
{
	if(GetNGThresholdP_B()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdP_B){
		return false;
	}
	if(GetNGThresholdP_D()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdP_D){
		return false;
	}
	if(GetNGThresholdS_B()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_B){
		return false;
	}
	if(GetNGThresholdS_D()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdS_D){
		return false;
	}
	if(GetNGThresholdR_B()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_B){
		return false;
	}
	if(GetNGThresholdR_D()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdR_D){
		return false;
	}
	if(GetNGThresholdH_B()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_B){
		return false;
	}
	if(GetNGThresholdH_D()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdH_D){
		return false;
	}
	if(GetMinimumNGSizeP()!=((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeP){
		return false;
	}
	if(GetMinimumNGSizeS()!=((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeS){
		return false;
	}
	if(GetMinimumNGSizeR()!=((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeR){
		return false;
	}
	if(GetMinimumNGSizeH()!=((ButtonThreshold *)ParentWidget->GUIBase)->wMinimumNGSizeH){
		return false;
	}
	if(GetCheckPadIns()!=((ButtonThreshold *)ParentWidget->GUIBase)->wCheckPadIns){
		return false;
	}
	if(GetCheckSilkIns()!=((ButtonThreshold *)ParentWidget->GUIBase)->wCheckSilkIns){
		return false;
	}
	if(GetCheckResistIns()!=((ButtonThreshold *)ParentWidget->GUIBase)->wCheckResistIns){
		return false;
	}
	if(GetCheckHoleIns()!=((ButtonThreshold *)ParentWidget->GUIBase)->wCheckHoleIns){
		return false;
	}
	if(GetDonePadIns()!=((ButtonThreshold *)ParentWidget->GUIBase)->wDonePadIns){
		return false;
	}
	if(GetDoneSilkIns()!=((ButtonThreshold *)ParentWidget->GUIBase)->wDoneSilkIns){
		return false;
	}
	if(GetDoneResistIns()!=((ButtonThreshold *)ParentWidget->GUIBase)->wDoneResistIns){
		return false;
	}
	if(GetDoneHoleIns()!=((ButtonThreshold *)ParentWidget->GUIBase)->wDoneHoleIns){
		return false;
	}
	if(GetNGThresholdForPad_B()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForPad_B){
		return false;
	}
	if(GetNGThresholdForPad_D()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForPad_D){
		return false;
	}
	if(GetNGThresholdForSilk_B()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_B){
		return false;
	}
	if(GetNGThresholdForSilk_D()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForSilk_D){
		return false;
	}
	if(GetNGThresholdForResist_B()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_B){
		return false;
	}
	if(GetNGThresholdForResist_D()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForResist_D){
		return false;
	}
	if(GetNGThresholdForHole_B()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_B){
		return false;
	}
	if(GetNGThresholdForHole_D()!=((ButtonThreshold *)ParentWidget->GUIBase)->wNGThresholdForHole_D){
		return false;
	}
	if(GetIsCalcPixelInterPoration()!=((ButtonThreshold *)ParentWidget->GUIBase)->wIsCalcPixelInterPoration){
		return false;
	}
	return true;
}
