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

#include "PropertySwitchPhaseResource.h"
#include "XGUIDLL.h"
#include "PropertySwitchPhase.h"
#include "PropertySwitchPhaseForm.h"
#include "XPropertySwitchPhasePacket.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertySwitchPhase";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for SwitchPhase");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendAddManualBlock		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendModifyItem			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIReqTestMap					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIClearMap						(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqPhaseItemList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckPhaseItemList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqItemInfoList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckItemInfoList			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqAddPhase				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckAddPhase				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdDeletePhase				(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdCopyTargetToMaster		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqMatchingResult			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckMatchingResult			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqEnableExecuteMatch		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckEnableExecuteMatch		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendEnableExecuteMatch	(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdMakeAutoGeneration		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdDeleteAllItemInAllPhases	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdDeleteAllPhases			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReUseMark					(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertySwitchPhaseForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PropertySwitchPhase.png")));
}
DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"SwitchPhase"));
}
static	bool	MacroScanFrom1(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCancelScan(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroAutoGeneration(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroDeleteAllPhases(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroDeleteAllMarks(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroReUseMark(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ScanFrom1";
		Functions[ret].Explain.append(/**/"Scan from 1");
		Functions[ret].ArgName.append(/**/"Start phase number");
		Functions[ret].DLL_ExcuteMacro	=MacroScanFrom1;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CancelScan";
		Functions[ret].Explain.append(/**/"Cancel scanning");
		Functions[ret].DLL_ExcuteMacro	=MacroCancelScan;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AutoGeneration";
		Functions[ret].Explain.append(/**/"Automatic item generation");
		Functions[ret].DLL_ExcuteMacro	=MacroAutoGeneration;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DeleteAllPhases";
		Functions[ret].Explain.append(/**/"Delete all added phases");
		Functions[ret].DLL_ExcuteMacro	=MacroDeleteAllPhases;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DeleteAllMarks";
		Functions[ret].Explain.append(/**/"Delete all Marks");
		Functions[ret].DLL_ExcuteMacro	=MacroDeleteAllMarks;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ReUseMark";
		Functions[ret].Explain.append(/**/"Use Mark in 1st phase to other phase");
		Functions[ret].DLL_ExcuteMacro	=MacroReUseMark;
		ret++;
	}
	
	return ret;
}


static	bool	MacroScanFrom1(GUIFormBase *Instance ,QStringList &Args)
{
	PropertySwitchPhaseForm	*V=dynamic_cast<PropertySwitchPhaseForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	int	StartPhaseNo	=Args[0].toInt();

	V->ScanFrom1(StartPhaseNo);

	return true;
}

static	bool	MacroCancelScan(GUIFormBase *Instance ,QStringList &Args)
{
	PropertySwitchPhaseForm	*V=dynamic_cast<PropertySwitchPhaseForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->CancelScan();

	return true;
}

static	bool	MacroAutoGeneration(GUIFormBase *Instance ,QStringList &Args)
{
	PropertySwitchPhaseForm	*V=dynamic_cast<PropertySwitchPhaseForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->AutoGeneration();

	return true;
}

static	bool	MacroDeleteAllPhases(GUIFormBase *Instance ,QStringList &Args)
{
	PropertySwitchPhaseForm	*V=dynamic_cast<PropertySwitchPhaseForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->DeleteAllPhases();

	return true;
}
static	bool	MacroDeleteAllMarks(GUIFormBase *Instance ,QStringList &Args)
{
	PropertySwitchPhaseForm	*V=dynamic_cast<PropertySwitchPhaseForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->DeleteAllMarks();

	return true;
}
static	bool	MacroReUseMark(GUIFormBase *Instance ,QStringList &Args)
{
	PropertySwitchPhaseForm	*V=dynamic_cast<PropertySwitchPhaseForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->ReUseMark();

	return true;
}