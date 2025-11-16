#if	!defined(XCommonFilterMoveImage_h)
#define	XCommonFilterMoveImage_h


#include "XGUIPacketForDLL.h"
#include "XDateTime.h"

class	CmdFilterReqXY : public GUIDirectMessage
{
public:
	int		MovX,MovY;
	CmdFilterReqXY(LayersBase *base):GUIDirectMessage(base){	MovX=MovY=0;		}
	CmdFilterReqXY(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	MovX=MovY=0;	}
};

class	CmdFilterSetXY : public GUIDirectMessage
{
public:
	int		MovX,MovY;
	CmdFilterSetXY(LayersBase *base):GUIDirectMessage(base){	MovX=MovY=0;	}
	CmdFilterSetXY(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	MovX=MovY=0;	}
};


#endif