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

#ifndef DISPLAYSERVER_H
#define DISPLAYSERVER_H

#include "displayserver_global.h"
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	DisplayServer :public GUIFormBase
{
    Q_OBJECT
	QLabel	HLabel;
public:
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	DisplayServer(LayersBase *Base ,QWidget *parent);
	
	virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;

private slots:
	void	ResizeAction();
};
#endif // DISPLAYSERVER_H