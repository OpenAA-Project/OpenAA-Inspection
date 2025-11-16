#include "EasyGenerateInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyGenerateInspection\EasyGenerateInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
