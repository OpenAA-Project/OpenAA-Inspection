/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFlexAreaFast.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//	äTóv
//
//	çÏê¨é“
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


FlexAreaFast::FlexAreaFast(const FlexAreaFast &src)
{
	Initial();
	CopyFLine(src.GetFLinePoint(),src.GetFLineLen());
	SetShape(src.GetShape());
	Info= src.Info;
}

FlexAreaFast::FlexAreaFast(const FlexArea &src)
{
	Initial();
	CopyFLine(src.GetFLinePoint(),src.GetFLineLen());
	SetShape(src.GetShape());
	Info.Len=src.GetFLineLen();
	Info.AddX=src.GetFLineAddX();
	Info.AddY=src.GetFLineAddY();
	Info.MinX=src.GetMinX();
	Info.MaxX=src.GetMaxX();
	Info.PatternByte=src.GetPatternByte();
}

FlexAreaFast::~FlexAreaFast(void)
{
	if(FLinesPointer!=NULL){
		delete [] FLinesPointer;
		FLinesPointer=NULL;
	}
	Info.Len=0;
	Info.AddX=0;	Info.AddY=0;
	Info.MinX=0;	Info.MaxX=0;
	Info.PatternByte=0;
}

int  FlexAreaFast::GetHeight(void) const
{
	if(Info.Len==0)	return 0;
	return (GetFLineAbsY(Info.Len-1)+1 - GetFLineAbsY(0));
}

int  FlexAreaFast::GetMinY(void) const
{
	if(Info.Len==0)	return 0;
	return GetFLineAbsY(0);
}
int  FlexAreaFast::GetMaxY(void) const
{
	if(Info.Len==0)	return 0;
	return (GetFLineAbsY(Info.Len-1)+1);
}
double  FlexAreaFast::GetLength(void) const
{
	double  len;
	int     y1,y2;
	int     i;
	if(Info.Len==0)	return 0.0;
	len=0.0;
	y1=GetFLineAbsY(0);
	for(i=1;i<Info.Len;i++){
		y2=GetFLineAbsY(i);
		len+=sqrt( (double)( (y2 - y1)*(y2 - y1) ) );
		y1=y2;
	}
	return(len);
}
void  FlexAreaFast::SetShape(struct BlockShape &bshape)
{
	AShape=bshape;
}
struct  BlockShape  &FlexAreaFast::GetShape(void)  const
{
	return((struct BlockShape &)AShape);
}

void  FlexAreaFast::CopyFLine(struct FlexLine *FL,int len)
{
	CopyFLineOnly(FL,len);
	Regulate();
}
void  FlexAreaFast::CopyFLineOnly(struct FlexLine *FL,int len)
{
	if(FLinesPointer!=NULL){
		delete [] FLinesPointer;
		FLinesPointer=NULL;
	}
	if(len>MAXFlexAreaFastLines){
		FLinesPointer=new FlexLine[len];
		for(uint32 i=0;i<(uint32)len;i++){
			FLinesPointer[i]=FL[i];
		}
	}else{
		FLinesPointer=NULL;
		for(uint32 i=0;i<(uint32)len;i++){
			FLinesDim[i]=FL[i];
		}
	}
	Info.Len=len;
}
void  FlexAreaFast::SuckFrom(FlexAreaBasePure &src)
{
	SetShape( src.GetShape() );
	CopyFLine( src.GetFLinePoint() , src.GetFLineLen() );
	Info.AddX=src.GetFLineAddX();
	Info.AddY=src.GetFLineAddY();
	Info.MinX=src.GetMinX();
	Info.MaxX=src.GetMaxX();
	Info.PatternByte=src.GetPatternByte();
}

