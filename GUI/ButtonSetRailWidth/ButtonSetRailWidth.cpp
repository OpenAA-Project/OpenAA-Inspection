#include "ButtonSetRailWidthResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSetRailWidth\ButtonSetRailWidth.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSetRailWidth.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ButtonSetRailWidthForm.h"
#include "XGUI.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"SetRailWidth";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for setting Rail width");
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
	return(new ButtonSetRailWidthForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"double";
	Data[0].VariableNameWithRoute=/**/"MaxSize";
	Data[0].Pointer				 =&((ButtonSetRailWidthForm *)Instance)->MaxSize;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSetRailWidth.png")));
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"RAILWIDTH",(int)1000);
	//A->TableName=/**/"MASTERDATA";
	//A->FieldName=/**/"RAILWIDTH";
	//A->DefaultData.setValue((int)1000);
	Data.AppendList(A);
}
