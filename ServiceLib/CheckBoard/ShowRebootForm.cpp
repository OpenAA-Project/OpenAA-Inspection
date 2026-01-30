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

#include "ShowRebootForm.h"
#include "ui_ShowRebootForm.h"

ShowRebootForm::ShowRebootForm(int ReasonIndex ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowRebootForm)
{
    ui->setupUi(this);
	setWindowFlags(Qt::WindowStaysOnTopHint);

	ui->stackedWidget->setCurrentIndex(ReasonIndex);

	TM.setInterval(5000);
	TM.setSingleShot(true);
	connect(&TM,SIGNAL(timeout()),this,SLOT(OnTimerTicked()));
	TM.start();
}

ShowRebootForm::~ShowRebootForm()
{
    delete ui;
}

void ShowRebootForm::OnTimerTicked()
{
	emit  SignalTimeUp();
}