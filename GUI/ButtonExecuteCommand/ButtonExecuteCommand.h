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

#ifndef BUTTONEXECUTECOMMAND_H
#define BUTTONEXECUTECOMMAND_H

#include "buttonexecutecommand_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonExecuteCommand : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	QString		ExecutableProgram;
	QStringList	ArgumentParam;
	QString		WorkingPath;

	ButtonExecuteCommand(LayersBase *Base ,QWidget *parent);
	~ButtonExecuteCommand(void);
	virtual void	Prepare(void)	override;

	void	Execute(void);
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

#endif // BUTTONEXECUTECOMMAND_H