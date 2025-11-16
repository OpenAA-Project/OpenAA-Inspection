#include "CartonMenuResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CartonMenu\CartonMenu.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "CartonMenu.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "CartonMenuForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"CartonMenu";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for set shift on filter");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCartonMenuAutoGen		(Base,sRoot,sName);
	(*Base)	=new IntegrationSendInsectionLevel		(Base,sRoot,sName);
	(*Base)	=new IntegrationSetRun					(Base,sRoot,sName);
	(*Base)	=new IntegrationDeliverTimeoutValue		(Base,sRoot,sName);
	(*Base)	=new IntegrationDeliverMoveForAlignment	(Base,sRoot,sName);
	(*Base)	=new IntegrationBuildAlignment			(Base,sRoot,sName);
	(*Base)	=new IntegrationResetSlaves				(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new CartonMenuForm(Base,parent));
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
	Data[0].VariableNameWithRoute=/**/"StackInstName";
	Data[0].Pointer				 =&((CartonMenuForm *)Instance)->StackInstName;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ShowBlade";
	Data[1].Pointer				 =&((CartonMenuForm *)Instance)->ShowBlade;
	Data[2].Type				 =/**/"QStringList";
	Data[2].VariableNameWithRoute=/**/"ButtonNameList";
	Data[2].Pointer				 =&((CartonMenuForm *)Instance)->ButtonNameList;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/CartonMenu.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"BCRInspection"));
}
static	bool	MacroSetRun				(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroAutoGenerate		(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroOpenRun			(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroOpenSwitchPhase	(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroOpenMask			(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroOpenAlignment		(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroOpenInspection		(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroOpenBlade			(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetExposure		(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroMoveForAlignment	(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroBuildAlignment		(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetInspectionRunOnly(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroAdjustTrigger		(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenRun";
		Functions[ret].Explain.append(/**/"Open run widget");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenRun;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AutoGenerate";
		Functions[ret].Explain.append(/**/"execute auto-generation");
		Functions[ret].DLL_ExcuteMacro	=MacroAutoGenerate;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenSwitchPhase";
		Functions[ret].Explain.append(/**/"Open SwitchPhase widget");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenSwitchPhase;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenMask";
		Functions[ret].Explain.append(/**/"Open mask widget");
		Functions[ret].ArgName.append(/**/"Selext page number(0,1,,,)");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenMask;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenAlignment";
		Functions[ret].Explain.append(/**/"Open alignment widget");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenAlignment;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenInspection";
		Functions[ret].Explain.append(/**/"Open inspection widget");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenInspection;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenBlade";
		Functions[ret].Explain.append(/**/"Open blade widget");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenBlade;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetExposure";
		Functions[ret].Explain.append(/**/"Open exposure widget");
		Functions[ret].DLL_ExcuteMacro	=MacroSetExposure;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MoveForAlignment";
		Functions[ret].Explain.append(/**/"Move for Alignment");
		Functions[ret].DLL_ExcuteMacro	=MacroMoveForAlignment;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"BuildAlignment";
		Functions[ret].Explain.append(/**/"Check and repair Alignment");
		Functions[ret].DLL_ExcuteMacro	=MacroBuildAlignment;
		ret++;
	}	
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetRun";
		Functions[ret].Explain.append(/**/"Set state of running");
		Functions[ret].ArgName.append(/**/"true(Run)/false(Stop)");
		Functions[ret].DLL_ExcuteMacro	=MacroSetRun;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetInspectionRunOnly";
		Functions[ret].Explain.append(/**/"Set state of InspectionRun");
		Functions[ret].ArgName.append(/**/"true(Run)/false(Stop)");
		Functions[ret].DLL_ExcuteMacro	=MacroSetInspectionRunOnly;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AdjustTrigger";
		Functions[ret].Explain.append(/**/"Adjust Trigger");
		Functions[ret].DLL_ExcuteMacro	=MacroAdjustTrigger;
		ret++;
	}	
	return ret;
}

static bool	MacroSetRun(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()>=1){
		bool	StateRun=false;
		if(Args[0].toUpper()==QString(/**/"TRUE")
		|| Args[0].toUpper()==QString(/**/"RUN")){
			StateRun=true;
		}
		else
		if(Args[0].toUpper()==QString(/**/"false")
		|| Args[0].toUpper()==QString(/**/"STOP")){
			StateRun=false;
		}
		else{
			return false;
		}
		V->SetRun(StateRun);
	}
	return true;
}

static bool	MacroSetInspectionRunOnly(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()>=1){
		bool	StateRun=false;
		if(Args[0].toUpper()==QString(/**/"TRUE")
		|| Args[0].toUpper()==QString(/**/"RUN")){
			StateRun=true;
		}
		else
		if(Args[0].toUpper()==QString(/**/"false")
		|| Args[0].toUpper()==QString(/**/"STOP")){
			StateRun=false;
		}
		else{
			return false;
		}
		V->SetInspectionRunOnly(StateRun);
	}
	return true;
}

static bool	MacroAutoGenerate(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->ExecuteAutoGenerate();

	return true;
}

static bool	MacroOpenRun(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->OpenRun();

	return true;
}

static bool	MacroOpenSwitchPhase(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->OpenSwitchPhase();

	return true;
}

static bool	MacroOpenMask(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}
	int	n=0;
	if(Args.count()>=1){
		n	=Args[0].toInt();
	}
	V->OpenMask(n);

	return true;
}

static bool	MacroOpenAlignment(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->OpenAlignment();

	return true;
}

static bool	MacroOpenInspection(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->OpenInspection();

	return true;
}

static bool	MacroOpenBlade(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->OpenBlade();

	return true;
}

static bool	MacroSetExposure(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->OpenExposure();

	return true;
}
static	bool	MacroMoveForAlignment	(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->MoveForAlignment();

	return true;
}

static	bool	MacroBuildAlignment	(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->BuildAlignment();

	return true;
}

static	bool	MacroAdjustTrigger(GUIFormBase *Instance ,QStringList &Args)
{
	CartonMenuForm	*V=dynamic_cast<CartonMenuForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->AdjustTrigger();

	return true;
}