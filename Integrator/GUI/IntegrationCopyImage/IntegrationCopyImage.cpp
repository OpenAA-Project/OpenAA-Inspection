#include "IntegrationCopyImageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationCopyImage\IntegrationCopyImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationCopyImage.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "IntegrationCopyImageForm.h"
#include "XMacroFunction.h"

//extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"CopyImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to copy Target image to Master image");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new IntegrationCmdCopyImage		(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationCopyImageForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				  =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SlaveNo";
	Data[0].Pointer			  =&((IntegrationCopyImageForm *)Instance)->SlaveNo;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"Msg";
	Data[1].Pointer				 =&((IntegrationCopyImageForm *)Instance)->Msg;
	Data[1].Translatable		 =true;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"CharColor";
	Data[2].Pointer				 =&((IntegrationCopyImageForm *)Instance)->CharColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"BackColor";
	Data[3].Pointer				 =&((IntegrationCopyImageForm *)Instance)->BackColor;
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((IntegrationCopyImageForm *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationCopyImage.png")));
}

static	bool	MacroExecuteCopy(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ExecuteCopy";
		Functions[ret].Explain.append(/**/"Execute copy");
		Functions[ret].DLL_ExcuteMacro	=MacroExecuteCopy;
		ret++;
	}
	return ret;
}

static bool	MacroExecuteCopy(GUIFormBase *Instance ,QStringList &Args)
{
	IntegrationCopyImageForm	*V=dynamic_cast<IntegrationCopyImageForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->ExecuteCopy();

	return true;
}

