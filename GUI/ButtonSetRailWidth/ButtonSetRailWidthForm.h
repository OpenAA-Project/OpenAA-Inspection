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


#ifndef BUTTONSETRAILWIDTHFORM_H
#define BUTTONSETRAILWIDTHFORM_H

#include "XGUIFormBase.h"
#include "ui_ButtonSetRailWidthForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ButtonSetRailWidthForm : public GUIFormBase
{
	Q_OBJECT

public:
	int32	InitialWidth;
	double	MaxSize;

	ButtonSetRailWidthForm(LayersBase *Base ,QWidget *parent = 0);
	~ButtonSetRailWidthForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

private:
	Ui::ButtonSetRailWidthFormClass ui;

private slots:
	void on_pushButtonSet_clicked();
};

#endif // BUTTONSETRAILWIDTHFORM_H