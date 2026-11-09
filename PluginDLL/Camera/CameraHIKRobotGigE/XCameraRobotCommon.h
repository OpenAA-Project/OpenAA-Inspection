#pragma once
#include "XGUIPacketForDLL.h"

class	CmdSetContinuousMode : public GUIDirectMessage
{
public:
	bool	ContinuousON;

	CmdSetContinuousMode(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetCaptureOne : public GUIDirectMessage
{
public:
	int		Index;
	CmdSetCaptureOne(LayersBase *base):GUIDirectMessage(base){	Index=-1;	}
};

class	CmdReqCaptureClosed : public GUIDirectMessage
{
public:
	float	Pos[6];
	float	CompareParamJ[6];
	int		Index;
	double	MinD;
	CmdReqCaptureClosed(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdResetCounter: public GUIDirectMessage
{
public:
	CmdResetCounter(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqCapturedCount: public GUIDirectMessage
{
public:
	qint64	CapturedCount;
	CmdReqCapturedCount(LayersBase *base):GUIDirectMessage(base){}
};

class JointFrameClass
{
public:
	float	CurrentPos[6];
	int		Index;

	JointFrameClass(){}
};


class	CmdReqJointFrameClass: public GUIDirectMessage
{
public:
	JointFrameClass	*Dim;
	int				DimCount;

	CmdReqJointFrameClass(LayersBase *base):GUIDirectMessage(base){	Dim=NULL;	}
	~CmdReqJointFrameClass(void)
	{
		if(Dim!=NULL){
			delete	[]Dim;
			Dim=NULL;
		}
	}
};

class	CmdLockCapture: public GUIDirectMessage
{
public:
	CmdLockCapture(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdUnlockCapture: public GUIDirectMessage
{
public:
	CmdUnlockCapture(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdImageToTarget: public GUIDirectMessage
{
public:
	int TargetPhase ,TargetPage;
	int		Index;

	CmdImageToTarget(LayersBase *base):GUIDirectMessage(base){}
};