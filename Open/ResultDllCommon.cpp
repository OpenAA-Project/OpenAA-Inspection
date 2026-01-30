/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
