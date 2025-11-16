/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XTypeDef.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XTYPEDEF)
#define	XTYPEDEF
#include <QtGlobal>

#ifdef Q_OS_WIN
#define	FuncCall	__cdecl
#else
#define	FuncCall	
#endif

class	IdentifiedClass
{
public:
	IdentifiedClass(void){}
	virtual	~IdentifiedClass(void){}
};

typedef	unsigned char		BYTE;
typedef	unsigned char		byte;
typedef	signed char			int8;
typedef	short				int16;
typedef	qint32				int32;
typedef	qint64				int64;
typedef	unsigned short		uint16;
typedef	unsigned int		uint32;
typedef	quint64				uint64;
#ifndef	_WINDEF_
typedef	unsigned long		DWORD;
typedef	quint64				QWORD;
typedef	unsigned short		WORD;
#endif

#define	Saturation256(x)	(((x)<0)?0:((x)<256)?(x):255)

#define	MaxCountOfPhase		100

enum	bool3
{
	 true3
	,false3
	,none3
};

enum	VersionType
{
	Ver_Qt				=0
	,Ver_Regulus		=1
	,Ver_Revision		=2
	,Ver_IsMatched		=3
};

enum	ExeResult
{
	 _ER_true				=0
	,_ER_NoFunc				=1
	,_ER_ReqRetryLater		=2
	,_ER_ReqCaptureAgain	=3
	,_ER_false				=-1
};

enum OriginType{
	 _OriginType_FromUnknown	=0
	,_OriginType_FromLibrary	=1
	,_OriginType_FromManual		=2
	,_OriginType_FromParts		=3
	,_OriginType_FromMPA		=4
	,_OriginType_FromCAD		=5
	,_OriginType_FromAutomatic	=6
};

enum _ResultType{
	 _ResultDWORD	=0
	,_ResultDouble	=1
	,_ResultInt64	=2
	,_ResultWORD	=3
	,_ResultBYTE	=4
};


#ifdef _MSC_VER

#if	QT_VERSION<0x050000
#define	hypot(x,y)	_hypot(x,y)
#endif

enum	DirectValueType{
	 _DT_None			=0
	,_DT_bool			=1
	,_DT_byte			=2		//unsigned char
	,_DT_char			=23		//signed char
	,_DT_short			=3
	,_DT_ushort			=24
	,_DT_int			=20
	,_DT_int32			=4
	,_DT_uint32			=25
	,_DT_int64			=5
	,_DT_uint64			=26
	,_DT_QString		=6
	,_DT_double			=7
	,_DT_longdouble		=27
	,_DT_float			=8
	,_DT_enum			=9
	,_DT_struct			=10
	,_DT_QColor			=11
	,_DT_QFont			=12
	,_DT_QStringList	=13
	,_DT_WidgetList		=14
	,_DT_TunableList	=15
	,_DT_FileName		=16
	,_DT_PathName		=17
	,_DT_FileNames		=18
	,_DT_QImage			=19
	,_DT_QByteArray		=21
	,_DT_IntList		=22
};

#endif
#include <cmath>

#endif
