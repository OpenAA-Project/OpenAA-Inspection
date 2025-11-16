#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "ReviewStructureItems.h"
#include "../XGUIReviewCommonPacket.h"

class GUICmdReqStaticMachineID : public GUIDirectMessage
{
public:
	// Send
	int32		DefaultTopMachineID;
	int32		DefaultBottomMachineID;	

public:
	GUICmdReqStaticMachineID(LayersBase *base):GUIDirectMessage(base),DefaultTopMachineID(-1),DefaultBottomMachineID(-1){}
	GUICmdReqStaticMachineID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase),DefaultTopMachineID(-1),DefaultBottomMachineID(-1){}
};
