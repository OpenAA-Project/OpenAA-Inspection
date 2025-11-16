#include "ResultCategorizer.h"
#include "XResultAnalizerDLL.h"
#include "XLanguageClass.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XPointer.h"
#include "XResult.h"
#include "swap.h"

const	char	*sRoot=/**/"ResultAnalizer";
const	char	*sName=/**/"ResultCategorizer";

DEFFUNCEX	void	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
}

DEFFUNCEX	bool	DLL_GetOrganization(QString &str)
{
	str=/**/"MEGATRADE";
	return true;
}
DEFFUNCEX	WORD	DLL_GetVersion(void)
{
	return 1;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangLibSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	ResultAnalizerItemBase	*DLL_Initial(LayersBase *base)
{
	return new ResultCategorizer(base);
}
DEFFUNCEX	void			DLL_Release(ResultAnalizerItemBase *handle)
{
	delete	handle;
}
DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEditPost			(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	ResultCategorizer	*d=(ResultCategorizer *)handle;
	d->Allocate();
	return _ER_true;
}
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspectionPost		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	ResultCategorizer	*d=(ResultCategorizer *)handle;
	d->ExecuteStartByInspection();
	return _ER_true;
}
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingPost		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	ResultCategorizer	*d=(ResultCategorizer *)handle;
	return d->Execute(Res);
}
