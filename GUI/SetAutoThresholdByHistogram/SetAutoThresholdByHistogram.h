#pragma once

#include "setautothresholdbyhistogram_global.h"

#include "XGUIPacketForDLL.h"

//--------------------------------------------------------------------------
class	CmdUpdateThresholdByHistogram : public GUIDirectMessage
{
public:
	CmdUpdateThresholdByHistogram(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateThresholdByHistogram(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};