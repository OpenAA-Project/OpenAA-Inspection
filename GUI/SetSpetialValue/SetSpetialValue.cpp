#include "SetSpetialValueResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SetSpetialValue\SetSpetialValue.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "SetSpetialValue.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "SetSpetialValueForm.h"
#include "XGUI.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"SetSpetialValue";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for setting spetial sequence value");
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
	return(new SetSpetialValueForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SetSpetialValue.png")));
}

//DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
//{
//	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase();
//	A->TableName=/**/"MASTERDATA";
//	A->FieldName=/**/"MACOFFSET";
//	A->DefaultData.setValue((int)0);
//	Data.AppendList(A);
//}
