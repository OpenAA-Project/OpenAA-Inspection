#include "XMultiSpectralLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMultiSpectral.h"

MultiSpectralLibrary::MultiSpectralLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	SearchDot		=2;
	ThresholdLength	=15;
	OKDot			=15;
}

MultiSpectralLibrary::~MultiSpectralLibrary(void)
{
}

bool	MultiSpectralLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,ThresholdLength)==false)
		return false;
	if(::Save(f,OKDot)==false)
		return false;
	return true;
}
bool	MultiSpectralLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,ThresholdLength)==false)
		return false;
	if(::Load(f,OKDot)==false)
		return false;
	return true;
}

MultiSpectralLibrary	&MultiSpectralLibrary::operator=(const AlgorithmLibrary &src)
{
	MultiSpectralLibrary	*s=(MultiSpectralLibrary *)&src;
	SearchDot		=s->SearchDot;
	ThresholdLength	=s->ThresholdLength;
	return *this;
}
