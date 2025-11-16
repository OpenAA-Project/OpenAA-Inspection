/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\MTOutConnection.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef MTOUTCONNECTION_H
#define MTOUTCONNECTION_H


#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

typedef	void *	MTOCHandle;

enum	MTOC_Operation
{
	_MTOC_Ope_None		=0
};

enum	MTOC_Command
{
	_MTOC_Cmd_None		=0
};

enum	MTOC_ImageAttr
{
	 _MTOC_Img_Master	=1
	,_MTOC_Img_Target	-2
};
enum	MTOC_BinaryAttr
{
	 _MTOC_Bin_MasterOutline		=1
	,_MTOC_Bin_TargetOutline		=2
};

extern "C"{

DEFFUNCEX	MTOCHandle	DLL_OC_Connect(char *IPAddress ,int Port);
DEFFUNCEX	MTOCHandle	DLL_OC_Close(MTOCHandle handle );

DEFFUNCEX	int			DLL_OC_EnumParam(MTOCHandle handle ,char **Keywords ,int MaxParams);
DEFFUNCEX	bool		DLL_OC_GetParam(MTOCHandle handle,char *Keyword ,void *);

DEFFUNCEX	bool		DLL_OC_GetImage(MTOCHandle handle ,MTOC_ImageAttr attr
										,BYTE **Image[]
										,int areaX1 ,int areay1,int areaX2 ,int areay2
										,int *DotPerLine, int *MaxLines, int *LayerCount);
DEFFUNCEX	bool		DLL_OC_SetImage(MTOCHandle handle ,MTOC_ImageAttr attr
										,int areaX1 ,int areay1,int areaX2 ,int areay2
										,int *DotPerLine, int *MaxLines, int *LayerCount);

DEFFUNCEX	bool		DLL_OC_GetBinarized(MTOCHandle handle,MTOC_BinaryAttr Attr 
											,BYTE **Image[]
											,int areaX1 ,int areay1,int areaX2 ,int areay2
											,int *DotPerLine, int *MaxLines, int *LayerCount);

DEFFUNCEX	bool		DLL_OC_RegistCallback(MTOCHandle handle,bool (*Func)(MTOCHandle handle ,MTOC_Operation ope));

DEFFUNCEX	bool		DLL_OC_SendCommand(MTOCHandle handle,MTOC_Command cmd ,void *data);

};

#endif

