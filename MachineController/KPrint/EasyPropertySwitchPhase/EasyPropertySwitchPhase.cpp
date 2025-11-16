#include "EasyPropertySwitchPhaseResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyPropertySwitchPhase\EasyPropertySwitchPhase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
