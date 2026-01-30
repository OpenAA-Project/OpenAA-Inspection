/*
 * Copyright (C) 2017
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

#ifndef CHOOSEITEMTYPEFORM_H
#define CHOOSEITEMTYPEFORM_H

#include <QDialog>
#include "ui_ChooseItemTypeForm.h"
#include "XServiceForLayers.h"

class ChooseItemTypeForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	ChooseItemTypeForm(LayersBase *base, QWidget *parent = 0);
	~ChooseItemTypeForm();

	enum	ItemType{
		Type_Pad	=1
		,Type_Line	=2
		,Type_Matching	=3
	};

private:
	Ui::ChooseItemTypeFormClass ui;

private slots:
	void on_toolButtonMatchingLine_clicked();
	void on_toolButtonLine_clicked();
	void on_toolButtonPad_clicked();
};

#endif // CHOOSEITEMTYPEFORM_H