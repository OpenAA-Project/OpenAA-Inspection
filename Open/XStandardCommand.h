#if	!defined(XStandardCommand_h)
#define	XStandardCommand_h

#include "XGUIPacketForDLL.h"
#include <QString>

class	CmdGetLibName : public GUIDirectMessage
{
public:
	int		LibID;
	QString	LibName;
	CmdGetLibName(LayersBase *base):GUIDirectMessage(base){}
	CmdGetLibName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



#endif