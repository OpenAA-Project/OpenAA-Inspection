/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "LEDControl16HPrnDialog.h"
#include "ui_LEDControl16HPrnDialog.h"
#include "DefineSignalDialog.h"
#include "LEDControl16HioPrn.h"

LEDControl16HPrnDialog::LEDControl16HPrnDialog(LEDControl16HioPanel *p,QWidget *parent) :
    QDialog(parent)
    ,Panel(p)
    ,ui(new Ui::LEDControl16HPrnDialog)
{
    ui->setupUi(this);

	ShowData();
}

LEDControl16HPrnDialog::~LEDControl16HPrnDialog()
{
    delete ui;
}

void LEDControl16HPrnDialog::ShowData(void)
{
    ui->spinBoxConveyerLength		->setValue(Panel->HIOFixedData.ConveyerLength	);
    ui->spinBoxGateOpenTerm			->setValue(Panel->HIOFixedData.GateOpenTerm	);
    ui->spinBoxMulInputA			->setValue(Panel->HIOFixedData.MulInputA		);
    ui->spinBoxMulInputB			->setValue(Panel->HIOFixedData.MulInputB		);
    ui->spinBoxMinOFF				->setValue(Panel->HIOFixedData.TriggerFilterMinOFF	);
    ui->spinBoxMinON				->setValue(Panel->HIOFixedData.TriggerFilterMinON	);
    ui->spinBoxDelayFrameTriggerA	->setValue(Panel->HIOFixedData.DelayFrameTriggerA);
    ui->spinBoxDelayFrameTriggerB	->setValue(Panel->HIOFixedData.DelayFrameTriggerB);
    ui->spinBoxDelayFrameTriggerC	->setValue(Panel->HIOFixedData.DelayFrameTriggerC);
    ui->spinBoxDelayFrameTriggerD	->setValue(Panel->HIOFixedData.DelayFrameTriggerD);
    ui->spinBoxResultAAcceptStart	->setValue(Panel->HIOFixedData.ResultAAcceptStart);
    ui->spinBoxResultBAcceptStart	->setValue(Panel->HIOFixedData.ResultBAcceptStart);
    ui->spinBoxResultCAcceptStart	->setValue(Panel->HIOFixedData.ResultCAcceptStart);
    ui->spinBoxResultDAcceptStart	->setValue(Panel->HIOFixedData.ResultDAcceptStart);
    ui->spinBoxResultACloseAccept	->setValue(Panel->HIOFixedData.ResultACloseAccept);
    ui->spinBoxResultBCloseAccept	->setValue(Panel->HIOFixedData.ResultBCloseAccept);
    ui->spinBoxResultCCloseAccept	->setValue(Panel->HIOFixedData.ResultCCloseAccept);
    ui->spinBoxResultDCloseAccept	->setValue(Panel->HIOFixedData.ResultDCloseAccept);
    ui->doubleSpinBoxTriggerDelayParameter	->setValue(Panel->HIOFixedData.TriggerDelayParameter);
}

void LEDControl16HPrnDialog::GetDataFromWindow(void)
{
    Panel->HIOFixedData.ConveyerLength		=ui->spinBoxConveyerLength		->value();
    Panel->HIOFixedData.GateOpenTerm		=ui->spinBoxGateOpenTerm		->value();
    Panel->HIOFixedData.MulInputA			=ui->spinBoxMulInputA			->value();
    Panel->HIOFixedData.MulInputB			=ui->spinBoxMulInputB			->value();
    Panel->HIOFixedData.TriggerFilterMinOFF	=ui->spinBoxMinOFF				->value();
    Panel->HIOFixedData.TriggerFilterMinON	=ui->spinBoxMinON				->value();
    Panel->HIOFixedData.DelayFrameTriggerA	=ui->spinBoxDelayFrameTriggerA	->value();
    Panel->HIOFixedData.DelayFrameTriggerB	=ui->spinBoxDelayFrameTriggerB	->value();
    Panel->HIOFixedData.DelayFrameTriggerC	=ui->spinBoxDelayFrameTriggerC	->value();
    Panel->HIOFixedData.DelayFrameTriggerD	=ui->spinBoxDelayFrameTriggerD	->value();
    Panel->HIOFixedData.ResultAAcceptStart	=ui->spinBoxResultAAcceptStart	->value();
    Panel->HIOFixedData.ResultBAcceptStart	=ui->spinBoxResultBAcceptStart	->value();
    Panel->HIOFixedData.ResultCAcceptStart	=ui->spinBoxResultCAcceptStart	->value();
    Panel->HIOFixedData.ResultDAcceptStart	=ui->spinBoxResultDAcceptStart	->value();
    Panel->HIOFixedData.ResultACloseAccept	=ui->spinBoxResultACloseAccept	->value();
    Panel->HIOFixedData.ResultBCloseAccept	=ui->spinBoxResultBCloseAccept	->value();
    Panel->HIOFixedData.ResultCCloseAccept	=ui->spinBoxResultCCloseAccept	->value();
    Panel->HIOFixedData.ResultDCloseAccept	=ui->spinBoxResultDCloseAccept	->value();
    Panel->HIOFixedData.TriggerDelayParameter	=ui->doubleSpinBoxTriggerDelayParameter	->value();
}

void LEDControl16HPrnDialog::on_pushButtonSend_clicked()
{
	GetDataFromWindow();
	Panel->SendGio();
}

void LEDControl16HPrnDialog::on_pushButtonSave_clicked()
{
	GetDataFromWindow();
	Panel->SaveDefault();
}

void LEDControl16HPrnDialog::on_pushButtonLoad_clicked()
{
	Panel->LoadDefault();
	ShowData();
}

void LEDControl16HPrnDialog::on_pushButtonRequire_clicked()
{
	Panel->RequireGio();
	ShowData();
}

void LEDControl16HPrnDialog::on_pushButtonClose_clicked()
{
	done(true);
}

void LEDControl16HPrnDialog::on_pushButtonDefineSignals_clicked()
{
	DefineSignalDialog	D(Panel);
	D.exec();
}

void LEDControl16HPrnDialog::on_pushButtonShowTiming_clicked()
{
	Panel->ShowTimingChart();
	done(true);
}