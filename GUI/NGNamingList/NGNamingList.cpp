#include "NGNamingListResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\NGNamingList\NGNamingList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "NGNamingList.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
//#include "XGUI.h"
#include "XGeneralFunc.h"
#include "NGNamingListForm.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"NGNamingList";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"NG Naming List for Inspection");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new NGNamingListForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqNGNamingList	(Base,sRoot,sName);
	(*Base)=new GUICmdSendNGNamingList(Base,sRoot,sName);
	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"WidthAreaName";
	Data[0].Pointer				 =&((NGNamingListForm *)Instance)->WidthAreaName;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"WidthNGCountInPiece";
	Data[1].Pointer				 =&((NGNamingListForm *)Instance)->WidthNGCountInPiece;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"TargetImagePanelName";
	Data[2].Pointer				 =&((NGNamingListForm *)Instance)->TargetImagePanelName;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/NGNamingList.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
