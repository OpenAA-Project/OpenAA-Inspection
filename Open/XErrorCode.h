/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XErrorCode.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XERRORCODE_H)
#define	XERRORCODE_H

#include <QIODevice>
#include <QString>
#include "XDateTime.h"
#include <QTextStream>
#include "NList.h"
#include "XTypeDef.h"


#define	Error_Nothing					(0)

#define	Error_NoDLL_GetDLLType			(0x1000+0x0001)
#define	Error_InvalidDLL_GetDLLType		(0x1000+0x0002)
#define	Error_NoDLL_GetVersion			(0x1000+0x0003)
#define	Error_LowerDLL_GetVersion		(0x1000+0x0004)
#define	Error_NoDLL_GetName				(0x1000+0x0005)
#define	Error_NoDLL_CreateInstance		(0x1000+0x0006)
#define	Error_NoDLL_DeleteInstance		(0x1000+0x0007)
#define	Error_NoDLL_GetPropertyString	(0x1000+0x0008)
#define	Error_NoDLL_GetExplain			(0x1000+0x0009)
#define	Error_NoDLL_Initial				(0x1000+0x000a)
#define	Error_NoDLL_ReceivePacket		(0x1000+0x000b)
#define	Error_DLL_NotExistPath			(0x1000+0x000c)
#define	Error_DLL_FalseInCopyright		(0x1000+0x000d)
#define	Error_NoDLL_InitialQt			(0x1000+0x000e)
#define	Error_NoDLL_GetSystemVersion	(0x1000+0x000f)

#define	Error_DLLAnalyzeProperty		(0x1000+0x0100)

#define	Error_Camera_NoFunc_DLL_GetDLLType			(0x2000+0x0001)
#define	Error_Camera_NoFunc_DLL_GetName				(0x2000+0x0002)
#define	Error_Camera_NoFunc_DLL_GetVersion			(0x2000+0x0003)
#define	Error_Camera_NoFunc_DLL_Initial				(0x2000+0x0004)
#define	Error_Camera_NoFunc_DLL_Close				(0x2000+0x0005)
#define	Error_Camera_NoFunc_DLL_Load				(0x2000+0x0006)
#define	Error_Camera_NoFunc_DLL_Save				(0x2000+0x0007)
#define	Error_Camera_NoFunc_DLL_ShowSetting			(0x2000+0x0008)
#define	Error_Camera_NoFunc_DLL_PrepareCapture		(0x2000+0x0009)
#define	Error_Camera_NoFunc_DLL_StartCapture		(0x2000+0x000a)
#define	Error_Camera_NoFunc_DLL_HaltCapture			(0x2000+0x000b)
#define	Error_Camera_NoFunc_DLL_GetStatus			(0x2000+0x000c)
#define	Error_Camera_NoFunc_DLL_ClearError			(0x2000+0x000d)
#define	Error_Camera_NoFunc_DLL_GetImage			(0x2000+0x000e)
#define	Error_Camera_NoFunc_DLL_GetSystemVersion	(0x2000+0x000f)
#define	Error_CameraDLL								(0x2000+0x0010)
#define	Error_Camera_DLL_InitialError				(0x2000+0x0011)

#define	Error_Light_NoFunc_DLL_GetDLLType			(0x3000+0x0001)
#define	Error_Light_NoFunc_DLL_GetName				(0x3000+0x0002)
#define	Error_Light_NoFunc_DLL_GetVersion			(0x3000+0x0003)
#define	Error_Light_NoFunc_DLL_Initial				(0x3000+0x0004)
#define	Error_Light_DLL_Initial1					(0x3000+0x0104)
#define	Error_Light_DLL_Initial2					(0x3000+0x0204)
#define	Error_Light_DLL_Initial3					(0x3000+0x0304)
#define	Error_Light_DLL_Initial4					(0x3000+0x0404)
#define	Error_Light_NoFunc_DLL_Close				(0x3000+0x0005)
#define	Error_Light_NoFunc_DLL_Load					(0x3000+0x0006)
#define	Error_Light_NoFunc_DLL_Save					(0x3000+0x0007)
#define	Error_Light_NoFunc_DLL_ShowSetting			(0x3000+0x0008)
#define	Error_Light_NoFunc_DLL_GetLightPatternCount	(0x3000+0x0009)
#define	Error_Light_NoFunc_DLL_GetSystemVersion		(0x3000+0x000a)
#define	Error_Light_NotLoaded						(0x3000+0x000b)
#define	Error_LightDLL								(0x3000+0x0010)