void  FlexAreaFast::Regulate(void)
{
	int     i;
	int     minx,maxx;
	if(Info.Len==0){
		Info.MinX=0;
		Info.MaxX=0;
		return;
	}
	struct FlexLine *tFL=GetFLinePoint();
	if(Info.Len>1){
		QSort(tFL,Info.Len,sizeof(struct FlexLine),YSortFunc);
	}

	minx=GetFLineLeftX(0);
	maxx=GetFLineRightX(0);
	Info.PatternByte	=0;
	for(i=1;i<Info.Len;i++){
		if(minx>GetFLineLeftX(i))	minx=GetFLineLeftX(i);
		if(maxx<GetFLineRightX(i))	maxx=GetFLineRightX(i);
		Info.PatternByte+=GetFLineNumb(i);
	}
	Info.MinX=minx;
	Info.MaxX=maxx;
}
void  FlexAreaFast::Clear(void)
{
	if(FLinesPointer!=NULL){
		delete [] FLinesPointer;
		FLinesPointer=NULL;
	}
	Info.Len=0;
	Info.AddX=0;	Info.AddY=0;
	Info.MinX=0;	Info.MaxX=0;
	Info.PatternByte=0;
}
void  FlexAreaFast::MoveToNoClip(int dx, int dy)
{
	Info.AddX+=dx;
	Info.AddY+=dy;
}
int  FlexAreaFast::DirectCopyTo(struct FlexLine dest[] ,int destnumb ,int startIndex)
{
	int     i,j;
	if(Info.Len==0)	return 0;
	if(startIndex<0)	startIndex=0;
	j=startIndex;
	for(i=0;i<(int)Info.Len;i++){
		if(j>=destnumb)	break;
		dest[j]= (FLinesPointer==NULL)?FLinesDim[i]:FLinesPointer[i];
		j++;
	}
	return (j - startIndex);
}
int   FlexAreaFast::SearchNearBy(struct FlexLine Key)
{
	int     low,high,mid;
	int     KeyY;
	int     MidY;
	if(Info.Len==0)	return -1;
	KeyY=Key._GetAbsY()+Info.AddY;
	low=0;
	high=Info.Len-1;
	while(low<=high){
		mid=(low+high)/2;
		MidY= (FLinesPointer==NULL)?(FLinesDim[mid]._GetAbsY()+Info.AddY):(FLinesPointer[mid]._GetAbsY()+Info.AddY);
		if(KeyY<MidY){
			high=mid-1;
		}else if(KeyY>MidY){
			low=mid+1;
		}else{
			return mid;
		}
	}
	return -1;
}
struct FlexLine *FlexAreaFast::GetFlexLine(int index)
{
	if(index<0 || index>=(int)Info.Len){
		return NULL;
	}
	return (FLinesPointer==NULL)?&FLinesDim[index]:&FLinesPointer[index];
}
bool  FlexAreaFast::GetFlexLine(int index , struct FlexLine &Ret)   const
{
	if(index<0 || index>=(int)Info.Len){
		return false;
	}
	Ret=(FLinesPointer==NULL)?FLinesDim[index]:FLinesPointer[index];
	return true;
}
int  FlexAreaFast::FindIndex(int AbsY ,int &IndexStart ,int &IndexEnd)
{
	int     low,high,mid;
	int     KeyY;
	int     MidY;
	if(Info.Len==0){
		IndexStart=-1;
		IndexEnd=-1;
		return -1;
	}
	KeyY=AbsY;
	low=0;
	high=Info.Len-1;
	while(low<=high){
		mid=(low+high)/2;
		MidY= (FLinesPointer==NULL)?(FLinesDim[mid]._GetAbsY()+Info.AddY):(FLinesPointer[mid]._GetAbsY()+Info.AddY);
		if(KeyY<MidY){
			high=mid-1;
		}else if(KeyY>MidY){
			low=mid+1;
		}else{
			//å©Ç¬Ç©Ç¡ÇΩ
			IndexStart=mid;
			IndexEnd=mid;
			//ëOï˚íTçı
			for(int i=mid-1;i>=0;i--){
				MidY= (FLinesPointer==NULL)?(FLinesDim[i]._GetAbsY()+Info.AddY):(FLinesPointer[i]._GetAbsY()+Info.AddY);
				if(MidY==KeyY){
					IndexStart=i;
				}else{
					break;
				}
			}
			//å„ï˚íTçı
			for(int i=mid+1;i<(int)Info.Len;i++){
				MidY= (FLinesPointer==NULL)?(FLinesDim[i]._GetAbsY()+Info.AddY):(FLinesPointer[i]._GetAbsY()+Info.AddY);
				if(MidY==KeyY){
					IndexEnd=i;
				}else{
					break;
				}
			}
			return (IndexEnd - IndexStart + 1);
		}
	}
	//å©Ç¬Ç©ÇÁÇ»Ç©Ç¡ÇΩ
	IndexStart=-1;
	IndexEnd=-1;
	return -1;
}
bool  FlexAreaFast::WriteBase(QIODevice *str)
{
	if(str->write( (const char *)&Info , sizeof(Info) ) != sizeof(Info) ){
		return false;
	}

	//AShape
	if(str->write( (const char *)&AShape , sizeof(struct BlockShape) ) != sizeof(struct BlockShape) ){
		return false;
	}
	//FLines
	struct FlexLine  *fl=(FLinesPointer==NULL)?FLinesDim:FLinesPointer;
	if(str->write( (const char *)fl , sizeof(struct FlexLine)*Info.Len ) != sizeof(struct FlexLine)*Info.Len ){
		return false;
	}
	return true;
}
bool  FlexAreaFast::ReadBase(QIODevice *str)
{
	if(str->read( (char *)&Info , sizeof(Info) ) != sizeof(Info) ){
		return false;
	}
	//AShape
	if(str->read( (char *)&AShape , sizeof(struct BlockShape) ) != sizeof(struct BlockShape) ){
		return false;
	}
	//FLines
	if(FLinesPointer!=NULL){
		delete [] FLinesPointer;
		FLinesPointer=NULL;
	}
	if(Info.Len>MAXFlexAreaFastLines){
		FLinesPointer=new FlexLine[Info.Len];
		if(str->read( (char *)FLinesPointer , sizeof(struct FlexLine)*Info.Len ) != sizeof(struct FlexLine)*Info.Len ){
			delete [] FLinesPointer;
			FLinesPointer=NULL;
			return false;
		}
	}else{
		FLinesPointer=NULL;
		if(str->read( (char *)FLinesDim , sizeof(struct FlexLine)*Info.Len ) != sizeof(struct FlexLine)*Info.Len ){
			return false;
		}
	}
	return true;
}
void  FlexAreaFast::SortFLine(struct FlexLine *FL ,int FLNumb)
{
	int     i,j;
	struct  FlexLine    temp;
	for(i=0;i<FLNumb-1;i++){
		for(j=i+1;j<FLNumb;j++){
			if( (FL[i]._GetAbsY()+Info.AddY) > (FL[j]._GetAbsY()+Info.AddY) ){
				temp=FL[i];
				FL[i]=FL[j];
				FL[j]=temp;
			}
		}
	}
}
void  FlexAreaFast::SortFLine(void)
{
	int     i,j;
	struct  FlexLine    temp;
	struct  FlexLine    *fl=(FLinesPointer==NULL)?FLinesDim:FLinesPointer;
	for(i=0;i<(int)Info.Len-1;i++){
		for(j=i+1;j<(int)Info.Len;j++){
			if( (fl[i]._GetAbsY()+Info.AddY) > (fl[j]._GetAbsY()+Info.AddY) ){
				temp=fl[i];
				fl[i]=fl[j];
				fl[j]=temp;
			}
		}
	}
}


