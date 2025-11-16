/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMakeAverageImage\PropertyMakeAverageImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyMakeAverageImageResource.h"
#include "PropertyMakeAverageImage.h"
#include "PropertyMakeAverageImageForm.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"
#include "XGUIDLL.h"
#include "XPropertyMakeAverageImagePacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyMakeAverageImage";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for MakeAverageImage");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSetAverageToMaster(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAverageCount	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAverageCount	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdResetAverage		(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyMakeAverageImageForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyMakeAverageImage.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"MakeAverageImage"));
}

static	bool	MacroResetAverage(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ResetAverage";
		Functions[ret].Explain.append(/**/"Reset(Clear) average");
		Functions[ret].DLL_ExcuteMacro	=MacroResetAverage;
		ret++;
	}

	return ret;
}


DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List)
{
	List.Add(GUILIB_ID,/**/"Button" ,/**/"AutoScanningMode");
}

static	bool	MacroResetAverage(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyMakeAverageImageForm	*V=dynamic_cast<PropertyMakeAverageImageForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->ResetAverage();

	return true;
}