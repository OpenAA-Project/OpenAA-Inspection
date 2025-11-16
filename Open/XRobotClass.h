#pragma once

#include <QtGui>
//#include <QSqlDatabase>
#include <QLibrary>
#include <QMutex>
#include <QString>
#include <QIODevice>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "X3DCommon.h"

class	GUIDirectMessage;
class	RobotFigure;

enum EnumRobotEvent
{
	_Robot_NoProblem
	,_Robot_DoneMotion
	,_Robot_CommandError
	,_Robot_Error
	,_Robot_Input
};


class RobotFigure
{
public:
	Point3D	Position;
	Angle3D	Angle	;

	RobotFigure(void);
	RobotFigure(const RobotFigure &src);

	RobotFigure	&operator=(const RobotFigure &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//----------------------------------------------------------------------------------------------------

class	RobotDLLBaseClass: public QWidget 
							,public IdentifiedClass
							,public ServiceForLayers
{
	Q_OBJECT
public:
	RobotDLLBaseClass(QWidget *parent ,LayersBase *base):QWidget(parent),ServiceForLayers(base){}
	virtual	~RobotDLLBaseClass(void){}

	virtual	bool	Initial(void)	{	return true;	}
	virtual	bool	Close(void)		{	return true;	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
	virtual	void	LoopOnIdle(void){}

	virtual	bool	Save(QIODevice *f)						=0;
	virtual	bool	Load(QIODevice *f)						=0;

	virtual	bool	ShowSettingDialog(void)					=0;

	virtual	bool	MotionMove(RobotFigure &target ,float Speed)				{	return true;	}
	virtual	bool	MotionMove(RobotFigure target[],int PointCount ,float Speed){	return true;	}
	virtual	bool	GetFigure(RobotFigure &CurrentFigure)						{	return false;	}
	virtual	bool	GetButtonState(bool Buttons[])								{	return false;	}
	virtual	bool	SetDragMode(bool EnableDrag)								{	return false;	}
	virtual	bool	TrajectoryStart(const QString &FileName)					{	return false;	}
	virtual	bool	TrajectoryEnd(void)											{	return false;	}
	virtual	bool	StartTrajectory(const QString &FileName)					{	return false;	}


	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)				{	return true;	}
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb){	return true;	}
	virtual	bool	Reallocate(int newPhaseNumb)									{	return true;	}

signals:
	void	SignalRobotEvent(EnumRobotEvent &ev);
};

//----------------------------------------------------------------------------------------------------

