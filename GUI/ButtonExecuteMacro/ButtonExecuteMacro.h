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

#ifndef BUTTONEXECUTEMACRO_H
#define BUTTONEXECUTEMACRO_H

#include "buttonexecutemacro_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMacroExecuter.h"
#include "XExecuteBatch.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonExecuteMacro : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	//MacroSentenseContainer	SContainer;
	BatchContainer			BatchData;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	MacroFileName;
	QString	MacroFileNameByEditGUI;

	ButtonExecuteMacro(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

public slots:
	void	SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};

#endif // BUTTONEXECUTEMACRO_H