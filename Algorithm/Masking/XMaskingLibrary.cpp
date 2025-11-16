#include "XMaskingLibrary.h"
#include "XGeneralFunc.h"
#include "XDataModelPageLayerItem.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMasking.h"

MaskingLibrary::MaskingLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	Operation=_Masking_Effective;
}

MaskingLibrary::~MaskingLibrary(void)
{
}

bool	MaskingLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	BYTE	d=(BYTE)Operation;
	if(::Save(f,d)==false)
		return false;
	if(LimitedLibraries.Save(f)==false)
		return false;
	return true;
}
bool	MaskingLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	Operation=(MaskingLibOperation)d;
	if(LimitedLibraries.Load(f)==false)
		return false;
	return true;
}

MaskingLibrary	&MaskingLibrary::operator=(const AlgorithmLibrary &src)
{
	MaskingLibrary	*s=(MaskingLibrary *)&src;
	Operation=s->Operation;
	LimitedLibraries	=s->LimitedLibraries;
	return *this;
}

void	MaskingLibrary::MakeAreaOnly(BYTE **TmpData,int page,int XByte ,int YLen,NPListPack<AlgorithmItemPLI> &ItemList)
{
	int	XLen=XByte*8;
	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpData,XByte,XLen,YLen ,FPack);

	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetLayersBase()->GetDotPerLine(page),GetLayersBase()->GetMaxLines(page));

		MaskingItem	*v=new MaskingItem();

		v->SetArea(*a);
		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		ItemList.AppendList(v);
	}
}