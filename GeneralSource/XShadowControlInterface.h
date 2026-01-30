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

#pragma once

#include <QtGui>
#include <QLibrary>
#include "XTypeDef.h"
#include "XParamGlobal.h"
#include "XServiceForLayers.h"
#include "XDLLManager.h"
#include "NList.h"

class	ImageBuffer;
class	LanguagePackage;
class	CameraClass;
class	GUIDirectMessage;
class	SpecifiedBroadcaster;
class	CameraInterface;
class	ShadowTree;
class	ShadowParameter;

class	ShadowControlInterface : public DLLManager 
								,public ServiceForLayers
								,public NPList<ShadowControlInterface>
{

	WORD		(*DLL_GetDLLType)(void);
	bool		(*DLL_GetName)(QString &str);
	WORD		(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);
	void		(*DLL_SetLanguage)(LanguagePackage &Pkg ,int LanguageCode);
	bool		(*DLL_CheckCopyright)(QString &CopyrightString);

	ShadowTree	*(*DLL_Initial)(int ShadowNumber,LayersBase *ParentBase
								,const QString &GlobalParamFileName
								,const QString &GUIFileName);
	bool		(*DLL_Close)(ShadowTree *handle);
	bool		(*DLL_ShowSetting)(ShadowTree *handle, QWidget *parent);

	QLibrary 	DllLib;
	QString		LibraryFileName;
	QString		Copyright;
	bool		InFunc;
	ShadowTree	*Inst;
public:
	ShadowControlInterface(int ShadowNumber ,LayersBase *base);
	ShadowControlInterface(const ShadowControlInterface &src);
	~ShadowControlInterface(void);

	ShadowControlInterface	&operator=(const ShadowControlInterface &src);
	bool	LoadDLL(const QString &dllfilename,int32 &ErrorCode);
	bool	SetLanguageCode(int LanguageCode);

	QString	GetLibraryFileName(void);
	QString	GetCopyright(void);
	QString	GetName(void);
	WORD	GetVersion(void);
	WORD	GetDLLType(void);
	const QString	GetExplain(void);

	ShadowTree	*Initial(int ShadowNumber,LayersBase *ParentBase 
						,const QString &GlobalParamFileName
						,const QString &ShadowGUIFileName);
	ShadowTree	*GetInstance(void)	{	return Inst;	}
	bool		ShowSetting(QWidget *parent);
	bool	Close(ShadowTree *handle);
};


class	ShadowControlInterfaceContainer :public ServiceForLayers
										,public NPListPack<ShadowControlInterface>
{
public:
	ShadowControlInterfaceContainer(LayersBase *base);
	ShadowControlInterfaceContainer(const ShadowControlInterfaceContainer &src);

	ShadowControlInterfaceContainer	&operator=(const ShadowControlInterfaceContainer &src);
	bool	InitialDLL(void);

	bool	SaveShadowParam(QIODevice *f);
	bool	LoadShadowParam(QIODevice *f);
};