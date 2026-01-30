/*
 * Copyright (C) 2021
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

#include "splitter_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QSplitter>

class Splitter :public GUIFormBase
{
	Q_OBJECT

	QSplitter	SplitterInst;
	bool		FirstMode;
	GUIFormBase	*Child1;
	GUIFormBase	*Child2;
public:
	QString		Direction;
	QString		ChildInst1;
	QString		ChildInst2;

	Splitter(LayersBase *Base ,QWidget *parent = 0);

	virtual void	ReadyParam(void)override;

private:
private slots:
	void	ResizeAction();
};
