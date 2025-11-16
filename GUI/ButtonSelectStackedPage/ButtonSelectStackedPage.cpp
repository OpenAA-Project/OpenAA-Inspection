/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectStackedPage\ButtonSelectStackedPage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSelectStackedPage.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "ButtonSelectStackedPageForm.h"
#include "XGUIDLL.h"
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SelectStackedPage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to select StackForm page");
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
	return(new ButtonSelectStackedPageForm(Base,parent));
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
	Data[0].VariableNameWithRoute=/**/"StackFormInst";
	Data[0].Pointer				 =&((ButtonSelectStackedPageForm *)Instance)->StackFormInst;
	Data[1].Type				 =/**/"QStringList";
	Data[1].VariableNameWithRoute=/**/"Msg";
	Data[1].Pointer				 =&((ButtonSelectStackedPageForm *)Instance)->Msg;
	Data[1].Translatable		 =true;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"CharColor";
	Data[2].Pointer				 =&((ButtonSelectStackedPageForm *)Instance)->CharColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSelectStackedPageForm *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"FirstPage";
	Data[4].Pointer				 =&((ButtonSelectStackedPageForm *)Instance)->FirstPage;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSelectStackedPage.png")));
}

static bool	MacroSelectPage(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SelectPage";
		Functions[ret].Explain.append(/**/"Select page button");
		Functions[ret].ArgName.append(/**/"Page number(0,1,,,)");
		Functions[ret].DLL_ExcuteMacro	=MacroSelectPage;
		ret++;
	}

	return ret;
}

static bool	MacroSelectPage(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSelectStackedPageForm	*V=dynamic_cast<ButtonSelectStackedPageForm *>(Instance);
	if(V==NULL){
		return false;
	}
	int	n=0;
	if(Args.count()>=1){
		n	=Args[0].toInt();
	}
	V->SelectPage(n);

	return true;
}