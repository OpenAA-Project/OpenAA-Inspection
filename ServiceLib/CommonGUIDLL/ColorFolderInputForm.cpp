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

#include "CommonGUIDLLResource.h"

#include "ColorFolderInputForm.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"

ColorFolderInputForm::ColorFolderInputForm(LayersBase *base,const QString &folderName ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	FolderName	=folderName;
	ui.EditFolderName	->setText(FolderName);
}

ColorFolderInputForm::~ColorFolderInputForm()
{

}

void ColorFolderInputForm::closeEvent ( QCloseEvent * event )
{
	QDialog::closeEvent (event);
	deleteLater ();
}

void ColorFolderInputForm::on_ButtonOK_clicked()
{
	FolderName	=ui.EditFolderName->text();
	done((int)true);

}

void ColorFolderInputForm::on_ButtonCancel_clicked()
{
	done((int)false);
}