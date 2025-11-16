#if	!defined(XVRSCONTROLCOMMAND_H)
#define	XVRSCONTROLCOMMAND_H

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QString>
#include "XGUIPacketForDLL.h"

class	CmdVRSOrigin : public GUIDirectMessage
{
public:

	CmdVRSOrigin(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdVRSEscape : public GUIDirectMessage
{
public:

	CmdVRSEscape(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdVRSMoveX : public GUIDirectMessage
{
public:
	int	Dx;

	CmdVRSMoveX(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdVRSMoveY : public GUIDirectMessage
{
public:
	int	Dy;

	CmdVRSMoveY(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdVRSMoveZ : public GUIDirectMessage
{
public:
	int	Dz;

	CmdVRSMoveZ(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdVRSMoveXY : public GUIDirectMessage
{
public:
	int	Dx;
	int	Dy;

	CmdVRSMoveXY(LayersBase *base)
		:GUIDirectMessage(base){}
};

#endif