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

#if	!defined(XPrinterDLL_H)
#define	XPrinterDLL_H


#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"

class	LayersBase;
class	PrinterDLLBaseClass;

extern	"C"{

DEFFUNCEX	WORD	DLL_GetDLLType(void);
//	return	DLL type for PrinterDLL

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
//	return DLL-Name. 

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void);
//	return Printer DLL version

DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);


DEFFUNCEX	const char	*DLL_GetExplain(void);

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
//	return Copyright string
DEFFUNCEX	void		DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	PrinterDLLBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &PrinterParamStr);
//	Initialize Printer DLL. 
//		This function must create and open handle. 
//	return:		Printer handle(memory block)
//				if proocess fails, return 0

DEFFUNCEX	void		_cdecl	DLL_SetLayersBasePointer(PrinterDLLBaseClass *handle ,LayersBase *base);
//	Set LayersBase pointer into PrinterDLL


DEFFUNCEX	bool		_cdecl	DLL_Close(PrinterDLLBaseClass *handle);
//	Release handle and close DLL
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Load(PrinterDLLBaseClass *handle ,QIODevice &str);
//	Load Printer attribution(setting) information of handle
//	This function must load information from stream
//	In this function, Printer attribution information must be set to a handle
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_Save(PrinterDLLBaseClass *handle ,QIODevice &str);
//	Save Printer attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(PrinterDLLBaseClass *handle, QWidget *parent);
//	This function shows dialog to set Printer(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Printering pattern(Which Printer is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false

};


#endif