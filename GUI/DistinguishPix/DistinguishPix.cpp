/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DistinguishPix\DistinguishPix.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DistinguishPixFormResource.h"
#include "DistinguishPix.h"
#include "DistinguishPixForm.h"

static	const	char	*sRoot=/**/"List";
static	const	char	*sName=/**/"DistinguishPix";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"List for DistinguishPix");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DistinguishPixForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"NG1Str";
	Data[0].Pointer				 =&((DistinguishPixForm *)Instance)->NG1Str;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"NG2Str";
	Data[1].Pointer				 =&((DistinguishPixForm *)Instance)->NG2Str;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"NG3Str";
	Data[2].Pointer				 =&((DistinguishPixForm *)Instance)->NG3Str;
	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"NG4Str";
	Data[3].Pointer				 =&((DistinguishPixForm *)Instance)->NG4Str;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"PhaseToLoad";
	Data[4].Pointer				 =&((DistinguishPixForm *)Instance)->PhaseToLoad;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DistinguishPix.png")));
}
