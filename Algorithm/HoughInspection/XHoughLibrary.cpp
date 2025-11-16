#include "XHoughInspection.h"
#include "XGeneralFunc.h"
#include "XImageProcess.h"

HoughLibrary::HoughLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	ZoneWidth		=10;	
	MaxIsolation	=10;
	MinPixels		=10000;
	NGLength		=100;
	BinarizedLength	=200;
	PickupL			=0;
	PickupH			=255;
	RemoveDynamicMask=true;
	ReducedSize		=5;
	MaxLineCount	=100;
	MinNGWidth		=0;
	MaxNGWidth		=10;
	MinAverageContinuous	=20;
	DynamicBinarize	=false;
}

bool	HoughLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=7;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,ZoneWidth)==false){
		return false;
	}
	if(::Save(f,MaxIsolation)==false){
		return false;
	}
	if(::Save(f,MinPixels)==false){
		return false;
	}
	if(::Save(f,NGLength)==false){
		return false;
	}
	if(::Save(f,BinarizedLength)==false){
		return false;
	}
	if(::Save(f,PickupL)==false){
		return false;
	}
	if(::Save(f,PickupH)==false){
		return false;
	}
	if(::Save(f,RemoveDynamicMask)==false){
		return false;
	}
	if(::Save(f,ReducedSize)==false){
		return false;
	}
	if(::Save(f,MaxLineCount)==false){
		return false;
	}
	if(::Save(f,MaxNGWidth)==false){
		return false;
	}
	if(::Save(f,MinNGWidth)==false){
		return false;
	}
	if(::Save(f,MinAverageContinuous)==false){
		return false;
	}
	if(::Save(f,DynamicBinarize)==false){
		return false;
	}
	return true;
}
bool	HoughLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,ZoneWidth)==false){
		return false;
	}
	if(::Load(f,MaxIsolation)==false){
		return false;
	}
	if(::Load(f,MinPixels)==false){
		return false;
	}
	if(::Load(f,NGLength)==false){
		return false;
	}
	if(::Load(f,BinarizedLength)==false){
		return false;
	}
	if(::Load(f,PickupL)==false){
		return false;
	}
	if(::Load(f,PickupH)==false){
		return false;
	}
	if(::Load(f,RemoveDynamicMask)==false){
		return false;
	}
	if(Ver>=2){
		if(::Load(f,ReducedSize)==false){
			return false;
		}
	}
	if(Ver>=3){
		if(::Load(f,MaxLineCount)==false){
			return false;
		}
	}	
	if(Ver>=4){
		if(::Load(f,MaxNGWidth)==false){
			return false;
		}
	}
	if(Ver>=5){
		if(::Load(f,MinNGWidth)==false){
			return false;
		}
	}	
	if(Ver>=6){
		if(::Load(f,MinAverageContinuous)==false){
			return false;
		}
	}
	if(Ver>=7){
		if(::Load(f,DynamicBinarize)==false){
			return false;
		}
	}
	return true;
}

HoughLibrary	&HoughLibrary::operator=(const AlgorithmLibrary &src)
{
	const HoughLibrary	*s=dynamic_cast<const HoughLibrary *>(&src);
	ZoneWidth		=s->ZoneWidth;	
	MaxIsolation	=s->MaxIsolation;
	MinPixels		=s->MinPixels;
	NGLength		=s->NGLength;
	BinarizedLength	=s->BinarizedLength;
	PickupL			=s->PickupL;
	PickupH			=s->PickupH;
	RemoveDynamicMask=s->RemoveDynamicMask;
	ReducedSize		=s->ReducedSize;
	MaxLineCount	=s->MaxLineCount;
	MinNGWidth		=s->MinNGWidth;
	MaxNGWidth		=s->MaxNGWidth;
	MinAverageContinuous	=s->MinAverageContinuous;
	DynamicBinarize	=s->DynamicBinarize;
	return *this;
}


//==============================================================

HoughLibraryContainer::HoughLibraryContainer(LayersBase *base)
	:AlgorithmLibraryContainer(base)
{}