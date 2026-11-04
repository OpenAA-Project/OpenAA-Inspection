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

//#include "XAlignmentShiftRotationResource.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentShiftRotation.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDisplayImagePacket.h"
#include "XYCross.h"
#include "XAlignmentCommon.h"
#include "XImageProcess.h"
#include "XAlignmentShiftRotationCommon.h"
#include "XPacketAlignmentShiftRotation.h"


AlignmentShiftRotationThreshold::AlignmentShiftRotationThreshold(AlignmentShiftRotationItem *parent)
	:AlgorithmThreshold(parent)
{
	Threshold=0;
	LineCount=0;
	TargetLayer=-1;
	LineLen=0;
	SearchDotX=0;
	SearchDotY=0;
	SparseAngle=0;
}
AlignmentShiftRotationThreshold::~AlignmentShiftRotationThreshold(void)
{
	Threshold=0;
	LineCount=0;
	TargetLayer=-1;
	LineLen=0;
	SearchDotX=0;
	SearchDotY=0;
	SparseAngle=0;
}

void	AlignmentShiftRotationThreshold::RegistHist(void)
{
}

void	AlignmentShiftRotationThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const AlignmentShiftRotationThreshold *p = dynamic_cast<const AlignmentShiftRotationThreshold *>(&src);
	if(p==NULL)	return;
	
	Threshold	=p->Threshold;
	LineCount	=p->LineCount;
	TargetLayer	=p->TargetLayer;
	LineLen		=p->LineLen;
	SearchDotX	=p->SearchDotX;
	SearchDotY	=p->SearchDotY;
	SparseAngle	=p->SparseAngle;
	Rotation	=p->Rotation;
}
void	AlignmentShiftRotationThreshold::FromLibrary(AlgorithmLibrary *src)
{
	AlignmentShiftRotationLibrary *p = dynamic_cast<AlignmentShiftRotationLibrary *>(src);
	if(p==NULL)	return;
	Threshold	=p->Threshold;
	LineCount	=p->LineCount;
	TargetLayer	=p->TargetLayer;
	LineLen		=p->LineLen;
	SearchDotX	=p->SearchDotX;
	SearchDotY	=p->SearchDotY;
	SparseAngle	=p->SparseAngle;
	Rotation	=p->Rotation;
}
void	AlignmentShiftRotationThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	AlignmentShiftRotationLibrary *p = dynamic_cast<AlignmentShiftRotationLibrary *>(Dest);
	if(p==NULL)	return;
	p->Threshold	=Threshold;
	p->LineCount	=LineCount;
	p->TargetLayer	=TargetLayer;
	p->LineLen		=LineLen;
	p->SearchDotX	=SearchDotX;
	p->SearchDotY	=SearchDotY;
	p->SparseAngle	=SparseAngle;
	p->Rotation		=Rotation;
}
bool	AlignmentShiftRotationThreshold::IsEqual(const AlgorithmThreshold &src)	const
{
	const AlignmentShiftRotationThreshold *p = dynamic_cast<const AlignmentShiftRotationThreshold *>(&src);
	if(p==NULL)	return false;
	if(Threshold	!=p->Threshold)	return false;
	if(LineCount	!=p->LineCount)	return false;
	if(TargetLayer	!=p->TargetLayer)	return false;
	if(LineLen		!=p->LineLen)	return false;
	if(SearchDotX	!=p->SearchDotX)	return false;
	if(SearchDotY	!=p->SearchDotY)	return false;
	if(SparseAngle	!=p->SparseAngle)	return false;
	if(Rotation		!=p->Rotation)	return false;
	return true;
}
bool	AlignmentShiftRotationThreshold::Save(QIODevice *f)
{
	if(::Save(f,Threshold)==false)
		return false;
	if(::Save(f,LineCount)==false)
		return false;
	if(::Save(f,TargetLayer)==false)
		return false;
	if(::Save(f,LineLen)==false)
		return false;
	if(::Save(f,SearchDotX)==false)
		return false;
	if(::Save(f,SearchDotY)==false)
		return false;
	if(::Save(f,SparseAngle)==false)
		return false;
	if(Rotation.Save(f)==false)
		return false;
	return true;
}
bool	AlignmentShiftRotationThreshold::Load(QIODevice *f)
{
	if(::Load(f,Threshold)==false)
		return false;
	if(::Load(f,LineCount)==false)
		return false;
	if(::Load(f,TargetLayer)==false)
		return false;
	if(::Load(f,LineLen)==false)
		return false;
	if(::Load(f,SearchDotX)==false)
		return false;
	if(::Load(f,SearchDotY)==false)
		return false;
	if(::Load(f,SparseAngle)==false)
		return false;
	if(Rotation.Load(f)==false)
		return false;
	return true;
}
int		AlignmentShiftRotationThreshold::GetSize(void)	const
{	
	return sizeof(this);
}

void	AlignmentShiftRotationThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("Threshold",Threshold);
	RetContainer.Add("LineCount",LineCount);
	RetContainer.Add("TargetLayer",TargetLayer);
	RetContainer.Add("LineLen",LineLen);
	RetContainer.Add("SearchDotX",SearchDotX);
	RetContainer.Add("SearchDotY",SearchDotY);
	RetContainer.Add("SparseAngle",SparseAngle);
}


//===========================================================================

AlignmentShiftRotationItem::AlignmentVLine::AlignmentVLine(void)
{
	AddedS=0;
	AddedSS=0;
	VLineX=0;
	VLineY1=0;
	VLineY2=0;
	VDot=NULL;
}
AlignmentShiftRotationItem::AlignmentVLine::AlignmentVLine(const AlignmentVLine &srv)
{
	AddedS=srv.AddedS;
	AddedSS=srv.AddedSS;
	VLineX=srv.VLineX;
	VLineY1=srv.VLineY1;
	VLineY2=srv.VLineY2;
	VDot=NULL;
	if(srv.VDot!=NULL){
		int Len=VLineY2-VLineY1+1;
		VDot=new BYTE[Len];
		memcpy(VDot,srv.VDot,Len);
	}
}

