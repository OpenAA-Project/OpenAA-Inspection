/*
 * Copyright (C) 2023
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

#include "LearningSettingDialog.h"
#include "WEditParameterTab.h"
#include "XDataInLayer.h"

LearningSettingDialog::LearningSettingDialog(LayersBase *_Base,ParamBase *base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(_Base)
{
	ui.setupUi(this);
	Base=base;

	WTabGeneral=new WEditParameterTab(Base ,-1,ui.frame);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(ui.frame->width(),ui.frame->height());

}

LearningSettingDialog::~LearningSettingDialog()
{

}


void LearningSettingDialog::on_ButtonOK_clicked()
{
	WTabGeneral->LoadFromWindow();
	Base->SaveDefault(GetLayersBase()->GetUserPath());
	done(true);
}

void LearningSettingDialog::on_ButtonCancel_clicked()
{
	done(false);
}