#include "DetailSettingForm.h"
#include "ButtonThreshold2.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QMessageBox>

DetailSettingForm::DetailSettingForm(QWidget *parent,GUIFormBase *Base,PixelInspectionBase *PBase)
	: QDialog(parent),LayoutHeight(75)//101->26
{
	ui.setupUi(this);

	ParentWidget=(ThresholdSettingForm *)parent;
	GUIBase		=Base;
	PixelBase	=PBase;

	for(int i=0;i<PLibNumb;i++){
		PLibLevelList[0]==NULL;
	}

	//connect
	connect(ui.hsNGThresholdP	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdPValueChanged(int)));
	connect(ui.dsbNGThresholdP	,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdPValueChanged(double)));
	connect(ui.hsNGThresholdS	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdSValueChanged(int)));
	connect(ui.dsbNGThresholdS	,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdSValueChanged(double)));
	connect(ui.hsNGThresholdR	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdRValueChanged(int)));
	connect(ui.dsbNGThresholdR	,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdRValueChanged(double)));
	connect(ui.hsNGThresholdH	,SIGNAL(valueChanged(int))	 ,this,SLOT(hsNGThresholdHValueChanged(int)));
	connect(ui.dsbNGThresholdH	,SIGNAL(valueChanged(double)),this,SLOT(dsbNGThresholdHValueChanged(double)));
	connect(ui.diMinimumNGSizeP	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizePValueChanged(int)));
	connect(ui.sbMinimumNGSizeP	,SIGNAL(valueChanged(int))	 ,ui.diMinimumNGSizeP,SLOT(setValue(int)));
	connect(ui.diMinimumNGSizeS	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeSValueChanged(int)));
	connect(ui.sbMinimumNGSizeS	,SIGNAL(valueChanged(int))	 ,ui.diMinimumNGSizeS,SLOT(setValue(int)));
	connect(ui.diMinimumNGSizeR	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeRValueChanged(int)));
	connect(ui.sbMinimumNGSizeR	,SIGNAL(valueChanged(int))	 ,ui.diMinimumNGSizeR,SLOT(setValue(int)));
	connect(ui.diMinimumNGSizeH	,SIGNAL(valueChanged(int))	 ,this,SLOT(diMinimumNGSizeHValueChanged(int)));
	connect(ui.sbMinimumNGSizeH	,SIGNAL(valueChanged(int))	 ,ui.diMinimumNGSizeH,SLOT(setValue(int)));

	connect(ui.hsNGThresholdForPad		,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForPadValueChanged(int)));
	connect(ui.sbNGThresholdForPad		,SIGNAL(valueChanged(int)),ui.hsNGThresholdForPad		,SLOT(setValue(int)));
	connect(ui.diMinimumNGSizeForPad	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForPadValueChanged(int)));
	connect(ui.sbMinimumNGSizeForPad	,SIGNAL(valueChanged(int)),ui.diMinimumNGSizeForPad		,SLOT(setValue(int)));
	connect(ui.hsNGThresholdForSilk		,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForSilkValueChanged(int)));
	connect(ui.sbNGThresholdForSilk		,SIGNAL(valueChanged(int)),ui.hsNGThresholdForSilk		,SLOT(setValue(int)));
	connect(ui.diMinimumNGSizeForSilk	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForSilkValueChanged(int)));
	connect(ui.sbMinimumNGSizeForSilk	,SIGNAL(valueChanged(int)),ui.diMinimumNGSizeForSilk	,SLOT(setValue(int)));
	connect(ui.hsNGThresholdForResist	,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForResistValueChanged(int)));
	connect(ui.sbNGThresholdForResist	,SIGNAL(valueChanged(int)),ui.hsNGThresholdForResist	,SLOT(setValue(int)));
	connect(ui.diMinimumNGSizeForResist ,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForResistValueChanged(int)));
	connect(ui.sbMinimumNGSizeForResist ,SIGNAL(valueChanged(int)),ui.diMinimumNGSizeForResist	,SLOT(setValue(int)));
	connect(ui.hsNGThresholdForHole		,SIGNAL(valueChanged(int)),this,SLOT(hsNGThresholdForHoleValueChanged(int)));
	connect(ui.sbNGThresholdForHole		,SIGNAL(valueChanged(int)),ui.hsNGThresholdForHole		,SLOT(setValue(int)));
	connect(ui.diMinimumNGSizeForHole	,SIGNAL(valueChanged(int)),this,SLOT(diMinimumNGSizeForHoleValueChanged(int)));
	connect(ui.sbMinimumNGSizeForHole	,SIGNAL(valueChanged(int)),ui.diMinimumNGSizeForHole	,SLOT(setValue(int)));

	connect(ui.chSettingForPad		,SIGNAL(toggled(bool)),this,SLOT(chSettingForPadToggled(bool)));
	connect(ui.chSettingForSilk		,SIGNAL(toggled(bool)),this,SLOT(chSettingForSilkToggled(bool)));
	connect(ui.chSettingForResist	,SIGNAL(toggled(bool)),this,SLOT(chSettingForResistToggled(bool)));
	connect(ui.chSettingForHole		,SIGNAL(toggled(bool)),this,SLOT(chSettingForHoleToggled(bool)));

	//Initial	
	InspectionLevel			=PixelBase->getInspectionLevel();
	Colored					=PixelBase->getColored();
	DefaultLibraryID		=PixelBase->getDefaultLibraryID();
	BrightnessRange			=PixelBase->getBrightnessRange();

	InitialSetting();

	InitialMultiAlgorithmSupport	=false;
	PixelAlgorithmBasePointer		=NULL;
	PixelAlgorithmInPageRootPointer	=NULL;

	//PixelLibrarySetting.datを読み込む
	if(LoadPixelLibrarySetting()==true){
		if(CheckSettingData()==true){
			if(ExecMultiAlgorithmSupport()==true){
///				IsMultiAlgorithmSupport=true;
			}
		}
	}
	else{
		QMessageBox::warning(NULL,"Warning","Not loaded PixelLibrarySetting file.",QMessageBox::Ok,QMessageBox::Ok);
	}

	//レイアウト
	gbDetailSettingPY					=ui.gbDetailSettingP					->y();
	gbDetailSettingPH					=ui.gbDetailSettingP					->height();
	gbDetailSettingSY					=ui.gbDetailSettingS					->y();
	gbDetailSettingSH					=ui.gbDetailSettingS					->height();
	gbDetailSettingRY					=ui.gbDetailSettingR					->y();
	gbDetailSettingRH					=ui.gbDetailSettingR					->height();
	gbDetailSettingHY					=ui.gbDetailSettingH					->y();
	gbDetailSettingHH					=ui.gbDetailSettingH					->height();
	gbDetailSettingForPadY				=ui.gbDetailSettingForPad				->y();
	gbDetailSettingForPadH				=ui.gbDetailSettingForPad				->height();
	gbDetailSettingForSilkY				=ui.gbDetailSettingForSilk				->y();
	gbDetailSettingForSilkH				=ui.gbDetailSettingForSilk				->height();
	gbDetailSettingForResistY			=ui.gbDetailSettingForResist			->y();
	gbDetailSettingForResistH			=ui.gbDetailSettingForResist			->height();
	gbDetailSettingForHoleY				=ui.gbDetailSettingForHole				->y();
	gbDetailSettingForHoleH				=ui.gbDetailSettingForHole				->height();
	chbIsCalcPixelInterPorationPadY		=ui.chbIsCalcPixelInterPorationPad		->y();
	chbIsCalcPixelInterPorationSilkY	=ui.chbIsCalcPixelInterPorationSilk		->y();
	chbIsCalcPixelInterPorationResistY	=ui.chbIsCalcPixelInterPorationResist	->y();
	chbIsCalcPixelInterPorationHoleY	=ui.chbIsCalcPixelInterPorationHole		->y();
	gbDetailSettingY					=ui.gbDetailSetting						->y();
	gbDetailSettingH					=ui.gbDetailSetting						->height();
	lbDecisionY							=ui.lbDecision							->y();
	lbCancelY							=ui.lbCancel							->y();
