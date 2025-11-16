/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelXYZSize\PanelXYZSize.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PanelXYZSize.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "PanelXYZSizeForm.h"
#include "XGUI.h"



static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"XYZSize";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for setting X-Y-Z size");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new PanelXYZSizeForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);

	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"LimitMaxX";
	Data[0].Pointer				 =&((PanelXYZSizeForm *)Instance)->LimitMaxX;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"LimitMaxY";
	Data[1].Pointer				 =&((PanelXYZSizeForm *)Instance)->LimitMaxY;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"LimitMaxZ";
	Data[2].Pointer				 =&((PanelXYZSizeForm *)Instance)->LimitMaxZ;
	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelXYZSize.png")));
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"XSIZE",(int)1000);
	Data.AppendList(A);

	GuiAdditionalDatabase	*B=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"YSIZE",(int)1000);
	Data.AppendList(B);

	GuiAdditionalDatabase	*C=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"ZSIZE",(int)10);
	Data.AppendList(C);
}
