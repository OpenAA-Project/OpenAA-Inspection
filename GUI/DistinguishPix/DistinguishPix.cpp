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


#include "DistinguishPixFormResource.h"
#include "DistinguishPix.h"
#include "DistinguishPixForm.h"

static	const	char	*sRoot=/**/"List";
static	const	char	*sName=/**/"DistinguishPix";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"List for DistinguishPix");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DistinguishPixForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"NG1Str";
	Data[0].Pointer				 =&((DistinguishPixForm *)Instance)->NG1Str;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"NG2Str";
	Data[1].Pointer				 =&((DistinguishPixForm *)Instance)->NG2Str;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"NG3Str";
	Data[2].Pointer				 =&((DistinguishPixForm *)Instance)->NG3Str;
	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"NG4Str";
	Data[3].Pointer				 =&((DistinguishPixForm *)Instance)->NG4Str;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"PhaseToLoad";
	Data[4].Pointer				 =&((DistinguishPixForm *)Instance)->PhaseToLoad;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DistinguishPix.png")));
}