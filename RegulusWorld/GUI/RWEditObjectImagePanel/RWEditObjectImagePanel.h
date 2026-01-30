/*
 * Copyright (C) 2023
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

#include "rweditobjectimagepanel_global.h"
#include "XDisplayImage3D.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	RWEditObjectImagePanel : public GUIFormBase
{
	Q_OBJECT

	XDisplayImage3D5Panels	Panel;
public:
	RWEditObjectImagePanel(LayersBase *Base ,QWidget *parent);
	~RWEditObjectImagePanel(void){}

protected:
	virtual	void resizeEvent(QResizeEvent *event)	override;

};