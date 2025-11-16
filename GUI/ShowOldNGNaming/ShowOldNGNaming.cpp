#include "ShowOldNGNamingResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowOldNGNaming\ShowOldNGNaming.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ShowOldNGNaming.h"
#include "ShowOldNGNamingForm.h"

#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"

const	char	*sRoot=/**/"List";
const	char	*sName=/**/"ShowOldNGNaming";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Progressbar on idle");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowOldNGNamingForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);

	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"GenerationLevel";
	Data[0].Pointer				 =&((ShowOldNGNamingForm *)Instance)->GenerationLevel;

	Data[1].Type				 =/**/"QStringList";
	Data[1].VariableNameWithRoute=/**/"TargetImagePanelNames";
	Data[1].Pointer				 =&((ShowOldNGNamingForm *)Instance)->TargetImagePanelNames;


	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowOldNGNaming.png")));
}
