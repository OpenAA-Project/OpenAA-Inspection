#include "PropertyFrameDefResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyFrameDef\PropertyFrameDef.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "PropertyFrameDefFormResource.h"
#include "PropertyFrameDef.h"
#include "PropertyFrameDefForm.h"
#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include"XPropertyFrameDefPacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyFrameDef";

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

	(*Base)=new GUICmdAddFrameAreaManual			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqFrameContainer			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckFrameContainer			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqMaxFrameNumber			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckMaxFrameNumber			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetItemNumber				(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyFrameDefForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyFrameDef.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"FrameDef"));
}
