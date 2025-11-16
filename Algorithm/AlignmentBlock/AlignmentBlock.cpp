#include "AlignmentBlock.h"
#include "XAlgorithmDLL.h"
#include "XAlignmentBlock.h"
#include "XDirectCommPacket.h"
#include "AdjustAlignmentBlockForm.h"
#include "XAlignmentBlockLibrary.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"AlignmentBlock";

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
	return AlignmentBlockVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Alignment block";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"AlignmentBlockIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	AlignmentBlockBase	*base=new AlignmentBlockBase(Base);
	base->Initial(Base);

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
	return new AlignmentBlockLibraryContainer(Base);
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeAlignment;
}

DEFFUNCEX	void		DLL_RemoveAddedResultData(AddedDataClass *d)
{
	delete	d;
}

DEFFUNCEX	AlignmentPacketBase	*DLL_GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY ,AlgorithmItemRoot *Item,bool FromGlobal)
{
	AlignmentBlockBase	*abase=dynamic_cast<AlignmentBlockBase *>(base);
	if(abase!=NULL){
		return ((AlignmentBlockInPage *)(abase->GetPageDataPhase(Item->GetPhaseCode())
											->GetPageData(localPage)))
											->AppendAlignmentBlockPacket2D(Item,localX,localY,FromGlobal);
	}
	return NULL;
}
DEFFUNCEX	int			DLL_GetPriority(int AlgorithmBit_Type)
{
	if(AlgorithmBit_Type==PriorityType_ExecuteInitialAfterEdit)
		return 10;
	return 100;
}
DEFFUNCEX	void	DLL_GetAlignmentForProcessing(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet)
{
	AlignmentBlockBase	*abase=dynamic_cast<AlignmentBlockBase *>(base);
	if(abase!=NULL){
		AlignmentPacket2D	*p2d=static_cast<AlignmentPacket2D *>(&Packet);
		if(p2d!=NULL)
			((AlignmentBlockInPage *)(abase->GetPageData(localPage)))->GetAlignmentBlock(*p2d);
	}
}
DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	AdjustAlignmentBlockForm	*DForm=new AdjustAlignmentBlockForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((AlignmentBlockItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((AlignmentBlockItem *)item)->Load(f,LBase);
}
