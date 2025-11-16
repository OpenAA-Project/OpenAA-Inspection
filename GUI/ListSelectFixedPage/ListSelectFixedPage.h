#pragma once

#include "XGUIPacketForDLL.h"

//--------------------------------------------------------------------------
class	CmdGetCurrentPage : public GUIDirectMessage
{
public:
	int	CurrentPage;

	CmdGetCurrentPage(LayersBase *base):GUIDirectMessage(base){}
	CmdGetCurrentPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//--------------------------------------------------------------------------
class	CmdSetCurrentPage : public GUIDirectMessage
{
public:
	int	CurrentPage;

	CmdSetCurrentPage(LayersBase *base):GUIDirectMessage(base){}
	CmdSetCurrentPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

