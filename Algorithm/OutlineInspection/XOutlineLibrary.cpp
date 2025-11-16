/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\OutlineInspection\XOutlineInspect.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "OutlineInspectionResource.h"

#define	_USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XOutlineInspect.h"
#include "XOutlineLibrary.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XParamGlobal.h"
#include "XPSpline.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XMaskingFromGeneral.h"
#include "XDisplayBitImage.h"
#include <omp.h>
#include "XOutlineAlgoPacket.h"
#include "NGTypeDialog.h"
#include "MonoNGTypeDialog.h"



OutlineInspectLibNGTypeItem::OutlineInspectLibNGTypeItem(LayersBase *base,AlgorithmLibraryContainer *lib)
	:LibNGTypeItem(base)
{
	Lib=lib;
	MinSize=0;
	MaxSize=9999;
	MinRoundRate=0;
	MaxRoundRate=100;
}

bool	OutlineInspectLibNGTypeItem::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(ColorZone.Save(f)==false)
		return false;
	if(::Save(f,MinSize)==false)
		return false;
	if(::Save(f,MaxSize)==false)
		return false;
	if(::Save(f,MinRoundRate)==false)
		return false;
	if(::Save(f,MaxRoundRate)==false)
		return false;
	return true;
}
bool	OutlineInspectLibNGTypeItem::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(ColorZone.Load(f)==false)
		return false;
	if(::Load(f,MinSize)==false)
		return false;
	if(::Load(f,MaxSize)==false)
		return false;
	if(::Load(f,MinRoundRate)==false)
		return false;
	if(::Load(f,MaxRoundRate)==false)
		return false;
	return true;
}

bool	OutlineInspectLibNGTypeItem::ShowSetting(void)
{
	if(Lib->GetLayersBase()->GetParamGlobal()->GetLayerNumb()==1){
		MonoNGTypeDialog	D(Lib->GetLayersBase(),this);
		D.exec();
		return true;
	}
	else{
		NGTypeDialog	D(Lib->GetLayersBase(),this);
		D.exec();
		return true;
	}
}

//============================================================

OutlineInspectLibrary::OutlineInspectLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	TransDot	=2;	//輪郭ばらつきドット
	InsideWidth	=3;
	OutsideWidth=3;
	NoiseDot	=1;
	ChoppedLength	=100;
	Priority	=0;
	MinAreaDot		=0;
	MaxAreaDot		=10000000;
	MinAreaSize		=0;
	MaxAreaSize		=100000;
	InsideTrWidth	=1;
	OutsideTrWidth	=1;
	MatchSlideOnMaster	=true;

	InsideNOKDot	=5;
	InsideNMergin	=10;
	OutsideNOKDot	=5;
	OutsideNMergin	=10;

	InsideBOKDot	=5;
	InsideBMergin	=10;
	OutsideBOKDot	=5;
	OutsideBMergin	=10;

	EffectiveNInside	=true;
	EffectiveNOutside	=true;
	EffectiveBInside	=false;
	EffectiveBOutside	=true;

	SelfSearch	=4;		/*	検査時　探索距離	*/
	AdjustMode	=true;
	AdjustLimitLInside	=20;
	AdjustLimitHInside	=20;
	AdjustLimitLOutside	=20;
	AdjustLimitHOutside	=20;
	DiffMode	=false;
	AbsMode		=false;
}