///	chSettingForPadY					=ui.chSettingForPad						->y();
	chSettingForSilkY					=ui.chSettingForSilk					->y();
	chSettingForResistY					=ui.chSettingForResist					->y();
	chSettingForHoleY					=ui.chSettingForHole					->y();
	H									=height();
	SetLayout();

	//ボタン
	QImage DecisionImage(ParentWidget->DecisionImageBmpFile[((ButtonThreshold2 *)GUIBase)->LanguageCode]);
	BtnDecision=new mtImageToolButton(ui.lbDecision,false);
	BtnDecision->setImageBmp(DecisionImage);
	BtnDecision->setIconSize(QSize(DecisionImage.width(),DecisionImage.height()));
	connect(BtnDecision,SIGNAL(SignalClicked()),this,SLOT(SlotBtnDecisionClicked()));

	QImage CancelImage(ParentWidget->CancelImageBmpFile[((ButtonThreshold2 *)GUIBase)->LanguageCode]);
	BtnCancel=new mtImageToolButton(ui.lbCancel,false);
	BtnCancel->setImageBmp(CancelImage);
	BtnCancel->setIconSize(QSize(CancelImage.width(),CancelImage.height()));
	connect(BtnCancel,SIGNAL(SignalClicked()),this,SLOT(SlotBtnCancelClicked()));

	connect(ui.gbDetailSettingForPad	,SIGNAL(toggled(bool)),this,SLOT(gbDetailSettingForPadToggled(bool)));
	connect(ui.gbDetailSettingForSilk	,SIGNAL(toggled(bool)),this,SLOT(gbDetailSettingForSilkToggled(bool)));
	connect(ui.gbDetailSettingForResist	,SIGNAL(toggled(bool)),this,SLOT(gbDetailSettingForResistToggled(bool)));
	connect(ui.gbDetailSettingForHole	,SIGNAL(toggled(bool)),this,SLOT(gbDetailSettingForHoleToggled(bool)));

	connect(ui.pbSaveInsParam	,SIGNAL(clicked()),this,SLOT(pbSaveInsParamClicked()));
	connect(ui.pbLoadInsParam	,SIGNAL(clicked()),this,SLOT(pbLoadInsParamClicked()));

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
///	LangSolver.SetUI(this);
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
void DetailSettingForm::hsNGThresholdPValueChanged(int Value)
{
	ui.dsbNGThresholdP->setValue(Value/10.0);
}

void DetailSettingForm::dsbNGThresholdPValueChanged(double Value)
{
	ui.hsNGThresholdP->setValue(Value*10);
}

void DetailSettingForm::hsNGThresholdSValueChanged(int Value)
{
	ui.dsbNGThresholdS->setValue(Value/10.0);
}

void DetailSettingForm::dsbNGThresholdSValueChanged(double Value)
{
	ui.hsNGThresholdS->setValue(Value*10);
}

void DetailSettingForm::hsNGThresholdRValueChanged(int Value)
{
	ui.dsbNGThresholdR->setValue(Value/10.0);
}

void DetailSettingForm::dsbNGThresholdRValueChanged(double Value)
{
	ui.hsNGThresholdR->setValue(Value*10);
}

void DetailSettingForm::hsNGThresholdHValueChanged(int Value)
{
	ui.dsbNGThresholdH->setValue(Value/10.0);
}

void DetailSettingForm::dsbNGThresholdHValueChanged(double Value)
{
	ui.hsNGThresholdH->setValue(Value*10);
}

void DetailSettingForm::diMinimumNGSizePValueChanged(int Value)
{
	ui.sbMinimumNGSizeP->setValue(Value);
}

void DetailSettingForm::diMinimumNGSizeSValueChanged(int Value)
{
	ui.sbMinimumNGSizeS->setValue(Value);
}

void DetailSettingForm::diMinimumNGSizeRValueChanged(int Value)
{
	ui.sbMinimumNGSizeR->setValue(Value);
}

void DetailSettingForm::diMinimumNGSizeHValueChanged(int Value)
{
	ui.sbMinimumNGSizeH->setValue(Value);
}

void DetailSettingForm::hsNGThresholdForPadValueChanged(int Value)
{
	ui.sbNGThresholdForPad->setValue(Value);
}

void DetailSettingForm::diMinimumNGSizeForPadValueChanged(int Value)
{
	ui.sbMinimumNGSizeForPad->setValue(Value);
}

void DetailSettingForm::hsNGThresholdForSilkValueChanged(int Value)
{
	ui.sbNGThresholdForSilk->setValue(Value);
}

void DetailSettingForm::diMinimumNGSizeForSilkValueChanged(int Value)
{
	ui.sbMinimumNGSizeForSilk->setValue(Value);
}

void DetailSettingForm::hsNGThresholdForResistValueChanged(int Value)
{
	ui.sbNGThresholdForResist->setValue(Value);
}

void DetailSettingForm::diMinimumNGSizeForResistValueChanged(int Value)
{
	ui.sbMinimumNGSizeForResist->setValue(Value);
}

void DetailSettingForm::hsNGThresholdForHoleValueChanged(int Value)
{
	ui.sbNGThresholdForHole->setValue(Value);
}

void DetailSettingForm::diMinimumNGSizeForHoleValueChanged(int Value)
{
	ui.sbMinimumNGSizeForHole->setValue(Value);
}

void DetailSettingForm::pbSaveInsParamClicked()
{
	//検査パラメータの保存
	QString InsParamFilePath=QFileDialog::getSaveFileName(
							this,"Please save a Inspection setting parameter file.",/**/"PixelParameter.dat",/**/"Inspection setting parameter file (*.dat)");
	if(InsParamFilePath.isEmpty()){
		return;
	}
	QFile	File(InsParamFilePath);
	if(File.open(QIODevice::WriteOnly)==true){
		QTextStream mystream(&File);

		mystream << /**/"InspectionLevel               :" << QString::number(ParentWidget							->GetInspectionLevel())		<< endl;
		mystream << /**/"Colored                       :" << QString::number(PixelBase								->getColored())					<< endl;
		mystream << /**/"DefaultLibraryID              :" << QString::number(PixelBase								->getDefaultLibraryID())			<< endl;
		mystream << /**/"BrightnessRange               :" << QString::number(PixelBase								->getBrightnessRange())			<< endl;
		mystream << /**/"CheckPadIns                   :" << QString::number(ui.chSettingForPad						->isChecked())				<< endl;
		mystream << /**/"NGThresholdP                  :" << QString::number(ui.dsbNGThresholdP						->value())					<< endl;
		mystream << /**/"MinimumNGSizeP                :" << QString::number(ui.sbMinimumNGSizeP					->value())					<< endl;
		mystream <<	/**/"DonePadIns                    :" << QString::number(ui.gbDetailSettingForPad				->isChecked())				<< endl;
		mystream << /**/"NGThresholdForPad             :" << QString::number(ui.sbNGThresholdForPad					->value())					<< endl;
		mystream << /**/"MinimumNGSizeForPad           :" << QString::number(ui.sbMinimumNGSizeForPad				->value())					<< endl;
		mystream << /**/"IsCalcPixelInterPorationPad   :" << QString::number(ui.chbIsCalcPixelInterPorationPad		->isChecked())				<< endl;
		mystream << /**/"CheckSilkIns                  :" << QString::number(ui.chSettingForSilk					->isChecked())				<< endl;
		mystream << /**/"NGThresholdS                  :" << QString::number(ui.dsbNGThresholdS						->value())					<< endl;
		mystream << /**/"MinimumNGSizeS                :" << QString::number(ui.sbMinimumNGSizeS					->value())					<< endl;
		mystream << /**/"DoneSilkIns                   :" << QString::number(ui.gbDetailSettingForSilk				->isChecked())				<< endl;
		mystream << /**/"NGThresholdForSilk            :" << QString::number(ui.sbNGThresholdForSilk				->value())					<< endl;
		mystream << /**/"MinimumNGSizeForSilk          :" << QString::number(ui.sbMinimumNGSizeForSilk				->value())					<< endl;
		mystream << /**/"IsCalcPixelInterPorationSilk  :" << QString::number(ui.chbIsCalcPixelInterPorationSilk		->isChecked())				<< endl;
		mystream << /**/"CheckResistIns                :" << QString::number(ui.chSettingForResist					->isChecked())				<< endl;
		mystream << /**/"NGThresholdR                  :" << QString::number(ui.dsbNGThresholdR						->value())					<< endl;
		mystream << /**/"MinimumNGSizeR                :" << QString::number(ui.sbMinimumNGSizeR					->value())					<< endl;
		mystream << /**/"DoneResistIns                 :" << QString::number(ui.gbDetailSettingForResist			->isChecked())				<< endl;
		mystream << /**/"NGThresholdForResist          :" << QString::number(ui.sbNGThresholdForResist				->value())					<< endl;
		mystream << /**/"MinimumNGSizeForResist        :" << QString::number(ui.sbMinimumNGSizeForResist			->value())					<< endl;
		mystream << /**/"IsCalcPixelInterPorationResist:" << QString::number(ui.chbIsCalcPixelInterPorationResist	->isChecked())				<< endl;
		mystream << /**/"CheckHoleIns                  :" << QString::number(ui.chSettingForHole					->isChecked())				<< endl;
		mystream << /**/"NGThresholdH                  :" << QString::number(ui.dsbNGThresholdH						->value())					<< endl;
		mystream << /**/"MinimumNGSizeH                :" << QString::number(ui.sbMinimumNGSizeH					->value())					<< endl;
		mystream << /**/"DoneHoleIns                   :" << QString::number(ui.gbDetailSettingForHole				->isChecked())				<< endl;
		mystream << /**/"NGThresholdForHole            :" << QString::number(ui.sbNGThresholdForHole				->value())					<< endl;
		mystream << /**/"MinimumNGSizeForHole          :" << QString::number(ui.sbMinimumNGSizeForHole				->value())					<< endl;
		mystream << /**/"IsCalcPixelInterPorationHole  :" << QString::number(ui.chbIsCalcPixelInterPorationHole		->isChecked())				<< endl;

		File.close();
	}
}

