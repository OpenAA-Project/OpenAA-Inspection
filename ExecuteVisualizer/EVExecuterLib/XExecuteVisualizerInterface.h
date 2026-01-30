/*
 * Copyright (C) 2022
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

#include "NList.h"
#include "XTypeDef.h"
#include <QString>
#include <QPainter>
#include <QIODevice>
#include <QLabel>
#include <QWidget>
#include <QTimer>
#include <QLibrary>
#include "XServiceForLayers.h"
#include <QLibrary>
#include "XExecuteVisualizer.h"
#include "XYCross.h"
#include "XDLLManager.h"


class	RunnerObjDLL : public NPList<RunnerObjDLL>,public DLLManager,public ServiceForLayers
{
	friend	class	RunerDLLContainer;

	QString			FileName;
	QLibrary 		DllLib;

	bool	(*DLL_GetName)(QString &Root,QString &Name);
	WORD	(*DLL_GetVersion)(void);
	void	(*DLL_GetUsageFiles)(QStringList &RelativeFilePath);
	const char	*(*DLL_GetExplain)(void);
	void	(*DLL_SetLanguageCommon)(LanguagePackage &Pkg,int LanguageCode);
	void	(*DLL_SetLanguage)		(LanguagePackage &Pkg,int LanguageCode);
	bool	(*DLL_CheckCopyright)(QString &CopyrightString);
	bool	(*DLL_Initial)(LayersBase *Base);
	void	(*DLL_Close)(void);
	void	(*DLL_InitialQt)(QApplication *AppBase);

	RunnerObject *(*DLL_CreateInstance)(LayersBase *Base,RunnerMap *rmap);
	void	(*DLL_DeleteInstance)(RunnerObject *Instance);

	bool	(*DLL_ShowSettingDialog)(RunnerObject *handle);


	QString			DLLRoot;
	QString			DLLName;

public:
	RunnerObjDLL(LayersBase *Base);
	virtual	~RunnerObjDLL(void);

	bool	LoadDLL(const QString &filename);

	void	GetRootName(QString &_DLLRoot,QString &_DLLName){ _DLLRoot=DLLRoot;	_DLLName=DLLName; }
	const QString	GetExplain(void);
	WORD	GetVersion(void);

	RunnerObject *CreateInstance(RunnerMap *rmap);
	void	DeleteInstance(RunnerObject *Instance);

	bool	IsSettingDialog(void);
	bool	ShowSettingDialog(RunnerObject *handle);

	const	QString &GetFileName(void)	{ return FileName; }
	void	GetExportFunctions(QStringList &Str);
};