AlignmentShiftRotationItem::AlignmentVLine::~AlignmentVLine(void)
{
	if(VDot!=NULL){
		delete [] VDot;
		VDot=NULL;
	}
	AddedS=0;
	AddedSS=0;
	VLineX=0;
	VLineY1=0;
	VLineY2=0;
}

AlignmentShiftRotationItem::AlignmentVLine	&AlignmentShiftRotationItem::AlignmentVLine::operator=(const AlignmentShiftRotationItem::AlignmentVLine &src)
{
	if(this==&src)	return *this;
	AddedS=src.AddedS;
	AddedSS=src.AddedSS;
	VLineX=src.VLineX;
	VLineY1=src.VLineY1;
	VLineY2=src.VLineY2;
	if(VDot!=NULL){
		delete [] VDot;
		VDot=NULL;
	}
	if(src.VDot!=NULL){
		int Len=VLineY2-VLineY1+1;
		VDot=new BYTE[Len];
		memcpy(VDot,src.VDot,Len);
	}
	return *this;
}

bool	AlignmentShiftRotationItem::AlignmentVLine::Allocate(ImageBuffer &Images)
{
	if(VDot!=NULL){
		delete [] VDot;
		VDot=NULL;
	}
	int Len=VLineY2-VLineY1+1;
	VDot=new BYTE[Len];
	for(int y=VLineY1;y<=VLineY2;y++)
	{
		int	Index = y-VLineY1;
		VDot[Index]=0;
		BYTE c = Images.GetPixel(VLineX,y);
		VDot[Index]=c;
	}

	AddedS=0;
	AddedSS=0;
	for(int i=0;i<Len;i++){
		BYTE	c=VDot[i];
		AddedS+=c;
		AddedSS+=c*c;
	}

	return true;
}

double	AlignmentShiftRotationItem::AlignmentVLine::Match(int dx ,int dy ,ImageBuffer &Image)
{
	int Len=VLineY2-VLineY1+1;
	BYTE	*s=VDot;
	int		AddedD=0;
	int		AddedDD=0;
	int		AddedSD=0;
	for(int i=0;i<Len;i++){
		BYTE	*d=Image.GetY(VLineY1+dy+i);
		BYTE	c=d[VLineX+dx];
		AddedD+=c;
		AddedDD+=c*c;
		AddedSD+=c*s[i];
	}

	double	AvrS=((double)AddedS)/Len;
	double	AvrD=((double)AddedD)/Len;

	double	MS=AddedSS-AvrS*AvrS*Len;
	double	MD=AddedDD-AvrD*AvrD*Len;
	double	M=MS*MD;
	if(M<=0)
		return 0;
	return (AddedSD-AvrS*AvrD*Len)/sqrt(M);

	return 0;
}

void	AlignmentShiftRotationItem::AlignmentVLine::Move(int Dx ,int Dy)
{
	VLineX+=Dx;
	VLineY1+=Dy;
	VLineY2+=Dy;
}

void	AlignmentShiftRotationItem::AlignmentVLine::Draw(QPainter &p, int movx ,int movy ,double ZoomRate)
{
	int	x1 = (int)((double)(VLineX +movx)*ZoomRate);
	int	y1 = (int)((double)(VLineY1+movy)*ZoomRate);
	int	y2 = (int)((double)(VLineY2+movy)*ZoomRate);

	p.setPen(QPen(Qt::green,1));
	p.drawLine(x1,y1,x1,y2);
}
bool	AlignmentShiftRotationItem::AlignmentVLine::Save(QIODevice *f)
{
	if(::Save(f,AddedS)==false)		return false;
	if(::Save(f,AddedSS)==false)	return false;
	if(::Save(f,VLineX)==false)		return false;
	if(::Save(f,VLineY1)==false)	return false;
	if(::Save(f,VLineY2)==false)	return false;
	int Len=VLineY2-VLineY1+1;
	if(f->write((const char *)VDot,Len)!=Len)	return false;
	return true;
}

bool	AlignmentShiftRotationItem::AlignmentVLine::Load(QIODevice *f)
{
	if(::Load(f,AddedS)==false)		return false;
	if(::Load(f,AddedSS)==false)	return false;
	if(::Load(f,VLineX)==false)		return false;
	if(::Load(f,VLineY1)==false)	return false;
	if(::Load(f,VLineY2)==false)	return false;
	int Len=VLineY2-VLineY1+1;
	if(VDot!=NULL){
		delete	[]VDot;
	}
	VDot=new BYTE[Len];
	if(f->read((char *)VDot,Len)!=Len)	return false;
	return true;
}

//===========================================================================
AlignmentShiftRotationItem::AlignmentHLine::AlignmentHLine(void)
{
	AddedS=0;
	AddedSS=0;
	HLineX1=0;
	HLineX2=0;
	HLineY=0;
	HDot=NULL;
}
AlignmentShiftRotationItem::AlignmentHLine::AlignmentHLine(const AlignmentHLine &srv)
{
	AddedS=srv.AddedS;
	AddedSS=srv.AddedSS;
	HLineX1=srv.HLineX1;
	HLineX2=srv.HLineX2;
	HLineY=srv.HLineY;
	HDot=NULL;
	if(srv.HDot!=NULL){
		int Len=HLineX2-HLineX1+1;
		HDot=new BYTE[Len];
		memcpy(HDot,srv.HDot,Len);
	}
}

