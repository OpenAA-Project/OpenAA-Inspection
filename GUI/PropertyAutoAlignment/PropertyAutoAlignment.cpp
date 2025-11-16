/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoAlignment\PropertyAutoAlignment.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyAutoAlignmentFormResource.h"
#include "PropertyAutoAlignment.h"
#include "PropertyAutoAlignmentForm.h"
#include "XGUIDLL.h"
#include "XAutoAlignmentPacket.h"
#include "XMacroFunction.h"

static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGenerateBlocks(GUIFormBase *Instance ,QStringList &Args);

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyAutoAlignment";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return /**/"Show Property for AutoAlignment";
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdCreateAutoAlignmentSheet	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqAutoAlignmentInfo		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAutoAlignmentInfo		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqAutoAlignmentSheet		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAutoAlignmentSheet		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetAutoAlignmentShowingState(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAddAutoAlignmentSheet		(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyAutoAlignmentForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyAutoAlignment.png")));
}
DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoAlignment"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearLibList";
		Functions[ret].Explain.append(/**/"Clear all LibID in current list");
		Functions[ret].DLL_ExcuteMacro	=MacroClearLibList;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetLib";
		Functions[ret].ArgName.append(/**/"LibID");
		Functions[ret].Explain.append(/**/"Set LibID in current list");
		Functions[ret].DLL_ExcuteMacro	=MacroSetLib;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Generate";
		Functions[ret].Explain.append(/**/"Generate blocks");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateBlocks;
		ret++;
	}

	return ret;
}


static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAutoAlignmentForm	*V=dynamic_cast<PropertyAutoAlignmentForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ClearLibList();

	return true;
}

static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAutoAlignmentForm	*V=dynamic_cast<PropertyAutoAlignmentForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->SetLib(LibID);

	return true;
}

static	bool	MacroGenerateBlocks(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAutoAlignmentForm	*V=dynamic_cast<PropertyAutoAlignmentForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->GenerateBlocks();

	return true;
}