#define	Error_Filter_NoFunc_DLL_GetDLLType			(0x4000+0x0001)
#define	Error_Filter_NoFunc_DLL_GetName				(0x4000+0x0002)
#define	Error_Filter_NoFunc_DLL_GetVersion			(0x4000+0x0003)
#define	Error_Filter_NoFunc_DLL_Initial				(0x4000+0x0004)
#define	Error_Filter_NoFunc_DLL_Close				(0x4000+0x0005)
#define	Error_Filter_NoFunc_DLL_Load				(0x4000+0x0006)
#define	Error_Filter_NoFunc_DLL_Save				(0x4000+0x0007)
#define	Error_Filter_NoFunc_DLL_ShowSetting			(0x4000+0x0008)
#define	Error_Filter_NoFunc_DLL_ExecuteBeforeScan	(0x4000+0x0009)
#define	Error_Filter_NoFunc_DLL_ExecuteImage		(0x4000+0x000a)
#define	Error_Filter_NoFunc_DLL_GetSystemVersion	(0x4000+0x000b)
#define	Error_Filter_NoFunc_DLL_GetExplain			(0x4000+0x000c)
#define	Error_FilterDLL								(0x4000+0x0010)

#define	Error_DFSFilter_NoFunc_DLL_GetDLLType		(0x5000+0x0001)
#define	Error_DFSFilter_NoFunc_DLL_GetName			(0x5000+0x0002)
#define	Error_DFSFilter_NoFunc_DLL_GetVersion		(0x5000+0x0003)
#define	Error_DFSFilter_NoFunc_DLL_Initial			(0x5000+0x0004)
#define	Error_DFSFilter_NoFunc_DLL_Close			(0x5000+0x0005)
#define	Error_DFSFilter_NoFunc_DLL_Load				(0x5000+0x0006)
#define	Error_DFSFilter_NoFunc_DLL_Save				(0x5000+0x0007)
#define	Error_DFSFilter_NoFunc_DLL_ShowSetting		(0x5000+0x0008)
#define	Error_DFSFilter_NoFunc_DLL_GetSystemVersion	(0x5000+0x000b)
#define	Error_DFSFilter_NoFunc_DLL_GetExplain		(0x5000+0x000c)
#define	Error_DFSFilter_NoFunc_DLL_ExecuteSaveFileInDFS	(0x5000+0x000d)
#define	Error_DFSFilterDLL							(0x5000+0x0010)

#define	Error_Printer_NoFunc_DLL_GetDLLType			(0x6000+0x0001)
#define	Error_Printer_NoFunc_DLL_GetName			(0x6000+0x0002)
#define	Error_Printer_NoFunc_DLL_GetVersion			(0x6000+0x0003)
#define	Error_Printer_NoFunc_DLL_Initial			(0x6000+0x0004)
#define	Error_Printer_NoFunc_DLL_Close				(0x6000+0x0005)
#define	Error_Printer_NoFunc_DLL_Load				(0x6000+0x0006)
#define	Error_Printer_NoFunc_DLL_Save				(0x6000+0x0007)
#define	Error_Printer_NoFunc_DLL_ShowSetting		(0x6000+0x0008)
#define	Error_Printer_NoFunc_DLL_GetSystemVersion	(0x6000+0x000a)
#define	Error_Printer_NotLoaded						(0x6000+0x000b)
#define	Error_PrinterDLL							(0x6000+0x0010)


#define	Error_Hasp_NoFunc_DLL_GetDLLType			(0x7000+0x0001)
#define	Error_Hasp_NoFunc_DLL_GetName				(0x7000+0x0002)
#define	Error_Hasp_NoFunc_DLL_GetVersion			(0x7000+0x0003)
#define	Error_Hasp_NoFunc_DLL_Initial				(0x7000+0x0004)
#define	Error_Hasp_DLL_Initial1						(0x7000+0x0104)
#define	Error_Hasp_DLL_Initial2						(0x7000+0x0204)
#define	Error_Hasp_DLL_Initial3						(0x7000+0x0304)
#define	Error_Hasp_DLL_Initial4						(0x7000+0x0404)
#define	Error_Hasp_NoFunc_DLL_Close					(0x7000+0x0005)
#define	Error_Hasp_NoFunc_DLL_GetSystemVersion		(0x7000+0x000a)
#define	Error_Hasp_NotLoaded						(0x7000+0x000b)
#define	Error_HaspDLL								(0x7000+0x0010)

#define	Error_Authentic_NotRecognized				(0x7000+0x1001)
#define	Error_Authentic_InvalidLicenseKey			(0x7000+0x1002)
#define	Error_Authentic_InvalidTerm					(0x7000+0x1003)
#define	Error_Authentic_MismatchID					(0x7000+0x1004)
#define	Error_Authentic_MaxCount					(0x7000+0x1005)

