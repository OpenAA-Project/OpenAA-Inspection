#if	!defined(XStatusCommon_h)
#define	XStatusCommon_h

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	CmdShowMessage : public GUIDirectMessage
{
public:
	bool		HTMLMode;
	QString		Comment;

	CmdShowMessage(LayersBase *base):GUIDirectMessage(base){}
	CmdShowMessage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
