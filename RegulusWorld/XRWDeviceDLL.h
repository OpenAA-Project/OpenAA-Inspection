/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\RegulusWorld\XRWDeviceDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XRWDeviceDLLH
#define XRWDeviceDLLH

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	LayersBase;
class	RWDeviceBaseClass;

extern	"C"{

DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for DeviceDLL

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void);
//	return Device DLL version

DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	void		DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	const char	*DLL_GetExplain(void);

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
//	return Copyright string

DEFFUNCEX	RWDeviceBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &DeviceParamStr);
//	Initialize Device DLL. 
//		This function must create and open handle. 
//	return:		Device handle(memory block)
//				if proocess fails, return 0

DEFFUNCEX	bool		_cdecl	DLL_Close(RWDeviceBaseClass *handle);
//	Release handle and close DLL
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Load(RWDeviceBaseClass *handle ,QIODevice &str);
//	Load Device attribution(setting) information of handle
//	This function must load information from stream
//	In this function, Device attribution information must be set to a handle
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Save(RWDeviceBaseClass *handle ,QIODevice &str);
//	Save Device attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(RWDeviceBaseClass *handle, QWidget *parent);
//	This function shows dialog to set Device(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Deviceing pattern(Which Device is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false

};

#endif
