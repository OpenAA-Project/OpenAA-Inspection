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

#ifndef BUTTONOUTLINEOFFSETWINDOW_H
#define BUTTONOUTLINEOFFSETWINDOW_H

#include "buttonoutlineoffsetwindow_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	OutlineOffsetForm;

class	ButtonOutlineOffsetWindow: public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	OutlineOffsetForm	*Window;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonOutlineOffsetWindow(LayersBase *Base ,QWidget *parent);
	~ButtonOutlineOffsetWindow(void);
	
	virtual void	Prepare(void)	override;
private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
};

#endif // BUTTONOUTLINEOFFSETWINDOW_H