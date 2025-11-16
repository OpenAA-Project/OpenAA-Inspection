/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyRepeatControl\PropertyRepeatControl.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyRepeatControl.h"
#include "PropertyRepeatControlForm.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"
#include "XGUIDLL.h"
#include "XPropertyRepeatControlPacket.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyRepeatControl";

static	bool	MacroCreateWhole(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for RepeatControl");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualRepeatControl	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendModifyRepeatControl		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqRepeatControlInfoList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckRepeatControlInfoList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdCreateWholeRepeatControl		(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyRepeatControlForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyRepeatControl.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"RepeatControl"));
}


DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateWhole";
		Functions[ret].ArgName.append(/**/"RepeatCount");
		Functions[ret].Explain.append(/**/"Create whole repeat-count");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateWhole;
		ret++;
	}

	return ret;
}

static	bool	MacroCreateWhole(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyRepeatControlForm	*V=dynamic_cast<PropertyRepeatControlForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	RepeatCount=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->CreateWhole(RepeatCount);

	return true;
}
