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