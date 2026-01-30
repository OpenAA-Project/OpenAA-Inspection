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

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XFlatInspectionLibrary.h"
#include "XFlatInspection.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include <QColor>

class	FlatInspectionImagePanel;
class	CmdFlatInspectionDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	FlatInspectionImagePanel	*ImagePanelPoint;

	CmdFlatInspectionDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdFlatInspectionDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdSendAddManualFlatInspection : public GUICmdPacketBase
{
public:
	int			LibID;
	FlexArea	Area;
	FlatInspectionItem::FlatInspectionType	FIType;

	GUICmdSendAddManualFlatInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdReqFIT_Type: public GUIDirectMessage
{
public:
	FlatInspectionItem::FlatInspectionType	FIT_Type;
	bool									ShowMaskMap;

	CmdReqFIT_Type(LayersBase *base):GUIDirectMessage(base){}
	CmdReqFIT_Type(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};