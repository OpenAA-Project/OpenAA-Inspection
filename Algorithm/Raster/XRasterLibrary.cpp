#include <QBuffer>
#include <QString>

#include "XRaster.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XRasterPacket.h"
#include "swap.h"
#include <omp.h>

#include "XFlexArea.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XGUIRasterPacket.h"
#include "XUndo.h"
#include "XCrossObj.h"
#include <float.h>
#include "XRasterLibrary.h"



RasterLibrary::RasterLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	MaxShrinkDot=0;
	MaxShiftDot	=0;

	ShrinkDot		=0;
	InsideEdgeWidth	=5;
	OutsideEdgeWidth=5;
}

RasterLibrary::~RasterLibrary(void)
{
}

bool	RasterLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=RasterVersion;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,MaxShrinkDot)==false)
		return false;
	if(::Save(f,MaxShiftDot)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,InsideEdgeWidth)==false)
		return false;
	if(::Save(f,OutsideEdgeWidth)==false)
		return false;
	if(AllocatedStaticLib.Save(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Save(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Save(f)==false)
		return false;
	return true;
}
bool	RasterLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,MaxShrinkDot)==false)
		return false;
	if(::Load(f,MaxShiftDot)==false)
		return false;
	if(::Load(f,ShrinkDot)==false)
		return false;
	if(::Load(f,InsideEdgeWidth)==false)
		return false;
	if(::Load(f,OutsideEdgeWidth)==false)
		return false;
	if(AllocatedStaticLib.Load(f)==false)
		return false;
	if(AllocatedInsideEdgeLib.Load(f)==false)
		return false;
	if(AllocatedOutsideEdgeLib.Load(f)==false)
		return false;

	return true;
}
RasterLibrary	&RasterLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((RasterLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

RasterLibraryContainer::RasterLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
RasterLibraryContainer::~RasterLibraryContainer(void)
{
}