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

#ifndef BUTTONANYMODE_H
#define BUTTONANYMODE_H

#include "buttonanymode_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

class	SignalOperandBit;

class	ButtonAnyMode : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
	DWORD	LastKeyTime;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;
	int32	SystemRegisterNo;
	int32	ShortcutKey;

	ButtonAnyMode(LayersBase *Base ,QWidget *parent);
	~ButtonAnyMode(void);
	
	virtual void	Prepare(void)	override;

private:
	SignalOperandBit	*ioMode;
	virtual	void	keyPressEvent ( QKeyEvent * event )	override;
private slots:
	void	SlotToggled ( bool checked );
	void	ResizeAction();
};
#endif // BUTTONANYMODE_H