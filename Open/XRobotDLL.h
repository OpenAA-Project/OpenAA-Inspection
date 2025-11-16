#pragma once

#include <QtGui>
#include <QIODevice>
#include "XTypeDef.h"
#include "XDLLType.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	LayersBase;
class	RobotDLLBaseClass;

extern	"C"{

DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for RobotDLL

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void);
//	return Light DLL version

DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	void		DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	const char	*DLL_GetExplain(void);

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
//	return Copyright string

DEFFUNCEX	RobotDLLBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &LightParamStr);
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0

DEFFUNCEX	bool		_cdecl	DLL_Close(RobotDLLBaseClass *handle);
//	Release handle and close DLL
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Load(RobotDLLBaseClass *handle ,QIODevice &str);
//	Load light attribution(setting) information of handle
//	This function must load information from stream
//	In this function, light attribution information must be set to a handle
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Save(RobotDLLBaseClass *handle ,QIODevice &str);
//	Save light attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(RobotDLLBaseClass *handle, QWidget *parent);
//	This function shows dialog to set light(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Lighting pattern(Which light is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false


};