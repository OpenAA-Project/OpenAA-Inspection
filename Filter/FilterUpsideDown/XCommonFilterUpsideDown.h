#if	!defined(XCOMMONFILTERUPSIDEDOWN_H)
#define	XCOMMONFILTERUPSIDEDOWN_H

#include "XGUIPacketForDLL.h"

class	CmdExecuteFilter : public GUIDirectMessage
{
public:
	CmdExecuteFilter(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteFilter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdExecuteClearFilter : public GUIDirectMessage
{
public:
	CmdExecuteClearFilter(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteClearFilter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif