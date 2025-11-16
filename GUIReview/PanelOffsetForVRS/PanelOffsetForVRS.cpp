#include "PanelOffsetForVRSResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelOffsetForVRS\PanelOffsetForVRS.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PanelOffsetForVRS.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "PanelOffsetVRSForm.h"
#include "XGUI.h"



static	char	*sRoot=/**/"Panel";
static	char	*sName=/**/"OffsetForVRS";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for setting offset in Front/Back");
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
	return(new PanelOffsetVRSForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);

	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SysRegisterFrontX";
	Data[0].Pointer				 =&((PanelOffsetVRSForm *)Instance)->SysRegisterFrontX;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"SysRegisterFrontY";
	Data[1].Pointer				 =&((PanelOffsetVRSForm *)Instance)->SysRegisterFrontY;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"SysRegisterBackX";
	Data[2].Pointer				 =&((PanelOffsetVRSForm *)Instance)->SysRegisterBackX;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"SysRegisterBackY";
	Data[3].Pointer				 =&((PanelOffsetVRSForm *)Instance)->SysRegisterBackX;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelOffsetVRS.png")));
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"OFFSETFRONTX",(int)1000);
	Data.AppendList(A);

	GuiAdditionalDatabase	*B=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"OFFSETFRONTY",(int)1000);
	Data.AppendList(B);

	GuiAdditionalDatabase	*C=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"OFFSETBACKX",(int)1000);
	Data.AppendList(C);

	GuiAdditionalDatabase	*D=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"OFFSETBACKY",(int)1000);
	Data.AppendList(D);
}
