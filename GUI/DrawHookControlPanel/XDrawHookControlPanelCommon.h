#if	!defined(XDrawHookControlPanelCommon_H)
#define	XDrawHookControlPanelCommon_H

#include "XGUIPacketForDLL.h"
#include "XFlexArea.h"


class	CmdDHControlPanel_SetType : public GUIDirectMessage
{
public:
	int		DrawType;	//0:Line	1:Draw	2:Text

	CmdDHControlPanel_SetType(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_SetType(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_SetLineType : public GUIDirectMessage
{
public:
	int		LineType;

	CmdDHControlPanel_SetLineType(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_SetLineType(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_SetLineWidth : public GUIDirectMessage
{
public:
	int		LineWidth;

	CmdDHControlPanel_SetLineWidth(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_SetLineWidth(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_SetLineColor : public GUIDirectMessage
{
public:
	QColor	LineColor;

	CmdDHControlPanel_SetLineColor(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_SetLineColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_GetLineColor : public GUIDirectMessage
{
public:
	QColor	LineColor;

	CmdDHControlPanel_GetLineColor(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_GetLineColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_GetDrawColor : public GUIDirectMessage
{
public:
	QColor	LineColor;
	QColor	InsideColor;

	CmdDHControlPanel_GetDrawColor(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_GetDrawColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDHControlPanel_SetLineStartType : public GUIDirectMessage
{
public:
	int		LineStartType;

	CmdDHControlPanel_SetLineStartType(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_SetLineStartType(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_SetLineEndType : public GUIDirectMessage
{
public:
	int		LineEndType;

	CmdDHControlPanel_SetLineEndType(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_SetLineEndType(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//--------------------

class	CmdDHControlPanel_SetDrawType : public GUIDirectMessage
{
public:
	int		DrawType;

	CmdDHControlPanel_SetDrawType(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_SetDrawType(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_SetDrawLineWidth : public GUIDirectMessage
{
public:
	int		DrawLineWidth;

	CmdDHControlPanel_SetDrawLineWidth(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_SetDrawLineWidth(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_SetDrawLineColor : public GUIDirectMessage
{
public:
	QColor		DrawLineColor;
	bool		ChangeSelection;
	CmdDHControlPanel_SetDrawLineColor(LayersBase *base):GUIDirectMessage(base){	ChangeSelection=false;	}
	CmdDHControlPanel_SetDrawLineColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ChangeSelection=false;	}
};

class	CmdDHControlPanel_SetDrawInsideType : public GUIDirectMessage
{
public:
	int		DrawInsideType;

	CmdDHControlPanel_SetDrawInsideType(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_SetDrawInsideType(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_SetDrawInsideColor : public GUIDirectMessage
{
public:
	QColor		DrawInsideColor;
	bool		ChangeSelection;
	CmdDHControlPanel_SetDrawInsideColor(LayersBase *base):GUIDirectMessage(base){	ChangeSelection=false;	}
	CmdDHControlPanel_SetDrawInsideColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ChangeSelection=false;	}
};

//--------------------
class	CmdDHControlPanel_SelectTextFont : public GUIDirectMessage
{
public:
	QFont	TextFont;

	CmdDHControlPanel_SelectTextFont(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_SelectTextFont(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_SetTextFont : public GUIDirectMessage
{
public:
	QFont	TextFont;
	bool		ChangeSelection;
	CmdDHControlPanel_SetTextFont(LayersBase *base):GUIDirectMessage(base)			{	ChangeSelection=false;	}
	CmdDHControlPanel_SetTextFont(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	ChangeSelection=false;	}
};

class	CmdDHControlPanel_SetTextColor : public GUIDirectMessage
{
public:
	QColor		TextColor;
	bool		ChangeSelection;
	CmdDHControlPanel_SetTextColor(LayersBase *base):GUIDirectMessage(base)			{	ChangeSelection=false;	}
	CmdDHControlPanel_SetTextColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	ChangeSelection=false;	}
};

class	CmdDHControlPanel_GetTextColor : public GUIDirectMessage
{
public:
	QColor		TextColor;

	CmdDHControlPanel_GetTextColor(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_GetTextColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//--------------------

class	CmdDHControlPanel_ExeNew : public GUIDirectMessage
{
public:
	CmdDHControlPanel_ExeNew(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_ExeNew(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_ExeSelect : public GUIDirectMessage
{
public:
	bool	MoveMode;

	CmdDHControlPanel_ExeSelect(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_ExeSelect(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_ExeDel : public GUIDirectMessage
{
public:
	CmdDHControlPanel_ExeDel(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_ExeDel(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdDHControlPanel_ExeCancel : public GUIDirectMessage
{
public:
	CmdDHControlPanel_ExeCancel(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_ExeCancel(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_Transform: public GUIDirectMessage
{
public:
	double	m[6];
	CmdDHControlPanel_Transform(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_Transform(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDHControlPanel_MakeFlexArea: public GUIDirectMessage
{
public:
	FlexArea	Area;
	CmdDHControlPanel_MakeFlexArea(LayersBase *base):GUIDirectMessage(base){}
	CmdDHControlPanel_MakeFlexArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif