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

#include "ButtonSettingColorDifferenceResource.h"
#include "ButtonSettingColorDifferenceForm.h"
#include "ui_ButtonSettingColorDifferenceForm.h"
#include "SettingColorDifferenceDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ButtonSettingColorDifferenceForm::ButtonSettingColorDifferenceForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ButtonSettingColorDifferenceForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SlaveNo=0;
	Msg=/**/"Set Threshold";
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSettingColorDifferenceForm::~ButtonSettingColorDifferenceForm()
{
    delete ui;
}
void	ButtonSettingColorDifferenceForm::Prepare(void)
{
	ui->PushButtonThreshold->setText(Msg);
	ui->PushButtonThreshold->setFont (CFont);
	ResizeAction();
}
void	ButtonSettingColorDifferenceForm::ResizeAction()
{
	ui->PushButtonThreshold->resize(width(),height());
}

void ButtonSettingColorDifferenceForm::on_PushButtonThreshold_clicked()
{
	SettingColorDifferenceDialog	D(GetLayersBase(),this);
	D.exec();
	//delete	D;
}