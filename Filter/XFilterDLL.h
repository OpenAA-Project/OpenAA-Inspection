/*
 * Copyright (C) 2024
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



#if	!defined(XFILTERDLL_H)
#define	XFILTERDLL_H


#include <QtGui>
#include "XTypeDef.h"

class  QString;
class  LayersBase;
class  RootNameListContainer;


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