#include "startcapturebuttonResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartCaptureButton\startcapturebutton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StartCaptureButton.h"
#include "XPushCmdPacket.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Action";
const	char	*sName=/**/"StartCaptureButton";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for starting capture");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdPushedStartCapture		(Base,sRoot,sName);
	(*Base)=new GUICmdRepliedPushStartCapture	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new StartCaptureButton(Base,parent));
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
	Data[0].Pointer				 =&((StartCaptureButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((StartCaptureButton *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((StartCaptureButton *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((StartCaptureButton *)Instance)->CFont;
	Data[4].Type				 =/**/"Master,Target";
	Data[4].VariableNameWithRoute=/**/"ImageType";
	Data[4].Pointer				 =&((StartCaptureButton *)Instance)->ImageType;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StartCaptureButton.png")));
}


static	bool	MacroStart(GUIFormBase *Instance ,QStringList &Args)
{
	StartCaptureButton	*V=dynamic_cast<StartCaptureButton *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandStart();

	return true;
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Scan";
		Functions[ret].Explain.append(/**/"Scan image");
		Functions[ret].DLL_ExcuteMacro	=MacroStart;
		ret++;
	}

	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
