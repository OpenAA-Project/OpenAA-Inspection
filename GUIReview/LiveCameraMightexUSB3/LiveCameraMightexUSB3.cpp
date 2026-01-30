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

#include "LiveCameraMightexUSB3Resource.h"
#include "LiveCameraMightexUSB3.h"

#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "LiveMightexForm.h"

char	*sRoot=/**/"Review";
char	*sName=/**/"LiveCameraMightexUSB3";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show LiveCamera view for MightexUSB3");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new LiveMightexForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);

	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ChildPanel";
	Data[0].Pointer				 =&((LiveMightexForm *)Instance)->ChildPanel;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ReverseX";
	Data[1].Pointer				 =&((LiveMightexForm *)Instance)->ReverseX;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ReverseY";
	Data[2].Pointer				 =&((LiveMightexForm *)Instance)->ReverseY;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ShowSettingButton";
	Data[3].Pointer				 =&((LiveMightexForm *)Instance)->ShowSettingButton;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowLiveButton";
	Data[4].Pointer				 =&((LiveMightexForm *)Instance)->ShowLiveButton;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"SysRegLiveMode";
	Data[5].Pointer				=&((LiveMightexForm *)Instance)->SysRegLiveMode;
	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LiveCameraMightexUSB3.png")));
}

