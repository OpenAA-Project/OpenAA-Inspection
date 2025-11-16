#include "LEDControl16GPrnDialog.h"
#include "ui_LEDControl16GPrnDialog.h"
#include "DefineSignalDialog.h"
#include "LEDControl16GPrn.h"

LEDControl16GPrnDialog::LEDControl16GPrnDialog(LEDControl16GPanel *p,QWidget *parent) :
    QDialog(parent)
    ,Panel(p)
    ,ui(new Ui::LEDControl16GPrnDialog)
{
    ui->setupUi(this);

	ShowData();
}

LEDControl16GPrnDialog::~LEDControl16GPrnDialog()
{
    delete ui;
}

void LEDControl16GPrnDialog::ShowData(void)
{
    ui->spinBoxConveyerLength		->setValue(Panel->GIOFixedData.ConveyerLength	);
    ui->spinBoxGateOpenTerm			->setValue(Panel->GIOFixedData.GateOpenTerm	);
    ui->spinBoxMulInputA			->setValue(Panel->GIOFixedData.MulInputA		);
    ui->spinBoxMulInputB			->setValue(Panel->GIOFixedData.MulInputB		);
    ui->spinBoxMinOFF				->setValue(Panel->GIOFixedData.TriggerFilterMinOFF	);
    ui->spinBoxMinON				->setValue(Panel->GIOFixedData.TriggerFilterMinON	);
    ui->spinBoxDelayFrameTriggerA	->setValue(Panel->GIOFixedData.DelayFrameTriggerA);
    ui->spinBoxDelayFrameTriggerB	->setValue(Panel->GIOFixedData.DelayFrameTriggerB);
    ui->spinBoxDelayFrameTriggerC	->setValue(Panel->GIOFixedData.DelayFrameTriggerC);
    ui->spinBoxDelayFrameTriggerD	->setValue(Panel->GIOFixedData.DelayFrameTriggerD);
    ui->spinBoxResultAAcceptStart	->setValue(Panel->GIOFixedData.ResultAAcceptStart);
    ui->spinBoxResultBAcceptStart	->setValue(Panel->GIOFixedData.ResultBAcceptStart);
    ui->spinBoxResultCAcceptStart	->setValue(Panel->GIOFixedData.ResultCAcceptStart);
    ui->spinBoxResultDAcceptStart	->setValue(Panel->GIOFixedData.ResultDAcceptStart);
    ui->spinBoxResultACloseAccept	->setValue(Panel->GIOFixedData.ResultACloseAccept);
    ui->spinBoxResultBCloseAccept	->setValue(Panel->GIOFixedData.ResultBCloseAccept);
    ui->spinBoxResultCCloseAccept	->setValue(Panel->GIOFixedData.ResultCCloseAccept);
    ui->spinBoxResultDCloseAccept	->setValue(Panel->GIOFixedData.ResultDCloseAccept);
    ui->doubleSpinBoxTriggerDelayParameter	->setValue(Panel->GIOFixedData.TriggerDelayParameter);
}

void LEDControl16GPrnDialog::GetDataFromWindow(void)
{
    Panel->GIOFixedData.ConveyerLength		=ui->spinBoxConveyerLength		->value();
    Panel->GIOFixedData.GateOpenTerm		=ui->spinBoxGateOpenTerm		->value();
    Panel->GIOFixedData.MulInputA			=ui->spinBoxMulInputA			->value();
    Panel->GIOFixedData.MulInputB			=ui->spinBoxMulInputB			->value();
    Panel->GIOFixedData.TriggerFilterMinOFF	=ui->spinBoxMinOFF				->value();
    Panel->GIOFixedData.TriggerFilterMinON	=ui->spinBoxMinON				->value();
    Panel->GIOFixedData.DelayFrameTriggerA	=ui->spinBoxDelayFrameTriggerA	->value();
    Panel->GIOFixedData.DelayFrameTriggerB	=ui->spinBoxDelayFrameTriggerB	->value();
    Panel->GIOFixedData.DelayFrameTriggerC	=ui->spinBoxDelayFrameTriggerC	->value();
    Panel->GIOFixedData.DelayFrameTriggerD	=ui->spinBoxDelayFrameTriggerD	->value();
    Panel->GIOFixedData.ResultAAcceptStart	=ui->spinBoxResultAAcceptStart	->value();
    Panel->GIOFixedData.ResultBAcceptStart	=ui->spinBoxResultBAcceptStart	->value();
    Panel->GIOFixedData.ResultCAcceptStart	=ui->spinBoxResultCAcceptStart	->value();
    Panel->GIOFixedData.ResultDAcceptStart	=ui->spinBoxResultDAcceptStart	->value();
    Panel->GIOFixedData.ResultACloseAccept	=ui->spinBoxResultACloseAccept	->value();
    Panel->GIOFixedData.ResultBCloseAccept	=ui->spinBoxResultBCloseAccept	->value();
    Panel->GIOFixedData.ResultCCloseAccept	=ui->spinBoxResultCCloseAccept	->value();
    Panel->GIOFixedData.ResultDCloseAccept	=ui->spinBoxResultDCloseAccept	->value();
    Panel->GIOFixedData.TriggerDelayParameter	=ui->doubleSpinBoxTriggerDelayParameter	->value();
}

void LEDControl16GPrnDialog::on_pushButtonSend_clicked()
{
	GetDataFromWindow();
	Panel->SendGio();
}

void LEDControl16GPrnDialog::on_pushButtonSave_clicked()
{
	GetDataFromWindow();
	Panel->SaveDefault();
}

void LEDControl16GPrnDialog::on_pushButtonLoad_clicked()
{
	Panel->LoadDefault();
	ShowData();
}

void LEDControl16GPrnDialog::on_pushButtonRequire_clicked()
{
	Panel->RequireGio();
	ShowData();
}

void LEDControl16GPrnDialog::on_pushButtonClose_clicked()
{
	done(true);
}

void LEDControl16GPrnDialog::on_pushButtonDefineSignals_clicked()
{
	DefineSignalDialog	D(Panel);
	D.exec();
}

void LEDControl16GPrnDialog::on_pushButtonShowTiming_clicked()
{
	Panel->ShowTimingChart();
	done(true);
}
