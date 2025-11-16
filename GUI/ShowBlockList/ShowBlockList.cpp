#include "ShowBlockListResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowBlockList\ShowBlockList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowBlockListForm.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"ShowBlockList";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Block list");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUIReqUsedLibrary		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIAckUsedLibrary		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIReqLayerValueCount	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIAckLayerValueCount	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIReqStatisticByLib	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIAckStatisticByLib	(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowBlockListForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"EasyMode";
	Data[0].Pointer				 =&((ShowBlockListForm *)Instance)->EasyMode;
	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowBlockList.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