void DetailSettingForm::pbLoadInsParamClicked()
{
	//検査パラメータの読込
	QString InsParamFilePath=QFileDialog::getOpenFileName(
							this,"Please choose a Inspection setting parameter file.",/**/"",/**/"Inspection setting parameter file (*.dat)");
	if(InsParamFilePath.isEmpty()){
		return;
	}
	QFile	File(InsParamFilePath);
	if(File.open(QIODevice::ReadOnly)==true){
		QTextStream mystream(&File);

		QString myString;
		while (!mystream.atEnd()){
			myString=mystream.readLine();
			int SplitIndex=myString.indexOf(/**/":");
			QString Param=myString.mid(SplitIndex+1);
			QString ParamName=myString.left(SplitIndex).remove(' ');
			if(ParamName==/**/"InspectionLevel"){
				InspectionLevel=Param.toInt();
			}
			else if(ParamName==/**/"Colored"){
				Colored=Param.toInt();
			}
			else if(ParamName==/**/"DefaultLibraryID"){
				DefaultLibraryID=Param.toInt();
			}
			else if(ParamName==/**/"BrightnessRange"){
				BrightnessRange=Param.toInt();
			}
			else if(ParamName==/**/"CheckPadIns"){
				CheckPadIns=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdP"){
				NGThresholdP=Param.toDouble();
			}
			else if(ParamName==/**/"MinimumNGSizeP"){
				MinimumNGSizeP=Param.toInt();
			}
			else if(ParamName==/**/"DonePadIns"){
				DonePadIns=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdForPad"){
				NGThresholdForPad=Param.toInt();
			}
			else if(ParamName==/**/"MinimumNGSizeForPad"){
				MinimumNGSizeForPad=Param.toInt();
			}
			else if(ParamName==/**/"IsCalcPixelInterPorationPad"){
				IsCalcPixelInterPorationPad=Param.toInt();
			}
			else if(ParamName==/**/"CheckSilkIns"){
				CheckSilkIns=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdS"){
				NGThresholdS=Param.toDouble();
			}
			else if(ParamName==/**/"MinimumNGSizeS"){
				MinimumNGSizeS=Param.toInt();
			}
			else if(ParamName==/**/"DoneSilkIns"){
				DoneSilkIns=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdForSilk"){
				NGThresholdForSilk=Param.toInt();
			}
			else if(ParamName==/**/"MinimumNGSizeForSilk"){
				MinimumNGSizeForSilk=Param.toInt();
			}
			else if(ParamName==/**/"IsCalcPixelInterPorationSilk"){
				IsCalcPixelInterPorationSilk=Param.toInt();
			}
			else if(ParamName==/**/"CheckResistIns"){
				CheckResistIns=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdR"){
				NGThresholdR=Param.toDouble();
			}
			else if(ParamName==/**/"MinimumNGSizeR"){
				MinimumNGSizeR=Param.toInt();
			}
			else if(ParamName==/**/"DoneResistIns"){
				DoneResistIns=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdForResist"){
				NGThresholdForResist=Param.toInt();
			}
			else if(ParamName==/**/"MinimumNGSizeForResist"){
				MinimumNGSizeForResist=Param.toInt();
			}
			else if(ParamName==/**/"IsCalcPixelInterPorationResist"){
				IsCalcPixelInterPorationResist=Param.toInt();
			}
			else if(ParamName==/**/"CheckHoleIns"){
				CheckHoleIns=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdH"){
				NGThresholdH=Param.toDouble();
			}
			else if(ParamName==/**/"MinimumNGSizeH"){
				MinimumNGSizeH=Param.toInt();
			}
			else if(ParamName==/**/"DoneHoleIns"){
				DoneHoleIns=Param.toInt();
			}
			else if(ParamName==/**/"NGThresholdForHole"){
				NGThresholdForHole=Param.toInt();
			}
			else if(ParamName==/**/"MinimumNGSizeForHole"){
				MinimumNGSizeForHole=Param.toInt();
			}
			else if(ParamName==/**/"IsCalcPixelInterPorationHole"){
				IsCalcPixelInterPorationHole=Param.toInt();
			}
		}
		File.close();

		//画面設定
		ParentWidget->SetImageSlider(InspectionLevel);
		ui.dsbNGThresholdP					->setValue	(NGThresholdP);
		ui.dsbNGThresholdS					->setValue	(NGThresholdS);
		ui.dsbNGThresholdR					->setValue	(NGThresholdR);
		ui.dsbNGThresholdH					->setValue	(NGThresholdH);
		ui.sbMinimumNGSizeP					->setValue	(MinimumNGSizeP);
		ui.sbMinimumNGSizeS					->setValue	(MinimumNGSizeS);
		ui.sbMinimumNGSizeR					->setValue	(MinimumNGSizeR);
		ui.sbMinimumNGSizeH					->setValue	(MinimumNGSizeH);
		ui.chSettingForPad					->setChecked(CheckPadIns);
		ui.chSettingForSilk					->setChecked(CheckSilkIns);
		ui.chSettingForResist				->setChecked(CheckResistIns);
		ui.chSettingForHole					->setChecked(CheckHoleIns);
		ui.gbDetailSettingForPad			->setChecked(DonePadIns);
		ui.gbDetailSettingForSilk			->setChecked(DoneSilkIns);
		ui.gbDetailSettingForResist			->setChecked(DoneResistIns);
		ui.gbDetailSettingForHole			->setChecked(DoneHoleIns);
		ui.sbNGThresholdForPad				->setValue	(NGThresholdForPad);
		ui.sbMinimumNGSizeForPad			->setValue	(MinimumNGSizeForPad);
		ui.sbNGThresholdForSilk				->setValue	(NGThresholdForSilk);
		ui.sbMinimumNGSizeForSilk			->setValue	(MinimumNGSizeForSilk);
		ui.sbNGThresholdForResist			->setValue	(NGThresholdForResist);
		ui.sbMinimumNGSizeForResist			->setValue	(MinimumNGSizeForResist);
		ui.sbNGThresholdForHole				->setValue	(NGThresholdForHole);
		ui.sbMinimumNGSizeForHole			->setValue	(MinimumNGSizeForHole);
		ui.chbIsCalcPixelInterPorationPad	->setChecked(IsCalcPixelInterPorationPad);
		ui.chbIsCalcPixelInterPorationSilk	->setChecked(IsCalcPixelInterPorationSilk);
		ui.chbIsCalcPixelInterPorationResist->setChecked(IsCalcPixelInterPorationResist);
		ui.chbIsCalcPixelInterPorationHole	->setChecked(IsCalcPixelInterPorationHole);
	}
}