AlignmentShiftRotationItem::AlignmentHLine::~AlignmentHLine(void)
{
	if(HDot!=NULL){
		delete [] HDot;
		HDot=NULL;
	}
	AddedS=0;
	AddedSS=0;
	HLineX1=0;
	HLineX2=0;
	HLineY=0;
}

AlignmentShiftRotationItem::AlignmentHLine	&AlignmentShiftRotationItem::AlignmentHLine::operator=(const AlignmentShiftRotationItem::AlignmentHLine &src)
{
	if(this==&src)	return *this;
	AddedS=src.AddedS;
	AddedSS=src.AddedSS;
	HLineX1=src.HLineX1;
	HLineX2=src.HLineX2;
	HLineY=src.HLineY;
	if(HDot!=NULL){
		delete [] HDot;
		HDot=NULL;
	}
	if(src.HDot!=NULL){
		int Len=HLineX2-HLineX1+1;
		HDot=new BYTE[Len];
		memcpy(HDot,src.HDot,Len);
	}
	return *this;
}
bool	AlignmentShiftRotationItem::AlignmentHLine::Allocate(ImageBuffer &Image)
{
	if(HDot!=NULL){
		delete [] HDot;
		HDot=NULL;
	}
	int Len=HLineX2-HLineX1+1;
	HDot=new BYTE[Len];
	for(int x=HLineX1;x<=HLineX2;x++)
	{
		int	Index = x-HLineX1;
		HDot[Index]=0;
		BYTE c = Image.GetPixel(x,HLineY);
		HDot[Index]=c;
	}

	AddedS=0;
	AddedSS=0;
	for(int i=0;i<Len;i++){
		BYTE	c=HDot[i];
		AddedS+=c;
		AddedSS+=c*c;
	}

	return true;
}

void	AlignmentShiftRotationItem::AlignmentHLine::Move(int Dx ,int Dy)
{
	HLineX1+=Dx;
	HLineX2+=Dx;
	HLineY+=Dy;
}

double	AlignmentShiftRotationItem::AlignmentHLine::Match(int dx ,int dy ,ImageBuffer &Image)
{
	BYTE	*d=Image.GetY(HLineY+dy);
	if(d!=NULL){
		int Len=HLineX2-HLineX1+1;
		BYTE	*s=HDot;
		int		AddedD=0;
		int		AddedDD=0;
		int		AddedSD=0;
		for(int i=0;i<Len;i++){
			int	X=HLineX1+i+dx;
			BYTE	c=d[X];
			AddedD+=c;
			AddedDD+=c*c;
			AddedSD+=c*s[i];
		}

		double	AvrS=((double)AddedS)/Len;
		double	AvrD=((double)AddedD)/Len;

		double	MS=AddedSS-AvrS*AvrS*Len;
		double	MD=AddedDD-AvrD*AvrD*Len;
		double	M=MS*MD;
		if(M<=0)
			return 0;
		return (AddedSD-AvrS*AvrD*Len)/sqrt(M);
	}
	return 0;
}

void	AlignmentShiftRotationItem::AlignmentHLine::Draw(QPainter &p, int movx ,int movy ,double ZoomRate)
{
	int	x1 = (int)((double)(HLineX1+movx)*ZoomRate);
	int	x2 = (int)((double)(HLineX2+movx)*ZoomRate);
	int	y1 = (int)((double)(HLineY +movy)*ZoomRate);

	p.setPen(QPen(Qt::green,1));
	p.drawLine(x1,y1,x2,y1);
}
bool	AlignmentShiftRotationItem::AlignmentHLine::Save(QIODevice *f)
{
	if(::Save(f,AddedS)==false)		return false;
	if(::Save(f,AddedSS)==false)	return false;
	if(::Save(f,HLineX1)==false)	return false;
	if(::Save(f,HLineX2)==false)	return false;
	if(::Save(f,HLineY)==false)		return false;
	int Len=HLineX2-HLineX1+1;
	if(f->write((const char *)HDot,Len)!=Len)	return false;
	return true;
}

bool	AlignmentShiftRotationItem::AlignmentHLine::Load(QIODevice *f)
{
	if(::Load(f,AddedS)==false)		return false;
	if(::Load(f,AddedSS)==false)	return false;
	if(::Load(f,HLineX1)==false)	return false;
	if(::Load(f,HLineX2)==false)	return false;
	if(::Load(f,HLineY)==false)		return false;
	int Len=HLineX2-HLineX1+1;
	if(HDot!=NULL){
		delete	[]HDot;
	}
	HDot=new BYTE[Len];
	if(f->read((char *)HDot,Len)!=Len)	return false;
	return true;
}
//===========================================================================

AlignmentShiftRotationItem::VHLineGroup::VHLineGroup(int layer)
{
	Layer=layer;
}

AlignmentShiftRotationItem::VHLineGroup::VHLineGroup(const AlignmentShiftRotationItem::VHLineGroup &src)
{
	Layer=src.Layer;
	for(AlignmentVLine *r=src.VLines.GetFirst();r!=NULL;r=r->GetNext())
	{
		AlignmentVLine *New=new AlignmentVLine(*r);
		VLines.AppendList(New);
	}
	for(AlignmentHLine *r=src.HLines.GetFirst();r!=NULL;r=r->GetNext())
	{
		AlignmentHLine *New=new AlignmentHLine(*r);
		HLines.AppendList(New);
	}
}

double	Calc(ImageBuffer &ImageBuff,int dx ,int dy);

struct TmpVarList
{
	int	X,Y;
	double	Var;
};

#define	MaxTmpVarListCount	100000

