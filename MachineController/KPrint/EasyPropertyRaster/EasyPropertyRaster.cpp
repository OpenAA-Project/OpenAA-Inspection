#include "EasyPropertyRasterResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyPropertyRaster\EasyPropertyRaster.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyPropertyRaster.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "EasyPropertyRasterForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyPropertyRaster";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Easy property for Raster");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new IntegrationCmdLoadRaster			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdRotate				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdExtend				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdMoveXY				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAutoGenerate			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdXMirror				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdYMirror				(Base,sRoot,sName);
	(*Base)=new IntegrationCmdRasterDeleteAllItem	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdTilt					(Base,sRoot,sName);
	(*Base)=new IntegrationCmdDelMaskByCAD			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAddRegArea			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAddRegColorArea		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdReqElementInfo		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAckElementInfo		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdSetCurrentElementID	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdSetRegColor			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdGeneraeRasterAlgorithm(Base,sRoot,sName);
	(*Base)=new IntegrationCmdDeleteRegColor		(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new EasyPropertyRasterForm(Base,parent));
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
	Data[0].Pointer			  =&((EasyPropertyRasterForm *)Instance)->SlaveNo;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyPropertyRaster.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Raster"));
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
		Functions[ret].Explain.append(/**/"Make Allocation");
		Functions[ret].DLL_ExcuteMacro	=MacroMakeAllocation;
		ret++;
	}
	return ret;
}

static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args)
{
	EasyPropertyRasterForm	*V=dynamic_cast<EasyPropertyRasterForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->GenerateAutomatically();

	return true;
}
static	bool	MacroMakeAllocation(GUIFormBase *Instance ,QStringList &Args)
{
	EasyPropertyRasterForm	*V=dynamic_cast<EasyPropertyRasterForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->MakeAllocation();

	return true;
}