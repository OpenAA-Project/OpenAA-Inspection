#if	!defined(XCMDPANELPARAM_H)
#define	XCMDPANELPARAM_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class CmdPanelParam : public GUIDirectMessage
{
public :
	int nStartX;
	int nStartY;
	int nWidth;
	int nHeight;

	CmdPanelParam(LayersBase *base):GUIDirectMessage(base){}
};
#endif