void DetailSettingForm::SlotBtnDecisionClicked()
{
	//設定値が何も変わっていない場合はそのまま抜ける
	if(CheckIsEdit()==false){
		reject();
		return;
	}

	NGThresholdP					=ui.dsbNGThresholdP						->value();
	NGThresholdS					=ui.dsbNGThresholdS						->value();
	NGThresholdR					=ui.dsbNGThresholdR						->value();
	NGThresholdH					=ui.dsbNGThresholdH						->value();
	MinimumNGSizeP					=ui.sbMinimumNGSizeP					->value();
	MinimumNGSizeS					=ui.sbMinimumNGSizeS					->value();
	MinimumNGSizeR					=ui.sbMinimumNGSizeR					->value();
	MinimumNGSizeH					=ui.sbMinimumNGSizeH					->value();
	CheckPadIns						=ui.chSettingForPad						->isChecked();
	CheckSilkIns					=ui.chSettingForSilk					->isChecked();
	CheckResistIns					=ui.chSettingForResist					->isChecked();
	CheckHoleIns					=ui.chSettingForHole					->isChecked();
	DonePadIns						=ui.gbDetailSettingForPad				->isChecked();
	DoneSilkIns						=ui.gbDetailSettingForSilk				->isChecked();
	DoneResistIns					=ui.gbDetailSettingForResist			->isChecked();
	DoneHoleIns						=ui.gbDetailSettingForHole				->isChecked();
	NGThresholdForPad				=ui.sbNGThresholdForPad					->value();
	MinimumNGSizeForPad				=ui.sbMinimumNGSizeForPad				->value();
	NGThresholdForSilk				=ui.sbNGThresholdForSilk				->value();
	MinimumNGSizeForSilk			=ui.sbMinimumNGSizeForSilk				->value();
	NGThresholdForResist			=ui.sbNGThresholdForResist				->value();
	MinimumNGSizeForResist			=ui.sbMinimumNGSizeForResist			->value();
	NGThresholdForHole				=ui.sbNGThresholdForHole				->value();
	MinimumNGSizeForHole			=ui.sbMinimumNGSizeForHole				->value();
	IsCalcPixelInterPorationPad		=ui.chbIsCalcPixelInterPorationPad		->isChecked();
	IsCalcPixelInterPorationSilk	=ui.chbIsCalcPixelInterPorationSilk		->isChecked();
	IsCalcPixelInterPorationResist	=ui.chbIsCalcPixelInterPorationResist	->isChecked();
	IsCalcPixelInterPorationHole	=ui.chbIsCalcPixelInterPorationHole		->isChecked();

	for(int i=0;i<PLibNumb;i++){
		if(PLibLevelList[i]==NULL){
			continue;
		}
		PixelInspectionLibrary	*PLibList=(PixelInspectionLibrary *)PLibLevelList[i]->GetLibrary();

		PLibList->DetailSettingNarrow		=chSetting[i]					->isChecked();
		PLibList->RelativeNGThresholdNarrow	=dsbNGThreshold[i]				->value();
		PLibList->NGSizeNarrow				=sbMinimumNGSize[i]				->value();
		PLibList->DetailSettingBroad		=gbDetailSetting[i]				->isChecked();
		PLibList->AbsoluteNGThresholdBroad	=sbNGThreshold[i]				->value();
		PLibList->NGSizeBroad				=sbDetailMinimumNGSize[i]		->value();
		PLibList->IsCalcPixelInterPoration	=chbIsCalcPixelInterPoration[i]	->isChecked();

		//ライブラリの中身をデータベースに保存
		//ライブラリの上書保存コードが無くても仮想関数で上書保存できる
		PixelAlgorithmBasePointer->GetLibraryContainer()->Update(*PLibLevelList[i]);
	}

	//しきい値再設定処理を実行
	CmdReqCalcThresholdPacket	CmdReqCalcThr(GUIBase->GetLayersBase());
	PixelAlgorithmBasePointer->TransmitDirectly(&CmdReqCalcThr);

	accept();
}

void DetailSettingForm::SlotBtnCancelClicked()
{
	reject();
}

struct	PixelLibrarySettingString
{
	QString	StringReadLine;
	uint	Priority;
};

int	PLibFunc(const void *a ,const void *b)
{
	if(((struct PixelLibrarySettingString *)a)->Priority<((struct PixelLibrarySettingString *)b)->Priority){
		return -1;
	}
	if(((struct PixelLibrarySettingString *)a)->Priority>((struct PixelLibrarySettingString *)b)->Priority){
		return 1;
	}
	return 0;
}

struct	AutoAlignmentLibraryStruct
{
	AutoAlignmentLibrary	*AutoAlignmentLibraryPointer;
	int						Priority;
};

int	AALibFunc(const void *a ,const void *b)
{
	if(((struct AutoAlignmentLibraryStruct *)a)->Priority<((struct AutoAlignmentLibraryStruct *)b)->Priority){
		return -1;
	}
	if(((struct AutoAlignmentLibraryStruct *)a)->Priority>((struct AutoAlignmentLibraryStruct *)b)->Priority){
		return 1;
	}
	return 0;
}

void DetailSettingForm::InitialSetting()
{
	chSetting[0]	=ui.chSettingForPad;
	chSetting[1]	=ui.chSettingForSilk;
	chSetting[2]	=ui.chSettingForResist;
	chSetting[3]	=ui.chSettingForHole;

	dsbNGThreshold[0]	=ui.dsbNGThresholdP;
	dsbNGThreshold[1]	=ui.dsbNGThresholdS;
	dsbNGThreshold[2]	=ui.dsbNGThresholdR;
	dsbNGThreshold[3]	=ui.dsbNGThresholdH;

	sbMinimumNGSize[0]	=ui.sbMinimumNGSizeP;
	sbMinimumNGSize[1]	=ui.sbMinimumNGSizeS;
	sbMinimumNGSize[2]	=ui.sbMinimumNGSizeR;
	sbMinimumNGSize[3]	=ui.sbMinimumNGSizeH;

	gbDetailSetting[0]	=ui.gbDetailSettingForPad;
	gbDetailSetting[1]	=ui.gbDetailSettingForSilk;
	gbDetailSetting[2]	=ui.gbDetailSettingForResist;
	gbDetailSetting[3]	=ui.gbDetailSettingForHole;

	sbNGThreshold[0]	=ui.sbNGThresholdForPad;
	sbNGThreshold[1]	=ui.sbNGThresholdForSilk;
	sbNGThreshold[2]	=ui.sbNGThresholdForResist;
	sbNGThreshold[3]	=ui.sbNGThresholdForHole;

	sbDetailMinimumNGSize[0]	=ui.sbMinimumNGSizeForPad;
	sbDetailMinimumNGSize[1]	=ui.sbMinimumNGSizeForSilk;
	sbDetailMinimumNGSize[2]	=ui.sbMinimumNGSizeForResist; 
	sbDetailMinimumNGSize[3]	=ui.sbMinimumNGSizeForHole;

	chbIsCalcPixelInterPoration[0]	=ui.chbIsCalcPixelInterPorationPad;
	chbIsCalcPixelInterPoration[1]	=ui.chbIsCalcPixelInterPorationSilk;
	chbIsCalcPixelInterPoration[2]	=ui.chbIsCalcPixelInterPorationResist;
	chbIsCalcPixelInterPoration[3]	=ui.chbIsCalcPixelInterPorationHole;
}

