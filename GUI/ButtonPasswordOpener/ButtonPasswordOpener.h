/*
 * Copyright (C) 2022
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

#ifndef BUTTONPASSWORDOPENER_H
#define BUTTONPASSWORDOPENER_H

#include "buttonpasswordopener_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include<QString>
#include<QWidget>
#include<QColor>
#include<QFont>
#include<QPushButton>
#include "mtToolButtonColored.h"

class ButtonPasswordOpener : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	ExpiredTimeSec;
	QColor	LockedColor;
	QColor	UnlockedColor;

	ButtonPasswordOpener(LayersBase *Base ,QWidget *parent);
	~ButtonPasswordOpener(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

protected:
	virtual	bool OnIdle(void)	override;
private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


#endif // BUTTONPASSWORDOPENER_H