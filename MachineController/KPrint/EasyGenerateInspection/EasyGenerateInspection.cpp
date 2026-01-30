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

#include "EasyGenerateInspectionResource.h"

#include "EasyGenerateInspection.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "EasyGenerateInspectionForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyGenerateInspection";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Easy generate inspection automatically");
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
	return(new EasyGenerateInspectionForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return -1;

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyGenerateInspection.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

static	bool	MacroGenerateStart(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGenerateStartInSlave(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"GenerateStart";
		Functions[ret].Explain.append(/**/"Generate start");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateStart;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"GenerateStartInSlave";
		Functions[ret].Explain.append(/**/"Generate start");
		Functions[ret].ArgName.append(/**/"Slave number");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateStartInSlave;
		ret++;
	}
	return ret;
}

static bool	MacroGenerateStart(GUIFormBase *Instance ,QStringList &Args)
{
	EasyGenerateInspectionForm	*V=dynamic_cast<EasyGenerateInspectionForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->GenerateStart();

	return true;
}

static bool	MacroGenerateStartInSlave(GUIFormBase *Instance ,QStringList &Args)
{
	EasyGenerateInspectionForm	*V=dynamic_cast<EasyGenerateInspectionForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	int	SlaveNo	=Args[0].toInt();

	V->GenerateStart(SlaveNo);

	return true;
}