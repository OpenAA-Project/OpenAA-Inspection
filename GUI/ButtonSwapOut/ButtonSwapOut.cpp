//#include "ButtonSwapOutResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSwapOut\ButtonSwapOut.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSwapOut.h"
#include "ButtonSwapOutForm.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SwapOut";

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
	return(new ButtonSwapOutForm(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSwapOutForm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QFont";
	Data[1].VariableNameWithRoute=/**/"CFont";
	Data[1].Pointer				 =&((ButtonSwapOutForm *)Instance)->CFont;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"ButtonColor";
	Data[2].Pointer				 =&((ButtonSwapOutForm *)Instance)->ButtonColor;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"MasterImage";
	Data[3].Pointer				 =&((ButtonSwapOutForm *)Instance)->MasterImage;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSwapOut.png")));
}

static	bool	MacroSwapOut(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSwapOutForm	*V=dynamic_cast<ButtonSwapOutForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->CommandSwapOut();

	return true;
}


DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SwapOut";
		Functions[ret].Explain.append(/**/"Swap-OUT image buffer");
		Functions[ret].DLL_ExcuteMacro	=MacroSwapOut;
		ret++;
	}

	return ret;
}
