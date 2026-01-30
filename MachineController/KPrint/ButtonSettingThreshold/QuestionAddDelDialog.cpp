/*
 * Copyright (C) 2025
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

#include "ButtonSettingThresholdResource.h"
#include "QuestionAddDelDialog.h"
#include "ui_QuestionAddDelDialog.h"
#include "XGeneralFunc.h"

QuestionAddDelDialog::QuestionAddDelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionAddDelDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SetWidgetCenter(this);
}

QuestionAddDelDialog::~QuestionAddDelDialog()
{
    delete ui;
}

void QuestionAddDelDialog::on_toolButtonOK_clicked()
{
	done(1);
}

void QuestionAddDelDialog::on_toolButtonNG_clicked()
{
	done(2);
}

void QuestionAddDelDialog::on_toolButtonCancel_clicked()
{
	done(0);
}