#include "RasterInspection.h"
#include "XAlgorithmDLL.h"
#include "XRasterInspection.h"
#include "XRasterInspectionLibrary.h"
#include "XDirectCommPacket.h"
#include "AdjustItemForm.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"RasterInspection";

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
	return RasterInspectionVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Raster inspection";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"RasterInspectionIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	RasterInspectionBase	*base=new RasterInspectionBase(Base);
	base->Initial(Base);


	//(*Base)=new SlaveCommReqLibraryInMaskOfRasterInspection(Base,sRoot,sName);
	//(*Base)=new SlaveCommAckLibraryInMaskOfRasterInspection(Base,sRoot,sName);

	//(*Base)=new GUICmdReqPanelImage	(Base,sRoot,sName);
	//(*Base)=new GUICmdAckPanelImage	(Base,sRoot,sName);
	//(*Base)=new GUICmdReqItemInfo	(Base,sRoot,sName);
	//(*Base)=new GUICmdAckItemInfo	(Base,sRoot,sName);
	//(*Base)=new GUICmdSendMasterPositions	(Base,sRoot,sName);

	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new RasterInspectionLibraryContainer(Base);
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeProcessing | AlgorithmBit_TypeDynamicMasking;
}

DEFFUNCEX	void		DLL_RemoveAddedResultData(AddedDataClass *d)
{
	delete	d;
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	AdjustItemForm	*DForm=new AdjustItemForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((RasterInspectionItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((RasterInspectionItem *)item)->Load(f,LBase);
}
