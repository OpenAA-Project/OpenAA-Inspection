#include "PQSystemSetting.h"
#include "PQSystemSettingForm.h"
#include "XDLLType.h"
#include "XPQSystemRunnerDLL.h"
#include "XLanguageClass.h"

const	char	*sRoot=/**/"System";
const	char	*sName=/**/"Setting";

extern	LangSolverNew	LangLibSolver;

bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return true;
}

WORD	DLL_GetDLLType(void)
{
	return DLLPQSystemRunner;
}
WORD	DLL_GetVersion(void)
{
	return 1;
}

const char	*DLL_GetExplain(void)
{
	return /**/"PQSystem setting";
}

void	DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode)
{
	LangLibSolver.SetLanguage(Pkg,LanguageCode);
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="Copyright(c) MEGATRADE 2022.5";
	return true;
}

PQSystemRunner	*DLL_CreateRunner(LayersBase *Base)
{
	return new PQSystemSettingForm(Base,sRoot,sName);
}

void	DLL_CloseRunner(PQSystemRunner *handle)
{
	delete	handle;
}

void	DLL_InitialQt(QApplication *AppBase)
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
