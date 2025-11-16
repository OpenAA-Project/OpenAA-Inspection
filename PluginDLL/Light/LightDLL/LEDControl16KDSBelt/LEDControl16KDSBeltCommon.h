#pragma once
#include "XGUIPacketForDLL.h"

class	CmdReqIsConnected : public GUIDirectMessage
{
public:
	bool	Connected;

	CmdReqIsConnected(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdStartSequence : public GUIDirectMessage
{
public:
	CmdStartSequence(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdEndSequence : public GUIDirectMessage
{
public:
	CmdEndSequence(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdReqEncoderPulse : public GUIDirectMessage
{
public:
	int		EncoderPulse;

	CmdReqEncoderPulse(LayersBase *base)
		:GUIDirectMessage(base){}
};