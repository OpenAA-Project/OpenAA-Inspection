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

#ifndef MANUALINPUTFORM_H
#define MANUALINPUTFORM_H

#include <QDialog>
#include "ui_ManualInputForm.h"
#include "XTypeDef.h"
#include "XServiceForLayers.h"

class ManualInputForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	ManualInputForm(LayersBase *base, QWidget *parent);
	~ManualInputForm();

	bool		Ok;			//true:�����r��		false:�m�f����
    int32		NGLevel;	//0:Most important NG 1,2,3...lighter

private:
	Ui::ManualInputFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // MANUALINPUTFORM_H