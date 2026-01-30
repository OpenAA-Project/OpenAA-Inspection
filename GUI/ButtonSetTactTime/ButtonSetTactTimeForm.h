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


#ifndef BUTTONSETTACTTIMEFORM_H
#define BUTTONSETTACTTIMEFORM_H

#include "XGUIFormBase.h"
#include "ui_ButtonSetTactTimeForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ButtonSetTactTimeForm : public GUIFormBase
{
	Q_OBJECT

public:
	ButtonSetTactTimeForm(LayersBase *Base ,QWidget *parent = 0);
	~ButtonSetTactTimeForm();

	virtual void	BuildForShow(void)	override;
private:
	Ui::ButtonSetTactTimeFormClass ui;

private slots:
	void on_pushButtonSet_clicked();
};

#endif // BUTTONSETTACTTIMEFORM_H