bool	AlignmentShiftRotationItem::VHLineGroup::Allocate(const FlexArea &area ,ImageBufferListContainer &Images
				,const AlignmentShiftRotationThreshold *RThr)
{
	if(Layer<0){
		Layer=0;
		int	layer=0;
		double	LastVar = 0;
		for(ImageBufferList *SrcBuff=Images.GetFirst();SrcBuff!=NULL;SrcBuff=SrcBuff->GetNext(),layer++)
		{
			if(SrcBuff->IsNull())	continue;
			double Avr ,Var;
			area.CalcAvrVar(0,0,*SrcBuff,Avr ,Var	,0.99,0.99);
			if(LastVar<Var){
				LastVar=Var;
				Layer=layer;
			}
		}
	}
	ImageBuffer *SrcBuff = Images[Layer];
	int Len=area.GetFLineLen();
	int DimCount=0;
	struct TmpVarList *TmpDim = new struct TmpVarList[MaxTmpVarListCount];

	for(int i=0;i<Len;i++)
	{
		int	AbsY = area.GetFLineAbsY(i);
		int	LeftX = area.GetFLineLeftX(i);
		int	RightX = area.GetFLineRightX(i);

		for(int x=LeftX;x<RightX-RThr->LineLen;x++){
			TmpDim[DimCount].X = x;
			TmpDim[DimCount].Y = AbsY;
			TmpDim[DimCount].Var=CalcVarH(x,x+RThr->LineLen,AbsY,SrcBuff);
			if(DimCount<MaxTmpVarListCount){
				DimCount++;
			}
		}
	}
	QSort(TmpDim, DimCount, sizeof(struct TmpVarList), [](const void *a, const void *b)->int{
		const struct TmpVarList *A = (const struct TmpVarList *)a;
		const struct TmpVarList *B = (const struct TmpVarList *)b;
		if(A->Var<B->Var)	return 1;
		if(A->Var>B->Var)	return -1;
		return 0;
		});
	HLines.RemoveAll();
	for(int i=0;i<DimCount;i++)
	{
		bool	Flag = true;
		for(AlignmentHLine *r=HLines.GetFirst();r!=NULL;r=r->GetNext())
		{
			double	Len = hypot((double)(r->HLineX1-TmpDim[i].X),(double)(r->HLineY-TmpDim[i].Y));
			if(Len<5){
				Flag=false;
				break;
			}
		}
		if(Flag==false)	continue;
		if(TmpDim[i].Var<RThr->Threshold)
			break;
		AlignmentHLine *New=new AlignmentHLine();
		New->HLineX1=TmpDim[i].X;
		New->HLineX2=TmpDim[i].X+RThr->LineLen-1;
		New->HLineY =TmpDim[i].Y;
		New->Allocate(*SrcBuff);
		HLines.AppendList(New);
		if(HLines.GetCount()>=RThr->LineCount){
			break;
		}
	}

	DimCount=0;
	int	AMaxY=area.GetMaxY();
	for(int i=0;i<Len;i++)
	{
		int	AbsY = area.GetFLineAbsY(i);
		int	LeftX = area.GetFLineLeftX(i);
		int	RightX = area.GetFLineRightX(i);

		if(0<=AbsY && AbsY+RThr->LineLen<AMaxY){
			for(int x=LeftX;x<RightX;x++){
				TmpDim[DimCount].X = x;
				TmpDim[DimCount].Y = AbsY;
				TmpDim[DimCount].Var=CalcVarV(x,AbsY,AbsY+RThr->LineLen,SrcBuff);
				if(DimCount<MaxTmpVarListCount){
					DimCount++;
				}
			}
		}
	}
	QSort(TmpDim, DimCount, sizeof(struct TmpVarList), [](const void *a, const void *b)->int{
		const struct TmpVarList *A = (const struct TmpVarList *)a;
		const struct TmpVarList *B = (const struct TmpVarList *)b;
		if(A->Var<B->Var)	return 1;
		if(A->Var>B->Var)	return -1;
		return 0;
		});
	VLines.RemoveAll();
	for(int i=0;i<DimCount;i++)
	{
		bool	Flag = true;
		for(AlignmentVLine *r=VLines.GetFirst();r!=NULL;r=r->GetNext())
		{
			double	Len = hypot((double)(r->VLineX-TmpDim[i].X),(double)(r->VLineY1-TmpDim[i].Y));
			if(Len<5){
				Flag=false;
				break;
			}
		}
		if(Flag==false)	continue;
		if(TmpDim[i].Var<RThr->Threshold)
			break;
		AlignmentVLine *New=new AlignmentVLine();
		New->VLineX = TmpDim[i].X;
		New->VLineY1 = TmpDim[i].Y;
		New->VLineY2 = TmpDim[i].Y+RThr->LineLen-1;
		New->Allocate(*SrcBuff);
		VLines.AppendList(New);
		if(VLines.GetCount()>=RThr->LineCount){
			break;
		}

	}
	delete[] TmpDim;

	return true;
}

double	AlignmentShiftRotationItem::VHLineGroup::CalcVarH(int x1,int x2,int y,ImageBuffer *SrcBuff)
{
	int	Len=x2-x1+1;
	if(Len<=0)	return 0;
	double	Avr=0;
	for(int x=x1;x<=x2;x++){
		BYTE c = SrcBuff->GetPixel(x,y);
		Avr+=c;
	}
	Avr/=Len;
	double	Var=0;
	for(int x=x1;x<=x2;x++){
		BYTE c = SrcBuff->GetPixel(x,y);
		double d = (double)c-Avr;
		Var+=d*d;
	}
	Var/=Len;
	return Var;
}
double	AlignmentShiftRotationItem::VHLineGroup::CalcVarV(int x,int y1,int y2,ImageBuffer *SrcBuff)
{
	int	Len=y2-y1+1;
	if(Len<=0)	return 0;
	double	Avr=0;
	for(int y=y1;y<=y2;y++){
		BYTE c = SrcBuff->GetPixel(x,y);
		Avr+=c;
	}
	Avr/=Len;
	double	Var=0;
	for(int y=y1;y<=y2;y++){
		BYTE c = SrcBuff->GetPixel(x,y);
		double d = (double)c-Avr;
		Var+=d*d;
	}
	Var/=Len;
	return Var;
}


