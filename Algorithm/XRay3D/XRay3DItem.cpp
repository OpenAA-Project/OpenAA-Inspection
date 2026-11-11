/*
 * Copyright (C) 2023
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


#include "XXRay3D.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//=====================================================================================

XRay3DThreshold::XRay3DThreshold(XRay3DItem *parent)
:AlgorithmThreshold(parent)
{
	SearchDot		=50;
}

void	XRay3DThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const XRay3DThreshold *s=(const XRay3DThreshold *)&src;
	SearchDot		=s->SearchDot;
}
bool	XRay3DThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const XRay3DThreshold *s=(const XRay3DThreshold *)&src;
	if(SearchDot	==s->SearchDot)
		return true;
	return false;
}
bool	XRay3DThreshold::Save(QIODevice *f)
{
	WORD	Ver=XRay3DVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,SearchDot)==false)
		return false;

	return true;
}

bool	XRay3DThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,SearchDot)==false)
		return false;

	return true;
}
//===========================================================================================

XRay3DItem::XRay3DItem(void)
{

}

XRay3DItem::~XRay3DItem(void)
{

}

XRay3DItem &XRay3DItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(*((XRay3DItem *)&src));


	return *this;
}

void	XRay3DItem::CopyThreshold(XRay3DItem &src)
{
	GetThresholdW()->CopyFrom(*((XRay3DThreshold *)src.GetThresholdR()));
}

void	XRay3DItem::CopyThresholdOnly(XRay3DItem &src)
{
	GetThresholdW()->CopyFrom(*((XRay3DThreshold *)src.GetThresholdR()));
}

void	XRay3DItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((XRay3DItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((XRay3DItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((XRay3DItem *)Data));
		}
	}
}

void	XRay3DItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	XRay3DItem	*ASrc=dynamic_cast<XRay3DItem *>(src);
}
void	XRay3DItem::CopyArea(XRay3DItem &src)
{
	SetArea(src.GetArea());
}

ExeResult	XRay3DItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	int	cx,cy;
	GetCenter(cx,cy);
	int	XLen=GetArea().GetWidth();
	int	YLen=GetArea().GetHeight();

	const	XRay3DThreshold	*RThr=GetThresholdR();

	return Ret;
}

ExeResult	XRay3DItem::ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ExeResult	Ret=AlgorithmItemPI::ExecutePreProcessing	(ExeID ,ThreadNo,Res);
	
	return Ret;
}

void	XRay3DItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	XRay3DDrawAttr	*BAttr=dynamic_cast<XRay3DDrawAttr *>(Attr);
	if(BAttr!=NULL){

		QColor	SavedColor;
		SavedColor=BAttr->NormalColor;
		switch(GetLibID()&7){
			case 0:	BAttr->NormalColor=BAttr->BlockColor0;	break;
			case 1:	BAttr->NormalColor=BAttr->BlockColor1;	break;
			case 2:	BAttr->NormalColor=BAttr->BlockColor2;	break;
			case 3:	BAttr->NormalColor=BAttr->BlockColor3;	break;
			case 4:	BAttr->NormalColor=BAttr->BlockColor4;	break;
			case 5:	BAttr->NormalColor=BAttr->BlockColor5;	break;
			case 6:	BAttr->NormalColor=BAttr->BlockColor6;	break;
			case 7:	BAttr->NormalColor=BAttr->BlockColor7;	break;
		}
		AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

void	XRay3DItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		QColor	c=Qt::green;
		c.setAlpha(100);
		GetArea().Draw(0,0,&IData ,c.rgba()
						,ZoomRate ,MovX ,MovY);

		PData.setPen(Qt::red);
	}
}