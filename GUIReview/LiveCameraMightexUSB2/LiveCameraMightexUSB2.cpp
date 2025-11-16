#include "LiveCameraMightexUSB2Resource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUIReview\LiveCameraMightexUSB2\LiveCameraMightexUSB2.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "LiveCameraMightexUSB2.h"

#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "LiveMightexForm.h"

char	*sRoot=/**/"Review";
char	*sName=/**/"LiveCameraMightexUSB2";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show LiveCamera view for MightexUSB3");
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
	return(new LiveMightexForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);

	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ReverseX";
	Data[0].Pointer				 =&((LiveMightexForm *)Instance)->ReverseX;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ReverseY";
	Data[1].Pointer				 =&((LiveMightexForm *)Instance)->ReverseY;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowSettingButton";
	Data[2].Pointer				 =&((LiveMightexForm *)Instance)->ShowSettingButton;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ShowLiveButton";
	Data[3].Pointer				 =&((LiveMightexForm *)Instance)->ShowLiveButton;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SysRegLiveMode";
	Data[4].Pointer				 =&((LiveMightexForm *)Instance)->SysRegLiveMode;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LiveCameraMightexUSB2.png")));
}