#define	Error_Robot_NoFunc_DLL_GetDLLType			(0x3000+0x0001)
#define	Error_Robot_NoFunc_DLL_GetName				(0x3000+0x0002)
#define	Error_Robot_NoFunc_DLL_GetVersion			(0x3000+0x0003)
#define	Error_Robot_NoFunc_DLL_Initial				(0x3000+0x0004)
#define	Error_Robot_NoFunc_DLL_Close				(0x3000+0x0005)
#define	Error_Robot_NoFunc_DLL_Load					(0x3000+0x0006)
#define	Error_Robot_NoFunc_DLL_Save					(0x3000+0x0007)
#define	Error_Robot_NoFunc_DLL_ShowSetting			(0x3000+0x0008)
#define	Error_Robot_DLL_Initial						(0x3000+0x0009)
#define	Error_Robot_NoFunc_DLL_GetSystemVersion		(0x3000+0x000a)
#define	Error_Robot_NotLoaded						(0x3000+0x000b)
#define	Error_RobotDLL								(0x3000+0x0010)

#define	Error_MismatchStrategyCode					(0x8000+0x0001)

#define	Error_Comm									(0x10000+0x001)
#define	Error_FileAccess							(0x10000+0x002)
#define	Error_ResultServer							(0x20000+0x001)

//==============================================================================

class	ErrorCodeListContainer;

class	ErrorCodeList : public NPList<ErrorCodeList>
{
	friend	class	ErrorCodeListContainer;

	QString		Message;
	int32		ErrorCode;
	XDateTime	ErrorTime;
public:
	enum		CautionLevel{
					_None		=0
					,_Critical	=1		//stop system
					,_Important	=2		//die something for function, thread
					,_Alart		=3		//Never die , light level error
					,_Message	=4		//pure message
	};
private:
	CautionLevel	Level;
	int			Page;					//Not saved
public:

	ErrorCodeList(void);
	ErrorCodeList(CautionLevel level,const QString &_message ,int errorcode=-1);
	explicit	ErrorCodeList(CautionLevel r){	Level=r;	ErrorCode=0;	Page=0;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	ErrorCodeList	&operator=(const ErrorCodeList &src);

	void	SetError(int errorCode 
					,const QString &errorMessage 
					,ErrorCodeList::CautionLevel level
					,const XDateTime &errorTime);
	void	SetPage(int page)				{	Page=page;	}
	void	SetCautionLevel(CautionLevel r)	{	Level=r;	}
	void	Clear(void)						{	Message=/**/"";	ErrorCode=0;	Page=0;	Level=_None;	}
	void	OutputStr(QTextStream &TxtStr);
	
	int				GetPage(void)		const	{	return Page;		}
	CautionLevel	GetLevel(void)		const	{	return Level;		}
	const QString	&GetMessageStr(void)const	{	return Message;		}
	int32			GetErrorCode(void)	const	{	return ErrorCode;	}
	const XDateTime	&GetErrorTime(void)	const	{	return ErrorTime;	}

};

inline	void	ErrorCodeList::SetError(int errorCode 
					,const QString &errorMessage 
					,ErrorCodeList::CautionLevel level
					,const XDateTime &errorTime)
{
	ErrorCode	=errorCode;
	Message		=errorMessage;
	Level		=level;
	ErrorTime	=errorTime;
}

class	ErrorCodeListContainer : public NPListPack<ErrorCodeList>
{
public:
	ErrorCodeListContainer(void);

	void	AddErrorCode(ErrorCodeList::CautionLevel level,const QString &_message ,int errorcode=-1);
	void	AddErrorCode(ErrorCodeList::CautionLevel level,int errorcode);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

bool	CheckSystemVersionFunc(QStringList &Str 
							   ,const QString &DLLType 
							   ,const QString &DLLRoot 
							   ,const QString &DLLName 
							   ,const char *(*DLL_GetSystemVersion)(VersionType vtype));
bool	CheckSystemVersionFunc(QStringList &Str);

inline	ErrorCodeList::ErrorCodeList(void)
{
	Page		=0;
	Level		=_None;
	ErrorCode	=0;
	Page		=0;
}

inline	ErrorCodeList::ErrorCodeList(CautionLevel level,const QString &_message,int errorcode)
:	Message(_message)
	,ErrorCode(errorcode)
	,ErrorTime(XDateTime::currentDateTime())
	,Level(level)
	,Page(0)
{
}


class CommErrorList : public NPList<CommErrorList>
{
public:
	XDateTime	TM;
	QString		ClassNameStr;
	int			GlobalPage;
	int			SlaveNo;

	CommErrorList(){	GlobalPage=-1;	SlaveNo=-1;	}

};

#define	MaxCommErrorList	100


#endif