/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyNaming\PropertyNaming.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyNamingFormResource.h"
#include "PropertyNaming.h"
#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "XPropertyNamingPacket.h"
#include "PropertyNamingForm.h"
#include "XMacroFunction.h"

static	bool	MacroCreateNaming(GUIFormBase *Instance ,QStringList &Args);


const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyNamingForm";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Naming");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdAddNamingArea			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdChangeNamingAttr		(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqSelectedNamingItems	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetSelectedNamingItems	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSelectedNamingItems	(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqNamingList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendNamingList			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqSetGroup				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqClearGroup			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqNamingGroupList		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendNamingGroupList		(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqGenerateIndex		(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyNamingForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyNaming.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Naming"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateNaming";
		Functions[ret].ArgName.append(/**/"Name");
		Functions[ret].ArgName.append(/**/"X");
		Functions[ret].ArgName.append(/**/"Y");
		Functions[ret].ArgName.append(/**/"XSize");
		Functions[ret].ArgName.append(/**/"YSize");
		Functions[ret].ArgName.append(/**/"Expand");
		Functions[ret].Explain.append(/**/"Create rectangle naming area");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateNaming;
		ret++;
	}
	return ret;
}

static	bool	MacroCreateNaming(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyNamingForm	*V=dynamic_cast<PropertyNamingForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<5){
		return false;
	}
	bool	ok;
	QString	AreaName=Args[0];

	int	Left=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Top	=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	XSize=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	YSize=Args[4].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Expand=Args[5].toInt(&ok);
	if(ok==false){
		return false;
	}
	FlexArea	Area;
	Area.SetRectangle(Left,Top,Left+XSize,Top+YSize);
	V->CreateArea(AreaName,Area,-1,-1,Expand);

	return true;
}
