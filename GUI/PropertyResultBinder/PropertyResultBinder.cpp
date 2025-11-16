/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyResultBinder\PropertyResultBinder.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "PropertyResultBinderFormResource.h"
#include "PropertyResultBinder.h"
#include "PropertyResultBinderForm.h"
#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include"XPropertyResultBinderPacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyResultBinder";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for ResultBinder");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	//(*Base)=new GUICmdReqGridList		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendGridList	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAddAreaManual	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqItemInfo		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendItemInfo	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSetItemInfo		(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyResultBinderForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyResultBinder.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ResultBinder"));
}
