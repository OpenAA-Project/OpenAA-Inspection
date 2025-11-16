//#include "ShiftMarkResource.h"
#include "ShiftMark.h"
#include "XAlgorithmDLL.h"
#include "XShiftMark.h"
#include "XShiftMarkLibrary.h"
#include "CheckShiftMarkForm.h"
#include "XDirectCommPacket.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"ShiftMark";

DEFFUNCEX	bool		DLL_GetOrganization(QString &str)
{
	str=/**/"MEGATRADE";
	return true;
}
DEFFUNCEX	WORD		DLL_GetDLLType(void)
{
	return DLLAlgorithmMode;
}
DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return true;
}
DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return ShiftMarkVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "見当ずれ検査";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"ShiftMarkIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	ShiftMarkBase	*base=new ShiftMarkBase(Base);
	base->Initial(Base);

	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new ShiftMarkLibraryContainer(Base);
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeProcessing;
}

DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d)
{
	delete	d;
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	CheckShiftMarkForm	*DForm=new CheckShiftMarkForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((ShiftMarkItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((ShiftMarkItem *)item)->Load(f,LBase);
}
