#include "XDXFOperationLibrary.h"

DXFOperationLibrary::DXFOperationLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	MaxEnlargeDot	=2;
	MaxShrinkDot	=2;
	MaxShiftDot		=2;
	MaxAngleRadius	=1;
	UnstableZone	=2;
}
DXFOperationLibrary::~DXFOperationLibrary(void)
{
}

bool	DXFOperationLibrary::SaveBlob(QIODevice *f)
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
bool	DXFOperationLibrary::LoadBlob(QIODevice *f)
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

DXFOperationLibrary	&DXFOperationLibrary::operator=(const AlgorithmLibrary &src)
{
	const	DXFOperationLibrary	*s=dynamic_cast<const DXFOperationLibrary *>(&src);
	MaxEnlargeDot	=s->MaxEnlargeDot;
	MaxShrinkDot	=s->MaxShrinkDot;
	MaxShiftDot		=s->MaxShiftDot;
	MaxAngleRadius	=s->MaxAngleRadius;
	UnstableZone	=s->UnstableZone;
	return *this;
}