//-----------------------------------------------------------------------------

bool  FlexAreaFast::IsNull(void) const
{
	if(Info.Len==0)	return true;
	return false;
}
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

bool    FlexAreaFast::IsInclude(int x ,int y)         const 
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


void    FlexAreaFast::Initial(int NoZone,int DotPerLine, int MaxLines)
{
	Clear();
}

bool    FlexAreaFast::IsInRectangle(int x1 ,int y1 ,int x2 ,int y2)   const
{
	if(Info.Len==0)	return false;
	int     areaMinX=Info.MinX + Info.AddX;
	int     areaMaxX=Info.MaxX + Info.AddX;
	int     areaMinY=GetFLineAbsY(0);
	int     areaMaxY=GetFLineAbsY(Info.Len-1);
	if(x1<=areaMinX && x2>=areaMaxX &&
	   y1<=areaMinY && y2>=areaMaxY){
		return true;
	}
	return false;
}

bool    FlexAreaFast::CheckOverlap(const FlexAreaFast *b)	const
{
	if(CheckOverlapRectRect(	GetMinX(),	 GetMinY(),   GetMaxX(),   GetMaxY()
		,b->GetMinX(),b->GetMinY(),b->GetMaxX(),b->GetMaxY())==false){
		return(false);
	}

	const	struct	FlexLine *ks=GetFLinePoint();
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




bool    FlexAreaFast::CheckOverlap(const FlexAreaFast *src ,int srcDx, int srcDy) const
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

bool    FlexAreaFast::CheckOverlapNeighbor(const FlexAreaFast *b)   const
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
bool    FlexAreaFast::IsInclude(const FlexAreaFast *b)  const
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

bool    FlexAreaFast::CheckOverlapRectangle(int x1 ,int y1 ,int x2 ,int y2)   const
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

bool    FlexAreaFast::CheckOverlapLine(int x1 ,int y1 ,int x2 ,int y2)	const
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
bool    FlexAreaFast::CheckOverlapLine(double x1 ,double y1 ,double x2 ,double y2)    const
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
int     FlexAreaFast::SearchFirst(int y) const     //ÇôÇÕê‚ëŒíl
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
static	int  NearByFunc(const void *a ,const void *b)
{
	return(((struct FlexLine *)a)->_GetAbsY() - ((struct FlexLine *)b)->_GetAbsY() );
}

bool    FlexAreaFast::NearBy(struct FlexLine &L)
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


void    FlexAreaFast::EatArea(const FlexAreaFast *food)
{
	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *tmp;
	if(GetFLineLen()+food->GetFLineLen()>MAXFlexAreaFastLines){
		tmp=new struct FlexLine[GetFLineLen()+food->GetFLineLen()];
	}
	else{
		tmp=tmpDim;
	}
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
	CopyFLine(tmp,mLen);
	if(tmpDim!=tmp){
		delete[] tmp;
	}
}
void    FlexAreaFast::Restruct(void)
{
	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *FL;
	if(GetFLineLen()>MAXFlexAreaFastLines){
		FL=new struct FlexLine[GetFLineLen()];
	}
	else{
		FL=tmpDim;
	}

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
	if(FL!=tmpDim){
		CopyFLine(FL,mLen);
		delete[] FL;
	}
	else{
		CopyFLineOnly(FL,mLen);
	}
}

void    FlexAreaFast::BindArea(void)
{
	for(int i=0;i<GetFLineLen()-1;){
		if(GetFLineAbsY(i)==GetFLineAbsY(i+1)
		&& GetFLineRightX(i)>=GetFLineLeftX(i+1)){

			struct FlexLine tmpDim[MAXFlexAreaFastLines];
			struct FlexLine *FL;
			if(GetFLineLen()>MAXFlexAreaFastLines){
				FL=new struct FlexLine[GetFLineLen()-1];
			}
			else{
				FL=tmpDim;
			}
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
			if(FL!=tmpDim){
				CopyFLine(FL,Ln);
				delete[] FL;
			}
			else{
				CopyFLineOnly(FL,Ln);
			}
			break;
		}
		else{
			i++;
		}
	}
}
int     FlexAreaFast::GetByte(void)
{
	return(sizeof(FlexAreaFast)
		  +GetFLineLen()*sizeof(struct FlexLine)	);
}

void    FlexAreaFast::CopyFrom(FlexAreaFast &src ,int dx ,int dy)
{
	operator=(src);
	MoveToNoClip(dx,dy);
}

void    FlexAreaFast::GetWeightCenter(double &cx, double &cy)  //èdêSÇÃåvéZ
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

struct	FlexAreaCreateZoom
{
	int	X1,X2;
};

void	FlexAreaFast::CreateZoom(double ZoomRate ,int Cx,int Cy)
{
	int	NLen=GetFLineLen();
	struct FlexLine tmpDim[MAXFlexAreaFastLines];

	if(ZoomRate<=1.0){
		int	LastY= -99999999;
		struct	FlexAreaCreateZoom	LastXLine[1000];
		int	LastXNumb=0;

		struct FlexLine *FL;
		if(NLen>MAXFlexAreaFastLines){
			FL=new struct FlexLine[NLen];
		}
		else{
			FL=tmpDim;
		}

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
		if(FL!=tmpDim){
			CopyFLine(FL,FLNumb);
			delete[] FL;
		}
		else{
			CopyFLine(FL,FLNumb);
		}
	}
	else{
		int	tLen=NLen*(int)ceil(ZoomRate);
		struct FlexLine *FL;
		if(tLen>MAXFlexAreaFastLines){
			FL=new struct FlexLine[tLen];
		}
		else{
			FL=tmpDim;
		}

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
		if(FL!=tmpDim){
			CopyFLine(FL,FLNumb);
			delete[] FL;
		}
		else{
			CopyFLine(FL,FLNumb);
		}
	}
	Regulate();
}

void	FlexAreaFast::Swap(FlexAreaFast &dest)
{
	struct	FlexLine	*tempFLinesPointer;
	struct	BlockShape	tempAShape;
	struct  FlexAreaInfo	tempInfo;
	tempFLinesPointer=dest.FLinesPointer;
	dest.FLinesPointer=FLinesPointer;
	FLinesPointer=tempFLinesPointer;
	tempAShape=dest.AShape;
	dest.AShape=AShape;
	AShape=tempAShape;
	tempInfo=dest.Info;
	dest.Info=Info;
	Info=tempInfo;

	struct  FlexLine    tmpFLinesDim[MAXFlexAreaFastLines];
	memcpy(tmpFLinesDim,dest.FLinesDim,sizeof(dest.FLinesDim));
	memcpy(dest.FLinesDim,FLinesDim,sizeof(FLinesDim));
	memcpy(FLinesDim,tmpFLinesDim,sizeof(tmpFLinesDim));
}

void     FlexAreaFast::MoveToClip(int dx, int dy
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

		struct FlexLine tmpDim[MAXFlexAreaFastLines];
		struct FlexLine *FL;
		if(GetFLineLen()>MAXFlexAreaFastLines){
			FL=new struct FlexLine[GetFLineLen()];
		}
		else{
			FL=tmpDim;
		}

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
		if(FL!=tmpDim){
			CopyFLine(FL,mLen);
			delete[] FL;
		}
		else{
			CopyFLine(FL,mLen);
		}
		AShape.MoveTo(dx,dy);
	}
}

