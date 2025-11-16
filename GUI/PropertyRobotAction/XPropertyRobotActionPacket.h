#pragma once

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XRobotAction.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include <QColor>

class	RobotActionImagePanel;
class	CmdRobotActionDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	RobotActionImagePanel	*ImagePanelPoint;

	CmdRobotActionDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdRobotActionDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdSendAddManualRobotAction : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			LibID;

	GUICmdSendAddManualRobotAction(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedRobotAction : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	IntList		LayerList;

	GUICmdSendModifySelectedRobotAction(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdRobotActionClicked : public GUIDirectMessage
{
public:
	int						UniversalDx,UniversalDy;
	RobotActionImagePanel	*ImagePanelPoint;

	CmdRobotActionClicked(LayersBase *base):GUIDirectMessage(base){}
	CmdRobotActionClicked(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
