#include "ThresholdList.h"
#include "XDLLType.h"
#include "XPQSystemRunnerDLL.h"
#include "ThresholdListForm.h"

const	char	*sRoot=/**/"ChronologicalSetting";
const	char	*sName=/**/"ThresholdList";


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

const const char	*DLL_GetExplain(void)
{
	return /**/"Chronological Setting - ThresholdList";
}

void	DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="Copyright(c) MEGATRADE 2021.10";
	return true;
}

PQSystemRunner	*DLL_CreateRunner(LayersBase *Base)
{
	return new ThresholdListForm(Base,sRoot,sName);
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
