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

#include "EasyPropertySwitchPhaseResource.h"

#include "EasyPropertySwitchPhase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "EasyPropertySwitchPhaseForm.h"
#include "XMacroFunction.h"
#include "XPropertySwitchPhasePacket.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyPropertySwitchPhase";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Easy property for SwitchPhase");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new IntegrationCmdScanFrom1			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdCancelScan			(Base,sRoot,sName);
	(*Base)=new CmdSignalLoadMasterImage			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdMakeAutoGeneration	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdDeleteAllPhases		(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new EasyPropertySwitchPhaseForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return -1;
	Data[0].Type				  =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SlaveNo";
	Data[0].Pointer			  =&((EasyPropertySwitchPhaseForm *)Instance)->SlaveNo;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyPropertySwitchPhase.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

static	bool	MacroDeleteAllPhase(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DeleteAllPhase";
		Functions[ret].Explain.append(/**/"Delete all additional phases");
		Functions[ret].DLL_ExcuteMacro	=MacroDeleteAllPhase;
		ret++;
	}

	return ret;
}

static	bool	MacroDeleteAllPhase(GUIFormBase *Instance ,QStringList &Args)
{
	EasyPropertySwitchPhaseForm	*V=dynamic_cast<EasyPropertySwitchPhaseForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->DeleteAllAdditionalPhases();

	return true;
}