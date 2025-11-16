#if	!defined(XFrameDefCommon_h)
#define	XFrameDefCommon_h

#include "XGUIPacketForDLL.h"

class	CmdReqShowInitial : public GUIDirectMessage
{
public:

	CmdReqShowInitial(LayersBase *base):GUIDirectMessage(base){}
	CmdReqShowInitial(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif