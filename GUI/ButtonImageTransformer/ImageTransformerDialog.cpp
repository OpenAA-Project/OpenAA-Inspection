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

#include "ButtonImageTransformerResource.h"
#include "ImageTransformerDialog.h"
#include "ui_ImageTransformerDialog.h"
#include "XGeneralFunc.h"

ImageTransformerDialog::ImageTransformerDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::ImageTransformerDialog)
{
    ui->setupUi(this);

	QStringList	S;
	for(int page=0;page<GetPageNumb();page++){
		S.append(QString(/**/"Page ")+QString::number(page));
	}
	ui->listWidgetPages->addItems(S);
	MasterImage=true;
	TargetImage=true;
	InstallOperationLog(this);
}

ImageTransformerDialog::~ImageTransformerDialog()
{
    delete ui;
}

void ImageTransformerDialog::on_pushButton_3_clicked()
{
	done(-1);
}

void ImageTransformerDialog::on_pushButtonUpsideDown_clicked()
{
	::GetSelectedRows(ui->listWidgetPages,SelectedPages);
	MasterImage	=	ui->checkBoxMasterImage->isChecked();
	TargetImage	=	ui->checkBoxTargetImage->isChecked();
	done(1);
}

void ImageTransformerDialog::on_pushButtonLeftsideRight_clicked()
{
	::GetSelectedRows(ui->listWidgetPages,SelectedPages);
	MasterImage	=	ui->checkBoxMasterImage->isChecked();
	TargetImage	=	ui->checkBoxTargetImage->isChecked();
	done(2);
}