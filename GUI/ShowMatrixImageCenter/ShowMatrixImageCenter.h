#ifndef SHOWMATRIXIMAGECENTER_H
#define SHOWMATRIXIMAGECENTER_H

#include "showmatriximagecenter_global.h"
#include "XGUIPacketForDLL.h"

class	CmdSetCenterInImage : public GUIDirectMessage
{
public:
	int	x,y;

	CmdSetCenterInImage(LayersBase *base):GUIDirectMessage(base){}
	CmdSetCenterInImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqCenterInImage : public GUIDirectMessage
{
public:
	int	x,y;

	CmdReqCenterInImage(LayersBase *base):GUIDirectMessage(base){	x=y=0;	}
	CmdReqCenterInImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	x=y=0;	}
};

#endif // SHOWMATRIXIMAGECENTER_H