bool DetailSettingForm::LoadPixelLibrarySetting()
{
	//PixelLibrarySettingString
	struct PixelLibrarySettingString PLibInStack[10];
	struct PixelLibrarySettingString *PLib=PLibInStack;

	//PixelLibrarySetting.datの読み込み
	int	PLibNumb=0;
///	QString FileName=/**/"./PixelLibrarySetting.dat";	//仮
	QString FileName=((ButtonThreshold2 *)GUIBase)->GetPixelLibSettingFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==false){
		return false;
	}
	QTextStream mystream(&File);
	QString myString;
	QStringList myStringList;
	while (!mystream.atEnd()){
		myString	=mystream.readLine();
		myStringList=myString.split(',');
		PLib[PLibNumb].StringReadLine	=myString;
		PLib[PLibNumb].Priority			=myStringList.last().toInt();
		PLibNumb++;
	}
	File.close();
	QSort(PLib,PLibNumb,sizeof(PLib[0]),PLibFunc);

	for(int i=0;i<PLibNumb;i++){
		PLibSettingStringList.append(PLib[i].StringReadLine);
	}

	return true;
}

bool DetailSettingForm::CheckSettingData()
{
	LoadAlgorithmData();

	int PLibNumb=PLibSettingStringList.count();
	for(int i=0;i<PLibNumb;i++){
		QString Msg;
		QStringList myStringList=PLibSettingStringList.at(i).split(',');
		if(CheckPixelLibrarySettingData(myStringList,Msg)==false){
			QMessageBox::StandardButton Btn=QMessageBox::warning(NULL,"Warning",Msg,QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel);
			if(Btn==QMessageBox::Cancel){
				return false;
			}
			else{
				continue;
			}
		}
	}
	return true;
}

bool DetailSettingForm::LoadAlgorithmData()
{
	//AlgorithmListNameとPixelLibraryの取得
	AlgorithmListName.clear();
	PixelLibraryIDList.clear();
	PixelLibraryNameList.clear();
	AlgorithmListName.append(/**/"");
	PixelLibraryIDList.append(/**/"");
	PixelLibraryNameList.append(/**/"");
	for(LogicDLL *L=GUIBase->GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLName()==/**/"PixelInspection"){
			AlgorithmLibraryContainer	*PixelAL=L->GetInstance()->GetLibraryContainer();
			if(PixelAL!=NULL){
				PixelAL->EnumLibrary(L->GetInstance()->GetLibType(),PixelAList);
				for(AlgorithmLibraryList *p=PixelAList.GetFirst();p!=NULL;p=p->GetNext()){
					PixelLibraryIDList.append(QString::number(p->GetLibID()));
					PixelLibraryNameList.append(p->GetLibName());
				}
			}
			PixelAlgorithmBasePointer=GUIBase->GetLayersBase()->GetAlgorithmBase(L->GetDLLRoot(),L->GetDLLName());
			if(PixelAlgorithmBasePointer==NULL){
				//AlgorithmBaseなし
				return false;
			}
			PixelAlgorithmInPageRootPointer=PixelAlgorithmBasePointer->GetPageData(0);
			if(PixelAlgorithmInPageRootPointer==NULL){
				//AlgorithmInPageRootなし
				return false;
			}
		}
		AlgorithmListName.append(L->GetDLLName());
	}
	return true;
}

bool DetailSettingForm::CheckPixelLibrarySettingData(const QStringList &myStringList,QString &Msg)
{
	int Cnt;
	if((Cnt=myStringList.count())<7){
		return false;
	}

	int iCnt=0;
	int i;
	for(i=0;i<PixelLibraryIDList.count();i++){
		if(myStringList.at(iCnt)==PixelLibraryIDList.at(i)){
			break;
		}
	}
	iCnt++;
	if(i==PixelLibraryIDList.count()){
		Msg+="Not found PixelLibrary ID.\n";
	}
	else{
		if(myStringList.at(iCnt)!=PixelLibraryNameList.at(i)){
			Msg+="Not found PixelLibrary Name.\n";
		}
	}
	iCnt++;
	for(i=0;i<AlgorithmListName.count();i++){
		if(myStringList.at(iCnt)==AlgorithmListName.at(i)){
			break;
		}
	}
	iCnt++;
	if(i==AlgorithmListName.count()){
		Msg+="Not found Algorithm Name.\n";
	}
	else{
		//Libraryの取得
		CreateLibraryNameList(AlgorithmListName.at(i));
		for(i=0;i<LibraryIDList.count();i++){
			if(myStringList.at(iCnt)==LibraryIDList.at(i)){
				break;
			}
		}
		iCnt++;
		if(i==LibraryIDList.count()){
			Msg+="Not found Library ID.\n";
		}
		else{
			if(myStringList.at(iCnt)!=LibraryNameList.at(i)){
				Msg+="Not found Library Name.\n";
			}
		}
		iCnt++;
		//UniqueID
		iCnt++;
		//Unique
		iCnt++;
	}
	bool IsOK;
	myStringList.at(iCnt).toInt(&IsOK);
	if(IsOK==false){
		Msg+="Not correct Priority.\n";
	}

	return Msg.isEmpty();
}

bool DetailSettingForm::CreateLibraryNameList(const QString AlgorithmName)
{
	LibraryIDList.clear();
	LibraryNameList.clear();
	LibraryIDList.append(/**/"");
	LibraryNameList.append(/**/"");
	for(LogicDLL *L=GUIBase->GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLName()==AlgorithmName){
			AlgorithmLibraryContainer  *AL=L->GetInstance()->GetLibraryContainer();
			if(AL!=NULL){
				AlgorithmLibraryListContainer	AList;
				AL->EnumLibrary(L->GetInstance()->GetLibType(),AList);
				for(AlgorithmLibraryList *p=AList.GetFirst();p!=NULL;p=p->GetNext()){
					LibraryIDList.append(QString::number(p->GetLibID()));
					LibraryNameList.append(p->GetLibName());
				}
				if(L->GetDLLName()==/**/"AutoAlignment"){
					AAlignAList=AList;
				}
				return true;
			}
		}
	}
	return false;
}

//それぞれの領域で閾値を作成する
bool DetailSettingForm::ExecMultiAlgorithmSupport()
{
	int PLibNumb=PLibSettingStringList.count();
	for(int i=0;i<PLibNumb;i++){
		QString Msg;
		QStringList myStringList=PLibSettingStringList.at(i).split(',');
		if(CalcMultiAlgorithmSupport(myStringList.at(0).toInt(),myStringList.at(2),myStringList.at(3).toInt(),Msg)==false){
			QMessageBox::StandardButton Btn=QMessageBox::warning(NULL,"Warning",Msg,QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel);
			if(Btn==QMessageBox::Cancel){
				break;
			}
		}
	}
	return true;
}

