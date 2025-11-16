#pragma once

#include "buttonaddsubpage_global.h"
#include "XGUIPacketForDLL.h"

//--------------------------------------------------------------------------
class	CmdAddPage : public GUIDirectMessage
{
public:
	CmdAddPage(LayersBase *base):GUIDirectMessage(base){}
	CmdAddPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdSubPage : public GUIDirectMessage
{
public:
	CmdSubPage(LayersBase *base):GUIDirectMessage(base){}
	CmdSubPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertPage : public GUIDirectMessage
{
public:
	int	IndexPage;	//Insert forwarder

	CmdInsertPage(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRemovePage : public GUIDirectMessage
{
public:
	int	IndexPage;

	CmdRemovePage(LayersBase *base):GUIDirectMessage(base){}
	CmdRemovePage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
