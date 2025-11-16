#include "XNickInspection.h"
#include "XGeneralFunc.h"
#include "XImageProcess.h"

NickInspectionLibrary::NickInspectionLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	NGPercentage	=25;
	RefBrightness	=200;
	EnableWhite		=true;
	LimitSize		=1000;
}

bool	NickInspectionLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,NGPercentage)==false){
		return false;
	}
	if(::Save(f,RefBrightness)==false){
		return false;
	}
	if(::Save(f,EnableWhite)==false){
		return false;
	}
	if(::Save(f,LimitSize)==false){
		return false;
	}
	if(LibList.Save(f)==false){
		return false;
	}
	return true;
}
bool	NickInspectionLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,NGPercentage)==false){
		return false;
	}
	if(::Load(f,RefBrightness)==false){
		return false;
	}
	if(::Load(f,EnableWhite)==false){
		return false;
	}
	if(::Load(f,LimitSize)==false){
		return false;
	}
	if(LibList.Load(f)==false){
		return false;
	}
	return true;
}

NickInspectionLibrary	&NickInspectionLibrary::operator=(const AlgorithmLibrary &src)
{
	const NickInspectionLibrary	*s=dynamic_cast<const NickInspectionLibrary *>(&src);

	NGPercentage	=s->NGPercentage;
	RefBrightness	=s->RefBrightness;
	EnableWhite		=s->EnableWhite;
	LimitSize		=s->LimitSize;
	LibList			=s->LibList;
	return *this;
}
void	NickInspectionLibrary::MakeBlocks(PureFlexAreaListContainer &Blocks
										,const BYTE **MaskMap
										,int Page)
{
	if(LimitSize==0)
		return;

	int	XByte	=(GetDotPerLine(Page)+7)/8;
	int	YLen	=GetMaxLines(Page);
	int	XNumb=GetDotPerLine(Page)/LimitSize;
	int	YNumb=GetMaxLines  (Page)/LimitSize;

	int	Mergin=LimitSize/6;

	for(int yn=0;yn<YNumb;yn++){
		int	y1=yn*LimitSize-Mergin;
		int	y2=(yn+1)*LimitSize+Mergin;
		if(y1<0)
			y1=0;
		if(y2>=GetMaxLines(Page))
			y2=GetMaxLines(Page);
		for(int xn=0;xn<XNumb;xn++){
			int	x1=xn*LimitSize-Mergin;
			int	x2=(xn+1)*LimitSize+Mergin;
			if(x1<0)
				x1=0;
			if(x2>=GetDotPerLine(Page))
				x2=GetDotPerLine(Page);

			PureFlexAreaListContainer FPack ;
			::PickupFlexArea(MaskMap ,XByte ,GetDotPerLine(Page),YLen ,FPack 
					,x1,y1,x2,y2);
			PureFlexAreaList *f;
			while((f=FPack.GetFirst())!=NULL){
				FPack.RemoveList(f);
				if(f->GetPatternByte()<10){
					delete	f;
				}
				else{
					Blocks.AppendList(f);
				}
			}
		}
	}
}


//==============================================================

NickInspectionLibraryContainer::NickInspectionLibraryContainer(LayersBase *base)
	:AlgorithmLibraryContainer(base)
{}