/*
 * Copyright (C) 2012
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

#ifndef FORMAUTOSAVEIMAGESELECTLOT_H
#define FORMAUTOSAVEIMAGESELECTLOT_H

#include <QDialog>
#include "ui_FormAutoSaveImageSelectLot.h"
#include "XServiceForLayers.h"
#include "XAutoSaveImage.h"

class FormAutoSaveImageSelectLot : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	FormAutoSaveImageSelectLot(LayersBase *Base ,QWidget *parent = 0);
	~FormAutoSaveImageSelectLot();

private:
	Ui::FormAutoSaveImageSelectLotClass ui;
	CmdGetLotStringList	RCmd;

private slots:
	void on_tableWidget_doubleClicked(QModelIndex);
	void on_pushButtonCancel_clicked();
	void on_pushButtonSelect_clicked();
};

#endif // FORMAUTOSAVEIMAGESELECTLOT_H