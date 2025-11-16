#ifndef _RUNLEN_H_
#define _RUNLEN_H_
#include "windows.h"

// ×ÝÚÝ¸Þ½ÃÞ°À—Ìˆæ‚ÌŠm•Û
BOOL	RL_Alloc( ULONG ulFrmCnt );
// ×ÝÚÝ¸Þ½ÃÞ°À—Ìˆæ‚ÌŠJ•ú
BOOL	RL_Free();
// ×ÝÚÝ¸Þ½ÃÞ°À‚Ì¸Ø±
void	RL_Clr();
// ÃÞ°À‚ð²Ò°¼Þ‚Ö•ÏŠ·
//BOOL	RL_Cnv( HANDLE hDev, BYTE *bMem, IPMFRAMEINFO *pFramePar, ULONG ulRlStart, ULONG ulRlSize,
//									ULONG ulFrmCnt, ULONG ulFrmNo, BOOL fLoop, BOOL fGrabber, BYTE *bImg );
// ×ÝÚÝ¸Þ½•Û‘¶
//BOOL	RL_Save( CString *strFname, BYTE *bMem, IPMFRAMEINFO *pFramePar, ULONG ulRlStart, ULONG ulRlSize, ULONG ulFrmNo, BOOL fLoop );

#endif //_RUNLEN_H_
