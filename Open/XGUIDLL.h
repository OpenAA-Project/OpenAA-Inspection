/*
 * Copyright (C) 2025
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


#if	!defined(XGUIDLL_H)
#define	XGUIDLL_H

#include "NList.h"
#include <QString>
#include <QIODevice>
#include "XTypeDef.h"
#include <QIcon>
#include <QBuffer>
#include "XDLLType.h"
#include <QWidget>
#include <QApplication>
#include "XGUIFormBase.h"
#include "XDataComponent.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

struct	PropertyClass
{
	QString		Type;
	QString		VariableNameWithRoute;
	void		*Pointer;
	QString		Explain;
	QString		DLLFuncName;
	bool		Translatable;

	PropertyClass(){	Translatable=false;	}
};

class	ParamGlobal;
class	ParamComm;
class	LayersBase;
class	GuiAdditionalDatabase;
class	ErrorCodeList;

class	ExportFuncForMacro;
class	LanguagePackage;


#if	!defined(ForApplication)

extern "C"{

#ifdef _MSC_VER
DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	WORD	DLL_GetDLLType(void);
DEFFUNCEX	WORD	DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	void	DLL_GetUsageFiles(QStringList &RelativeFilePath);

DEFFUNCEX	const char	*DLL_GetExplain(void);
DEFFUNCEX	void	DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	void	DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base);
DEFFUNCEX	void	DLL_Close(void);
DEFFUNCEX	void	DLL_InitialQt(QApplication *AppBase);
DEFFUNCEX	bool	DLL_ReceivePacket(LayersBase *Base,int32 cmd ,int32 globalPage ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData);
DEFFUNCEX	bool	DLL_ReceivePacketDirectComm(LayersBase *Base
												,int32 cmd ,int32 globalPage 
												,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName
												,QBuffer &buff
												,int32 IDForUndo
												,ErrorCodeList &ErrorData);
DEFFUNCEX	bool	DLL_ReceiveIntegrationPacket(LayersBase *Base,int32 cmd ,int32 SlaveNo 
									  ,const char *EmitterRoot ,const char *EmitterName 
									  ,const char *ClassName,QBuffer &buff
									  ,int32 IDForUndo
									  ,ErrorCodeList &ErrorData);
									  
DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent);
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance);
DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD maxDataDim);

DEFFUNCEX	QIcon	*DLL_GetIcon(void);
DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data);

DEFFUNCEX	void	DLL_EntryAlgorithm	(LayersBase *Base,RootNameListContainer &List);
DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);

#else

bool	DLL_GetName(QString &Root ,QString &Name);
WORD	DLL_GetDLLType(void);
WORD	DLL_GetVersion(void);
const char	*DLL_GetSystemVersion(VersionType vtype);
void	DLL_GetUsageFiles(QStringList &RelativeFilePath);

const char	*DLL_GetExplain(void);
void	DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode);
void	DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);
bool	DLL_CheckCopyright(QString &CopyrightString);
bool	DLL_Initial(LayersBase *Base);
void	DLL_Close(void);
void	DLL_InitialQt(QApplication *AppBase);
bool	DLL_ReceivePacket(LayersBase *Base,int32 cmd ,int32 globalPage ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData);
bool	DLL_ReceivePacketDirectComm(LayersBase *Base
												,int32 cmd ,int32 globalPage 
												,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName
												,QBuffer &buff
												,int32 IDForUndo
												,ErrorCodeList &ErrorData);
bool	DLL_ReceiveIntegrationPacket(LayersBase *Base,int32 cmd ,int32 SlaveNo 
									  ,const char *EmitterRoot ,const char *EmitterName 
									  ,const char *ClassName,QBuffer &buff
									  ,int32 IDForUndo
									  ,ErrorCodeList &ErrorData);

GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent);
void	DLL_DeleteInstance(GUIFormBase *Instance);
int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD maxDataDim);

QIcon	*DLL_GetIcon(void);
void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data);

void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List);

int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);
#endif


};

#endif
#endif
