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
#include "XCheckDataValidation.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XCheckDataValidation.h"
#include "XGUI.h"


class	CmdCheckDataValidationDrawModePacket : public GUIDirectMessage
{
public:
	CheckDataValidationType	VType;

	CmdCheckDataValidationDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCheckDataValidationDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CheckDataValidationImagePanel;
class	CmdCheckDataValidationDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	CheckDataValidationImagePanel	*ImagePanelPoint;

	CmdCheckDataValidationDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdCheckDataValidationDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdSendAddManualCheckDataValidation : public GUICmdPacketBase
{
public:
	int			Phase;
	QByteArray	BItem;
	FlexArea	Area;
	IntList		LayerList;
	int32		LibType;
	int32		LibID;
	CheckDataValidationType	VType;

	GUICmdSendAddManualCheckDataValidation(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedCheckDataValidation : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	IntList		LayerList;

	GUICmdSendModifySelectedCheckDataValidation(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqGridList : public GUICmdPacketBase
{
public:
	int32					Phase;
	CheckDataValidationType	VType;

	GUICmdReqGridList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckGridList : public GUICmdPacketBase
{
public:
	CheckDataValidationGridListContainer	ListData;

	GUICmdAckGridList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==========================================================================================

class	GUICmdReqCheckDataValidationItemData : public GUICmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	ItemID;

	GUICmdReqCheckDataValidationItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckCheckDataValidationItemData : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;
	int32		LibType;
	int32		LibID;

	GUICmdAckCheckDataValidationItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetCheckDataValidationItemData : public GUICmdPacketBase
{
public:
	int			Phase;
	int			Page;
	int			ItemID;
	QByteArray	BItem;
	int32		LibType;
	int32		LibID;

	GUICmdSetCheckDataValidationItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdDeleteCheckDataValidationItem: public GUICmdPacketBase
{
public:
	int			Phase;
	int			Page;
	int			ItemID;

	GUICmdDeleteCheckDataValidationItem(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==========================================================================================

class ThresholdMemberList : public NPListSaveLoad<ThresholdMemberList>
{
public:
	QString			MemberName;
	DirectValueType	VType;

	ThresholdMemberList(void){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class ThresholdMemberListContainer : public NPListPackSaveLoad<ThresholdMemberList>
{
public:
	ThresholdMemberListContainer(void){}

	virtual	ThresholdMemberList	*Create(void)	{	return new ThresholdMemberList();	}
};


class	GUICmdReqThresholdMemberString : public GUICmdPacketBase
{
public:
	int32		LibType;
	int32		LibID;

	GUICmdReqThresholdMemberString(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckThresholdMemberString : public GUICmdPacketBase
{
public:
	ThresholdMemberListContainer	LContainer;

	GUICmdAckThresholdMemberString(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};