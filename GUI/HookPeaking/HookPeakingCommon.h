#if	!defined(HookPeakingCommon_h)
#define	HookPeakingCommon_h

#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"

class	CmdSetPeaking : public GUIDirectMessage
{
public:
	double		Alpha;
	bool		Active;

	CmdSetPeaking(LayersBase *base):GUIDirectMessage(base){}
	CmdSetPeaking(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetPeaking : public GUIDirectMessage
{
public:
	double		Alpha;
	bool		Active;

	CmdGetPeaking(LayersBase *base):GUIDirectMessage(base){}
	CmdGetPeaking(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetPeakingColor : public GUIDirectMessage
{
public:
	QColor	Color;

	CmdSetPeakingColor(LayersBase *base):GUIDirectMessage(base){}
	CmdSetPeakingColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetPeakingColor : public GUIDirectMessage
{
public:
	QColor	Color;

	CmdGetPeakingColor(LayersBase *base):GUIDirectMessage(base){}
	CmdGetPeakingColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDrawPeaking : public GUIDirectMessage
{
public:
	QImage		*PntImage;
	QPainter	*Pnt;
	int		movx,movy;
	double	ZoomRate;

	CmdDrawPeaking(LayersBase *base):GUIDirectMessage(base){}
};

#endif