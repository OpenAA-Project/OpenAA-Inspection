#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "CameraXtiumMitsubishiCIS.h"

SettingDialog::SettingDialog(CameraXtiumMitsubishiCIS *cam ,QWidget *parent) :
    QDialog(parent)
	,Cam(cam)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

	ConfigFileName	=cam->ConfigFileName	;
	CameraType		=cam->CameraType		;
	LineClock		=cam->LineClock			;
	BoardCount		=cam->BoardCount		;
	Resolution		=cam->Resolution		;
	OuterTrigger	=cam->OuterTrigger		;
	LEDControl		=cam->LEDControl		;
	LEDDutyFull		=cam->LEDDutyFull		;
	LEDDutyA		=cam->LEDDutyA			;
	LEDDutyB		=cam->LEDDutyB			;
	LEDDivide		=cam->LEDDivide			;
	Gain			=cam->Gain				;
	GainR			=cam->GainR				;
	GainG			=cam->GainG				;
	GainB			=cam->GainB				;
	YDirection		=cam->YDirection		;
	Gamma			=cam->Gamma				;
	//EvenOffsetY		=cam->Board[0]->ChannelA.OffsetY;
	//OddOffsetY		=cam->Board[0]->ChannelB.OffsetY;
	ModeAdjustWhite	=cam->ModeAdjustWhite	;

	ui->comboBoxType->setCurrentIndex(CameraType);
	ui->spinBoxBoardCount	->setValue(BoardCount);
	ui->lineEditConfigFileName	->setText(ConfigFileName);
	ui->spinBoxBoardLineClock	->setValue(LineClock);

	ui->comboBoxResolution		->setCurrentIndex(Resolution);
	ui->checkBoxOuterTriggerMode->setChecked(OuterTrigger);
	ui->comboBoxLEDControl		->setCurrentIndex(LEDControl);
	ui->doubleSpinBoxLEDDutyFull->setValue(LEDDutyFull);
	ui->doubleSpinBoxLEDDutyA	->setValue(LEDDutyA);
	ui->doubleSpinBoxLEDDutyB	->setValue(LEDDutyB);
	ui->comboBoxLEDDivide		->setCurrentIndex(LEDDivide);
	ui->checkBoxGainMode		->setChecked(Gain);
	ui->doubleSpinBoxGainRed	->setValue(GainR);
	ui->doubleSpinBoxGainGreen	->setValue(GainG);
	ui->doubleSpinBoxGainBlue	->setValue(GainB);
	ui->checkBoxScanDirection	->setChecked(YDirection);
	ui->checkBoxGamma			->setChecked(Gamma);

	ui->spinBoxEvenOffsetY		->setValue(EvenOffsetY	);
	ui->spinBoxOddOffsetY		->setValue(OddOffsetY	);
	ui->checkBoxModeAdjustWhite	->setChecked(ModeAdjustWhite);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_comboBoxType_currentIndexChanged(int index)
{

}

void SettingDialog::on_pushButtonConfigFileName_clicked()
{

}

void SettingDialog::on_checkBoxGainMode_clicked()
{
	if(ui->checkBoxGainMode->isChecked()==true){
		ui->doubleSpinBoxGainRed	->setEnabled(true);
		ui->doubleSpinBoxGainGreen	->setEnabled(true);
		ui->doubleSpinBoxGainBlue	->setEnabled(true);
	}
	else{
		ui->doubleSpinBoxGainRed	->setEnabled(false);
		ui->doubleSpinBoxGainGreen	->setEnabled(false);
		ui->doubleSpinBoxGainBlue	->setEnabled(false);
	}
}

void SettingDialog::on_pushButtonOK_clicked()
{
	CameraType		=ui->comboBoxType				->currentIndex();
	BoardCount		=ui->spinBoxBoardCount			->value();
	ConfigFileName	=ui->lineEditConfigFileName		->text();
	LineClock		=ui->spinBoxBoardLineClock		->value();

	Resolution		=ui->comboBoxResolution			->currentIndex();
	OuterTrigger	=ui->checkBoxOuterTriggerMode	->isChecked();
	LEDControl		=ui->comboBoxLEDControl			->currentIndex();
	LEDDutyFull		=ui->doubleSpinBoxLEDDutyFull	->value();
	LEDDutyA		=ui->doubleSpinBoxLEDDutyA		->value();
	LEDDutyB		=ui->doubleSpinBoxLEDDutyB		->value();
	LEDDivide		=ui->comboBoxLEDDivide			->currentIndex();
	Gain			=ui->checkBoxGainMode			->isChecked();
	GainR			=ui->doubleSpinBoxGainRed		->value();
	GainG			=ui->doubleSpinBoxGainGreen		->value();
	GainB			=ui->doubleSpinBoxGainBlue		->value();
	YDirection		=ui->checkBoxScanDirection		->isChecked();
	Gamma			=ui->checkBoxGamma				->isChecked();
	EvenOffsetY		=ui->spinBoxEvenOffsetY			->value();
	OddOffsetY		=ui->spinBoxOddOffsetY			->value();
	ModeAdjustWhite	=ui->checkBoxModeAdjustWhite	->isChecked();

	Cam->ConfigFileName	=ConfigFileName	;
	Cam->CameraType		=CameraType		;
	Cam->LineClock		=LineClock		;
	Cam->BoardCount		=BoardCount		;
	Cam->Resolution		=Resolution		;
	Cam->OuterTrigger	=OuterTrigger	;
	Cam->LEDControl		=LEDControl		;
	Cam->LEDDutyFull	=LEDDutyFull	;
	Cam->LEDDutyA		=LEDDutyA		;
	Cam->LEDDutyB		=LEDDutyB		;
	Cam->LEDDivide		=LEDDivide		;
	Cam->Gain			=Gain			;
	Cam->GainR			=GainR			;
	Cam->GainG			=GainG			;
	Cam->GainB			=GainB			;
	Cam->YDirection		=YDirection		;
	Cam->Gamma			=Gamma			;
	Cam->ModeAdjustWhite=ModeAdjustWhite;

	//for(int i=0;i<Cam->BoardCount;i++){
	//	Cam->Board[i]->ChannelA.OffsetY	=EvenOffsetY;
	//	Cam->Board[i]->ChannelB.OffsetY	=OddOffsetY	;
	//}

	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingDialog::on_pushButtonAdjustBlack_clicked()
{
	Cam->SetLightOnOff(false);
	for(int i=0;i<Cam->BoardCount;i++){
		Cam->ExecuteAdjustBlack(ui->checkBoxOuterTriggerMode	->isChecked());
	}
	Cam->SetLightOnOff(true);
}

void SettingDialog::on_pushButtonAdjustWhite_clicked()
{
	Cam->SetModeAdjustWhite(true);
	Cam->SetLightOnOff(true);
	for(int i=0;i<Cam->BoardCount;i++){
		Cam->ExecuteAdjustWhite(ui->checkBoxOuterTriggerMode	->isChecked());
	}
}
