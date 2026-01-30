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

#pragma once

#include "buttoncopyshadowtreealgorithm_global.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"


class  ButtonCopyShadowTreeAlgorithm: public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonCopyShadowTreeAlgorithm(LayersBase *Base ,QWidget *parent);
	~ButtonCopyShadowTreeAlgorithm(void);

	virtual	void	Prepare(void)		override;

private slots:
	void SlotClicked (int ButtonNumber);
	void	ResizeAction();
};