struct	FlexAreaYDim
{
	int	StartI;
	int	ICount;
};
void     FlexAreaFast::MakeBitData(BYTE **data ,int XDotLen ,int YDotLen ,bool EnableThread) const
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

void     FlexAreaFast::MakeNotBitData(BYTE **data ,int XDotLen ,int YDotLen ,int mx ,int my)  const
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
void     FlexAreaFast::MakeBitData(BYTE **data 
                       ,int dx ,int dy
                       ,int XDotLen, int YDotLen)                      const
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
void	 FlexAreaFast::MakeBitData(ImageBuffer &BitImg ,int dx, int dy)           const
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

void     FlexAreaFast::MakeMaskBitData(BYTE **data,int DotPerLine, int MaxLines)  const
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

bool     FlexAreaFast::CheckOverlapBit(BYTE *data  ,int xbyte,int DotPerLine, int MaxLines)   const
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
bool     FlexAreaFast::CheckOverlapBit(BYTE **data , int XDot ,int YDot)  const
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

const	BYTE	FlexAreaFast::BitCountTable[]={
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
int64	 FlexAreaFast::GetCrossBitCount(BYTE **data)  const
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

int64	 FlexAreaFast::GetCrossBitCount(BYTE **data,int dx ,int dy,int srcxbyte ,int srcylen ,int LineIsolation)	const
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

void    FlexAreaFast::Sub(const FlexAreaFast &src1 , const FlexAreaFast &src2)
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

	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *FL;
	if(MaxLen>MAXFlexAreaFastLines){
		FL=new struct FlexLine[MaxLen];
	}
	else{
		FL=tmpDim;
	}
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
	if(FL!=tmpDim){
		CopyFLine(FL,mLen);
		delete[] FL;
	}
	else{
		CopyFLine(FL,mLen);
	}
}

