#pragma once
#include "XGUIPacketForDLL.h"


class	CmdReqRealtimeGraphCamera: public GUIDirectMessage
{
public:
	int		CamNo;
	bool	Capturing;

	CmdReqRealtimeGraphCamera(LayersBase *base):GUIDirectMessage(base){}
	CmdReqRealtimeGraphCamera(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
