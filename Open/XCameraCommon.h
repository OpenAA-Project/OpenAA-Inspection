/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XCameraCommon.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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