/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
