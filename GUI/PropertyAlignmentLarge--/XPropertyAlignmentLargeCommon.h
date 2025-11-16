#if	!defined(XPropertyAlignmentLargeCommon_H)
#define	XPropertyAlignmentLargeCommon_H

//#include "XGUIDLL.h"
//#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include "XGeneralFunc.h"

//=========================================================================

class	CmdSelectAlignmentLargeLibraryDialog : public GUIDirectMessage
{
public:
	int		LibID;

	CmdSelectAlignmentLargeLibraryDialog(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdSelectAlignmentLargeLibraryDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};

#endif