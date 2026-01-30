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

#if	!defined(XMACROFUNCTION_H)
#define	XMACROFUNCTION_H

#include <QString>
#include <QStringList>
#include "XTypeDef.h"

class	GUIFormBase;
class	AlgorithmBase;

class	ExportFuncForMacro
{
public:
	QString		FuncName;
	QStringList	ArgName;
	QStringList	Explain;
	bool		(*DLL_ExcuteMacro)(GUIFormBase *Instance ,QStringList &Args);
	bool		(*DLL_ExcuteMacroAlgo)(AlgorithmBase *Instance ,QStringList &Args);

	ExportFuncForMacro(void){	DLL_ExcuteMacro=NULL;	DLL_ExcuteMacroAlgo=NULL;	}

};


class	DLLMacroFunc
{
	ExportFuncForMacro	*MacroFunctions;
	int					MacroFunctionCount;
public:
	DLLMacroFunc(void);
	virtual	~DLLMacroFunc(void);

	virtual	int		RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)	=0;

	ExportFuncForMacro	*SearchMacroFunc(const QString &FuncName);

	bool	ExecuteMacro(GUIFormBase *Instance
								,const QString &FunctionName ,const QString &Arg1=/**/""
															 ,const QString &Arg2=/**/""
															 ,const QString &Arg3=/**/""
															 ,const QString &Arg4=/**/""
															 ,const QString &Arg5=/**/""
															 ,const QString &Arg6=/**/""
															 ,const QString &Arg7=/**/""
															 ,const QString &Arg8=/**/""
															 ,const QString &Arg9=/**/""
															 ,const QString &Arg10=/**/"");
	void	SetupMacro(void);
	void	GetMacroNames(QStringList &Str);

};


#endif