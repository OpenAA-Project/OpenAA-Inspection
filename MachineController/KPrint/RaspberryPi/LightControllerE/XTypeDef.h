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

typedef	unsigned char		BYTE;
typedef	unsigned char		byte;
typedef	signed char			int8;
typedef	short				int16;
typedef	signed int			int32;

typedef	unsigned short		uint16;
typedef	unsigned int		uint32;

#ifndef	_WINDEF_
typedef	unsigned long		DWORD;

typedef	unsigned short		WORD;
#endif

#define	Saturation256(x)	(((x)<0)?0:((x)<256)?(x):255)

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

#ifdef _MSC_VER

#define	hypot(x,y)	_hypot(x,y)


#endif


#endif
