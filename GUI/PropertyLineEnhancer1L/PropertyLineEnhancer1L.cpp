/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyLineEnhancer1L\PropertyLineEnhancer1L.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyLineEnhancer1LFormResource.h"
#include "XGUIDLL.h"
#include "PropertyLineEnhancer1L.h"
#include "PropertyLineEnhancer1LForm.h"
#include "XPropertyLineEnhancer1LPacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyLineEnhancer1L";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for LineEnhancer1L");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqAreaHistgramInMaster	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdCreateLineEnhancer1L	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdPickupTestList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdTestClear				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetDrawing				(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyLineEnhancer1LForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyLineEnhancer1L.png")));
}
DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"LineEnhancer1L"));
}
