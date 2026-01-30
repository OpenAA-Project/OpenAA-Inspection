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
#include "XColorCorrector.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XGUI.h"


class	CmdColorCorrectorDrawModePacket : public GUIDirectMessage
{
public:
	ColorCorrectorType	VType;

	CmdColorCorrectorDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdColorCorrectorDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ColorCorrectorImagePanel;
class	CmdColorCorrectorDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	ColorCorrectorImagePanel	*ImagePanelPoint;

	CmdColorCorrectorDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdColorCorrectorDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdSendAddManualColorCorrector : public GUICmdPacketBase
{
public:
	int			Phase;
	QByteArray	BItem;
	FlexArea	Area;
	ColorCorrectorType	VType;

	GUICmdSendAddManualColorCorrector(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedColorCorrector : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	IntList		LayerList;

	GUICmdSendModifySelectedColorCorrector(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class ColorCorrectorGridList : public NPListSaveLoad<ColorCorrectorGridList>
{
public:
	int		Phase	;
	int		Page	;
	int		ItemID	;
	int32	x1,y1,x2,y2;

	ColorCorrectorGridList(void){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};
class ColorCorrectorGridListContainer : public NPListPackSaveLoad<ColorCorrectorGridList>
{
public:
	ColorCorrectorGridListContainer(void){}
	virtual	ColorCorrectorGridList	*Create(void)	{	return new ColorCorrectorGridList();	}
};

class	GUICmdReqGridList : public GUICmdPacketBase
{
public:
	int32					Phase;
	ColorCorrectorType	VType;

	GUICmdReqGridList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckGridList : public GUICmdPacketBase
{
public:
	ColorCorrectorGridListContainer	ListData;

	GUICmdAckGridList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==========================================================================================

class	GUICmdReqColorCorrectorItemData : public GUICmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	ItemID;

	GUICmdReqColorCorrectorItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckColorCorrectorItemData : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;

	GUICmdAckColorCorrectorItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetColorCorrectorItemData : public GUICmdPacketBase
{
public:
	int			Phase;
	int			Page;
	int			ItemID;
	QByteArray	BItem;

	GUICmdSetColorCorrectorItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdDeleteColorCorrectorItem: public GUICmdPacketBase
{
public:
	int			Phase;
	int			Page;
	int			ItemID;

	GUICmdDeleteColorCorrectorItem(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