bool	OutlineInspectLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=OutlineInspectionVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(PickupColor.Save(f)==false){
		return false;
	}
	if(::Save(f,TransDot)==false){
		return false;
	}
	if(::Save(f,InsideWidth)==false){
		return false;
	}
	if(::Save(f,OutsideWidth)==false){
		return false;
	}
	if(::Save(f,NoiseDot)==false){
		return false;
	}
	if(::Save(f,ChoppedLength)==false){
		return false;
	}
	if(::Save(f,Priority)==false){
		return false;
	}
	if(::Save(f,MinAreaDot)==false){
		return false;
	}
	if(::Save(f,MaxAreaDot)==false){
		return false;
	}
	if(::Save(f,MinAreaSize)==false){
		return false;
	}
	if(::Save(f,MaxAreaSize)==false){
		return false;
	}

	if(::Save(f,InsideTrWidth)==false){
		return false;
	}
	if(::Save(f,OutsideTrWidth)==false){
		return false;
	}

	if(InsideNOKColor.Save(f)==false){
		return false;
	}
	if(InsideNTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,InsideNOKDot)==false){
		return false;
	}
	if(::Save(f,InsideNMergin)==false){
		return false;
	}
	if(OutsideNOKColor.Save(f)==false){
		return false;
	}
	if(OutsideNTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,OutsideNOKDot)==false){
		return false;
	}
	if(::Save(f,OutsideNMergin)==false){
		return false;
	}

	if(InsideBOKColor.Save(f)==false){
		return false;
	}
	if(InsideBTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,InsideBOKDot)==false){
		return false;
	}
	if(::Save(f,InsideBMergin)==false){
		return false;
	}
	if(OutsideBOKColor.Save(f)==false){
		return false;
	}
	if(OutsideBTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,OutsideBOKDot)==false){
		return false;
	}
	if(::Save(f,OutsideBMergin)==false){
		return false;
	}

	if(::Save(f,EffectiveNInside)==false){
		return false;
	}
	if(::Save(f,EffectiveNOutside)==false){
		return false;
	}
	if(::Save(f,EffectiveBInside)==false){
		return false;
	}
	if(::Save(f,EffectiveBOutside)==false){
		return false;
	}

	if(::Save(f,SelfSearch)==false){
		return false;
	}
	if(::Save(f,AdjustMode)==false){
		return false;
	}
	if(::Save(f,AdjustLimitLInside)==false){
		return false;
	}
	if(::Save(f,AdjustLimitHInside)==false){
		return false;
	}
	if(::Save(f,AdjustLimitLOutside)==false){
		return false;
	}
	if(::Save(f,AdjustLimitHOutside)==false){
		return false;
	}

	if(::Save(f,MatchSlideOnMaster)==false){
		return false;
	}

	if(::Save(f,DiffMode)==false){
		return false;
	}
	if(::Save(f,AbsMode)==false){
		return false;
	}

	return true;
}
bool	OutlineInspectLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(PickupColor.Load(f)==false){
		return false;
	}
	if(::Load(f,TransDot)==false){
		return false;
	}
	if(::Load(f,InsideWidth)==false){
		return false;
	}
	if(::Load(f,OutsideWidth)==false){
		return false;
	}
	if(::Load(f,NoiseDot)==false){
		return false;
	}
	if(::Load(f,ChoppedLength)==false){
		return false;
	}
	if(::Load(f,Priority)==false){
		return false;
	}
	if(::Load(f,MinAreaDot)==false){
		return false;
	}
	if(::Load(f,MaxAreaDot)==false){
		return false;
	}
	if(::Load(f,MinAreaSize)==false){
		return false;
	}
	if(::Load(f,MaxAreaSize)==false){
		return false;
	}

	if(::Load(f,InsideTrWidth)==false){
		return false;
	}
	if(::Load(f,OutsideTrWidth)==false){
		return false;
	}

	if(InsideNOKColor.Load(f)==false){
		return false;
	}
	if(InsideNTrOKColor.Load(f)==false){
		return false;
	}
	if(::Load(f,InsideNOKDot)==false){
		return false;
	}
	if(::Load(f,InsideNMergin)==false){
		return false;
	}
	if(OutsideNOKColor.Load(f)==false){
		return false;
	}
	if(OutsideNTrOKColor.Load(f)==false){
		return false;
	}
	if(::Load(f,OutsideNOKDot)==false){
		return false;
	}
	if(::Load(f,OutsideNMergin)==false){
		return false;
	}

	if(Ver>=2){
		if(InsideBOKColor.Load(f)==false){
			return false;
		}
		if(InsideBTrOKColor.Load(f)==false){
			return false;
		}
		if(::Load(f,InsideBOKDot)==false){
			return false;
		}
		if(::Load(f,InsideBMergin)==false){
			return false;
		}
		if(OutsideBOKColor.Load(f)==false){
			return false;
		}
		if(OutsideBTrOKColor.Load(f)==false){
			return false;
		}
		if(::Load(f,OutsideBOKDot)==false){
			return false;
		}
		if(::Load(f,OutsideBMergin)==false){
			return false;
		}
	}
	if(Ver>=3){
		if(::Load(f,EffectiveNInside)==false){
			return false;
		}
		if(::Load(f,EffectiveNOutside)==false){
			return false;
		}
		if(::Load(f,EffectiveBInside)==false){
			return false;
		}
		if(::Load(f,EffectiveBOutside)==false){
			return false;
		}
	}
	else{
		EffectiveNInside	=true;
		EffectiveNOutside	=true;
		EffectiveBInside	=false;
		EffectiveBOutside	=true;
	}

	if(::Load(f,SelfSearch)==false){
		return false;
	}
	if(::Load(f,AdjustMode)==false){
		return false;
	}
	if(::Load(f,AdjustLimitLInside)==false){
		return false;
	}
	if(::Load(f,AdjustLimitHInside)==false){
		return false;
	}
	AdjustLimitLOutside=AdjustLimitLInside;
	AdjustLimitHOutside=AdjustLimitHInside;
	if(Ver>=5){
		if(::Load(f,AdjustLimitLOutside)==false){
			return false;
		}
		if(::Load(f,AdjustLimitHOutside)==false){
			return false;
		}
	}

	if(Ver>=4){
		if(::Load(f,MatchSlideOnMaster)==false){
			return false;
		}
		if(::Load(f,DiffMode)==false){
			return false;
		}
	}
	if(Ver>=6){
		if(::Load(f,AbsMode)==false){
			return false;
		}
	}
	return true;}

