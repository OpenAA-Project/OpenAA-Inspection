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
#define ShowTopBottomSideInfoForm_H

#include "XGUIFormBase.h"
#include "ui_ShowTopBottomSideInfoForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowTopBottomSideInfoForm: public GUIFormBase
{
	Q_OBJECT

public:
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

	ShowTopBottomSideInfoForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowTopBottomSideInfoForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

private:
	Ui::ShowTopBottomSideInfoFormClass ui;
private slots:
	void	ResizeAction();
};

#endif // ShowTopBottomSideInfoForm_H