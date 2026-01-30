/*
 * Copyright (C) 2023
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