OutlineInspectLibrary	&OutlineInspectLibrary::operator=(const AlgorithmLibrary &src)
{
	const OutlineInspectLibrary	*s=dynamic_cast<const OutlineInspectLibrary *>(&src);

	if(s!=NULL){
		PickupColor		=s->PickupColor;
		TransDot		=s->TransDot;	//輪郭ばらつきドット
		InsideWidth		=s->InsideWidth;
		OutsideWidth	=s->OutsideWidth;;
		NoiseDot		=s->NoiseDot;
		ChoppedLength	=s->ChoppedLength;
		Priority		=s->Priority;
		MinAreaDot		=s->MinAreaDot;
		MaxAreaDot		=s->MaxAreaDot;
		MinAreaSize		=s->MinAreaSize;
		MaxAreaSize		=s->MaxAreaSize;
		InsideTrWidth	=s->InsideTrWidth;
		OutsideTrWidth	=s->OutsideTrWidth;
		MatchSlideOnMaster	=s->MatchSlideOnMaster;

		//検査時のデータ
		InsideNOKColor		=s->InsideNOKColor;
		InsideNTrOKColor	=s->InsideNTrOKColor;
		InsideNOKDot		=s->InsideNOKDot;
		OutsideNOKColor		=s->OutsideNOKColor;
		OutsideNTrOKColor	=s->OutsideNTrOKColor;
		OutsideNOKDot		=s->OutsideNOKDot;

		InsideBOKColor		=s->InsideBOKColor;
		InsideBTrOKColor	=s->InsideBTrOKColor;
		InsideBOKDot		=s->InsideBOKDot;
		OutsideBOKColor		=s->OutsideBOKColor;
		OutsideBTrOKColor	=s->OutsideBTrOKColor;
		OutsideBOKDot		=s->OutsideBOKDot;

		EffectiveNInside	=s->EffectiveNInside;
		EffectiveNOutside	=s->EffectiveNOutside;
		EffectiveBInside	=s->EffectiveBInside;
		EffectiveBOutside	=s->EffectiveBOutside;

		SelfSearch			=s->SelfSearch;		/*	検査時　探索距離	*/
		AdjustMode			=s->AdjustMode;
		AdjustLimitLInside	=s->AdjustLimitLInside;
		AdjustLimitHInside	=s->AdjustLimitHInside;
		AdjustLimitLOutside	=s->AdjustLimitLOutside;
		AdjustLimitHOutside	=s->AdjustLimitHOutside;
		DiffMode			=s->DiffMode;
		AbsMode				=s->AbsMode;
	}
	return *this;
}
