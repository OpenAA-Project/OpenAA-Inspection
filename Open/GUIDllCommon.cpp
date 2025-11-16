/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\GUIDllCommon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XLanguageClass.h"
extern	LangSolverNew	LangLibSolver;

DEFFUNCEX	WORD	DLL_GetDLLType(void)
{
	return(GUILIB_ID);
}

DEFFUNCEX	WORD	DLL_GetVersion(void)
{
	return(GUILIB_Version);
}

DEFFUNCEX	void	DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode)
{
	LangLibSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_CloseInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	void	DLL_InitialQt(QApplication *AppBase)
{
	//static	bool	Done=false;
	//if(qApp==NULL){
	//	int	a=0;
	//	char	*av[10];
	//	av[0]=/**/"";
	//	//QApplication	*Q=new QApplication(a,av);
	//}
	//else{
	//	Done=true;
	//}
}
