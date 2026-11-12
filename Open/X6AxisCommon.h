#pragma once

#include "XTypedef.h"

struct AxisInfo
{
	bool	DragModeON;
	bool	ArriveHome;
	bool	ClearMasterScans;
	bool	StartInspection;
	bool	EndInspection;
	int		TargetCaptureOn;	//Page number
	int		MasterCaptureOn;	//Page number
	int		InsertCaptureON;	//Page number
	int		RemoveCaptureON;	//Page number
	double	Distance;
	int		PageCount;
	bool3	LightON;
	float	CurrentJointPos[6];
	int		ReqCaptureNo;
	float	AckJointPos[6];
	float	CompareParamJ[6];
};

#define	SharedMemoryKey	/**/"RobotAxis"