AlignmentShiftRotationItem::VHLineGroup &AlignmentShiftRotationItem::VHLineGroup::operator=(const AlignmentShiftRotationItem::VHLineGroup &src)
{
	Layer=src.Layer;
	for(AlignmentVLine *r=src.VLines.GetFirst();r!=NULL;r=r->GetNext())
	{
		AlignmentVLine *New=new AlignmentVLine(*r);
		VLines.AppendList(New);
	}
	for(AlignmentHLine *r=src.HLines.GetFirst();r!=NULL;r=r->GetNext())
	{
		AlignmentHLine *New=new AlignmentHLine(*r);
		HLines.AppendList(New);
	}
	return *this;
}

void	AlignmentShiftRotationItem::VHLineGroup::Move(int Dx ,int Dy)
{
	for(AlignmentVLine *r=VLines.GetFirst();r!=NULL;r=r->GetNext())
	{
		r->Move(Dx,Dy);
	}
	for(AlignmentHLine *r=HLines.GetFirst();r!=NULL;r=r->GetNext())
	{
		r->Move(Dx,Dy);
	}
}
void	AlignmentShiftRotationItem::VHLineGroup::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate)
{
	QPainter	p(&pnt);

	for(AlignmentVLine *r=VLines.GetFirst();r!=NULL;r=r->GetNext())
	{
		r->Draw(p,movx,movy,ZoomRate);
	}
	for(AlignmentHLine *r=HLines.GetFirst();r!=NULL;r=r->GetNext())
	{
		r->Draw(p,movx,movy,ZoomRate);
	}
}

double	AlignmentShiftRotationItem::VHLineGroup::Match(int dx ,int dy ,ImagePointerContainer &Images)
{
	if(VLines.GetCount()==0)
		return 0;
	if(HLines.GetCount()==0)
		return 0;
	double	MaxV=0;
	for(AlignmentVLine *L=VLines.GetFirst();L!=NULL;L=L->GetNext()){
		double	d=L->Match(dx ,dy ,*Images[Layer]); 
		MaxV+=d*d*d;
	}
	MaxV/=VLines.GetCount();

	double	MaxH=0;
	for(AlignmentHLine *L=HLines.GetFirst();L!=NULL;L=L->GetNext()){
		double	d=L->Match(dx ,dy ,*Images[Layer]); 
		MaxH+=d*d*d;
	}
	MaxH/=HLines.GetCount();

	return MaxV*MaxH;
}

bool	AlignmentShiftRotationItem::VHLineGroup::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)	return false;
	int32	LenVLines=VLines.GetCount();
	if(::Save(f,LenVLines)==false)	return false;
	for(AlignmentVLine *L=VLines.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false){
			return false;
		}
	}
	int32	LenHLines=HLines.GetCount();
	if(::Save(f,LenHLines)==false)	return false;
	for(AlignmentHLine *L=HLines.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	AlignmentShiftRotationItem::VHLineGroup::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)	return false;

	int32	LenVLines;
	if(::Load(f,LenVLines)==false)	return false;
	VLines.RemoveAll();
	for(int i=0;i<LenVLines;i++){
		AlignmentVLine *L=new AlignmentVLine();
		if(L->Load(f)==false){
			return false;
		}
		VLines.AppendList(L);
	}

	int32	LenHLines;
	if(::Load(f,LenHLines)==false)	return false;
	HLines.RemoveAll();
	for(int i=0;i<LenHLines;i++){
		AlignmentHLine *L=new AlignmentHLine();
		if(L->Load(f)==false){
			return false;
		}
		HLines.AppendList(L);
	}
	return true;
}
//===========================================================================
AlignmentShiftRotationItem::VHLines::VHLines(double angleradian)
{
	AngleRadian=angleradian;
	MasterCx=MasterCy=0;
}

AlignmentShiftRotationItem::VHLines::VHLines(const AlignmentShiftRotationItem::VHLines &src)
{
	AngleRadian=src.AngleRadian;
	for(VHLineGroup *r=src.LineGroup.GetFirst();r!=NULL;r=r->GetNext())
	{
		VHLineGroup *New=new VHLineGroup(*r);
		LineGroup.AppendList(New);
	}
	Image=src.Image;
	MasterCx=src.MasterCx;
	MasterCy=src.MasterCy;
}

AlignmentShiftRotationItem::VHLines	&AlignmentShiftRotationItem::VHLines::operator=(const AlignmentShiftRotationItem::VHLines &src)
{
	AngleRadian=src.AngleRadian;
	for(VHLineGroup *r=src.LineGroup.GetFirst();r!=NULL;r=r->GetNext())
	{
		VHLineGroup *New=new VHLineGroup(*r);
		LineGroup.AppendList(New);
	}
	Image=src.Image;
	MasterCx=src.MasterCx;
	MasterCy=src.MasterCy;

	return *this;
}

