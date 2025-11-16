#include "XGerberAperture.h"
#include "XGerberFastLibrary.h"

GerberFastLibrary::GerberFastLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	MaxEnlargeDot	=2;
	MaxShrinkDot	=2;
	MaxShiftDot		=2;
	MaxAngleRadius	=1;
	UnstableZone	=2;
}
GerberFastLibrary::~GerberFastLibrary(void)
{
}

bool	GerberFastLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,MaxEnlargeDot)==false)
		return false;
	if(::Save(f,MaxShrinkDot)==false)
		return false;
	if(::Save(f,MaxShiftDot)==false)
		return false;
	if(::Save(f,MaxAngleRadius)==false)
		return false;
	if(::Save(f,UnstableZone)==false)
		return false;
	return true;
}
bool	GerberFastLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,MaxEnlargeDot)==false)
		return false;
	if(::Load(f,MaxShrinkDot)==false)
		return false;
	if(::Load(f,MaxShiftDot)==false)
		return false;
	if(::Load(f,MaxAngleRadius)==false)
		return false;
	if(::Load(f,UnstableZone)==false)
		return false;
	return true;
}

GerberFastLibrary	&GerberFastLibrary::operator=(const AlgorithmLibrary &src)
{
	const GerberFastLibrary	*s=dynamic_cast<const GerberFastLibrary *>(&src);
	MaxEnlargeDot	=s->MaxEnlargeDot;
	MaxShrinkDot	=s->MaxShrinkDot;
	MaxShiftDot		=s->MaxShiftDot;
	MaxAngleRadius	=s->MaxAngleRadius;
	UnstableZone	=s->UnstableZone;
	return *this;
}