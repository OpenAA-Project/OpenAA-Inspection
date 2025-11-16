/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraGraphinNSUF7400DForMMC\CameraGraphin\RunLen.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef _RUNLEN_H_
#define _RUNLEN_H_
#include "windows.h"

// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦¡¦¡¦m¡¦¡¦
BOOL	RL_Alloc( ULONG ulFrmCnt );
// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦¡¦¡¦J¡¦¡¦
BOOL	RL_Free();
// ×ÝÚÝ¸Þ½ÃÞ°¡¦Ì¸Ø±
void	RL_Clr();
// ÃÞ°À¡¦ð²Ò°¼Þ¡¦¡¦¡¦¡¦
//BOOL	RL_Cnv( HANDLE hDev, BYTE *bMem, IPMFRAMEINFO *pFramePar, ULONG ulRlStart, ULONG ulRlSize,
//									ULONG ulFrmCnt, ULONG ulFrmNo, BOOL fLoop, BOOL fGrabber, BYTE *bImg );
// ×ÝÚÝ¸Þ¡¦¡¦¡¦
//BOOL	RL_Save( CString *strFname, BYTE *bMem, IPMFRAMEINFO *pFramePar, ULONG ulRlStart, ULONG ulRlSize, ULONG ulFrmNo, BOOL fLoop );

#endif //_RUNLEN_H_