bool	AlignmentShiftRotationItem::VHLines::Allocate(const FlexArea &area ,ImagePointerContainer &Images
														,const AlignmentShiftRotationThreshold *RThr)
{
	FlexArea	Area=area;
	Area.GetCenter(MasterCx,MasterCy);
	Area.Rotate(AngleRadian*180.0/M_PI ,MasterCx, MasterCy);

	int	W = Area.GetWidth();
	int	H = Area.GetHeight();
	ImageBufferListContainer	ImagesBuff;
	ImagesBuff.Reallocate(Images.GetCount());
	ImagesBuff.Set(0,W,H);
	double	CosS = cos(AngleRadian);
	double	SinS = sin(AngleRadian);
	int	AreaMinX = Area.GetMinX();
	int	AreaMinY = Area.GetMinY();
	for(int layer=0;layer<Images.GetCount();layer++)
	{
		ImageBuffer	*SrcBuff=Images[layer];
		if(SrcBuff==NULL)	continue;
		ImageBuffer	*DstBuff=ImagesBuff[layer];
		if(DstBuff==NULL)	continue;

		for(int y=0;y<H;y++)
		{
			for(int x=0;x<W;x++)
			{
				int	DstX=x+AreaMinX;
				int	DstY=y+AreaMinY;

				double	SrcX =  CosS*(DstX-MasterCx) - SinS*(DstY-MasterCy) + MasterCx;
				double	SrcY =  SinS*(DstX-MasterCx) + CosS*(DstY-MasterCy) + MasterCy;

				int	iSrcX=floor(SrcX);
				int	iSrcY=floor(SrcY);
				if(0<=iSrcX && (iSrcX+1)<SrcBuff->GetWidth() && 0<=iSrcY && (iSrcY+1)<SrcBuff->GetHeight()){
					double	sX=SrcX-iSrcX;
					double	sY=SrcY-iSrcY;

					BYTE	p00=SrcBuff->GetPixel(iSrcX,iSrcY);
					BYTE	p10=SrcBuff->GetPixel(iSrcX+1,iSrcY);
					BYTE	p01=SrcBuff->GetPixel(iSrcX,iSrcY+1);
					BYTE	p11=SrcBuff->GetPixel(iSrcX+1,iSrcY+1);

					int	P=p00*(1.0-sX)*(1.0-sY)
						 +p10*sX*(1.0-sY)
						 +p01*(1.0-sX)*sY
						 +p11*sX*sY;

					DstBuff->SetPixel(DstX-AreaMinX,DstY-AreaMinY
									 ,Clipping(P,0,255));
				}
			}
		}
	}

	int	WNumb=3;
	if(W<50){
		WNumb=1;
	}
	else if(W<100){
		WNumb=2;
	}
	int	HNumb=3;
	if(H<50){
		HNumb=1;
	}
	else if(H<100){
		HNumb=2;
	}
	int	WLen = W/WNumb;
	int	HLen = H/HNumb;

	for(int h=0;h<HNumb;h++)
	{
		for(int w=0;w<WNumb;w++)
		{
			VHLineGroup	*New=new VHLineGroup(RThr->TargetLayer);
			FlexArea	SubArea=area;
			SubArea.ClipArea(SubArea.GetMinX()+w*WLen		,SubArea.GetMinY()+h*HLen
							,SubArea.GetMinX()+(w+1)*WLen-1	,SubArea.GetMinY()+(h+1)*HLen-1);
			SubArea.Rotate(AngleRadian*180.0/M_PI ,MasterCx, MasterCy);

			SubArea.MoveToNoClip(-AreaMinX,-AreaMinY);
			New->Allocate(SubArea ,ImagesBuff,RThr);
			New->Move(AreaMinX,AreaMinY);
			LineGroup.AppendList(New);
		}
	}
	Area.MoveToNoClip(-AreaMinX,-AreaMinY);
	Image.Set(Area,ImagesBuff);
	Area.MoveToNoClip(AreaMinX,AreaMinY);
	Image.MoveToNoClip(AreaMinX,AreaMinY);

	return true;
}
void	AlignmentShiftRotationItem::VHLines::Release(void)
{
	LineGroup.RemoveAll();
	Image.Clear();
}
void	AlignmentShiftRotationItem::VHLines::Move(int Dx ,int Dy)
{
	MasterCx+=Dx;
	MasterCy+=Dy;
	for(VHLineGroup *r=LineGroup.GetFirst();r!=NULL;r=r->GetNext())
	{
		r->Move(Dx,Dy);
	}
	Image.MoveToNoClip(Dx,Dy);
}

double	AlignmentShiftRotationItem::VHLines::Match(int mx ,int my ,int &rx ,int &ry
						,ImagePointerContainer &Images 
						,const AlignmentShiftRotationThreshold *RThr)
{
	double	MaxD=0;
	for(int dy=-RThr->SearchDotY;dy<=RThr->SearchDotY;dy++){
		for(int dx=-RThr->SearchDotX;dx<=RThr->SearchDotX;dx++){
			double	MaxHV=0;
			for(VHLineGroup *L=LineGroup.GetFirst();L!=NULL;L=L->GetNext()){
				double	d=L->Match(mx+dx ,my+dy ,Images);
				MaxHV+=d;
			}
			if(LineGroup.GetCount()>0){
				MaxHV/=LineGroup.GetCount();
				if(MaxD<MaxHV){
					MaxD=MaxHV;
					rx=dx;
					ry=dy;
				}
			}
		}
	}
	return MaxD;
}


void	AlignmentShiftRotationItem::VHLines::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate)
{
	for(VHLineGroup *r=LineGroup.GetFirst();r!=NULL;r=r->GetNext())
	{
		r->Draw(pnt ,movx ,movy ,ZoomRate);
	}
}

