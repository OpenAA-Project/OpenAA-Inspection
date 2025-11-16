#include "ZoomMechanicalPanelResource.h"

/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUIReview\ReviewZHeight\ReviewZHeight.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ZoomMechanicalPanel.h"
#include "ZoomMechanicalPanelForm.h"
#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
//#include "XGUI.h"
#include "XDataInLayer.h"

char	*sRoot=/**/"Review";
char	*sName=/**/"ZoomMechanicalPanel";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Zooming panel mechanically on VRS");
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
	return(new ZoomMechanicalPanelForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);

	Data[0].Type				 =/**/"double";
	Data[0].VariableNameWithRoute=/**/"MinZoomRate";
	Data[0].Pointer				 =&((ZoomMechanicalPanelForm *)Instance)->MinZoomRate;
	Data[1].Type				 =/**/"double";
	Data[1].VariableNameWithRoute=/**/"MaxZoomRate";
	Data[1].Pointer				 =&((ZoomMechanicalPanelForm *)Instance)->MaxZoomRate;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"SysValueZoom";
	Data[2].Pointer				 =&((ZoomMechanicalPanelForm *)Instance)->SysValueZoom;
	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ZoomMechanicalPanel.png")));
}
