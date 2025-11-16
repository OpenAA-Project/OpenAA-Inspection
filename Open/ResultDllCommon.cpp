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
#include "XResultDLL.h"
#include "XLanguageClass.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"

extern	LangSolverNew	LangLibSolver;

class	ResultInspection;

DEFFUNCEX	WORD	DLL_GetDLLType(void)
{
	return(DLLResultMode);
}

DEFFUNCEX	void	DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode)
{
	LangLibSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEdit		(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecuteInitialAfterEdit(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspection	(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecuteStartByInspection(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecutePreAlignment			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecutePreAlignment(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteAlignment			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecuteAlignment(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecutePreProcessing		(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecutePreProcessing(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteProcessing			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecuteProcessing(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingRevived	(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecuteProcessingRevived(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecutePostProcessing		(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecutePostProcessing(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecutePreScanning			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecutePreScanning(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteScanning				(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecuteScanning(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecutePostScanning			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecutePostScanning(ExeID ,Res);
}
DEFFUNCEX	ExeResult	DLL_ExecuteManageResult			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res)
{
	return inst->ExecuteManageResult(ExeID ,Res);
}

DEFFUNCEX	void	DLL_InitialQt(QApplication *AppBase)
{
	static	bool	Done=false;
	if(qApp==NULL){
		int	a=0;
		char	*av[10];
		av[0]=/**/"";
		//QApplication	*Q=new QApplication(a,av);
	}
	else{
		Done=true;
	}
}