void	AlignmentShiftRotationItem::VHLines::DrawImage(QImage &pnt, int movx ,int movy ,double ZoomRate)
{
	Image.DrawImage(0 ,0 ,&pnt
						,ZoomRate , movx , movy
						,true ,true ,true);
}
bool	AlignmentShiftRotationItem::VHLines::Save(QIODevice *f)
{
	int32	LineGroupCount=LineGroup.GetCount();
	if(::Save(f,LineGroupCount)==false)	return false;
	for(VHLineGroup *L=LineGroup.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false){
			return false;
		}
	}
	if(::Save(f,AngleRadian)==false)	return false;
	if(Image.Save(f)==false)			return false;
	if(::Save(f,MasterCx)==false)	return false;
	if(::Save(f,MasterCy)==false)	return false;
	return true;
}
bool	AlignmentShiftRotationItem::VHLines::Load(QIODevice *f)
{
	int32	LineGroupCount;
	if(::Load(f,LineGroupCount)==false)	return false;
	LineGroup.RemoveAll();
	for(int i=0;i<LineGroupCount;i++){
		VHLineGroup *L=new VHLineGroup();
		if(L->Load(f)==false){
			return false;
		}
		LineGroup.AppendList(L);
	}
	if(::Load(f,AngleRadian)==false)	return false;
	if(Image.Load(f)==false)			return false;
	if(::Load(f,MasterCx)==false)	return false;
	if(::Load(f,MasterCy)==false)	return false;
	return true;
}
//===========================================================================

AlignmentShiftRotationItem::AlignmentShiftRotationItem(void)
{
}
AlignmentShiftRotationItem::~AlignmentShiftRotationItem(void)
{
}

void	AlignmentShiftRotationItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemRoot::SetRefereneFrom(src,OffsetX,OffsetY);
}

void    AlignmentShiftRotationItem::MoveTo(int dx ,int dy)
{
	AlgorithmItemRoot::MoveTo(dx,dy);
	for(VHLines *r=VHLinesRotation.GetFirst();r!=NULL;r=r->GetNext())
	{
		r->Move(dx,dy);
	}
}

AlgorithmItemPI	&AlignmentShiftRotationItem::operator=(const AlgorithmItemRoot &src)
{
	const AlignmentShiftRotationItem *p = dynamic_cast<const AlignmentShiftRotationItem *>(&src);
	if(p==NULL)	return *this;
	AVector	=p->AVector;
	AlgorithmItemPI::operator=(src);
	const AlgorithmThreshold	*RThr=((AlgorithmItemRoot *)&src)->GetThresholdBaseReadable();
	GetThresholdW()->CopyFrom(*((const AlignmentShiftRotationThreshold *)RThr));

	VHLinesRotation.RemoveAll();
	for(VHLines *r=p->VHLinesRotation.GetFirst();r!=NULL;r=r->GetNext())
	{
		VHLines *New=new VHLines(*r);
		VHLinesRotation.AppendList(New);
	}

	MasterCx		=p->MasterCx		;
	MasterCy		=p->MasterCy		;
	ShiftByGlobalX	=p->ShiftByGlobalX	;
	ShiftByGlobalY	=p->ShiftByGlobalY	;
	ResultDx		=p->ResultDx		;
	ResultDy		=p->ResultDy		;
	ResultRotation	=p->ResultRotation	;

	return *this;
}

AlignmentShiftRotationItem &AlignmentShiftRotationItem::operator=(const AlignmentShiftRotationItem &src)
{
	if(this==&src)	return *this;
	AVector	=src.AVector;

	AlgorithmItemPI::operator=(src);
	const AlgorithmThreshold	*RThr=((AlgorithmItemRoot *)&src)->GetThresholdBaseReadable();
	GetThresholdW()->CopyFrom(*((const AlignmentShiftRotationThreshold *)RThr));

	VHLinesRotation.RemoveAll();
	for(VHLines *r=src.VHLinesRotation.GetFirst();r!=NULL;r=r->GetNext())
	{
		VHLines *New=new VHLines(*r);
		VHLinesRotation.AppendList(New);
	}
	MasterCx		=src.MasterCx		;
	MasterCy		=src.MasterCy		;
	ShiftByGlobalX	=src.ShiftByGlobalX	;
	ShiftByGlobalY	=src.ShiftByGlobalY	;
	ResultDx		=src.ResultDx		;
	ResultDy		=src.ResultDy		;
	ResultRotation	=src.ResultRotation	;
	return *this;
}


