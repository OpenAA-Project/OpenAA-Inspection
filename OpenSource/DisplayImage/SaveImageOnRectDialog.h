/*
 * Copyright (C) 2021
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

#ifndef SAVEIMAGEONRECTDIALOG_H
#define SAVEIMAGEONRECTDIALOG_H

#include <QDialog>
#include "ui_SaveImageOnRectDialog.h"

#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XServiceForLayers.h"

class	DisplayImage;

class SaveImageOnRectDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT
	DisplayImage	*ImageBase;

public:
	SaveImageOnRectDialog(DisplayImage *Base,QWidget *parent);
	~SaveImageOnRectDialog();

private:
	Ui::SaveImageOnRectDialogClass ui;

private slots:
	void on_pushButton_2_clicked();
	void on_pushButtonOK_clicked();
	void on_pushButtonTest_clicked();
};

#endif // SAVEIMAGEONRECTDIALOG_H