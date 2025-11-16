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