void    FlexAreaFast::Sub(const FlexAreaFast &src , int dx ,int dy)
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
void    FlexAreaFast::Add(const FlexAreaFast &src1 , const FlexAreaFast &src2)
{
	int	mLen1=src1.GetFLineLen();
	int	mLen2=src2.GetFLineLen();
	int	mLen=mLen1+mLen2;

	struct FlexLine ttmpDim[MAXFlexAreaFastLines];
	struct FlexLine *tFL;
	if(mLen>MAXFlexAreaFastLines){
		tFL=new struct FlexLine[mLen];
	}
	else{
		tFL=ttmpDim;
	}

	memcpy(&tFL[0    ],src1.GetFLinePoint(),sizeof(struct FlexLine)*mLen1);
	memcpy(&tFL[mLen1],src2.GetFLinePoint(),sizeof(struct FlexLine)*mLen2);
	QSort(tFL,mLen,sizeof(struct FlexLine),YSortFunc);

	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *FL;
	if(mLen>MAXFlexAreaFastLines){
		FL=new struct FlexLine[mLen];
	}
	else{
		FL=ttmpDim;
	}

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
	if(FL!=ttmpDim){
		CopyFLine(FL,L);
		delete	[]FL;
	}
	else{
		CopyFLine(FL,L);
	}
	if(tFL!=ttmpDim){
		delete	[]tFL;
	}
}

