/*
 * Copyright (C) 2025
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

#include "counterimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XCounter.h"

class	CounterImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	CounterImagePanel(LayersBase *Base ,QWidget *parent);
	~CounterImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)			override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;

protected:
	virtual	void	resizeEvent(QResizeEvent *event)	override;
};