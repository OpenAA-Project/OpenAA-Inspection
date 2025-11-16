#include "EasyPropertyDXFOperationResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyPropertyDXFOperation\EasyPropertyDXFOperation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyPropertyDXFOperation.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "EasyPropertyDXFOperationForm.h"
#include "XMacroFunction.h"
#include "AllocationLibByColorDialog.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyPropertyDXFOperation";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Easy property for DXFOperationing");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new IntegrationCmdLoadDXF				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdRotate				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdExtend				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdMoveXY				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAutoGenerate			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdXMirror				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdYMirror				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdEnfatLine				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdDXFDeleteAllItem		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdTilt					(Base,sRoot,sName);
	(*Base)=new IntegrationCmdDelBrade				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdSetAllocationLibByColor(Base,sRoot,sName);
	(*Base)=new IntegrationCmdReqDXFColor			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAckDXFColor			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdDelMaskByCAD			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdExecuteInitialMask	(Base,sRoot,sName);

	(*Base)=new IntegrationCmdReqAllocationLibByColor	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAckAllocationLibByColor	(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new EasyPropertyDXFOperationForm(Base,parent));
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
	Data[0].Pointer			  =&((EasyPropertyDXFOperationForm *)Instance)->SlaveNo;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyPropertyDXFOperation.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DXFOperation"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"Masking"));
}

static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroMakeAllocation(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Generate";
		Functions[ret].Explain.append(/**/"Generate Automatically");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateAutomatically;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MakeAllocation";
		Functions[ret].Explain.append(/**/"Generate allocation");
		Functions[ret].DLL_ExcuteMacro	=MacroMakeAllocation;
		ret++;
	}
	return ret;
}

static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args)
{
	EasyPropertyDXFOperationForm	*V=dynamic_cast<EasyPropertyDXFOperationForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->GenerateAutomatically();

	return true;
}

static	bool	MacroMakeAllocation(GUIFormBase *Instance ,QStringList &Args)
{
	EasyPropertyDXFOperationForm	*V=dynamic_cast<EasyPropertyDXFOperationForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->MakeAllocation();

	return true;
}
