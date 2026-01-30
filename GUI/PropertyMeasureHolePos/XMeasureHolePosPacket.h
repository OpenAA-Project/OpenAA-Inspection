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

#ifndef XMeasureHolePosPACKET_H
#define XMeasureHolePosPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "NListComp.h"
#include "XMeasureHolePos.h"

class	MeasureHolePosDrawAttr;


//===========================================================================

class	CmdMeasureHolePosDrawModePacket : public GUIDirectMessage
{
public:
	MeasureHolePosDrawAttr	*DrawAttr;

	CmdMeasureHolePosDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	MeasureHolePosImagePanel;
class	CmdMeasureHolePosDrawEnd : public GUIDirectMessage
{
public:
	VectorLineBase	*Vector;
	FlexArea		Area;
	MeasureHolePosImagePanel	*ImagePanelPoint;

	CmdMeasureHolePosDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdMeasureHolePosGetColorMap : public GUIDirectMessage
{
public:
	FlexArea	Area;
	MeasureHolePosImagePanel	*ImagePanelPoint;

	GUICmdMeasureHolePosGetColorMap(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSendAddManualMeasureHolePos : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;
	VectorLineBase		*Vector;

	GUICmdSendAddManualMeasureHolePos(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendAddManualMeasureHolePos(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdReqMeasureHolePosColorMap : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	CmdReqMeasureHolePosColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdAckMeasureHolePosColorMap : public GUICmdPacketBase
{
public:
	ColorLogic	Color;

	CmdAckMeasureHolePosColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqItemList : public GUICmdPacketBase
{
public:
	GUICmdReqItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendItemList : public GUICmdPacketBase
{
public:
	HolePosListForPacketPack	ListInfo;

	GUICmdSendItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeList(int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===========================================================================

class	GUICmdReqItemThreshold : public GUICmdPacketBase
{
public:
	int		ItemID;

	GUICmdReqItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendItemThreshold : public GUICmdPacketBase
{
public:
	QString					ItemName;
	MeasureHolePosThreshold	*Thre;

	GUICmdSendItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendItemThreshold(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetItemThreshold : public GUICmdPacketBase
{
public:
	int						ItemID;
	QString					ItemName;
	MeasureHolePosThreshold	*Thre;

	GUICmdSetItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSetItemThreshold(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif