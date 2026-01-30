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
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XLearningRegist.h"


class	IntegrationCmdUpdateThreshold : public IntegrationCmdPacketBase
{
public:
	int		LibType;
	int		LibID;
	int		LearningMenuID;
	int		InspectionID;
	int		ShadowLevel		;
	int		ShadowNumber	;
	int		Phase;
	int		Page;
	int32	ItemID;		//-1:Adapt All items
	LearningResource	LRes;

	IntegrationCmdUpdateThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdReqLearningMenu: public IntegrationCmdPacketBase
{
public:
	int	LibType;

	IntegrationCmdReqLearningMenu(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdAckLearningMenu: public IntegrationCmdPacketBase
{
public:
	LearningMenu	LearningMenuDim[100];
	int32			MenuDimNumb;

	IntegrationCmdAckLearningMenu(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	CmdSetInvisibleAll: public GUIDirectMessage
{
public:
	CmdSetInvisibleAll(LayersBase *base):GUIDirectMessage(base){	}
	CmdSetInvisibleAll(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	}
};

class	CmdSetUpdateMode: public GUIDirectMessage
{
public:
	bool	StartUpdate;
	CmdSetUpdateMode(LayersBase *base):GUIDirectMessage(base){	}
	CmdSetUpdateMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	}
};

class	CmdPressLine: public GUIDirectMessage
{
public:
	int		MachineID;
	int		InspectionID;

	CmdPressLine(LayersBase *base):GUIDirectMessage(base){	}
	CmdPressLine(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	}
};

class	IntegrationCmdReqItemInfo: public IntegrationCmdPacketBase
{
public:
	int	LibType	;
	int	Phase	;
	int	Layer	;
	int	ItemID	;

	IntegrationCmdReqItemInfo(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName 
							,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdAckItemInfo: public IntegrationCmdPacketBase
{
public:
	ReportedTopicContainer ReportedContainer;

	IntegrationCmdAckItemInfo(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName
							,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};