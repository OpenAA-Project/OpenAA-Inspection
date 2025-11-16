#include "CeramicSurfaceMenuResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CeramicSurfaceMenu\CeramicSurfaceMenu.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "CeramicSurfaceMenuProperty.h"
#include "XPushCmdPacket.h"


char	*sRoot=/**/"Inspection";
char	*sName=/**/"CeramicSurfaceMenuProperty";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show menu for CeramicSurface");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdPushedStartCapture		(Base,sRoot,sName);
	(*Base)=new GUICmdRepliedPushStartCapture	(Base,sRoot,sName);

	(*Base)=new GUICmdStartInspect(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReplyInspect(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new CeramicSurfaceMenuProperty(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"QFont";
	Data[0].VariableNameWithRoute=/**/"CFont";
	Data[0].Pointer				 =&((CeramicSurfaceMenuProperty *)Instance)->CFont;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/CeramicSurfaceMenuProperty.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"HalconInspection"));
}
