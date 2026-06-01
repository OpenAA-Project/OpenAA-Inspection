/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "XColorCorrector.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"

ColorCorrectorThresholdBase::ColorCorrectorThresholdBase(AlgorithmItemRoot *parent)
		:AlgorithmThreshold(parent){}
void	ColorCorrectorThresholdBase::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	ColorCorrectorThresholdBase::IsEqual(const AlgorithmThreshold &src)	const
{
	return true;
}
bool	ColorCorrectorThresholdBase::Save(QIODevice *f)	
{
	return true;
}
bool	ColorCorrectorThresholdBase::Load(QIODevice *f)	
{
	return true;
}
ColorCorrectorItemBase::ColorCorrectorItemBase(void)
{
}

void	ColorCorrectorItemBase::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ColorCorrectorDrawAttr	*MAttr=(ColorCorrectorDrawAttr *)Attr;
	if(GetItemClassType()==(int)MAttr->VType){
		AlgorithmItemPITemplate<ColorCorrectorInPage,ColorCorrectorBase>::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
//=====================================================================================

ColorShiftVThreshold::ColorShiftVThreshold(ColorShiftVItem *parent)
:ColorCorrectorThresholdBase(parent)
{
	BandHeight	=0;
	SearchXDot	=0;
	SearchYDot	=0;
	RegularLayer=1;
}

bool	ColorShiftVThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const ColorShiftVThreshold	*s=dynamic_cast<const ColorShiftVThreshold *>(&src);
	if(s!=NULL){
		if(ColorCorrectorThresholdBase::IsEqual(src)==true
		&& BandHeight	==s->BandHeight
		&& SearchXDot	==s->SearchXDot
		&& SearchYDot	==s->SearchYDot
		&& RegularLayer	==s->RegularLayer)
			return true;
	}
	return false;
}
void	ColorShiftVThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const ColorShiftVThreshold	*s=dynamic_cast<const ColorShiftVThreshold *>(&src);
	if(s!=NULL){
		ColorCorrectorThresholdBase::CopyFrom(src);
		BandHeight	=s->BandHeight;
		SearchXDot	=s->SearchXDot;
		SearchYDot	=s->SearchYDot;
		RegularLayer=s->RegularLayer;
	}
}
bool	ColorShiftVThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);

	if(::Save(file,BandHeight)==false)
		return(false);
	if(::Save(file,SearchXDot)==false)
		return(false);
	if(::Save(file,SearchYDot)==false)
		return(false);
	if(::Save(file,RegularLayer)==false)
		return(false);
	return(true);
}
bool	ColorShiftVThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);

	if(::Load(file,BandHeight)==false)
		return(false);
	if(::Load(file,SearchXDot)==false)
		return(false);
	if(::Load(file,SearchYDot)==false)
		return(false);
	if(::Load(file,RegularLayer)==false)
		return(false);

	return(true);
}

//-----------------------------------------------------------------
ColorShiftVItem::ColorShiftVItem(void)
{
}

ExeResult	ColorShiftVItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);


	return Ret;
}

ExeResult	ColorShiftVItem::ExecutePreAlignment		(int ExeID,int ThreadNo,ResultInItemRoot *Res)
{
	ExeResult	Ret=AlgorithmItemPI::ExecutePreAlignment(ExeID ,ThreadNo,Res);

	return Ret;
}

//=====================================================================================

ColorChangeVThreshold::ColorChangeVThreshold(ColorChangeVItem *parent)
:ColorCorrectorThresholdBase(parent)
{
}

bool	ColorChangeVThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const ColorChangeVThreshold	*s=dynamic_cast<const ColorChangeVThreshold *>(&src);
	if(s!=NULL){
		if(ColorCorrectorThresholdBase::IsEqual(src)==true)
			return true;
	}
	return false;
}
void	ColorChangeVThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const ColorChangeVThreshold	*s=dynamic_cast<const ColorChangeVThreshold *>(&src);
	if(s!=NULL){
		ColorCorrectorThresholdBase::CopyFrom(src);
	}
}
bool	ColorChangeVThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(ColorCorrectorThresholdBase::Save(file)==false)
		return(false);

	return(true);
}
bool	ColorChangeVThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(ColorCorrectorThresholdBase::Load(file)==false)
		return(false);

	return(true);
}

//-----------------------------------------------------------------
ColorChangeVItem::ColorChangeVItem(void)
{
}

ExeResult	ColorChangeVItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);


	return Ret;
}
ExeResult	ColorChangeVItem::ExecutePreAlignment		(int ExeID,int ThreadNo,ResultInItemRoot *Res)
{
	ExeResult	Ret=AlgorithmItemPI::ExecutePreAlignment(ExeID ,ThreadNo,Res);

	return Ret;
}


//=====================================================================================