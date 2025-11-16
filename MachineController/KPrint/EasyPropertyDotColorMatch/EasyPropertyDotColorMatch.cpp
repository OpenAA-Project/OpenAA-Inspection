#include "EasyPropertyDotColorMatchResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyPropertyDotColorMatch\EasyPropertyDotColorMatch.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyPropertyDotColorMatch.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "EasyPropertyDotColorMatchForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyPropertyDotColorMatch";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Easy property for DotColorMatching");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new IntegrationCmdGenerate			(Base,sRoot,sName);
	(*Base)=new IntegrationDeleteAll			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdReqLimitedMask	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAckLimitedMask	(Base,sRoot,sName);
	(*Base)=new GUICmdSetLevel(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new EasyPropertyDotColorMatchForm(Base,parent));
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
	Data[0].Pointer			  =&((EasyPropertyDotColorMatchForm *)Instance)->SlaveNo;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyPropertyDotColorMatch.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}


static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Generate";
		Functions[ret].Explain.append(/**/"Generate Automatically");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateAutomatically;
		ret++;
	}
	return ret;
}

static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args)
{
	EasyPropertyDotColorMatchForm	*V=dynamic_cast<EasyPropertyDotColorMatchForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->GenerateAutomatically();

	return true;
}
