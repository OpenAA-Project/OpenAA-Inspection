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

#include "DisplayImageResource.h"
#include "SaveImageOnRectDialog.h"
#include "XDisplayImage.h"

SaveImageOnRectDialog::SaveImageOnRectDialog(DisplayImage *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base->GetLayersBase())
{
	ui.setupUi(this);
	ImageBase=Base;
	ui.lineEditFormat->setText(ImageBase->FormatStrOnRect);
}

SaveImageOnRectDialog::~SaveImageOnRectDialog()
{

}


void SaveImageOnRectDialog::on_pushButtonTest_clicked()
{

}

void SaveImageOnRectDialog::on_pushButtonOK_clicked()
{
	ImageBase->FormatStrOnPoint		=ui.lineEditFormat->text();
	done(true);
}

void SaveImageOnRectDialog::on_pushButton_2_clicked()
{
	done(false);
}