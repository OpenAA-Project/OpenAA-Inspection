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

#include "ShowMatrixImageCenterResource.h"

#include "ShowMatrixImageCenter.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ShowMatrixImageCenterForm.h"
#include "XGUI.h"

static	const	char	*sRoot=/**/"ETC";
static	const	char	*sName=/**/"ShowMatrixImageCenter";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel to show matrix of image center");
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
	return(new ShowMatrixImageCenterForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowMatrixImageCenter.png")));
}

static	bool	MacroSetCenter(GUIFormBase *Instance ,QStringList &Args);


DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetCenter";
		Functions[ret].Explain.append(/**/"Set center of image");
		Functions[ret].ArgName.append(/**/"Center X pos in GlobalImage");
		Functions[ret].ArgName.append(/**/"Center Y pos in GlobalImage");
		Functions[ret].DLL_ExcuteMacro	=MacroSetCenter;
		ret++;
	}


	return ret;
}


static	bool	MacroSetCenter(GUIFormBase *Instance ,QStringList &Args)
{
	ShowMatrixImageCenterForm	*V=dynamic_cast<ShowMatrixImageCenterForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	x=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->SetCenter(x,y);

	return true;
}