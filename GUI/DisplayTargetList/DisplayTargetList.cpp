/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayTargetList\DisplayTargetList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayTargetList.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XCriticalFunc.h"
#include "XResult.h"
#include "XDataInLayer.h"

const	char	*sRoot=/**/"Panel";
const	char	*sName=/**/"DisplayTargetList";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show total inspection count");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqImageForList		(Base,sRoot,sName);
	(*Base)=new GUICmdAckImageForList		(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DisplayTargetList(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);

	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"RelatedInst";
	Data[0].Pointer				 =&((DisplayTargetList *)Instance)->RelatedInst;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayTargetList.png")));
}
