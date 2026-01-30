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

#ifndef XCAMERACOMMONH
#define XCAMERACOMMONH

#include "XTypeDef.h"
#include "XParamGlobal.h"
#include"XGUIPacketForDLL.h"

class	LayersBase;

enum CameraQuickProperty
{
	CameraQuickProperty_Brighter		=0x0001
	,CameraQuickProperty_Faster			=0x0002
	,CameraQuickProperty_SideBrighter	=0x0004
};

class CameraInfoDetailBase
{
public:
	CameraInfoDetailBase(){}
	virtual	~CameraInfoDetailBase(){}

	virtual	const QString	GetCameraMessage(void){		return /**/"";	}
};

class CameraReqInfoAnyData
{
public:
	CameraReqInfoAnyData(void){}
	virtual	~CameraReqInfoAnyData(void){}
};



class	CameraReqInfo
{
public:
	int32	XLen;			//Dot counts of X direction
	int32	YLen;			//Dot counts of Y direction
	int32	LayerNumber;	//Layer counts of simultanious caption
	int32	PageNumb;		//Local page count
	double	MaxFPS;			//May be no sense

  //Set in DLL_Initial in CameraDLL
	int32		CamMinimumDotPerLine;
	int32		CamMaximumDotPerLine;
	int32		CamMinimumLines;
	int32		CamMaximumLines;
	int32		CamSimultaneousLayerCount;
	bool		CamColored;
	int32		ErrorCode;		//0: No error
	char		ErrorMessage[256];
	CameraReqInfoAnyData		*AnyData;

	CameraReqInfo(void)	{	AnyData=NULL;	}
	virtual	~CameraReqInfo(void){}
	CameraReqInfo(const CameraReqInfo &src);
	CameraReqInfo	&operator=(const CameraReqInfo &src);
};

inline	CameraReqInfo::CameraReqInfo(const CameraReqInfo &src)
{
	XLen				=src.XLen				;		
	YLen				=src.YLen				;		
	LayerNumber			=src.LayerNumber		;
	PageNumb			=src.PageNumb			;	

	CamMinimumDotPerLine=src.CamMinimumDotPerLine	;
	CamMaximumDotPerLine=src.CamMaximumDotPerLine	;
	CamMinimumLines		=src.CamMinimumLines		;
	CamMaximumLines		=src.CamMaximumLines		;
	CamSimultaneousLayerCount	=src.CamSimultaneousLayerCount;
	CamColored			=src.CamColored	;
	ErrorCode			=src.ErrorCode	;
	memcpy(ErrorMessage,src.ErrorMessage,sizeof(ErrorMessage));
	AnyData=	src.AnyData;
}
inline	CameraReqInfo	&CameraReqInfo::operator=(const CameraReqInfo &src)
{
	XLen				=src.XLen				;		
	YLen				=src.YLen				;		
	LayerNumber			=src.LayerNumber		;
	PageNumb			=src.PageNumb			;	

	CamMinimumDotPerLine=src.CamMinimumDotPerLine	;
	CamMaximumDotPerLine=src.CamMaximumDotPerLine	;
	CamMinimumLines		=src.CamMinimumLines		;
	CamMaximumLines		=src.CamMaximumLines		;
	CamSimultaneousLayerCount	=src.CamSimultaneousLayerCount;
	CamColored			=src.CamColored	;
	ErrorCode			=src.ErrorCode	;
	memcpy(ErrorMessage,src.ErrorMessage,sizeof(ErrorMessage));
	AnyData=	src.AnyData;
	return *this;
}

class	SpecifiedBroadcasterSendResetCamera : public SpecifiedBroadcaster
{
public:
	int		Page;
	int		Cmd;
	SpecifiedBroadcasterSendResetCamera(void){}
};

class	SpecifiedBroadcasterCalibrateCamera : public SpecifiedBroadcaster
{
public:
	int		Page;
	SpecifiedBroadcasterCalibrateCamera(void){}
};
//
//------------------------------------------------------------------

class	CameraDLLInfo
{
public:
	bool	MutexInDLL;		//true:must set Mutex in DLL	,false:Mutex in CameraInterface

public:
	CameraDLLInfo(void);
};

inline	CameraDLLInfo::CameraDLLInfo(void)
{
	MutexInDLL=false;
}

//------------------------------------------------------------------

extern	"C"{

typedef	struct	_CameraScanInfo
{
	bool	ReverseRightLeft:1;
	bool	ReverseTopDown:1;
	bool	FreeRun:1;

	bool	ScanMastered:1;
	int32		CurrentScanNumber;
	StrategicListContainer StrategicList;
	CameraInfoDetailBase	*DetailResult;
	CameraReqInfoAnyData	*AnyData;

	_CameraScanInfo(void){	
		ReverseRightLeft=false;	
		ReverseTopDown	=false;	
		FreeRun			=false;
		CurrentScanNumber		=0;
		ScanMastered			=true;
		DetailResult	=NULL;
		AnyData			=NULL;
	}
	~_CameraScanInfo(void){
		StrategicList.RemoveAll();
		delete	DetailResult;
	}
	struct _CameraScanInfo &operator=(struct _CameraScanInfo &src)
	{
		ReverseRightLeft	=src.ReverseRightLeft;
		ReverseTopDown		=src.ReverseTopDown;
		FreeRun				=src.FreeRun;
		CurrentScanNumber	=src.CurrentScanNumber;
		ScanMastered		=src.ScanMastered;
		StrategicList		=src.StrategicList;
		DetailResult		=src.DetailResult;
		AnyData				=src.AnyData;
		src.DetailResult	=NULL;
		return *this;
	}
}CameraScanInfo;

};

#endif