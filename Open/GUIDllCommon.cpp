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

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XLanguageClass.h"
extern	LangSolverNew	LangLibSolver;

DEFFUNCEX	WORD	DLL_GetDLLType(void)
{
	return(GUILIB_ID);
}

DEFFUNCEX	WORD	DLL_GetVersion(void)
{
	return(GUILIB_Version);
}

DEFFUNCEX	void	DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode)
{
	LangLibSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_CloseInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	void	DLL_InitialQt(QApplication *AppBase)
{
	//static	bool	Done=false;
	//if(qApp==NULL){
	//	int	a=0;
	//	char	*av[10];
	//	av[0]=/**/"";
	//	//QApplication	*Q=new QApplication(a,av);
	//}
	//else{
	//	Done=true;
	//}
}