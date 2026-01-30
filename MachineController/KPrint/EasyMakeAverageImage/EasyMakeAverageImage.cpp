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

#include "EasyMakeAverageImageResource.h"
#include "EasyMakeAverageImage.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "EasyMakeAverageImageForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyMakeAverageImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Easy MakeAverageImage");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdStartScan		(Base,sRoot,sName);
	(*Base)	=new IntegrationReqScanningCount	(Base,sRoot,sName);
	(*Base)	=new IntegrationAckScanningCount	(Base,sRoot,sName);
	(*Base)	=new IntegrationClearScanningCount	(Base,sRoot,sName);
	(*Base)	=new IntegrationGenerateAverageImage(Base,sRoot,sName);
	(*Base)	=new IntegrationResetAverageImage	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new EasyMakeAverageImageForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return -1;

	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"TargetSlaveNo";
	Data[0].Pointer				 =&((EasyMakeAverageImageForm *)Instance)->TargetSlaveNo;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyMakeAverageImage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args);
//
//DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
//{
//	int32	ret=0;
//
//	if(MaxBuffer>ret){
//		Functions[ret].FuncName	=/**/"Generate";
//		Functions[ret].Explain.append(/**/"Generate Automatically");
//		Functions[ret].DLL_ExcuteMacro	=MacroGenerateAutomatically;
//		ret++;
//	}
//	return ret;
//}
//
//static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args)
//{
//	EasyMakeAverageImageForm	*V=dynamic_cast<EasyMakeAverageImageForm *>(Instance);
//	if(V==NULL){
//		return false;
//	}
//	V->GenerateAutomatically();
//
//	return true;
//}