//それぞれの領域で閾値を作成する
bool DetailSettingForm::CalcMultiAlgorithmSupport(int PixelLibID,const QString AlgorithmName,int LibID,QString &Msg)
{
	//アルゴリズム（領域）の指定がない場合、まだ選ばれていない領域（ResistFlexArea）をセット
	if(AlgorithmName.isEmpty()==true){
		//ピクセルライブラリを取得
		AlgorithmLibraryList *p=NULL;
		for(p=PixelAList.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->GetLibID()==PixelLibID){
				break;
			}
		}
		if(p==NULL){
			Msg="Not load pixel library. ( library ID = " + QString::number(PixelLibID) + " )";
			return false;
		}

		//ピクセルライブラリを取得
///		PLibList[_Resist]=new PixelInspectionLibrary(PixelAlgorithmBasePointer->GetLibType(),GUIBase->GetLayersBase());
		//ライブラリの生成コードが無くても仮想関数で生成できる
//		PLibList[_Resist]=dynamic_cast<PixelInspectionLibrary *>(PixelAlgorithmBasePointer->GetLibraryContainer()->CreateNew());
		PLibLevelList[_Resist]=new AlgorithmLibraryLevelContainer(PixelAlgorithmBasePointer->GetLibraryContainer());
		if(PixelAlgorithmInPageRootPointer->GetLibraryContainer()->GetLibrary(p->GetLibID(),*(PLibLevelList[_Resist]))==false){
			//ピクセルライブラリがなかったら？？？
			Msg="Not load pixel library. ( library ID = " + QString::number(PixelLibID) + " )";
			return false;
		}
		PixelInspectionLibrary	*PLibList=(PixelInspectionLibrary *)PLibLevelList[_Resist]->GetLibrary();
		SetLibData(_Resist,PLibList);

		return true;
	}

	for(LogicDLL *L=GUIBase->GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLName()==AlgorithmName){
			//ライブラリ情報を取得
			AlgorithmBase	*AlgorithmBasePointer=GUIBase->GetLayersBase()->GetAlgorithmBase(L->GetDLLRoot(),L->GetDLLName());
			if(AlgorithmBasePointer==NULL){
				//AlgorithmBaseなし
				return false;
			}
			AlgorithmInPageRoot	*AlgorithmInPageRootPointer=AlgorithmBasePointer->GetPageData(0);
			if(AlgorithmInPageRootPointer==NULL){
				//AlgorithmInPageRootなし
				return false;
			}
			AlgorithmInPagePI	*AlgorithmInPagePIPointer=dynamic_cast<AlgorithmInPagePI *>(AlgorithmInPageRootPointer);
			if(AlgorithmInPagePIPointer==NULL){
				//AlgorithmInPagePIなし
				return false;
			}

			PixelType PType=_Other;
			struct AutoAlignmentLibraryStruct AALibInStack[10];
			struct AutoAlignmentLibraryStruct *AALib=AALibInStack;
			if(AlgorithmName=="AutoAlignment"){
				int	AALibNumb=0;
				for(AlgorithmLibraryList *p=AAlignAList.GetFirst();p!=NULL;p=p->GetNext()){
					//オートアライメントライブラリを取得
					AlgorithmLibraryLevelContainer	AutoAlignLevel(AlgorithmBasePointer->GetLibraryContainer());
					//AutoAlignmentLibrary *AutoAlignmentLib=dynamic_cast<AutoAlignmentLibrary *>(AlgorithmBasePointer->GetLibraryContainer()->CreateNew());
					if(AlgorithmBasePointer->GetLibraryContainer()->GetLibrary(p->GetLibID(),AutoAlignLevel)){
						AutoAlignmentLibrary *AutoAlignmentLib=(AutoAlignmentLibrary *)AutoAlignLevel.GetLibrary();
						if(AutoAlignmentLib!=NULL){
							if(AutoAlignmentLib->StartupExecute==true){
								AALib[AALibNumb].AutoAlignmentLibraryPointer=AutoAlignmentLib;
								AALib[AALibNumb].Priority					=AutoAlignmentLib->Priority;
								AALibNumb++;
							}
							else{
								delete AutoAlignmentLib;
							}
						}
					}
				}
				QSort(AALib,AALibNumb,sizeof(AALib[0]),AALibFunc);
				if(AALib[0].AutoAlignmentLibraryPointer->GetLibID()==LibID){
					PType=_Pad;
				}
				else{
					PType=_Silk;
				}
				for(int i=0;i<AALibNumb;i++){
					delete AALib[i].AutoAlignmentLibraryPointer;
				}
			}

			AlgorithmLibraryContainer  *AL=L->GetInstance()->GetLibraryContainer();
			if(AL!=NULL){
				AlgorithmLibraryListContainer	AList;
				AL->EnumLibrary(L->GetInstance()->GetLibType(),AList);
				for(AlgorithmLibraryList *pAlgorithmLibraryList=AList.GetFirst();pAlgorithmLibraryList!=NULL;pAlgorithmLibraryList=pAlgorithmLibraryList->GetNext()){
					if(pAlgorithmLibraryList->GetLibID()==LibID){
						//ピクセルライブラリを取得
						AlgorithmLibraryList *p=NULL;
						for(p=PixelAList.GetFirst();p!=NULL;p=p->GetNext()){
							if(p->GetLibID()==PixelLibID){
								break;
							}
						}
						if(p==NULL){
							return true;
						}

						if(AlgorithmName==/**/"AutoPCBHoleAligner"){
							PType=_Hole;
						}
						else if(AlgorithmName==/**/"DynamicClassify"){
							PType=_Pad;
						}

						if(PType==_Other){
							return true;
						}

						//ピクセルライブラリを取得
///						PLibList[PType]=new PixelInspectionLibrary(PixelAlgorithmBasePointer->GetLibType(),GUIBase->GetLayersBase());
						//ライブラリの生成コードが無くても仮想関数で生成できる
						PLibLevelList[PType]=new AlgorithmLibraryLevelContainer(PixelAlgorithmBasePointer->GetLibraryContainer());
						//PLibList[PType]=dynamic_cast<PixelInspectionLibrary *>(PixelAlgorithmBasePointer->GetLibraryContainer()->CreateNew());
						if(PixelAlgorithmInPageRootPointer->GetLibraryContainer()->GetLibrary(p->GetLibID(),*(PLibLevelList[PType]))==false){
							//ピクセルライブラリがなかったら？？？
							Msg="Not load pixel library. ( library ID = " + QString::number(PixelLibID) + " )";
							return false;
						}
						PixelInspectionLibrary	*PLibList=(PixelInspectionLibrary	*)PLibLevelList[PType]->GetLibrary();
						SetLibData(PType,PLibList);

						return true;
					}
				}
			}
			return true;
		}
	}

	return false;
}

void DetailSettingForm::SetLibData(PixelType PType,PixelInspectionLibrary *PLib)
{
	chSetting[PType]					->setChecked(PLib->DetailSettingNarrow);
	dsbNGThreshold[PType]				->setValue	(PLib->RelativeNGThresholdNarrow);
	sbMinimumNGSize[PType]				->setValue	(PLib->NGSizeNarrow);
	gbDetailSetting[PType]				->setChecked(PLib->DetailSettingBroad);
	sbNGThreshold[PType]				->setValue	(PLib->AbsoluteNGThresholdBroad);
	sbDetailMinimumNGSize[PType]		->setValue	(PLib->NGSizeBroad);
	chbIsCalcPixelInterPoration[PType]	->setChecked(PLib->IsCalcPixelInterPoration);
}