bool	FlexAreaFast::SubInside(const FlexArea &src, int dx ,int dy ,float Multiply)
{
	if(GetFLineLen()==0){
		return(true);
	}
	int MaxLen=(GetFLineLen() +src.GetFLineLen())*Multiply;

	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *FL;
	if(MaxLen>MAXFlexAreaFastLines){
		FL=new struct FlexLine[MaxLen];
	}
	else{
		FL=tmpDim;
	}

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
	if(FL!=tmpDim){
		CopyFLine(FL,mLen);
		delete[] FL;
	}
	else{
		CopyFLine(FL,mLen);
	}
	return(true);
}

void    FlexAreaFast::CopyMove(const FlexAreaFast &src , int dx ,int dy)
{
	operator=(src);
	MoveToNoClip(dx, dy);
}

FlexAreaFast    &FlexAreaFast::operator=(const FlexAreaFast &src)
{
	CopyFLine(src.GetFLinePoint(),src.GetFLineLen());
	SetShape(src.GetShape());

	SetAddXY(src.GetFLineAddX(),src.GetFLineAddY());

	Regulate();
	return(*this);
}

FlexAreaFast    &FlexAreaFast::operator=(const FlexArea &src)
{
	CopyFLine(src.GetFLinePoint(),src.GetFLineLen());
	SetShape(src.GetShape());

	SetAddXY(src.GetFLineAddX(),src.GetFLineAddY());

	Regulate();
	return(*this);
}


