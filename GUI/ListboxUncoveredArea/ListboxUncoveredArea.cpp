#include "ListboxUncoveredAreaResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListboxUncoveredArea\ListboxUncoveredAreaForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ListboxUncoveredAreaForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"

const	char	*sRoot=/**/"List";
const	char	*sName=/**/"UncoveredArea";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Uncovered area List");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ListboxUncoveredAreaForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqUncoveredAreaList	(Base,sRoot,sName);
	(*Base)=new GUICmdSendUncoveredAreaList	(Base,sRoot,sName);
	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"ImagePanelName";
	Data[0].Pointer				 =&((ListboxUncoveredAreaForm *)Instance)->ImagePanelName;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"MaxRowCount";
	Data[1].Pointer				 =&((ListboxUncoveredAreaForm *)Instance)->MaxRowCount;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ListboxUncoveredArea.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}



