//#include "ButtonSwapInResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSwapIn\ButtonSwapIn.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSwapIn.h"
#include "ButtonSwapInForm.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SwapIn";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Swap-IN");
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
	return(new ButtonSwapInForm(Base,parent));
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
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonSwapInForm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QFont";
	Data[1].VariableNameWithRoute=/**/"CFont";
	Data[1].Pointer				 =&((ButtonSwapInForm *)Instance)->CFont;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"ButtonColor";
	Data[2].Pointer				 =&((ButtonSwapInForm *)Instance)->ButtonColor;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"MasterImage";
	Data[3].Pointer				 =&((ButtonSwapInForm *)Instance)->MasterImage;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSwapIn.png")));
}


static	bool	MacroSwapIn(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSwapInForm	*V=dynamic_cast<ButtonSwapInForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->CommandSwapIn();

	return true;
}


DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SwapIn";
		Functions[ret].Explain.append(/**/"Swap-IN image buffer");
		Functions[ret].DLL_ExcuteMacro	=MacroSwapIn;
		ret++;
	}

	return ret;
}