FlexAreaFast    &FlexAreaFast::operator+=(const FlexAreaFast &src)
{
	if(src.GetFLineLen()==0){
		return(*this);
		}

	if(GetFLineLen()==0){
		operator=(src);
		}
	else{
		EatArea(&src);
	}
	return(*this);
}
FlexAreaFast    &FlexAreaFast::operator&=(const FlexAreaFast &src)
{
	int MaxLen = GetFLineLen()+src.GetFLineLen();
	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *FL;
	if(MaxLen>MAXFlexAreaFastLines){
		FL=new struct FlexLine[MaxLen];
	}
	else{
		FL=tmpDim;
	}
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
	if(FL!=tmpDim){
		CopyFLine(FL,FLNumb);
		delete[] FL;
	}
	else{
		CopyFLine(FL,FLNumb);
	}

	return(*this);
}

FlexAreaFast    &FlexAreaFast::operator|=(const FlexAreaFast &src)
{
	int	MaxLen=GetFLineLen()+src.GetFLineLen();
	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *FL;
	if(MaxLen>MAXFlexAreaFastLines){
		FL=new struct FlexLine[MaxLen];
	}
	else{
		FL=tmpDim;
	}
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
	if(FL!=tmpDim){
		CopyFLine(FL,FLNumb);
		delete[] FL;
	}
	else{
		CopyFLine(FL,FLNumb);
	}

	return(*this);
}

bool        FlexAreaFast::operator==(const FlexAreaFast &src) const
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
bool        FlexAreaFast::operator!=(const FlexAreaFast &src) const
{
	return(!operator==(src));
}


qint64		FlexAreaFast::GetCrossCount(FlexAreaFast &src ,int dx ,int dy)    const
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

qint64		FlexAreaFast::GetCrossCount(int x1,int y1 ,int x2,int y2)     const
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

void    FlexAreaFast::ClipArea(int Left ,int Top ,int Right ,int Bottom)
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
void    FlexAreaFast::ClipArea(FlexAreaFast &BoundArea)
{
	int	MaxLen=GetFLineLen()+BoundArea.GetFLineLen();
	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *FL;
	if(MaxLen>MAXFlexAreaFastLines){
		FL=new struct FlexLine[MaxLen];
	}
	else{
		FL=tmpDim;
	}

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
	if(FL!=tmpDim){
		CopyFLine(FL,KNumb);
		delete[] FL;
	}
	else{
		CopyFLine(FL,KNumb);
	}
}

void    FlexAreaFast::ClipByMask(BYTE **Mask,int DotPerLine, int MaxLines)
{
	int	MaxLen=GetFLineLen()*10;
	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *FL;
	if(MaxLen>MAXFlexAreaFastLines){
		FL=new struct FlexLine[MaxLen];
	}
	else{
		FL=tmpDim;
	}
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
	if(FL!=tmpDim){
		delete	[]FL;
	}
	CopyFLine(tFL,FLIndex);
	delete[]tFL;
}

int     FlexAreaFast::MakeBrightList(int *BrList ,int DotPerLine, int MaxLines ,ImageBuffer &data,int dx ,int dy,int Isolation)
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

int     FlexAreaFast::MakeBrightList(unsigned int   *BrList ,int DotPerLine, int MaxLines ,ImageBuffer &data,int dx ,int dy,int Isolation)
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

int     FlexAreaFast::MakeBrightList(unsigned short *BrList ,int DotPerLine, int MaxLines ,ImageBuffer &data,int dx ,int dy,int Isolation)
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

void    FlexAreaFast::ThinAreaPartial(uchar **bmpdata,uchar **tmpdata,int xbyte ,int YLen)
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

void    FlexAreaFast::FatAreaPartial (int turn ,uchar **bmpdata,uchar **tmpdata,int xbyte ,int YLen)
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