void DetailSettingForm::SetLayout()
{
	//setUpdatesEnabled
	setUpdatesEnabled(false);

	if(ui.gbDetailSettingForPad->isChecked()==true){
		ui.gbDetailSettingP					->setGeometry	(ui.gbDetailSettingP					->x(),gbDetailSettingPY					,ui.gbDetailSettingP			->width(),gbDetailSettingPH);
		ui.gbDetailSettingS					->setGeometry	(ui.gbDetailSettingS					->x(),gbDetailSettingSY					,ui.gbDetailSettingS			->width(),gbDetailSettingSH);
		ui.gbDetailSettingR					->setGeometry	(ui.gbDetailSettingR					->x(),gbDetailSettingRY					,ui.gbDetailSettingR			->width(),gbDetailSettingRH);
		ui.gbDetailSettingH					->setGeometry	(ui.gbDetailSettingH					->x(),gbDetailSettingHY					,ui.gbDetailSettingH			->width(),gbDetailSettingHH);
		ui.gbDetailSettingForPad			->setGeometry	(ui.gbDetailSettingForPad				->x(),gbDetailSettingForPadY			,ui.gbDetailSettingForPad		->width(),gbDetailSettingForPadH);
		ui.gbDetailSettingForSilk			->setGeometry	(ui.gbDetailSettingForSilk				->x(),gbDetailSettingForSilkY			,ui.gbDetailSettingForSilk		->width(),gbDetailSettingForSilkH);
		ui.gbDetailSettingForResist			->setGeometry	(ui.gbDetailSettingForResist			->x(),gbDetailSettingForResistY			,ui.gbDetailSettingForResist	->width(),gbDetailSettingForResistH);
		ui.gbDetailSettingForHole			->setGeometry	(ui.gbDetailSettingForHole				->x(),gbDetailSettingForHoleY			,ui.gbDetailSettingForHole		->width(),gbDetailSettingForHoleH);
		ui.chbIsCalcPixelInterPorationPad	->move			(ui.chbIsCalcPixelInterPorationPad		->x(),chbIsCalcPixelInterPorationPadY);
		ui.chbIsCalcPixelInterPorationSilk	->move			(ui.chbIsCalcPixelInterPorationSilk		->x(),chbIsCalcPixelInterPorationSilkY);
		ui.chbIsCalcPixelInterPorationResist->move			(ui.chbIsCalcPixelInterPorationResist	->x(),chbIsCalcPixelInterPorationResistY);
		ui.chbIsCalcPixelInterPorationHole	->move			(ui.chbIsCalcPixelInterPorationHole		->x(),chbIsCalcPixelInterPorationHoleY);
		ui.gbDetailSetting					->setGeometry	(ui.gbDetailSetting						->x(),gbDetailSettingY					,ui.gbDetailSetting				->width(),gbDetailSettingH);
		ui.lbDecision						->move			(ui.lbDecision							->x(),lbDecisionY);
		ui.lbCancel							->move			(ui.lbCancel							->x(),lbCancelY);
		ui.chSettingForSilk					->move			(ui.chSettingForSilk					->x(),chSettingForSilkY);
		ui.chSettingForResist				->move			(ui.chSettingForResist					->x(),chSettingForResistY);
		ui.chSettingForHole					->move			(ui.chSettingForHole					->x(),chSettingForHoleY);
		resize(width(),H);
	}
	else{
		ui.gbDetailSettingP					->setGeometry	(ui.gbDetailSettingP					->x(),gbDetailSettingPY									,ui.gbDetailSettingP			->width(),gbDetailSettingPH		-LayoutHeight);
		ui.gbDetailSettingS					->setGeometry	(ui.gbDetailSettingS					->x(),gbDetailSettingSY					-LayoutHeight	,ui.gbDetailSettingS			->width(),gbDetailSettingSH);
		ui.gbDetailSettingR					->setGeometry	(ui.gbDetailSettingR					->x(),gbDetailSettingRY					-LayoutHeight	,ui.gbDetailSettingR			->width(),gbDetailSettingRH);
		ui.gbDetailSettingH					->setGeometry	(ui.gbDetailSettingH					->x(),gbDetailSettingHY					-LayoutHeight	,ui.gbDetailSettingH			->width(),gbDetailSettingHH);
		ui.gbDetailSettingForPad			->setGeometry	(ui.gbDetailSettingForPad				->x(),gbDetailSettingForPadY							,ui.gbDetailSettingForPad		->width(),gbDetailSettingForPadH-LayoutHeight);
		ui.gbDetailSettingForSilk			->setGeometry	(ui.gbDetailSettingForSilk				->x(),gbDetailSettingForSilkY							,ui.gbDetailSettingForSilk		->width(),gbDetailSettingForSilkH);
		ui.gbDetailSettingForResist			->setGeometry	(ui.gbDetailSettingForResist			->x(),gbDetailSettingForResistY							,ui.gbDetailSettingForResist	->width(),gbDetailSettingForResistH);
		ui.gbDetailSettingForHole			->setGeometry	(ui.gbDetailSettingForHole				->x(),gbDetailSettingForHoleY							,ui.gbDetailSettingForHole		->width(),gbDetailSettingForHoleH);
		ui.chbIsCalcPixelInterPorationPad	->move			(ui.chbIsCalcPixelInterPorationPad		->x(),chbIsCalcPixelInterPorationPadY	-LayoutHeight);
		ui.chbIsCalcPixelInterPorationSilk	->move			(ui.chbIsCalcPixelInterPorationSilk		->x(),chbIsCalcPixelInterPorationSilkY);
		ui.chbIsCalcPixelInterPorationResist->move			(ui.chbIsCalcPixelInterPorationResist	->x(),chbIsCalcPixelInterPorationResistY);
		ui.chbIsCalcPixelInterPorationHole	->move			(ui.chbIsCalcPixelInterPorationHole		->x(),chbIsCalcPixelInterPorationHoleY);
		ui.gbDetailSetting					->setGeometry	(ui.gbDetailSetting						->x(),gbDetailSettingY									,ui.gbDetailSetting				->width(),gbDetailSettingH		-LayoutHeight);
		ui.lbDecision						->move			(ui.lbDecision							->x(),lbDecisionY						-LayoutHeight);
		ui.lbCancel							->move			(ui.lbCancel							->x(),lbCancelY							-LayoutHeight);
		ui.chSettingForSilk					->move			(ui.chSettingForSilk					->x(),chSettingForSilkY					-LayoutHeight);
		ui.chSettingForResist				->move			(ui.chSettingForResist					->x(),chSettingForResistY				-LayoutHeight);
		ui.chSettingForHole					->move			(ui.chSettingForHole					->x(),chSettingForHoleY					-LayoutHeight);
		resize(width(),H-LayoutHeight);
	}

	if(ui.gbDetailSettingForSilk->isChecked()==false){
		ui.gbDetailSettingS					->resize(ui.gbDetailSettingS					->width()	,gbDetailSettingSH									-LayoutHeight);
		ui.gbDetailSettingR					->move	(ui.gbDetailSettingR					->x()		,ui.gbDetailSettingR					->y()		-LayoutHeight);
		ui.gbDetailSettingH					->move	(ui.gbDetailSettingH					->x()		,ui.gbDetailSettingH					->y()		-LayoutHeight);
		ui.gbDetailSettingForSilk			->resize(ui.gbDetailSettingForSilk				->width()	,gbDetailSettingForSilkH							-LayoutHeight);
		ui.chbIsCalcPixelInterPorationSilk	->move	(ui.chbIsCalcPixelInterPorationSilk		->x()		,ui.chbIsCalcPixelInterPorationSilk		->y()		-LayoutHeight);
		ui.gbDetailSetting					->resize(ui.gbDetailSetting						->width()	,ui.gbDetailSetting						->height()	-LayoutHeight);
		ui.lbDecision						->move	(ui.lbDecision							->x()		,ui.lbDecision							->y()		-LayoutHeight);
		ui.lbCancel							->move	(ui.lbCancel							->x()		,ui.lbCancel							->y()		-LayoutHeight);
		ui.chSettingForResist				->move	(ui.chSettingForResist					->x()		,ui.chSettingForResist					->y()		-LayoutHeight);
		ui.chSettingForHole					->move	(ui.chSettingForHole					->x()		,ui.chSettingForHole					->y()		-LayoutHeight);
		resize(width(),height()-LayoutHeight);
	}

	if(ui.gbDetailSettingForResist->isChecked()==false){
		ui.gbDetailSettingR					->resize(ui.gbDetailSettingR					->width()	,gbDetailSettingRH									-LayoutHeight);
		ui.gbDetailSettingH					->move	(ui.gbDetailSettingH					->x()		,ui.gbDetailSettingH					->y()		-LayoutHeight);
		ui.gbDetailSettingForResist			->resize(ui.gbDetailSettingForResist			->width()	,gbDetailSettingForResistH							-LayoutHeight);
		ui.chbIsCalcPixelInterPorationResist->move	(ui.chbIsCalcPixelInterPorationResist	->x()		,ui.chbIsCalcPixelInterPorationResist	->y()		-LayoutHeight);
		ui.gbDetailSetting					->resize(ui.gbDetailSetting						->width()	,ui.gbDetailSetting						->height()	-LayoutHeight);
		ui.lbDecision						->move	(ui.lbDecision							->x()		,ui.lbDecision							->y()		-LayoutHeight);
		ui.lbCancel							->move	(ui.lbCancel							->x()		,ui.lbCancel							->y()		-LayoutHeight);
		ui.chSettingForHole					->move	(ui.chSettingForHole					->x()		,ui.chSettingForHole					->y()		-LayoutHeight);
		resize(width(),height()-LayoutHeight);
	}

	if(ui.gbDetailSettingForHole->isChecked()==false){
		ui.gbDetailSettingH					->resize(ui.gbDetailSettingH					->width()	,gbDetailSettingHH									-LayoutHeight);
		ui.gbDetailSettingForHole			->resize(ui.gbDetailSettingForHole				->width()	,gbDetailSettingForHoleH							-LayoutHeight);
		ui.chbIsCalcPixelInterPorationHole	->move	(ui.chbIsCalcPixelInterPorationHole		->x()		,ui.chbIsCalcPixelInterPorationHole		->y()		-LayoutHeight);
		ui.gbDetailSetting					->resize(ui.gbDetailSetting						->width()	,ui.gbDetailSetting						->height()	-LayoutHeight);
		ui.lbDecision						->move	(ui.lbDecision							->x()		,ui.lbDecision							->y()		-LayoutHeight);
		ui.lbCancel							->move	(ui.lbCancel							->x()		,ui.lbCancel							->y()		-LayoutHeight);
		resize(width(),height()-LayoutHeight);
	}

	//setUpdatesEnabled
	setUpdatesEnabled(true);
}

