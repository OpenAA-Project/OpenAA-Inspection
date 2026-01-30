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

#ifndef BUTTONSETMACHINE_H
#define BUTTONSETMACHINE_H

#include "buttonsetmachine_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	ButtonSetMachine : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	MachineID;

	ButtonSetMachine(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)		override;
	bool			SetMachineID(int ID);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	CmdButtonUp	:public GUIDirectMessage
{
public:
	CmdButtonUp(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONSETMACHINE_H