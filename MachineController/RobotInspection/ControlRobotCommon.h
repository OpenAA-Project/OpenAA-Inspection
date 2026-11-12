#pragma once

#include <QIODevice>
#include "NListComp.h"

#define CommRobotSocket   "CommRobotSocket"
#define SharedMemoryKey   "SharedMemoryRobot"

typedef struct JointPos
{
	double jPos[6];   /* Six joint positions, unit: deg */
	JointPos(double J1, double J2, double J3, double J4, double J5, double J6)
	{
		jPos[0] = J1;
		jPos[1] = J2;
		jPos[2] = J3;
		jPos[3] = J4;
		jPos[4] = J5;
		jPos[5] = J6;
	}

	JointPos()
	{

	}
}JointPos;



class SplinePointList : public NPListSaveLoad<SplinePointList>
{
public:
	JointPos	JPos;
	bool		CapturePoint;

	SplinePointList(void){	CapturePoint=false;	}
	SplinePointList(const SplinePointList &src);

	SplinePointList	&operator=(const SplinePointList &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class SplinePointListContainer : public NPListPackSaveLoad<SplinePointList>
{
public:
	SplinePointListContainer(void){}
	SplinePointListContainer(const SplinePointListContainer &src);

	virtual	SplinePointList	*Create(void)	{	return new SplinePointList();	}

	SplinePointListContainer	&operator=(const SplinePointListContainer &src);
};

/*
double	GetDistanceXYZ(DescPose &s1,DescPose &s2);
double	GetDistancePQR(DescPose &s1,DescPose &s2);
double	GetDistanceXYZ(JointPos &s1,JointPos &s2);
double	GetDistancePQR(JointPos &s1,JointPos &s2);

bool	Save(QIODevice *f,const DescPose &a);
bool	Load(QIODevice *f,DescPose &a);
*/

bool	Save(QIODevice *f,const JointPos &a);
bool	Load(QIODevice *f,JointPos &a);

struct RobotInfo
{
	JointPos	CurrentJoint;
	enum CommandType
	{
		CMD_None				=0
		,CMD_SetTotalPage		=1
		,CMD_CaptureImage		=2
		,CMD_InsertPage			=3
		,CMD_RemovePage			=4
		,CMD_InspectImage		=5
	};
	CommandType	Cmd;
	int			Page;
};