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


#ifndef SHOWMASTERNAMESFORM_H
#define SHOWMASTERNAMESFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowMasterNamesForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowMasterNamesForm : public GUIFormBase
{
	Q_OBJECT

public:
	QFont	TitleFont;
	QFont	DataFont;
	bool	ShowMasterID;
	bool	ShowMasterName;
	bool	ShowLotID;
	bool	ShowLotName;
	bool	ShowWorkerID;
	bool	ShowWorkerName;

	QString	TitleMasterID;
	QString	TitleMasterName;
	QString	TitleLotID;
	QString	TitleLotName;
	QString	TitleWorkerID;
	QString	TitleWorkerName;

	ShowMasterNamesForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowMasterNamesForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

private:
	Ui::ShowMasterNamesFormClass ui;
private slots:
	void	ResizeAction();
};

#endif // SHOWMASTERNAMESFORM_H