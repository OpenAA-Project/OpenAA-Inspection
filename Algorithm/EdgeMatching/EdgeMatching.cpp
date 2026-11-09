#include "XAlgorithmDLL.h"
#include "XEdgeMatching.h"
#include "XEdgeMatchingLibrary.h"
#include "EditEdgeMatchingForm.h"

const char *sRoot = "Basic";
const char *sName = "EdgeMatching";

DEFFUNCEX bool DLL_GetOrganization(QString &str)
{
    str = "MEGATRADE";
    return true;
}

DEFFUNCEX WORD DLL_GetDLLType(void)
{
    return DLLAlgorithmMode;
}

DEFFUNCEX bool DLL_GetName(QString &Root, QString &Name)
{
    Root = sRoot;
    Name = sName;
    return true;
}

DEFFUNCEX WORD DLL_GetVersion(void)
{
    return EdgeMatchingVersion;
}

DEFFUNCEX const char *DLL_GetExplain(void)
{
    return "Edge Matching";
}

DEFFUNCEX void DLL_SetLanguage(LanguagePackage &Pkg, int LanguageCode)
{
}

DEFFUNCEX const char *DLL_GetBlobName(void)
{
    return "EdgeMatching";
}

DEFFUNCEX DWORD DLL_GetAlgorithmType(void)
{
    return AlgorithmBit_TypePreAlignment | AlgorithmBit_TypeAlignment;
}

DEFFUNCEX AlgorithmBase *DLL_InitialAlloc(LayersBase *Base)
{
    AlgorithmBase *base = new EdgeMatchingBase(Base);
    base->Initial(Base);
    return base;
}

DEFFUNCEX void DLL_Close(void)
{
}

DEFFUNCEX AlgorithmLibraryContainer *DLL_NewLibrary(LayersBase *Base)
{
    return new EdgeMatchingLibraryContainer(Base);
}

DEFFUNCEX int DLL_GetPriority(int AlgorithmBit_Type)
{
    if (AlgorithmBit_Type == PriorityType_ExecuteInitialAfterEdit) return 100000;
    if (AlgorithmBit_Type == PriorityType_ExecuteAlignment) return 100000;
    return 100;
}

DEFFUNCEX bool DLL_SaveItem(QIODevice *f, AlgorithmItemRoot *item)
{
    return ((EdgeMatchingItem *)item)->Save(f);
}

DEFFUNCEX bool DLL_LoadItem(QIODevice *f, AlgorithmItemRoot *item, LayersBase *LBase)
{
    return ((EdgeMatchingItem *)item)->Load(f, LBase);
}

DEFFUNCEX ResultBaseForAlgorithmRoot *DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
    return new ResultBaseForAlgorithmPI(parent);
}

 DEFFUNCEX QWidget *DLL_ShowAndSetItems(QWidget *parent, int32 Command, AlgorithmBase *InstBase, AlgorithmItemIndependentPack &Data, ShowAndSetItemsBaseClass *Something)
 {
     EditEdgeMatchingForm *DForm = new EditEdgeMatchingForm(InstBase->GetLayersBase());
     DForm->Initial(InstBase, Data);
     DForm->show();
     return DForm;
 }