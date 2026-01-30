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

#if	!defined(EVOBJDLL_H)
#define	EVOBJDLL_H

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	RunnerMap;
class	LanguagePackage;

extern "C"{

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name);
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

DEFFUNCEX	RunnerObject	*DLL_CreateInstance(LayersBase *Base,RunnerMap *rmap);
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance);

DEFFUNCEX	bool	DLL_ShowSettingDialog(RunnerObject *handle);
};


#endif