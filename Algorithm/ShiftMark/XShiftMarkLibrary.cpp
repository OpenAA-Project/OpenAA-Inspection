

#include "XShiftMarkLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XDataInLayer.h"
#include <QBuffer>
#include "XShiftMark.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


ShiftMarkLibrary::ShiftMarkLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	SearchDotEdge	=40;
	SearchDotMarkMin=200;
	SearchDotMarkMax=200;
	NGByLosingMark	=true;
	ThresholdLost	=60;		//消失判定しきい値（0-100)
	EnableMark		=true;
	ColorMatch		=true;
}

bool	ShiftMarkLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=5;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,SearchDotEdge)==false)
		return false;
	if(::Save(f,SearchDotMarkMin)==false)
		return false;
	if(::Save(f,SearchDotMarkMax)==false)
		return false;
	if(::Save(f,NGByLosingMark)==false)
		return false;
	if(::Save(f,ThresholdLost)==false)
		return false;
	if(::Save(f,EnableMark)==false)
		return false;
	if(::Save(f,ColorMatch)==false)
		return false;

	return true;
}
bool	ShiftMarkLibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,SearchDotEdge)==false)
		return false;
	if(Ver<=1){
		SearchDotMarkMin=0;
		if(::Load(f,SearchDotMarkMax)==false)
			return false;
	}
	else{
		if(::Load(f,SearchDotMarkMin)==false)
			return false;
		if(::Load(f,SearchDotMarkMax)==false)
			return false;
	}
	if(::Load(f,NGByLosingMark)==false)
		return false;
	if(::Load(f,ThresholdLost)==false)
		return false;
	if(Ver>=5){
		if(::Load(f,EnableMark)==false)
			return false;
		if(::Load(f,ColorMatch)==false)
			return false;
	}
	else{
		EnableMark=true;
		ColorMatch=true;
	}
	return true;
}



ShiftMarkLibrary	&ShiftMarkLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((ShiftMarkLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}


//==============================================================================
ShiftMarkLibraryContainer::ShiftMarkLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}