void	DetailSettingForm::SetEnabledForPad(bool checked)
{
	ui.lbStrongP		->setEnabled(checked);
	ui.hsNGThresholdP	->setEnabled(checked);
	ui.lbWeakP			->setEnabled(checked);
	ui.dsbNGThresholdP	->setEnabled(checked);
	ui.diMinimumNGSizeP	->setEnabled(checked);
	ui.lbMinimumNGSizeP	->setEnabled(checked);
	ui.sbMinimumNGSizeP	->setEnabled(checked);
}

void	DetailSettingForm::SetEnabledForSilk(bool checked)
{
	ui.lbStrongS		->setEnabled(checked);
	ui.hsNGThresholdS	->setEnabled(checked);
	ui.lbWeakS			->setEnabled(checked);
	ui.dsbNGThresholdS	->setEnabled(checked);
	ui.diMinimumNGSizeS	->setEnabled(checked);
	ui.lbMinimumNGSizeS	->setEnabled(checked);
	ui.sbMinimumNGSizeS	->setEnabled(checked);
}

void	DetailSettingForm::SetEnabledForResist(bool checked)
{
	ui.lbStrongR		->setEnabled(checked);
	ui.hsNGThresholdR	->setEnabled(checked);
	ui.lbWeakR			->setEnabled(checked);
	ui.dsbNGThresholdR	->setEnabled(checked);
	ui.diMinimumNGSizeR	->setEnabled(checked);
	ui.lbMinimumNGSizeR	->setEnabled(checked);
	ui.sbMinimumNGSizeR	->setEnabled(checked);
}

void	DetailSettingForm::SetEnabledForHole(bool checked)
{
	ui.lbStrongH		->setEnabled(checked);
	ui.hsNGThresholdH	->setEnabled(checked);
	ui.lbWeakH			->setEnabled(checked);
	ui.dsbNGThresholdH	->setEnabled(checked);
	ui.diMinimumNGSizeH	->setEnabled(checked);
	ui.lbMinimumNGSizeH	->setEnabled(checked);
	ui.sbMinimumNGSizeH	->setEnabled(checked);
}

bool	DetailSettingForm::CheckIsEdit()
{
	//変更があるかどうかチェック
	for(int i=0;i<PLibNumb;i++){
		if(PLibLevelList[i]==NULL){
			continue;
		}
		PixelInspectionLibrary	*PLibList=(PixelInspectionLibrary *)PLibLevelList[i]->GetLibrary();

		if(PLibList->DetailSettingNarrow!=chSetting[i]->isChecked()){
			return true;
		}
		if(PLibList->RelativeNGThresholdNarrow!=dsbNGThreshold[i]->value()){
			return true;
		}
		if(PLibList->NGSizeNarrow!=sbMinimumNGSize[i]->value()){
			return true;
		}
		if(PLibList->DetailSettingBroad!=gbDetailSetting[i]->isChecked()){
			return true;
		}
		if(PLibList->AbsoluteNGThresholdBroad!=sbNGThreshold[i]->value()){
			return true;
		}
		if(PLibList->NGSizeBroad!=sbDetailMinimumNGSize[i]->value()){
			return true;
		}
		if(PLibList->IsCalcPixelInterPoration!=chbIsCalcPixelInterPoration[i]->isChecked()){
			return true;
		}
	}
	return false;
/*
	//変更があるかどうかチェック
	if(NGThresholdP!=ui.dsbNGThresholdP->value()){
		return true;
	}
	if(NGThresholdS!=ui.dsbNGThresholdS->value(){
		return true;
	}
	if(NGThresholdR!=ui.dsbNGThresholdR->value(){
		return true;
	}
	if(NGThresholdH!=ui.dsbNGThresholdH->value(){
		return true;
	}
	if(MinimumNGSizeP!=ui.sbMinimumNGSizeP->value(){
		return true;
	}
	if(MinimumNGSizeS!=ui.sbMinimumNGSizeS->value(){
		return true;
	}
	if(MinimumNGSizeR!=ui.sbMinimumNGSizeR->value(){
		return true;
	}
	if(MinimumNGSizeH!=ui.sbMinimumNGSizeH->value(){
		return true;
	}
	if(CheckPadIns!=ui.chSettingForPad->isChecked(){
		return true;
	}
	if(CheckSilkIns!=ui.chSettingForSilk->isChecked(){
		return true;
	}
	if(CheckResistIns!=ui.chSettingForResist->isChecked(){
		return true;
	}
	if(CheckHoleIns!=ui.chSettingForHole->isChecked(){
		return true;
	}
	if(DonePadIns!=ui.gbDetailSettingForPad->isChecked(){
		return true;
	}
	if(DoneSilkIns!=ui.gbDetailSettingForSilk->isChecked(){
		return true;
	}
	if(DoneResistIns!=ui.gbDetailSettingForResist->isChecked(){
		return true;
	}
	if(DoneHoleIns!=ui.gbDetailSettingForHole->isChecked(){
		return true;
	}
	if(NGThresholdForPad!=ui.sbNGThresholdForPad->value(){
		return true;
	}
	if(MinimumNGSizeForPad!=ui.sbMinimumNGSizeForPad->value(){
		return true;
	}
	if(NGThresholdForSilk!=ui.sbNGThresholdForSilk->value(){
		return true;
	}
	if(MinimumNGSizeForSilk!=ui.sbMinimumNGSizeForSilk->value(){
		return true;
	}
	if(NGThresholdForResist!=ui.sbNGThresholdForResist->value(){
		return true;
	}
	if(MinimumNGSizeForResist!=ui.sbMinimumNGSizeForResist->value(){
		return true;
	}
	if(NGThresholdForHole!=ui.sbNGThresholdForHole->value(){
		return true;
	}
	if(MinimumNGSizeForHole!=ui.sbMinimumNGSizeForHole->value(){
		return true;
	}
	if(IsCalcPixelInterPorationPad!=ui.chbIsCalcPixelInterPorationPad->isChecked(){
		return true;
	}
	if(IsCalcPixelInterPorationSilk!=ui.chbIsCalcPixelInterPorationSilk->isChecked(){
		return true;
	}
	if(IsCalcPixelInterPorationResist!=ui.chbIsCalcPixelInterPorationResist->isChecked(){
		return true;
	}
	if(IsCalcPixelInterPorationHole!=ui.chbIsCalcPixelInterPorationHole->isChecked(){
		return true;
	}
	return false;
*/
}
