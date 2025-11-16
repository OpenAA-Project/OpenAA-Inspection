/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyMakeAverageImage\EasyMakeAverageImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
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
