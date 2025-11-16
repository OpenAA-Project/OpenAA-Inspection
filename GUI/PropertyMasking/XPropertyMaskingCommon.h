#if	!defined(XPropertyMaskingCommon_H)
#define	XPropertyMaskingCommon_H

#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include "XGeneralFunc.h"
#include "XAlgorithmLibrary.h"

class	CmdSelectMaskingLibraryDialog : public GUIDirectMessage
{
public:
	int		LibID;

	CmdSelectMaskingLibraryDialog(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdSelectMaskingLibraryDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};


#endif