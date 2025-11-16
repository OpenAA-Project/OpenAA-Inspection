#if	!defined(XCommonFilterUDColorShift_h)
#define	XCommonFilterUDColorShift_h


#include "XGUIPacketForDLL.h"
#include "XDateTime.h"

class	CmdExecuteFilter : public GUIDirectMessage
{
public:
	int		VShift;
	CmdExecuteFilter(LayersBase *base):GUIDirectMessage(base){	VShift=0;	}
	CmdExecuteFilter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	VShift=0;	}
};

class	CmdExecuteClearFilter : public GUIDirectMessage
{
public:
	int		VShift;
	CmdExecuteClearFilter(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteClearFilter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecuteFilterEveryTime : public GUIDirectMessage
{
public:
	XDateTime	MasterTime;
	CmdExecuteFilterEveryTime(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteFilterEveryTime(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecuteClearFilterEveryTime : public GUIDirectMessage
{
public:
	XDateTime	MasterTime;
	CmdExecuteClearFilterEveryTime(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteClearFilterEveryTime(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif