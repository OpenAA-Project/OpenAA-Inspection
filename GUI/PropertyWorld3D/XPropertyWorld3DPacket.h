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
#pragma once

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XWorld3D.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include <QColor>

class	World3DImagePanel;
class	CmdWorld3DDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	World3DImagePanel	*ImagePanelPoint;

	CmdWorld3DDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdWorld3DDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	GUICmdLoadStepFile : public GUICmdPacketBase
{
public:
	QByteArray	FArray;

	GUICmdLoadStepFile(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};