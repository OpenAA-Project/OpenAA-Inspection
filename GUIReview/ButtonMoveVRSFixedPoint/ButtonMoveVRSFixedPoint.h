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

#ifndef BUTTONMOVEVRSFIXEDPOINT_H
#define BUTTONMOVEVRSFIXEDPOINT_H

#include "buttonmovevrsfixedpoint_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include <QEvent>
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	SignalOperandBit;
class	SignalOperandInt;

class	KeyedColorButton : public mtToolButtonColored
{
public:
	KeyedColorButton(bool ColorDialogOnLClick ,QWidget *parent = 0);
	KeyedColorButton(bool ColorDialogOnLClick ,const QColor &col ,QWidget *parent = 0);

	virtual	void leaveEvent ( QEvent * e )	override;
};

class	ButtonMoveVRSFixedPoint : public GUIFormBase
{
	Q_OBJECT

	KeyedColorButton	Button;

	SignalOperandBit	*oPushedOperand;
	SignalOperandInt	*iFixedXPos;
	SignalOperandInt	*iFixedYPos;

	int		LastX;
	int		LastY;
	DWORD	LastKeyTime;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	XPos,YPos;
	bool	AbsoluteMode;
	bool	ToggleMode;
	int32	SysBitNumber;
	int32	SysRegisterXPos;
	int32	SysRegisterYPos;
	bool	ReleaseButtonOnOtherOperation;
	int32	ShortcutKey;

	ButtonMoveVRSFixedPoint(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
private:
	virtual	void	keyPressEvent ( QKeyEvent * event )	override;
};

#endif // BUTTONMOVEVRSFIXEDPOINT_H