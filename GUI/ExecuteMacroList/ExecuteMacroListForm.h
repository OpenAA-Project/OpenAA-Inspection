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

#ifndef EXECUTEMACROLISTFORM_H
#define EXECUTEMACROLISTFORM_H

#include "XGUIFormBase.h"
#include "ui_ExecuteMacroListForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMacroExecuter.h"

class ExecuteMacroListForm : public GUIFormBase
{
	Q_OBJECT

	MacroSentenseContainer	SContainer;

public:
	ExecuteMacroListForm(LayersBase *Base ,QWidget *parent = 0);
	~ExecuteMacroListForm();

private:
	Ui::ExecuteMacroListFormClass ui;

	void ShowList(void);
	volatile	bool	CancelMode;

private slots:
	void on_pushButtonStopExecute_clicked();
	void on_pushButtonStartExecute_clicked();
	void on_pushButtonLoadMacro_clicked();
};

#endif // EXECUTEMACROLISTFORM_H