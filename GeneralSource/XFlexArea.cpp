/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFlexArea.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//	概要
//
//	作成者
//
/*----------------------------------------------------------------------------*/
#include "XTypeDef.h"
#include "XFlexArea.h"
#include "XCrossObj.h"
#include "swap.h"
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include "XPointer.h"
#include "XBsearch.h"
#include "XMainSchemeMemory.h"
#include <omp.h>
#include "XGeneralFunc.h"
#include "XImageProcess.h"
#include "XTransform.h"

//================================================================================

static	int   YSortFunc(const void *a ,const void *b)
{
	struct	FlexLine	*ma=(struct FlexLine *)a;
	struct	FlexLine	*mb=(struct FlexLine *)b;

	if(ma->_GetAbsY()>mb->_GetAbsY()){
		return(1);
	}
	if(ma->_GetAbsY()<mb->_GetAbsY()){
		return(-1);
	}

	if(ma->_GetLeftX()>mb->_GetLeftX()){
		return(1);
	}
	if(ma->_GetLeftX()<mb->_GetLeftX()){
		return(-1);
	}

	return(0);
}

static	int   YOnlySortFunc(const void *a ,const void *b)
{
	struct	FlexLine	*ma=(struct FlexLine *)a;
	struct	FlexLine	*mb=(struct FlexLine *)b;

	if(ma->_GetAbsY()>mb->_GetAbsY()){
		return(1);
	}
	if(ma->_GetAbsY()<mb->_GetAbsY()){
		return(-1);
	}

	return(0);
}

//================================================================================
static	struct  BlockShape  StaticAShape;


FlexAreaBasePure::FlexAreaBasePure(void)
{
	Begin();
	//DotPerLine=MaxLines=99999999;
}

FlexAreaBasePure::FlexAreaBasePure(int tDotPerLine,int tMaxLines)
{
	Begin();
	//DotPerLine	=tDotPerLine;
	//MaxLines	=tMaxLines;
}

void	FlexAreaBasePure::Begin(void)
{
	MinX		=0;
	MaxX		=0;
	AddX=AddY	=0;
	FLines		=NULL;
	Len			=0;
	AShape		=NULL;
	PatternByte	=0;
}
FlexAreaBasePure::~FlexAreaBasePure(void)
{
	if(FLines!=NULL){
		delete	[]FLines;
	}
	FLines=NULL;
	Len=0;
	if(AShape!=NULL){
		delete	AShape;
		AShape=NULL;
	}
}

void	FlexAreaBasePure::SetRefereneFrom(const FlexAreaBasePure *src)
{
	PointerCopy(src);
	Regulate();
}

int     FlexAreaBasePure::GetHeight(void)const 
{
	if(Len!=0){
		return FLines[Len-1]._GetAbsY()-FLines[0]._GetAbsY()+1;
	}
	return 0;
}
int     FlexAreaBasePure::GetMinY(void)const 
{
	if(Len!=0){
		return FLines[0]._GetAbsY()+AddY;
	}
	return 0;
}
int     FlexAreaBasePure::GetMaxY(void)const 
{
	if(Len!=0){
		return FLines[Len-1]._GetAbsY()+AddY;
	}
	return 0;
}

void	FlexAreaBasePure::SetFLineOnly(struct FlexLine *FL,int len)
{
	if(FLines!=NULL){
		delete	[]FLines;
	}
	FLines=FL;
	Len=len;
	AddX=0;
	AddY=0;
}

void	FlexAreaBasePure::SetFLine(struct FlexLine *FL,int len)
{
	SetFLineOnly(FL,len);
	Regulate();
}

void	FlexAreaBasePure::SetFLine(struct FlexLine *FL,int len ,unsigned short mIndexPoint)
{
	SetFLineOnly(FL,len);
	Regulate();
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexAreaBasePure::Regulate(void)
{
	MinX=  0x7FFFFFFF;
	MaxX= -0x7FFFFFFF;
	PatternByte	=0;
	for(unsigned int i=0;i<Len;i++){
		if(MinX > FLines[i]._GetLeftX()){
			MinX= FLines[i]._GetLeftX();
		}
		if(MaxX < FLines[i]._GetRightX()){
			MaxX= FLines[i]._GetRightX();
		}
		PatternByte+=GetFLineNumb(i);
	}
	MinX+=AddX;
	MaxX+=AddX;
	SortFLine();
}

void	  FlexAreaBasePure::PointerCopy(const FlexAreaBasePure *src)
{
	if(FLines!=NULL){
		delete	[]FLines;
	}
	if(src->Len>0){
		FLines=new struct FlexLine[src->Len];
		memcpy(FLines,src->FLines,src->Len*sizeof(struct FlexLine));
	}
	else{
		FLines=new struct FlexLine[1];
	}
	Len=src->Len;

	AddX=src->AddX;
	AddY=src->AddY;
	MinX=src->MinX;
	MaxX=src->MaxX;
	if(src->AShape!=NULL){
		if(AShape==NULL){
			AShape=new struct  BlockShape;
		}
		*AShape		=*src->AShape;
	}
	else{
		if(AShape!=NULL){
			delete	AShape;
			AShape=NULL;
		}
	}
	PatternByte=src->PatternByte;
	//DotPerLine	=src->DotPerLine;
	//MaxLines	=src->MaxLines;
}

int	FlexAreaBasePure::DirectCopyTo(struct FlexLine dest[] ,int destnumb ,int startIndex)
{
	int	i;
	for(i=0;i<destnumb && (i+startIndex)<GetFLineLen();i++){
		dest[i]._SetAbsY (FLines[startIndex+i]._GetAbsY ()+AddY);
		dest[i]._SetLeftX(FLines[startIndex+i]._GetLeftX()+AddX);
		dest[i]. SetNumb (FLines[startIndex+i]. GetNumb ());
		}
	if(i>=destnumb){
		return(-1);
	}
	return(i);
}
   
void    FlexAreaBasePure::SetShape(struct BlockShape &bshape)
{   
	if(bshape.Kind==BlockShape::_sNone || bshape.Kind==BlockShape::_sFree){
		if(AShape!=NULL){
			delete	AShape;
			AShape=NULL;
		}
	}
	else{
		if(AShape==NULL){
			AShape=new struct  BlockShape;
		}
		*AShape=bshape;
	}
}

struct  BlockShape  &FlexAreaBasePure::GetShape(void)	const 
{    
	if(AShape!=NULL)
		return(*AShape);
	else
		return(StaticAShape);
}

void	FlexAreaBasePure::SuckFrom(FlexAreaBasePure &src)
{
	//FlexAreaBaseMinMax::CopyFrom(src);
	AddX=src.AddX;
	AddY=src.AddY;
	MinX=src.MinX;
	MaxX=src.MaxX;

	if(FLines!=NULL){
		delete	[]FLines;
	}
	FLines=src.FLines;
	Len=src.Len;

	src.FLines=NULL;
	src.Len=0;

	if(src.AShape!=NULL){
		if(AShape==NULL){
			AShape=new struct  BlockShape;
		}
		*AShape		=*src.AShape;
	}
	else{
		if(AShape!=NULL){
			delete	AShape;
			AShape=NULL;
		}
	}
	PatternByte	=src.PatternByte;
	//DotPerLine	=src.DotPerLine;
	//MaxLines	=src.MaxLines;
}

int		FlexAreaBasePure::FindIndex(int AbsY ,int &IndexStart ,int &IndexEnd)
{
	struct FlexLine m;
	m._SetAbsY(this,AbsY);

	struct FlexLine *k=(struct FlexLine *)EqualSearch(&m,GetFLinePoint(),GetFLineLen(),sizeof(struct FlexLine),YOnlySortFunc);
	if(k==NULL){
		return(0);
	}
	//int L=(FLines-k)/sizeof(struct FlexLine);
	int L=k-GetFLinePoint();
	while(L>0){
		if(GetFLineAbsY(L+1)!=AbsY){
			break;
		}
		L--;
	}
	IndexStart=L;

	int M=k-GetFLinePoint();
	while(M<Len-1){
		if(GetFLineAbsY(M+1)!=AbsY){
			break;
		}
		M++;
	}
	IndexEnd=M;
	return M-L+1;
}

struct BlockShape	&BlockShape::operator=(const struct BlockShape &src)
{
	if(this!=&src){
		if(Kind==_sPoly){
			delete	[]Shape.bsPoly.XY;
		}
		Kind =src.Kind;
		Shape=src.Shape;
		if(Kind==_sPoly){
			Shape.bsPoly.XY=new XYData[Shape.bsPoly.PointCount];
			memcpy(Shape.bsPoly.XY,src.Shape.bsPoly.XY,Shape.bsPoly.PointCount*sizeof(XYData));
		}
	}
	return(*this);
}
/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  src
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	BlockShape::operator==(const struct BlockShape &src)	const
{
	int	i;
	if(Kind ==src.Kind){
		switch(Kind){
			case _sNone:
				return(true);
			case _sRectangle:
				if(Shape.bsRectangle.X1==src.Shape.bsRectangle.X1
				&& Shape.bsRectangle.Y1==src.Shape.bsRectangle.Y1
				&& Shape.bsRectangle.X2==src.Shape.bsRectangle.X2
				&& Shape.bsRectangle.Y2==src.Shape.bsRectangle.Y2){
					return(true);
				}
				break;
			case _sEllipse:
				if(Shape.bsEllipse.Cx==src.Shape.bsEllipse.Cx
				&& Shape.bsEllipse.Cy==src.Shape.bsEllipse.Cy
				&& Shape.bsEllipse.Rx==src.Shape.bsEllipse.Rx
				&& Shape.bsEllipse.Ry==src.Shape.bsEllipse.Ry){
					return(true);
				}
				break;

			case _sRotRectangle:
				if(Shape.bsRotRectangle.X1==src.Shape.bsRotRectangle.X1
				&& Shape.bsRotRectangle.Y1==src.Shape.bsRotRectangle.Y1
				&& Shape.bsRotRectangle.X2==src.Shape.bsRotRectangle.X2
				&& Shape.bsRotRectangle.Y2==src.Shape.bsRotRectangle.Y2
				&& fabs(Shape.bsRotRectangle.Angle-src.Shape.bsRotRectangle.Angle)<0.001){
					return(true);
				}
				break;
			case _sRing:
				if(Shape.bsRing.Cx ==src.Shape.bsRing.Cx
				&& Shape.bsRing.Cy ==src.Shape.bsRing.Cy
				&& Shape.bsRing.Rx1==src.Shape.bsRing.Rx1
				&& Shape.bsRing.Ry1==src.Shape.bsRing.Ry1
				&& Shape.bsRing.Rx2==src.Shape.bsRing.Rx2
				&& Shape.bsRing.Ry2==src.Shape.bsRing.Ry2){
					return(true);
				}
				break;
			case _sFree:
				return(true);
			case _sPoly:
				if(Shape.bsPoly.PointCount==src.Shape.bsPoly.PointCount){
					for(i=0;i<Shape.bsPoly.PointCount;i++){
						if(Shape.bsPoly.XY[i].x!=src.Shape.bsPoly.XY[i].x
						&& Shape.bsPoly.XY[i].y!=src.Shape.bsPoly.XY[i].y){
							return false;
						}
					}
					return true;
				}
				break;
			}
		}
	return(false);
}
/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  src
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	BlockShape::operator!=(const struct BlockShape &src)	const
{
	return(!operator==(src));
}

void	BlockShape::Rotate(int AngleDegree ,int Cx, int Cy)
{
	switch(Kind){
		case _sNone:
			break;
		case _sRectangle:
			break;
		case _sEllipse:
			break;
		case _sRotEllipse:
			break;
		case _sRotRectangle:
			break;
		case _sRing:
			break;
		case _sFree:
			break;
		case _sPoly:
			break;
	}
}
void	BlockShape::MirrorX(int PointY)
{
	switch(Kind){
		case _sNone:
			break;
		case _sRectangle:
			break;
		case _sEllipse:
			break;
		case _sRotEllipse:
			break;
		case _sRotRectangle:
			break;
		case _sRing:
			break;
		case _sFree:
			break;
		case _sPoly:
			break;
	}
}
void	BlockShape::MirrorY(int PointX)
{
	switch(Kind){
		case _sNone:
			break;
		case _sRectangle:
			break;
		case _sEllipse:
			break;
		case _sRotEllipse:
			break;
		case _sRotRectangle:
			break;
		case _sRing:
			break;
		case _sFree:
			break;
		case _sPoly:
			break;
	}
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  x1
//	  x2
//	  y
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	FlexLine::_Set(int x1, int x2 ,int y)
{
	_SetLeftX(x1);
	SetNumb(x2-x1+1);
	if(GetNumb()==0){
		SetNumb(1);
	}
	_SetAbsY(y);
}



/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
FlexArea::FlexArea(void)
{
	Clear();
}
/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  src
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
FlexArea::FlexArea(const FlexArea &src)
{
	*this=src;
}

FlexArea::FlexArea(int tDotPerLine,int tMaxLines) : FlexAreaBasePure(tDotPerLine,tMaxLines)
{
	Clear();
}
/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
FlexArea::~FlexArea(void)
{
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	  FlexArea::IsOvered(int DotPerLine, int MaxLines)const 
{
	for(int i=0;i<GetFLineLen();i++){
		if(GetFLineLeftX(i) >=DotPerLine
		|| GetFLineAbsY(i)	>=MaxLines
		|| GetFLineRightX(i)>=DotPerLine){
			return(true);
		}
	}
	return(false);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  x1
//	  y1
//	  x2
//	  y2
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	  FlexArea::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)const
{
	if(IsNull()==true){
		return false;
	}
	x1=GetMinX();
	y1=GetMinY();
	x2=GetMaxX();
	y2=GetMaxY();
	return true;
}

void	FlexAreaBasePure::Swap(FlexAreaBasePure &dest)
{
	struct  FlexLine    *TmpFLines=FLines;
	FLines=dest.FLines;
	dest.FLines=TmpFLines;
	swap(Len,dest.Len);
	swap(AddX,dest.AddX);
	swap(AddY,dest.AddY);
	swap(MinX,dest.MinX);
	swap(MaxX,dest.MaxX);
	swap(PatternByte,dest.PatternByte);

	struct  BlockShape  *TmpAShape=AShape;
	AShape=dest.AShape;
	dest.AShape=TmpAShape;
}
void	FlexArea::Swap(FlexArea &dest)
{
	FlexAreaBasePure::Swap(*((FlexAreaBasePure *)&dest));
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  str
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
struct	FlexAreaPack
{
	uint32	IPoint;
	int32	AddX,AddY;
	int32   iDotPerLine,iMaxLines;
};

double  FlexAreaBasePure::GetLength(void)	const
{
	return hypot(GetWidth(),GetHeight());
}

bool	  FlexAreaBasePure::WriteBase(QIODevice *str)
{
	if(AShape!=NULL){
		if(str->write((const char *)AShape,sizeof(*AShape))!=sizeof(*AShape)){
			return(false);
		}
		if(AShape->Kind==BlockShape::_sPoly){
			if(str->write((const char *)AShape->Shape.bsPoly.XY,AShape->Shape.bsPoly.PointCount*sizeof(XYData))!=AShape->Shape.bsPoly.PointCount*sizeof(XYData)){
				return(false);
			}
		}
	}
	else{
		if(str->write((const char *)&StaticAShape,sizeof(StaticAShape))!=sizeof(StaticAShape)){
			return(false);
		}
	}
	int Len=GetFLineLen();
	if(str->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(Len!=0){
		if(str->write((const char *)GetFLinePoint(),sizeof(struct FlexLine)*Len)!=(int)(sizeof(struct FlexLine)*Len)){
			return(false);
		}
	}

	struct	FlexAreaPack	FlexAreaPackData;
	FlexAreaPackData.IPoint	=0;
	FlexAreaPackData.AddX	=AddX;
	FlexAreaPackData.AddY	=AddY;

	if(str->write((const char *)&FlexAreaPackData,sizeof(FlexAreaPackData))!=sizeof(FlexAreaPackData)){
		return(false);
	}

	return(true);
}
bool	  FlexAreaBasePure::ReadBase(QIODevice *str)
{
	struct  BlockShape  iAShape;

	Clear();
	if(str->read((char *)&iAShape,sizeof(iAShape))!=sizeof(iAShape)){
		return(false);
	}
	if(iAShape.Kind==BlockShape::_sNone){
		if(AShape!=NULL){
			delete	AShape;
			AShape=NULL;
		}
	}
	else{
		if(AShape==NULL){
			AShape=new struct  BlockShape;
		}
		else{
			if(AShape->Kind==BlockShape::_sPoly){
				delete	[]AShape->Shape.bsPoly.XY;
			}
		}
		if(iAShape.Kind==BlockShape::_sPoly){
			iAShape.Shape.bsPoly.XY=new XYData[iAShape.Shape.bsPoly.PointCount];
			if(str->read((char *)iAShape.Shape.bsPoly.XY,iAShape.Shape.bsPoly.PointCount*sizeof(XYData))!=iAShape.Shape.bsPoly.PointCount*sizeof(XYData)){
				return(false);
			}
		}
		*AShape=iAShape;
	}
	int mLen;
	if(str->read((char *)&mLen,sizeof(mLen))!=sizeof(mLen)){
		return(false);
	}
	struct FlexLine *FL=NULL;
	if(mLen!=0){
		FL=new struct FlexLine[mLen];
		if(str->read((char *)FL,sizeof(FL[0])*mLen)!=(int)(sizeof(FL[0])*mLen)){
			delete	[]FL;
			return(false);
		}
	}
	struct	FlexAreaPack	FlexAreaPackData;
	if(str->read((char *)&FlexAreaPackData,sizeof(FlexAreaPackData))!=sizeof(FlexAreaPackData)){
		return(false);
	}
	uint32	mIndexPoint	=FlexAreaPackData.IPoint;
	AddX=FlexAreaPackData.AddX;
	AddY=FlexAreaPackData.AddY;


	//if(str->read((char *)&mIndexPoint,sizeof(mIndexPoint))!=sizeof(mIndexPoint)){
	//	if(FL!=NULL){
	//		delete	[]FL;
	//	}
	//	return(false);
	//}

	SetFLine(FL,mLen ,mIndexPoint);

	/*
	if(str->read((char *)&AddX,sizeof(AddX))!=sizeof(AddX)){
		return(false);
	}
	if(str->read((char *)&AddY,sizeof(AddY))!=sizeof(AddY)){
		return(false);
	}
	int32     iDotPerLine,iMaxLines;
	if(str->read((char *)&iDotPerLine,sizeof(iDotPerLine))!=sizeof(iDotPerLine)){
		return(false);
	}
	if(str->read((char *)&iMaxLines,sizeof(iMaxLines))!=sizeof(iMaxLines)){
		return(false);
	}
	*/

	return(true);
}

bool	  FlexAreaBasePure::WriteBaseVer105(QIODevice *str)
{
	if(AShape!=NULL){
		bool	Flag=true;
		if(str->write((const char *)&Flag,sizeof(Flag))!=sizeof(Flag)){
			return(false);
		}
		if(str->write((const char *)AShape,sizeof(*AShape))!=sizeof(*AShape)){
			return(false);
		}
		if(AShape->Kind==BlockShape::_sPoly){
			if(str->write((const char *)AShape->Shape.bsPoly.XY,AShape->Shape.bsPoly.PointCount*sizeof(XYData))!=AShape->Shape.bsPoly.PointCount*sizeof(XYData)){
				return(false);
			}
		}
	}
	else{
		bool	Flag=false;
		if(str->write((const char *)&Flag,sizeof(Flag))!=sizeof(Flag)){
			return(false);
		}

	}
	int Len=GetFLineLen();
	if(str->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(Len!=0){
		if(str->write((const char *)GetFLinePoint(),sizeof(struct FlexLine)*Len)!=(int)(sizeof(struct FlexLine)*Len)){
			return(false);
		}
	}
	uint32	IPoint=0;
	if(str->write((const char *)&IPoint,sizeof(IPoint))!=sizeof(IPoint)){
		return(false);
	}
	if(str->write((const char *)&AddX,sizeof(AddX))!=sizeof(AddX)){
		return(false);
	}
	if(str->write((const char *)&AddY,sizeof(AddY))!=sizeof(AddY)){
		return(false);
	}

	return(true);
}
bool	  FlexAreaBasePure::ReadBaseVer105(QIODevice *str)
{
	Clear();
	bool	Flag;
	if(str->read((char *)&Flag,sizeof(Flag))!=sizeof(Flag)){
		return(false);
	}
	if(Flag==false){
		if(AShape!=NULL){
			delete	AShape;
			AShape=NULL;
		}
	}
	else{
		if(AShape==NULL){
			AShape=new struct  BlockShape;
		}
		else{
			if(AShape->Kind==BlockShape::_sPoly){
				delete	[]AShape->Shape.bsPoly.XY;
			}
		}
		if(str->read((char *)AShape,sizeof(*AShape))!=sizeof(*AShape)){
			return(false);
		}
		if(AShape->Kind==BlockShape::_sPoly){
			AShape->Shape.bsPoly.XY=new XYData[AShape->Shape.bsPoly.PointCount];
			if(str->read((char *)AShape->Shape.bsPoly.XY,AShape->Shape.bsPoly.PointCount*sizeof(XYData))!=AShape->Shape.bsPoly.PointCount*sizeof(XYData)){
				return(false);
			}
		}
	}
	int mLen;
	if(str->read((char *)&mLen,sizeof(mLen))!=sizeof(mLen)){
		return(false);
	}
	struct FlexLine *FL=NULL;
	if(mLen!=0){
		FL=new struct FlexLine[mLen];
		if(str->read((char *)FL,sizeof(FL[0])*mLen)!=(int)(sizeof(FL[0])*mLen)){
			delete	[]FL;
			return(false);
		}
	}
	uint32	mIndexPoint;
	if(str->read((char *)&mIndexPoint,sizeof(mIndexPoint))!=sizeof(mIndexPoint)){
		if(FL!=NULL){
			delete	[]FL;
		}
		return(false);
	}

	SetFLine(FL,mLen ,mIndexPoint);

	if(str->read((char *)&AddX,sizeof(AddX))!=sizeof(AddX)){
		return(false);
	}
	if(str->read((char *)&AddY,sizeof(AddY))!=sizeof(AddY)){
		return(false);
	}

	return(true);
}

bool	  FlexAreaBasePure::WriteBaseVer106(QIODevice *str)
{
	if(AShape!=NULL){
		bool	Flag=true;
		if(str->write((const char *)&Flag,sizeof(Flag))!=sizeof(Flag)){
			return(false);
		}
		if(str->write((const char *)AShape,sizeof(*AShape))!=sizeof(*AShape)){
			return(false);
		}
		if(AShape->Kind==BlockShape::_sPoly){
			if(str->write((const char *)AShape->Shape.bsPoly.XY,AShape->Shape.bsPoly.PointCount*sizeof(XYData))!=AShape->Shape.bsPoly.PointCount*sizeof(XYData)){
				return(false);
			}
		}
	}
	else{
		bool	Flag=false;
		if(str->write((const char *)&Flag,sizeof(Flag))!=sizeof(Flag)){
			return(false);
		}

	}
	bool	OwningFLines;
	if(str->write((const char *)&OwningFLines,sizeof(OwningFLines))!=sizeof(OwningFLines)){
		return(false);
	}
	int Len=GetFLineLen();
	if(str->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(Len!=0 && OwningFLines==true){
		if(str->write((const char *)GetFLinePoint(),sizeof(struct FlexLine)*Len)!=(int)(sizeof(struct FlexLine)*Len)){
			return(false);
		}
	}
	uint32	IPoint=0;
	if(str->write((const char *)&IPoint,sizeof(IPoint))!=sizeof(IPoint)){
		return(false);
	}
	if(str->write((const char *)&AddX,sizeof(AddX))!=sizeof(AddX)){
		return(false);
	}
	if(str->write((const char *)&AddY,sizeof(AddY))!=sizeof(AddY)){
		return(false);
	}

	return(true);
}

bool	  FlexAreaBasePure::ReadBaseVer106(QIODevice *str)
{
	Clear();
	bool	Flag;
	if(str->read((char *)&Flag,sizeof(Flag))!=sizeof(Flag)){
		return(false);
	}
	if(Flag==false){
		if(AShape!=NULL){
			delete	AShape;
			AShape=NULL;
		}
	}
	else{
		if(AShape==NULL){
			AShape=new struct  BlockShape;
		}
		else{
			if(AShape->Kind==BlockShape::_sPoly){
				delete	[]AShape->Shape.bsPoly.XY;
			}
		}
		if(str->read((char *)AShape,sizeof(*AShape))!=sizeof(*AShape)){
			return(false);
		}
		if(AShape->Kind==BlockShape::_sPoly){
			AShape->Shape.bsPoly.XY=new XYData[AShape->Shape.bsPoly.PointCount];
			if(str->read((char *)AShape->Shape.bsPoly.XY,AShape->Shape.bsPoly.PointCount*sizeof(XYData))!=AShape->Shape.bsPoly.PointCount*sizeof(XYData)){
				return(false);
			}
		}
	}
	bool	OwningFLines;
	if(str->read((char *)&OwningFLines,sizeof(OwningFLines))!=sizeof(OwningFLines)){
		return(false);
	}
	int mLen;
	if(str->read((char *)&mLen,sizeof(mLen))!=sizeof(mLen)){
		return(false);
	}
	if(OwningFLines==false){
		mLen=0;
	}

	struct FlexLine *FL=NULL;
	if(OwningFLines==true){
		if(mLen!=0){
			FL=new struct FlexLine[mLen];
			if(str->read((char *)FL,sizeof(FL[0])*mLen)!=(int)(sizeof(FL[0])*mLen)){
				delete	[]FL;
				return(false);
			}
		}
	}
	uint32	mIndexPoint;
	if(str->read((char *)&mIndexPoint,sizeof(mIndexPoint))!=sizeof(mIndexPoint)){
		if(FL!=NULL){
			delete	[]FL;
		}
		return(false);
	}

	SetFLine(FL,mLen ,mIndexPoint);

	if(str->read((char *)&AddX,sizeof(AddX))!=sizeof(AddX)){
		return(false);
	}
	if(str->read((char *)&AddY,sizeof(AddY))!=sizeof(AddY)){
		return(false);
	}

	return(true);
}

bool	  FlexAreaBasePure::WriteBaseVer107(QIODevice *str)
{
	if(AShape!=NULL){
		bool	Flag=true;
		if(str->write((const char *)&Flag,sizeof(Flag))!=sizeof(Flag)){
			return(false);
		}
		if(str->write((const char *)AShape,sizeof(*AShape))!=sizeof(*AShape)){
			return(false);
		}
		if(AShape->Kind==BlockShape::_sPoly){
			if(str->write((const char *)AShape->Shape.bsPoly.XY,AShape->Shape.bsPoly.PointCount*sizeof(XYData))!=AShape->Shape.bsPoly.PointCount*sizeof(XYData)){
				return(false);
			}
		}
	}
	else{
		bool	Flag=false;
		if(str->write((const char *)&Flag,sizeof(Flag))!=sizeof(Flag)){
			return(false);
		}

	}

	int Len=GetFLineLen();
	if(str->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(Len!=0){
		if(str->write((const char *)GetFLinePoint(),sizeof(struct FlexLine)*Len)!=(int)(sizeof(struct FlexLine)*Len)){
			return(false);
		}
	}
	uint32	IPoint=0;
	if(str->write((const char *)&IPoint,sizeof(IPoint))!=sizeof(IPoint)){
		return(false);
	}
	if(str->write((const char *)&AddX,sizeof(AddX))!=sizeof(AddX)){
		return(false);
	}
	if(str->write((const char *)&AddY,sizeof(AddY))!=sizeof(AddY)){
		return(false);
	}

	return(true);
}

bool	  FlexAreaBasePure::ReadBaseVer107(QIODevice *str)
{
	Clear();
	bool	Flag;
	if(str->read((char *)&Flag,sizeof(Flag))!=sizeof(Flag)){
		return(false);
	}
	if(Flag==false){
		if(AShape!=NULL){
			delete	AShape;
			AShape=NULL;
		}
	}
	else{
		if(AShape==NULL){
			AShape=new struct  BlockShape;
		}
		else{
			if(AShape->Kind==BlockShape::_sPoly){
				delete	[]AShape->Shape.bsPoly.XY;
			}
		}
		if(str->read((char *)AShape,sizeof(*AShape))!=sizeof(*AShape)){
			return(false);
		}
		if(AShape->Kind==BlockShape::_sPoly){
			AShape->Shape.bsPoly.XY=new XYData[AShape->Shape.bsPoly.PointCount];
			if(str->read((char *)AShape->Shape.bsPoly.XY,AShape->Shape.bsPoly.PointCount*sizeof(XYData))!=AShape->Shape.bsPoly.PointCount*sizeof(XYData)){
				return(false);
			}
		}
	}

	int mLen;
	if(str->read((char *)&mLen,sizeof(mLen))!=sizeof(mLen)){
		return(false);
	}

	struct FlexLine *FL=NULL;
	if(mLen!=0){
		FL=new struct FlexLine[mLen];
		if(str->read((char *)FL,sizeof(FL[0])*mLen)!=(int)(sizeof(FL[0])*mLen)){
			delete	[]FL;
			return(false);
		}
	}

	uint32	mIndexPoint;
	if(str->read((char *)&mIndexPoint,sizeof(mIndexPoint))!=sizeof(mIndexPoint)){
		if(FL!=NULL){
			delete	[]FL;
		}
		return(false);
	}
	SetFLine(FL,mLen ,mIndexPoint);

	if(str->read((char *)&AddX,sizeof(AddX))!=sizeof(AddX)){
		return(false);
	}
	if(str->read((char *)&AddY,sizeof(AddY))!=sizeof(AddY)){
		return(false);
	}

	return(true);
}

bool	  FlexArea::Write(QIODevice *str)
{
	BYTE	LVer=107;

	if(str->write((const char *)&LVer,sizeof(LVer))!=sizeof(LVer)){
		return(false);
	}
	if(WriteBaseVer107(str)==false){
		return(false);
	}

	return(true);
}


bool	  FlexArea::Read(QIODevice *str)
{
	BYTE	LVer;

	if(str->read((char *)&LVer,sizeof(LVer))!=sizeof(LVer)){
		return(false);
	}

	if(LVer==102){
		if(ReadBase(str)==false){
			return(false);
		}
		Regulate();
	}
	else if(LVer==105){
		if(ReadBaseVer105(str)==false){
			return(false);
		}
		Regulate();
	}
	else if(LVer==106){
		if(ReadBaseVer106(str)==false){
			return(false);
		}
		Regulate();
	}
	else if(LVer==107){
		if(ReadBaseVer107(str)==false){
			return(false);
		}
		Regulate();
	}
	return(true);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/

void	  FlexAreaBasePure::Clear(void)
{
	if(Len!=0){
		if(FLines!=NULL){
			delete	[]FLines;
		}
	}
	FLines=NULL;

	if(AShape!=NULL){
		delete	AShape;
		AShape=NULL;
	}
	Len=0;
	PatternByte=0;

	AddX=0;
	AddY=0;

	MinX=0;
	MaxX=0;
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  x1
//	  y1
//	  x2
//	  y2
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::SetRectangle(int x1 ,int y1 ,int x2 ,int y2)
{
	Clear();

	if(x1>x2){
		swap(x1,x2);
	}
	if(y1>y2){
		swap(y1,y2);
	}
	if(AShape==NULL){
		AShape=new struct  BlockShape;
	}
	if(AShape->Kind==BlockShape::_sPoly){
		delete	[]AShape->Shape.bsPoly.XY;
	}

	AShape->Kind=BlockShape::_sRectangle;
	AShape->Shape.bsRectangle.X1=x1;
	AShape->Shape.bsRectangle.Y1=y1;
	AShape->Shape.bsRectangle.X2=x2;
	AShape->Shape.bsRectangle.Y2=y2;

	int Len=y2-y1+1;
	struct FlexLine *FL=new struct FlexLine[Len];
	int n=0;
	for(int y=y1;y<=y2;y++,n++){
		FL[n]._SetAbsY (y);
		FL[n]._SetLeftX(x1);
		FL[n]. SetNumb (x2-x1+1);
		}
	SetFLine(FL,Len);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  cx
//	  cy
//	  rx
//	  ry
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::SetEllipse(int cx ,int cy ,int rx ,int ry)
{
	Clear();

	if(rx==0){
		rx=1;
	}
	if(ry==0){
		ry=1;
	}
	if(AShape==NULL){
		AShape=new struct  BlockShape;
	}
	if(AShape->Kind==BlockShape::_sPoly){
		delete	[]AShape->Shape.bsPoly.XY;
	}
	AShape->Kind=BlockShape::_sEllipse;
	AShape->Shape.bsEllipse.Cx=cx;
	AShape->Shape.bsEllipse.Cy=cy;
	AShape->Shape.bsEllipse.Rx=rx;
	AShape->Shape.bsEllipse.Ry=ry;

	int Len=ry*2+1;
	struct FlexLine *FL=new struct FlexLine[Len];
	int n=0;
	for(int y= -ry;y<=ry;y++,n++){
		FL[n]._SetAbsY(cy+y);
		int k=(int)(rx*sqrt(1.0-((double)y*(double)y)/((double)ry*(double)ry)));
		FL[n]._SetLeftX(cx-k);
		FL[n]. SetNumb (2*k+1);
		}
	SetFLine(FL,Len);
}

struct	RotRectPointStruct
{
	double	X,Y;
};

void	FlexArea::SetRotRectangle(int cx ,int cy, int rx ,int ry ,double SRadian)
{
	double	coss=cos(SRadian);
	double	sins=sin(SRadian);
	struct	RotRectPointStruct	Points[4];

	Points[0].X=(int)((double)(-rx)*coss - (double)(-ry)*sins)+cx;
	Points[0].Y=(int)((double)(-rx)*sins + (double)(-ry)*coss)+cy;

	Points[1].X=(int)((double)(+rx)*coss - (double)(-ry)*sins)+cx;
	Points[1].Y=(int)((double)(+rx)*sins + (double)(-ry)*coss)+cy;

	Points[2].X=(int)((double)(+rx)*coss - (double)(+ry)*sins)+cx;
	Points[2].Y=(int)((double)(+rx)*sins + (double)(+ry)*coss)+cy;

	Points[3].X=(int)((double)(-rx)*coss - (double)(+ry)*sins)+cx;
	Points[3].Y=(int)((double)(-rx)*sins + (double)(+ry)*coss)+cy;

	for(;;){
		bool	Changed=false;
		for(int i=0;i<3;i++){
			if(Points[i].Y>Points[i+1].Y || (Points[i].Y==Points[i+1].Y && Points[i].X>Points[i+1].X)){
				RotRectPointStruct	tmp=Points[i];
				Points[i]=Points[i+1];
				Points[i+1]=tmp;
				Changed=true;
			}
		}
		if(Changed==false){
			break;
		}
	}
	if(Points[1].X>Points[2].X){
		RotRectPointStruct	tmp=Points[1];
		Points[1]=Points[2];
		Points[2]=tmp;
	}
/*
		0				0	1
	1
			2
		3				3	4
*/

	int Len=Points[3].Y-Points[0].Y+1;
	struct FlexLine *FL=new struct FlexLine[Len];

	int	n=0;
	if(Points[0].Y==Points[1].Y){
		/*
			0	1


			3	4
		*/
		for(int y=Points[0].Y;y<=Points[3].Y;y++){
			FL[n]._SetAbsY (y);
			FL[n]._SetLeftX((int)Points[0].X);
			FL[n]. SetNumb (Points[1].X-Points[0].X+1);
			n++;
		}
	}
	else{
		double	D10=(Points[1].X-Points[0].X)/(Points[1].Y-Points[0].Y);
		double	D20=(Points[2].X-Points[0].X)/(Points[2].Y-Points[0].Y);
		double	D13=(Points[3].X-Points[1].X)/(Points[3].Y-Points[1].Y);
		double	D23=(Points[3].X-Points[2].X)/(Points[3].Y-Points[2].Y);

		if(Points[1].Y<=Points[2].Y){
			/*
					0
				1
						2
					3
			*/
			int	y;
			for(y=Points[0].Y;y<Points[1].Y;y++){
				double	x1=D10*(y-Points[0].Y)+Points[0].X;
				double	x2=D20*(y-Points[0].Y)+Points[0].X;
				FL[n]._SetAbsY (y);
				FL[n]._SetLeftX((int)x1);
				FL[n]. SetNumb (ceil(x2-x1+0.5));
				n++;
			}
			for(;y<Points[2].Y;y++){
				double	x1=D13*(y-Points[1].Y)+Points[1].X;
				double	x2=D20*(y-Points[0].Y)+Points[0].X;
				FL[n]._SetAbsY (y);
				FL[n]._SetLeftX((int)x1);
				FL[n]. SetNumb (ceil(x2-x1+0.5));
				n++;
			}
			for(;y<=Points[3].Y;y++){
				double	x1=D13*(y-Points[1].Y)+Points[1].X;
				double	x2=D23*(y-Points[2].Y)+Points[2].X;
				FL[n]._SetAbsY (y);
				FL[n]._SetLeftX((int)x1);
				FL[n]. SetNumb (ceil(x2-x1+0.5));
				n++;
			}
		}
		else{
			/*
					0
						2
				1
					3
			*/
			int	y;
			for(y=Points[0].Y;y<Points[2].Y;y++){
				double	x1=D10*(y-Points[0].Y)+Points[0].X;
				double	x2=D20*(y-Points[0].Y)+Points[0].X;
				FL[n]._SetAbsY (y);
				FL[n]._SetLeftX((int)x1);
				FL[n]. SetNumb (ceil(x2-x1+0.5));
				n++;
			}
			for(;y<Points[1].Y;y++){
				double	x1=D10*(y-Points[0].Y)+Points[0].X;
				double	x2=D23*(y-Points[2].Y)+Points[2].X;
				FL[n]._SetAbsY (y);
				FL[n]._SetLeftX((int)x1);
				FL[n]. SetNumb (ceil(x2-x1+0.5));
				n++;
			}
			for(;y<=Points[3].Y;y++){
				double	x1=D13*(y-Points[1].Y)+Points[1].X;
				double	x2=D23*(y-Points[2].Y)+Points[2].X;
				FL[n]._SetAbsY (y);
				FL[n]._SetLeftX((int)x1);
				FL[n]. SetNumb (ceil(x2-x1+0.5));
				n++;
			}
		}
	}
	SetFLine(FL,n);
}
void	FlexArea::SetRotEllipse(int cx ,int cy ,int rx ,int ry,double SRadian)
{
	double	c=cos(SRadian);
	double	s=sin(SRadian);
	double	rx2=rx*rx;
	double	ry2=ry*ry;
	double	c2=(double)c*(double)c;
	double	s2=(double)s*(double)s;
	double	K=sqrt((c2*ry2+s2*rx2)/(c2*c2+s2*s2+2*c2*s2));
	int	KInt=floor(K);
	struct FlexLine *FL=new struct FlexLine[KInt*2+1];
	int	n=0;
	for(int y= -KInt;y<=KInt;y++){
		double	D=(c2*ry2+rx2*s2-(double)y*(double)y)*rx2*ry2;
		if(D<0){
			continue;
		}
		D=sqrt(D);
		double	E=(rx2-ry2)*c*s*y;
		double	G=c2*ry2+s2*rx2;
		int	x1=floor((E-D)/G);
		int	x2=ceil((E+D)/G);

		FL[n]._SetAbsY (cy+y);
		FL[n]._SetLeftX(cx+x1);
		FL[n]. SetNumb (x2-x1+1);
		n++;
	}
	SetFLine(FL,n);
}
void	FlexArea::SetRing(int cx ,int cy ,int rx1 ,int ry1 ,int rx2 ,int ry2)
{
	if(rx1>rx2){
		swap(rx1,rx2);
	}
	if(ry1>ry2){
		swap(ry1,ry2);
	}

#if 1 // 20100212
	int itmp = 0;

	if ((0 == ry1) || (0 == ry2))
		itmp = 1;

	struct FlexLine *FL=new struct FlexLine[(ry2+ry1)*2+1 + itmp];
#else
	struct FlexLine *FL=new struct FlexLine[(ry2+ry1)*2+1];
#endif

	int	y;
	int	n=0;
	for(y=-ry2;y<=-ry1;y++){

#if 1 // 20100210
		double	D;

		if (0.0 == (double)ry2 * (double)ry2)
			D = rx2 * sqrt(1.0);
		else
			D = rx2 * sqrt(1.0 - (double)y * (double)y / ((double)ry2 * (double)ry2));
#else
		double	D=rx2*sqrt(1.0-(double)y*(double)y/((double)ry2*(double)ry2));
#endif

		int	x1=floor(cx-D);
		int	x2=ceil(cx+D);
		FL[n]._SetAbsY (cy+y);
		FL[n]._SetLeftX(x1);
		FL[n]. SetNumb (x2-x1);
		n++;
	}
	for(y=-ry1+1;y<ry1;y++){

#if 1 // 20100210
		double	D2;

		if (0.0 == (double)ry2 * (double)ry2)
			D2 = rx2 * sqrt(1.0);
		else
			D2 = rx2 * sqrt(1.0 - (double)y * (double)y / ((double)ry2 * (double)ry2));

		double	D1;

		if (0.0 == (double)ry1 * (double)ry1)
			D1 = rx1 * sqrt(1.0);
		else
			D1 = rx1 * sqrt(1.0 - (double)y * (double)y / ((double)ry1 * (double)ry1));
#else
		double	D2=rx2*sqrt(1.0-(double)y*(double)y/((double)ry2*(double)ry2));
		double	D1=rx1*sqrt(1.0-(double)y*(double)y/((double)ry1*(double)ry1));
#endif

		int	xa1=floor(cx-D2);
		int	xa2=ceil(cx+D2);
		int	xb1=floor(cx-D1);
		int	xb2=ceil(cx+D1);
		FL[n]._SetAbsY (cy+y);
		FL[n]._SetLeftX(xa1);
		FL[n]. SetNumb (xb1-xa1);
		n++;
		FL[n]._SetAbsY (cy+y);
		FL[n]._SetLeftX(xb2);
		FL[n]. SetNumb (xa2-xb2);
		n++;
	}
	for(y=ry1;y<=ry2;y++){

#if 1 // 20100210
		double	D;

		if (0.0 == (double)ry2 * (double)ry2)
			D = rx2 * sqrt(1.0);
		else
			D = rx2 * sqrt(1.0 - (double)y * (double)y / ((double)ry2 * (double)ry2));
#else
		double	D=rx2*sqrt(1.0-(double)y*(double)y/((double)ry2*(double)ry2));
#endif

		int	x1=floor(cx-D);
		int	x2=ceil(cx+D);
		FL[n]._SetAbsY (cy+y);
		FL[n]._SetLeftX(x1);
		FL[n]. SetNumb (x2-x1);
		n++;
	}
	SetFLine(FL,n);
}

static	int	CutLineByAngle(int X1,int X2,int Y
					,int Cx,int Cy ,double s1,double s2 ,double CosS1 ,double SinS1,double CosS2 ,double SinS2
					,int P[2][4])
{
	if(X1>X2)	swap(X1,X2);

	double	ts1=GetSita(X1-Cx,Y-Cy);
	double	ts2=GetSita(X2-Cx,Y-Cy);
	bool	b1=IsInsideAngle(ts1,s1,s2);
	bool	b2=IsInsideAngle(ts2,s1,s2);
	if(b1==true && b2==true){
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=X1;
					P[0][1]=Y;
					P[0][2]=X2;
					P[0][3]=Y;
					return 1;
				}
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX1;
				P[0][3]=Y;
				P[1][0]=hX2;
				P[1][1]=Y;
				P[1][2]=X2;
				P[1][3]=Y;
				return 2;
			}
		}
		P[0][0]=X1;
		P[0][1]=Y;
		P[0][2]=X2;
		P[0][3]=Y;
		return 1;
	}
	if(b1==true && b2==false){
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){				
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=X1;
					P[0][1]=Y;
					P[0][2]=hX2;
					P[0][3]=Y;
					return 1;
				}
				else{
					P[0][0]=X1;
					P[0][1]=Y;
					P[0][2]=hX1;
					P[0][3]=Y;
					return 1;
				}
			}
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX1;
				P[0][3]=Y;
				return 1;
			}
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1==0 && SinS2!=0){
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1!=0 && SinS2==0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=X1;
				P[0][1]=Y;
				P[0][2]=hX1;
				P[0][3]=Y;
				return 1;
			}
		}
	}
	if(b1==false && b2==true){
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){				
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=hX1;
					P[0][1]=Y;
					P[0][2]=X2;
					P[0][3]=Y;
					return 1;
				}
				else{
					P[0][0]=hX2;
					P[0][1]=Y;
					P[0][2]=X2;
					P[0][3]=Y;
					return 1;
				}
			}
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=hX1;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=hX2;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1==0 && SinS2!=0){
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(X1<=hX2 && hX2<=X2){
				P[0][0]=hX2;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
		}
		if(SinS1!=0 && SinS2==0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			if(X1<=hX1 && hX1<=X2){
				P[0][0]=hX1;
				P[0][1]=Y;
				P[0][2]=X2;
				P[0][3]=Y;
				return 1;
			}
		}
	}
	else{
		if(SinS1!=0 && SinS2!=0){
			int	hX1=CosS1*(Y-Cy)/SinS1+Cx;
			int	hX2=CosS2*(Y-Cy)/SinS2+Cx;
			if(hX1>hX2)	swap(hX1,hX2);
			if((X1<=hX1 && hX1<=X2) && (X1<=hX2 && hX2<=X2)){
				double	ts3=GetSita((hX1+hX2)/2-Cx,Y-Cy);
				bool	b3=IsInsideAngle(ts3,s1,s2);
				if(b3==true){
					P[0][0]=hX1;
					P[0][1]=Y;
					P[0][2]=hX2;
					P[0][3]=Y;
					return 1;
				}
			}
		}
	}
	return 0;
}

void	FlexArea::SetRingArc(int Cx ,int Cy ,int Rx1 ,int Ry1 ,int Rx2 ,int Ry2 ,double S1 ,double S2)
{
	double	CosS1=cos(S1);
	double	SinS1=sin(S1);
	double	CosS2=cos(S2);
	double	SinS2=sin(S2);

	if(Ry2<Ry1){
		swap(Rx1,Rx2);
		swap(Ry1,Ry2);
	}
	double	Ry22=Ry2*Ry2;
	double	Ry11=Ry1*Ry1;
	double	Rx22=Rx2*Rx2;
	double	Rx11=Rx1*Rx1;

	struct FlexLine *FL=new struct FlexLine[((Ry2+Ry1)*2+1)*2];
	int	n=0;
	int	ILen=Ry2*2+1;
	for(int i=0;i<ILen;i++){
		int	y=i-Ry2;
		if(y<=-Ry1 || Ry1<=y){
			double D;

			if (0.0 == Ry22)
				D = Rx22;
			else
				D = Rx22 - Rx22 * y * y / Ry22;

			if(D>=0){
				D=sqrt(D);
				double	X1=Cx-D;
				double	X2=Cx+D;

				int	P[2][4];
				int	N=CutLineByAngle(X1,X2,Cy+y
									,Cx,Cy ,S1,S2,CosS1,SinS1,CosS2,SinS2
									,P);
				for(int k=0;k<N;k++){
					FL[n]._SetAbsY (P[k][1]);
					FL[n]._SetLeftX(P[k][0]);
					FL[n]. SetNumb (P[k][2]-P[k][0]);
					n++;
				}
			}
		}
		else{
			double D2;

			if (0.0 == Ry22)
				D2 = Rx22;
			else
				D2 = Rx22 - Rx22 * y * y / Ry22;

			if(D2>=0){
				D2=sqrt(D2);
				double	X21=Cx-D2;
				double	X22=Cx+D2;

				double D1;

				if (0.0 == Ry11)
					D1 = Rx11;
				else
					D1 = Rx11 - Rx11 * y * y / Ry11;

				if(D1>=0){
					D1=sqrt(D1);
					double	X11=Cx-D1;
					double	X12=Cx+D1;
					int	P[2][4];
					int	N;
					N=CutLineByAngle(X11,X21,Cy+y
										,Cx,Cy ,S1,S2,CosS1,SinS1,CosS2,SinS2
										,P);
					for(int k=0;k<N;k++){
						FL[n]._SetAbsY (P[k][1]);
						FL[n]._SetLeftX(P[k][0]);
						FL[n]. SetNumb (P[k][2]-P[k][0]);
						n++;
					}
					N=CutLineByAngle(X12,X22,Cy+y
										,Cx,Cy ,S1,S2,CosS1,SinS1,CosS2,SinS2
										,P);
					for(int k=0;k<N;k++){
						FL[n]._SetAbsY (P[k][1]);
						FL[n]._SetLeftX(P[k][0]);
						FL[n]. SetNumb (P[k][2]-P[k][0]);
						n++;
					}
				}
			}
		}
	}
	SetFLine(FL,n);
}

void	FlexArea::SetLongCircle(int Cx1 ,int Cy1 ,int Cx2 ,int Cy2 ,int r)
{
	double	dx=Cx2-Cx1;
	double	dy=Cy2-Cy1;
	double	L=hypot(dx,dy);
	if(L>0.00001){
		double	hx=-dy*r/L;
		double	hy= dx*r/L;
		double	Rx11=Cx1+hx;
		double	Ry11=Cy1+hy;
		double	Rx12=Cx2+hx;
		double	Ry12=Cy2+hy;
		double	Rx21=Cx1-hx;
		double	Ry21=Cy1-hy;
		double	Rx22=Cx2-hx;
		double	Ry22=Cy2-hy;

		double	Ky11=Cy1-r;
		double	Ky12=Cy1+r;
		double	Ky21=Cy2-r;
		double	Ky22=Cy2+r;

		int	YMin=min(Ky11,Ky21);
		int	YMax=max(Ky12,Ky22);
		struct FlexLine *FL=new struct FlexLine[YMax-YMin+1];

		int	n=0;
		for(int y=YMin;y<=YMax;y++){
			int	gminx=99999999,gmaxx=-99999999;
			if(-r<=(y-Cy1) && (y-Cy1)<=r){
				double	x=sqrt((double)((double)r*(double)r-(y-Cy1)*(y-Cy1)));
				gminx=Cx1-x;
				gmaxx=Cx1+x;
			}
			long	X;
			if(GetCrossHalfInnerPoint(Rx11,Ry11,Rx12,Ry12,y , X)==true){
				if(X<gminx){
					gminx=X;
				}
				if(gmaxx<X){
					gmaxx=X;
				}
			}
			if(GetCrossHalfInnerPoint(Rx21,Ry21,Rx22,Ry22,y , X)==true){
				if(X<gminx){
					gminx=X;
				}
				if(gmaxx<X){
					gmaxx=X;
				}
			}
			if(-r<=(y-Cy2) && (y-Cy2)<=r){
				double	x=sqrt((double)(r*r-(y-Cy2)*(y-Cy2)));
				if(Cx2-x<gminx){
					gminx=Cx2-x;
				}
				if(Cx2+x>gmaxx){
					gmaxx=Cx2+x;
				}
			}
			FL[n]._SetAbsY(y);
			FL[n]._SetLeftX((int)gminx);
			FL[n].SetNumb(gmaxx-gminx);
			n++;
		}
		SetFLine(FL,n);
	}
	else{
		SetEllipse(Cx1 ,Cy1 ,r,r);
	}
}

static	bool	Cross(XYClass *a1,XYClass *af ,int &X,int y)
{
	if(a1->y==af->y){
		if(a1->y==y){
			X=a1->x;
			return true;
		}
		return false;
	}
	double	Xn,Yn;
	if(GetCrossInnerPoint( (long)a1->x, (long)a1->y, (long)af->x, (long)af->y
					, (long)-99999999,(long)y,(long)99999999,(long)y , Xn ,Yn)==false)
		return false;
	X=Xn;
	return true;
}

void	FlexArea::MakeConvexPolygon(XYClassContainer &P)
{
	if(P.GetCount()<3)
		return;

	XYClass *MinYP=NULL;
	for(XYClass *a=P.GetFirst();a!=NULL;a=a->GetNext()){
		if(MinYP==NULL || a->y<MinYP->y){
			MinYP=a;
		}
	}
	XYClass *a1=P.GetRingPrev(MinYP);
	XYClass *a2=P.GetRingNext(MinYP);
	XYClassContainer P2;
	XYClassContainer *C=&P;
	if(a1->x>a2->x){
		for(XYClass *a=P.GetLast();a!=NULL;a=a->GetPrev()){
			XYClass *b=new XYClass();
			*b=*a;
			P2.AppendList(b);
		}
		C=&P2;

		MinYP=NULL;
		for(XYClass *a=P2.GetFirst();a!=NULL;a=a->GetNext()){
			if(MinYP==NULL || a->y<MinYP->y){
				MinYP=a;
			}
		}
		a1=P2.GetRingPrev(MinYP);
		a2=P2.GetRingNext(MinYP);
	}
	XYClass *MaxYP=NULL;
	for(XYClass *a=P.GetFirst();a!=NULL;a=a->GetNext()){
		if(MaxYP==NULL || a->y>MaxYP->y){
			MaxYP=a;
		}
	}	
	XYClass *af=MinYP;
	XYClass *ab=MinYP;
	int	N=MaxYP->y-MinYP->y+1;
	struct  FlexLine    *FL=new struct FlexLine[N];
	int		X1,X2;
	int	Index=0;
	for(int y=MinYP->y;y<=MaxYP->y;y++,Index++){
		while(Cross(a1,af ,X1,y)==false){
			af=C->GetRingPrev(af);
			a1=C->GetRingPrev(a1);
		}
		while(Cross(a2,ab ,X2,y)==false){
			ab=C->GetRingNext(ab);
			a2=C->GetRingNext(a2);
		}
		FL[Index]._Set(X1,X2,y);
	}
	SetFLine(FL,Index);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  dx
//	  dy
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	BlockShape::MoveTo(int dx ,int dy)
{
	int	i;
	switch(Kind){
		case _sNone:
			break;
		case _sRectangle:
			Shape.bsRectangle.X1+=dx;
			Shape.bsRectangle.Y1+=dy;
			Shape.bsRectangle.X2+=dx;
			Shape.bsRectangle.Y2+=dy;
			break;
		case _sEllipse:
			Shape.bsEllipse.Cx+=dx;
			Shape.bsEllipse.Cy+=dy;
			break;
		case _sRotRectangle:
			Shape.bsRotRectangle.X1+=dx;
			Shape.bsRotRectangle.Y1+=dy;
			Shape.bsRotRectangle.X2+=dx;
			Shape.bsRotRectangle.Y2+=dy;
			break;
		case _sRing:
			Shape.bsRing.Cx+=dx;
			Shape.bsRing.Cy+=dy;
			break;
		case _sFree:
			break;
		case _sPoly:
			for(i=0;i<Shape.bsPoly.PointCount;i++){
				Shape.bsPoly.XY[i].x+=dx;
				Shape.bsPoly.XY[i].y+=dy;
			}
			break;
		}
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  dx
//	  dy
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/

void	  FlexAreaBasePure::MoveToNoClip(int dx, int dy)
{
	AddX+=dx;
	AddY+=dy;
	MinX+=dx;
	MaxX+=dx;

	if(AShape!=NULL){
		AShape->MoveTo(dx,dy);
	}
}

void	  FlexArea::MoveToClip(int dx, int dy
										,int mx1 ,int my1 ,int mx2 ,int my2)
{
	bool	Clipped=false;
	for(int i=0;i<GetFLineLen();i++){
		int y=GetFLineAbsY(i)+dy;
		if(y<my1 || my2<y){
			Clipped=true;
			break;
			}
		int x1	=GetFLineLeftX(i)+dx;
		int numb=GetFLineNumb(i);
		if(x1<mx1){
			Clipped=true;
			break;
			}
		if(x1+numb>mx2){
			Clipped=true;
			break;
			}
		}
	if(Clipped==false){
		MoveToNoClip(dx,dy);
		}
	else{
		struct FlexLine *FL=new struct FlexLine[GetFLineLen()];
		int mLen=0;
		for(int i=0;i<GetFLineLen();i++){
			int y=GetFLineAbsY(i)+dy;
			if(y<my1 || my2<y){
				continue;
			}
			int x1	=GetFLineLeftX(i)+dx;
			int numb=GetFLineNumb(i);
			if(x1<mx1){
				numb-=mx1-x1;
				x1=mx1;
				}
			if(x1+numb>mx2){
				numb=mx2-x1;
			}
			if(numb>0 && x1<mx2){
				FL[mLen]._SetAbsY (y);
				FL[mLen]._SetLeftX(x1);
				FL[mLen]. SetNumb (numb);
				mLen++;
				}
			}
		SetFLine(FL,mLen);
		if(AShape!=NULL){
			AShape->MoveTo(dx,dy);
		}
	}
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::Initial(int NoZone,int DotPerLine, int MaxLines)
{
	MoveToClip(0,0
				,NoZone ,NoZone
				,DotPerLine-NoZone ,MaxLines-NoZone);
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  b
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::_AddPoint(struct FlexLine &b)
{
	struct	FlexLine	*tmp=new struct FlexLine[GetFLineLen()+1];

	DirectCopyTo(tmp,GetFLineLen());
	tmp[GetFLineLen()]=b;
	QSort(tmp,GetFLineLen()+1,sizeof(struct FlexLine),YSortFunc);
	SetFLine(tmp,GetFLineLen()+1);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  b
//	  Numb
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::_AddPoints(struct FlexLine b[] ,int Numb)
{
	struct	FlexLine	*tmp=new struct FlexLine[GetFLineLen()+Numb];

	DirectCopyTo(tmp,GetFLineLen());
	for(int i=0;i<Numb;i++){
		tmp[GetFLineLen()+i]=b[i];
		}
	QSort(tmp,GetFLineLen()+Numb,sizeof(struct FlexLine),YSortFunc);
	SetFLine(tmp,GetFLineLen()+Numb);
}
/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  src
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
FlexArea    &FlexArea::operator=(const FlexArea &src)
{
	PointerCopy(&src);
	return(*this);
}
/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  src
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
FlexArea	&FlexArea::operator+=(const FlexArea &src)
{
	if(src.GetFLineLen()==0){
		return(*this);
		}

	if(GetFLineLen()==0){
		PointerCopy(&src);
		}
	else{
		if(AShape!=NULL){
			delete	AShape;
			AShape=NULL;
		}
		EatArea(&src);
		}
	return(*this);
}
void    FlexArea::CopyMove(const FlexArea &src , int dx ,int dy)
{
	PointerCopy(&src);
	MoveToNoClip(dx, dy);
}
FlexArea	&FlexArea::operator&=(const FlexArea &src)
{
	struct FlexLine *FL=new struct FlexLine[GetFLineLen()+src.GetFLineLen()];
	int	FLNumb=0;

	for(int i=0;i<GetFLineLen();i++){
		int y	=GetFLineAbsY(i);

		int	DestX1	=GetFLineLeftX(i);
		int	DestX2	=GetFLineRightX(i);
		int	Index	=src.SearchFirst(y);
		if(Index<0){
			continue;
		}
		for(int j=Index;j<src.GetFLineLen();j++){
			if(src.GetFLineAbsY(j)!=y){
				break;
			}
			int	SrcX1=src.GetFLineLeftX(j);
			int	SrcX2=src.GetFLineRightX(j);
			if(SrcX1<=DestX1 && DestX1<=SrcX2){
				int	mx1=DestX1;
				int	mx2=min(DestX2,SrcX2);
				FL[FLNumb]._SetAbsY(y);
				FL[FLNumb]._SetLeftX(mx1);
				FL[FLNumb].SetNumb(mx2-mx1);
				FLNumb++;
			}
			else if(DestX1<=SrcX1 && SrcX1<DestX2){
				int	mx1=SrcX1;
				int	mx2=min(DestX2,SrcX2);
				FL[FLNumb]._SetAbsY(y);
				FL[FLNumb]._SetLeftX(mx1);
				FL[FLNumb].SetNumb(mx2-mx1);
				FLNumb++;
			}
		}
	}
	SetFLine(FL,FLNumb);

	return(*this);
}
FlexArea	&FlexArea::operator|=(const FlexArea &src)
{
	struct FlexLine *FL=new struct FlexLine[GetFLineLen()+src.GetFLineLen()];
	int	FLNumb=0;

	for(int i=0;i<GetFLineLen();i++){
		int y	=GetFLineAbsY(i);

		int	DestX1	=GetFLineLeftX(i);
		int	DestX2	=GetFLineRightX(i);
		int	Index	=src.SearchFirst(y);
		if(Index<0){
			continue;
		}
		bool	WDestFlag=false;
		for(int j=Index;j<src.GetFLineLen();j++){
			if(src.GetFLineAbsY(j)!=y){
				break;
			}
			int	SrcX1=src.GetFLineLeftX(j);
			int	SrcX2=src.GetFLineRightX(j);
			if(SrcX2<DestX1){
				FL[FLNumb]._SetAbsY(y);
				FL[FLNumb]._SetLeftX(SrcX1);
				FL[FLNumb].SetNumb(SrcX2-SrcX1);
				FLNumb++;
			}
			else if(SrcX1<DestX1 && DestX1<=SrcX2 && SrcX2<=DestX2){
				DestX1=SrcX1;
			}
			else if(DestX1<=SrcX1 && SrcX2<=DestX2){
			}
			else if(SrcX1<DestX1 && DestX2<SrcX2){
				DestX1=SrcX1;
				DestX2=SrcX2;
			}
			else if(DestX1<=SrcX1 && SrcX1<DestX2 && DestX2<SrcX2){
				DestX2=SrcX2;
			}
			else{
				if(WDestFlag==false){
					FL[FLNumb]._SetAbsY(y);
					FL[FLNumb]._SetLeftX(DestX1);
					FL[FLNumb].SetNumb(DestX2-DestX1);
					FLNumb++;
					WDestFlag=true;
				}
				FL[FLNumb]._SetAbsY(y);
				FL[FLNumb]._SetLeftX(SrcX1);
				FL[FLNumb].SetNumb(SrcX2-SrcX1);
				FLNumb++;
			}
		}
		if(WDestFlag==false){
			FL[FLNumb]._SetAbsY(y);
			FL[FLNumb]._SetLeftX(DestX1);
			FL[FLNumb].SetNumb(DestX2-DestX1);
			FLNumb++;
			WDestFlag=true;
		}
	}
	for(int i=0;i<src.GetFLineLen();i++){
		int y	=src.GetFLineAbsY(i);

		int	DestX1	=src.GetFLineLeftX(i);
		int	DestX2	=src.GetFLineRightX(i);
		int	Index	=SearchFirst(y);
		if(Index<0){
			FL[FLNumb]._SetAbsY(y);
			FL[FLNumb]._SetLeftX(DestX1);
			FL[FLNumb].SetNumb(DestX2-DestX1);
			FLNumb++;
		}
	}
	SortFLine(FL,FLNumb);
	SetFLine(FL,FLNumb);

	return(*this);
}

void	FlexAreaBasePure::SortFLine(struct FlexLine *FL ,int FLNumb)
{
	QSort(FL,FLNumb,sizeof(FL[0]),YSortFunc);
}
void	FlexAreaBasePure::SortFLine(void)
{
	QSort(FLines,Len,sizeof(FLines[0]),YSortFunc);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  src
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool		FlexArea::operator==(const FlexArea &src)	const
{
	if(GetFLineLen()!=src.GetFLineLen()){
		return(false);
	}
	if(GetShape()!=src.GetShape()){
		return(false);
	}
	for(int i=0;i<GetFLineLen();i++){
		if(GetFLineAbsY (i)!=src.GetFLineAbsY(i)
		|| GetFLineLeftX(i)!=src.GetFLineLeftX(i)
		|| GetFLineNumb (i)!=src.GetFLineNumb (i)){
			return(false);
		}
	}
	return(true);
}
/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  src
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool		FlexArea::operator!=(const FlexArea &src)	const
{
	return(!operator==(src));
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  x1
//	  y1
//	  x2
//	  y2
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	  FlexArea::IsInRectangle(int x1 ,int y1 ,int x2 ,int y2)const 
{
	for(int i=0;i<GetFLineLen();i++){
		if(GetFLineAbsY(i)<y1 || y2<=GetFLineAbsY(i)){
			return(false);
		}
		if(GetFLineLeftX(i)<x1 || x2<=GetFLineRightX(i)){
			return(false);
		}
	}
	return(true);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  b
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	  FlexArea::CheckOverlap(const FlexArea *b)const 
{
	if(CheckOverlapRectRect(	GetMinX(),	 GetMinY(),   GetMaxX(),   GetMaxY()
		,b->GetMinX(),b->GetMinY(),b->GetMaxX(),b->GetMaxY())==false){
		return(false);
	}

	struct	FlexLine *ks=GetFLinePoint();
	for(int i=0;i<GetFLineLen();i++,ks++){
		int ys=ks->_GetAbsY(this);
		int ix1=ks->_GetLeftX(this);
		int ix2=ks->_GetRightX(this);
		int k=b->SearchFirst(ys);
		if(k>=0){
			while(k<b->GetFLineLen() && b->GetFLineAbsY(k)==ys){
				if((b->GetFLineRightX(k))<ix1 || ix2<=b->GetFLineLeftX(k)){
					k++;
					}
				else{
					return(true);
				}
			}
		}
	}
	return(false);
}
bool    FlexArea::CheckOverlap(const FlexArea *src ,int srcDx, int srcDy)	const 
{
	if(CheckOverlapRectRect(	GetMinX(),	 GetMinY(),   GetMaxX(),   GetMaxY()
		,src->GetMinX()+srcDx,src->GetMinY()+srcDy,src->GetMaxX()+srcDx,src->GetMaxY()+srcDy)==false){
		return(false);
	}

	struct	FlexLine *ks=GetFLinePoint();
	for(int i=0;i<GetFLineLen();i++,ks++){
		int ys=ks->_GetAbsY(this);
		int ix1=ks->_GetLeftX(this);
		int ix2=ks->_GetRightX(this);
		int k=src->SearchFirst(ys-srcDy);
		if(k>=0){
			while(k<src->GetFLineLen() && (src->GetFLineAbsY(k)+srcDy)==ys){
				if((src->GetFLineRightX(k)+srcDx)<ix1 || ix2<=(src->GetFLineLeftX(k)+srcDx)){
					k++;
					}
				else{
					return(true);
				}
			}
		}
	}
	return(false);
}

bool	  FlexArea::CheckOverlapNeighbor(const FlexArea *b)const 
{
	if(CheckOverlapRectRect(	GetMinX()-1,   GetMinY()-1,   GetMaxX()+1,	 GetMaxY()+1
		,b->GetMinX()-1,b->GetMinY()-1,b->GetMaxX()+1,b->GetMaxY()+1)==false){
		return(false);
	}

	struct	FlexLine *ks=GetFLinePoint();
	int	LMaxY=0;
	for(int i=0;i<GetFLineLen();i++,ks++){
		int ys=ks->_GetAbsY(this);
		int k=b->SearchFirst(ys-1);
		LMaxY=ys;
		if(k>=0){
			int ix1=ks->_GetLeftX(this)-1;
			int ix2=ks->_GetRightX(this)+1;
			while(k<b->GetFLineLen() && b->GetFLineAbsY(k)<=(ys+1)){
				if((b->GetFLineRightX(k))<ix1 || ix2<b->GetFLineLeftX(k)){
					k++;
					}
				else{
					return(true);
				}
			}
		}
	}
	int	ii=SearchFirst(LMaxY);
	if(ii>=0){
		for(int i=ii;i<GetFLineLen();i++){
			int ys=GetFLineAbsY(i);
			int ix1=GetFLineLeftX(i)-1;
			int ix2=GetFLineRightX(i)+1;
			int k=b->SearchFirst(ys);
			if(k>=0){
				while(k<b->GetFLineLen() && b->GetFLineAbsY(k)<=(ys+1)){
					if((b->GetFLineRightX(k))<ix1 || ix2<b->GetFLineLeftX(k)){
						k++;
					}
					else{
						return(true);
					}
				}
			}
			k=b->SearchFirst(ys+1);
			if(k>=0){
				while(k<b->GetFLineLen() && b->GetFLineAbsY(k)<=(ys+1)){
					if((b->GetFLineRightX(k))<ix1 || ix2<b->GetFLineLeftX(k)){
						k++;
						}
					else{
						return(true);
					}
				}
			}
		}
	}
	return(false);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  x1
//	  y1
//	  x2
//	  y2
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	  FlexArea::CheckOverlapRectangle(int x1 ,int y1 ,int x2 ,int y2)const 
{
	if(x1>x2){
		swap(x1,x2);
	}
	if(y1>y2){
		swap(y1,y2);
	}

	if(CheckOverlapRectRect( GetMinX(),GetMinY(),GetMaxX(),GetMaxY()
		,x1  ,y1  ,x2  ,y2)==false){
		return(false);
	}

	for(int y=max(y1,GetMinY());y<=y2;y++){
		if(GetMaxY()<y){
			break;
		}
		int k=SearchFirst(y);
		if(k>=0){
			while(k<GetFLineLen() && GetFLineAbsY(k)==y){
				if(GetFLineRightX(k)<x1 || x2<GetFLineLeftX(k)){
					k++;
				}
				else{
					return(true);
				}
			}
		}
	}
	return(false);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  x1
//	  y1
//	  x2
//	  y2
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	  FlexArea::CheckOverlapLine(int x1 ,int y1 ,int x2 ,int y2)const 
{
	long X;
	long Y;
	if(y1!=y2){
		for(int i=0;i<GetFLineLen();i++){
			if(GetCrossInnerPoint(x1,y1,x2,y2
						,GetFLineLeftX(i) ,GetFLineAbsY(i)
						,GetFLineRightX(i),GetFLineAbsY(i)
						, X ,Y)==true){
				return(true);
			}
		}
	}
	else{
		if(x1>x2){
			swap(x1,x2);
		}
		for(int i=0;i<GetFLineLen();i++){
			if(GetFLineAbsY(i)==y1){
				if(x1<=GetFLineLeftX(i) && GetFLineLeftX(i)<=x2){
					return true;
				}
				if(x1<=GetFLineRightX(i) && GetFLineRightX(i)<=x2){
					return true;
				}
				if(GetFLineLeftX(i)<= x1 && x1<=GetFLineRightX(i)){
					return true;
				}
				if(GetFLineLeftX(i)<= x2 && x2<=GetFLineRightX(i)){
					return true;
				}
			}
		}
	}
	return(false);
}

bool	  FlexArea::CheckOverlapLine(double x1 ,double y1 ,double x2 ,double y2)const 
{
	double	X;
	double	Y;
	if(y1!=y2){
		for(int i=0;i<GetFLineLen();i++){
			if(GetCrossInnerPoint(x1,y1,x2,y2
						,(double)GetFLineLeftX(i) ,(double)GetFLineAbsY(i)
						,(double)GetFLineRightX(i),(double)GetFLineAbsY(i)
						, X ,Y)==true){
				return(true);
			}
		}
	}
	else{
		if(x1>x2){
			swap(x1,x2);
		}
		int	iY=(int)y1;
		for(int i=0;i<GetFLineLen();i++){
			if(GetFLineAbsY(i)==iY){
				if(x1<=GetFLineLeftX(i) && GetFLineLeftX(i)<=x2){
					return true;
				}
				if(x1<=GetFLineRightX(i) && GetFLineRightX(i)<=x2){
					return true;
				}
				if(GetFLineLeftX(i)<= x1 && x1<=GetFLineRightX(i)){
					return true;
				}
				if(GetFLineLeftX(i)<= x2 && x2<=GetFLineRightX(i)){
					return true;
				}
			}
		}
	}
	return(false);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  y
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
int 	  FlexArea::SearchFirst(int y)const 
{
	struct FlexLine m;
	m._SetAbsY((FlexArea *)this,y);

	struct FlexLine *k=(struct FlexLine *)EqualSearch(&m,GetFLinePoint(),GetFLineLen(),sizeof(struct FlexLine),YOnlySortFunc);
	if(k==NULL){
		return(-1);
	}
	//int L=(FLines-k)/sizeof(struct FlexLine);
	int L=k-GetFLinePoint();
	while(L>0){
		if(GetFLineAbsY(L)!=y){
			return(L+1);
			}
		L--;
		}
	return(L);
}



/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  x
//	  y
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/

static	int   IsIncludeSearch(const void *a ,const void *b)
{
	if(((struct FlexLine *)a)->_GetAbsY()>((struct FlexLine *)b)->_GetAbsY()){
		return(1);
	}
	if(((struct FlexLine *)a)->_GetAbsY()<((struct FlexLine *)b)->_GetAbsY()){
		return(-1);
	}
	return(0);
}


bool	  FlexArea::IsInclude(int x ,int y)const
{
	int	N=GetFLineLen();
	if(N==0){
		return false;
	}
	if(x<GetMinX() || GetMaxX()<x || y<GetMinY() || GetMaxY()<y){
		return false;
	}
	int MaxY=GetFLineAbsY(N-1);
	if(y<GetFLineAbsY(0) || MaxY<y){
		return(false);
	}

	struct	 FlexLine	Key;
	Key._SetAbsY((FlexArea *)this,y);
	struct FlexLine *c=(struct FlexLine *)EqualSearch(&Key, GetFLinePoint(), N, sizeof(struct FlexLine), IsIncludeSearch);
	if(c==NULL){
		return(false);
	}
	int LIndex=(int)(c-GetFLinePoint());
	for(int i=LIndex;i>=0;i--){
		if(GetFLineAbsY(i)!=y){
			break;
		}
		if(GetFLineLeftX(i)<=x && x<GetFLineRightX(i)){
			return(true);
		}
	}
	
	for(int i=LIndex+1;i<N;i++){
		if(GetFLineAbsY(i)!=y){
			break;
		}
		if(GetFLineLeftX(i)<=x && x<GetFLineRightX(i)){
			return(true);
		}
	}
	return(false);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	  FlexArea::IsNull(void)const
{
	if(GetFLineLen()==0){
		return(true);
	}
	return(false);
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  data
//	  xbyte
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
//uchar   *__fastcall  FlexArea::GetPattern(ImageBuffer &data)
uchar	  *FlexArea::GetPattern(ImageBuffer &data ,int64 *BuffBytes)
{
	int64	Len=GetPatternByte();
	if(BuffBytes!=NULL){
		*BuffBytes=Len;
	}
	uchar	*D=new uchar[Len];

	uchar	*p=D;
	for(int i=0;i<GetFLineLen();i++){
		BYTE	*s=data.GetY(GetFLineAbsY(i));
		memcpy(p,&s[GetFLineLeftX(i)],GetFLineNumb(i));
		p+=GetFLineNumb(i);
		}
	return(D);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  data
//	  xbyte
//	  ptn
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::RestorePattern(ImageBuffer &data ,uchar *ptn)
{
	for(int i=0;i<GetFLineLen();i++){
		BYTE	*d=data.GetY(GetFLineAbsY(i));
		memcpy(&d[GetFLineLeftX(i)],ptn,GetFLineNumb(i));
		ptn+=GetFLineNumb(i);
		}
	data.SetChanged();
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  cx
//	  cy
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::GetCenter(int &cx ,int &cy)const
{
	cx=(GetMinX()+GetMaxX())/2;
	cy=(GetMinY()+GetMaxY())/2;
}

void	FlexArea::GetCenterOrOnIt(int &x ,int &y)const
{
	GetCenter(x ,y);
	if(IsInclude(x,y)==true)
		return;
	int	mx=x;
	int	my=(y+GetMinY())/2;
	if(IsInclude(mx,my)==true){
		x=mx;
		y=my;
		return;
	}
	mx=x;
	my=(y+GetMaxY())/2;
	if(IsInclude(mx,my)==true){
		x=mx;
		y=my;
		return;
	}
	mx=(x+GetMinX())/2;
	my=y;
	if(IsInclude(mx,my)==true){
		x=mx;
		y=my;
		return;
	}
	mx=(x+GetMaxX())/2;
	my=y;
	if(IsInclude(mx,my)==true){
		x=mx;
		y=my;
		return;
	}

	if(GetFLineLen()>0){
		int	sy=GetFLineAbsY(0);
		int	sx=GetFLineLeftX(0)+GetFLineNumb(0)/2;
		for(int ty=sy+1;ty<GetMaxY();ty++){
			if(IsInclude(mx,my)==false){
				x=sx;
				y=(sy+ty)/2;
				return;
			}
		}
	}
}

void	  FlexArea::GetCenter(double &cx ,double &cy)const
{
	cx=(GetMinX()+GetMaxX())/2.0;
	cy=(GetMinY()+GetMaxY())/2.0;
}

void    FlexArea::GetCenter(DualIntClass &xy)const
{
	xy.SetXY((GetMinX()+GetMaxX())/2,(GetMinY()+GetMaxY())/2);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  srcdata
//	  srcxbyte
//	  srcylen
//	  px
//	  py
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::BuildFromRaster(uchar *srcdata ,int srcxbyte ,int srcylen
										,int px ,int py)
{
	Clear();
	//AShape.Kind=BlockShape::_sFree;
	int Len=0;

	int N=0;
	uchar	*a=srcdata;
	for(int y=0;y<srcylen;y++,a+=srcxbyte){
		uchar	*p=a;
		bool	bmode=false;
		for(int i=0;i<srcxbyte;i++,p++){
			if(*p==0 && bmode==false){
				continue;
			}
			if(*p==0xFF && bmode==true){
				continue;
			}
			uchar	mask=0x80;
			for(int x=0;x<8;x++,mask>>=1){
				if((*p&mask)!=0){
					if(bmode==true){
						continue;
					}
					else{
						bmode=true;
						//N++;
						}
					}
				else{
					if(bmode==true){
						bmode=false;
						N++;
						continue;
						}
					else{
						continue;
					}
				}
			}
		}
		if(bmode==true){
			N++;
			}
		}
	if(N==0){
		return;
	}
	Len=N;
	struct FlexLine *MFLines=new struct FlexLine[Len];

	N=0;
	a=srcdata;
	for(int y=0;y<srcylen;y++,a+=srcxbyte){
		uchar	*p=a;
		bool	bmode=false;
		for(int i=0;i<srcxbyte;i++,p++){
			if(*p==0 && bmode==false){
				continue;
			}
			if(*p==0xFF && bmode==true){
				continue;
			}
			uchar	mask=0x80;
			for(int x=0;x<8;x++,mask>>=1){
				if((*p&mask)!=0){
					if(bmode==true){
						continue;
					}
					else{
						MFLines[N]._SetLeftX(px+i*8+x);
						MFLines[N]. SetNumb(0);
						MFLines[N]._SetAbsY(py+y);
						bmode=true;
						//N++;
						}
					}
				else{
					if(bmode==true){
						MFLines[N].SetNumb(px+i*8+x - MFLines[N]._GetLeftX());
						N++;
						bmode=false;
						continue;
						}
					else{
						continue;
					}
				}
			}
		}
		if(bmode==true){
			MFLines[N].SetNumb(px+srcxbyte*8 - MFLines[N]._GetLeftX());
			N++;
			}
		}
	//QSort(FLine,Len,sizeof(MFLines),FLinesFunc);
	int i;
	for(i=0;i<Len-1;i++){
		if(MFLines[i]._GetLeftX()!=MFLines[i+1]._GetLeftX()
			&& MFLines[i]. GetNumb ()!=MFLines[i+1]. GetNumb()){
			break;
		}
	}
	//if(i>=Len-1){
	//	AShape.Kind=BlockShape::_sRectangle;
	//	}
	//else{
	//	AShape.Kind=BlockShape::_sFree;
	//}
	SetFLine(MFLines,Len);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  srcdata
//	  srcxbyte
//	  srcylen
//	  px
//	  py
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::BuildFromRaster(uchar **srcdata ,int srcxbyte ,int srcylen
										,int px ,int py)
{
	Clear();
	//AShape.Kind=BlockShape::_sFree;
	int Len=0;

	int N=0;
	for(int y=0;y<srcylen;y++){
		uchar	*a=srcdata[y];
		uchar	*p=a;
		bool	bmode=false;
		for(int i=0;i<srcxbyte;i++,p++){
			if(*p==0 && bmode==false){
				continue;
			}
			if(*p==0xFF && bmode==true){
				continue;
			}
			uchar	mask=0x80;
			for(int x=0;x<8;x++,mask>>=1){
				if((*p&mask)!=0){
					if(bmode==true){
						continue;
					}
					else{
						bmode=true;
						//N++;
						}
					}
				else{
					if(bmode==true){
						bmode=false;
						N++;
						continue;
						}
					else{
						continue;
					}
				}
			}
		}
		if(bmode==true){
			N++;
			}
		}
	if(N==0){
		return;
	}
	Len=N;
	struct FlexLine *MFLines=new struct FlexLine[Len];

	N=0;
	for(int y=0;y<srcylen;y++){
		uchar	*a=srcdata[y];
		uchar	*p=a;
		bool	bmode=false;
		for(int i=0;i<srcxbyte;i++,p++){
			if(*p==0 && bmode==false){
				continue;
			}
			if(*p==0xFF && bmode==true){
				continue;
			}
			uchar	mask=0x80;
			for(int x=0;x<8;x++,mask>>=1){
				if((*p&mask)!=0){
					if(bmode==true){
						continue;
					}
					else{
						MFLines[N]._SetLeftX(px+i*8+x);
						MFLines[N]. SetNumb(0);
						MFLines[N]._SetAbsY(py+y);
						bmode=true;
						//N++;
						}
					}
				else{
					if(bmode==true){
						MFLines[N].SetNumb(px+i*8+x - MFLines[N]._GetLeftX());
						N++;
						bmode=false;
						continue;
						}
					else{
						continue;
					}
				}
			}
		}
		if(bmode==true){
			MFLines[N].SetNumb(px+srcxbyte*8 - MFLines[N]._GetLeftX());
			N++;
			}
		}
	//QSort(FLine,Len,sizeof(MFLines),FLinesFunc);
	int i;
	for(i=0;i<Len-1;i++){
		if(MFLines[i]._GetLeftX()!=MFLines[i+1]._GetLeftX()
		&& MFLines[i]. GetNumb ()!=MFLines[i+1]. GetNumb()){
			break;
		}
	}
	//if(i>=Len-1){
	//	AShape.Kind=BlockShape::_sRectangle;
	//	}
	//else{
	//	AShape.Kind=BlockShape::_sFree;
	//}
	SetFLine(MFLines,Len);
}

void	  FlexArea::BuildFromRaster(uchar **srcdata ,int srcxbyte ,int srcylen
										,int px ,int py
										,int minx ,int miny ,int maxx ,int maxy
										,int DotPerLine, int MaxLines)
{
	Clear();
	//AShape.Kind=BlockShape::_sFree;
	int Len=0;

	if(minx>DotPerLine){
		return;
	}
	if(miny>MaxLines){
		return;
	}
	if(maxx<0){
		return;
	}
	if(maxy<0){
		return;
	}

	int N=0;
	int MinB=minx>>3;
	//int MaxB=((maxx+7)>>3)+1;
	int MaxB=((maxx+7)>>3);
	if(MinB>=srcxbyte){
		return;
	}
	if(miny<0){
		miny=0;
	}
	if(MinB<0){
		MinB=0;
	}
	for(int y=miny;y<=maxy && y<srcylen;y++){
		uchar	*a= &srcdata[y][MinB];
		uchar	*p=a;
		bool	bmode=false;
		int	ILoop=min(MaxB,srcxbyte);
		for(int i=MinB;i<ILoop;i++,p++){
			if(*p==0 && bmode==false){
				continue;
			}
			if(*p==0xFF && bmode==true){
				continue;
			}
			uchar	mask=0x80;
			for(int x=0;x<8;x++,mask>>=1){
				if((*p&mask)!=0){
					if(bmode==true){
						continue;
					}
					else{
						bmode=true;
						//N++;
						}
					}
				else{
					if(bmode==true){
						bmode=false;
						N++;
						continue;
						}
					else{
						continue;
					}
				}
			}
		}
		if(bmode==true){
			N++;
			}
		}
	if(N==0){
		return;
	}
	Len=N;
	struct FlexLine *MFLines=new struct FlexLine[Len];

	N=0;
	for(int y=miny;y<=maxy && y<srcylen;y++){
		uchar	*a= &srcdata[y][MinB];
		uchar	*p=a;
		bool	bmode=false;
		for(int i=MinB;i<MaxB && i<srcxbyte;i++,p++){
			if(*p==0 && bmode==false){
				continue;
			}
			if(*p==0xFF && bmode==true){
				continue;
			}
			uchar	mask=0x80;
			for(int x=0;x<8;x++,mask>>=1){
				if((*p&mask)!=0){
					if(bmode==true){
						continue;
					}
					else{
						MFLines[N]._SetLeftX(px+i*8+x);
						MFLines[N]. SetNumb(0);
						MFLines[N]._SetAbsY(py+y);
						bmode=true;
						//N++;
						}
					}
				else{
					if(bmode==true){
						MFLines[N].SetNumb(px+i*8+x - MFLines[N]._GetLeftX());
						N++;
						bmode=false;
						continue;
						}
					else{
						continue;
					}
				}
			}
		}
		if(bmode==true){
			MFLines[N].SetNumb(px+MaxB*8 - MFLines[N]._GetLeftX());
			N++;
			}
		}
	//QSort(FLine,Len,sizeof(MFLines),FLinesFunc);
	int i;
	for(i=0;i<Len-1;i++){
		if(MFLines[i]._GetLeftX()!=MFLines[i+1]._GetLeftX()
		&& MFLines[i]. GetNumb ()!=MFLines[i+1]. GetNumb()){
			break;
		}
	}
	//if(i>=Len-1){
	//	AShape.Kind=BlockShape::_sRectangle;
	//	}
	//else{
	//	AShape.Kind=BlockShape::_sFree;
	//}

	SetFLine(MFLines,Len);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  Px
//	  Py
//	  Lx
//	  Ly
//	  xbyte
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
uchar	*FlexArea::MakeBitData(int &Px ,int &Py ,int &Lx ,int &Ly ,int &xbyte,int DotPerLine, int MaxLines)
{
	xbyte=(GetWidth()+7)/8;
	Px=GetMinX();
	Py=GetMinY();
	Lx=GetWidth();
	Ly=GetHeight();

	uchar	*d=new uchar[Lx*xbyte];
	memset(d,0,Lx*xbyte);
	for(int i=0;i<GetFLineLen();i++){
		if(GetFLineAbsY(i)<0 || GetFLineAbsY(i)>=MaxLines){
			continue;
		}
		uchar	*p= &d[GetFLineAbsY(i)*xbyte];
		int nx	=GetFLineLeftX(i);
		int numb=GetFLineNumb(i);
		if(nx<0){
			numb+=nx;
			nx=0;
			}
		if(nx>=DotPerLine){
			continue;
		}
		if(nx+numb>=DotPerLine){
			numb=DotPerLine-nx-1;
		}
		for(int x=0;x<numb;x++,nx++){
			p[nx>>3] |= (uchar)(0x80>>(nx&7));
			}
		}
	return(d);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  data
//	  xbyte
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void  FlexArea::MakeBitData(BYTE *data ,int xbyte,int DotPerLine, int MaxLines)	const
{
	for(int i=0;i<GetFLineLen();i++){
		if(GetFLineAbsY(i)<0 || GetFLineAbsY(i)>=MaxLines){
			continue;
		}
		uchar	*p= &data[GetFLineAbsY(i)*xbyte];
		int nx	=GetFLineLeftX(i);
		int Numb=GetFLineNumb(i);
		if(nx<0){
			Numb+=nx;
			nx=0;
			}
		if(nx>=DotPerLine){
			continue;
		}
		if(nx+Numb>=DotPerLine){
			Numb=DotPerLine-nx-1;
		}
		if(Numb<8){
			for(int x=0;x<Numb;x++,nx++){
				p[nx>>3] |= (uchar)(0x80>>(nx&7));
				}
			}
		else{
			int k=nx>>3;
			int h=nx&7;
			int len=Numb;
			p[k]|=(0xFF>>h);
			len-=8-h;
			k++;
			int blen=len>>3;
			for(int t=0;t<blen;t++){
				p[k]=0xFF;
				len-=8;
				k++;
				}
			p[k]|=(0xFF<<(8-len));
			}
		}
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  data
//	  xbyte
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
struct	FlexAreaYDim
{
	int	StartI;
	int	ICount;
};

void  FlexArea::MakeBitData(BYTE **data ,int XDotLen ,int YDotLen 
							,bool EnableThread)	const
{
	if(GetFLineLen()>=50){
		struct	FlexAreaYDim	YDim[1000];
		struct	FlexAreaYDim	*YDimPoint;

		if(GetFLineLen()>sizeof(YDim)/sizeof(YDim[0])){
			YDimPoint=new struct FlexAreaYDim[GetFLineLen()];
		}
		else{
			YDimPoint=YDim;
		}
		int	YDimCount=0;
		YDimPoint[0].StartI=0;
		YDimPoint[0].ICount=0;
		for(int i=0;i<GetFLineLen();){
			if(GetFLineAbsY(YDimPoint[YDimCount].StartI)!=GetFLineAbsY(i)){
				YDimCount++;
				YDimPoint[YDimCount].StartI=i;
				YDimPoint[YDimCount].ICount=0;
			}
			else{
				YDimPoint[YDimCount].ICount++;
				i++;
			}
		}
		YDimCount++;

		if(EnableThread==false){
			for(int e=0;e<YDimCount;e++){
				for(int t=0;t<YDimPoint[e].ICount;t++){
					int	i=YDimPoint[e].StartI+t;

					if(GetFLineAbsY(i)<0 || GetFLineAbsY(i)>=YDotLen){
						continue;
					}
					uchar	*p=data[GetFLineAbsY(i)];
					int nx	=GetFLineLeftX(i);
					int Numb=GetFLineNumb(i);
					if(nx<0){
						Numb+=nx;
						nx=0;
					}
					if(nx>=XDotLen){
						continue;
					}
					if(nx+Numb>=XDotLen){
						Numb=XDotLen-nx-1;
					}
					if(Numb<8){
						for(int x=0;x<Numb;x++,nx++){
							p[nx>>3] |= (uchar)(0x80>>(nx&7));
						}
					}
					else{
						int k=nx>>3;
						int h=nx&7;
						int len=Numb;
						p[k]|=(0xFF>>h);
						len-=8-h;
						k++;
						int blen=len>>3;
						for(int t=0;t<blen;t++){
							p[k]=0xFF;
							len-=8;
							k++;
						}
						p[k]|=(0xFF<<(8-len));
					}
				}
			}
		}
		else{
			#pragma omp parallel
			{
				#pragma omp for
				for(int e=0;e<YDimCount;e++){
					for(int t=0;t<YDimPoint[e].ICount;t++){
						int	i=YDimPoint[e].StartI+t;

						if(GetFLineAbsY(i)<0 || GetFLineAbsY(i)>=YDotLen){
							continue;
						}
						uchar	*p=data[GetFLineAbsY(i)];
						int nx	=GetFLineLeftX(i);
						int Numb=GetFLineNumb(i);
						if(nx<0){
							Numb+=nx;
							nx=0;
						}
						if(nx>=XDotLen){
							continue;
						}
						if(nx+Numb>=XDotLen){
							Numb=XDotLen-nx-1;
						}
						if(Numb<8){
							for(int x=0;x<Numb;x++,nx++){
								p[nx>>3] |= (uchar)(0x80>>(nx&7));
							}
						}
						else{
							int k=nx>>3;
							int h=nx&7;
							int len=Numb;
							p[k]|=(0xFF>>h);
							len-=8-h;
							k++;
							int blen=len>>3;
							for(int t=0;t<blen;t++){
								p[k]=0xFF;
								len-=8;
								k++;
							}
							p[k]|=(0xFF<<(8-len));
						}
					}
				}
			}
		}
		if(YDimPoint!=YDim){
			delete	[]YDimPoint;
		}
	}
	else{
		for(int i=0;i<GetFLineLen();i++){
			if(GetFLineAbsY(i)<0 || GetFLineAbsY(i)>=YDotLen){
				continue;
			}
			uchar	*p=data[GetFLineAbsY(i)];
			int nx	=GetFLineLeftX(i);
			int Numb=GetFLineNumb(i);
			if(nx<0){
				Numb+=nx;
				nx=0;
			}
			if(nx>=XDotLen){
				continue;
			}
			if(nx+Numb>=XDotLen){
				Numb=XDotLen-nx-1;
			}
			if(Numb<8){
				for(int x=0;x<Numb;x++,nx++){
					p[nx>>3] |= (uchar)(0x80>>(nx&7));
				}
			}
			else{
				int k=nx>>3;
				int h=nx&7;
				int len=Numb;
				p[k]|=(0xFF>>h);
				len-=8-h;
				k++;
				int blen=len>>3;
				for(int t=0;t<blen;t++){
					p[k]=0xFF;
					len-=8;
					k++;
				}
				p[k]|=(0xFF<<(8-len));
			}
		}
	}
}

void  FlexArea::MakeNotBitData(BYTE **data ,int XDotLen ,int YDotLen ,int mx ,int my)	const
{
	if(GetFLineLen()>=50){
		struct	FlexAreaYDim	YDim[1000];
		struct	FlexAreaYDim	*YDimPoint;

		if(GetFLineLen()>sizeof(YDim)/sizeof(YDim[0])){
			YDimPoint=new struct FlexAreaYDim[GetFLineLen()];
		}
		else{
			YDimPoint=YDim;
		}
		int	YDimCount=0;
		YDimPoint[0].StartI=0;
		YDimPoint[0].ICount=0;
		for(int i=0;i<GetFLineLen();){
			if(GetFLineAbsY(YDimPoint[YDimCount].StartI)!=GetFLineAbsY(i)){
				YDimCount++;
				YDimPoint[YDimCount].StartI=i;
				YDimPoint[YDimCount].ICount=0;
			}
			else{
				YDimPoint[YDimCount].ICount++;
				i++;
			}
		}
		YDimCount++;

		//#pragma omp parallel
		//{
		//	#pragma omp for
			for(int e=0;e<YDimCount;e++){
				for(int t=0;t<YDimPoint[e].ICount;t++){
					int	i=YDimPoint[e].StartI+t;

					int	Sy=GetFLineAbsY(i)+my;
					if(Sy<0 || Sy>=YDotLen){
						continue;
					}
					uchar	*p=data[Sy];
					int nx	=GetFLineLeftX(i)+mx;
					int Numb=GetFLineNumb(i);
					if(nx<0){
						Numb+=nx;
						nx=0;
						}
					if(nx>=XDotLen){
						continue;
					}
					if(nx+Numb>=XDotLen){
						Numb=XDotLen-nx-1;
					}
					if(Numb<8){
						for(int x=0;x<Numb;x++,nx++){
							p[nx>>3] &= ~(uchar)(0x80>>(nx&7));
							}
						}
					else{
						int k=nx>>3;
						int h=nx&7;
						int len=Numb;
						p[k]&=~(0xFF>>h);
						len-=8-h;
						k++;
						int blen=len>>3;
						for(int t=0;t<blen;t++){
							p[k]=0;
							len-=8;
							k++;
							}
						p[k]&=~(0xFF<<(8-len));
						}
				}
			}
		//}
		if(YDimPoint!=YDim){
			delete	[]YDimPoint;
		}
	}
	else{
		for(int i=0;i<GetFLineLen();i++){
			int	Sy=GetFLineAbsY(i)+my;
			if(Sy<0 || Sy>=YDotLen){
				continue;
			}
			uchar	*p=data[Sy];
			int nx	=GetFLineLeftX(i)+mx;
			int Numb=GetFLineNumb(i);
			if(nx<0){
				Numb+=nx;
				nx=0;
			}
			if(nx>=XDotLen){
				continue;
			}
			if(nx+Numb>=XDotLen){
				Numb=XDotLen-nx-1;
			}
			if(Numb<8){
				for(int x=0;x<Numb;x++,nx++){
					p[nx>>3] &= ~(uchar)(0x80>>(nx&7));
			   }
			}
			else{
				int k=nx>>3;
				int h=nx&7;
				int len=Numb;
				p[k]&=~(0xFF>>h);
				len-=8-h;
				k++;
				int blen=len>>3;
				for(int t=0;t<blen;t++){
					p[k]=0;
					len-=8;
					k++;
				}
				p[k]&=~(0xFF<<(8-len));
			}
		}
	}
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  data
//	  xbyte
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void  FlexArea::MakeMaskBitData(BYTE **data,int DotPerLine, int MaxLines)	const
{
	if(GetFLineLen()>=50){
		struct	FlexAreaYDim	YDim[1000];
		struct	FlexAreaYDim	*YDimPoint;

		if(GetFLineLen()>sizeof(YDim)/sizeof(YDim[0])){
			YDimPoint=new struct FlexAreaYDim[GetFLineLen()];
		}
		else{
			YDimPoint=YDim;
		}
		int	YDimCount=0;
		YDimPoint[0].StartI=0;
		YDimPoint[0].ICount=0;
		for(int i=0;i<GetFLineLen();){
			if(GetFLineAbsY(YDimPoint[YDimCount].StartI)!=GetFLineAbsY(i)){
				YDimCount++;
				YDimPoint[YDimCount].StartI=i;
				YDimPoint[YDimCount].ICount=0;
			}
			else{
				YDimPoint[YDimCount].ICount++;
				i++;
			}
		}
		YDimCount++;

		#pragma omp parallel
		{
			#pragma omp for
			for(int e=0;e<YDimCount;e++){
				for(int t=0;t<YDimPoint[e].ICount;t++){
					int	i=YDimPoint[e].StartI+t;
					if(GetFLineAbsY(i)<0 || GetFLineAbsY(i)>=MaxLines){
						continue;
					}
					uchar	*p=data[GetFLineAbsY(i)];
					int nx	=GetFLineLeftX(i);
					int Numb=GetFLineNumb(i);
					if(nx<0){
						Numb+=nx;
						nx=0;
					}
					if(nx>=DotPerLine){
						continue;
					}
					if(nx+Numb>=DotPerLine){
						Numb=DotPerLine-nx-1;
					}
					if(Numb<8){
						for(int x=0;x<Numb;x++,nx++){
							p[nx>>3] &= ~(uchar)(0x80>>(nx&7));
						}
					}
					else{
						int k=nx>>3;
						int h=nx&7;
						int len=Numb;
						p[k]|=(0xFF>>h);
						len-=8-h;
						k++;
						int blen=len>>3;
						for(int t=0;t<blen;t++){
							p[k]=0;
							len-=8;
							k++;
						}
						p[k]&=~(0xFF<<(8-len));
					}
				}
			}
		}
		if(YDimPoint!=YDim){
			delete	[]YDimPoint;
		}
	}
	else{
		for(int i=0;i<GetFLineLen();i++){
			if(GetFLineAbsY(i)<0 || GetFLineAbsY(i)>=MaxLines){
				continue;
			}
			uchar	*p=data[GetFLineAbsY(i)];
			int nx	=GetFLineLeftX(i);
			int Numb=GetFLineNumb(i);
			if(nx<0){
				Numb+=nx;
				nx=0;
			}
			if(nx>=DotPerLine){
				continue;
			}
			if(nx+Numb>=DotPerLine){
				Numb=DotPerLine-nx-1;
			}
			if(Numb<8){
				for(int x=0;x<Numb;x++,nx++){
					p[nx>>3] &= ~(uchar)(0x80>>(nx&7));
				}
			}
			else{
				int k=nx>>3;
				int h=nx&7;
				int len=Numb;
				p[k]|=(0xFF>>h);
				len-=8-h;
				k++;
				int blen=len>>3;
				for(int t=0;t<blen;t++){
					p[k]=0;
					len-=8;
					k++;
				}
				p[k]&=~(0xFF<<(8-len));
			}
		}
	}
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  data
//	  xbyte
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool  FlexArea::CheckOverlapBit(BYTE *data ,int xbyte,int DotPerLine, int MaxLines)	const
{
	for(int i=0;i<GetFLineLen();i++){
		int Y=GetFLineAbsY(i);
		if(Y<0 || Y>=MaxLines){
			continue;
		}
		uchar	*p= &data[Y*xbyte];
		int nx	=GetFLineLeftX(i);
		int Numb=GetFLineNumb(i);
		if(nx<0){
			Numb-= -nx;
			nx=0;
			}
		if(Numb<=0){
			continue;
		}
		if(nx>DotPerLine){
			continue;
		}
		if(nx+Numb>=DotPerLine){
			Numb=DotPerLine-nx;
		}

		if(Numb<8){
			for(int x=0;x<Numb;x++,nx++){
				if((p[nx>>3] & (uchar)(0x80>>(nx&7)))!=0){
					return(true);
				}
			}
		}
		else{
			int k=nx>>3;
			int h=nx&7;
			int len=Numb;
			if((p[k]&(0xFF>>h))!=0){
				return(true);
			}
			len-=8-h;
			k++;
			int blen=len>>3;
			for(int t=0;t<blen;t++){
				if(p[k]!=0){
					return(true);
				}
				len-=8;
				k++;
			}
			if((p[k]&(0xFF<<(8-len)))!=0){
				return(true);
			}
		}
	}
	return(false);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  data
//	  xbyte
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool  FlexArea::CheckOverlapBit(BYTE **data , int XDot ,int YDot)	const
{
	for(int i=0;i<GetFLineLen();i++){
		int Y=GetFLineAbsY(i);
		if(Y<0 || Y>=YDot){
			continue;
		}
		uchar	*p=data[Y];
		int nx	=GetFLineLeftX(i);
		int Numb=GetFLineNumb(i);
		if(nx<0){
			Numb-= -nx;
			nx=0;
			}
		if(Numb<=0){
			continue;
		}
		if(nx>XDot){
			continue;
		}
		if(nx+Numb>=XDot){
			Numb=XDot-nx;
		}

		if(Numb<8){
			for(int x=0;x<Numb;x++,nx++){
				if((p[nx>>3] & (uchar)(0x80>>(nx&7)))!=0){
					return(true);
				}
			}
		}
		else{
			int k=nx>>3;
			int h=nx&7;
			int len=Numb;
			if((p[k]&(0xFF>>h))!=0){
				return(true);
			}
			len-=8-h;
			k++;
			int blen=len>>3;
			for(int t=0;t<blen;t++){
				if(p[k]!=0){
					return(true);
				}
				len-=8;
				k++;
				}
			if((p[k]&(0xFF<<(8-len)))!=0){
				return(true);
			}
		}
	}
	return(false);
}



/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  data
//	  PBuff
//	  xbyte
//	  YLen
//	  dx
//	  dy
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::CopyPattern(uchar *data,ImageBuffer &PBuff, int YLen ,int DotPerLine, int MaxLines ,int dx ,int dy)
{
	for(int i=0;i<GetFLineLen();i++){
		int y=GetFLineAbsY(i)+dy;
		if(y<0 || y>=YLen){
			data+=GetFLineNumb(i);
			continue;
			}
		int x1=GetFLineLeftX(i)+dx;
		int Lx=0;
		if(x1<0){
			Lx= -x1;
			x1=0;
		}
		int x2=GetFLineRightX(i)+dx;
		if(x2>=DotPerLine){
			x2=DotPerLine;
		}
		if(x1<DotPerLine){
			uchar	*p=PBuff.GetY(y)+x1;
			memcpy(data,p,x2-x1);
			}
		data+=GetFLineNumb(i);
	}
}

void	 FlexArea::CopyPartial(ImageBuffer &Dst,ImageBuffer &Src, int dx ,int dy)
{
	if(GetFLineLen()==0){
		return;
	}

	for(int i=0;i<GetFLineLen();i++){
		int y=GetFLineAbsY(i);
		int DstY=y+dy;
		if(DstY<0 || DstY>=Dst.GetHeight()){
			continue;
			}
		int x1=GetFLineLeftX(i);
		int x2=GetFLineRightX(i);
		int DstX1=x1+dx;
		int DstX2=x2+dx;
		if(DstX1<0){
			DstX2+=DstX1;
			DstX1=0;
			}
		if(DstX2>=Dst.GetWidth()){
			DstX2=Dst.GetWidth();
		}
		if(DstX1>=Dst.GetWidth()){
			DstX1=Dst.GetWidth();
		}
		int len=DstX2-DstX1;
		if(len<=0){
			continue;
		}
	}
	Dst.SetChanged();
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  XY
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::MakeOutlineDot(XYClassCluster &XY)
{
	if(GetFLineLen()==0)
		return;

	BYTE	*Dummy=new BYTE[GetFLineLen()];
	for(int i=0;i<GetFLineLen();i++){
		Dummy[i]=0;
		}
	XY.RemoveAll();

	for(;;){
		int i;
		for(i=0;i<GetFLineLen();i++){
			if((Dummy[i] & 0x01)==0){
				break;
			}
		}
		if(i>=GetFLineLen()){
			delete	[]Dummy;
			return;
			}
		XYClassArea *w=new XYClassArea();
		if(PickOutlineDot(w,i,Dummy)==true){
			w->Regulate();
			XY.AppendList(w);
		}
		else{
			delete	w;
		}
	}
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  w
//	  startn
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/

bool	  FlexArea::PickOutlineDot(XYClassArea *w ,int startn ,BYTE *Dummy)
//左回りで輪郭を捉える
{
	int n=startn;
	int direc=0;
	int i;
	int NowX;
	struct	POInner{
		int direc;
		int n;
		};
	static	int Error;

	for(;;){

		if(direc==0){
			//左側の伝道
			//左側のとき、必ず下向きに探索
			if((Dummy[n] & 0x01)!=0){
				return(false);
			}
			Dummy[n] |= 0x01;
			for(i=n+1;i<GetFLineLen();i++){
				if(GetFLineAbsY(i)==GetFLineAbsY(n)+1){
					if(GetFLineRightX(n)<GetFLineLeftX(i)
					|| GetFLineRightX(i)<GetFLineLeftX(n)){
						continue;
					}
					break;
				}
			}
			if(i<GetFLineLen()){
				if(GetFLineLeftX(i)<GetFLineLeftX(n)){
					XYClass *a=new XYClass(GetFLineLeftX(n),GetFLineAbsY(n));
					w->AppendList(a);
					NowX=GetFLineLeftX(n);
					n=i;
					direc=1;
					}
				else{
					for(int x=GetFLineLeftX(n);x<=GetFLineLeftX(i);x++){
						XYClass *a=new XYClass(x,GetFLineAbsY(n));
						w->AppendList(a);
						NowX=x;
						}
					n=i;
					direc=0;
					}
				}
			else{
				for(int x=GetFLineLeftX(n);x<=GetFLineRightX(n);x++){
					XYClass *a=new XYClass(x,GetFLineAbsY(n));
					w->AppendList(a);
					NowX=x;
					}
				direc=2;
				}
			}
		else if(direc==1){
			//上側の伝道
			//上側のとき、必ず左向きに探索
			//if((FLines[n].Dummy & 0x02)!=0)
			//	  return(false);
			Dummy[n] |= 0x02;
			int k= -1;
			for(i=n-1;i>=0;i--){
			//for(i=0;i<n;i++){
				if(GetFLineAbsY(i)==GetFLineAbsY(n)-1){
					if(GetFLineRightX(i)>=GetFLineLeftX(n)
					&& GetFLineRightX(i)<=NowX){
						if(k==-1 || GetFLineRightX(n)<GetFLineRightX(i)){
							k=i;
						}
					}
				}
			}
			if(i<0){
				i=n;
			}
			if(k!=-1){
				i=k;
				for(int x=NowX;x>=GetFLineRightX(i);x--){
					XYClass *a=new XYClass(x,GetFLineAbsY(n));
					w->AppendList(a);
					NowX=x;
					}
				if(NowX==GetFLineLeftX(n)){
					Dummy[n] |= 0x01;
				}
				n=i;
				direc=2;
			}
			else{
				for(int x=NowX;x>=GetFLineLeftX(n);x--){
					XYClass *a=new XYClass(x,GetFLineAbsY(n));
					w->AppendList(a);
					NowX=x;
					}
				n=i;
				direc=0;
				}
			}
		else if(direc==2){
			//右側の伝道
			//右側のとき、必ず上向きに探索
	//		if((Dummy[n] & 0x04)!=0){
	//			return(false);
	//		}
			Dummy[n] |= 0x04;
			int k= -1;
			for(i=0;i<n;i++){
				if(GetFLineAbsY(i)==GetFLineAbsY(n)-1){
					if(GetFLineRightX(n)<GetFLineLeftX(i)
					|| GetFLineRightX(i)<GetFLineLeftX(n)){
						continue;
					}
					k=i;
				}
			}
			if(k!=-1){
				i=k;
				if(GetFLineAbsY(n)==GetFLineAbsY(startn)
				&& (GetFLineRightX(n)==GetFLineLeftX(startn)
				 || GetFLineRightX(n)==GetFLineLeftX(startn)+1)){
					return(true);
					}

				if(GetFLineRightX(n)>GetFLineRightX(i)){
					for(int x=GetFLineRightX(n);x>=GetFLineRightX(i);x--){
						XYClass *a=new XYClass(x,GetFLineAbsY(n));
						w->AppendList(a);
						NowX=x;
						}
					n=i;
					direc=2;
					}
				else{
					for(int x=GetFLineRightX(n);x<=GetFLineRightX(i);x++){
						for(int j=n+1;j<GetFLineLen() && GetFLineAbsY(j)<=GetFLineAbsY(n)+1;j++){
							if(GetFLineAbsY(j)==GetFLineAbsY(n)){
								continue;
							}
							if(x==GetFLineLeftX(j) && (Dummy[j]&0x01)==0){
								n=j;
								direc=0;
								goto	MM2;
								}
							}
						XYClass *a=new XYClass(x,GetFLineAbsY(n));
						w->AppendList(a);
						NowX=x;
						if(GetFLineAbsY(n)==GetFLineAbsY(startn)
						&& (x==GetFLineLeftX(startn)
						 || x==GetFLineLeftX(startn)+1)){
							return(true);
							}
						}
					if(i+1<GetFLineLen()
					&& GetFLineAbsY(i)==GetFLineAbsY(i+1)
					&& (GetFLineRightX(i)+1)>=GetFLineLeftX(i+1)
					&& (Dummy[i+1]&0x01)==0){
						n=i+1;
						direc=0;
						}
					else{
						n=i;
						direc=2;
						}
					MM2:;
					}
				}
			else{
				for(int x=GetFLineRightX(n);x>=GetFLineLeftX(n);x--){
					XYClass *a=new XYClass(x,GetFLineAbsY(n));
					w->AppendList(a);
					NowX=x;
					}
				direc=0;
				}
			}
		else if(direc==3){
			//下側の伝道
			//下側のとき、必ず右向きに探索
			Dummy[n] |= 0x08;
			}
		if(direc==0 && n==startn){
			return(true);
		}
	}
}

void	 FlexArea::BindArea(void)
{
	for(int i=0;i<GetFLineLen()-1;){
		if(GetFLineAbsY(i)==GetFLineAbsY(i+1)
		&& GetFLineRightX(i)>=GetFLineLeftX(i+1)){
			struct FlexLine *FL=new struct FlexLine[GetFLineLen()-1];
			int Ln=0;
			int LastY= -1;
			int	LastRight= -1;
			int	LastLeft= -1;

			for(int k=0;k<GetFLineLen();){
				if(LastY!=GetFLineAbsY(k)
				|| LastRight<GetFLineLeftX(k)){
					LastY=GetFLineAbsY(k);
					LastRight=GetFLineRightX(k);
					LastLeft =GetFLineLeftX(k) ;
					GetFlexLine(k,FL[Ln]);
					Ln++;
					k++;
					}
				else{
					while(LastY==GetFLineAbsY(k)
					&& LastRight>=GetFLineLeftX(k)){
						LastRight=GetFLineRightX(k);
						k++;
						if(k>=GetFLineLen()){
							break;
						}
					}
					FL[Ln-1].SetNumb(LastRight-FL[Ln-1]._GetLeftX());
				}
			}
			SetFLine(FL,Ln);
			break;
		}
		else{
			i++;
		}
	}
}
/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  Left
//	  Top
//	  Right
//	  Bottom
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::ClipArea(int Left ,int Top ,int Right ,int Bottom)
{
	bool	Clipable=false;
	for(int i=0;i<GetFLineLen();i++){
		if(GetFLineAbsY(i)<Top || Bottom<=GetFLineAbsY(i)){
			Clipable=true;
			break;
			}
		else if(GetFLineRightX(i)<Left || Right<=GetFLineLeftX(i)){
			Clipable=true;
			break;
			}
		else if(GetFLineNumb(i)<=0){
			Clipable=true;
			break;
			}
		else if(GetFLineLeftX(i)<Left){
			Clipable=true;
			break;
			}
		else if(Right<GetFLineRightX(i)){
			Clipable=true;
			break;
			}
		}

	if(Clipable==true){
		struct	FlexLine	*FL=GetFLinePoint();	//new struct	FlexLine[GetFLineLen()];
		int Ln=0;
		for(int i=0;i<GetFLineLen();i++){
			int y=GetFLineAbsY(i);
			if(Top<=y && y<=Bottom){
				int x1=GetFLineLeftX(i);
				int x2=GetFLineRightX(i);
				if(x1<Left){
					x1=Left;
				}
				if(x2>Right){
					x2=Right;
				}
				if(x1<=x2){
					FL[Ln]._SetAbsY (y -GetFLineAddY());
					FL[Ln]._SetLeftX(x1-GetFLineAddX());
					FL[Ln].SetNumb(x2-x1);
					Ln++;
				}
			}
		}

		//SetFLine(FL,Ln);
		ShrinkLen(Ln);
		Regulate();
	}
}

void    FlexArea::ClipArea(FlexArea &BoundArea)
{
	int	N=GetFLineLen()+BoundArea.GetFLineLen();
	struct	FlexLine	*FL=new struct	FlexLine[N];
	int	TopI=-1;
	for(int i=0;i<GetFLineLen();i++){
		int y=GetFLineAbsY(i);
		if(BoundArea.GetMinY()<=y && y<=BoundArea.GetMaxY()){
			TopI=i;
			break;
		}
	}
	if(TopI==-1){
		delete	[]FL;
		return;
	}
	int	TopB=-1;
	for(int i=0;i<BoundArea.GetFLineLen();i++){
		if(GetFLineAbsY(TopI)==BoundArea.GetFLineAbsY(i)){
			TopB=i;
			break;
		}
	}
	if(TopB==-1){
		delete	[]FL;
		return;
	}

	int	KNumb=0;
	for(int i=TopI;i<GetFLineLen();i++){
		int y=GetFLineAbsY(i);
		int x1=GetFLineLeftX(i);
		int x2=GetFLineRightX(i);
		if(y!=BoundArea.GetFLineAbsY(TopB)){
			for(int j=TopB+1;j<BoundArea.GetFLineLen();j++){
				if(BoundArea.GetFLineAbsY(j)==y){
					TopB=j;
					break;
				}
			}
		}
		if(y!=BoundArea.GetFLineAbsY(TopB)){
			break;
		}
		for(int j=TopB;j<BoundArea.GetFLineLen() && BoundArea.GetFLineAbsY(j)==y;j++){
			int hx1=BoundArea.GetFLineLeftX(j);
			int hx2=BoundArea.GetFLineRightX(j);
			if(hx2<x1)
				continue;
			else if(hx1<=x1 && x1<=hx2 && hx2<=x2){
				FL[KNumb]._SetAbsY(y);
				FL[KNumb]._SetLeftX(x1);
				FL[KNumb].SetNumb(hx2-x1);
				if(FL[KNumb].GetNumb()>0){
					KNumb++;
				}
				x1=hx2+1;
			}
			else if(x1<=hx1 && hx2<=x2){
				FL[KNumb]._SetAbsY(y);
				FL[KNumb]._SetLeftX(hx1);
				FL[KNumb].SetNumb(hx2-hx1);
				if(FL[KNumb].GetNumb()>0){
					KNumb++;
				}
				x1=hx2+1;
			}
			else if(hx1<=x1 && x2<=hx2){
				FL[KNumb]._SetAbsY(y);
				FL[KNumb]._SetLeftX(x1);
				FL[KNumb].SetNumb(x2-x1);
				if(FL[KNumb].GetNumb()>0){
					KNumb++;
				}
				x1=x2+1;
			}
			else if(x1<=hx1 && hx1<=x2 && x2<=hx2){
				FL[KNumb]._SetAbsY(y);
				FL[KNumb]._SetLeftX(hx1);
				FL[KNumb].SetNumb(x2-hx1);
				if(FL[KNumb].GetNumb()>0){
					KNumb++;
				}
				x1=x2+1;
			}
			else if(x2<hx1){
				break;
			}
			if(x2<x1){
				break;
			}
		}
	}
	SetFLine(FL,KNumb);
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  a
//	  b
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
static	int  NearByFunc(const void *a ,const void *b)
{
	return(((struct FlexLine *)a)->_GetAbsY() - ((struct FlexLine *)b)->_GetAbsY() );
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  L
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	  FlexArea::NearBy(struct FlexLine &L)
{
	int px1=L._GetLeftX(this);
	int px2=L._GetRightX(this);
	struct FlexLine LL;
	LL._SetLeftX(this,L._GetLeftX());
	LL._SetAbsY (this,L._GetAbsY ());

	struct FlexLine *src=(struct FlexLine *)EqualSearch(&LL,GetFLinePoint(),GetFLineLen(),sizeof(LL),NearByFunc);
	if(src==NULL){
		return(false);
	}
	int N=src-GetFLinePoint();
	for(int i=N;i<GetFLineLen();i++){
		if(GetFLineAbsY(i)-1==L._GetAbsY(this)
		|| GetFLineAbsY(i)	==L._GetAbsY(this)){
			int kx1=GetFLineLeftX(i);
			int kx2=GetFLineRightX(i);
			if(kx1-1<=px1 && px1<=kx2+1){
				return(true);
			}
			if(kx1-1<=px2 && px2<=kx2+1){
				return(true);
			}
			if(px1-1<=kx1 && kx1<=px2+1){
				return(true);
			}
			if(px1-1<=kx2 && kx2<=px2+1){
				return(true);
			}
			}
		else{
			break;
		}
	}
	for(int i=N-1;i>=0;i--){
		if(GetFLineAbsY(i)	==L._GetAbsY()
		|| GetFLineAbsY(i)+1==L._GetAbsY()){
			int kx1=GetFLineLeftX(i);
			int kx2=GetFLineRightX(i);
			if(kx1-1<=px1 && px1<=kx2+1){
				return(true);
			}
			if(kx1-1<=px2 && px2<=kx2+1){
				return(true);
			}
			if(px1-1<=kx1 && kx1<=px2+1){
				return(true);
			}
			if(px1-1<=kx2 && kx2<=px2+1){
				return(true);
			}
		}
		else{
			break;
		}
	}

	return(false);
}
/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  food
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::EatArea(const FlexArea *food)
{
	struct FlexLine *tmp=new struct FlexLine[GetFLineLen()+food->GetFLineLen()];
	DirectCopyTo(tmp,GetFLineLen());

	int mLen=GetFLineLen();
	for(int i=0;i<food->GetFLineLen();i++){
		int dY =food->GetFLineAbsY(i);
		int dx1=food->GetFLineLeftX(i);
		int dx2=food->GetFLineRightX(i);
		int j;
		struct FlexLine *src=tmp;
		for(j=0;j<mLen;j++,src++){
			if(tmp[j]._GetAbsY()==dY){
				int mx1=src->_GetLeftX();
				int mx2=src->_GetRightX();
				if(mx1-1<=dx1 && dx1<=mx2+1){
					if(mx2<dx2){
						mx2=dx2;
						src->SetNumb(dx2-src->_GetLeftX());
						}
					break;
					}
				else if(mx1-1<=dx2 && dx2<=mx2+1){
					if(dx1<mx1){
						mx1=dx1;
						src->_SetLeftX (dx1);
						src-> SetNumb  (mx2-src->_GetLeftX());
						}
					break;
					}
				}
			}
		if(j>=mLen){
			food->GetFlexLine(i,*src);
			mLen++;
			}
		}
	QSort(tmp,mLen,sizeof(tmp[0]),YSortFunc);
	SetFLine(tmp,mLen);
}

void	  FlexArea::SetFLineFromDirty(struct FlexLine *Src, int SrcLen)
{
	QSort(Src,SrcLen,sizeof(Src[0]),YSortFunc);
	struct FlexLine *Tmp=new struct FlexLine[SrcLen];
	int	TmpLen=0;
	if(SrcLen!=0){
		Tmp[0]=Src[0];
		TmpLen++;
	}
	for(int i=1;i<SrcLen;i++){
		if(Tmp[TmpLen-1]._GetAbsY()!=Src[i]._GetAbsY()){
			Tmp[TmpLen]=Src[i];
			TmpLen++;
		}
		else{
			if(Tmp[TmpLen-1]._GetRightX()>=(Src[i]._GetLeftX()-1)){
				if(Tmp[TmpLen-1]._GetRightX()<Src[i]._GetRightX()){
					Tmp[TmpLen-1].SetNumb(Src[i]._GetRightX()-Tmp[TmpLen-1]._GetLeftX());
				}
			}
			else{
				Tmp[TmpLen]=Src[i];
				TmpLen++;
			}
		}
	}
	if(SrcLen/2>TmpLen){
		struct FlexLine *Tmp2=new struct FlexLine[TmpLen];
		memcpy(Tmp2,Tmp,sizeof(Tmp[0])*TmpLen);
		delete	[]Tmp;
		SetFLine(Tmp2,TmpLen);
	}
	else{
		SetFLine(Tmp,TmpLen);
	}
}

class	FlexLineStack
{
public:
	struct	 FlexLine	*Data;
	int		AllocNumb;
	int		Len;

	explicit	FlexLineStack(void);
	~FlexLineStack(void);

	void	Push(int x1, int x2 ,int y);
};

FlexLineStack::FlexLineStack(void)
{
	AllocNumb=100;
	Data=new struct FlexLine[AllocNumb];
	Len=0;
}
FlexLineStack::~FlexLineStack(void)
{
	if(Data!=NULL){
		delete	[]Data;
	}
	Data=NULL;
}
void	FlexLineStack::Push(int x1, int x2 ,int y)
{
	if(Len>=AllocNumb){
		int	NewAllocNumb=AllocNumb+AllocNumb/2;
		struct	 FlexLine	*TmpData=new struct FlexLine[NewAllocNumb];
		memcpy(TmpData,Data,sizeof(Data[0])*AllocNumb);
		AllocNumb=NewAllocNumb;
		delete	[]Data;
		Data=TmpData;
	}
	Data[Len]._SetAbsY(y);
	Data[Len]._SetLeftX(x1);
	Data[Len].SetNumb(x2-x1);
	Len++;
}

struct	IndexYStruct
{
	int		Point;
	int		AbsY;
	int		CountOfSameY;
};

static	void	RecursiveClusterize(NPListPack<FlexLineList> &FlexLineContainer,FlexLineList *Current,NPListPack<FlexLineList> &DestFlex)
{
	int	Y=Current->y;
	FirstStep:;
	for(FlexLineList *a=FlexLineContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->y==Y){
			for(FlexLineList *h=a;h!=NULL;h=h->GetNext()){
				if((Current->x1<=h->x1 && h->x1 <=(Current->x2+1))
				|| (Current->x1<=(h->x2+1) && h->x2 <=(Current->x2+1))
				|| (h->x1<=Current->x1 && Current->x2<=h->x2)){
					FlexLineContainer.RemoveList(h);
					DestFlex.AppendList(h);
					RecursiveClusterize(FlexLineContainer,h,DestFlex);
					goto	FirstStep;
				}
			}
		}
	}
	for(FlexLineList *a=FlexLineContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->y==(Y+1)){
			for(FlexLineList *h=a;h!=NULL;h=h->GetNext()){
				if((Current->x1<=h->x1 && h->x1 <=(Current->x2+1))
				|| (Current->x1<=(h->x2+1) && h->x2 <=(Current->x2+1))
				|| (h->x1<=Current->x1 && Current->x2<=h->x2)){
					FlexLineContainer.RemoveList(h);
					DestFlex.AppendList(h);
					RecursiveClusterize(FlexLineContainer,h,DestFlex);
					goto	FirstStep;
				}
			}
		}
	}
	for(FlexLineList *a=FlexLineContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->y==(Y-1)){
			for(FlexLineList *h=a;h!=NULL;h=h->GetNext()){
				if((Current->x1<=h->x1 && h->x1 <=(Current->x2+1))
				|| (Current->x1<=(h->x2+1) && h->x2 <=(Current->x2+1))
				|| (h->x1<=Current->x1 && Current->x2<=h->x2)){
					FlexLineContainer.RemoveList(h);
					DestFlex.AppendList(h);
					RecursiveClusterize(FlexLineContainer,h,DestFlex);
					goto	FirstStep;
				}
			}
		}
	}
}

static	void	RecursiveClusterizePickup(NPListPack<FlexLineList> &FlexLineContainer,NPListPack<FlexLineList> &Current ,NPListPack<FlexLineList> &NewContainer)
{
	for(FlexLineList *c=Current.GetFirst();c!=NULL;c=c->GetNext()){
		for(FlexLineList *a=FlexLineContainer.GetFirst();a!=NULL;){
			FlexLineList *NextA=a->GetNext();
			if((a->y==c->y) || (a->y==(c->y+1)) || (a->y==(c->y-1))){
				if((c->x1<=a->x1 && a->x1 <=(c->x2+1))
				|| (c->x1<=(a->x2+1) && a->x2 <=(c->x2+1))
				|| (a->x1<=c->x1 && c->x2<=a->x2)){
					FlexLineContainer.RemoveList(a);
					NewContainer.AppendList(a);
				}
			}
			if(a->y>(c->y+1))
				break;
			a=NextA;
		}
	}
}
static	void	RecursiveClusterizePickup(NPListPack<FlexLineList> &FlexLineContainer,FlexLineList *CurrentFirst ,NPListPack<FlexLineList> &NewContainer)
{
	for(FlexLineList *c=CurrentFirst;c!=NULL;c=c->GetNext()){
		for(FlexLineList *a=FlexLineContainer.GetFirst();a!=NULL;){
			FlexLineList *NextA=a->GetNext();
			if((a->y==c->y) || (a->y==(c->y+1)) || (a->y==(c->y-1))){
				if((c->x1<=a->x1 && a->x1 <=(c->x2+1))
				|| (c->x1<=(a->x2+1) && a->x2 <=(c->x2+1))
				|| (a->x1<=c->x1 && c->x2<=a->x2)){
					FlexLineContainer.RemoveList(a);
					NewContainer.AppendList(a);
				}
			}
			if(a->y>(c->y+1))
				break;
			a=NextA;
		}
	}
}

static	void	RecursiveClusterize(NPListPack<FlexLineList> &FlexLineContainer,NPListPack<FlexLineList> &Current,NPListPack<FlexLineList> &DestFlex)
{
	/*
	NPListPack<FlexLineList> NewContainer;
	RecursiveClusterizePickup(FlexLineContainer,Current ,NewContainer);

	if(NewContainer.GetCount()>0){
		RecursiveClusterize(FlexLineContainer,NewContainer,DestFlex);
		DestFlex.AddMove(NewContainer);
	}
	*/
	FlexLineList *CurrentFirst=Current.GetFirst();
	bool	LoopFlag;
	do{
		LoopFlag=false;
		NPListPack<FlexLineList> NewContainer;
		RecursiveClusterizePickup(FlexLineContainer,CurrentFirst ,NewContainer);

		if(NewContainer.GetCount()>0){
			CurrentFirst=NewContainer.GetFirst();
			DestFlex.AddMove(NewContainer);
			LoopFlag=true;
		}
	}while(LoopFlag==true);

}


void	FlexArea::Clusterize(PureFlexAreaListContainer &Piece)
{
	int	N=GetFLineLen();
	if(N==0)
		return;

	//_heapchk();

	NPListPack<FlexLineList>	FlexLineContainer;
	FlexLineList	FlexLineListDim[8192];
	FlexLineList	*FlexLineListPoint;
	if(N<8192){
		FlexLineListPoint=FlexLineListDim;
	}
	else{
		FlexLineListPoint=new FlexLineList[N];
	}

	for(int i=0;i<N;i++){
		FlexLineList	*d=&FlexLineListPoint[i];
		d->Set(GetFLineLeftX(i),GetFLineRightX(i),GetFLineAbsY(i));
		FlexLineContainer.AppendList(d);
	}
	//_heapchk();
	FlexLineList	*L;
	while((L=FlexLineContainer.GetFirst())!=NULL){
		FlexLineContainer.RemoveList(L);

		NPListPack<FlexLineList>	DestFlex;
		{
			NPListPack<FlexLineList>	Current;
			Current.AppendList(L);

			for(FlexLineList *a=FlexLineContainer.GetFirst();a!=NULL;){
				FlexLineList *NextA=a->GetNext();
				int	Ly=L->y;
				if((a->y==L->y) || (a->y==(L->y+1)) || (a->y==(L->y-1))){
					if((L->x1<=a->x1 && a->x1 <=(L->x2+1))
					|| (L->x1<=(a->x2+1) && a->x2 <=(L->x2+1))
					|| (a->x1<=L->x1 && L->x2<=a->x2)){
						FlexLineContainer.RemoveList(a);
						Current.AppendList(a);
						L=a;
					}
				}
				if(a->y>(Ly+1))
					break;
				a=NextA;
			}
			RecursiveClusterize(FlexLineContainer,Current,DestFlex);
			DestFlex.AddMove(Current);
		}

		int	Len=DestFlex.GetCount();
		if(Len>0){
			struct  FlexLine	*FL=new struct  FlexLine[Len];
			int	k=0;
			FlexLineList *a;
			while((a=DestFlex.GetFirst())!=NULL){
				DestFlex.RemoveList(a);
				FL[k]._Set(a->x1,a->x2,a->y);
				k++;
			}
			PureFlexAreaList	*P=new PureFlexAreaList();
			P->SetFLine(FL,Len);
			P->Regulate();
			Piece.AppendList(P);
			//_heapchk();
		}
	}
	if(FlexLineListPoint!=FlexLineListDim){
		delete	[]FlexLineListPoint;
	}
	//_heapchk();
}

bool	FlexArea::ChopRect(PureFlexAreaListContainer &Piece ,int ChopSize)
{
	if(ChopSize<=0){
		return false;
	}
	int	XNumb=(GetWidth ()+ChopSize-1)/ChopSize;
	int	YNumb=(GetHeight()+ChopSize-1)/ChopSize;

	FlexLineStack	**PDim=new FlexLineStack*[YNumb];
	for(int y=0;y<YNumb;y++){
		PDim[y]=new FlexLineStack[XNumb];
	}
	int	X1=GetMinX();
	int	Y1=GetMinY();

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX(i);
		int x2=GetFLineRightX(i);
		int y =GetFLineAbsY(i);
		int	yn=(y-Y1)/ChopSize;
		int	x1n=(x1-X1)/ChopSize;
		int	x2n=(x2-X1)/ChopSize;
		int	px1,px2;
		if(0<=yn && yn<YNumb){
			if(x1n<0){
				x1n=0;
			}
			if(x1n>=XNumb){
				x1n=XNumb-1;
			}
			if(x2n<0){
				x2n=0;
			}
			if(x2n>=XNumb){
				x2n=XNumb-1;
			}

			for(int xn=x1n;xn<=x2n && xn<XNumb;xn++){
				if(xn==x1n){
					px1=x1;
				}
				else{
					px1=xn*ChopSize+X1;
				}
				if(xn==x2n){
					px2=x2;
				}
				else{
					px2=(xn+1)*ChopSize+X1;
				}
				PDim[yn][xn].Push(px1,px2,y);
			}
		}
	}
	if(YNumb*XNumb>200){
		int	n=YNumb*XNumb;
		XYClass	*xy=new XYClass[n];
		int	t=0;
		for(int yn=0;yn<YNumb;yn++){
			for(int xn=0;xn<XNumb;xn++){
				xy[t].x=xn;
				xy[t].y=yn;
				t++;
			}
		}

		//Inpossible for OpenMP
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<n;i++){
				int xn=xy[i].x;
				int yn=xy[i].y;
				if(PDim[yn][xn].Len>0){
					FlexArea	p;
					p.SetFLine(PDim[yn][xn].Data ,PDim[yn][xn].Len);
					PDim[yn][xn].Data=NULL;
					p.Regulate();

					PureFlexAreaListContainer Slices;
					p.Clusterize(Slices);
					#pragma omp critical
					{
						Piece.AddMove(Slices);
					}
				}
			}
		}
		delete	[]xy;
	}
	else{
		for(int yn=0;yn<YNumb;yn++){
			for(int xn=0;xn<XNumb;xn++){
				if(PDim[yn][xn].Len>0){
					FlexArea	p;
					p.SetFLine(PDim[yn][xn].Data ,PDim[yn][xn].Len);
					PDim[yn][xn].Data=NULL;
					p.Regulate();
					PureFlexAreaListContainer Slices;
					p.Clusterize(Slices);
					Piece.AddMove(Slices);
				}
			}
		}
	}
	for(int y=0;y<YNumb;y++){
		delete	[]PDim[y];
	}
	delete	[]PDim;
	return true;
}


bool	FlexArea::ChopRect(PureFlexAreaListContainer &Piece,int ChopSize,int OverlapSize)
{
	int	SlideLen=ChopSize-OverlapSize;
	if(SlideLen<=0)
		return false;
	int	XNumb=(GetWidth()+SlideLen-1)/SlideLen;
	int	YNumb=(GetHeight()+SlideLen-1)/SlideLen;

	FlexLineStack **PDim=new FlexLineStack*[YNumb];
	for(int y=0;y<YNumb;y++){
		PDim[y]=new FlexLineStack[XNumb];
	}
	int	X1=GetMinX();
	int	Y1=GetMinY();

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX(i);
		int x2=GetFLineRightX(i);
		int y=GetFLineAbsY(i);

		int	yn2=min(YNumb,(y-Y1)/SlideLen);
		for(int yn=max(0,((y-Y1)-ChopSize-1)/SlideLen);yn<yn2;yn++){
			for(int xn=0;xn<XNumb;xn++){
				int	xn1=xn*SlideLen+X1;
				int	xn2=xn1+ChopSize;
				if(xn1<=x1 && x1<=xn2){
					xn1=x1;
					xn2=min(xn2,x2);
				}
				else
				if(x1<=xn1 && xn1<x2){
					xn2=min(xn2,x2);
				}
				else{
					continue;
				}
				PDim[yn][xn].Push(xn1,xn2,y);
			}
		}
	}
	if(YNumb*XNumb>200){
		int	n=YNumb*XNumb;
		XYClass *xy=new XYClass[n];
		int	t=0;
		for(int yn=0;yn<YNumb;yn++){
			for(int xn=0;xn<XNumb;xn++){
				xy[t].x=xn;
				xy[t].y=yn;
				t++;
			}
		}

		//Inpossible for OpenMP
#pragma omp parallel
		{
#pragma omp for
			for(int i=0;i<n;i++){
				int xn=xy[i].x;
				int yn=xy[i].y;
				if(PDim[yn][xn].Len>0){
					FlexArea	p;
					p.SetFLine(PDim[yn][xn].Data,PDim[yn][xn].Len);
					PDim[yn][xn].Data=NULL;
					p.Regulate();

					PureFlexAreaListContainer Slices;
					p.Clusterize(Slices);
#pragma omp critical
					{
						Piece.AddMove(Slices);
					}
				}
			}
		}
		delete[]xy;
	}
	else{
		for(int yn=0;yn<YNumb;yn++){
			for(int xn=0;xn<XNumb;xn++){
				if(PDim[yn][xn].Len>0){
					FlexArea	p;
					p.SetFLine(PDim[yn][xn].Data,PDim[yn][xn].Len);
					PDim[yn][xn].Data=NULL;
					p.Regulate();
					PureFlexAreaListContainer Slices;
					p.Clusterize(Slices);
					Piece.AddMove(Slices);
				}
			}
		}
	}
	for(int y=0;y<YNumb;y++){
		delete[]PDim[y];
	}
	delete[]PDim;
	return true;
}
/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	 FlexArea::Restruct(void)
{
	struct	FlexLine	*FL=new struct	FlexLine[GetFLineLen()];
	DirectCopyTo(FL,GetFLineLen());
	int mLen=GetFLineLen();
	struct	FlexLine	*src=FL;

	for(int i=0;i<mLen;i++,src++){
		int Y  =src->_GetAbsY();
		int mx1=src->_GetLeftX();
		int mx2=src->_GetRightX();
		struct	FlexLine	*dst= &FL[i+1];
		for(int j=i+1;j<mLen;){
			if(Y==dst->_GetAbsY()){
				int nx1=dst->_GetLeftX();
				int nx2=dst->_GetRightX();
				if(mx1-1<=nx1 && nx1<=mx2+1){
					if(mx2<nx2){
						src->SetNumb(nx2-src->_GetLeftX());
						mx2=nx2;
						}
					memmove(&FL[j],&FL[j+1],(mLen-j-1)*sizeof(FL[0]));
					mLen--;
					}
				else if(mx1-1<=nx2 && nx2<=mx2+1){
					if(nx1<mx1){
						src->_SetLeftX(nx1);
						src-> SetNumb (mx2-src->_GetLeftX());
						mx1=nx1;
						}
					memmove(&FL[j],&FL[j+1],(mLen-j-1)*sizeof(FL[0]));
					mLen--;
					}
				else{
					j++;
					dst++;
					}
				}
			else{
				j++;
				dst++;
				}
			}
		}
	SetFLine(FL,mLen);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  b
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	  FlexArea::IsInclude(const FlexArea *b)const
{
	if(GetMinX()<=b->GetMinX() && b->GetMaxX()<=GetMaxX()
	&& GetMinY()<=b->GetMinY() && b->GetMaxY()<=GetMaxY()){
		for(int i=0;i<b->GetFLineLen();i++){
			int Y  =b->GetFLineAbsY(i);
			int mx1=b->GetFLineLeftX(i);
			int mx2=b->GetFLineRightX(i);
			int j;
			for(j=0;j<GetFLineLen();j++){
				if(GetFLineAbsY(j)==Y
					&& GetFLineLeftX(j)<=mx1 && mx2<=GetFLineRightX(j)){
					break;
				}
			}
			if(j>=GetFLineLen()){
				return(false);
			}
		}
		return(true);
	}
	return(false);
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  dx
//	  dy
//	  src
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考void	 ClusterizeLocal(FlexArea *parent ,int index1 ,int index2 ,NPListPack<IntClass> &PathIndex)
//
/*----------------------------------------------------------------------------*/
int 	  FlexArea::GetSumColor(int dx,int dy,ImageBuffer &src 
								,int xdotperline ,int ymaxlines)	const
{
	int D=0;

	struct	 FlexLine	*FL=GetFLinePoint();
	for(int i=0;i<GetFLineLen();i++,FL++){
		int Y=FL->_GetAbsY(this) +dy;
		if(Y<0 || Y>=ymaxlines){
			continue;
		}
		int X=FL->_GetLeftX(this)+dx;
		int N=FL->GetNumb ();
		if(X<0){
			N-= -X;
			X=0;
			}
		if(N<=0){
			continue;
		}
		if(X>xdotperline){
			continue;
		}
		if(X+N>=xdotperline){
			N=xdotperline-X;
		}
		BYTE	*p=src.GetY(Y)+X;

		for(int j=0;j<N;j++){
			D+= p[j];
		}		
	}
	return(D);
}

int 	  FlexArea::GetSumColorSep4(int dx,int dy,ImageBuffer &src 
									,int xdotperline ,int ymaxlines)	const
{
	int D=0;

	struct	 FlexLine	*FL=GetFLinePoint();
	for(int i=0;i<GetFLineLen();i++,FL++){
		int Y=FL->_GetAbsY(this) +dy;
		if((Y&1)==0)
			continue;
		if(Y<0 || Y>=ymaxlines){
			continue;
		}
		int X=FL->_GetLeftX(this)+dx;
		int N=FL->GetNumb ();
		if(X<0){
			N-= -X;
			X=0;
			}
		if(N<=0){
			continue;
		}
		if(X>xdotperline){
			continue;
		}
		if(X+N>=xdotperline){
			N=xdotperline-X;
		}
		BYTE	*p=src.GetY(Y)+X;

		for(int j=0;j<N;j+=2){
			D+= p[j];
		}		
	}
	return(D);
}


void	   FlexArea::GetLowHightColor(int dx,int dy,ImageBuffer &src,int &LColor ,int &HColor ,int xdotperline ,int ymaxlines)
{
	LColor=256;
	HColor=0;

	struct	 FlexLine	*FL=GetFLinePoint();
	for(int i=0;i<GetFLineLen();i++,FL++){
		int Y=FL->_GetAbsY(this) +dy;
		if(Y<0 || Y>=ymaxlines){
			continue;
		}
		int X=FL->_GetLeftX(this)+dx;
		int N=FL->GetNumb ();
		if(X<0){
			N-= -X;
			X=0;
			}
		if(N<=0){
			continue;
		}
		if(X>xdotperline){
			continue;
		}
		if(X+N>=xdotperline){
			N=xdotperline-X;
		}
		BYTE	*p=src.GetY(Y)+X;
		for(int j=0;j<N;j++,p++){	
			if(*p>HColor){
				HColor= *p;
			}
			if(*p<LColor){
				LColor= *p;
			}
		}
	}
}

void	  FlexArea::GetLowHightColor(int dx,int dy,BYTE **src,int &LColor ,int &HColor ,int xdotperline ,int ymaxlines)
{
	LColor=256;
	HColor=0;

	struct	 FlexLine	*FL=GetFLinePoint();
	for(int i=0;i<GetFLineLen();i++,FL++){
		int Y=FL->_GetAbsY(this) +dy;
		if(Y<0 || Y>=ymaxlines){
			continue;
		}
		int X=FL->_GetLeftX(this)+dx;
		int N=FL->GetNumb ();
		if(X<0){
			N-= -X;
			X=0;
			}
		if(N<=0){
			continue;
		}
		if(X>xdotperline){
			continue;
		}
		if(X+N>=xdotperline){
			N=xdotperline-X;
		}
		BYTE	*p=src[Y]+X;
		for(int j=0;j<N;j++,p++){
			if(*p>HColor){
				HColor= *p;
			}
			if(*p<LColor){
				LColor= *p;
			}
		}
	}
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
int 	  FlexArea::GetClippedPatternByte(int DotPerLine, int MaxLines)
{
	int D=0;

	struct	 FlexLine	*FL=GetFLinePoint();
	for(int i=0;i<GetFLineLen();i++,FL++){
		int Y=FL->_GetAbsY(this);
		if(Y<0 || Y>=MaxLines){
			continue;
		}
		int X=FL->_GetLeftX(this);
		int N=FL->GetNumb ();
		if(X<0){
			N-= -X;
			X=0;
			}
		if(N<=0){
			continue;
		}
		if(X>DotPerLine){
			continue;
		}
		if(X+N>=DotPerLine){
			N=DotPerLine-X;
		}
		D+=N;
	}
	return(D);
}


#define FLexAreaMaxCount	100

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  LData
//	  x
//	  y
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	 FlexArea::ClearClusterFunc(struct ClearClusterFuncStruct *LData ,int x ,int y)
{
	if(x<0 || x>=LData->DotPerLine
	|| y<0 || y>=LData->MaxLines){
		LData->LCount--;
		return(true);
		}
	uchar	*B= &(LData->BmpData[y*LData->NGBmpX+(x>>3)]);
	uchar	Mask=(uchar)(0x80>>(x&7));
	if(((*B)&Mask)==0){
		LData->LCount--;
		return(true);
		}
	(*B) &=~Mask;
	LData->LCount++;
	if(LData->LCount>=FLexAreaMaxCount){
		return(false);
	}


	if(ClearClusterFunc(LData,x-1 ,y-1)==false){
		return(false);
	}
	if(ClearClusterFunc(LData,x   ,y-1)==false){
		return(false);
	}
	if(ClearClusterFunc(LData,x+1 ,y-1)==false){
		return(false);
	}
	if(ClearClusterFunc(LData,x-1 ,y)==false){
		return(false);
	}
	if(ClearClusterFunc(LData,x+1 ,y)==false){
		return(false);
	}
	if(ClearClusterFunc(LData,x-1 ,y+1)==false){
		return(false);
	}
	if(ClearClusterFunc(LData,x   ,y+1)==false){
		return(false);
	}
	if(ClearClusterFunc(LData,x+1 ,y+1)==false){
		return(false);
	}
	LData->LCount--;
	return(true);
}


/*
void FlexArea::ClearCluster(BYTE *data ,int xbyte)
{
	struct ClearClusterFuncStruct	LData;

	LData.BmpData=data;
	LData.NGBmpX =xbyte;
	LData.DotPerLine	=DotPerLine;
	LData.MaxLines		=MaxLines;

	for(int i=0;i<GetFLineLen();i++){
		int y=GetFLineAbsY(i);
		if(y<0 || y>=MaxLines)
			continue;
		int x=GetFLineLeftX(i);
		int N=GetFLineNumb (i);
		if(x<0){
			N-= -x;
			x=0;
			}
		if(N<=0)
			continue;
		if(x>DotPerLine)
			continue;
		if(x+N>=DotPerLine)
			N=DotPerLine-x;

		for(int j=0;j<N;j++){
			uchar	*B= &(data[y*xbyte+((x+j)>>3)]);
			uchar	Mask=(uchar)(0x80>>((x+j)&7));
			(*B) &=~Mask;
			//LData.LCount=0;
			//ClearClusterFunc(&LData ,x+j ,y);
			}
		}
}
*/
/*
void FlexArea::ClearCluster(BYTE **data ,int xbyte)
{
	for(int i=0;i<GetFLineLen();i++){
		int y=GetFLineAbsY(i);
		if(y<0 || y>=MaxLines)
			continue;
		int x=GetFLineLeftX(i);
		int N=GetFLineNumb(i);
		if(x<0){
			N-= -x;
			x=0;
			}
		if(N<=0)
			continue;
		if(x>DotPerLine)
			continue;
		if(x+N>=DotPerLine)
			N=DotPerLine-x;

		for(int j=0;j<N;j++){
			uchar	*B= &(data[y][((x+j)>>3)]);
			uchar	Mask=(uchar)(0x80>>((x+j)&7));
			(*B) &=~Mask;
			}
		}
}
*/

int  FlexArea::MakeBrightList(int *BrList ,int DotPerLine, int MaxLines ,ImageBuffer &data,int dx ,int dy ,int Isolation)
{
	int ret=0;
	int X;
	BYTE	*p;
	int	LNumb=GetFLineLen();
	if(data.IsBitBuff()==false){
		if(Isolation<=1){
			for(int i=0;i<LNumb;i++){
				int Y=GetFLineAbsY(i) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(i)+dx;
					N=GetFLineNumb(i);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<data.GetWidth()){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=(data.GetY(Y)+X);
						for(int j=0;j<N;j++,p++){
							BrList[*p]++;
						}
					}
				}
				ret+=N;
			}
		}
		else{
			if(LNumb<20){
				Isolation=1;
			}
			if(LNumb<50){
				Isolation=min(1,Isolation);
			}
			int	SNumb=LNumb/Isolation;
			for(int i=0;i<SNumb;i++){
				int	k=i*Isolation;
				int Y=GetFLineAbsY(k) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(k)+dx;
					N=GetFLineNumb(k);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<data.GetWidth()){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=(data.GetY(Y)+X);
						for(int j=0;j<N;j++,p++){
							BrList[*p]++;
						}
					}
				}
				ret+=N;
			}
		}
	}
	else{
		int	DataMaxX=data.GetWidth()*8;
		if(Isolation<=1){
			for(int i=0;i<LNumb;i++){
				int Y=GetFLineAbsY(i) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(i)+dx;
					N=GetFLineNumb(i);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<DataMaxX){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=data.GetY(Y);
						for(int j=0;j<N;j++){
							if(GetBmpBitOnY(p,X+j)==0)
								BrList[0]++;
							else
								BrList[255]++;
						}
					}
				}
				ret+=N;
			}
		}
		else{
			if(LNumb<20){
				Isolation=1;
			}
			if(LNumb<50){
				Isolation=min(1,Isolation);
			}
			int	SNumb=LNumb/Isolation;
			for(int i=0;i<SNumb;i++){
				int	k=i*Isolation;
				int Y=GetFLineAbsY(k) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(k)+dx;
					N=GetFLineNumb(k);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<DataMaxX){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=data.GetY(Y);
						for(int j=0;j<N;j++){
							if(GetBmpBitOnY(p,X+j)==0)
								BrList[0]++;
							else
								BrList[255]++;
						}
					}
				}
				ret+=N;
			}
		}
	}
	return(ret);
}

int  FlexArea::MakeBrightList(unsigned int *BrList ,int DotPerLine, int MaxLines ,ImageBuffer &data,int dx ,int dy ,int Isolation)
{
	int ret=0;
	int X;
	BYTE	*p;
	int	LNumb=GetFLineLen();
	if(data.IsBitBuff()==false){
		if(Isolation<=1){
			for(int i=0;i<LNumb;i++){
				int Y=GetFLineAbsY(i) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(i)+dx;
					N=GetFLineNumb(i);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<data.GetWidth()){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=(data.GetY(Y)+X);
						for(int j=0;j<N;j++,p++){
							BrList[*p]++;
						}
					}
				}
				ret+=N;
			}
		}
		else{
			if(LNumb<20){
				Isolation=1;
			}
			if(LNumb<50){
				Isolation=min(1,Isolation);
			}
			int	SNumb=LNumb/Isolation;
			for(int i=0;i<SNumb;i++){
				int	k=i*Isolation;
				int Y=GetFLineAbsY(k) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(k)+dx;
					N=GetFLineNumb(k);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<data.GetWidth()){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=(data.GetY(Y)+X);
						for(int j=0;j<N;j++,p++){
							BrList[*p]++;
						}
					}
				}
				ret+=N;
			}
		}
	}
	else{
		int	DataMaxX=data.GetWidth()*8;
		if(Isolation<=1){
			for(int i=0;i<LNumb;i++){
				int Y=GetFLineAbsY(i) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(i)+dx;
					N=GetFLineNumb(i);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<DataMaxX){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=data.GetY(Y);
						for(int j=0;j<N;j++){
							if(GetBmpBitOnY(p,X+j)==0)
								BrList[0]++;
							else
								BrList[255]++;
						}
					}
				}
				ret+=N;
			}
		}
		else{
			if(LNumb<20){
				Isolation=1;
			}
			if(LNumb<50){
				Isolation=min(1,Isolation);
			}
			int	SNumb=LNumb/Isolation;
			for(int i=0;i<SNumb;i++){
				int	k=i*Isolation;
				int Y=GetFLineAbsY(k) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(k)+dx;
					N=GetFLineNumb(k);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<DataMaxX){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=data.GetY(Y);
						for(int j=0;j<N;j++){
							if(GetBmpBitOnY(p,X+j)==0)
								BrList[0]++;
							else
								BrList[255]++;
						}
					}
				}
				ret+=N;
			}
		}
	}
	return(ret);
}

int  FlexArea::MakeBrightList(unsigned short *BrList ,int DotPerLine, int MaxLines ,ImageBuffer &data,int dx ,int dy ,int Isolation)
{
	int ret=0;
	int X;
	BYTE	*p;
	int	LNumb=GetFLineLen();
	if(data.IsBitBuff()==false){
		if(Isolation<=1){
			for(int i=0;i<LNumb;i++){
				int Y=GetFLineAbsY(i) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(i)+dx;
					N=GetFLineNumb(i);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<data.GetWidth()){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=(data.GetY(Y)+X);
						for(int j=0;j<N;j++,p++){
							BrList[*p]++;
						}
					}
				}
				ret+=N;
			}
		}
		else{
			if(LNumb<20){
				Isolation=1;
			}
			if(LNumb<50){
				Isolation=min(1,Isolation);
			}
			int	SNumb=LNumb/Isolation;
			for(int i=0;i<SNumb;i++){
				int	k=i*Isolation;
				int Y=GetFLineAbsY(k) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(k)+dx;
					N=GetFLineNumb(k);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<data.GetWidth()){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=(data.GetY(Y)+X);
						for(int j=0;j<N;j++,p++){
							BrList[*p]++;
						}
					}
				}
				ret+=N;
			}
		}
	}
	else{
		int	DataMaxX=data.GetWidth()*8;
		if(Isolation<=1){
			for(int i=0;i<LNumb;i++){
				int Y=GetFLineAbsY(i) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(i)+dx;
					N=GetFLineNumb(i);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<DataMaxX){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=data.GetY(Y);
						for(int j=0;j<N;j++){
							if(GetBmpBitOnY(p,X+j)==0)
								BrList[0]++;
							else
								BrList[255]++;
						}
					}
				}
				ret+=N;
			}
		}
		else{
			if(LNumb<20){
				Isolation=1;
			}
			if(LNumb<50){
				Isolation=min(1,Isolation);
			}
			int	SNumb=LNumb/Isolation;
			for(int i=0;i<SNumb;i++){
				int	k=i*Isolation;
				int Y=GetFLineAbsY(k) +dy;
				int	N=0;
				if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
					X=GetFLineLeftX(k)+dx;
					N=GetFLineNumb(k);
					if(X<0){
						N-= -X;
						X=0;
					}
					if(N>0 && X<DotPerLine && X<DataMaxX){
						if(X+N>=DotPerLine){
							N=DotPerLine-X;
						}
						p=data.GetY(Y);
						for(int j=0;j<N;j++){
							if(GetBmpBitOnY(p,X+j)==0)
								BrList[0]++;
							else
								BrList[255]++;
						}
					}
				}
				ret+=N;
			}
		}
	}
	return(ret);
}
void	  FlexArea::GetWeightCenter(double &cx, double &cy)  //重心の計算
{
	cx=0;
	cy=0;
	int N=0;
	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX(i);
		int x2=GetFLineRightX(i);
		int y =GetFLineAbsY(i);
		for(int x=x1;x<x2;x++){
			cx+=x;
			cy+=y;
			N++;
			}
		}
	if(N==0){
		return;
	}
	cx/=N;
	cy/=N;
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  bitmapmaskpattern
//	  xbyte
//
//	3.概要
//
//	4.機能説明__fastcall
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	FlexArea::MaskRemove(BYTE *bitmapmaskpattern ,int xbyte,int DotPerLine, int MaxLines)
{
	NPListPack<FlexLineList>	CpList;

	if(CheckOverlapBit(bitmapmaskpattern ,xbyte,DotPerLine, MaxLines)==false){
		return;
	}

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i);
		int x2=GetFLineRightX(i);
		int y =GetFLineAbsY  (i);

		if(y<0 || y>=MaxLines){
			continue;
		}
		if(x1<0){
			x1=0;
		}
		if(x1>=DotPerLine){
			x1=DotPerLine-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=DotPerLine){
			x2=DotPerLine-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2==0 || x1==(DotPerLine-1)){
			continue;
		}

		BYTE	*p= &bitmapmaskpattern[y*xbyte+(x1>>3)];
		BYTE	mask=0x80>>(x1&7);

		int LastX=x1;
		bool	WhiteMode;
		if( ((*p)&mask)!=0){
			WhiteMode=false;
		}
		else{
			WhiteMode=true;
		}

		for(int x=x1;x<x2;x++){
			if( ((*p)&mask)!=0){
				WhiteMode=false;
				if(x!=LastX){
					FlexLineList	*c=new FlexLineList();
					c->x1=LastX;
					c->x2=x;
					c->y=y;
					CpList.AppendList(c);
					}
				while(((*p)&mask)!=0){
					mask>>=1;
					if(mask==0){
						mask=0x80;
						p++;
						}
					x++;
					if(x>=x2){
						break;
					}
				}
				if(x<x2){
					WhiteMode=true;
				}
				LastX=x;
			}
			else if(WhiteMode==false){
				LastX=x;
				WhiteMode=true;
				}
			mask>>=1;
			if(mask==0){
				mask=0x80;
				p++;
				}
			}
		if(LastX!=x2 && WhiteMode==true){
			FlexLineList	*c=new FlexLineList();
			c->x1=LastX;
			c->x2=x2;
			c->y=y;
			CpList.AppendList(c);
			}
		}

	struct	FlexLine	*FL=new struct	FlexLine [CpList.GetNumber()];

	int n=0;
	for(FlexLineList *m=CpList.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->x2-m->x1>0){
			FL[n]._SetLeftX(m->x1);
			FL[n]. SetNumb (m->x2-m->x1);
			FL[n]._SetAbsY (m->y);
			n++;
			}
		}
	SetFLine(FL,n);
	if(AShape!=NULL){
		delete	AShape;
		AShape=NULL;
	}
	//AShape.Kind=BlockShape::_sFree;
};

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  bitmapmaskpattern
//	  xbyte
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	FlexArea::MaskRemove(BYTE **bitmapmaskpattern ,int xbyte
							,int XDot ,int YDot)
{
	NPListPack<FlexLineList>	CpList;

	if(CheckOverlapBit(bitmapmaskpattern ,XDot, YDot)==false){
		return;
	}

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX(i);
		int x2=GetFLineRightX(i);
		int y =GetFLineAbsY(i);

		if(y<0 || y>=YDot){
			continue;
		}
		if(x1<0){
			x1=0;
		}
		if(x1>=XDot){
			x1=XDot-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=XDot){
			x2=XDot-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2==0 || x1==(XDot-1)){
			continue;
		}

		BYTE	*p= &bitmapmaskpattern[y][(x1>>3)];
		BYTE	mask=0x80>>(x1&7);

		int LastX=x1;
		bool	WhiteMode;
		if( ((*p)&mask)!=0){
			WhiteMode=false;
		}
		else{
			WhiteMode=true;
		}

		for(int x=x1;x<x2;x++){
			if( ((*p)&mask)!=0){
				WhiteMode=false;
				if(x!=LastX){
					FlexLineList	*c=new FlexLineList();
					c->x1=LastX;
					c->x2=x;
					c->y=y;
					CpList.AppendList(c);
					}
				while(((*p)&mask)!=0){
					mask>>=1;
					if(mask==0){
						mask=0x80;
						p++;
						}
					x++;
					if(x>=x2){
						break;
					}
				}
				if(x<x2){
					WhiteMode=true;
				}
				LastX=x;
				}
			else if(WhiteMode==false){
				LastX=x;
				WhiteMode=true;
				}
			mask>>=1;
			if(mask==0){
				mask=0x80;
				p++;
				}
			}
		if(LastX!=x2 && WhiteMode==true){
			FlexLineList	*c=new FlexLineList();
			c->x1=LastX;
			c->x2=x2;
			c->y=y;
			CpList.AppendList(c);
			}
		}

	struct	FlexLine	*FL=new struct	FlexLine [CpList.GetNumber()];

	int n=0;
	for(FlexLineList *m=CpList.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->x2-m->x1>0){
			FL[n]._SetLeftX(m->x1);
			FL[n]. SetNumb (m->x2-m->x1);
			FL[n]._SetAbsY (m->y);
			n++;
			}
		}
	SetFLine(FL,n);
	if(AShape!=NULL){
		delete	AShape;
		AShape=NULL;
	}
	//AShape.Kind=BlockShape::_sFree;
}

void    FlexArea::ClipByMask(BYTE **Mask,int DotPerLine, int MaxLines)
{
	int	MaxLen=GetFLineLen()*10;
	struct  FlexLine    *FL=new struct  FlexLine[MaxLen];
	int	FLIndex=0;
	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX(i);
		int x2=GetFLineRightX(i);
		int y =GetFLineAbsY(i);

		if(y<0 || y>=MaxLines){
			continue;
		}
		if(x1<0){
			x1=0;
		}
		if(x1>=DotPerLine){
			x1=DotPerLine-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=DotPerLine){
			x2=DotPerLine-1;
		}
		BYTE	*s=Mask[y];
		bool	Inside=false;
		for(int x=x1;x<x2;x++){
			if(GetBmpBitOnY(s,x)!=0){
				FL[FLIndex]._SetAbsY(y);
				FL[FLIndex]._SetLeftX(x);
				FL[FLIndex].SetNumb(0);
				Inside=true;
				for(;x<x2;x++){
					if(GetBmpBitOnY(s,x)==0){
						FL[FLIndex].SetNumb(x-FL[FLIndex]._GetLeftX());
						FLIndex++;
						Inside=false;
						break;
					}
				}
			}
			if(FLIndex>=MaxLen){
				int	MaxLen2=MaxLen*2;
				struct  FlexLine    *FL2=new struct  FlexLine[MaxLen2];
				memcpy(FL,FL2,FLIndex*sizeof(struct  FlexLine));
				delete	[]FL;
				FL=FL2;
				MaxLen=MaxLen2;
			}
		}
		if(Inside==true){
			FL[FLIndex].SetNumb(x2-FL[FLIndex]._GetLeftX());
			FLIndex++;
		}
		if(FLIndex>=MaxLen){
			int	MaxLen2=MaxLen*2;
			struct  FlexLine    *FL2=new struct  FlexLine[MaxLen2];
			memcpy(FL,FL2,FLIndex*sizeof(struct  FlexLine));
			delete	[]FL;
			FL=FL2;
			MaxLen=MaxLen2;
		}
	}
	struct  FlexLine    *tFL=new struct  FlexLine[FLIndex];
	memcpy(tFL,FL,FLIndex*sizeof(struct  FlexLine));
	delete	[]FL;
	SetFLine(tFL,FLIndex);
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  _x1
//	  _x2
//	  _y
//
//	3.概要

//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
inline FlexLineList::FlexLineList(int _x1 ,int _x2 ,int _y)
{
	x1=_x1;
	x2=_x2;
	y =_y;
}

/*----------------------------------------------------------------------------*/
//	1.日本語名
//
//	2.概要
//
//	3.機能説明
//
//	4.備考
//
/*----------------------------------------------------------------------------*/
struct FlexAreaFuncData
{
	RFlexAreaList	*dst;
	FlexArea		*src;
	bool			*Checked;
};


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  D
//	  x1
//	  x2
//	  y
//	  NowPoint
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void  FlexArea::SearchAdd(struct FlexAreaFuncData *D
									,int x1 ,int x2 ,int y
									,int NowPoint)
{
	int i,mx2;
	struct	FlexLine	*s;
	for(i=NowPoint+1 ;i<D->src->GetFLineLen();i++){
		s= &D->src->GetFLinePoint()[i];
		if(s->_GetAbsY(D->src)-y>1 || s->_GetAbsY(D->src)-y<-1){
			break;
		}
		if(D->Checked[i]==false){
			if((x1<=s->_GetLeftX(D->src)+1 && s->_GetLeftX(D->src)+1<=x2)
			|| (x1<=s->_GetLeftX(D->src)+s->GetNumb()+2 && s->_GetLeftX(D->src)+s->GetNumb()+2<=x2)
			|| (s->_GetLeftX(D->src)<=x1+1 && x2-1<=s->_GetLeftX(D->src)+s->GetNumb())){
				D->dst->FLineList.AppendList(new FlexLineList(s->_GetLeftX(D->src) ,s->_GetLeftX(D->src)+s->GetNumb() ,s->_GetAbsY(D->src)));
				mx2=s->_GetLeftX(D->src)+s->GetNumb();
				D->Checked[i]=true;
				SearchAdd(D ,s->_GetLeftX(D->src),mx2,s->_GetAbsY(D->src) ,i);
				}
			}
		}
	for(i=NowPoint-1 ;i>=0;i--){
		s= &D->src->GetFLinePoint()[i];
		if(s->_GetAbsY(D->src)-y>1 || s->_GetAbsY(D->src)-y<-1){
			break;
		}
		if(D->Checked[i]==false){
			if((x1<=s->_GetLeftX(D->src)+1 && s->_GetLeftX(D->src)+1<=x2)
			|| (x1<=s->_GetLeftX(D->src)+s->GetNumb()+2 && s->_GetLeftX(D->src)+s->GetNumb()+2<=x2)
			|| (s->_GetLeftX(D->src)<=x1+1 && x2-1<=s->_GetLeftX(D->src)+s->GetNumb())){
				D->dst->FLineList.AppendList(new FlexLineList(s->_GetLeftX(D->src) ,s->_GetLeftX(D->src)+s->GetNumb() ,s->_GetAbsY(D->src)));
				mx2=s->_GetLeftX(D->src)+s->GetNumb();
				D->Checked[i]=true;
				SearchAdd(D ,s->_GetLeftX(D->src),mx2,s->_GetAbsY(D->src) ,i);
				}
			}
		}
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  dst
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
int    FlexArea::ClusterDivide(NPListPack<RFlexAreaList> &dst)
{
	//QSort(FLines,Len,sizeof(FLines[0]),YSortFunc);
	FlexArea	src= *this;

	bool	*Checked=new bool[GetFLineLen()];
	for(int i=0;i<GetFLineLen();i++){
		Checked[i]=false;
		}
	while(src.GetPatternByte()!=0){
		RFlexAreaList	 *D=new RFlexAreaList();
		struct	FlexLine	*s;
		int i;
		bool	CheckedOn=false;
		for(i=0 , s=src.GetFLinePoint();i<src.GetFLineLen();i++,s++){
			if(Checked[i]==false){
				int x1=s->_GetLeftX(&src);
				int x2=s->_GetLeftX(&src) + s->GetNumb();
				int y =s->_GetAbsY(&src);

				Checked[i]=true;
				D->FLineList.AppendList(new FlexLineList(x1 ,x2 ,y));
				s->SetNumb(0);
				struct FlexAreaFuncData Data;
				Data.src= &src;
				Data.dst=D;
				Data.Checked=Checked;
				SearchAdd(&Data,x1,x2,y ,i);
				CheckedOn=true;
				break;
				}
			}
		if(CheckedOn==false){
			break;
		}
		if(D->GetPatternByte()!=0){
			dst.AppendList(D);
			}
		else{
			delete	D;
		}
	}
	delete	[]Checked;
	return(dst.GetNumber());
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
int64 RFlexAreaList::GetPatternByte(void)	const
{
	int64 tByte=0;
	for(FlexLineList *d=FLineList.GetFirst();d!=NULL;d=d->GetNext()){
		tByte+=d->x2-d->x1;
		}
	return(tByte);
}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  src
//
//	3.概要
//
//	4.機能説明__fastcall
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
FlexArea	&FlexArea::operator=(const RFlexAreaList &src)
{
	int mLen=src.FLineList.GetNumber();
	struct FlexLine *FL=new struct FlexLine[mLen];
	int i=0;
	for(FlexLineList *c=src.FLineList.GetFirst();c!=NULL;c=c->GetNext(),i++){
		FL[i]._SetLeftX(c->x1);
		FL[i]. SetNumb (c->x2 - c->x1);
		FL[i]._SetAbsY (c->y);
		}
	QSort(FL,mLen,sizeof(FL[0]),YSortFunc);
	SetFLine(FL,i);

	return(*this);
}

/*----------------------------------------------------------------------------*/
//	1.日本語名
//
//	2.概要
//
//	3.機能説明
//
//	4.備考
//
/*----------------------------------------------------------------------------*/
struct	GetClusterCenterStruct
{
	BYTE	*data;
	double	AddX;
	double	AddY;
	int 	PointNumb;
	int 	ThrLevel;
	int		DotPerLine;
	int		MaxLines;
	NPListPack<XYClass>  R;

	/*----------------------------------------------------------------------------*/
	//
	//	1.日本語名
	//
	//	2.パラメタ説明
	//
	//	3.概要
	//
	//	4.機能説明
	//
	//	5.戻り値
	//
	//	6.備考
	//
	/*----------------------------------------------------------------------------*/
	GetClusterCenterStruct(void)
	{
		data=NULL;
		AddX=0.0;
		AddY=0.0;
		PointNumb=0;
		ThrLevel	=0;
		DotPerLine	=0;
		MaxLines	=0;
	}
	/*----------------------------------------------------------------------------*/
	//
	//	1.日本語名
	//
	//	2.パラメタ説明
	//
	//	3.概要
	//
	//	4.機能説明
	//
	//	5.戻り値
	//
	//	6.備考
	//
	/*----------------------------------------------------------------------------*/
	~GetClusterCenterStruct(void){	R.RemoveAll();	}
};

int MAXCLUSTERPOINT=5000;

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  data
//	  x
//	  y
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
static	void	  SearchGetClusterCenter(struct  GetClusterCenterStruct &data,int x ,int y)
{
	if(x<0 || x>=data.DotPerLine
	|| y<0 || y>=data.MaxLines){
		return;
	}
	for(XYClass *m=data.R.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->x==x && m->y==y){
			return;
		}
	}

	if(data.data[y*data.DotPerLine+x]<data.ThrLevel){
		return;
	}
	data.R.AppendList(new XYClass(x,y));
	data.AddX+=x;
	data.AddY+=y;
	data.PointNumb++;
	if(data.PointNumb>=MAXCLUSTERPOINT){
		return;
	}

	SearchGetClusterCenter(data,x-1 ,y-1);
	SearchGetClusterCenter(data,x	,y-1);
	SearchGetClusterCenter(data,x+1 ,y-1);
	SearchGetClusterCenter(data,x-1 ,y);
	SearchGetClusterCenter(data,x+1 ,y);
	SearchGetClusterCenter(data,x-1 ,y+1);
	SearchGetClusterCenter(data,x	,y+1);
	SearchGetClusterCenter(data,x+1 ,y+1);
}


/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  data
//	  X
//	  Y
//	  searchdot__fastcall
//	  ThrLevel
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
bool	  FlexArea::GetClusterCenter(BYTE *data ,double &X ,double &Y ,int searchdot ,int ThrLevel ,int DotPerLine, int MaxLines)
{
	int cx,cy;
	int x,y;

	GetCenter(cx,cy);

	for(int len=1;len<=searchdot;len+=3){
		y=cy-len;
		for(x=cx-len;x<=cx+len;x+=2){
			if(data[y*DotPerLine+x]>=ThrLevel){
				goto	Found;
			}
		}
		for(;y<=cy+len;y+=2){
			if(data[y*DotPerLine+x]>=ThrLevel){
				goto	Found;
			}
		}
		for(;x>=cx-len;x-=2){
			if(data[y*DotPerLine+x]>=ThrLevel){
				goto	Found;
			}
		}
		for(;y>=cy-len;y-=2){
			if(data[y*DotPerLine+x]>=ThrLevel){
				goto	Found;
			}
		}
	}
	return(false);

	Found:
	struct	GetClusterCenterStruct	ssData;

	ssData.ThrLevel	=ThrLevel;
	ssData.data		=data;
	ssData.DotPerLine	=DotPerLine;
	ssData.MaxLines		=MaxLines;

	SearchGetClusterCenter(ssData,x,y);

	if(ssData.PointNumb==0){
		return(false);
	}
	X=ssData.AddX/ssData.PointNumb;
	Y=ssData.AddY/ssData.PointNumb;

	return(true);

}

/*----------------------------------------------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  newW
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::ChangeWidth(int newW)
{
	if(AShape!=NULL){
		if(AShape->Kind==BlockShape::_sRectangle){
			int x1=AShape->Shape.bsRectangle.X1;
			int y1=AShape->Shape.bsRectangle.Y1;
			int x2=AShape->Shape.bsRectangle.X2;
			int y2=AShape->Shape.bsRectangle.Y2;
			int oldw=x2-x1;
			int dw=(newW-oldw)/2;

			x1-=dw;
			x2+=newW-oldw-dw;
			SetRectangle(x1,y1,x2,y2);
		}
		if(AShape->Kind==BlockShape::_sEllipse){
			int cx=AShape->Shape.bsEllipse.Cx;
			int cy=AShape->Shape.bsEllipse.Cy;
			//int Rx=AShape.Shape.bsEllipse.Rx;
			int Ry=AShape->Shape.bsEllipse.Ry;
			SetEllipse(cx ,cy ,newW ,Ry);
		}
	}
}
/*-------------------------------------__fastcall---------------------------------------*/
//
//	1.日本語名
//
//	2.パラメタ説明
//	  newH
//
//	3.概要
//
//	4.機能説明
//
//	5.戻り値
//
//	6.備考
//
/*----------------------------------------------------------------------------*/
void	  FlexArea::ChangeHeight(int newH)
{
	if(AShape!=NULL){
		if(AShape->Kind==BlockShape::_sRectangle){
			int x1=AShape->Shape.bsRectangle.X1;
			int y1=AShape->Shape.bsRectangle.Y1;
			int x2=AShape->Shape.bsRectangle.X2;
			int y2=AShape->Shape.bsRectangle.Y2;
			int oldh=y2-y1;
			int dh=(newH-oldh)/2;

			y1-=dh;
			y2+=newH-oldh-dh;
			SetRectangle(x1,y1,x2,y2);
		}
		if(AShape->Kind==BlockShape::_sEllipse){
			int Cx=AShape->Shape.bsEllipse.Cx;
			int Cy=AShape->Shape.bsEllipse.Cy;
			int Rx=AShape->Shape.bsEllipse.Rx;
			//int Ry=AShape.Shape.bsEllipse.Ry;
			SetEllipse(Cx ,Cy ,Rx,newH);
		}
	}
}

void	  FlexArea::Sub(const FlexArea &src1 , const FlexArea &src2)
{
	int	src1FLineLen=src1.GetFLineLen();
	int	src2FLineLen=src2.GetFLineLen();
	if(src1FLineLen==0 && src2FLineLen==0){
		return;
	}
	int	Multiply=1;
MultiplyPoint:;
	Multiply++;
	int MaxLen=src1FLineLen*Multiply;
	struct FlexLine *FL=new struct FlexLine[MaxLen];
	int mLen=0;

	int m=0;
	int LastM=m;
	int LastY=src1.GetFLineAbsY(0);
	for(int i=0;i<src1FLineLen;i++){
		int	Src1Y=src1.GetFLineAbsY(i);
		if(LastY==Src1Y){
			m=LastM;
		}
		if(m<src2FLineLen){
			while(src2.GetFLineAbsY(m)<Src1Y){
				m++;
				if(m>=src2FLineLen){
					break;
				}
				if(src2.GetFLineAbsY(m)>Src1Y){
					break;
				}
			}
		}
		int x1=   src1.GetFLineLeftX(i);
		int x2=x1+src1.GetFLineNumb(i);
		LastM=m;
		if(m<src2FLineLen){
			while(src2.GetFLineAbsY(m)==Src1Y){
				if(x1>=x2){
					break;
				}
				int rx1=	src2.GetFLineLeftX(m);
				int rx2=rx1+src2.GetFLineNumb(m);
				if(rx1<=x1){
					if(rx2<x1){
						goto	MMNext;
					}
					if(x1<=rx2){
						x1=rx2;
						goto	MMNext;
					}
				}
				else{
					if(rx1<x2){
						if(rx1-x1!=0){
							FL[mLen]._SetAbsY (Src1Y);
							FL[mLen]._SetLeftX(x1);
							FL[mLen]. SetNumb (rx1-x1);
							mLen++;
						}
						if(mLen>=MaxLen){
							delete	[]FL;
							goto	MultiplyPoint;
						}
						x1=rx2;
					}
					else{
						FL[mLen]._SetAbsY (Src1Y);
						FL[mLen]._SetLeftX(x1);
						FL[mLen]. SetNumb (x2-x1);
						mLen++;
						if(mLen>=MaxLen){
							delete	[]FL;
							goto	MultiplyPoint;
						}
						x1=x2+1;
						break;
					}
				}
				MMNext:;
				m++;
				if(m>=src2FLineLen){
					break;
				}
			}
		}
		if(x1<x2){
			FL[mLen]._SetAbsY (Src1Y);
			FL[mLen]._SetLeftX(x1);
			FL[mLen]. SetNumb (x2-x1);
			mLen++;
			if(mLen>=MaxLen){
				delete	[]FL;
				goto	MultiplyPoint;

			}
		}
		LastY=Src1Y;
	}
	SetFLine(FL,mLen);
}
void	FlexArea::Sub(const FlexArea &src, int dx ,int dy)
{

	if(GetFLineLen()==0){
		return;
	}
	if(SubInside(src, dx ,dy ,1.1)==false){
		if(SubInside(src, dx ,dy ,3)==false){
			if(SubInside(src, dx ,dy ,5)==false){
				SubInside(src, dx ,dy ,10);
				}
			}
		}
}
void	FlexArea::Add(const FlexArea &src1 , const FlexArea &src2)
{
	int	mLen1=src1.GetFLineLen();
	int	mLen2=src2.GetFLineLen();
	int	mLen=mLen1+mLen2;
	struct FlexLine *tFL=new struct FlexLine[mLen];
	memcpy(&tFL[0    ],src1.GetFLinePoint(),sizeof(struct FlexLine)*mLen1);
	memcpy(&tFL[mLen1],src2.GetFLinePoint(),sizeof(struct FlexLine)*mLen2);
	QSort(tFL,mLen,sizeof(struct FlexLine),YSortFunc);
	struct FlexLine *FL=new struct FlexLine[mLen];
	int	L=0;
	for(int i=0;i<mLen;){
		FL[L]=tFL[i];
		i++;
		for(;i<mLen;i++){
			if(FL[L]._GetAbsY()!=tFL[i]._GetAbsY()){
				break;
			}
			if(FL[L]._GetLeftX()<=tFL[i]._GetLeftX() && (FL[L]._GetRightX()+1)>=tFL[i]._GetLeftX()){
				FL[L]._Numb=tFL[i]._GetRightX() - FL[L]._GetLeftX();
			}
			else if(FL[L]._GetRightX()<tFL[i]._GetLeftX()){
				break;
			}
		}
		L++;
	}
	SetFLine(FL,L);
}

bool	FlexArea::SubInside(const FlexArea &src, int dx ,int dy ,float Multiply)
{
	if(GetFLineLen()==0){
		return(true);
	}
	int MaxLen=(GetFLineLen() +src.GetFLineLen())*Multiply;
	struct FlexLine *FL=new struct FlexLine[MaxLen];
	int mLen=0;

	int m=0;
	int LastM=m;
	int LastY=GetFLineAbsY(0);
	for(int i=0;i<GetFLineLen();i++){
		if(LastY==GetFLineAbsY(i)){
			m=LastM;
		}
		if(m<src.GetFLineLen()){
			while((src.GetFLineAbsY(m)+dy)<GetFLineAbsY(i)){
				m++;
				if(m>=src.GetFLineLen()){
					break;
				}
				if((src.GetFLineAbsY(m)+dy)>GetFLineAbsY(i)){
					break;
				}
			}
		}
		int x1=   GetFLineLeftX(i);
		int x2=x1+GetFLineNumb(i);
		LastM=m;
		if(m<src.GetFLineLen()){
			while((src.GetFLineAbsY(m)+dy)==GetFLineAbsY(i)){
				if(x1>=x2){
					break;
				}
				int rx1=	src.GetFLineLeftX(m)+dx;
				int rx2=rx1+src.GetFLineNumb(m);
				if(rx1<=x1){
					if(rx2<x1){
						goto	MMNext;
					}
					if(x1<=rx2){
						x1=rx2;
						goto	MMNext;
						}
					}
				else{
					if(rx1<x2){
						if(rx1-x1!=0){
							FL[mLen]._SetAbsY (GetFLineAbsY(i));
							FL[mLen]._SetLeftX(x1);
							FL[mLen]. SetNumb (rx1-x1);
							mLen++;
							}
						if(mLen>=MaxLen){
							delete	[]FL;
							return(false);
							}
						x1=rx2;
						}
					else{
						FL[mLen]._SetAbsY (GetFLineAbsY(i));
						FL[mLen]._SetLeftX(x1);
						FL[mLen]. SetNumb (x2-x1);
						mLen++;
						if(mLen>=MaxLen){
							delete	[]FL;
							return(false);
							}
						x1=x2+1;
						break;
						}
					}
				MMNext:;
				m++;
				if(m>=src.GetFLineLen()){
					break;
				}
			}
		}
		if(x1<x2){
			FL[mLen]._SetAbsY (GetFLineAbsY(i));
			FL[mLen]._SetLeftX(x1);
			FL[mLen]. SetNumb (x2-x1);
			mLen++;
			if(mLen>=MaxLen){
				delete	[]FL;
				return(false);
				}
			}
		LastY=GetFLineAbsY(i);
		}
	SetFLine(FL,mLen);
	return(true);
}

void	FlexArea::ThinAreaPartial(uchar **bmpdata,uchar **tmpdata,int xbyte ,int YLen)
{
	int	DotPerLine=xbyte*8;
	int	MaxLines=YLen;

	if(GetMinX()<0 || GetMaxX()>DotPerLine || GetMinX()>=DotPerLine){
		Regulate();
		}
	if(GetMinX()<0 || GetMaxX()>DotPerLine || GetMinX()>=DotPerLine){
		return;
	}
	if(GetMinY()<0 || GetMaxY()>MaxLines || GetMinY()>=MaxLines){
		return;
	}

	int KMinXb=GetMinX()/8;
	int KMaxXb=(GetMaxX()+7)/8;
	int KMinX=KMinXb*8;
	int KMaxX=KMaxXb*8;

	if(KMaxXb>xbyte){
		KMaxXb=xbyte;
	}

	if(YLen<=0){
		YLen=MaxLines;
	}
	MatrixBuffBlockCopy(tmpdata					,xbyte,YLen
					   ,(const BYTE **)bmpdata	,xbyte,YLen
					   ,max(0,KMinXb-1)		,max(0,GetMinY()-1)
					   ,min(xbyte,KMaxXb+3)	,min(YLen,GetMaxY()+2));

	int	NNumb=GetMaxY()-1 - GetMinY();
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<NNumb;i++){
			int	y=GetMinY()+i;

			if(y>=1 && (y+1)<YLen){
				uchar	*p2=  &bmpdata[y][KMinXb];
				uchar	*p1=  &tmpdata[y][KMinXb];
				uchar	*p1p= &tmpdata[y+1][KMinXb];
				uchar	*p1m= &tmpdata[y-1][KMinXb];
				for(int x=KMinX;(x+8)<KMaxX;x+=8,p2++,p1++,p1p++,p1m++){
					if(x<=1){
						continue;
					}
					uchar	m22;
					if((m22= *p1)==0){
						continue;
					}

					uchar	m11= *(p1m-1);
					uchar	m12= *(p1m);
					uchar	m13= *(p1m+1);
					uchar	m21= *(p1-1);
					uchar	m23= *(p1+1);
					uchar	m31= *(p1p-1);
					uchar	m32= *(p1p);
					uchar	m33= *(p1p+1);

					if(m22==0xFF
					&& m11==0xFF
					&& m12==0xFF
					&& m13==0xFF
					&& m21==0xFF
					&& m23==0xFF
					&& m31==0xFF
					&& m32==0xFF
					&& m33==0xFF){
						continue;
					}

					BYTE	r=m12 & m32;
					BYTE	t=m22 & r;
					*p2 = *p2 & ((r
							  & ((m21 & m11 & m31)<<7)
							  & ((t)<<1)) | 0x7F);

					*p2 &= 0x81 |( r
								 & (t>>1)
								 & (t<<1) );

					*p2 = *p2 & ((r
							  & ((m23 & m13 & m33)>>7)
							  & ((t)>>1)) | 0xFE);
				}
			}
		}
	}
	MatrixBuffBlockClear(tmpdata,xbyte,YLen
					   ,KMinXb,GetMinY(),KMaxXb,GetMaxY());
}

void	FlexArea::FatAreaPartial(int turn ,uchar **bmpdata,uchar **tmpdata,int xbyte ,int YLen)
{
	int	DotPerLine=xbyte*8;
	int	MaxLines=YLen;

	if(GetMinX()<0 || GetMaxX()>DotPerLine || GetMinX()>=DotPerLine){
		Regulate();
		}
	if(GetMinX()<0 || GetMaxX()>DotPerLine || GetMinX()>=DotPerLine){
		return;
	}

	int KMinXb=(GetMinX()-turn)/8;
	if(KMinXb<0){
		KMinXb=0;
	}
	int KMaxXb=(GetMaxX()+7+turn)/8;
	if(KMaxXb>=DotPerLine/8-1){
		KMaxXb=DotPerLine/8-1;
	}
	if(KMaxXb>xbyte){
		KMaxXb=xbyte;
	}
	int KMinX=KMinXb*8;
	int KMaxX=KMaxXb*8;

	if(YLen<=0){
		YLen=MaxLines;
	}

	int	NNumb=GetMaxY()+1+turn -(GetMinY()-turn-1)+1;
	MatrixBuffBlockCopy(tmpdata					,xbyte,YLen
					   ,(const BYTE **)bmpdata	,xbyte,YLen
					   ,max(0,KMinXb-1)		,max(0,GetMinY()-turn-1-1)
					   ,min(xbyte,KMaxXb+2)	,min(GetMinY()-turn-1+NNumb+1,YLen));

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<NNumb;i++){
			int	y=GetMinY()-turn-1+i;
	//for(int y=GetMinY()-turn-1;y<=GetMaxY()+1+turn;y++){
			if(y>=1 && y<MaxLines-1 && (y+1)<YLen){
				uchar	*p2=  &bmpdata[y][KMinXb];
				uchar	*p1=  &tmpdata[y][KMinXb];
				uchar	*p1p= &tmpdata[y+1][KMinXb];
				uchar	*p1m= &tmpdata[y-1][KMinXb];
				for(int x=KMinX;(x+8)<KMaxX;x+=8,p2++,p1++,p1p++,p1m++){
					if(x<=1){
						continue;
					}
					uchar	m22;
					if((m22= *p1)==0xFF){
						continue;
					}
					uchar	m11= *(p1m-1);
					uchar	m12= *(p1m);
					uchar	m13= *(p1m+1);
					uchar	m21= *(p1-1);
					uchar	m23= *(p1+1);
					uchar	m31= *(p1p-1);
					uchar	m32= *(p1p);
					uchar	m33= *(p1p+1);

					if(m22==0
					&& m11==0
					&& m12==0
					&& m13==0
					&& m21==0
					&& m23==0
					&& m31==0
					&& m32==0
					&& m33==0){
						continue;
					}

					BYTE	r=m12 | m32;
					BYTE	t=m22 | r;

					*p2 |=	((r)
						  | ((m21 | m11 | m31)<<7)
						  | ((t)<<1)) & (~m22) &0x80;
					//_heapchk();

					*p2 |= (r
						  | (t>>1)
						  | (t<<1)) & 0x7E;

					*p2 |= ((r)
						 | ((m23 | m13 | m33)>>7)
						 | ((t)>>1))&(~m22) &0x01;

				}
			}
		}
	}

	MatrixBuffBlockClear(tmpdata,xbyte,YLen
						,KMinXb,((GetMinY()-turn)>0)?(GetMinY()-turn):0
						,KMaxXb,((GetMaxY()+turn)<=MaxLines)?(GetMaxY()+turn):MaxLines);
}


void	  FlexArea::PaintWithColor(BYTE **data, int col,int dx ,int dy ,int DotPerLine, int MaxLines)
{
	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i)+dx;
		int x2=GetFLineRightX(i)+dx;
		int y =GetFLineAbsY  (i)+dy;

		if(y<0 || y>=MaxLines){
			continue;
		}
		if(x1<0){
			x1=0;
		}
		if(x1>=DotPerLine){
			x1=DotPerLine-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=DotPerLine){
			x2=DotPerLine-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2==0 || x1==(DotPerLine-1)){
			continue;
		}
		BYTE	*p=data[y]+x1;
		for(int x=x1;x<x2;x++){
		   *p=col;
		   p++;
		}
	}
}

void	  FlexArea::PaintWithColor(ImageBuffer &data, int col,int dx ,int dy)
{
	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i)+dx;
		int x2=GetFLineRightX(i)+dx;
		int y =GetFLineAbsY  (i)+dy;

		if(y<0 || y>=data.GetHeight()){
			continue;
		}
		if(x1<0){
			x1=0;
		}
		if(x1>=data.GetWidth()){
			x1=data.GetWidth()-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=data.GetWidth()){
			x2=data.GetWidth()-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2==0 || x1==(data.GetWidth()-1)){
			continue;
		}
		BYTE	*p=data.GetY(y)+x1;
		for(int x=x1;x<x2;x++){
		   *p=col;
		   p++;
		}
	}
	data.SetChanged();
}

int 	  FlexArea::GetByte(void)
{
	return(sizeof(FlexArea)
		  +GetFLineLen()*sizeof(struct FlexLine)	);
}


static int	GetSearchFunc(const void *e1, const void *e2)
{
	if(((struct FlexLine *)e1)->_GetAbsY()>((struct FlexLine *)e2)->_GetAbsY()){
		return(1);
	}
	if(((struct FlexLine *)e1)->_GetAbsY()<((struct FlexLine *)e2)->_GetAbsY()){
		return(-1);
	}
	return(0);
}

int   FlexArea::GetSearch(int absY)
{
	struct	FlexLine	Key;

	Key._SetAbsY(this ,absY);

	struct FlexLine *r=(struct FlexLine *)EqualLeastSearch(&Key , GetFLinePoint() , GetFLineLen() , sizeof(Key), GetSearchFunc);
	if(r==NULL){
		return(-1);
	}
	int index=r-GetFLinePoint();
	return(index);
}

PureFlexAreaList::PureFlexAreaList(const PureFlexAreaList &src)
{
	FlexArea::operator=(src);
}

PureFlexAreaList::PureFlexAreaList(const FlexArea &src)
{
	FlexArea::operator=(src);
}

/*
void  FlexArea::CutEffectMaskArea(int Left ,int Top ,int Right ,int Bottom)
{
	MoveToClip(0,0,Left ,Top ,Right ,Bottom);
}
*/

PureFlexAreaList	&PureFlexAreaList::operator=(const PureFlexAreaList &src)
{
	FlexArea::operator=(*((FlexArea *)&src));
	return(*this);
}
PureFlexAreaList	&PureFlexAreaList::operator=(const FlexArea &src)
{
	FlexArea::operator=(src);
	return(*this);
}

qint64	FlexArea::GetCrossCount(FlexArea &src ,int dx ,int dy)	const
{
	qint64	RetCount=0;
	int		IndexStart ,IndexEnd;
	int		SrcN;
	int		LastY=-99999999;
	bool	EffectiveIndexEnd=false;
	int		SrcNumb=src.GetFLineLen();
	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i)-dx;
		int x2=GetFLineRightX(i)-dx;
		int y =GetFLineAbsY  (i)-dy;
		if(LastY!=y){
			if(EffectiveIndexEnd==true && (LastY+1)==y){
				IndexStart=SrcNumb;
				EffectiveIndexEnd=false;
				for(int k=IndexEnd+1;k<SrcNumb;k++){
					if(src.GetFLineAbsY(k)==y){
						IndexStart=k;
						IndexEnd=k;
						EffectiveIndexEnd=true;
						break;
					}
				}
				for(int k=IndexStart+1;k<SrcNumb;k++){
					if(src.GetFLineAbsY(k)!=y){
						break;
					}
					IndexEnd=k;
				}
				SrcN=IndexEnd-IndexStart+1;
			}
			else{
				SrcN=src.FindIndex(y,IndexStart ,IndexEnd);
				if(SrcN==0){
					EffectiveIndexEnd=false;
				}
				else{
					EffectiveIndexEnd=true;
				}
			}
		}
		LastY=y;
		for(int t=0;t<SrcN;t++){
			int dx1=src.GetFLineLeftX (t+IndexStart);
			int dx2=src.GetFLineRightX(t+IndexStart);
			if(dx1<=x1){
				if(x1<=dx2){
					if(dx1<=x2 && x2<=dx2){
						RetCount+=x2-x1;
					}
					else{
						RetCount+=dx2-x1;
					}
				}
			}
			else
			if(dx1<=x2){
				if(x2<=dx2){
					RetCount+=x2-dx1;
				}
				else{
					RetCount+=dx2-dx1;
				}
			}
		}
	}
	return RetCount;
}
qint64		FlexArea::GetCrossCount(int x1,int y1 ,int x2,int y2)	const
{
	if(y2<GetMinY() || x2<GetMinX()
	|| GetMaxY()<y1 || GetMaxX()<x1){
		return 0;
	}
	qint64	Ret=0;
	int	N=GetFLineLen();
	for(int i=0;i<N;i++){
		int y =GetFLineAbsY  (i);
		if(y1<=y){
			if(y<=y2){
				int sx1=GetFLineLeftX (i);
				if(x2<sx1){
					continue;
				}
				int sx2=GetFLineRightX(i);
				if(sx2<x1){
					continue;
				}
				int	Lx1=max(sx1,x1);
				int	Lx2=min(sx2,x2);
				if(Lx1<Lx2){
					Ret+=Lx2-Lx1;
				}
			}
			else{
				return Ret;
			}
		}
	}
	return Ret;
}

double	 FlexArea::GetBunsan(ImageBuffer &data ,double avr,int dx ,int dy)	const
{
	int 	N=0;
	double	D=0.0;
	int		tMaxX=data.GetWidth();
	int		tMaxY=data.GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i)+dx;
		int x2=GetFLineRightX(i)+dx;
		int y =GetFLineAbsY  (i)+dy;

		if(y<0 || y>=tMaxY){
			continue;
		}
		if(x1<0){
			x1=0;
		}
		if(x1>=tMaxX){
			x1=tMaxX-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=tMaxX){
			x2=tMaxX-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2==0 || x1==(tMaxX-1)){
			continue;
		}
		BYTE	*p=data.GetY(y)+x1;
		for(int x=x1;x<x2;x++){
		   D+=(*p-avr)*(*p-avr);
		   p++;
		   N++;
		   }
		}
	if(N!=0){
		D=D/N;
	}
	return(D);
}

double	 FlexArea::GetBunsan(ImageBuffer &data ,double avr,int dx ,int dy
							,int CenterX ,int CenterY ,double radian)	const
{
	int 	N=0;
	double	D=0.0;
	double	SinS=sin(radian);
	double	CosS=cos(radian);
	int		Width=data.GetWidth();
	int		Height=data.GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i);
		int x2=GetFLineRightX(i);
		int y =GetFLineAbsY  (i);

		if(y<0 || y>=Height){
			continue;
		}
		if(x1<0){
			x1=0;
		}
		if(x1>=Width){
			x1=Width-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=Width){
			x2=Width-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2==0 || x1==(Width-1)){
			continue;
		}
		double	SinDxY=-(y-CenterY)*SinS+CenterX+dx;
		double	CosDyY= (y-CenterY)*CosS+CenterY+dy;		
		for(int x=x1;x<x2;x++){
			int	DstX=(x-CenterX)*CosS+SinDxY;
			int	DstY=(x-CenterX)*SinS+CosDyY;
			if(0<=DstX && DstX<Width && 0<=DstY && DstY<Height){
				BYTE	*p=data.GetY(DstY)+DstX;
				D+=(*p-avr)*(*p-avr);
				N++;
			}
		}
	}
	if(N!=0){
		D=D/N;
	}
	return(D);
}

bool	FlexArea::GetPeak(ImageBuffer &Buffer ,int dx ,int dy 
						, int &PeakL ,int &PeakH)	const
{
	int	iPeakL=256;
	int	iPeakH=-1;
	int		tMaxX=Buffer.GetWidth();
	int		tMaxY=Buffer.GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i)+dx;
		int x2=GetFLineRightX(i)+dx;
		int y =GetFLineAbsY  (i)+dy;

		if(y<0 || y>=tMaxY){
			continue;
		}
		if(x1<0){
			x1=0;
		}
		if(x1>=tMaxX){
			x1=tMaxX-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=tMaxX){
			x2=tMaxX-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2==0 || x1==(tMaxX-1)){
			continue;
		}
		BYTE	*p=Buffer.GetY(y)+x1;
		for(int x=x1;x<x2;x++){
			if(*p<iPeakL)
				iPeakL=*p;
			if(*p>iPeakH)
				iPeakH=*p;
		}
	}
	if(iPeakL<256 && iPeakH>=0){
		PeakL=iPeakL;
		PeakH=iPeakH;
		return true;
	}
	return false;
}

void	  FlexArea::MaskEllipse(int ra ,int rb ,int cx ,int cy)
{
	struct	FlexLine	*DestFLines=new struct FlexLine[GetFLineLen()*2];
	int 				DestLen=0;

	for(int i=0;i<GetFLineLen();i++){
		int y =GetFLineAbsY (i);
		if(cy-rb>y || y>cy+rb){
			GetFlexLine(i,DestFLines[DestLen]);
			DestLen++;
			continue;
			}
		int x1=GetFLineLeftX (i);
		int x2=GetFLineRightX(i);

		if(rb==0){
			rb=1;
		}
		int Q=ra*sqrt((double)((double)rb*(double)rb-(double)(y-cy)*(double)(y-cy)))/rb;
		int px1=cx-Q;
		int px2=cx+Q;

		if(x2<=px1){
			GetFlexLine(i,DestFLines[DestLen]);
			DestLen++;
			}
		else
		if(x1<px1 && px1<=x2 && x2<px2){
			GetFlexLine(i,DestFLines[DestLen]);
			DestFLines[DestLen].SetNumb(px1-x1);
			DestLen++;
			}
		else
		if(px1<=x1 && x2<=px2){
			continue;
			}
		else
		if(x1<px1 && px2<x2){
			GetFlexLine(i,DestFLines[DestLen]);
			DestFLines[DestLen].SetNumb(px1-x1);
			DestLen++;
			GetFlexLine(i,DestFLines[DestLen]);
			DestFLines[DestLen]._SetLeftX(px2);
			DestFLines[DestLen].SetNumb(x2-px2);
			DestLen++;
			}
		else
		if(px1<=x1 && x1<=px2 && px2<x2){
			GetFlexLine(i,DestFLines[DestLen]);
			DestFLines[DestLen]._SetLeftX(px2);
			DestFLines[DestLen].SetNumb(x2-px2);
			DestLen++;
			}
		else
		if(px1<=x1){
			GetFlexLine(i,DestFLines[DestLen]);
			DestLen++;
			}
		}
	SetFLine(DestFLines,DestLen);
}

void	  FlexArea::ClipInEllipse(int ra ,int rb ,int cx ,int cy)
{
	struct	FlexLine	*DestFLines=new struct FlexLine[GetFLineLen()];
	int 				DestLen=0;

	for(int i=0;i<GetFLineLen();i++){
		int y =GetFLineAbsY (i);
		if(y<cy-rb){
			continue;
		}
		if(y>cy+rb){
			break;
		}
		int x1=GetFLineLeftX(i);
		int x2=x1+GetFLineNumb(i);
		int Q=ra*sqrt((double)((double)rb*(double)rb-(double)(y-cy)*(double)(y-cy)))/rb;
		int px1=cx-Q;
		int px2=cx+Q;
		if(x2<px1){
			continue;
		}
		else
		if(x1<=px1 && px1<=x2 && x2<=px2){
			DestFLines[DestLen]._SetAbsY(y);
			DestFLines[DestLen]._SetLeftX(px1);
			DestFLines[DestLen]. SetNumb(x2-px1);
			if(DestFLines[DestLen].GetNumb()==0){
				DestFLines[DestLen].SetNumb(1);
			}
			DestLen++;
			}
		else
		if(px1<=x1 && x2<=px2){
			GetFlexLine(i,DestFLines[DestLen]);
			DestLen++;
			}
		else
		if(x1<px1 && px2<=x2){
			DestFLines[DestLen]._SetAbsY(y);
			DestFLines[DestLen]._SetLeftX(px1);
			DestFLines[DestLen].SetNumb(px2-px1);
			if(DestFLines[DestLen].GetNumb()==0){
				DestFLines[DestLen].SetNumb(1);
			}
			DestLen++;
			}
		else
		if(px1<=x1 && x1<px2 && px2<x2){
			DestFLines[DestLen]._SetAbsY(y);
			DestFLines[DestLen]._SetLeftX(x1);
			DestFLines[DestLen].SetNumb(px2-x1);
			if(DestFLines[DestLen].GetNumb()==0){
				DestFLines[DestLen].SetNumb(1);
			}
			DestLen++;
			}
		else
		if(px2<=x1){
			continue;
			}
		}
	SetFLine(DestFLines,DestLen);
}



void	  FlexArea::MakeBitData(BYTE **data
								,int dx ,int dy
								,int XDotLen, int YDotLen)	const
{
	int	NNumb=GetFLineLen();

//	#pragma omp parallel
//	{
//		#pragma omp for
		for(int i=0;i<NNumb;i++){
			int y=GetFLineAbsY(i)+dy;
			if(y>=0 && y<YDotLen){
				uchar	*p=data[y];
				int nx	=GetFLineLeftX(i)+dx;
				int Numb=GetFLineNumb (i);
				if(nx<0){
					Numb+=nx;
					nx=0;
					}
				if(nx<XDotLen){
					if(nx+Numb>=XDotLen){
						Numb=XDotLen-nx-1;
					}
					if(Numb<8){
						for(int x=0;x<Numb;x++,nx++){
							p[nx>>3] |= (uchar)(0x80>>(nx&7));
						}
					}
					else{
						int k=nx>>3;
						int h=nx&7;
						int len=Numb;
						p[k]|=(0xFF>>h);
						len-=8-h;
						k++;
						int blen=len>>3;
						for(int t=0;t<blen;t++){
							p[k]=0xFF;
							len-=8;
							k++;
							}
						p[k]|=(0xFF<<(8-len));
					}
				}
			}
		}
//	}
}
void	 FlexArea::MakeBitData(ImageBuffer &BitImg ,int dx, int dy)	const
{
	int	NNumb=GetFLineLen();
	int	XDotLen=BitImg.GetWidth()*8;
	int	YDotLen=BitImg.GetHeight();

//	#pragma omp parallel
//	{
//		#pragma omp for
		for(int i=0;i<NNumb;i++){
			int y=GetFLineAbsY(i)+dy;
			if(y>=0 && y<YDotLen){
				uchar	*p=BitImg.GetY(y);
				int nx	=GetFLineLeftX(i)+dx;
				int Numb=GetFLineNumb (i);
				if(nx<0){
					Numb+=nx;
					nx=0;
					}
				if(nx<XDotLen){
					if(nx+Numb>=XDotLen){
						Numb=XDotLen-nx-1;
					}
					if(Numb<8){
						for(int x=0;x<Numb;x++,nx++){
							p[nx>>3] |= (uchar)(0x80>>(nx&7));
						}
					}
					else{
						int k=nx>>3;
						int h=nx&7;
						int len=Numb;
						p[k]|=(0xFF>>h);
						len-=8-h;
						k++;
						int blen=len>>3;
						for(int t=0;t<blen;t++){
							p[k]=0xFF;
							len-=8;
							k++;
							}
						p[k]|=(0xFF<<(8-len));
					}
				}
			}
		}
//	}
}

void	  FlexArea::CopyFrom(FlexArea &src ,int dx ,int dy)
{
	operator=(src);
	MoveToNoClip(dx,dy);
}



struct FlexLine FlexAreaBasePure::GetFlexLine(int index)
{
	struct FlexLine ret;
	if(0<=index && index<Len){
		ret=FLines[index];
		ret._SetAbsY (ret._GetAbsY ()+AddY);
		ret._SetLeftX(ret._GetLeftX()+AddX);
	}
	return(ret);
}
bool	FlexAreaBasePure::GetFlexLine(int index , struct FlexLine &Ret)const
{
	if(0<=index && index<Len){
		Ret._SetAbsY (FLines[index]._GetAbsY ()+AddY);
		Ret._SetLeftX(FLines[index]._GetLeftX()+AddX);
		Ret.SetNumb(FLines[index].GetNumb());
		return true;
	}
	return false;
}

int FlexAreaBasePure::SearchNearBy(struct FlexLine Key)
{
	Key._SetAbsY (Key._GetAbsY ()-AddY);
	Key._SetLeftX(Key._GetLeftX()-AddX);
	struct FlexLine *ret=(struct FlexLine *)EqualSearch(&Key,GetFLinePoint(),GetFLineLen(),sizeof(struct FlexLine),NearByFunc);
	if(ret==NULL)
		return -1;
	return(ret-GetFLinePoint());
}

static	int ColTableSortFunc(const void *a, const void *b)
{
	if(((struct  ColSortedTable *)a)->Numb>((struct  ColSortedTable *)b)->Numb){
		return(1);
	}
	if(((struct  ColSortedTable *)a)->Numb<((struct  ColSortedTable *)b)->Numb){
		return(-1);
	}
	return(0);
}
	
double  FlexArea::GetAverage(int dx ,int dy ,ImageBuffer &buff
						,double AdoptRateL,double AdoptRateH)	const
{
	int	CTable[256];

	int	YSep=1;
	int	XSep=1;
	int	YSize=buff.GetHeight();
	int	XSize=buff.GetWidth() ;
	if(YSize>200){
		YSep=5;
	}
	else if(YSize>100){
		YSep=3;
	}
	else if(YSize>50){
		YSep=2;
	}
	if(XSize>200){
		XSep=5;
	}
	else if(XSize>100){
		XSep=3;
	}
	else if(XSize>50){
		XSep=2;
	}

	memset(CTable,0,sizeof(CTable));
	int	DotCount=0;
	for(int i=0;i<GetFLineLen();i++){
		int y =GetFLineAbsY(i)+dy;
		if(y<0 || YSize<=y){
			continue;
		}
		if((y%YSep)!=0){
			continue;
		}
		int	x1=max(GetFLineLeftX(i)+dx,0);
		int	x2=min(GetFLineRightX(i)+dx,XSize);
		int	Numb=x2-x1;
		if(Numb<=0){
			continue;
		}
		BYTE	*p=buff.GetY(y)+x1;

		for(int x=0;x<Numb;x+=XSep ,p+=XSep){
			CTable[*p]++;
			DotCount++;
		}
	}
	int	AbandanDotL=(1.0-AdoptRateL)*DotCount/2;
	int	AbandanDotH=(1.0-AdoptRateH)*DotCount/2;
	int	L1;
	int	L2;
	int	D=0;
	for(L1=0;L1<256;L1++){
		if(D+CTable[L1]>AbandanDotL){
			break;
		}
		D+=CTable[L1];
	}
	D=0;
	for(L2=255;L2>=0;L2--){
		if(D+CTable[L2]>AbandanDotH){
			break;
		}
		D+=CTable[L2];
	}
	DotCount=0;
	double	A=0;
	for(int i=L1;i<=L2;i++){
		DotCount+=CTable[i];
		A+=((double)i)*((double)CTable[i]);
	}
	if(DotCount==0){
		return 0;
	}
	double	Avr=A/DotCount;
	return Avr;
}

double	 FlexArea::GetAverageHalf(ImageBuffer &Data
								,int dx ,int dy ,bool SkippingMode)	const
{
	int 	N=0;
	double	D=0.0;
	int 	RFrac=1;
	struct	ColSortedTable	ColTable[256];
	int	YSize=Data.GetHeight();
	int	XSize=Data.GetWidth() ;

	for(int i=0;i<sizeof(ColTable)/sizeof(ColTable[0]);i++){
		ColTable[i].ColNumb=i;
		ColTable[i].Numb=0;
		}
	if(SkippingMode==true){
		if(GetFLineLen()>200){
			RFrac=7;
		}
		else if(GetFLineLen()>150){
			RFrac=5;
		}
		else if(GetFLineLen()>100){
			RFrac=4;
		}
		else if(GetFLineLen()>60){
			RFrac=3;
		}
		else if(GetFLineLen()>20){
			RFrac=2;
		}
	}
	else{
		if(GetMaxY()-GetMinY()>50){
			RFrac=2;
		}
		else{
			RFrac=1;
		}
	}

	for(int i=0;i<GetFLineLen();i+=RFrac){
		int x1=GetFLineLeftX (i)+dx;
		int x2=GetFLineRightX(i)+dx;
		int y =GetFLineAbsY  (i)+dy;

		if(y<0 || y>=YSize){
			continue;
		}
		if(x1<0){
			x1=0;
		}
		if(x1>=XSize){
			x1=XSize-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=XSize){
			x2=XSize-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2<=0 || x1>=(XSize-1)){
			continue;
		}
		BYTE	*p=Data.GetY(y);
		int Len=x2-x1;
		int XFrac;
		if(SkippingMode==true){
			if(Len>=300){
				XFrac=6;
			}
			else if(Len>=200){
				XFrac=4;
			}
			else if(Len>=100){
				XFrac=2;
			}
			else{
				XFrac=1;
			}
		}
		else{
			if(Len>50){
				XFrac=2;
			}
			else{
				XFrac=1;
			}
		}
		for(int x=x1;x<x2;x+=XFrac){
		   ColTable[*(p+x)].Numb++;
		   }
		N+=(x2-x1)/XFrac;
		}
	//QSort(ColTable,sizeof(ColTable)/sizeof(ColTable[0]),sizeof(ColTable[0]),ColTableSortFunc);
	unsigned int kN=N/4;

	int tL=0;
	int iL;
	for(iL=0;iL<sizeof(ColTable)/sizeof(ColTable[0]);iL++){
		if(tL+ColTable[iL].Numb>kN){
			break;
		}
		tL+=ColTable[iL].Numb;
	}
	int tH=0;
	int iH;
	for(iH=sizeof(ColTable)/sizeof(ColTable[0])-1;iH>=0;iH--){
		if(tH+ColTable[iH].Numb>kN){
			break;
		}
		tH+=ColTable[iH].Numb;
	}
	N=0;
	for(int i=iL;i<=iH;i++){
		D+=ColTable[i].Numb*ColTable[i].ColNumb;
		N+=ColTable[i].Numb;
		}
	if(N==0){
		return(0);
	}
	D/=N;
	return(D);
}

double	 FlexArea::GetAverage(ImageBuffer &Data,int dx ,int dy)	const
{
	int 	N=0;
	double	D=0.0;
	int	YSize=Data.GetHeight();
	int	XSize=Data.GetWidth() ;

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i)+dx;
		int x2=GetFLineRightX(i)+dx;
		int y =GetFLineAbsY  (i)+dy;

		if(y<0 || y>=YSize){
			continue;
		}

		if(x1<0){
			x1=0;
		}
		if(x1>=XSize){
			x1=XSize-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=XSize){
			x2=XSize-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2<=0 || x1>=(XSize-1)){
			continue;
		}

		int Len=x2-x1+1;
		if(Len<=0){
			continue;
		}
		BYTE	*p=Data.GetY(y)+x1;
		int Di=0;
		for(int n=0;n<Len;n++){
		   Di+= *p;
		   p++;
		   }
		D+=Di;
		N+=Len;
		}
	if(N==0){
		return(0);
	}
	return(D/N);
}

double	 FlexArea::GetAverage(ImageBuffer &Data,int dx ,int dy
							,int CenterX ,int CenterY ,double radian)	const
{
	int 	N=0;
	double	D=0.0;
	double	SinS=sin(radian);
	double	CosS=cos(radian);
	int		Width=Data.GetWidth();
	int		Height=Data.GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i);
		int x2=GetFLineRightX(i);
		int y =GetFLineAbsY  (i);

		if(y<0 || y>=Height){
			continue;
		}

		if(x1<0){
			x1=0;
		}
		if(x1>=Width){
			x1=Width-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=Width){
			x2=Width-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2<=0 || x1>=(Width-1)){
			continue;
		}

		int Len=x2-x1+1;
		if(Len<=0){
			continue;
		}
		int Di=0;

		double	SinDxY=-(y-CenterY)*SinS+CenterX+dx;
		double	CosDyY= (y-CenterY)*CosS+CenterY+dy;
		for(int n=0;n<Len;n++){
			int	x=x1+n;
			int	DstX=(x-CenterX)*CosS+SinDxY;
			int	DstY=(x-CenterX)*SinS+CosDyY;
			if(0<=DstX && DstX<Width && 0<=DstY && DstY<Height){
				BYTE	*p=Data.GetY(DstY)+DstX;
				Di+= *p;
				N++;
		   }
		}
		D+=Di;
	}
	if(N==0){
		return(0);
	}
	return(D/N);
}
double	 FlexArea::GetAverageRough(ImageBuffer &Data,int dx ,int dy)	const
{
	int 	N=0;
	double	D=0.0;
	int 	RFrac=1;
	int		Width=Data.GetWidth();
	int		Height=Data.GetHeight();

	if(GetFLineLen()>100){
		RFrac=4;
	}
	else if(GetFLineLen()>60){
		RFrac=3;
	}
	else if(GetFLineLen()>20){
		RFrac=2;
	}

	for(int i=0;i<GetFLineLen();i+=RFrac){
		int x1=GetFLineLeftX (i)+dx;
		int x2=GetFLineRightX(i)+dx;
		int y =GetFLineAbsY  (i)+dy;

		if(y<0 || y>=Height){
			continue;
		}

		if(x1<0){
			x1=0;
		}
		if(x1>=Width){
			x1=Width-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=Width){
			x2=Width-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2<=0 || x1>=(Width-1)){
			continue;
		}

		int Len=x2-x1;
		if(Len<=0){
			continue;
		}
		BYTE	*p=Data.GetY(y);
		int Di=0;
		for(int x=x1;x<=x2;x++){
		   Di+= *(p+x);
		   }
		D+=Di;
		N+=(x2-x1+1);
		}
	if(N==0){
		return(0);
	}
	return(D/N);
}

double	 FlexArea::GetAverageClipped(ImageBuffer &Data,int dx ,int dy
									 ,int X1,int Y1,int X2,int Y2)		const
{
	int 	N=0;
	double	D=0.0;
	int		Width=Data.GetWidth();
	int		Height=Data.GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i)+dx;
		int x2=GetFLineRightX(i)+dx;
		int y =GetFLineAbsY  (i)+dy;

		if(y<0 || y>=Height){
			continue;
		}
		if(y<Y1 || Y2<y){
			continue;
		}

		if(x1<0){
			x1=0;
		}
		if(x1>=Width){
			x1=Width-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=Width){
			x2=Width-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2<=0 || x1>=(Width-1)){
			continue;
		}

		if(x2<X1 || X2<x1){
			continue;
		}
		int rx1=max(X1,x1);
		int rx2=min(X2,x2);

		int Len=rx2-rx1;
		if(Len<=0){
			continue;
		}
		BYTE	*p=Data.GetY(y);
		int Di=0;
		for(int x=rx1;x<=rx2;x++){
		   Di+= *(p+x);
		   }
		D+=Di;
		N+=(rx2-rx1+1);
		}
	if(N==0){
		return(0);
	}
	return(D/N);
}

void	FlexArea::GetMinMaxBrightness(ImageBuffer &Data,int dx ,int dy 
									,int &MinBrightness,int &MaxBrightness)	const
{
	MinBrightness	=255;
	MaxBrightness	=0;
	int		Width=Data.GetWidth();
	int		Height=Data.GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i)+dx;
		int x2=GetFLineRightX(i)+dx;
		int y =GetFLineAbsY  (i)+dy;

		if(y<0 || y>=Height){
			continue;
		}

		if(x1<0){
			x1=0;
		}
		if(x1>=Width){
			x1=Width-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=Width){
			x2=Width-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2<=0 || x1>=(Width-1)){
			continue;
		}

		int Len=x2-x1;
		if(Len<=0){
			continue;
		}
		BYTE	*p=Data.GetY(y);

		for(int x=x1;x<=x2;x++){
		   int	c=*(p+x);
		   if(c<MinBrightness)
				MinBrightness=c;
		   if(c>MaxBrightness)
				MaxBrightness=c;
		}
	}
}
void	  FlexArea::FillData(BYTE col ,ImageBuffer &data)
{
	int		Width=data.GetWidth();
	int		Height=data.GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i);
		int x2=GetFLineRightX(i);
		int y =GetFLineAbsY  (i);

		if(y<0 || y>=Height){
			continue;
		}
		if(x1<0){
			x1=0;
		}
		if(x1>=Width){
			x1=Width-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=Width){
			x2=Width-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2==0 || x1==(Width-1)){
			continue;
		}
		BYTE	*p=data.GetY(y)+x1;
		int len=x2-x1;
		if(len>0){
			memset(p,col,len);
		}
	}
	data.SetChanged();
}

void	  FlexArea::FillData(BYTE col ,BYTE **Image)
{
	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i);
		int x2=GetFLineRightX(i);
		int y =GetFLineAbsY  (i);

		BYTE	*p=Image[y]+x1;
		int len=x2-x1;
		if(len>0){
			memset(p,col,len);
		}
	}
}

int 	 FlexArea::MazeBool2(int index1 ,int index2)
//	０：接触している
//	１：Ｙで離れている
//	２：Ｘで離れている
{
	int y1=GetFLineAbsY(index1);
	int y2=GetFLineAbsY(index2);
	if(y1-y2>=2 || y1-y2<=-2){
		return(1);
	}
	int x11=GetFLineLeftX(index1);
	int x12=GetFLineRightX(index1);
	//int x21=GetFLineLeftX(index2);
	int x22=GetFLineRightX(index2);
	if(x22<x11 || x12<x11){
		return(2);
	}
	return(0);
}

static	bool   MazeBoolLocal(FlexArea *parent ,int index1 ,int index2 ,IntList &PathIndex)
{
	IntClass *d;
	for(int i=index2;i>=0;i--){
		if(i==index1){
			continue;
		}
		for(d=PathIndex.GetFirst();d!=NULL;d=d->GetNext()){
			if(d->GetValue()==i){
				break;
			}
		}
		if(d!=NULL){
			continue;
		}
		int ret=parent->MazeBool2(index1,i);
		if(ret==1){
			break;
		}
		else
		if(ret==0){
			if(i==0){
				return(true);
			}
			PathIndex.Add(i);
			if(MazeBoolLocal(parent ,i ,i-1 ,PathIndex)==true){
				return(true);
			}
		}
	}
	for(int i=index2;i<parent->GetFLineLen();i++){
		if(i==index1){
			continue;
		}
		for(d=PathIndex.GetFirst();d!=NULL;d=d->GetNext()){
			if(d->GetValue()==i){
				break;
			}
		}
		if(d!=NULL){
			continue;
		}
		int ret=parent->MazeBool2(index1,i);
		if(ret==1){
			break;
		}
		else
		if(ret==0){
			PathIndex.Add(i);
			if(MazeBoolLocal(parent ,i ,i+1 ,PathIndex)==true){
				return(true);
			}
		}
	}
	return(false);
}


bool	  FlexArea::MazeBool(int index)
//indexの番号のFlexLineの要素が、0番目の要素に経路でたどり着くときtrue
{
	IntList	PathIndex;

	return(MazeBoolLocal(this ,index ,index ,PathIndex));
}

 static  void  ClusterizeLocal(FlexArea *parent ,int index1 ,int index2 ,IntList &PathIndex)
{
	IntClass *d;
	for(int i=index2;i<parent->GetFLineLen();i++){
		if(i==index1){
			continue;
		}
		for(d=PathIndex.GetFirst();d!=NULL;d=d->GetNext()){
			if(d->GetValue()==i){
				break;
			}
		}
		if(d!=NULL){
			continue;
		}
		int ret=parent->MazeBool2(index1,i);
		if(ret==1){
			break;
		}
		else
		if(ret==0){
			PathIndex.Add(i);
			if(i+1<parent->GetFLineLen()){
				ClusterizeLocal(parent ,i ,i+1 ,PathIndex);
				}
			}
		}
	for(int i=index2;i>=0;i--){
		if(i==index1){
			continue;
		}
		for(d=PathIndex.GetFirst();d!=NULL;d=d->GetNext()){
			if(d->GetValue()==i){
				break;
			}
		}
		if(d!=NULL){
			continue;
		}
		int ret=parent->MazeBool2(index1,i);
		if(ret==1){
			break;
		}
		else
		if(ret==0){
			PathIndex.Add(i);
			if(i-1>=0){
				ClusterizeLocal(parent ,i ,i-1 ,PathIndex);
				}
			}
		}
}

bool	  FlexArea::Clusterize(FlexArea &Remaining)
{

	IntList	PathIndex;

	PathIndex.Add(0);
	ClusterizeLocal(this ,0,0 ,PathIndex);
	int FlexLineNumb=PathIndex.GetCount();
	if(FlexLineNumb==GetFLineLen()){
		Remaining.Clear();
		return(true);
	}

	struct FlexLine *FL=new struct FlexLine[FlexLineNumb];
	IntClass	*d=PathIndex.GetFirst();
	for(int i=0;i<FlexLineNumb && d!=NULL;i++,d=d->GetNext()){
		FL[i]=GetFLinePoint()[d->GetValue()];
		}
	FlexArea	PTmp;
	PTmp= *this;
	SetFLine(FL,FlexLineNumb);
	Remaining.Sub(PTmp,*this);
	return(true);
}

struct	FlexAreaOneSegment
{
	int	x1,x2,y;
};


bool	  FlexArea::Draw(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode)
{
	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(m->width()<=Lx1 || Lx2<0 || m->height()<=Ly1 || Ly2<0){
		return false;
	}
	int	Len=GetFLineLen();

	if(ZoomRate<=1.0){
		if(Lx2-Lx1<4 && Ly2-Ly1<4){
			if(Lx1<0)
				Lx1=0;
			if(Lx2>=m->width())
				Lx2=m->width();
			if(Ly1<0)
				Ly1=0;
			if(Ly2>=m->height())
				Ly2=m->height();
			for(int y=Ly1;y<Ly2;y++){
				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=Lx1;
				for(int x=Lx1;x<Lx2;x++,dst++){
					*dst=c;
				}
			}
			return true;
		}
		int		MaxDimNumb=10000;
		struct	FlexAreaOneSegment	SegDataDim[10000];
		struct	FlexAreaOneSegment	*SegData;
		if(Len>sizeof(SegDataDim)/sizeof(SegDataDim[0])){
			SegData=new struct	FlexAreaOneSegment[Len];
			MaxDimNumb=Len;
		}
		else{
			SegData=SegDataDim;
		}

		int	N=0;
		int	MHeight=m->height();
		for(int i=0;i<Len;i++){
			int	y =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
			if(0<=y && y<MHeight){
				int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
				int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
				if(N!=0 && SegData[N-1].y==y){
					bool	Bound=false;
					for(int k=N-1;k>=0;k--){
						if(SegData[k].y!=y){
							break;
						}
						if((x1<=SegData[k].x1) && (SegData[k].x1<=x2)){
							SegData[k].x1=x1;
						}
						if((x1<=SegData[k].x2) && (SegData[k].x2<=x2)){
							SegData[k].x2=x2;
						}
						if(SegData[k].x1<=x1 && x2<=SegData[k].x2){
PNext:;
							x1=SegData[k].x1;
							x2=SegData[k].x2;
							for(int t=N-1;t>=0;t--){
								if(k==t){
									continue;
								}
								if(SegData[t].y!=y){
									break;
								}
								if((x1<=SegData[t].x1) && (SegData[t].x1<=x2)){
									SegData[t].x1=x1;
								}
								if((x1<=SegData[t].x2) && (SegData[t].x2<=x2)){
									SegData[t].x2=x2;
								}
								if(SegData[t].x1<=x1 && x2<=SegData[t].x2){
									for(int s=k;s<N-1;s++){
										SegData[s]=SegData[s+1];
									}
									N--;
									k=t;
									goto	PNext;
								}
							}
							Bound=true;
							break;
						}
					}
					if(Bound==false && ((x2<SegData[N-1].x1) || (SegData[N-1].x2<x1))){
						SegData[N].y=y;
						SegData[N].x1=x1;
						SegData[N].x2=x2;
						N++;
					}
				}
				else{
					SegData[N].y=y;
					SegData[N].x1=x1;
					SegData[N].x2=x2;
					N++;
				}
				if(N>=MaxDimNumb){
					break;
				}
			}
		}

		if(MultiThreadMode==true && (Lx2-Lx1)>=200 && (Ly2-Ly1)>=100){
			#pragma omp parallel
			{
				#pragma omp for
				for(int i=0;i<N;i++){
					int x1=SegData[i].x1;
					int x2=SegData[i].x2;
					int	y =SegData[i].y ;

					if(x1>=m->width()){
						continue;
					}
					if(x2<0){
						continue;
					}
					if(x1>x2){
						continue;
					}
					if(x1<0){
						x1=0;
					}
					if(x2>=m->width()){
						x2=m->width()-1;
					}

					QRgb *dst=(QRgb *)m->scanLine(y);
					dst+=x1;
					for(int x=x1;x<x2;x++,dst++){
						*dst=c;
					}
				}
			}
		}
		else{
			for(int i=0;i<N;i++){
				int x1=SegData[i].x1;
				int x2=SegData[i].x2;
				int	y =SegData[i].y ;

				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=x1;
				for(int x=x1;x<x2;x++,dst++){
					*dst=c;
				}
			}
		}
		if(SegData!=SegDataDim){
			delete	[]SegData;
		}
	}
	else{
		if(MultiThreadMode==true && (Lx2-Lx1)>=200 && (Ly2-Ly1)>=100){
			#pragma omp parallel
			{
				#pragma omp for
				for(int i=0;i<Len;i++){
					int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
					int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
					int	y1=(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
					int	y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

					if(y2<0 || y1>=m->height()){
						continue;
					}
					if(x1>=m->width()){
						continue;
					}
					if(x2<0){
						continue;
					}
					if(x1>x2){
						continue;
					}
					if(x1<0){
						x1=0;
					}
					if(x2>=m->width()){
						x2=m->width()-1;
					}

					for(int y=y1;y<y2;y++){
						if(y<0){
							continue;
						}
						if(y>=m->height()){
							break;
						}
						QRgb *dst=(QRgb *)m->scanLine(y);
						dst+=x1;
						for(int x=x1;x<x2;x++,dst++){
							*dst=c;
						}
					}
				}
			}
		}
		else{
			for(int i=0;i<Len;i++){
				int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
				int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
				int	y1=(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
				int	y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

				if(y2<0 || y1>=m->height()){
					continue;
				}
				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
					dst+=x1;
					for(int x=x1;x<x2;x++,dst++){
						*dst=c;
					}
				}
			}
		}
	}
	return true;
}
	
struct	FlexAreaOneSegment2
{
	int	x1,x2,y;
	int	RY,RX;
};

bool   FlexArea::Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
					,double ZoomRate ,int movx ,int movy
					,int alpha)
{
	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(m->width()<=Lx1 || Lx2<0 || m->height()<=Ly1 || Ly2<0){
		return false;
	}

	int	Len=GetFLineLen();

	if(ZoomRate<=1.0){
		int		MaxDimNumb=10000;
		struct	FlexAreaOneSegment2	SegDataDim[10000];
		struct	FlexAreaOneSegment2	*SegData;
		if(Len>sizeof(SegDataDim)/sizeof(SegDataDim[0])){
			SegData=new struct	FlexAreaOneSegment2[Len];
			MaxDimNumb=Len;
		}
		else{
			SegData=SegDataDim;
		}

		int	N=0;
		int	MHeight=m->height();
		for(int i=0;i<Len;i++){
			int	Y		=GetFLineAbsY  (i);
			int	LeftX	=GetFLineLeftX (i);
			int	RightX	=GetFLineRightX(i);
			int x1=(LeftX +dx+movx)*ZoomRate;
			int x2=(RightX+dx+movx)*ZoomRate;
			int	y =(Y+dy+movy)*ZoomRate;
			if(0<=y && y<MHeight){
				if(N!=0 && SegData[N-1].y==y){
					bool	Bound=false;
					for(int k=N-1;k>=0;k--){
						if(SegData[k].y!=y){
							break;
						}
						if((x1<=SegData[k].x1) && (SegData[k].x1<=x2)){
							SegData[k].x1=x1;
							SegData[k].RX=LeftX;
						}
						if((x1<=SegData[k].x2) && (SegData[k].x2<=x2)){
							SegData[k].x2=x2;
						}
						if(SegData[k].x1<=x1 && x2<=SegData[k].x2){
PNext:;
							x1=SegData[k].x1;
							x2=SegData[k].x2;
							for(int t=N-1;t>=0;t--){
								if(k==t){
									continue;
								}
								if(SegData[t].y!=y){
									break;
								}
								if((x1<=SegData[t].x1) && (SegData[t].x1<=x2)){
									SegData[t].x1=x1;
									SegData[t].RX=LeftX;
								}
								if((x1<=SegData[t].x2) && (SegData[t].x2<=x2)){
									SegData[t].x2=x2;
								}
								if(SegData[t].x1<=x1 && x2<=SegData[t].x2){
									for(int s=k;s<N-1;s++){
										SegData[s]=SegData[s+1];
									}
									N--;
									k=t;
									goto	PNext;
								}
							}
							Bound=true;
							break;
						}
					}
					if(Bound==false && ((x2<SegData[N-1].x1) || (SegData[N-1].x2<x1))){
						SegData[N].y=y;
						SegData[N].x1=x1;
						SegData[N].x2=x2;
						SegData[N].RY=Y;
						SegData[N].RX=LeftX;
						N++;
					}
				}
				else{
					SegData[N].y=y;
					SegData[N].x1=x1;
					SegData[N].x2=x2;
					SegData[N].RY=Y;
					SegData[N].RX=LeftX;
					N++;
				}
				if(N>=MaxDimNumb){
					break;
				}
			}
		}
		int	SourceW=IBuff[0]->GetWidth();
		int	SourceH=IBuff[0]->GetHeight();
		double	Z=1.0/ZoomRate;
		if(IBuffNumb>=3){
			for(int i=0;i<N;i++){
				int x1=SegData[i].x1;
				int x2=SegData[i].x2;
				int	y =SegData[i].y ;

				if(SegData[i].RY<0 || SourceH<=SegData[i].RY){
					continue;
				}
				int	LeftX=SegData[i].RX;
				BYTE	*sR=IBuff[0]->GetY(SegData[i].RY);
				BYTE	*sG=IBuff[1]->GetY(SegData[i].RY);
				BYTE	*sB=IBuff[2]->GetY(SegData[i].RY);

				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=x1;
				double	Zh=0;
				for(int x=x1;x<x2;x++,dst++){
					int	mx=LeftX+Zh;
					if(mx>=0 && mx<SourceW){
						*dst=qRgba(*(sR+mx),*(sG+mx),*(sB+mx),alpha);
					}
					Zh+=Z;
				}
			}
		}
		else if(IBuffNumb==2){
			for(int i=0;i<N;i++){
				int x1=SegData[i].x1;
				int x2=SegData[i].x2;
				int	y =SegData[i].y ;

				if(SegData[i].RY<0 || SourceH<=SegData[i].RY){
					continue;
				}
				int	LeftX=SegData[i].RX;
				BYTE	*sR=IBuff[0]->GetY(SegData[i].RY);
				BYTE	*sG=IBuff[1]->GetY(SegData[i].RY);

				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=x1;
				double	Zh=0;
				for(int x=x1;x<x2;x++,dst++){
					int	mx=LeftX+Zh;
					if(mx>=0 && mx<SourceW){
						*dst=qRgba(*(sR+mx),*(sG+mx),*(sG+mx),alpha);
					}
					Zh+=Z;
				}
			}
		}
		else if(IBuffNumb==1){
			for(int i=0;i<N;i++){
				int x1=SegData[i].x1;
				int x2=SegData[i].x2;
				int	y =SegData[i].y ;

				if(SegData[i].RY<0 || SourceH<=SegData[i].RY){
					continue;
				}
				int	LeftX=SegData[i].RX;
				BYTE	*sR=IBuff[0]->GetY(SegData[i].RY);

				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=x1;
				double	Zh=0;
				for(int x=x1;x<x2;x++,dst++){
					int	mx=LeftX+Zh;
					if(mx>=0 && mx<SourceW){
						*dst=qRgba(*(sR+mx),*(sR+mx),*(sR+mx),alpha);
					}
					Zh+=Z;
				}
			}
		}
		if(SegData!=SegDataDim){
			delete	[]SegData;
		}
	}
	else{
		int	SourceW=IBuff[0]->GetWidth();
		int	SourceH=IBuff[0]->GetHeight();
		double	Z=1.0/ZoomRate;
		if(IBuffNumb>=3){
			for(int i=0;i<Len;i++){
				int	Y		=GetFLineAbsY  (i);
				int	LeftX	=GetFLineLeftX (i);
				int	RightX	=GetFLineRightX(i);

				if(Y<0 || SourceH<=Y){
					continue;
				}
				int x1=(LeftX	+dx+movx)*ZoomRate;
				int x2=(RightX	+dx+movx)*ZoomRate;
				int	y1=(Y		+dy+movy)*ZoomRate;
				int	y2=(Y+1		+dy+movy)*ZoomRate;

				if(y2<0 || y1>=m->height()){
					continue;
				}
				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				BYTE	*sR=IBuff[0]->GetY(Y);
				BYTE	*sG=IBuff[1]->GetY(Y);
				BYTE	*sB=IBuff[2]->GetY(Y);
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
					double	Zh=0;
					dst+=x1;
					for(int x=x1;x<x2;x++,dst++){
						int	mx=LeftX+Zh;
						if(mx>=0 && mx<SourceW){
							*dst=qRgba(*(sR+mx),*(sG+mx),*(sB+mx),alpha);
						}
						Zh+=Z;
					}
				}
			}
		}
		else if(IBuffNumb==2){
			for(int i=0;i<Len;i++){
				int	Y		=GetFLineAbsY  (i);
				int	LeftX	=GetFLineLeftX (i);
				int	RightX	=GetFLineRightX(i);

				if(Y<0 || SourceH<=Y){
					continue;
				}
				int x1=(LeftX	+dx+movx)*ZoomRate;
				int x2=(RightX	+dx+movx)*ZoomRate;
				int	y1=(Y		+dy+movy)*ZoomRate;
				int	y2=(Y+1		+dy+movy)*ZoomRate;

				if(y2<0 || y1>=m->height()){
					continue;
				}
				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				BYTE	*sR=IBuff[0]->GetY(Y);
				BYTE	*sG=IBuff[1]->GetY(Y);
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
					double	Zh=0;
					dst+=x1;
					for(int x=x1;x<x2;x++,dst++){
						int	mx=LeftX+Zh;
						if(mx>=0 && mx<SourceW){
							*dst=qRgba(*(sR+mx),*(sG+mx),*(sG+mx),alpha);
						}
						Zh+=Z;
					}
				}
			}
		}
		else if(IBuffNumb==1){
			for(int i=0;i<Len;i++){
				int	Y		=GetFLineAbsY  (i);
				int	LeftX	=GetFLineLeftX (i);
				int	RightX	=GetFLineRightX(i);

				if(Y<0 || SourceH<=Y){
					continue;
				}
				int x1=(LeftX	+dx+movx)*ZoomRate;
				int x2=(RightX	+dx+movx)*ZoomRate;
				int	y1=(Y		+dy+movy)*ZoomRate;
				int	y2=(Y+1		+dy+movy)*ZoomRate;

				if(y2<0 || y1>=m->height()){
					continue;
				}
				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				BYTE	*sR=IBuff[0]->GetY(Y);
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
					double	Zh=0;
					dst+=x1;
					for(int x=x1;x<x2;x++,dst++){
						int	mx=LeftX+Zh;
						if(mx>=0 && mx<SourceW){
							*dst=qRgba(*(sR+mx),*(sR+mx),*(sR+mx),alpha);
						}
						Zh+=Z;
					}
				}
			}
		}
	}
	return true;
}
	
bool   FlexArea::Draw(int dx ,int dy ,QImage *m ,ImageBuffer *IBuff[] ,int IBuffNumb
									,double ZoomRate ,int movx ,int movy
									,BYTE ColorTable[3][256]
									,int alpha)
{
	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(m->width()<=Lx1 || Lx2<0 || m->height()<=Ly1 || Ly2<0){
		return false;
	}

	int	Len=GetFLineLen();

	if(ZoomRate<=1.0){
		int		MaxDimNumb=10000;
		struct	FlexAreaOneSegment2	SegDataDim[10000];
		struct	FlexAreaOneSegment2	*SegData;
		if(Len>sizeof(SegDataDim)/sizeof(SegDataDim[0])){
			SegData=new struct	FlexAreaOneSegment2[Len];
			MaxDimNumb=Len;
		}
		else{
			SegData=SegDataDim;
		}

		int	N=0;
		int	MHeight=m->height();
		for(int i=0;i<Len;i++){
			int	Y		=GetFLineAbsY  (i);
			int	LeftX	=GetFLineLeftX (i);
			int	RightX	=GetFLineRightX(i);
			int x1=(LeftX +dx+movx)*ZoomRate;
			int x2=(RightX+dx+movx)*ZoomRate;
			int	y =(Y+dy+movy)*ZoomRate;
			if(0<=y && y<MHeight){
				if(N!=0 && SegData[N-1].y==y){
					bool	Bound=false;
					for(int k=N-1;k>=0;k--){
						if(SegData[k].y!=y){
							break;
						}
						if((x1<=SegData[k].x1) && (SegData[k].x1<=x2)){
							SegData[k].x1=x1;
							SegData[k].RX=LeftX;
						}
						if((x1<=SegData[k].x2) && (SegData[k].x2<=x2)){
							SegData[k].x2=x2;
						}
						if(SegData[k].x1<=x1 && x2<=SegData[k].x2){
PNext:;
							x1=SegData[k].x1;
							x2=SegData[k].x2;
							for(int t=N-1;t>=0;t--){
								if(k==t){
									continue;
								}
								if(SegData[t].y!=y){
									break;
								}
								if((x1<=SegData[t].x1) && (SegData[t].x1<=x2)){
									SegData[t].x1=x1;
									SegData[t].RX=LeftX;
								}
								if((x1<=SegData[t].x2) && (SegData[t].x2<=x2)){
									SegData[t].x2=x2;
								}
								if(SegData[t].x1<=x1 && x2<=SegData[t].x2){
									for(int s=k;s<N-1;s++){
										SegData[s]=SegData[s+1];
									}
									N--;
									k=t;
									goto	PNext;
								}
							}
							Bound=true;
							break;
						}
					}
					if(Bound==false && ((x2<SegData[N-1].x1) || (SegData[N-1].x2<x1))){
						SegData[N].y=y;
						SegData[N].x1=x1;
						SegData[N].x2=x2;
						SegData[N].RY=Y;
						SegData[N].RX=LeftX;
						N++;
					}
				}
				else{
					SegData[N].y=y;
					SegData[N].x1=x1;
					SegData[N].x2=x2;
					SegData[N].RY=Y;
					SegData[N].RX=LeftX;
					N++;
				}
				if(N>=MaxDimNumb){
					break;
				}
			}
		}
		int	SourceW=IBuff[0]->GetWidth();
		int	SourceH=IBuff[0]->GetHeight();
		double	Z=1.0/ZoomRate;
		if(IBuffNumb>=3){
			for(int i=0;i<N;i++){
				int x1=SegData[i].x1;
				int x2=SegData[i].x2;
				int	y =SegData[i].y ;

				if(SegData[i].RY<0 || SourceH<=SegData[i].RY){
					continue;
				}
				int	LeftX=SegData[i].RX;
				BYTE	*sR=IBuff[0]->GetY(SegData[i].RY);
				BYTE	*sG=IBuff[1]->GetY(SegData[i].RY);
				BYTE	*sB=IBuff[2]->GetY(SegData[i].RY);

				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=x1;
				double	Zh=0;
				for(int x=x1;x<x2;x++,dst++){
					int	mx=LeftX+Zh;
					if(mx>=0 && mx<SourceW){
						*dst=qRgba(ColorTable[0][*(sR+mx)]
								,  ColorTable[1][*(sG+mx)]
								,  ColorTable[2][*(sB+mx)]
								, alpha);
					}
					Zh+=Z;
				}
			}
		}
		else if(IBuffNumb==2){
			for(int i=0;i<N;i++){
				int x1=SegData[i].x1;
				int x2=SegData[i].x2;
				int	y =SegData[i].y ;

				if(SegData[i].RY<0 || SourceH<=SegData[i].RY){
					continue;
				}
				int	LeftX=SegData[i].RX;
				BYTE	*sR=IBuff[0]->GetY(SegData[i].RY);
				BYTE	*sG=IBuff[1]->GetY(SegData[i].RY);

				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=x1;
				double	Zh=0;
				for(int x=x1;x<x2;x++,dst++){
					int	mx=LeftX+Zh;
					if(mx>=0 && mx<SourceW){
						*dst=qRgba(ColorTable[0][*(sR+mx)]
								,  ColorTable[1][*(sG+mx)]
								,  ColorTable[2][*(sG+mx)]
								,alpha);
					}
					Zh+=Z;
				}
			}
		}
		else if(IBuffNumb==1){
			for(int i=0;i<N;i++){
				int x1=SegData[i].x1;
				int x2=SegData[i].x2;
				int	y =SegData[i].y ;

				if(SegData[i].RY<0 || SourceH<=SegData[i].RY){
					continue;
				}
				int	LeftX=SegData[i].RX;
				BYTE	*sR=IBuff[0]->GetY(SegData[i].RY);

				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=x1;
				double	Zh=0;
				for(int x=x1;x<x2;x++,dst++){
					int	mx=LeftX+Zh;
					if(mx>=0 && mx<SourceW){
						*dst=qRgba(ColorTable[0][*(sR+mx)]
								 , ColorTable[1][*(sR+mx)]
								 , ColorTable[2][*(sR+mx)]
								 , alpha);
					}
					Zh+=Z;
				}
			}
		}
		if(SegData!=SegDataDim){
			delete	[]SegData;
		}
	}
	else{
		int	SourceW=IBuff[0]->GetWidth();
		int	SourceH=IBuff[0]->GetHeight();
		double	Z=1.0/ZoomRate;
		if(IBuffNumb>=3){
			for(int i=0;i<Len;i++){
				int	Y		=GetFLineAbsY  (i);
				int	LeftX	=GetFLineLeftX (i);
				int	RightX	=GetFLineRightX(i);

				if(Y<0 || SourceH<=Y){
					continue;
				}
				int x1=(LeftX	+dx+movx)*ZoomRate;
				int x2=(RightX	+dx+movx)*ZoomRate;
				int	y1=(Y		+dy+movy)*ZoomRate;
				int	y2=(Y+1		+dy+movy)*ZoomRate;

				if(y2<0 || y1>=m->height()){
					continue;
				}
				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				BYTE	*sR=IBuff[0]->GetY(Y);
				BYTE	*sG=IBuff[1]->GetY(Y);
				BYTE	*sB=IBuff[2]->GetY(Y);
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
					double	Zh=0;
					dst+=x1;
					for(int x=x1;x<x2;x++,dst++){
						int	mx=LeftX+Zh;
						if(mx>=0 && mx<SourceW){
							*dst=qRgba(ColorTable[0][*(sR+mx)]
									 , ColorTable[1][*(sG+mx)]
									 , ColorTable[2][*(sB+mx)]
									 , alpha);
						}
						Zh+=Z;
					}
				}
			}
		}
		else if(IBuffNumb==2){
			for(int i=0;i<Len;i++){
				int	Y		=GetFLineAbsY  (i);
				int	LeftX	=GetFLineLeftX (i);
				int	RightX	=GetFLineRightX(i);

				if(Y<0 || SourceH<=Y){
					continue;
				}
				int x1=(LeftX	+dx+movx)*ZoomRate;
				int x2=(RightX	+dx+movx)*ZoomRate;
				int	y1=(Y		+dy+movy)*ZoomRate;
				int	y2=(Y+1		+dy+movy)*ZoomRate;

				if(y2<0 || y1>=m->height()){
					continue;
				}
				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				BYTE	*sR=IBuff[0]->GetY(Y);
				BYTE	*sG=IBuff[1]->GetY(Y);
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
					double	Zh=0;
					dst+=x1;
					for(int x=x1;x<x2;x++,dst++){
						int	mx=LeftX+Zh;
						if(mx>=0 && mx<SourceW){
							*dst=qRgba(ColorTable[0][*(sR+mx)]
									 , ColorTable[1][*(sG+mx)]
									 , ColorTable[2][*(sG+mx)]
									 ,alpha);
						}
						Zh+=Z;
					}
				}
			}
		}
		else if(IBuffNumb==1){
			for(int i=0;i<Len;i++){
				int	Y		=GetFLineAbsY  (i);
				int	LeftX	=GetFLineLeftX (i);
				int	RightX	=GetFLineRightX(i);

				if(Y<0 || SourceH<=Y){
					continue;
				}
				int x1=(LeftX	+dx+movx)*ZoomRate;
				int x2=(RightX	+dx+movx)*ZoomRate;
				int	y1=(Y		+dy+movy)*ZoomRate;
				int	y2=(Y+1		+dy+movy)*ZoomRate;

				if(y2<0 || y1>=m->height()){
					continue;
				}
				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				BYTE	*sR=IBuff[0]->GetY(Y);
				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
					double	Zh=0;
					dst+=x1;
					for(int x=x1;x<x2;x++,dst++){
						int	mx=LeftX+Zh;
						if(mx>=0 && mx<SourceW){
							*dst=qRgba(ColorTable[0][*(sR+mx)]
									 , ColorTable[1][*(sR+mx)]
									 , ColorTable[2][*(sR+mx)]
									 ,alpha);
						}
						Zh+=Z;
					}
				}
			}
		}
	}
	return true;
}
FlexArea	FlexArea::MakeSkipYArea(int SkipY)
{
	int	N=GetFLineLen();
	struct FlexLine	*FLine=new struct FlexLine[N];
	int	k=0;
	for(int i=0;i<N;i++){
		int	Y=GetFLineAbsY(i);
		if((Y%SkipY)==0){
			FLine[k]=GetFLinePoint()[i];
			k++;
		}
		else{
			int	LNumb=GetFLineNumb(i)/8;
			if(i>0 && GetFLineAbsY(i-1)<Y
			&& (i+1)<N && GetFLineAbsY(i+1)>Y
			&& GetFLineNumb(i-1)<LNumb && LNumb>GetFLineNumb(i+1)){
				FLine[k]=GetFLinePoint()[i];
				k++;
			}
		}
	}
	FlexArea	A;
	A.SetFLine(FLine,k);
	return A;
}

inline static int int_comp(const int16 *a,const int16 *b)
{
	return *a - *b;
}

bool	  FlexArea::DrawOutline(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode)
{
//	QColor cColor=QColor(c);
//	cColor.setAlpha(50);
//	QRgb ca=cColor.rgba();

//	QRgb ca=qRgba(0,255,255,50);
//	QRgb cb=qRgba(255,255,0,50);

	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(m->width()<=Lx1 || Lx2<0 || m->height()<=Ly1 || Ly2<0){
		return false;
	}

	int	Len=GetFLineLen();

	try{
		if(ZoomRate<=1.0){
			int		MaxDimNumb=10000;
			struct	FlexAreaOneSegment	SegDataDim[10000];
			struct	FlexAreaOneSegment	*SegData;
			if(Len>sizeof(SegDataDim)/sizeof(SegDataDim[0])){
				SegData=new struct	FlexAreaOneSegment[Len];
				MaxDimNumb=Len;
			}
			else{
				SegData=SegDataDim;
			}

			int	N=0;
			int	MHeight=m->height();
			for(int i=0;i<Len;i++){
				int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
				int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
				int	y =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
				if(0<=y && y<MHeight){
					if(N!=0 && SegData[N-1].y==y){
						bool	Bound=false;
						for(int k=N-1;k>=0;k--){
							if(SegData[k].y!=y){
								break;
							}
							if((x1<=SegData[k].x1) && (SegData[k].x1<=x2)){
								SegData[k].x1=x1;
							}
							if((x1<=SegData[k].x2) && (SegData[k].x2<=x2)){
								SegData[k].x2=x2;
							}
							if(SegData[k].x1<=x1 && x2<=SegData[k].x2){
PNext:;
								x1=SegData[k].x1;
								x2=SegData[k].x2;
								for(int t=N-1;t>=0;t--){
									if(k==t){
										continue;
									}
									if(SegData[t].y!=y){
										break;
									}
									if((x1<=SegData[t].x1) && (SegData[t].x1<=x2)){
										SegData[t].x1=x1;
									}
									if((x1<=SegData[t].x2) && (SegData[t].x2<=x2)){
										SegData[t].x2=x2;
									}
									if(SegData[t].x1<=x1 && x2<=SegData[t].x2){
										for(int s=k;s<N-1;s++){
											SegData[s]=SegData[s+1];
										}
										N--;
										k=t;
										goto	PNext;
									}
								}
								Bound=true;
								break;
							}
						}
						if(Bound==false && ((x2<SegData[N-1].x1) || (SegData[N-1].x2<x1))){
							SegData[N].y=y;
							SegData[N].x1=x1;
							SegData[N].x2=x2;
							N++;
						}
					}
					else{
						SegData[N].y=y;
						SegData[N].x1=x1;
						SegData[N].x2=x2;
						N++;
					}
					if(N>=MaxDimNumb){
						break;
					}
				}
			}
			if(MultiThreadMode==true){
				#pragma omp parallel
				{
					#pragma omp for
					for(int i=0;i<N;i++){
						int x1=SegData[i].x1;
						int x2=SegData[i].x2;
						int	y =SegData[i].y ;

						if(x1>=m->width()){
							continue;
						}
						if(x2<0){
							continue;
						}
						if(x1>x2){
							continue;
						}
						if(x1<0){
							x1=0;
						}
						if(x2>=m->width()){
							x2=m->width()-1;
						}

						QRgb *dst=(QRgb *)m->scanLine(y);
						dst+=x1;
						for(int x=x1;x<x2;x++,dst++){
							*dst=c;
						}
					}
				}
			}
			else{
				for(int i=0;i<N;i++){
					int x1=SegData[i].x1;
					int x2=SegData[i].x2;
					int	y =SegData[i].y ;

					if(x1>=m->width()){
						continue;
					}
					if(x2<0){
						continue;
					}
					if(x1>x2){
						continue;
					}
					if(x1<0){
						x1=0;
					}
					if(x2>=m->width()){
						x2=m->width()-1;
					}

					QRgb *dst=(QRgb *)m->scanLine(y);
					dst+=x1;
					for(int x=x1;x<x2;x++,dst++){
						*dst=c;
					}
				}
			}
			if(SegData!=SegDataDim){
				delete	[]SegData;
			}
		}
		else{
			int PreCnt=0;
			int NowCnt=1;
			int16 Px1[7296],Px2[7296],Py2[7296];
			int16 Nx1[7296],Nx2[7296],Ny2[7296];
			int16 SortedX[7296<<2];
			for(int i=0;i<Len;i++){
				int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
				int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
				int y1=(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
				int y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

				if(y2<0 || y1>=m->height()){
					continue;
				}
				if(x2<0 || (NowCnt==1 && x1>=m->width())){
					if(y2-Py2[0]>y2-y1 && PreCnt>1){
						//ラインを引く
						if(Py2[0]>=0){
							memcpy(SortedX		 ,Px1,sizeof(int16)*PreCnt);
							memcpy(SortedX+PreCnt,Px2,sizeof(int16)*PreCnt);
							QSort(SortedX,(PreCnt<<1),sizeof(int16),(int (*)(const void*,const void*))int_comp);
							#pragma omp parallel
							{
								#pragma omp for
								for(int j=0;j<(PreCnt<<1);j+=2){
									QRgb *dst=(QRgb *)m->scanLine(Py2[0]);
									dst+=SortedX[j];
									for(int x=SortedX[j];x<SortedX[j+1];x++,dst++){
										if(x>=0 && x<m->width()){
											*dst=c;
										}
									}
								}
							}
						}
						PreCnt=0;
					}
					continue;
				}
				if(x1>x2){
					continue;
				}
				//両端
				if(x1<m->width()){
					for(int y=y1;y<y2;y++){
						if(y<0){
							continue;
						}
						if(y>=m->height()){
							break;
						}
						QRgb *dst=(QRgb *)m->scanLine(y);
						if(x1>0){
							*(dst+x1)=c;
						}
						if(x2<m->width()-1){
							*(dst+x2)=c;
						}
					}
				}
				//次のラインを読み込む
				Nx1[NowCnt-1]=x1;
				Nx2[NowCnt-1]=x2;
				Ny2[NowCnt-1]=y2;
				if(i+1<Len && y1==(int)((GetFLineAbsY(i+1)+dy+movy)*ZoomRate)){
					NowCnt++;
					continue;
				}
				//ラインを引く
				if(y1>=0){
					memcpy(SortedX					 ,Nx1,sizeof(int16)*NowCnt);
					memcpy(SortedX+NowCnt			 ,Nx2,sizeof(int16)*NowCnt);
					memcpy(SortedX+(NowCnt<<1)		 ,Px1,sizeof(int16)*PreCnt);
					memcpy(SortedX+(NowCnt<<1)+PreCnt,Px2,sizeof(int16)*PreCnt);
					QSort(SortedX,(PreCnt<<1)+(NowCnt<<1),sizeof(int16),(int (*)(const void*,const void*))int_comp);
					#pragma omp parallel
					{
						#pragma omp for
						for(int j=0;j<(PreCnt<<1)+(NowCnt<<1);j+=2){
							QRgb *dst=(QRgb *)m->scanLine(y1);
							dst+=SortedX[j];
							for(int x=SortedX[j];x<SortedX[j+1];x++,dst++){
								if(x>=0 && x<m->width()){
									*dst=c;
								}
							}
						}
					}
				}
				PreCnt=NowCnt;
				memcpy(Px1,Nx1,sizeof(int)*NowCnt);
				memcpy(Px2,Nx2,sizeof(int)*NowCnt);
				memcpy(Py2,Ny2,sizeof(int)*NowCnt);
				NowCnt=1;
			}
			//最後
			if(Py2[0]<m->height()-1){
				#pragma omp parallel
				{
					#pragma omp for
					for(int j=0;j<PreCnt;j++){
						if(Py2[j]>0){
							QRgb *dst=(QRgb *)m->scanLine(Py2[j]-1);
							dst+=Px1[j];
							for(int x=Px1[j];x<Px2[j];x++,dst++){
								if(x>=0 && x<m->width()){
									*dst=c;
								}
							}
						}
					}
				}
			}
		}
	}
	catch(...){
		//何らかのエラー（アドレス違反等）が発生
	}
	return true;
}

bool	  FlexArea::DrawAlpha(int dx ,int dy ,QImage *m ,QRgb c
									,double ZoomRate ,int movx ,int movy
									,bool MultiThreadMode)
{
	int	Lx1=(GetMinX()+dx+movx)*ZoomRate;
	int	Ly1=(GetMinY()+dy+movy)*ZoomRate;
	int	Lx2=(GetMaxX()+dx+movx)*ZoomRate;
	int	Ly2=(GetMaxY()+dy+movy)*ZoomRate;
	if(m->width()<=Lx1 || Lx2<0 || m->height()<=Ly1 || Ly2<0){
		return false;
	}

	int	cr=qRed(c);
	int	cg=qGreen(c);
	int	cb=qBlue(c);
	int	ca=qAlpha(c);
	int	Len=GetFLineLen();
	if(ZoomRate<=1.0){
		int		MaxDimNumb=10000;
		struct	FlexAreaOneSegment	SegDataDim[10000];
		struct	FlexAreaOneSegment	*SegData;
		if(Len>sizeof(SegDataDim)/sizeof(SegDataDim[0])){
			SegData=new struct	FlexAreaOneSegment[Len];
			MaxDimNumb=Len;
		}
		else{
			SegData=SegDataDim;
		}
		int	N=0;
		int	MHeight=m->height();
		for(int i=0;i<Len;i++){
			int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
			int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
			int	y =(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
			if(0<=y && y<MHeight){
				if(N!=0 && SegData[N-1].y==y){
					bool	Bound=false;
					for(int k=N-1;k>=0;k--){
						if(SegData[k].y!=y){
							break;
						}
						if((x1<=SegData[k].x1) && (SegData[k].x1<=x2)){
							SegData[k].x1=x1;
						}
						if((x1<=SegData[k].x2) && (SegData[k].x2<=x2)){
							SegData[k].x2=x2;
						}
						if(SegData[k].x1<=x1 && x2<=SegData[k].x2){
PNext:;
							x1=SegData[k].x1;
							x2=SegData[k].x2;
							for(int t=N-1;t>=0;t--){
								if(k==t){
									continue;
								}
								if(SegData[t].y!=y){
									break;
								}
								if((x1<=SegData[t].x1) && (SegData[t].x1<=x2)){
									SegData[t].x1=x1;
								}
								if((x1<=SegData[t].x2) && (SegData[t].x2<=x2)){
									SegData[t].x2=x2;
								}
								if(SegData[t].x1<=x1 && x2<=SegData[t].x2){
									for(int s=k;s<N-1;s++){
										SegData[s]=SegData[s+1];
									}
									N--;
									k=t;
									goto	PNext;
								}
							}
							Bound=true;
							break;
						}
					}
					if(Bound==false && ((x2<SegData[N-1].x1) || (SegData[N-1].x2<x1))){
						SegData[N].y=y;
						SegData[N].x1=x1;
						SegData[N].x2=x2;
						N++;
					}
				}
				else{
					SegData[N].y=y;
					SegData[N].x1=x1;
					SegData[N].x2=x2;
					N++;
				}
				if(N>=MaxDimNumb){
					break;
				}
			}
		}
		if(MultiThreadMode==true && N>=24){
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for(int i=0;i<N;i++){
					int x1=SegData[i].x1;
					int x2=SegData[i].x2;
					int	y =SegData[i].y ;

					if(y<0 || y>=m->height()){
						continue;
					}
					if(x1>=m->width()){
						continue;
					}
					if(x2<0){
						continue;
					}
					if(x1>x2){
						continue;
					}
					if(x1<0){
						x1=0;
					}
					if(x2>=m->width()){
						x2=m->width()-1;
					}

					QRgb *dst=(QRgb *)m->scanLine(y);
					dst+=x1;
					for(int x=x1;x<=x2;x++,dst++){
						*dst=qRgba(	 Clipping((((cr-qRed(*dst))*ca)>>8)+qRed(*dst),0,255)
									,Clipping((((cg-qGreen(*dst))*ca)>>8)+qGreen(*dst),0,255)
									,Clipping((((cb-qBlue(*dst))*ca)>>8)+qBlue(*dst),0,255)
									,ca);
					}
				}
			//}
		}
		else{
			for(int i=0;i<N;i++){
				int x1=SegData[i].x1;
				int x2=SegData[i].x2;
				int	y =SegData[i].y ;

				if(y<0 || y>=m->height()){
					continue;
				}
				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=x1;
				for(int x=x1;x<=x2;x++,dst++){
					*dst=qRgba(	 Clipping((((cr-qRed(*dst))*ca)>>8)+qRed(*dst),0,255)
								,Clipping((((cg-qGreen(*dst))*ca)>>8)+qGreen(*dst),0,255)
								,Clipping((((cb-qBlue(*dst))*ca)>>8)+qBlue(*dst),0,255)
								,ca);
				}
			}
		}
		if(SegData!=SegDataDim){
			delete	[]SegData;
		}
	}
	else{
		if(MultiThreadMode==true && Len>=24){
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for(int i=0;i<Len;i++){
					int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
					int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
					int	y1=(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
					int	y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

					if(y2<0 || y1>=m->height()){
						continue;
					}
					if(x1>=m->width()){
						continue;
					}
					if(x2<0){
						continue;
					}
					if(x1>x2){
						continue;
					}
					if(x1<0){
						x1=0;
					}
					if(x2>=m->width()){
						x2=m->width()-1;
					}

					for(int y=y1;y<y2;y++){
						if(y<0){
							continue;
						}
						if(y>=m->height()){
							break;
						}
						QRgb *dst=(QRgb *)m->scanLine(y);
						dst+=x1;
						for(int x=x1;x<=x2;x++,dst++){
							*dst=qRgba(	 Clipping((((cr-qRed(*dst))*ca)>>8)+qRed(*dst),0,255)
										,Clipping((((cg-qGreen(*dst))*ca)>>8)+qGreen(*dst),0,255)
										,Clipping((((cb-qBlue(*dst))*ca)>>8)+qBlue(*dst),0,255)
										,ca);
						}
					}
				}
			//}
		}
		else{
			for(int i=0;i<Len;i++){
				int x1=(GetFLineLeftX (i)+dx+movx)*ZoomRate;
				int x2=(GetFLineRightX(i)+dx+movx)*ZoomRate;
				int	y1=(GetFLineAbsY  (i)+dy+movy)*ZoomRate;
				int	y2=(GetFLineAbsY(i)+1+dy+movy)*ZoomRate;

				if(y2<0 || y1>=m->height()){
					continue;
				}
				if(x1>=m->width()){
					continue;
				}
				if(x2<0){
					continue;
				}
				if(x1>x2){
					continue;
				}
				if(x1<0){
					x1=0;
				}
				if(x2>=m->width()){
					x2=m->width()-1;
				}

				for(int y=y1;y<y2;y++){
					if(y<0){
						continue;
					}
					if(y>=m->height()){
						break;
					}
					QRgb *dst=(QRgb *)m->scanLine(y);
					dst+=x1;
					for(int x=x1;x<=x2;x++,dst++){
						*dst=qRgba(	 Clipping((((cr-qRed(*dst))*ca)>>8)+qRed(*dst),0,255)
									,Clipping((((cg-qGreen(*dst))*ca)>>8)+qGreen(*dst),0,255)
									,Clipping((((cb-qBlue(*dst))*ca)>>8)+qBlue(*dst),0,255)
									,ca);
					}
				}
			}
		}
	}
	return true;
}

double	FlexArea::GetVar(int dx ,int dy,ImageBuffer &bufftop
					,double &DAvr)	const
{
	int64	D=0;
	uint	Avr=0;
	uchar	*p1;
	int 	N=0;
	int		tMaxX=bufftop.GetWidth();
	int		tMaxY=bufftop.GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int y =GetFLineAbsY(i)+dy;
		if(y<0)
			continue;
		if(tMaxY<=y)
			break;
		int	x1=GetFLineLeftX(i)+dx;
		int	x2=GetFLineRightX(i)+dx;
		if(x1<0)
			x1=0;
		if(tMaxX<=x2)
			x2=tMaxX;
		int	Numb=x2-x1;
		p1=bufftop.GetY(y)+x1;

		if(Numb>0){
			uint	Dtmp=0;
			for(int x=0;x<Numb;x++ ,p1++){
				Avr+= *p1;
				Dtmp+=(*p1)*(*p1);
			}
			D+=Dtmp;
			N +=Numb;
		}
	}
	if(N<=0)
		return 0;
	DAvr=(double)Avr/(double)N;

	double	DD=(double)D/(double)N;
	DD=DD-DAvr*DAvr;
	if(DD<0){
		return(0);
	}

	DD=sqrt(DD);

	return(DD);
}

double  FlexArea::GetVarByDiffMaster(int dx ,int dy
									,ImageBuffer &TargetBuff
									,ImageBuffer &MasterBuff
									,double &DAvr)          const
{
	uint	D=0;
	uint	Avr=0;
	uchar	*p1;
	uchar	*p2;
	int 	N=0;
	int		tMaxX=TargetBuff.GetWidth();
	int		tMaxY=TargetBuff.GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int my =GetFLineAbsY(i);
		int ty =my+dy;
		if(ty<0)
			continue;
		if(tMaxY<=ty)
			break;
		int	mx1=GetFLineLeftX(i);
		int	mx2=GetFLineRightX(i);
		int	tx1=mx1+dx;
		int	tx2=mx2+dx;
		if(tx1<0)
			tx1=0;
		if(tMaxX<=tx2)
			tx2=tMaxX;
		if(mx1<0)
			mx1=0;
		if(tMaxX<=mx2)
			mx2=tMaxX;
		int	tNumb=tx2-tx1;
		int	mNumb=mx2-mx1;
		int	Numb=min(tNumb,mNumb);
		p1=TargetBuff.GetY(ty)+tx1;
		p2=MasterBuff.GetY(my)+mx1;

		if(Numb>0){
			for(int x=0;x<Numb;x++ ,p1++,p2++){
				int	c=*p1 - *p2;
				Avr+= c;
				D+=c*c;
			}
			N +=Numb;
		}
	}
	if(N<=0)
		return 0;
	DAvr=(double)Avr/(double)N;

	double	DD=(double)D/(double)N;
	DD=DD-DAvr*DAvr;
	if(DD<0){
		return(0);
	}

	DD=sqrt(DD);

	return(DD);
}

bool	FlexArea::CalcAvrVar(int dx,int dy,ImageBuffer &buff,double &Avr ,double &Var
							 ,double AdoptRateL,double AdoptRateH
							 ,int AreaX1,int AreaY1 ,int AreaX2 ,int AreaY2)	const
{
	int		tMaxX=buff.GetWidth();
	int		tMaxY=buff.GetHeight();
	int	CTable[256];
	AreaX2	=min(AreaX2,tMaxX);
	AreaY2	=min(AreaY2,tMaxY);

	int	YSep=1;
	int	XSep=1;
	int	YSize=min(GetHeight(),AreaY2-AreaY1);
	int	XSize=min(GetWidth() ,AreaX2-AreaX1);
	if(YSize>200){
		YSep=5;
	}
	else if(YSize>100){
		YSep=3;
	}
	else if(YSize>50){
		YSep=2;
	}
	if(XSize>200){
		XSep=5;
	}
	else if(XSize>100){
		XSep=3;
	}
	else if(XSize>50){
		XSep=2;
	}

	memset(CTable,0,sizeof(CTable));
	int	DotCount=0;
	for(int i=0;i<GetFLineLen();i++){
		int y =GetFLineAbsY(i)+dy;
		if(y<AreaY1 || AreaY2<=y){
			continue;
		}
		if((y%YSep)!=0){
			continue;
		}
		int	x1=max(GetFLineLeftX(i)+dx,AreaX1);
		int	x2=min(GetFLineRightX(i)+dx,AreaX2);
		int	Numb=x2-x1;
		if(Numb<=0){
			continue;
		}
		BYTE	*p=buff.GetY(y)+x1;

		for(int x=0;x<Numb;x+=XSep ,p+=XSep){
			CTable[*p]++;
			DotCount++;
		}
	}
	int	AbandanDotL=(1.0-AdoptRateL)*DotCount/2;
	int	AbandanDotH=(1.0-AdoptRateH)*DotCount/2;
	int	L1;
	int	L2;
	int	D=0;
	for(L1=0;L1<256;L1++){
		if(D+CTable[L1]>=AbandanDotL){
			break;
		}
		D+=CTable[L1];
	}
	D=0;
	for(L2=255;L2>=0;L2--){
		if(D+CTable[L2]>=AbandanDotH){
			break;
		}
		D+=CTable[L2];
	}
	DotCount=0;
	double	A=0;
	double	A2=0;
	for(int i=L1;i<=L2 && i<256;i++){
		DotCount+=CTable[i];
		A+=((double)i)*((double)CTable[i]);
		A2+=((double)i*i)*((double)CTable[i]);
	}
	if(DotCount==0){
		return false;
	}
	Avr=A/DotCount;
	Var=(A2 - DotCount*Avr*Avr)/DotCount;
	return true;
}

bool	FlexArea::CalcAvrVar(int dx,int dy,ImageBuffer &buff,double &Avr ,double &Var
							 , BYTE **EffectiveMaskMap
							 , double AdoptRateL	,double AdoptRateH
							 , int AreaX1,int AreaY1 ,int AreaX2,int AreaY2)	const
{
	int		tMaxX=buff.GetWidth();
	int		tMaxY=buff.GetHeight();
	int	CTable[256];
	AreaX2	=min(AreaX2,tMaxX);
	AreaY2	=min(AreaY2,tMaxY);

	int	YSep=1;
	int	XSep=1;
	int	YSize=min(GetHeight(),AreaY2-AreaY1);
	int	XSize=min(GetWidth() ,AreaX2-AreaX1);
	if(YSize>200){
		YSep=5;
	}
	else if(YSize>100){
		YSep=3;
	}
	else if(YSize>50){
		YSep=2;
	}
	if(XSize>200){
		XSep=5;
	}
	else if(XSize>100){
		XSep=3;
	}
	else if(XSize>50){
		XSep=2;
	}

	memset(CTable,0,sizeof(CTable));
	int	DotCount=0;
	for(int i=0;i<GetFLineLen();i++){
		int y =GetFLineAbsY(i)+dy;
		if(y<AreaY1 || AreaY2<=y){
			continue;
		}
		if((y%YSep)!=0){
			continue;
		}
		int	x1=max(GetFLineLeftX(i)+dx,AreaX1);
		int	x2=min(GetFLineRightX(i)+dx,AreaX2);
		int	Numb=x2-x1;
		if(Numb<=0){
			continue;
		}
		BYTE	*m=EffectiveMaskMap[y];
		BYTE	*p=buff.GetY(y)+x1;

		for(int x=0;x<Numb;x+=XSep ,p+=XSep){
			int	X=x1+x;
			if((m[X>>3] & (0x80>>(X&7)))!=0){
				CTable[*p]++;
				DotCount++;
			}
		}
	}
	int	AbandanDotL=(1.0-AdoptRateL)*DotCount/2;
	int	AbandanDotH=(1.0-AdoptRateH)*DotCount/2;
	int	L1;
	int	L2;
	int	D=0;
	for(L1=0;L1<256;L1++){
		if(D+CTable[L1]>=AbandanDotL){
			break;
		}
		D+=CTable[L1];
	}
	D=0;
	for(L2=255;L2>=0;L2--){
		if(D+CTable[L2]>=AbandanDotH){
			break;
		}
		D+=CTable[L2];
	}
	DotCount=0;
	double	A=0;
	double	A2=0;
	for(int i=L1;i<=L2 && i<256;i++){
		DotCount+=CTable[i];
		A+=((double)i)*((double)CTable[i]);
		A2+=((double)i*i)*((double)CTable[i]);
	}
	if(DotCount==0){
		return false;
	}
	Avr=A/DotCount;
	Var=(A2 - DotCount*Avr*Avr)/DotCount;
	return true;
}


double	FlexArea::GetVar(int mx1 ,int my1 ,int mx2 ,int my2
					,ImageBuffer &bufftop ,double &DAvr)	const
{
	int		tMaxX=bufftop.GetWidth();
	int		tMaxY=bufftop.GetHeight();
	mx2	=min(mx2,tMaxX);
	my2	=min(my2,tMaxY);

	uint	D=0;
	uint	Avr=0;
	uchar	*p1;
	int 	N=0;

	for(int i=0;i<GetFLineLen();i++){
		int y  =GetFLineAbsY (i);
		int tx1=GetFLineLeftX(i);
		int tx2=GetFLineRightX(i);
		if(my1<=y && y<my2 && mx1<tx1 && mx2>tx1){
			if(mx1>tx1){
				tx1=mx1;
			}
			if(mx2<tx2){
				tx2=mx2;
			}
			int L=tx2-tx1;
			p1=bufftop.GetY(y)+(int)tx1;

			for(int x=0;x<L;x++ ,p1++){
				Avr+= *p1;
				D+=(*p1)*(*p1);
				}
			N +=L;
			}
		}
	DAvr=(double)Avr/(double)N;

	double	DD=(double)D/(double)N;
	DD=DD-DAvr*DAvr;
	if(DD<0){
		return(0);
	}

	DD=sqrt(DD);

	return(DD);
}

void	FlexArea::EnSmoothing(ImageBuffer &dstbuff)
{
	int bottomy=GetFLineAbsY(GetFLineLen()-1);
	for(int i=0;i<GetFLineLen();i++){
		int y =GetFLineAbsY(i);
		if(bottomy-1==y){
			break;
		}
		uchar	*p1=dstbuff.GetY(y)+GetFLineLeftX(i);
		for(int x=0;x<GetFLineNumb(i)-1;x++ ,p1++){
			*p1=(uchar)( (((uint)*(dstbuff.GetY(y  )+GetFLineLeftX(i)  ))
						+ ((uint)*(dstbuff.GetY(y  )+GetFLineLeftX(i)+1))
						+ ((uint)*(dstbuff.GetY(y+1)+GetFLineLeftX(i)  ))
						+ ((uint)*(dstbuff.GetY(y+1)+GetFLineLeftX(i)+1)))>>2);
			}
		}
	dstbuff.SetChanged();
}
static	uchar	LogTable[256];
static	bool	InitializedLogTable=false;

void	FlexArea::EnLogtrans (ImageBuffer &dstbuff)
{
	if(InitializedLogTable==false){
		for(int i=0;i<256;i++){
			int m=(int)(log((double)(i+1))/log(2.0)*32.0);
			if(m>=256){
				LogTable[i]=(uchar)255;
			}
			else{
				LogTable[i]=(uchar)m;
			}
		}
		InitializedLogTable=true;
	}
	int bottomy=GetFLineAbsY(GetFLineLen()-1);
	for(int i=0;i<GetFLineLen();i++){
		int y =GetFLineAbsY(i);
		if(bottomy-1==y){
			break;
		}
		uchar	*p1=dstbuff.GetY(y)+GetFLineLeftX(i);
		for(int x=0;x<GetFLineNumb(i)-1;x++ ,p1++){
			*p1=LogTable[*p1];
		}
	}
	dstbuff.SetChanged();
}

void	FlexArea::CreateRGBStock(ImagePointerContainer &Images, RGBStock &Stocker,int movx ,int movy)
{
	int	BitNumb=8;
	int	ColorWord=1<<BitNumb;
	Stocker.RemoveAll();
	if(Images.GetNumber()==3){
		int	NLen=GetFLineLen();
		ImageBuffer	*RBuff=Images.GetItem(0)->GetImage();
		ImageBuffer	*GBuff=Images.GetItem(1)->GetImage();
		ImageBuffer	*BBuff=Images.GetItem(2)->GetImage();
		int	LNumb=ColorWord*ColorWord*ColorWord;
		int	XLen=min(min(RBuff->GetWidth() ,GBuff->GetWidth()) ,BBuff->GetWidth());
		int	YLen=min(min(RBuff->GetHeight(),GBuff->GetHeight()),BBuff->GetHeight());
		BYTE	*GTable=new BYTE[LNumb];
		memset(GTable,0,LNumb);

		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<NLen;i++){
				int x1=GetFLineLeftX (i)+movx;
				int x2=GetFLineRightX(i)+movx;
				int y =GetFLineAbsY  (i)+movy;
				if(x1<0){
					x1=0;
				}
				if(x1>XLen){
					x1=XLen;
				}
				if(x2<0){
					x2=0;
				}
				if(x2>XLen){
					x2=XLen;
				}
				if(0<=y && y<YLen){
					BYTE	*pR=RBuff->GetY(y)+x1;
					BYTE	*pG=GBuff->GetY(y)+x1;
					BYTE	*pB=BBuff->GetY(y)+x1;

					for(int x=x1;x<x2;x++,pR++,pG++,pB++){
						GTable[((*pR)<<16)+((*pG)<<8)+(*pB)]=1;
					}
				}
			}
		}
		for(int i=0;i<LNumb;i++){
			if(GTable[i]!=0){
				int	r=(i>>16)&0xFF;
				int	g=(i>>8)&0xFF;
				int	b=i&0xFF;
				QRgb	d=qRgb(r,g,b);
				RGBSample *sc=new RGBSample(d,1);
				Stocker.AppendList(sc);
			}
		}
		delete	[]GTable;
	}
	else if(Images.GetNumber()==2){
		int	NLen=GetFLineLen();
		ImageBuffer	*RBuff=Images.GetItem(0)->GetImage();
		ImageBuffer	*GBuff=Images.GetItem(1)->GetImage();
		int	XLen=min(RBuff->GetWidth() ,GBuff->GetWidth());
		int	YLen=min(RBuff->GetHeight(),GBuff->GetHeight());
		int	LNumb=256*256;
		BYTE	*GTable=new BYTE[LNumb];
		memset(GTable,0,LNumb);
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<NLen;i++){
				int x1=GetFLineLeftX (i)+movx;
				int x2=GetFLineRightX(i)+movx;
				int y =GetFLineAbsY  (i)+movy;

				if(x1<0){
					x1=0;
				}
				if(x1>XLen){
					x1=XLen;
				}
				if(x2<0){
					x2=0;
				}
				if(x2>XLen){
					x2=XLen;
				}
				if(0<=y && y<YLen){
					BYTE	*pR=RBuff->GetY(y)+x1;
					BYTE	*pG=GBuff->GetY(y)+x1;

					for(int x=x1;x<x2;x++,pR++,pG++){
						GTable[(*pR)*256+(*pG)]=1;
					}
				}
			}
		}
		for(int i=0;i<LNumb;i++){
			if(GTable[i]!=0){
				int	r=(i>>8)&0xFF;
				int	g=(i)&0xFF;
				QRgb	d=qRgb(r,g,g);
				RGBSample *sc=new RGBSample(d,1);
				Stocker.AppendList(sc);
			}
		}
		delete	[]GTable;
	}
	else if(Images.GetNumber()==1){
		int	NLen=GetFLineLen();
		ImageBuffer	*RBuff=Images.GetItem(0)->GetImage();
		int	XLen=RBuff->GetWidth();
		int	YLen=RBuff->GetHeight();
		int	LNumb=256;
		BYTE	*GTable=new BYTE[LNumb];
		memset(GTable,0,LNumb);
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<NLen;i++){
				int x1=GetFLineLeftX (i)+movx;
				int x2=GetFLineRightX(i)+movx;
				int y =GetFLineAbsY  (i)+movy;

				if(x1<0){
					x1=0;
				}
				if(x1>XLen){
					x1=XLen;
				}
				if(x2<0){
					x2=0;
				}
				if(x2>XLen){
					x2=XLen;
				}
				if(0<=y && y<YLen){
					BYTE	*pR=RBuff->GetY(y)+x1;

					for(int x=x1;x<x2;x++,pR++){
						GTable[(*pR)]=1;
					}
				}
			}
		}
		for(int i=0;i<LNumb;i++){
			if(GTable[i]!=0){
				int	r=i&0xFF;
				QRgb	d=qRgb(r,r,r);
				RGBSample *sc=new RGBSample(d,1);
				Stocker.AppendList(sc);
			}
		}
		delete	[]GTable;
	}
}

struct	FlexAreaCreateZoom
{
	int	X1,X2;
};

void	FlexArea::CreateZoom(double ZoomRate ,int Cx,int Cy)
{
	int	NLen=GetFLineLen();
	if(ZoomRate<=1.0){
		int	LastY= -99999999;
		struct	FlexAreaCreateZoom	LastXLine[1000];
		int	LastXNumb=0;
		struct FlexLine *FL=new struct FlexLine[NLen];
		int	FLNumb=0;
		for(int i=0;i<NLen;i++){
			int x1=GetFLineLeftX (i);
			int x2=GetFLineRightX(i);
			int y =GetFLineAbsY  (i);
			x1=(x1-Cx)*ZoomRate+Cx;
			x2=(x2-Cx)*ZoomRate+Cx;
			y =(y -Cy)*ZoomRate+Cy;
			if(y!=LastY){
				if(LastY!=-99999999){
					for(int j=0;j<LastXNumb;j++){
						FL[FLNumb]._SetAbsY(LastY);
						FL[FLNumb]._SetLeftX(LastXLine[j].X1);
						FL[FLNumb].SetNumb(LastXLine[j].X2-LastXLine[j].X1);
						FLNumb++;
					}
				}
				LastY=y;
				LastXLine[0].X1=x1;
				LastXLine[0].X2=x2;
				LastXNumb=1;
			}
			else{
				LastXLine[LastXNumb].X1=x1;
				LastXLine[LastXNumb].X2=x2;
				LastXNumb++;
				for(int j=0;j<LastXNumb-1;j++){
					for(int k=j+1;k<LastXNumb;){
						if(LastXLine[j].X1<=LastXLine[k].X1 && LastXLine[k].X1<=LastXLine[j].X2){
							if(LastXLine[k].X2<=LastXLine[j].X2){
								memmove(&LastXLine[k],&LastXLine[k+1],sizeof(LastXLine[0])*(LastXNumb-k));
								LastXNumb--;
								goto	SkipKPP1;
							}
							else{
								LastXLine[j].X2=LastXLine[k].X2;
								memmove(&LastXLine[k],&LastXLine[k+1],sizeof(LastXLine[0])*(LastXNumb-k));
								LastXNumb--;
								goto	SkipKPP1;
							}
						}
						else if(LastXLine[k].X1<=LastXLine[j].X1 && LastXLine[j].X1<=LastXLine[k].X2){
							LastXLine[j].X1=LastXLine[k].X1;
							if(LastXLine[k].X2<=LastXLine[j].X2){
								memmove(&LastXLine[k],&LastXLine[k+1],sizeof(LastXLine[0])*(LastXNumb-k));
								LastXNumb--;
								goto	SkipKPP1;
							}
							else{
								LastXLine[j].X2=LastXLine[k].X2;
								memmove(&LastXLine[k],&LastXLine[k+1],sizeof(LastXLine[0])*(LastXNumb-k));
								LastXNumb--;
								goto	SkipKPP1;
							}
						}
						k++;
SkipKPP1:;
					}
				}
			}
		}
		if(LastY!=-99999999){
			for(int j=0;j<LastXNumb;j++){
				FL[FLNumb]._SetAbsY(LastY);
				FL[FLNumb]._SetLeftX(LastXLine[j].X1);
				FL[FLNumb].SetNumb(LastXLine[j].X2-LastXLine[j].X1);
				FLNumb++;
			}
		}
		SetFLine(FL,FLNumb);
	}
	else{
		struct FlexLine *FL=new struct FlexLine[NLen*(int)ceil(ZoomRate)];
		int	FLNumb=0;
		for(int i=0;i<NLen;i++){
			int x1=GetFLineLeftX (i);
			int x2=GetFLineRightX(i);
			int yn=GetFLineAbsY  (i);
			x1=(x1-Cx)*ZoomRate+Cx;
			x2=(x2-Cx)*ZoomRate+Cx;
			int	y1=(yn -Cy)*ZoomRate+Cy;
			int	y2=(yn+1 -Cy)*ZoomRate+Cy;
			int	YNumb=y2-y1;
			if(YNumb==0){
				YNumb=1;
			}

			for(int y=0;y<YNumb;y++){
				FL[FLNumb]._SetAbsY(y1+y);
				FL[FLNumb]._SetLeftX(x1);
				FL[FLNumb].SetNumb(x2-x1);
				FLNumb++;
			}
		}
		SetFLine(FL,FLNumb);
	}
	Regulate();
}

BYTE	*FlexArea::GetZoomPattern(double ZoomRate,int Cx,int Cy
								,ImageBuffer &Buff,int &BuffBytes)
{
	BYTE	*D=new BYTE[GetPatternByte()*(int)ceil(ZoomRate)*(int)ceil(ZoomRate)*2];
	BuffBytes=0;
	BYTE	*DestPoint=D;

	int	NLen=GetFLineLen();
	if(ZoomRate<=1.0){
		int	LastY= -99999999;
		struct	FlexAreaCreateZoom	LastXLine[1000];
		int	LastXNumb=0;
		struct FlexLine *FL=new struct FlexLine[NLen];
		int	FLNumb=0;
		for(int i=0;i<NLen;i++){
			int x1=GetFLineLeftX (i);
			int x2=GetFLineRightX(i);
			int sy =GetFLineAbsY  (i);
			x1=(x1-Cx)*ZoomRate+Cx;
			x2=(x2-Cx)*ZoomRate+Cx;
			int	y =(sy -Cy)*ZoomRate+Cy;
			if(y!=LastY){
				if(LastY!=-99999999){
					for(int j=0;j<LastXNumb;j++){
						FL[FLNumb]._SetAbsY(LastY);
						FL[FLNumb]._SetLeftX(LastXLine[j].X1);
						FL[FLNumb].SetNumb(LastXLine[j].X2-LastXLine[j].X1);
						if(0<=y && y<Buff.GetHeight()){
							BYTE	*SrcPoint=Buff.GetY(y);
							for(int x=LastXLine[j].X1;x<LastXLine[j].X2;x++){
								int	sx=(x-Cx)/ZoomRate+Cx;
								if(0<=sx && sx<Buff.GetWidth()){
									*DestPoint=SrcPoint[sx];
									DestPoint++;
								}
							}
						}
						FLNumb++;
					}
				}
				LastY=y;
				LastXLine[0].X1=x1;
				LastXLine[0].X2=x2;
				LastXNumb=1;
			}
			else{
				LastXLine[LastXNumb].X1=x1;
				LastXLine[LastXNumb].X2=x2;
				LastXNumb++;
				for(int j=0;j<LastXNumb-1;j++){
					for(int k=j+1;k<LastXNumb;){
						if(LastXLine[j].X1<=LastXLine[k].X1 && LastXLine[k].X1<=LastXLine[j].X2){
							if(LastXLine[k].X2<=LastXLine[j].X2){
								memmove(&LastXLine[k],&LastXLine[k+1],sizeof(LastXLine[0])*(LastXNumb-k));
								LastXNumb--;
								goto	SkipKPP1;
							}
							else{
								LastXLine[j].X2=LastXLine[k].X2;
								memmove(&LastXLine[k],&LastXLine[k+1],sizeof(LastXLine[0])*(LastXNumb-k));
								LastXNumb--;
								goto	SkipKPP1;
							}
						}
						else if(LastXLine[k].X1<=LastXLine[j].X1 && LastXLine[j].X1<=LastXLine[k].X2){
							LastXLine[j].X1=LastXLine[k].X1;
							if(LastXLine[k].X2<=LastXLine[j].X2){
								memmove(&LastXLine[k],&LastXLine[k+1],sizeof(LastXLine[0])*(LastXNumb-k));
								LastXNumb--;
								goto	SkipKPP1;
							}
							else{
								LastXLine[j].X2=LastXLine[k].X2;
								memmove(&LastXLine[k],&LastXLine[k+1],sizeof(LastXLine[0])*(LastXNumb-k));
								LastXNumb--;
								goto	SkipKPP1;
							}
						}
						k++;
SkipKPP1:;
					}
				}
			}
		}
		if(LastY!=-99999999){
			for(int j=0;j<LastXNumb;j++){
				FL[FLNumb]._SetAbsY(LastY);
				FL[FLNumb]._SetLeftX(LastXLine[j].X1);
				FL[FLNumb].SetNumb(LastXLine[j].X2-LastXLine[j].X1);
				int	y=(LastY-Cy)/ZoomRate+Cy;
				if(0<=y && y<Buff.GetHeight()){
					BYTE	*SrcPoint=Buff.GetY(y);
					for(int x=LastXLine[j].X1;x<LastXLine[j].X2;x++){
						int	sx=(x-Cx)/ZoomRate+Cx;
						if(0<=sx && sx<Buff.GetWidth()){
							*DestPoint=SrcPoint[sx];
							DestPoint++;
						}
					}
				}
				FLNumb++;
			}
		}
		SetFLine(FL,FLNumb);
	}
	else{
		struct FlexLine *FL=new struct FlexLine[NLen*(int)ceil(ZoomRate)];
		int	FLNumb=0;
		for(int i=0;i<NLen;i++){
			int xn1=GetFLineLeftX (i);
			int xn2=GetFLineRightX(i);
			int yn=GetFLineAbsY  (i);
			int	x1=(xn1-Cx)*ZoomRate+Cx;
			int	x2=(xn2-Cx)*ZoomRate+Cx;
			int	y1=(yn -Cy)*ZoomRate+Cy;
			int	y2=(yn+1 -Cy)*ZoomRate+Cy;
			int	YNumb=y2-y1;
			if(YNumb==0){
				YNumb=1;
			}

			for(int y=0;y<YNumb;y++){
				FL[FLNumb]._SetAbsY(y1+y);
				FL[FLNumb]._SetLeftX(x1);
				FL[FLNumb].SetNumb(x2-x1);
				if(0<=yn && yn<Buff.GetHeight()){
					BYTE	*SrcPoint=Buff.GetY(yn);
					for(int x=x1;x<x2;x++){
						int	sx=(x-Cx)/ZoomRate+Cx;
						if(0<=sx && sx<Buff.GetWidth()){
							*DestPoint=SrcPoint[sx];
							DestPoint++;
						}
					}
				}
				FLNumb++;
			}
		}
		SetFLine(FL,FLNumb);
	}
	Regulate();
	BuffBytes=DestPoint-D;
	return D;
}

void	FlexArea::RegulateBrightness(ImageBuffer &IBuff ,double Average ,double Deviation , int CellSize
									 ,double AdoptRateL,double AdoptRateH)
{
	int	CalcSize=CellSize*2;

	int	W=GetWidth();
	int	H=GetHeight();

	int	WCount=(W+CellSize-1)/CellSize;
	int	HCount=(H+CellSize-1)/CellSize;

	struct	ShaderStruct
	{
		double	Avr;
		double	Var;
		int		Ax1,Ay1,Ax2,Ay2;
	}*SDim;

	SDim=new struct	ShaderStruct[WCount*HCount];

	#pragma omp parallel
	{
		#pragma omp for
		for(int h=0;h<HCount;h++){
			for(int w=0;w<WCount;w++){
				int	rx1=w*CellSize+GetMinX();
				int	ry1=h*CellSize+GetMinY();
				int	rx2=rx1+CellSize;
				int	ry2=ry1+CellSize;
				if(rx2>IBuff.GetWidth())
					rx2=IBuff.GetWidth();
				if(ry2>IBuff.GetHeight())
					ry2=IBuff.GetHeight();

				int	kx1=rx1-(CalcSize-CellSize)/2;
				int	ky1=ry1-(CalcSize-CellSize)/2;
				int	kx2=rx2+(CalcSize-CellSize)/2;
				int	ky2=ry2+(CalcSize-CellSize)/2;

				if(kx1<0){
					kx2-=kx1;
					kx1=0;
				}
				if(ky1<0){
					ky2-=ky1;
					ky1=0;
				}
				if(kx2>=IBuff.GetWidth()){
					kx1-=kx2-IBuff.GetWidth();
					kx2=IBuff.GetWidth();
				}
				if(ky2>=IBuff.GetHeight()){
					ky1-=ky2-IBuff.GetHeight();
					ky2=IBuff.GetHeight();
				}

				int	Index=h*WCount+w;
				struct	ShaderStruct	*R= &SDim[Index];
				R->Ax1=rx1;
				R->Ay1=ry1;
				R->Ax2=rx2;
				R->Ay2=ry2;

				CalcAvrVar(0,0,IBuff,R->Avr,R->Var
									,AdoptRateL,AdoptRateH
									,kx1,ky1,kx2,ky2);
				R->Var=sqrt(R->Var);
			}
		}
	}

	int	NLen=GetFLineLen();
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<NLen;i++){
			int x1=GetFLineLeftX (i);
			int x2=GetFLineRightX(i);
			int y =GetFLineAbsY  (i);
			int	h=(y-GetMinY())/CellSize;
			BYTE	*p=IBuff.GetY(y)+x1;
			for(int x=x1;x<x2;x++,p++){
				int	w=(x-GetMinX())/CellSize;
				int	Index=h*WCount+w;
				struct	ShaderStruct	*R= &SDim[Index];

				double	MulVar;
				if(R->Var>0)
					MulVar=Deviation/R->Var;
				else
					MulVar=1.0;
				int	d=((*p)-R->Avr)*MulVar+Average;
				if(d<0)
					*p=0;
				else if(d<256)
					*p=d;
				else{
					*p=255;
				}
			}
		}
	}
	delete	[]SDim;
}

void	FlexArea::Multiply(double m)
{
	int	W=GetWidth()*m+16;
	int	H=GetHeight()*m+16;
	int	WByte=(W+7)/8;

	int	OffX=GetMinX()-8;
	int	OffY=GetMinY()-8;

	BYTE	BmpMapBuff[10000];
	BYTE	**BmpMap=MakeMatrixBuff(WByte,H,BmpMapBuff,sizeof(BmpMapBuff));
	MatrixBuffClear(BmpMap ,0,WByte,H);

	double	Mp=1.0/m;
	for(int y=0;y<H;y++){
		int	py=y*Mp+OffY;
		BYTE	*d=BmpMap[y];
		for(int x=0;x<W;x++){
			int	px=x*Mp+OffX;
			if(IsInclude(px ,py)==true){
				d[x>>3] |= 0x80>>(x&7);
			}
		}
	}
	BuildFromRaster(BmpMap ,WByte,H
					,OffX*m,OffY*m);
	if(BmpMap!=(BYTE **)BmpMapBuff){
		DeleteMatrixBuff(BmpMap ,H);
	}
}

double	FlexArea::GetCoeff(ImageBuffer &Src ,int dx ,int dy 
							,ImageBuffer &Dst
							,int Isolation ,bool ThreadMode)	const
{
	double	SumS=0;
	double	SumD=0;
	double	SumSS=0;
	double	SumDD=0;
	double	SumSD=0;
	int		SDCount=0;

	int	NLen=GetFLineLen();
	if(ThreadMode==true){
		if(Isolation<=1){
			#pragma omp parallel for reduction(+:SDCount,SumS,SumD,SumSS,SumDD,SumSD)
			for(int i=0;i<NLen;i++){
				int SrcX1=GetFLineLeftX (i);
				int SrcX2=GetFLineRightX(i);
				int SrcY =GetFLineAbsY	(i);
	
				int DstX1=SrcX1+dx;
				int DstX2=SrcX2+dx;
				int	DstY =SrcY +dy;
	
				if(SrcY<0 || SrcY>=Src.GetHeight()	|| DstY<0 || DstY>=Dst.GetHeight()){
					continue;
				}
				if(SrcX2<0 || SrcX1>=Src.GetWidth()	|| DstX2<0 || DstX1>=Dst.GetWidth()){
					continue;
				}
				if(SrcX1<0){
					SrcX1=0;
				}
				if(DstX1<0){
					SrcX1-=DstX1;
					DstX1=0;
				}
				if(SrcX2>Src.GetWidth()){
					SrcX2=Src.GetWidth();
				}
				if(DstX2>Dst.GetWidth()){
					DstX2=Dst.GetWidth();
				}
	
				BYTE	*s=&Src.GetY(SrcY)[SrcX1];
				BYTE	*d=&Dst.GetY(DstY)[DstX1];
				int	tSumS=0;
				int	tSumD=0;
				int	tSumSS=0;
				int	tSumDD=0;
				int	tSumSD=0;
				int	numb=min(SrcX2-SrcX1,DstX2-DstX1);
				if(numb>0){
					for(int k=0;k<numb;k++){
						int	a=*s;
						s++;
						int	b=*d;
						d++;
						tSumS	+=a;
						tSumSS	+=a*a;
						tSumD	+=b;
						tSumDD	+=b*b;
						tSumSD	+=a*b;
					}
					SDCount+=numb;
				}
				SumS+=tSumS;
				SumD+=tSumD;
				SumSS+=tSumSS;
				SumDD+=tSumDD;
				SumSD+=tSumSD;
			}
		}
		else{
			#pragma omp parallel for reduction(+:SDCount,SumS,SumD,SumSS,SumDD,SumSD)
			for(int i=0;i<NLen;i++){
				int SrcX1=GetFLineLeftX (i);
				int SrcX2=GetFLineRightX(i);
				int SrcY =GetFLineAbsY	(i);
				if((SrcY%Isolation)!=0)
					continue;
	
				int DstX1=SrcX1+dx;
				int DstX2=SrcX2+dx;
				int	DstY =SrcY +dy;
	
				if(SrcY<0 || SrcY>=Src.GetHeight()	|| DstY<0 || DstY>=Dst.GetHeight()){
					continue;
				}
				if(SrcX2<0 || SrcX1>=Src.GetWidth()	|| DstX2<0 || DstX1>=Dst.GetWidth()){
					continue;
				}
				if(SrcX1<0){
					SrcX1=0;
				}
				if(DstX1<0){
					SrcX1-=DstX1;
					DstX1=0;
				}
				if(SrcX2>Src.GetWidth()){
					SrcX2=Src.GetWidth();
				}
				if(DstX2>Dst.GetWidth()){
					DstX2=Dst.GetWidth();
				}
	
				BYTE	*s=Src.GetY(SrcY);
				BYTE	*d=Dst.GetY(DstY);
				int	xs,xd;
				int	tSumS=0;
				int	tSumD=0;
				int	tSumSS=0;
				int	tSumDD=0;
				int	tSumSD=0;
				for(xs=SrcX1,xd=DstX1;xs<SrcX2 && xd<DstX2;xs+=Isolation,xd+=Isolation){
					tSumS	+=s[xs];
					tSumSS	+=((int)s[xs])*((int)s[xs]);
					tSumD	+=d[xd];
					tSumDD	+=((int)d[xd])*((int)d[xd]);
					tSumSD	+=((int)s[xs])*((int)d[xd]);
					SDCount++;
				}
				SumS+=tSumS;
				SumD+=tSumD;
				SumSS+=tSumSS;
				SumDD+=tSumDD;
				SumSD+=tSumSD;
			}
		}
	}
	else{
		if(Isolation<=1){
			for(int i=0;i<NLen;i++){
				int SrcX1=GetFLineLeftX (i);
				int SrcX2=GetFLineRightX(i);
				int SrcY =GetFLineAbsY	(i);
	
				int DstX1=SrcX1+dx;
				int DstX2=SrcX2+dx;
				int	DstY =SrcY +dy;
	
				if(SrcY<0 || SrcY>=Src.GetHeight()	|| DstY<0 || DstY>=Dst.GetHeight()){
					continue;
				}
				if(SrcX2<0 || SrcX1>=Src.GetWidth()	|| DstX2<0 || DstX1>=Dst.GetWidth()){
					continue;
				}
				if(SrcX1<0){
					SrcX1=0;
				}
				if(DstX1<0){
					SrcX1-=DstX1;
					DstX1=0;
				}
				if(SrcX2>Src.GetWidth()){
					SrcX2=Src.GetWidth();
				}
				if(DstX2>Dst.GetWidth()){
					DstX2=Dst.GetWidth();
				}
	
				BYTE	*s=&Src.GetY(SrcY)[SrcX1];
				BYTE	*d=&Dst.GetY(DstY)[DstX1];
				int	tSumS=0;
				int	tSumD=0;
				int	tSumSS=0;
				int	tSumDD=0;
				int	tSumSD=0;
				int	numb=min(SrcX2-SrcX1,DstX2-DstX1);
				if(numb>0){
					for(int k=0;k<numb;k++){
						int	a=*s;
						s++;
						int	b=*d;
						d++;
						tSumS	+=a;
						tSumSS	+=a*a;
						tSumD	+=b;
						tSumDD	+=b*b;
						tSumSD	+=a*b;
					}
					SDCount+=numb;
				}
				SumS+=tSumS;
				SumD+=tSumD;
				SumSS+=tSumSS;
				SumDD+=tSumDD;
				SumSD+=tSumSD;
			}
		}
		else{
			for(int i=0;i<NLen;i++){
				int SrcX1=GetFLineLeftX (i);
				int SrcX2=GetFLineRightX(i);
				int SrcY =GetFLineAbsY	(i);
				if((SrcY%Isolation)!=0)
					continue;
	
				int DstX1=SrcX1+dx;
				int DstX2=SrcX2+dx;
				int	DstY =SrcY +dy;
	
				if(SrcY<0 || SrcY>=Src.GetHeight()	|| DstY<0 || DstY>=Dst.GetHeight()){
					continue;
				}
				if(SrcX2<0 || SrcX1>=Src.GetWidth()	|| DstX2<0 || DstX1>=Dst.GetWidth()){
					continue;
				}
				if(SrcX1<0){
					SrcX1=0;
				}
				if(DstX1<0){
					SrcX1-=DstX1;
					DstX1=0;
				}
				if(SrcX2>Src.GetWidth()){
					SrcX2=Src.GetWidth();
				}
				if(DstX2>Dst.GetWidth()){
					DstX2=Dst.GetWidth();
				}
	
				BYTE	*s=Src.GetY(SrcY);
				BYTE	*d=Dst.GetY(DstY);
				int	xs,xd;
				int	tSumS=0;
				int	tSumD=0;
				int	tSumSS=0;
				int	tSumDD=0;
				int	tSumSD=0;
				for(xs=SrcX1,xd=DstX1;xs<SrcX2 && xd<DstX2;xs+=Isolation,xd+=Isolation){
					tSumS	+=s[xs];
					tSumSS	+=((int)s[xs])*((int)s[xs]);
					tSumD	+=d[xd];
					tSumDD	+=((int)d[xd])*((int)d[xd]);
					tSumSD	+=((int)s[xs])*((int)d[xd]);
					SDCount++;
				}
				SumS+=tSumS;
				SumD+=tSumD;
				SumSS+=tSumSS;
				SumDD+=tSumDD;
				SumSD+=tSumSD;
			}
		}
	}
	if(SDCount==0){
		return 0.0;
	}
	double	AvrS=SumS/SDCount;
	double	AvrD=SumD/SDCount;

	double	D=(SumSS-SDCount*AvrS*AvrS)*(SumDD-SDCount*AvrD*AvrD);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=SumSD-SDCount*AvrS*AvrD;
	return K/D;
}

double  FlexArea::GetDistance(const FlexArea &src)	const
{
	int	Nd=GetFLineLen();
	double	MinD=99999999;
	for(int i=0;i<Nd;i++){
		int	Yd	=GetFLineAbsY(i);
		int	X1	=GetFLineLeftX(i);
		int	Numb=GetFLineNumb(i);
		if(i==0 && i==(Nd-1)){
			for(int n=0;n<Numb;n++){
				double	d=src.GetDistance(X1+n,Yd);
				if(d<MinD){
					MinD=d;
				}
			}
		}
		else{
			double	d1=src.GetDistance(X1,Yd);
			if(d1<MinD){
				MinD=d1;
			}
			double	d2=src.GetDistance(X1+Numb-1,Yd);
			if(d2<MinD){
				MinD=d2;
			}
		}
	}
	return MinD;
}

double  FlexArea::GetDistance(int Xs ,int Ys)	const
{
	int	Nd=GetFLineLen();
	double	MinD=99999999;
	for(int i=0;i<Nd;i++){
		int	Yd	=GetFLineAbsY(i);
		int	X1	=GetFLineLeftX(i);
		int	Numb=GetFLineNumb(i);
		if(i==0 && i==(Nd-1)){
			for(int n=0;n<Numb;n++){
				double	d=hypot(X1+n-Xs,Yd-Ys);
				if(d<MinD){
					MinD=d;
				}
			}
		}
		else{
			double	d1=hypot(X1-Xs,Yd-Ys);;
			if(d1<MinD){
				MinD=d1;
			}
			double	d2=hypot(X1+Numb-1-Xs,Yd-Ys);
			if(d2<MinD){
				MinD=d2;
			}
		}
	}
	return MinD;
}

double	FlexArea::GetCoeff(ImageBuffer &Src ,int dx ,int dy 
							,int CenterX ,int CenterY ,double radian
							,ImageBuffer &Dst,int Isolation ,bool ThreadMode)	const
{
	double	SumS=0;
	double	SumD=0;
	double	SumSS=0;
	double	SumDD=0;
	double	SumSD=0;
	int		SDCount=0;
	double	SinS=sin(radian);
	double	CosS=cos(radian);
	int		DstWidth	=Dst.GetWidth();
	int		DstHeight	=Dst.GetHeight();

	int	NLen=GetFLineLen();
	if(ThreadMode==true){
		if(Isolation<=1){
			#pragma omp parallel for reduction(+:SDCount,SumS,SumD,SumSS,SumDD,SumSD)
			for(int i=0;i<NLen;i++){
				int SrcX1=GetFLineLeftX (i);
				int SrcX2=GetFLineRightX(i);
				int SrcY =GetFLineAbsY	(i);
	
				if(SrcY<0 || SrcY>=Src.GetHeight()){
					continue;
				}
				if(SrcX2<0 || SrcX1>=Src.GetWidth()){
					continue;
				}
				if(SrcX1<0){
					SrcX1=0;
				}
				if(SrcX2>Src.GetWidth()){
					SrcX2=Src.GetWidth();
				}
	
				BYTE	*s=&Src.GetY(SrcY)[SrcX1];
				
				int	tSumS=0;
				int	tSumD=0;
				int	tSumSS=0;
				int	tSumDD=0;
				int	tSumSD=0;
				int	numb=SrcX2-SrcX1;
				if(numb>0){
					double	SinDxY=-(SrcY-CenterY)*SinS+CenterX+dx;
					double	CosDyY= (SrcY-CenterY)*CosS+CenterY+dy;

					for(int k=0;k<numb;k++,s++){
						int	x=SrcX1+k;
						int	DstY=(x-CenterX)*SinS+CosDyY;
						if(DstY<0 || DstY>=DstHeight){
							continue;
						}
						int	DstX=(x-CenterX)*CosS+SinDxY;
						if(0<=DstX && DstX<DstWidth){
							BYTE	*d=&Dst.GetY(DstY)[DstX];
							int	a=*s;
							int	b=*d;
							d++;
							tSumS	+=a;
							tSumSS	+=a*a;
							tSumD	+=b;
							tSumDD	+=b*b;
							tSumSD	+=a*b;
							SDCount++;
						}
					}
				}
				SumS+=tSumS;
				SumD+=tSumD;
				SumSS+=tSumSS;
				SumDD+=tSumDD;
				SumSD+=tSumSD;
			}
		}
		else{
			#pragma omp parallel for reduction(+:SDCount,SumS,SumD,SumSS,SumDD,SumSD)
			for(int i=0;i<NLen;i++){
				int SrcX1=GetFLineLeftX (i);
				int SrcX2=GetFLineRightX(i);
				int SrcY =GetFLineAbsY	(i);
				if((SrcY%Isolation)!=0)
					continue;
	
				if(SrcY<0 || SrcY>=Src.GetHeight()){
					continue;
				}
				if(SrcX2<0 || SrcX1>=Src.GetWidth()){
					continue;
				}
				if(SrcX1<0){
					SrcX1=0;
				}

				if(SrcX2>Src.GetWidth()){
					SrcX2=Src.GetWidth();
				}

				BYTE	*s=Src.GetY(SrcY);
				
				int	xs;
				int	tSumS=0;
				int	tSumD=0;
				int	tSumSS=0;
				int	tSumDD=0;
				int	tSumSD=0;
				double	SinDxY=-(SrcY-CenterY)*SinS+CenterX+dx;
				double	CosDyY= (SrcY-CenterY)*CosS+CenterY+dy;

				for(xs=SrcX1;xs<SrcX2;xs+=Isolation){
					int	DstY=(xs-CenterX)*SinS+CosDyY;
					if(DstY<0 || DstY>=DstHeight){
						continue;
					}
					int	DstX=(xs-CenterX)*CosS+SinDxY;
					if(0<=DstX && DstX<DstWidth){
						BYTE	*d=Dst.GetY(DstY);
						tSumS	+=s[xs];
						tSumSS	+=((int)s[xs])*((int)s[xs]);
						int	D=d[DstX];
						tSumD	+=D;
						tSumDD	+=((int)D)*((int)D);
						tSumSD	+=((int)s[xs])*((int)D);
						SDCount++;
					}
				}
				SumS+=tSumS;
				SumD+=tSumD;
				SumSS+=tSumSS;
				SumDD+=tSumDD;
				SumSD+=tSumSD;
			}
		}
	}
	else{
		if(Isolation<=1){
			for(int i=0;i<NLen;i++){
				int SrcX1=GetFLineLeftX (i);
				int SrcX2=GetFLineRightX(i);
				int SrcY =GetFLineAbsY	(i);
	
				if(SrcY<0 || SrcY>=Src.GetHeight()){
					continue;
				}
				if(SrcX2<0 || SrcX1>=Src.GetWidth()){
					continue;
				}
				if(SrcX1<0){
					SrcX1=0;
				}
				if(SrcX2>Src.GetWidth()){
					SrcX2=Src.GetWidth();
				}
	
				BYTE	*s=&Src.GetY(SrcY)[SrcX1];
				
				int	tSumS=0;
				int	tSumD=0;
				int	tSumSS=0;
				int	tSumDD=0;
				int	tSumSD=0;
				int	numb=SrcX2-SrcX1;
				if(numb>0){
					double	SinDxY=-(SrcY-CenterY)*SinS+CenterX+dx;
					double	CosDyY= (SrcY-CenterY)*CosS+CenterY+dy;
					for(int k=0;k<numb;k++,s++){
						int	x=SrcX1+k;
						int	DstY=(x-CenterX)*SinS+CosDyY;
						if(DstY<0 || DstY>=DstHeight){
							continue;
						}
						int	DstX=(x-CenterX)*CosS+SinDxY;
						if(0<=DstX && DstX<DstWidth){
							BYTE	*d=&Dst.GetY(DstY)[DstX];
							int	a=*s;
							int	b=*d;
							d++;
							tSumS	+=a;
							tSumSS	+=a*a;
							tSumD	+=b;
							tSumDD	+=b*b;
							tSumSD	+=a*b;
							SDCount++;
						}
					}
				}
				SumS+=tSumS;
				SumD+=tSumD;
				SumSS+=tSumSS;
				SumDD+=tSumDD;
				SumSD+=tSumSD;
			}
		}
		else{
			for(int i=0;i<NLen;i++){
				int SrcX1=GetFLineLeftX (i);
				int SrcX2=GetFLineRightX(i);
				int SrcY =GetFLineAbsY	(i);
				if((SrcY%Isolation)!=0)
					continue;
	
				if(SrcY<0 || SrcY>=Src.GetHeight()){
					continue;
				}
				if(SrcX2<0 || SrcX1>=Src.GetWidth()){
					continue;
				}
				if(SrcX1<0){
					SrcX1=0;
				}

				if(SrcX2>Src.GetWidth()){
					SrcX2=Src.GetWidth();
				}

				BYTE	*s=Src.GetY(SrcY);
				
				int	xs;
				int	tSumS=0;
				int	tSumD=0;
				int	tSumSS=0;
				int	tSumDD=0;
				int	tSumSD=0;
				double	SinDxY=-(SrcY-CenterY)*SinS+CenterX+dx;
				double	CosDyY= (SrcY-CenterY)*CosS+CenterY+dy;
				for(xs=SrcX1;xs<SrcX2;xs+=Isolation){
					int	DstY=(xs-CenterX)*SinS+CosDyY;
					if(DstY<0 || DstY>=DstHeight){
						continue;
					}
					int	DstX=(xs-CenterX)*CosS+SinDxY;
					if(0<=DstX && DstX<DstWidth){
						BYTE	*d=Dst.GetY(DstY);
						tSumS	+=s[xs];
						tSumSS	+=((int)s[xs])*((int)s[xs]);
						int	D=d[DstX];
						tSumD	+=D;
						tSumDD	+=((int)D)*((int)D);
						tSumSD	+=((int)s[xs])*((int)D);
						SDCount++;
					}
				}
				SumS+=tSumS;
				SumD+=tSumD;
				SumSS+=tSumSS;
				SumDD+=tSumDD;
				SumSD+=tSumSD;
			}
		}
	}
	if(SDCount==0){
		return 0.0;
	}
	double	AvrS=SumS/SDCount;
	double	AvrD=SumD/SDCount;

	double	D=(SumSS-SDCount*AvrS*AvrS)*(SumDD-SDCount*AvrD*AvrD);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=SumSD-SDCount*AvrS*AvrD;
	return K/D;
}

int 	 FlexArea::MakeShadeList(double *BrRate ,ImageBuffer &Img ,double Angle)
{
	XYClassCluster XY;

	MakeOutlineDot(XY);
	double	coss=cos(Angle);
	double	sins=sin(Angle);

	double	MinT=99999999;
	double	MaxT=-99999999;
	int	NLen=GetFLineLen();
	for(int i=0;i<NLen;i++){
		int SrcX1=GetFLineLeftX (i);
		int SrcX2=GetFLineRightX(i);
		int Y =GetFLineAbsY  (i);
		for(int X=SrcX1;X<SrcX2;X++){
			double	t=X*coss+Y*sins;
			if(t<MinT){
				MinT=t;
			}
			if(t>MaxT){
				MaxT=t;
			}
		}
	}
	int	iMinT=(int)MinT;
	int	iMaxT=(int)MaxT;
	int	L=iMaxT-iMinT+1;

	int	DotCount[100000];
	for(int i=0;i<L;i++){
		BrRate[i]=0.0;
		DotCount[i]=0;
	}

	for(int i=0;i<NLen;i++){
		int SrcX1=GetFLineLeftX (i);
		int SrcX2=GetFLineRightX(i);
		int Y =GetFLineAbsY  (i);
		BYTE	*s=Img.GetY(Y);
		for(int X=SrcX1;X<SrcX2;X++){
			int	t=(int)(X*coss+Y*sins-MinT);
			BrRate[t]+=s[X];
			DotCount[t]++;
		}
	}
	for(int i=0;i<L;i++){
		if(DotCount[i]>0){
			BrRate[i] /=DotCount[i];
		}
	}
	return L;
}

void	FlexArea::CreateColorLogic(ImagePointerContainer &Images, ColorLogic &CLogic ,int movx ,int movy)
{
	double	CenterCol[100];
	int	k=0;
	for(ImagePointerList *L=Images.GetFirst();L!=NULL;L=L->GetNext(),k++){
		ImageBuffer	*ColBuff=L->GetImage();
		int BrList[256];
		memset(BrList,0,sizeof(BrList));
		MakeBrightList(BrList ,ColBuff->GetWidth(),ColBuff->GetHeight(),*ColBuff,movx ,movy);
		double	ColC=0;
		int		Dots=0;
		for(int i=0;i<256;i++){
			ColC+=BrList[i]*i;
			Dots+=BrList[i];
		}
		CenterCol[k]=ColC/Dots;
	}

	double	LMax=0;
	if(Images.GetCount()>=3){
		ImageBuffer	*RBuff=Images.GetItem(0)->GetImage();
		ImageBuffer	*GBuff=Images.GetItem(1)->GetImage();
		ImageBuffer	*BBuff=Images.GetItem(2)->GetImage();
		for(int i=0;i<GetFLineLen();i++){
			int y =GetFLineAbsY(i);
			BYTE	*pR=RBuff->GetY(y+movy)+GetFLineLeftX(i)+movx;
			BYTE	*pG=GBuff->GetY(y+movy)+GetFLineLeftX(i)+movx;
			BYTE	*pB=BBuff->GetY(y+movy)+GetFLineLeftX(i)+movx;
			for(int x=0;x<GetFLineNumb(i);x++){
				double	L;
				L=(*pR-CenterCol[0])*(*pR-CenterCol[0])
				 +(*pG-CenterCol[1])*(*pG-CenterCol[1])
				 +(*pB-CenterCol[2])*(*pB-CenterCol[2]);
				if(L>LMax){
					LMax=L;
				}
				pR++;
				pG++;
				pB++;
			}
		}
		CLogic.Add(qRgb(CenterCol[0],CenterCol[1],CenterCol[2]) ,sqrt(LMax));
	}
	else if(Images.GetCount()==2){
		ImageBuffer	*RBuff=Images.GetItem(0)->GetImage();
		ImageBuffer	*GBuff=Images.GetItem(1)->GetImage();
		for(int i=0;i<GetFLineLen();i++){
			int y =GetFLineAbsY(i);
			BYTE	*pR=RBuff->GetY(y+movy)+GetFLineLeftX(i)+movx;
			BYTE	*pG=GBuff->GetY(y+movy)+GetFLineLeftX(i)+movx;
			for(int x=0;x<GetFLineNumb(i);x++){
				double	L;
				L=(*pR-CenterCol[0])*(*pR-CenterCol[0])
				 +(*pG-CenterCol[1])*(*pG-CenterCol[1]);
				if(L>LMax){
					LMax=L;
				}
				pR++;
				pG++;
			}
		}
		CLogic.Add(qRgb(CenterCol[0],CenterCol[1],CenterCol[1]) ,sqrt(LMax));
	}
	else if(Images.GetCount()==1){
		ImageBuffer	*RBuff=Images.GetItem(0)->GetImage();
		for(int i=0;i<GetFLineLen();i++){
			int y =GetFLineAbsY(i);
			BYTE	*pR=RBuff->GetY(y+movy)+GetFLineLeftX(i)+movx;
			for(int x=0;x<GetFLineNumb(i);x++){
				double	L;
				L=(*pR-CenterCol[0])*(*pR-CenterCol[0]);
				if(L>LMax){
					LMax=L;
				}
				pR++;
			}
		}
		CLogic.Add(qRgb(CenterCol[0],CenterCol[0],CenterCol[0]) ,sqrt(LMax));
	}
}


void  FlexArea::MakeBitmap(ColorLogic &Color ,int Mergin ,ImagePointerContainer &Images 
						,int MapDx ,int MapDy ,BYTE **DestMap ,int XLen ,int YLen)	const
{
	if(XLen==0){
		XLen=Images[0]->GetWidth();
	}
	if(YLen==0){
		YLen=Images[0]->GetHeight();
	}
	int	SrcXLen=Images[0]->GetWidth();
	int	SrcYLen=Images[0]->GetHeight();

	for(int i=0;i<GetFLineLen();i++){
		int	y=GetFLineAbsY(i);
		if(y<0 || (y+MapDy)>=YLen || y>=SrcYLen){
			continue;
		}
		uchar	*d=DestMap[y+MapDy];
		int nx	=GetFLineLeftX(i);
		int Numb=GetFLineNumb(i);
		if(nx<0){
			Numb+=nx;
			nx=0;
		}
		if((nx+MapDx)<0){
			Numb+=(nx+MapDx);
			nx=-MapDx;
		}
		if((nx+MapDx)>=XLen || nx>=SrcXLen){
			continue;
		}
		if((nx+MapDx+Numb)>=XLen){
			Numb=XLen-(nx+MapDx)-1;
		}
		if((nx+Numb)>=SrcXLen){
			Numb=SrcXLen-nx-1;
		}
		if(Images.GetCount()>=3){
			BYTE	*r=Images[0]->GetY(y)+nx;
			BYTE	*g=Images[1]->GetY(y)+nx;
			BYTE	*b=Images[2]->GetY(y)+nx;
			for(int x=0;x<Numb;x++){
				if(Color.Calc(*r,*g,*b,Mergin)==true){
					SetBmpBitOnY1(d,MapDx+nx+x);
				}
				else{
					SetBmpBitOnY0(d,MapDx+nx+x);
				}
				r++;
				g++;
				b++;
			}
		}
		else if(Images.GetCount()==2){
			BYTE	*r=Images[0]->GetY(y)+nx;
			BYTE	*g=Images[1]->GetY(y)+nx;
			for(int x=0;x<Numb;x++){
				if(Color.Calc(*r,*g,*g,Mergin)==true){
					SetBmpBitOnY1(d,MapDx+nx+x);
				}
				else{
					SetBmpBitOnY0(d,MapDx+nx+x);
				}
				r++;
				g++;
			}
		}
		else if(Images.GetCount()==1){
			BYTE	*r=Images[0]->GetY(y)+nx;
			for(int x=0;x<Numb;x++){
				if(Color.Calc(*r,*r,*r,Mergin)==true){
					SetBmpBitOnY1(d,MapDx+nx+x);
				}
				else{
					SetBmpBitOnY0(d,MapDx+nx+x);
				}
				r++;
			}
		}
	}
}
	
void    FlexArea::PaintWithColor(QImage &Dest, const QRgb &Col,int dx ,int dy)
{
	const	int	XLen=Dest.width();
	const	int	YLen=Dest.height();
	int	N=GetFLineLen();
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<N;i++){
			int x1=GetFLineLeftX (i)+dx;
			int x2=GetFLineRightX(i)+dx;
			int y =GetFLineAbsY  (i)+dy;

			if(y<0 || y>=YLen){
				continue;
			}
			if(x1<0){
				x1=0;
			}
			if(x1>=YLen){
				x1=YLen-1;
			}
			if(x2<0){
				x2=0;
			}
			if(x2>=XLen){
				x2=XLen-1;
			}

			if(x1>x2){
				continue;
			}
			if(x2==0 || x1==(XLen-1)){
				continue;
			}
			QRgb	*p=&((QRgb *)Dest.scanLine(y))[x1];
			for(int x=x1;x<x2;x++){
			   *p=Col;
			   p++;
			}
		}
	}
}


static	BYTE	BitCountTable[]={
 0	//0
,1	//1
,1	//2
,2	//3
,1	//4
,2	//5
,2	//6
,3	//7
,1	//8
,2	//9
,2	//10
,3	//11
,2	//12
,3	//13
,3	//14
,4	//15
,1	//16
,2	//17
,2	//18
,3	//19
,2	//20
,3	//21
,3	//22
,4	//23
,2	//24
,3	//25
,3	//26
,4	//27
,3	//28
,4	//29
,4	//30
,5	//31
,1	//32
,2	//33
,2	//34
,3	//35
,2	//36
,3	//37
,3	//38
,4	//39
,2	//40
,3	//41
,3	//42
,4	//43
,3	//44
,4	//45
,4	//46
,5	//47
,2	//48
,3	//49
,3	//50
,4	//51
,3	//52
,4	//53
,4	//54
,5	//55
,3	//56
,4	//57
,4	//58
,5	//59
,4	//60
,5	//61
,5	//62
,6	//63
,1	//64
,2	//65
,2	//66
,3	//67
,2	//68
,3	//69
,3	//70
,4	//71
,2	//72
,3	//73
,3	//74
,4	//75
,3	//76
,4	//77
,4	//78
,5	//79
,2	//80
,3	//81
,3	//82
,4	//83
,3	//84
,4	//85
,4	//86
,5	//87
,3	//88
,4	//89
,4	//90
,5	//91
,4	//92
,5	//93
,5	//94
,6	//95
,2	//96
,3	//97
,3	//98
,4	//99
,3	//100
,4	//101
,4	//102
,5	//103
,3	//104
,4	//105
,4	//106
,5	//107
,4	//108
,5	//109
,5	//110
,6	//111
,3	//112
,4	//113
,4	//114
,5	//115
,4	//116
,5	//117
,5	//118
,6	//119
,4	//120
,5	//121
,5	//122
,6	//123
,5	//124
,6	//125
,6	//126
,7	//127
,1	//128
,2	//129
,2	//130
,3	//131
,2	//132
,3	//133
,3	//134
,4	//135
,2	//136
,3	//137
,3	//138
,4	//139
,3	//140
,4	//141
,4	//142
,5	//143
,2	//144
,3	//145
,3	//146
,4	//147
,3	//148
,4	//149
,4	//150
,5	//151
,3	//152
,4	//153
,4	//154
,5	//155
,4	//156
,5	//157
,5	//158
,6	//159
,2	//160
,3	//161
,3	//162
,4	//163
,3	//164
,4	//165
,4	//166
,5	//167
,3	//168
,4	//169
,4	//170
,5	//171
,4	//172
,5	//173
,5	//174
,6	//175
,3	//176
,4	//177
,4	//178
,5	//179
,4	//180
,5	//181
,5	//182
,6	//183
,4	//184
,5	//185
,5	//186
,6	//187
,5	//188
,6	//189
,6	//190
,7	//191
,2	//192
,3	//193
,3	//194
,4	//195
,3	//196
,4	//197
,4	//198
,5	//199
,3	//200
,4	//201
,4	//202
,5	//203
,4	//204
,5	//205
,5	//206
,6	//207
,3	//208
,4	//209
,4	//210
,5	//211
,4	//212
,5	//213
,5	//214
,6	//215
,4	//216
,5	//217
,5	//218
,6	//219
,5	//220
,6	//221
,6	//222
,7	//223
,3	//224
,4	//225
,4	//226
,5	//227
,4	//228
,5	//229
,5	//230
,6	//231
,4	//232
,5	//233
,5	//234
,6	//235
,5	//236
,6	//237
,6	//238
,7	//239
,4	//240
,5	//241
,5	//242
,6	//243
,5	//244
,6	//245
,6	//246
,7	//247
,5	//248
,6	//249
,6	//250
,7	//251
,6	//252
,7	//253
,7	//254
,8	//255
};

int64		 FlexArea::GetCrossBitCount(BYTE **data)	const
{
	int64	Count=0;
	int	NLen=GetFLineLen();
	#pragma omp parallel for reduction(+:Count)
	for(int i=0;i<NLen;i++){
		int SrcX1	=GetFLineLeftX(i);
		int SrcX2	=GetFLineRightX(i);
		int Y		=GetFLineAbsY  (i);
		BYTE	*s=data[Y];
		int	X1=SrcX1>>3;
		int	X2=SrcX2>>3;
		if(X1==X2){
			for(int X=SrcX1;X<SrcX2;X++){
				if((s[X1]&(0x80>>(X&7)))!=0){
					Count++;
				}
			}
		}
		else{
			int	Bit1=SrcX1&7;
			int	Bit2=SrcX2&7;
			for(int X=Bit1;X<8;X++){
				if((s[X1]&(0x80>>X))!=0){
					Count++;
				}
			}
			for(int X=X1+1;X<X2-1;X++){
				Count+=BitCountTable[s[X]];
			}
			for(int X=0;X<Bit2;X++){
				if((s[X2-1]&(0x80>>X))!=0){
					Count++;
				}
			}
		}
	}
	return Count;
}
int64		 FlexArea::GetCrossBitCount(BYTE **data,int dx ,int dy 
										,int srcxbyte ,int srcylen 
										,int LineIsolation)	const
{
	int64	Count=0;
	int	XLen=srcxbyte*8;
	int	NLen=GetFLineLen();
	#pragma omp parallel for reduction(+:Count)
	for(int i=0;i<NLen;i++){
		int Y		=GetFLineAbsY  (i)+dy;
		if(Y<0 || Y>=srcylen)
			continue;
		if(LineIsolation>1 && Y%LineIsolation!=0)
			continue;
		int SrcX1	=GetFLineLeftX(i)+dx;
		int SrcX2	=GetFLineRightX(i)+dx;
		if(SrcX1<0)
			SrcX1=0;
		if(SrcX1>=XLen)
			SrcX1=XLen-1;
		if(SrcX2<0)
			SrcX2=0;
		if(SrcX2>=XLen)
			SrcX2=XLen-1;
		BYTE	*s=data[Y];
		int	X1=SrcX1>>3;
		int	X2=SrcX2>>3;
		if(X1==X2){
			for(int X=SrcX1;X<SrcX2;X++){
				if((s[X>>3]&(0x80>>(X&7)))!=0){
					Count++;
				}
			}
		}
		else{
			int	Bit1=SrcX1&7;
			int	Bit2=SrcX2&7;
			for(int X=Bit1;X<8;X++){
				if((s[X1]&(0x80>>X))!=0){
					Count++;
				}
			}
			for(int X=X1+1;X<X2-1;X++){
				Count+=BitCountTable[s[X]];
			}
			for(int X=0;X<Bit2;X++){
				if((s[X2-1]&(0x80>>X))!=0){
					Count++;
				}
			}
		}
	}
	return Count;
}


void	FlexArea::Rotate(double AngleDegree ,double Cx, double Cy)
{
	int	W=GetWidth();
	int	H=GetHeight();
	int	L=ceil(hypot(W,H))+2;

	double	mcx,mcy;
	GetCenter(mcx,mcy);

	int		XByte=(L+7)/8;
	int		XLen=XByte*8;
	int		YLen=L;

	BYTE	BMapBuff[10000];
	BYTE	**BMap=MakeMatrixBuff(XByte,YLen,BMapBuff,sizeof(BMapBuff));

	double	Radian=AngleDegree*2.0*M_PI/360.0;
	double	sins=sin(Radian);
	double	coss=cos(Radian);

	double	y2=YLen/2.0;
	double	x2=XLen/2.0;

	#pragma omp parallel for
	for(int y=0;y<YLen;y++){
		BYTE	*d=BMap[y];
		for(int x=0;x<XLen;x++){
			int	X= (x-x2)*coss-(y-y2)*sins+mcx;
			int	Y= (x-x2)*sins+(y-y2)*coss+mcy;
			if(IsInclude(X,Y)==true){
				SetBmpBitOnY1(d,x);
			}
			else{
				SetBmpBitOnY0(d,x);
			}
		}
	}
	int	Rx= (mcx-Cx)*coss+(mcy-Cy)*sins;
	int	Ry=-(mcx-Cx)*sins+(mcy-Cy)*coss;
	BuildFromRaster(BMap,XByte,YLen,Cx+Rx-x2,Cy+Ry-y2);
	if(BMap!=(BYTE **)BMapBuff){
		DeleteMatrixBuff(BMap,YLen);
	}
	if(AShape!=NULL){
		AShape->Rotate(AngleDegree,Cx, Cy);
	}
}
void	FlexArea::MirrorX(int PointY)
{
	int	NLen=GetFLineLen();
	struct  FlexLine	*FL=new struct  FlexLine[NLen];

	int	k=0;
	for(int i=NLen-1;i>=0;i--,k++){
		int SrcX1	=GetFLineLeftX(i);
		int Numb	=GetFLineNumb(i);
		int Y		=GetFLineAbsY  (i);
		FL[k]._SetLeftX(SrcX1);
		FL[k].SetNumb(Numb);
		FL[k]._SetAbsY(PointY-(Y-PointY));
	}
	if(AShape!=NULL){
		AShape->MirrorX(PointY);
	}
	QSort(FL,NLen,sizeof(FL[0]),YSortFunc);
	SetFLine(FL,NLen);
}
void	FlexArea::MirrorY(int PointX)
{
	int	NLen=GetFLineLen();
	struct  FlexLine	*FL=new struct  FlexLine[NLen];

	int	k=0;
	for(int i=NLen-1;i>=0;i--,k++){
		int SrcX1	=GetFLineLeftX(i);
		int Numb	=GetFLineNumb(i);
		int	SrcX2=SrcX1+Numb;
		int Y		=GetFLineAbsY  (i);
		FL[k]._SetLeftX(PointX-(SrcX2-PointX));
		FL[k].SetNumb(Numb);
		FL[k]._SetAbsY(Y);
	}
	if(AShape!=NULL){
		AShape->MirrorY(PointX);
	}
	QSort(FL,NLen,sizeof(FL[0]),YSortFunc);
	SetFLine(FL,NLen);
}

void    FlexArea::ThinAreaN(int TurnN)
{
	if(TurnN<=0)
		return;
	int	Mx=GetMinX()-8;
	int	My=GetMinY()-8;
	int	Width=GetWidth()+16;
	int	Height=GetHeight()+16;
	int	XByte=(Width+7)/8;
	BYTE	BmpMapBuff[10000];
	BYTE	TmpMapBuff[10000];
	BYTE	**BmpMap=MakeMatrixBuff(XByte ,Height,BmpMapBuff,sizeof(BmpMapBuff));
	BYTE	**TmpMap=MakeMatrixBuff(XByte ,Height,TmpMapBuff,sizeof(TmpMapBuff));
	MatrixBuffClear	(BmpMap ,0 ,XByte ,Height);
	MakeBitData(BmpMap,-Mx,-My ,Width,Height);
	::ThinAreaN(BmpMap
				,TmpMap
				,XByte ,Height
				,TurnN);
	BuildFromRaster(BmpMap ,XByte ,Height ,Mx,My);

	if(BmpMap!=(BYTE **)BmpMapBuff){
		DeleteMatrixBuff(BmpMap,Height);
	}
	if(TmpMap!=(BYTE **)TmpMapBuff){
		DeleteMatrixBuff(TmpMap,Height);
	}
}

void    FlexArea::FatAreaN (int TurnN)
{
	if(TurnN<=0)
		return;
	int	Mx=GetMinX()-TurnN-8;
	int	My=GetMinY()-TurnN-8;
	int	Width=GetWidth()+TurnN+TurnN+16;
	int	Height=GetHeight()+TurnN+TurnN+16;
	int	XByte=(Width+7)/8;
	BYTE	BmpMapBuff[10000];
	BYTE	TmpMapBuff[10000];
	BYTE	**BmpMap=MakeMatrixBuff(XByte ,Height,BmpMapBuff,sizeof(BmpMapBuff));
	BYTE	**TmpMap=MakeMatrixBuff(XByte ,Height,TmpMapBuff,sizeof(TmpMapBuff));
	MatrixBuffClear	(BmpMap ,0 ,XByte ,Height);
	MakeBitData(BmpMap,-Mx,-My ,Width,Height);
	::FatAreaN(BmpMap
				,TmpMap
				,XByte ,Height
				,TurnN);
	BuildFromRaster(BmpMap ,XByte ,Height ,Mx,My);

	if(BmpMap!=(BYTE **)BmpMapBuff){
		DeleteMatrixBuff(BmpMap,Height);
	}
	if(TmpMap!=(BYTE **)TmpMapBuff){
		DeleteMatrixBuff(TmpMap,Height);
	}
}

void    FlexArea::ThinArea1(void)
{
	int	Mx=GetMinX()-8;
	int	My=GetMinY()-8;
	int	Width=GetWidth()+16;
	int	Height=GetHeight()+16;
	int	XByte=(Width+7)/8;
	BYTE	BmpMapBuff[10000];
	BYTE	TmpMapBuff[10000];
	BYTE	**BmpMap=MakeMatrixBuff(XByte ,Height,BmpMapBuff,sizeof(BmpMapBuff));
	BYTE	**TmpMap=MakeMatrixBuff(XByte ,Height,TmpMapBuff,sizeof(TmpMapBuff));
	MatrixBuffClear	(BmpMap ,0 ,XByte ,Height);
	MakeBitData(BmpMap,-Mx,-My ,Width,Height);

	::ThinAreaN(BmpMap
				,TmpMap
				,XByte ,Height
				,1);
	MatrixBuffCopy(TmpMap		,XByte ,Height
				,(const BYTE **)BmpMap ,XByte ,Height);

	int	NLen=GetFLineLen();
	for(int i=0;i<NLen;i++){
		int Y	=GetFLineAbsY  (i)	-My;
		int X1	=GetFLineLeftX(i)	-Mx;
		int X2	=GetFLineRightX(i)	-Mx;
		BYTE	*s0=BmpMap[Y-1];
		BYTE	*st=BmpMap[Y];
		BYTE	*s1=BmpMap[Y+1];
		BYTE	*d =TmpMap[Y];
		for(int x=X1;x<X2;x++){
			if(GetBmpBitOnY(st,x)==0){
				if(GetBmpBitOnY(s0,x-1)==0 && GetBmpBitOnY(s0,x)==0 && GetBmpBitOnY(s0,x+1)==0
				&& GetBmpBitOnY(st,x-1)==0 && GetBmpBitOnY(st,x+1)==0
				&& GetBmpBitOnY(s1,x-1)==0 && GetBmpBitOnY(s1,x)==0 && GetBmpBitOnY(s1,x+1)==0){
					SetBmpBitOnY1(d,x);
				}
			}
		}
	}

	BuildFromRaster(TmpMap ,XByte ,Height ,Mx,My);

	if(BmpMap!=(BYTE **)BmpMapBuff){
		DeleteMatrixBuff(BmpMap,Height);
	}
	if(TmpMap!=(BYTE **)TmpMapBuff){
		DeleteMatrixBuff(TmpMap,Height);
	}
}
int		FlexArea::GetPatternWidth(void)	const
{
	int	NLen=GetFLineLen();
	int	Width=0;
	for(int i=0;i<NLen;i++){
		int Numb	=GetFLineNumb(i);
		Width=max(Width,Numb);
	}
	return Width;
}

int		FlexArea::GetPatternHeight(void)	const
{
	int	Height=0;
	for(int x=GetMinX();x<=GetMaxX();x++){
		int	LMinY=99999999;
		int	LMaxY=-99999999;
		for(int y=GetMinY();y<=GetMaxY();y++){
			if(IsInclude(x,y)==true){
				LMinY=min(LMinY,y);
				LMaxY=max(LMaxY,y);
			}
		}
		if(LMinY<LMaxY){
			int	H=LMaxY-LMinY;
			Height=max(Height,H);
		}
	}
	return Height;
}
QColor  FlexArea::MakeAverage(QImage &Image)	const
{
	int	W=Image.width();
	int	H=Image.height();
	int	NLen=GetFLineLen();
	double	vR=0.0;
	double	vG=0.0;
	double	vB=0.0;
	int		vNumb=0;
	for(int i=0;i<NLen;i++){
		int Y		=GetFLineAbsY  (i);
		if(Y<0 || Y>=H)
			continue;
		int SrcX	=GetFLineLeftX(i);
		int Numb	=GetFLineNumb(i);

		QRgb	*s=(QRgb *)Image.scanLine(Y);
		for(int k=0;k<Numb;k++){
			int	x=SrcX+k;
			if(0<=x && x<W){
				vR+=qRed(s[x]);
				vG+=qGreen(s[x]);
				vB+=qBlue(s[x]);
				vNumb++;
			}
		}
	}
	if(vNumb!=0){
		return QColor(vR/vNumb,vG/vNumb,vB/vNumb);
	}
	return QColor(0,0,0);
}


//==========================================================
void	FlexAreaPointerContainer::Add(FlexArea *a)
{
	AppendList(new FlexAreaPointerList(a));
}

//==========================================================
	
bool	PureFlexAreaList::Save(QIODevice *f)
{
	if(FlexArea::Save(f)==false)
		return false;
	return true;
}

bool	PureFlexAreaList::Load(QIODevice *f)
{
	if(FlexArea::Load(f)==false)
		return false;
	return true;
}
PureFlexAreaListContainer::PureFlexAreaListContainer(void)
{
	MinX=INT_MAX;
	MinY=INT_MAX;
	MaxX=INT_MIN;
	MaxY=INT_MIN;
}

PureFlexAreaListContainer::PureFlexAreaListContainer(const PureFlexAreaListContainer &src)
{
	MinX=INT_MAX;
	MinY=INT_MAX;
	MaxX=INT_MIN;
	MaxY=INT_MIN;

	for(PureFlexAreaList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		PureFlexAreaList	*b=new PureFlexAreaList();
		*b=*a;
		AppendList(b);
	}
}

void	PureFlexAreaListContainer::AppendList(PureFlexAreaList *L)
{
	MinX=min(MinX,L->GetMinX());
	MinY=min(MinY,L->GetMinY());
	MaxX=max(MaxX,L->GetMaxX());
	MaxY=max(MaxY,L->GetMaxY());
	NPListPackSaveLoad<PureFlexAreaList>::AppendList(L);
}

void    PureFlexAreaListContainer::RestructMinMax(void)
{
	MinX=INT_MAX;
	MinY=INT_MAX;
	MaxX=INT_MIN;
	MaxY=INT_MIN;
	for(PureFlexAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		MinX=min(MinX,a->GetMinX());
		MinY=min(MinY,a->GetMinY());
		MaxX=max(MaxX,a->GetMaxX());
		MaxY=max(MaxY,a->GetMaxY());
	}
}

bool    PureFlexAreaListContainer::Save(QIODevice *f)
{
	int32	N=GetCount();

	if(::Save(f,N)==false)
		return false;
	for(PureFlexAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool    PureFlexAreaListContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	MinX=INT_MAX;
	MinY=INT_MAX;
	MaxX=INT_MIN;
	MaxY=INT_MIN;
	for(int i=0;i<N;i++){
		PureFlexAreaList	*a=new PureFlexAreaList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
void	PureFlexAreaListContainer::MoveNoClip(int dx ,int dy)
{
	for(PureFlexAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToNoClip(dx,dy);
	}
	MinX+=dx;
	MinY+=dy;
	MaxX+=dx;
	MaxY+=dy;
}

void	PureFlexAreaListContainer::MoveClip(int dx ,int dy ,int Left ,int Top ,int Right ,int Bottom)
{
	for(PureFlexAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToClip(dx,dy,Left ,Top ,Right ,Bottom);
	}
	RestructMinMax();
}
int     PureFlexAreaListContainer::GetWidth(void)	const
{
	//PureFlexAreaList *a=GetFirst();
	//if(a==NULL){
	//	return 0;
	//}
	//int	MinX=a->GetMinX();
	//int	MaxX=a->GetMaxX();
	//for(a=a->GetNext();a!=NULL;a=a->GetNext()){
	//	MinX=min(MinX,a->GetMinX());
	//	MaxX=max(MaxX,a->GetMaxX());
	//}
	return MaxX-MinX;
}
int     PureFlexAreaListContainer::GetHeight(void)	const
{
	//PureFlexAreaList *a=GetFirst();
	//if(a==NULL){
	//	return 0;
	//}
	//int	MinY=a->GetMinY();
	//int	MaxY=a->GetMaxY();
	//for(a=a->GetNext();a!=NULL;a=a->GetNext()){
	//	MinY=min(MinY,a->GetMinY());
	//	MaxY=max(MaxY,a->GetMaxY());
	//}
	return MaxY-MinY;
}
int     PureFlexAreaListContainer::GetMinX(void)	const
{
	//PureFlexAreaList *a=GetFirst();
	//if(a==NULL){
	//	return -99999999;
	//}
	//int	MinX=a->GetMinX();
	//for(a=a->GetNext();a!=NULL;a=a->GetNext()){
	//	MinX=min(MinX,a->GetMinX());
	//}
	return MinX;
}
int     PureFlexAreaListContainer::GetMinY(void)	const
{
	//PureFlexAreaList *a=GetFirst();
	//if(a==NULL){
	//	return -99999999;
	//}
	//int	MinY=a->GetMinY();
	//for(a=a->GetNext();a!=NULL;a=a->GetNext()){
	//	MinY=min(MinY,a->GetMinY());
	//}
	return MinY;
}
int     PureFlexAreaListContainer::GetMaxX(void)	const
{
	//PureFlexAreaList *a=GetFirst();
	//if(a==NULL){
	//	return 99999999;
	//}
	//int	MaxX=a->GetMaxX();
	//for(a=a->GetNext();a!=NULL;a=a->GetNext()){
	//	MaxX=max(MaxX,a->GetMaxX());
	//}
	return MaxX;
}
int     PureFlexAreaListContainer::GetMaxY(void)	const
{
	//PureFlexAreaList *a=GetFirst();
	//if(a==NULL){
	//	return 99999999;
	//}
	//int	MaxY=a->GetMaxY();
	//for(a=a->GetNext();a!=NULL;a=a->GetNext()){
	//	MaxY=max(MaxY,a->GetMaxY());
	//}
	return MaxY;
}

PureFlexAreaListContainer	&PureFlexAreaListContainer::operator=(const PureFlexAreaListContainer &src)
{
	RemoveAll();
	MinX=INT_MAX;
	MinY=INT_MAX;
	MaxX=INT_MIN;
	MaxY=INT_MIN;
	for(PureFlexAreaList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		PureFlexAreaList	*b=new PureFlexAreaList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
PureFlexAreaListContainer	&PureFlexAreaListContainer::operator+=(const PureFlexAreaListContainer &src)
{
	for(PureFlexAreaList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		PureFlexAreaList	*b=new PureFlexAreaList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

bool	PureFlexAreaListContainer::IsInclude(int x ,int y)	const
{
	for(PureFlexAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(x,y)==true)
			return true;
	}
	return false;
}

FlexArea    PureFlexAreaListContainer::Bind(void)
{
	FlexArea	Ret;
	for(PureFlexAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		Ret+=*a;
	}
	return Ret;
}