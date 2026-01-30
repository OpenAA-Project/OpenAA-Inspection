/*
 * Copyright (C) 2020
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

#ifndef PROGRESSONIDLEFORM_H
#define PROGRESSONIDLEFORM_H

#include "ui_ProgressOnIdleForm.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class ProgressOnIdleForm : public GUIFormBase
{
	Q_OBJECT

public:
	ProgressOnIdleForm(LayersBase *Base,QWidget *parent = 0);
	~ProgressOnIdleForm();

private:
	Ui::ProgressOnIdleFormClass ui;

	bool OnIdle(void);

private slots:
	void	ResizeAction();
};

#endif // PROGRESSONIDLEFORM_H