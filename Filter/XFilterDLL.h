/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\XFilterDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XFILTERDLL_H)
#define	XFILTERDLL_H


#include <QtGui>
#include "XTypeDef.h"

class  QString;
class  LayersBase;
class  RootNameListContainer;

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif


extern	"C"{

class	FilterClassBase;
class	LanguagePackage;

DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for FilterDLL

DEFFUNCEX	bool	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD	DLL_GetVersion(void);
//	return Filter DLL version

DEFFUNCEX	const char	*DLL_GetExplain(void);
//	return explanation

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);

DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	FilterClassBase	*DLL_Initial(LayersBase *base);
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0

DEFFUNCEX	bool	DLL_Close(void *handle);
//	Release handle and close DLL
//	if process fails, it returns false

DEFFUNCEX	bool	DLL_Load(FilterClassBase *handle ,QIODevice &str);
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false

DEFFUNCEX	bool	DLL_Save(FilterClassBase *handle ,QIODevice &str);
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false

DEFFUNCEX	bool	DLL_ShowSetting(FilterClassBase *handle, QWidget *parent);
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false

DEFFUNCEX	void	DLL_ExecuteBeforeScan	(FilterClassBase *handle);
//	Execute something image before scanning

DEFFUNCEX	bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts);
//	Execute filtering image data
//	if process fails, it returns false

};

#endif