void	AlignmentShiftRotationItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			AlignmentShiftRotationInPage	*Pg=dynamic_cast<AlignmentShiftRotationInPage *>(GetParentInPage());
			UndoElement<AlignmentShiftRotationInPage>	*UPointer=new UndoElement<AlignmentShiftRotationInPage>(Pg,&AlignmentShiftRotationInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			AlignmentShiftRotationItem *src=(AlignmentShiftRotationItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((AlignmentShiftRotationItem *)Data)->GetLibID()){
			AlignmentShiftRotationInPage	*Pg=dynamic_cast<AlignmentShiftRotationInPage *>(GetParentInPage());
			UndoElement<AlignmentShiftRotationInPage>	*UPointer=new UndoElement<AlignmentShiftRotationInPage>(Pg,&AlignmentShiftRotationInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			AlignmentShiftRotationItem *src=(AlignmentShiftRotationItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
}

void    AlignmentShiftRotationItem::Clear(void)
{
	ResultDx=0;
	ResultDy=0;
	ResultRotation=0;
}
bool    AlignmentShiftRotationItem::Save(QIODevice *file)
{
	WORD	Ver=1;
	if(AlgorithmItemPI::Save(file)==false)
		return(false);

	if(::Save(file,Ver)==false)
		return false;

	int32	CountVHLinesRotation=VHLinesRotation.GetCount();
	if(::Save(file,CountVHLinesRotation)==false)
		return false;
	for(VHLines *L=VHLinesRotation.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(file)==false){
			return false;
		}
	}

	return(true);
}
bool    AlignmentShiftRotationItem::Load(QIODevice *file,LayersBase *LBase)
{
	WORD	Ver=0;
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return(false);
	if(::Load(file,Ver)==false)
		return false;

	int32	CountVHLinesRotation;
	VHLinesRotation.RemoveAll();
	if(::Load(file,CountVHLinesRotation)==false)
		return false;
	for(int i=0;i<CountVHLinesRotation;i++){
		VHLines *L=new VHLines();
		if(L->Load(file)==false){
			return false;
		}
		VHLinesRotation.AppendList(L);
	}

	return(true);
}

//bool    AlignmentShiftRotationItem::MakeArea(bool ReCalcBitMask=true,ImageBuffer *specialData=NULL);

void	AlignmentShiftRotationItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentShiftRotationDrawAttr	*a=dynamic_cast<AlignmentShiftRotationDrawAttr *>(Attr);
	if(a->DrawModeArea==true){
		AlgorithmItemRoot::Draw(pnt,movx,movy,ZoomRate,Attr);
	}
	else if(a->DrawModeHVLines==true){
		VHLines *r=VHLinesRotation[a->HVLinesAngleIndex];
		if(a->HVLinesPage==GetPage()
		&& a->HVLinesPhase==GetPhaseCode()
		&& a->HVLinesItemID==GetID()
		&& r!=NULL){
			r->Draw(pnt ,movx ,movy ,ZoomRate);
		}
	}
}
void	AlignmentShiftRotationItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG)
{
	QColor	ce=Qt::red;
	ce.setAlpha(180);

	GetArea().Draw(ShiftByGlobalX+ResultDx,ShiftByGlobalY+ResultDy,&IData ,ce.rgba()
							,ZoomRate ,MovX ,MovY);

	if(ZoomRate>=1.0){
		PData.drawText((MasterCx+MovX)*ZoomRate,(MasterCy+MovY)*ZoomRate
			,QString(/**/"Result:")+QString::number(ResultMatch,'f',4));
		PData.drawText((MasterCx+MovX)*ZoomRate,(MasterCy+MovY)*ZoomRate+16
			,QString(/**/"MasterX=") +QString::number((int)MasterCx)
			+QString(/**/",MasterY=")+QString::number((int)MasterCy));
		PData.drawText((MasterCx+MovX)*ZoomRate,(MasterCy+MovY)*ZoomRate+32
			,QString(/**/ "dx=")+QString::number((int)(ShiftByGlobalX+ResultDx))	//-MasterX))
			+QString(/**/",dy=")+QString::number((int)(ShiftByGlobalY+ResultDy))
			+QString(/**/",Rot=")+QString::number(ResultRotation*180.0/M_PI,'f',2));
	}

}

ExeResult	AlignmentShiftRotationItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	GetArea().GetCenter(MasterCx,MasterCy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(MasterCx,MasterCy);
	if(AVector!=NULL)
		AVector->Set(this);

	const AlignmentShiftRotationThreshold *RThr = GetThresholdR();
	int W = GetArea().GetWidth();
	int H = GetArea().GetHeight();
	double RadiusR=hypot(W/2.0,H/2.0);
	double StepS=1.0/RadiusR;
	if(RThr->SparseAngle>0){
		StepS*=RThr->SparseAngle;
	}
	ImagePointerContainer MasterImages;
	GetMasterBuffList(MasterImages);
	double StepDegree=180*StepS/M_PI;
	VHLinesRotation.RemoveAll();
	for(RotationRange *r=RThr->Rotation.GetFirst();r!=NULL;r=r->GetNext()){
		for(double s=r->MinAngleDegree;s<=r->MaxAngleDegree;s+=StepDegree){
			VHLines	*L=new VHLines(s*M_PI/180.0);
			L->Allocate(GetArea() ,MasterImages  ,RThr);
			VHLinesRotation.AppendList(L);
		}
	}

	return Ret;
}

ExeResult	AlignmentShiftRotationItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteStartByInspection	(ExeID ,ThreadNo,Res);
	return Ret;
}

ExeResult	AlignmentShiftRotationItem::ExecuteAlignment		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteAlignment	(ExeID ,ThreadNo,Res);
	ShiftByGlobalX=0;
	ShiftByGlobalY=0;
	if(AVector!=NULL){
		ShiftByGlobalX=AVector->ShiftX;
		ShiftByGlobalY=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		V.PosXOnTarget=MasterCx;
		V.PosYOnTarget=MasterCy;
		V.ShiftX=0;
		V.ShiftY=0;
		Parent->GetAlignmentForProcessing(V);
		ShiftByGlobalX=V.ShiftX;
		ShiftByGlobalY=V.ShiftY;
	}
	const AlignmentShiftRotationThreshold *RThr = GetThresholdR();

	ImagePointerContainer TargetImageList;
	GetTargetBuffList(TargetImageList);
	ResultMatch=0;
	ResultRotation=0;
	ResultDx	=0;
	ResultDy	=0;
	for(VHLines *L=VHLinesRotation.GetFirst();L!=NULL;L=L->GetNext()){
		int		rx ,ry;
		double	d=L->Match(ShiftByGlobalX ,ShiftByGlobalY ,rx ,ry ,TargetImageList  ,RThr);
		if(ResultMatch<d){
			ResultRotation	=L->AngleRadian;
			ResultMatch=d;
			ResultDx=rx;
			ResultDy=ry;
		}
	}

	return Ret;
}

void	AlignmentShiftRotationItem::CopyThresholdOnly(AlignmentShiftRotationItem *src)
{
	GetThresholdW()->CopyFrom(*((AlignmentShiftRotationThreshold *)src->GetThresholdR()));
	SetInvertLogic(src->GetInvertLogic());
}


//double	AlignmentShiftRotationItem::GetThreshLevel(ImagePointerContainer &Images ,int dx=0 ,int dy=0);
//double	AlignmentShiftRotationItem::MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget
//					,int dx,int dy,int N
//					,int DotPerLine,int MaxLines);
//bool	AlignmentShiftRotationItem::IsImageChanged(void);