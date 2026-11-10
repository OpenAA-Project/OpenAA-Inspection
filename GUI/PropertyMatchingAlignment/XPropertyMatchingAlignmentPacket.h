#pragma once

#include "XGUIPacketForDLL.h"

class	DisplayModeOfMatchingAlignment : public GUIDirectMessage
{
public:
	bool	ModeSpecified;
	DisplayModeOfMatchingAlignment(LayersBase *base):GUIDirectMessage(base){}
};

