#include "LEDControl16JPrnDialog.h"
#include "ui_LEDControl16JPrnDialog.h"
#include "DefineSignalDialog.h"
#include "LEDControl16JioPrn.h"

LEDControl16JPrnDialog::LEDControl16JPrnDialog(LEDControl16JioPanel *p,QWidget *parent) :
    QDialog(parent)
    ,Panel(p)
    ,ui(new Ui::LEDControl16JPrnDialog)
{
    ui->setupUi(this);

	ShowData();
}

LEDControl16JPrnDialog::~LEDControl16JPrnDialog()
{
    delete ui;
}

void LEDControl16JPrnDialog::ShowData(void)
{
    ui->spinBoxConveyerLength		->setValue(Panel->JioFixedData.ConveyerLength	);
    ui->spinBoxGateOpenTerm			->setValue(Panel->JioFixedData.GateOpenTerm	);
    ui->spinBoxMulInputA			->setValue(Panel->JioFixedData.MulInputA		);
    ui->spinBoxMulInputB			->setValue(Panel->JioFixedData.MulInputB		);
    ui->spinBoxMinOFF				->setValue(Panel->JioFixedData.TriggerFilterMinOFF	);
    ui->spinBoxMinON				->setValue(Panel->JioFixedData.TriggerFilterMinON	);
    ui->spinBoxDelayFrameTriggerA	->setValue(Panel->JioFixedData.DelayFrameTriggerA);
    ui->spinBoxDelayFrameTriggerB	->setValue(Panel->JioFixedData.DelayFrameTriggerB);
    ui->spinBoxDelayFrameTriggerC	->setValue(Panel->JioFixedData.DelayFrameTriggerC);
    ui->spinBoxDelayFrameTriggerD	->setValue(Panel->JioFixedData.DelayFrameTriggerD);
    ui->spinBoxResultAAcceptStart	->setValue(Panel->JioFixedData.ResultAAcceptStart);
    ui->spinBoxResultBAcceptStart	->setValue(Panel->JioFixedData.ResultBAcceptStart);
    ui->spinBoxResultCAcceptStart	->setValue(Panel->JioFixedData.ResultCAcceptStart);
    ui->spinBoxResultDAcceptStart	->setValue(Panel->JioFixedData.ResultDAcceptStart);
    ui->spinBoxResultACloseAccept	->setValue(Panel->JioFixedData.ResultACloseAccept);
    ui->spinBoxResultBCloseAccept	->setValue(Panel->JioFixedData.ResultBCloseAccept);
    ui->spinBoxResultCCloseAccept	->setValue(Panel->JioFixedData.ResultCCloseAccept);
    ui->spinBoxResultDCloseAccept	->setValue(Panel->JioFixedData.ResultDCloseAccept);
    ui->doubleSpinBoxTriggerDelayParameter	->setValue(Panel->JioFixedData.TriggerDelayParameter);
}

void LEDControl16JPrnDialog::GetDataFromWindow(void)
{
    Panel->JioFixedData.ConveyerLength		=ui->spinBoxConveyerLength		->value();
    Panel->JioFixedData.GateOpenTerm		=ui->spinBoxGateOpenTerm		->value();
    Panel->JioFixedData.MulInputA			=ui->spinBoxMulInputA			->value();
    Panel->JioFixedData.MulInputB			=ui->spinBoxMulInputB			->value();
    Panel->JioFixedData.TriggerFilterMinOFF	=ui->spinBoxMinOFF				->value();
    Panel->JioFixedData.TriggerFilterMinON	=ui->spinBoxMinON				->value();
    Panel->JioFixedData.DelayFrameTriggerA	=ui->spinBoxDelayFrameTriggerA	->value();
    Panel->JioFixedData.DelayFrameTriggerB	=ui->spinBoxDelayFrameTriggerB	->value();
    Panel->JioFixedData.DelayFrameTriggerC	=ui->spinBoxDelayFrameTriggerC	->value();
    Panel->JioFixedData.DelayFrameTriggerD	=ui->spinBoxDelayFrameTriggerD	->value();
    Panel->JioFixedData.ResultAAcceptStart	=ui->spinBoxResultAAcceptStart	->value();
    Panel->JioFixedData.ResultBAcceptStart	=ui->spinBoxResultBAcceptStart	->value();
    Panel->JioFixedData.ResultCAcceptStart	=ui->spinBoxResultCAcceptStart	->value();
    Panel->JioFixedData.ResultDAcceptStart	=ui->spinBoxResultDAcceptStart	->value();
    Panel->JioFixedData.ResultACloseAccept	=ui->spinBoxResultACloseAccept	->value();
    Panel->JioFixedData.ResultBCloseAccept	=ui->spinBoxResultBCloseAccept	->value();
    Panel->JioFixedData.ResultCCloseAccept	=ui->spinBoxResultCCloseAccept	->value();
    Panel->JioFixedData.ResultDCloseAccept	=ui->spinBoxResultDCloseAccept	->value();
    Panel->JioFixedData.TriggerDelayParameter	=ui->doubleSpinBoxTriggerDelayParameter	->value();
}

void LEDControl16JPrnDialog::on_pushButtonSend_clicked()
{
	GetDataFromWindow();
	Panel->SendGio();
}

void LEDControl16JPrnDialog::on_pushButtonSave_clicked()
{
	GetDataFromWindow();
	Panel->SaveDefault();
}

void LEDControl16JPrnDialog::on_pushButtonLoad_clicked()
{
	Panel->LoadDefault();
	ShowData();
}

void LEDControl16JPrnDialog::on_pushButtonRequire_clicked()
{
	Panel->RequireGio();
	ShowData();
}

void LEDControl16JPrnDialog::on_pushButtonClose_clicked()
{
	done(true);
}

void LEDControl16JPrnDialog::on_pushButtonDefineSignals_clicked()
{
	DefineSignalDialog	D(Panel);
	D.exec();
}

void LEDControl16JPrnDialog::on_pushButtonShowTiming_clicked()
{
	Panel->ShowTimingChart();
	done(true);
}