void    FlexAreaFast::ThinAreaN(int TurnN)
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
void    FlexAreaFast::FatAreaN (int TurnN)
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
void    FlexAreaFast::ThinArea1(void)	//1âÊëfé˚èkÇµÇƒêÿÇÍÇÈèÍçáÅAécÇ∑
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

void    FlexAreaFast::GetLowHightColor(int dx,int dy,ImageBuffer &src	,int &LColor ,int &HColor ,int xdotperline ,int ymaxlines)
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
void    FlexAreaFast::GetLowHightColor(int dx,int dy,BYTE **src		,int &LColor ,int &HColor ,int xdotperline ,int ymaxlines)
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

void     FlexAreaFast::BuildFromRaster(uchar **srcdata ,int srcxbyte ,int srcylen
											,int px,int py)
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

	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *MFLines;
	if(Len>MAXFlexAreaFastLines){
		MFLines=new struct FlexLine[Len];
	}
	else{
		MFLines=tmpDim;
	}

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

	if(MFLines!=tmpDim){
		CopyFLine(MFLines,Len);
		delete	[]MFLines;
	}
	else{
		CopyFLine(MFLines,Len);
	}
}

void     FlexAreaFast::BuildFromRaster(uchar **srcdata ,int srcxbyte ,int srcylen
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
	struct FlexLine tmpDim[MAXFlexAreaFastLines];
	struct FlexLine *MFLines;
	if(Len>MAXFlexAreaFastLines){
		MFLines=new struct FlexLine[Len];
	}
	else{
		MFLines=tmpDim;
	}

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

	if(MFLines!=tmpDim){
		CopyFLine(MFLines,Len);
		delete	[]MFLines;
	}
	else{
		CopyFLine(MFLines,Len);
	}
}


//==============================================================================
FlexAreaFast &FlexAreaFastDim10::operator[](int index)
{
	if(0<=index && index<sizeof(Dim)/sizeof(Dim[0])){
		DimNumb=max(DimNumb,index+1);
	}
	return(Dim[index]);
}
FlexAreaFast &FlexAreaFastDim100::operator[](int index)
{
	if(0<=index && index<sizeof(Dim)/sizeof(Dim[0])){
		DimNumb=max(DimNumb,index+1);
	}
	return(Dim[index]);
}
FlexAreaFast &FlexAreaFastDim1000::operator[](int index)
{
	if(0<=index && index<sizeof(Dim)/sizeof(Dim[0])){
		DimNumb=max(DimNumb,index+1);
	}
	return(Dim[index]);
}

FlexAreaFastDimPack::FlexAreaFastDimPack(void)
{
	Dim100=NULL;
	Dim1000Counter=0;
}

FlexAreaFastDimPack::~FlexAreaFastDimPack(void)
{
	if(Dim100!=NULL){
		delete	Dim100;
	}
	for(int i=0;i<Dim1000Counter;i++){
		if(Dim1000[i]!=NULL){
			delete	Dim1000[i];
		}
	}
}

FlexAreaFast    &FlexAreaFastDimPack::operator[](int index)
{
	if(index<10){
		return Dim10[index];
	}
	index -= 10;
	if(index<100){
		if(Dim100==NULL){
			Dim100=new FlexAreaFastDim100();
		}
		return (*Dim100)[index];
	}
	index -= 100;

	int	i=index/1000;
	int	j=index%1000;
	while(i>=Dim1000Counter){
		Dim1000[Dim1000Counter]=new FlexAreaFastDim1000();
		Dim1000Counter++;
	}

	return(*Dim1000[i])[j];
}
int     FlexAreaFastDimPack::GetCount(void)	const
{
	int	Ret = Dim10.GetCount();
	if(Dim100!=NULL){
		Ret += Dim100->GetCount();
	}

	for(int i=0;i<Dim1000Counter;i++){
		if(Dim1000[i]!=NULL){
			Ret+=Dim1000[i]->GetCount();
		}
	}
	return Ret;
}
