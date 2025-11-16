/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFlexAreaNoOptimize.cpp
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

struct	PourFromImageStruct
{
	ImageBuffer	*Img;
	int		PickupL;
	int		PickupH;
	BYTE	**TmpMap;
	BYTE	**Mask;
	int		DotPerLine;
	int		XByte;
	int		YLen;
	int		MaxBuffSize;
	int		LMinX,LMaxX;
	int		LMinY,LMaxY;
	int		ReEntCounter;
	void	(*func)(void);
};

static	int	PickPours(int Left,int Right,int Y ,struct FlexLine *BuffLines,struct	PourFromImageStruct &PData)
{
	PData.ReEntCounter++;
	if((PData.ReEntCounter&0xFFF)==0 && PData.func!=NULL){
		PData.func();
	}
	BYTE	*s=PData.Img->GetY(Y);
	BYTE	*b=PData.TmpMap[Y];
	BYTE	*m=PData.Mask[Y];
	int	x;
	int	L,R;
	int	Count=0;
	for(x=Left;x>0 && x>PData.LMinX;x--){
		if(s[x]<PData.PickupL || PData.PickupH<s[x] || GetBmpBitOnY(b,x)!=0 || GetBmpBitOnY(m,x)!=0){
			break;
		}
		Left=x;
	}
	for(x=Right;x<PData.DotPerLine && x<PData.LMaxX;x++){
		if(s[x]<PData.PickupL || PData.PickupH<s[x] || GetBmpBitOnY(b,x)!=0 || GetBmpBitOnY(m,x)!=0){
			break;
		}
		Right=x;
	}
	for(x=Left;x<Right;x++){
		if(PData.PickupL<=s[x] && s[x]<=PData.PickupH && GetBmpBitOnY(b,x)==0 && GetBmpBitOnY(m,x)==0){
			L=x;
			R=x;
			for(;x<Right;x++){
				if(s[x]<PData.PickupL || PData.PickupH<s[x] || GetBmpBitOnY(b,x)!=0 || GetBmpBitOnY(m,x)!=0){
					break;
				}
			}
			R=x;
			if(PData.MaxBuffSize>0){
				BuffLines[Count]._SetLeftX(L);
				BuffLines[Count].SetNumb(R-L);
				BuffLines[Count]._SetAbsY(Y);
				for(int i=L;i<R;i++){
					SetBmpBitOnY1(b,i);
				}
				Count++;
				PData.MaxBuffSize--;

				if(PData.LMinX<=(L-1) && (L-1)<PData.LMaxX){
					L--;
				}
				if(L<0)
					L=0;
				if(PData.LMinX<=(R+1) && (R+1)<PData.LMaxX){
					R++;
				}
				if(R>=PData.DotPerLine){
					R=PData.DotPerLine;
				}
				if(Y>0){
					if(PData.LMinY<=(Y-1) && (Y-1)<PData.LMaxY){
						Count+=PickPours(L,R,Y-1 ,&BuffLines[Count],PData);
					}
				}
				if(PData.MaxBuffSize>0){
					if(Y<PData.Img->GetHeight()-1){
						if(PData.LMinY<=(Y+1) && (Y+1)<PData.LMaxY){
							Count+=PickPours(L,R,Y+1 ,&BuffLines[Count],PData);
						}
					}
				}
			}
		}
	}
	return Count;
}

static	int	PickPoursWithoutMask(int Left,int Right,int Y ,struct FlexLine *BuffLines,struct	PourFromImageStruct &PData)
{
	PData.ReEntCounter++;
	if((PData.ReEntCounter&0xFFF)==0 && PData.func!=NULL){
		PData.func();
	}
	BYTE	*s=PData.Img->GetY(Y);
	BYTE	*b=PData.TmpMap[Y];
	int	x;
	int	L,R;
	int	Count=0;
	for(x=Left;x>0 && x>PData.LMinX;x--){
		if(s[x]<PData.PickupL || PData.PickupH<s[x] || GetBmpBitOnY(b,x)!=0){
			break;
		}
		Left=x;
	}
	for(x=Right;x<PData.DotPerLine && x<PData.LMaxX;x++){
		if(s[x]<PData.PickupL || PData.PickupH<s[x] || GetBmpBitOnY(b,x)!=0){
			break;
		}
		Right=x;
	}
	for(x=Left;x<Right;x++){
		if(PData.PickupL<=s[x] && s[x]<=PData.PickupH && GetBmpBitOnY(b,x)==0){
			L=x;
			R=x;
			for(;x<Right;x++){
				if(s[x]<PData.PickupL || PData.PickupH<s[x] || GetBmpBitOnY(b,x)!=0){
					break;
				}
			}
			R=x;
			if(PData.MaxBuffSize>0){
				BuffLines[Count]._SetLeftX(L);
				BuffLines[Count].SetNumb(R-L);
				BuffLines[Count]._SetAbsY(Y);
				for(int i=L;i<R;i++){
					SetBmpBitOnY1(b,i);
				}
				Count++;
				PData.MaxBuffSize--;

				if(PData.LMinX<=(L-1) && (L-1)<PData.LMaxX){
					L--;
				}
				if(L<0)
					L=0;
				if(PData.LMinX<=(R+1) && (R+1)<PData.LMaxX){
					R++;
				}
				if(R>=PData.DotPerLine){
					R=PData.DotPerLine;
				}
				if(Y>0){
					if(PData.LMinY<=(Y-1) && (Y-1)<PData.LMaxY){
						Count+=PickPoursWithoutMask(L,R,Y-1 ,&BuffLines[Count],PData);
					}
				}
				if(PData.MaxBuffSize>0){
					if(Y<PData.Img->GetHeight()-1){
						if(PData.LMinY<=(Y+1) && (Y+1)<PData.LMaxY){
							Count+=PickPoursWithoutMask(L,R,Y+1 ,&BuffLines[Count],PData);
						}
					}
				}
			}
		}
	}
	return Count;
}

void	FlexArea::PourFromImage(ImageBuffer &Img 
					,BYTE **Mask
					,int StartX, int StartY
					,int PickupL ,int PickupH
					,void (*func)(void)
					,int MaxBuffCount
					,int MaxSizeXLen,int MaxSizeYLen
					,BYTE **TmpMap)
{
	if(StartY<0 || Img.GetHeight()<=StartY)
		return;

	int	L,R;
	BYTE	*s=Img.GetY(StartY);
	int	LMinX=StartX-MaxSizeXLen/2;
	if(LMinX<0){
		LMinX=0;
	}
	int	LMaxX=MaxSizeXLen;
	if(LMaxX>Img.GetWidth()){
		LMaxX=Img.GetWidth();
		LMinX=LMaxX-MaxSizeXLen;
		if(LMinX<0){
			LMinX=0;
		}
	}
	int	LMinY=StartY-MaxSizeYLen/2;
	if(LMinY<0){
		LMinY=0;
	}
	int	LMaxY=MaxSizeYLen;
	if(LMaxY>Img.GetHeight()){
		LMaxY=Img.GetHeight();
		LMinY=LMaxY-MaxSizeYLen;
		if(LMinY<0){
			LMinY=0;
		}
	}

	L=max(0,StartX);
	R=min(StartX,Img.GetWidth());
	if(Mask!=NULL){
		for(int l=StartX;l>=0 && l>=LMinX;l--){
			if(0<=l && l<Img.GetWidth() && l<MaxSizeXLen){
				int	c=s[l];
				if(c<PickupL || PickupH<c
				|| GetBmpBit(Mask,l,StartY)!=0){
					break;
				}
				L=l;
			}
		}
		for(int r=StartX;r<Img.GetWidth() && r<LMaxX;r++){
			if(0<=r && r<Img.GetWidth() && r<MaxSizeXLen){
				int	c=s[r];
				if(c<PickupL || PickupH<c
				|| GetBmpBit(Mask,r,StartY)!=0){
					break;
				}
				R=r;
			}
		}
	}
	else{
		for(int l=StartX;l>=0 && l>=LMinX;l--){
			if(0<=l && l<Img.GetWidth() && l<MaxSizeXLen){
				int	c=s[l];
				if(c<PickupL || PickupH<c){
					break;
				}
				L=l;
			}
		}
		for(int r=StartX;r<Img.GetWidth() && r<LMaxX;r++){
			if(0<=r && r<Img.GetWidth() && r<MaxSizeXLen){
				int	c=s[r];
				if(c<PickupL || PickupH<c){
					break;
				}
				R=r;
			}
		}
	}
	if(L>R){
		return;
	}
	struct	PourFromImageStruct	PData;

	PData.Img=&Img;
	PData.DotPerLine	=Img.GetWidth();
	PData.XByte			=(Img.GetWidth()+7)/8;
	PData.YLen			=Img.GetHeight();
	if(TmpMap==NULL){
		PData.TmpMap=MakeMatrixBuff(PData.XByte,PData.YLen);
		MatrixBuffClear(PData.TmpMap,0,PData.XByte,PData.YLen);
	}
	else{
		PData.TmpMap=TmpMap;
	}
	PData.Mask			=Mask;
	PData.MaxBuffSize	=MaxBuffCount;
	PData.PickupL		=PickupL;
	PData.PickupH		=PickupH;
	PData.LMinX			=LMinX;
	PData.LMaxX			=LMaxX;
	PData.LMinY			=LMinY;
	PData.LMaxY			=LMaxY;
	PData.ReEntCounter	=0;
	PData.func			=func;
	//MatrixBuffClear(PData.TmpMap,0,PData.XByte,PData.YLen);

	struct   FlexLine	*BuffLines=new struct FlexLine[MaxBuffCount];
	int	Count;
	if(Mask!=NULL){
		Count=PickPours(L,R,StartY,BuffLines,PData);
	}
	else{
		Count=PickPoursWithoutMask(L,R,StartY,BuffLines,PData);
	}

	if(TmpMap==NULL){
		DeleteMatrixBuff(PData.TmpMap,PData.YLen);
	}
	if(Count>0){
		struct FlexLine	*FL=new struct FlexLine[Count];
		memcpy(FL,BuffLines,sizeof(struct FlexLine)*Count);

		//QSort(FL,Count,sizeof(FL[0]),YSortFunc);
		SetFLine(FL,Count);
		//Restruct();
	}
	delete	[]BuffLines;

	if(TmpMap!=NULL){
		MakeNotBitData(TmpMap ,PData.DotPerLine,PData.YLen);
	}
}

void	FlexArea::PourFromImage(ImageBuffer &Img 
					,BYTE **Mask
					,int StartX, int StartY
					,int PickupL ,int PickupH
					,void (*func)(void)
					,int MaxBuffCount,struct   FlexLine	*BuffLines
					,int MaxSizeXLen,int MaxSizeYLen
					,BYTE **TmpMap)
{
	if(StartY<0 || Img.GetHeight()<=StartY)
		return;

	int	L,R;
	BYTE	*s=Img.GetY(StartY);
	int	LMinX=StartX-MaxSizeXLen/2;
	if(LMinX<0){
		LMinX=0;
	}
	int	LMaxX=MaxSizeXLen;
	if(LMaxX>Img.GetWidth()){
		LMaxX=Img.GetWidth();
		LMinX=LMaxX-MaxSizeXLen;
		if(LMinX<0){
			LMinX=0;
		}
	}
	int	LMinY=StartY-MaxSizeYLen/2;
	if(LMinY<0){
		LMinY=0;
	}
	int	LMaxY=MaxSizeYLen;
	if(LMaxY>Img.GetHeight()){
		LMaxY=Img.GetHeight();
		LMinY=LMaxY-MaxSizeYLen;
		if(LMinY<0){
			LMinY=0;
		}
	}

	L=max(0,StartX);
	R=min(StartX,Img.GetWidth());
	if(Mask!=NULL){
		for(int l=StartX;l>=0 && l>=LMinX;l--){
			if(0<=l && l<Img.GetWidth() && l<MaxSizeXLen){
				int	c=s[l];
				if(c<PickupL || PickupH<c
				|| GetBmpBit(Mask,l,StartY)!=0){
					break;
				}
				L=l;
			}
		}
		for(int r=StartX;r<Img.GetWidth() && r<LMaxX;r++){
			if(0<=r && r<Img.GetWidth() && r<MaxSizeXLen){
				int	c=s[r];
				if(c<PickupL || PickupH<c
				|| GetBmpBit(Mask,r,StartY)!=0){
					break;
				}
				R=r;
			}
		}
	}
	else{
		for(int l=StartX;l>=0 && l>=LMinX;l--){
			if(0<=l && l<Img.GetWidth() && l<MaxSizeXLen){
				int	c=s[l];
				if(c<PickupL || PickupH<c){
					break;
				}
				L=l;
			}
		}
		for(int r=StartX;r<Img.GetWidth() && r<LMaxX;r++){
			if(0<=r && r<Img.GetWidth() && r<MaxSizeXLen){
				int	c=s[r];
				if(c<PickupL || PickupH<c){
					break;
				}
				R=r;
			}
		}
	}
	if(L>R){
		return;
	}
	struct	PourFromImageStruct	PData;

	PData.Img=&Img;
	PData.DotPerLine	=Img.GetWidth();
	PData.XByte			=(Img.GetWidth()+7)/8;
	PData.YLen			=Img.GetHeight();
	if(TmpMap==NULL){
		PData.TmpMap=MakeMatrixBuff(PData.XByte,PData.YLen);
		MatrixBuffClear(PData.TmpMap,0,PData.XByte,PData.YLen);
	}
	else{
		PData.TmpMap=TmpMap;
	}
	PData.Mask			=Mask;
	PData.MaxBuffSize	=MaxBuffCount;
	PData.PickupL		=PickupL;
	PData.PickupH		=PickupH;
	PData.LMinX			=LMinX;
	PData.LMaxX			=LMaxX;
	PData.LMinY			=LMinY;
	PData.LMaxY			=LMaxY;
	PData.ReEntCounter	=0;
	PData.func			=func;
	//MatrixBuffClear(PData.TmpMap,0,PData.XByte,PData.YLen);

	int	Count;
	if(Mask!=NULL){
		Count=PickPours(L,R,StartY,BuffLines,PData);
	}
	else{
		Count=PickPoursWithoutMask(L,R,StartY,BuffLines,PData);
	}

	if(TmpMap==NULL){
		DeleteMatrixBuff(PData.TmpMap,PData.YLen);
	}

	if(Count>0){
		struct FlexLine	*FL=new struct FlexLine[Count];
		memcpy(FL,BuffLines,sizeof(struct FlexLine)*Count);

		//QSort(FL,Count,sizeof(FL[0]),YSortFunc);
		SetFLine(FL,Count);
		//Restruct();
	}

	if(TmpMap!=NULL){
		MakeNotBitData(TmpMap ,PData.DotPerLine,PData.YLen);
	}
}

struct	PourFromImageStructColor
{
	ImagePointerContainer	*Img;
	ColorLogic	*PickupColor;
	BYTE	**TmpMap;
	BYTE	**Mask;
	int		DotPerLine;
	int		XByte;
	int		YLen;
	int		MaxBuffSize;
	int		StackLevel;
	int		LMinX,LMaxX;
	int		LMinY,LMaxY;
	int		ReEntCounter;
	void	(*func)(void);
};

#define	MaxStackLevelInPour	10000

static	int	PickPours(int Left,int Right,int Y ,struct FlexLine *BuffLines,struct	PourFromImageStructColor &PData)
{
	PData.StackLevel++;
	if(PData.StackLevel>MaxStackLevelInPour){
		return 0;
	}
	PData.ReEntCounter++;
	if((PData.ReEntCounter&0xFFF)==0 && PData.func!=NULL){
		PData.func();
	}

	BYTE	*b=PData.TmpMap[Y];
	BYTE	*m=PData.Mask[Y];
	int	x;
	int	L,R;
	int	Count=0;
	for(x=Left;x>0 && x>PData.LMinX;x--){
		if(PData.DotPerLine!=0 && x>=PData.DotPerLine){
			continue;
		}
		if(PData.PickupColor->Calc((BYTE)(*PData.Img)[0]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[1]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[2]->GetY(Y)[x],0)==false
		|| GetBmpBitOnY(b,x)!=0 || GetBmpBitOnY(m,x)!=0){
			break;
		}
		Left=x;
	}
	for(x=Right;x<(*PData.Img)[0]->GetWidth() && x<PData.LMaxX;x++){
		if(x<0){
			continue;
		}
		if(PData.PickupColor->Calc((BYTE)(*PData.Img)[0]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[1]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[2]->GetY(Y)[x],0)==false
		|| GetBmpBitOnY(b,x)!=0 || GetBmpBitOnY(m,x)!=0){
			break;
		}
		Right=x;
	}

	for(x=Left;x<Right;x++){
		if(x<0){
			continue;
		}
		if(PData.PickupColor->Calc((BYTE)(*PData.Img)[0]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[1]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[2]->GetY(Y)[x],0)==true
		&& GetBmpBitOnY(b,x)==0 && GetBmpBitOnY(m,x)==0){
		//if(PData.PickupL<=s[x] && s[x]<=PData.PickupH && GetBmpBitOnY(b,x)==0){
			L=x;
			R=x;
			for(;x<Right;x++){
				if(PData.PickupColor->Calc((BYTE)(*PData.Img)[0]->GetY(Y)[x]
										  ,(BYTE)(*PData.Img)[1]->GetY(Y)[x]
										  ,(BYTE)(*PData.Img)[2]->GetY(Y)[x],0)==false
				 || GetBmpBitOnY(b,x)!=0 || GetBmpBitOnY(m,x)!=0){
					break;
				}
			}
			R=x;
			if(PData.MaxBuffSize>0){
				BuffLines[Count]._SetLeftX(L);
				BuffLines[Count].SetNumb(R-L);
				BuffLines[Count]._SetAbsY(Y);
				for(int i=L;i<R;i++){
					SetBmpBitOnY1(b,i);
				}
				Count++;
				PData.MaxBuffSize--;

				if(PData.LMinX<=(L-1) && (L-1)<PData.LMaxX){
					L--;
				}
				if(L<0)
					L=0;
				if(PData.LMinX<=(R+1) && (R+1)<PData.LMaxX){
					R++;
				}
				if(R>=(*PData.Img)[0]->GetWidth()){
					R=(*PData.Img)[0]->GetWidth();
				}
				if(Y>0){
					if(PData.LMinY<=(Y-1) && (Y-1)<PData.LMaxY){
						Count+=PickPours(L,R,Y-1 ,&BuffLines[Count],PData);
						PData.StackLevel--;
					}
				}
				if(PData.MaxBuffSize>0){
					if(Y<(*PData.Img)[0]->GetHeight()-1){
						if(PData.LMinY<=(Y+1) && (Y+1)<PData.LMaxY){
							Count+=PickPours(L,R,Y+1 ,&BuffLines[Count],PData);
							PData.StackLevel--;
						}
					}
				}
			}
		}
	}
	return Count;
}



void	FlexArea::PourFromImage(ImagePointerContainer &Images
						,BYTE **Mask
						,int StartX, int StartY
						,ColorLogic &Color
						,void (*func)(void)
						,int MaxBuffCount
						,int MaxSize)
{
	struct   FlexLine	*BuffLines=new struct FlexLine[MaxBuffCount];

	int	L,R;
	BYTE	*s[100];

	int	LMinX=StartX-MaxSize/2;
	if(LMinX<0){
		LMinX=0;
	}
	int	LMaxX=LMinX+MaxSize;
	if(LMaxX>Images[0]->GetWidth()){
		LMaxX=Images[0]->GetWidth();
		LMinX=LMaxX-MaxSize;
		if(LMinX<0){
			LMinX=0;
		}
	}
	int	LMinY=StartY-MaxSize/2;
	if(LMinY<0){
		LMinY=0;
	}
	int	LMaxY=LMinY+MaxSize;
	if(LMaxY>Images[0]->GetHeight()){
		LMaxY=Images[0]->GetHeight();
		LMinY=LMaxY-MaxSize;
		if(LMinY<0){
			LMinY=0;
		}
	}
	int	layer=0;
	for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext()){
		s[layer]=Images[layer]->GetY(StartY);
		layer++;
	}
	for(int l=StartX;l>=0 && l>=LMinX;l--){
		if(Color.Calc(*((s[0])+l),*((s[1])+l),*((s[2])+l),0)==false
		|| GetBmpBit(Mask,l,StartY)!=0){
			break;
		}
		L=l;
	}
	for(int r=StartX;r<Images[0]->GetWidth() && r<LMaxX;r++){
		if(Color.Calc(*((s[0])+r),*((s[1])+r),*((s[2])+r),0)==false
		|| GetBmpBit(Mask,r,StartY)!=0){
			break;
		}
		R=r;
	}
	struct	PourFromImageStructColor	PData;

	PData.Img=&Images;
	PData.DotPerLine	=Images[0]->GetWidth();
	PData.XByte			=(Images[0]->GetWidth()+7)/8;
	PData.YLen			=Images[0]->GetHeight();
	PData.TmpMap		=MakeMatrixBuff(PData.XByte,PData.YLen);
	PData.MaxBuffSize	=MaxBuffCount;
	PData.StackLevel	=0;
	PData.Mask			=Mask;
	PData.LMinX			=LMinX;
	PData.LMaxX			=LMaxX;
	PData.LMinY			=LMinY;
	PData.LMaxY			=LMaxY;
	PData.PickupColor	=&Color;
	PData.ReEntCounter	=0;
	PData.func			=func;
	MatrixBuffClear(PData.TmpMap,0,PData.XByte,PData.YLen);

	int	Count=PickPours(L,R,StartY,BuffLines,PData);
	DeleteMatrixBuff(PData.TmpMap,PData.YLen);

	struct FlexLine	*FL=new struct FlexLine[Count];
	memcpy(FL,BuffLines,sizeof(struct FlexLine)*Count);
	delete	[]BuffLines;

	QSort(FL,Count,sizeof(FL[0]),YSortFunc);
	SetFLine(FL,Count);
	//Restruct();
}

//===============================================================================================
struct	PourFromImageStructColorN
{
	ImagePointerContainer	*Img;
	ColorLogic	*PickupColor;
	BYTE	**TmpMap;
	BYTE	**Mask;
	int		LayerNumb;
	int		DotPerLine;
	int		XByte;
	int		YLen;
	int		*LMinX,*LMaxX;
	int		*LMinY,*LMaxY;
	int		MaxSize;
	int		ReEntCounter;
	int		BandMinY;
	int		BandMaxY;
	int		BandCount;
	void	(*func)(void);
	struct   FlexLine	*BuffLines;
	int		NLen;
	int		AllocatedBuffLines;
};

static	bool	PickPours(int Left,int Right,int Y ,struct	PourFromImageStructColorN &PData)
{
	PData.ReEntCounter++;
	if((PData.ReEntCounter&0xFFF)==0 && PData.func!=NULL){
		PData.func();
	}

	BYTE	*b=PData.TmpMap[Y];
	BYTE	*m=(PData.Mask!=NULL)?PData.Mask[Y]:NULL;

	int	L0=0;
	int	L1=0;
	int	L2=0;
	if(PData.LayerNumb>=3){
		L0=0;
		L1=1;
		L2=2;
	}
	else
	if(PData.LayerNumb==2){
		L0=0;
		L1=1;
		L2=1;
	}
	else
	if(PData.LayerNumb==1){
		L0=0;
		L1=0;
		L2=0;
	}

	int	x;
	int	L,R;
	bool	Ret=false;
	for(x=Left;x>0 && (*PData.LMaxX-x)<PData.MaxSize;x--){
		if(PData.DotPerLine!=0 && x>=PData.DotPerLine){
			continue;
		}
		if(PData.PickupColor->Calc((BYTE)(*PData.Img)[L0]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[L1]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[L2]->GetY(Y)[x],0)==false
		|| GetBmpBitOnY(b,x)!=0 || (m!=NULL && GetBmpBitOnY(m,x)!=0)){
			break;
		}
		Left=x;
	}
	int	tMinL=min(Left,*PData.LMinX);
	for(x=Right;x<(*PData.Img)[0]->GetWidth() && (x-tMinL)<PData.MaxSize;x++){
		if(x<0){
			continue;
		}
		if(PData.PickupColor->Calc((BYTE)(*PData.Img)[L0]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[L1]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[L2]->GetY(Y)[x],0)==false
		|| GetBmpBitOnY(b,x)!=0 || (m!=NULL && GetBmpBitOnY(m,x)!=0)){
			break;
		}
		Right=x;
	}

	for(x=Left;x<Right;x++){
		if(x<0){
			continue;
		}
		if(PData.PickupColor->Calc((BYTE)(*PData.Img)[L0]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[L1]->GetY(Y)[x]
								  ,(BYTE)(*PData.Img)[L2]->GetY(Y)[x],0)==true
		&& GetBmpBitOnY(b,x)==0 && (m==NULL || GetBmpBitOnY(m,x)==0)){
		//if(PData.PickupL<=s[x] && s[x]<=PData.PickupH && GetBmpBitOnY(b,x)==0){
			L=x;
			R=x;
			for(;x<Right;x++){
				if(PData.PickupColor->Calc((BYTE)(*PData.Img)[L0]->GetY(Y)[x]
										  ,(BYTE)(*PData.Img)[L1]->GetY(Y)[x]
										  ,(BYTE)(*PData.Img)[L2]->GetY(Y)[x],0)==false
				 || GetBmpBitOnY(b,x)!=0 || (m!=NULL && GetBmpBitOnY(m,x)!=0)){
					break;
				}
			}
			R=x;
			if(PData.NLen==PData.AllocatedBuffLines){
				PData.AllocatedBuffLines+=1000;
				struct   FlexLine	*t=new struct FlexLine[PData.AllocatedBuffLines];
				memcpy(t,PData.BuffLines,PData.NLen*sizeof(struct FlexLine));
				delete	[]PData.BuffLines;
				PData.BuffLines=t;
			}
			Ret=true;
			PData.BuffLines[PData.NLen]._SetLeftX(L);
			PData.BuffLines[PData.NLen].SetNumb(R-L);
			PData.BuffLines[PData.NLen]._SetAbsY(Y);
			for(int i=L;i<R;i++){
				SetBmpBitOnY1(b,i);
			}
			PData.NLen++;

			*PData.LMinX=min(L,*PData.LMinX);
			*PData.LMaxX=max(R,*PData.LMaxX);
			*PData.LMinY=min(Y,*PData.LMinY);
			*PData.LMaxY=max(Y,*PData.LMaxY);

			L--;
			if(L<0)
				L=0;
			R++;
			if(R>=(*PData.Img)[0]->GetWidth()){
				R=(*PData.Img)[0]->GetWidth();
			}
			if(Y>0 && (Y-1)>=PData.BandMinY){
				if((*PData.LMaxY-(Y-1))<=PData.MaxSize){
					if(PickPours(L,R,Y-1 ,PData)==true){
						Ret=true;
					}
				}
			}
			if((Y+1)<PData.YLen && (Y+1)<PData.BandMaxY){
				if((Y+1)-*PData.LMaxY<=PData.MaxSize){
					if(PickPours(L,R,Y+1 ,PData)==true){
						Ret=true;
					}
				}
			}
			x=R;
		}
	}
	return Ret;
}


static	void	MakePickBand(int Left,int Right,int Y ,int BandNo ,struct PourFromImageStructColorN *PData)
{
	if((PData[BandNo].Mask==NULL || (GetBmpBit(PData[BandNo].Mask,Left,Y)!=0 && GetBmpBit(PData[BandNo].Mask,Right,Y)!=0)) 
	&& (GetBmpBit(PData[BandNo].TmpMap,Left,Y)==0 || GetBmpBit(PData[BandNo].TmpMap,Right,Y)==0)){
		if(PickPours(Left,Right,Y ,PData[BandNo])==true){
			QSort(PData[BandNo].BuffLines,PData[BandNo].NLen,sizeof(struct FlexLine),YSortFunc);
			if(BandNo>0){
				for(int i=0;i<PData[BandNo].NLen;i++){
					int	Y=PData[BandNo].BuffLines[i]._GetAbsY();
					if(Y>PData[BandNo].BandMinY)
						break;
					Left =PData[BandNo].BuffLines[i]._GetLeftX();
					Right=PData[BandNo].BuffLines[i]._GetRightX();
					MakePickBand(Left,Right,Y-1 ,BandNo-1 ,PData);
				}
			}
			if((BandNo+1)<PData[BandNo].BandCount){
				for(int i=PData[BandNo].NLen-1;i>=0;i--){
					int	Y=PData[BandNo].BuffLines[i]._GetAbsY();
					if((Y+1)<PData[BandNo].BandMaxY)
						break;
					Left =PData[BandNo].BuffLines[i]._GetLeftX();
					Right=PData[BandNo].BuffLines[i]._GetRightX();
					MakePickBand(Left,Right,Y+1 ,BandNo+1 ,PData);
				}
			}
		}
	}
}

void	FlexArea::PourFromImageLimitless(ImagePointerContainer &Images
						,BYTE **Mask
						,int StartX, int StartY
						,ColorLogic &Color
						,void (*func)(void)
						,int MaxSize)
{
	int	L=0;
	int	R=0;
	BYTE	*s[100];

	int	LMaxSize=(MaxSize>=0)?MaxSize:max(Images[0]->GetWidth(),Images[0]->GetHeight());

	int	layer=0;
	for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext()){
		s[layer]=Images[layer]->GetY(StartY);
		layer++;
	}

	if(layer>=3){
		for(int l=StartX;l>=0 && (StartX-l)<=LMaxSize;l--){
			if(Color.Calc(*((s[0])+l),*((s[1])+l),*((s[2])+l),0)==false
			|| (Mask!=NULL && GetBmpBit(Mask,l,StartY)!=0)){
				break;
			}
			L=l;
		}
		for(int r=StartX;r<Images[0]->GetWidth() && (r-StartX)<=LMaxSize && (r-L)<=LMaxSize;r++){
			if(Color.Calc(*((s[0])+r),*((s[1])+r),*((s[2])+r),0)==false
			||  (Mask!=NULL && GetBmpBit(Mask,r,StartY)!=0)){
				break;
			}
			R=r;
		}
	}
	else
	if(layer==2){
		for(int l=StartX;l>=0 && (StartX-l)<=LMaxSize;l--){
			if(Color.Calc(*((s[0])+l),*((s[1])+l),*((s[1])+l),0)==false
			|| (Mask!=NULL && GetBmpBit(Mask,l,StartY)!=0)){
				break;
			}
			L=l;
		}
		for(int r=StartX;r<Images[0]->GetWidth() && (r-StartX)<=LMaxSize && (r-L)<=LMaxSize;r++){
			if(Color.Calc(*((s[0])+r),*((s[1])+r),*((s[1])+r),0)==false
			||  (Mask!=NULL && GetBmpBit(Mask,r,StartY)!=0)){
				break;
			}
			R=r;
		}
	}
	else
	if(layer==1){
		for(int l=StartX;l>=0 && (StartX-l)<=LMaxSize;l--){
			if(Color.Calc(*((s[0])+l),*((s[0])+l),*((s[0])+l),0)==false
			|| (Mask!=NULL && GetBmpBit(Mask,l,StartY)!=0)){
				break;
			}
			L=l;
		}
		for(int r=StartX;r<Images[0]->GetWidth() && (r-StartX)<=LMaxSize && (r-L)<=LMaxSize;r++){
			if(Color.Calc(*((s[0])+r),*((s[0])+r),*((s[0])+r),0)==false
			||  (Mask!=NULL && GetBmpBit(Mask,r,StartY)!=0)){
				break;
			}
			R=r;
		}
	}


	int	BandHeight=2000;
	int	BandCount=(Images[0]->GetHeight()+BandHeight-1)/BandHeight;

	struct	PourFromImageStructColorN	*PData=new struct	PourFromImageStructColorN[BandCount];
	int	CIndex=StartY/BandHeight;

	int		LMinX	=L;
	int		LMaxX	=R;
	int		LMinY	=StartY;
	int		LMaxY	=StartY;
	int		XByte	=(Images[0]->GetWidth()+7)/8;
	int		YLen	=Images[0]->GetHeight();
	BYTE	**TmpMap=MakeMatrixBuff(XByte,YLen);

	for(int i=0;i<BandCount;i++){
		PData[i].Img=&Images;
		PData[i].LayerNumb		=layer;
		PData[i].DotPerLine		=Images[0]->GetWidth();
		PData[i].XByte			=XByte;
		PData[i].YLen			=YLen;
		PData[i].TmpMap			=TmpMap;
		PData[i].Mask			=Mask;
		PData[i].MaxSize		=LMaxSize;
		PData[i].LMinX			=&LMinX;
		PData[i].LMaxX			=&LMaxX;
		PData[i].LMinY			=&LMinY;
		PData[i].LMaxY			=&LMaxY;
		PData[i].BandMinY		=i*BandHeight;
		PData[i].BandMaxY		=i*BandHeight+BandHeight;
		PData[i].BandCount		=BandCount;
		PData[i].PickupColor	=&Color;
		PData[i].ReEntCounter	=0;
		PData[i].func			=func;
		PData[i].AllocatedBuffLines	=100;
		PData[i].NLen			=0;
		PData[i].BuffLines		=new struct FlexLine[100];
	}
	MatrixBuffClear(TmpMap,0,XByte,YLen);
	MakePickBand(L,R,StartY ,CIndex ,PData);

	int	NLen=0;
	for(int i=0;i<BandCount;i++){
		NLen+=PData[i].NLen;
	}
	struct FlexLine	*FL=new struct FlexLine[NLen];
	int	n=0;
	for(int i=0;i<BandCount;i++){
		memcpy(&FL[n],PData[i].BuffLines,sizeof(struct FlexLine)*PData[i].NLen);
		delete	[]PData[i].BuffLines;
		n+=PData[i].NLen;
		
	}
	DeleteMatrixBuff(TmpMap,YLen);

	QSort(FL,n,sizeof(FL[0]),YSortFunc);
	SetFLine(FL,n);
	//Restruct();
}

//===============================================================================================
struct	PourFromImageStructN
{
	ImageBuffer	*Img;
	int		PickupL ,PickupH;
	BYTE	**TmpMap;
	BYTE	**Mask;
	int		DotPerLine;
	int		XByte;
	int		YLen;
	int		*LMinX,*LMaxX;
	int		*LMinY,*LMaxY;
	int		MaxSize;
	int		ReEntCounter;
	int		BandMinY;
	int		BandMaxY;
	int		BandCount;
	void	(*func)(void);
	struct   FlexLine	*BuffLines;
	int		NLen;
	int		AllocatedBuffLines;
};

static	bool	PickPours(int Left,int Right,int Y ,struct	PourFromImageStructN &PData)
{
	PData.ReEntCounter++;
	if((PData.ReEntCounter&0xFFF)==0 && PData.func!=NULL){
		PData.func();
	}

	BYTE	*b=PData.TmpMap[Y];
	BYTE	*m=(PData.Mask!=NULL)?PData.Mask[Y]:NULL;

	int	x;
	int	L,R;
	bool	Ret=false;
	for(x=Left;x>0 && (*PData.LMaxX-x)<PData.MaxSize;x--){
		if(PData.DotPerLine!=0 && x>=PData.DotPerLine){
			continue;
		}
		if(((PData.Img->GetY(Y)[x]<PData.PickupL) || (PData.PickupH<PData.Img->GetY(Y)[x]))
		|| GetBmpBitOnY(b,x)!=0 || (m!=NULL && GetBmpBitOnY(m,x)!=0)){
			break;
		}
		Left=x;
	}
	int	tMinL=min(Left,*PData.LMinX);
	for(x=Right;x<PData.Img->GetWidth() && (x-tMinL)<PData.MaxSize;x++){
		if(x<0){
			continue;
		}
		if(((PData.Img->GetY(Y)[x]<PData.PickupL) || (PData.PickupH<PData.Img->GetY(Y)[x]))
		|| GetBmpBitOnY(b,x)!=0 || (m!=NULL && GetBmpBitOnY(m,x)!=0)){
			break;
		}
		Right=x;
	}

	for(x=Left;x<Right;x++){
		if(x<0){
			continue;
		}
		if(((PData.PickupL<=PData.Img->GetY(Y)[x]) && (PData.Img->GetY(Y)[x]<=PData.PickupH))
		&& GetBmpBitOnY(b,x)==0 && (m==NULL || GetBmpBitOnY(m,x)==0)){
		//if(PData.PickupL<=s[x] && s[x]<=PData.PickupH && GetBmpBitOnY(b,x)==0){
			L=x;
			R=x;
			for(;x<Right;x++){
				if(((PData.Img->GetY(Y)[x]<PData.PickupL) || (PData.PickupH<PData.Img->GetY(Y)[x]))
				 || GetBmpBitOnY(b,x)!=0 || (m!=NULL && GetBmpBitOnY(m,x)!=0)){
					break;
				}
			}
			R=x;
			if(PData.NLen==PData.AllocatedBuffLines){
				PData.AllocatedBuffLines+=1000;
				struct   FlexLine	*t=new struct FlexLine[PData.AllocatedBuffLines];
				memcpy(t,PData.BuffLines,PData.NLen*sizeof(struct FlexLine));
				delete	[]PData.BuffLines;
				PData.BuffLines=t;
			}
			Ret=true;
			PData.BuffLines[PData.NLen]._SetLeftX(L);
			PData.BuffLines[PData.NLen].SetNumb(R-L);
			PData.BuffLines[PData.NLen]._SetAbsY(Y);
			for(int i=L;i<R;i++){
				SetBmpBitOnY1(b,i);
			}
			PData.NLen++;

			*PData.LMinX=min(L,*PData.LMinX);
			*PData.LMaxX=max(R,*PData.LMaxX);
			*PData.LMinY=min(Y,*PData.LMinY);
			*PData.LMaxY=max(Y,*PData.LMaxY);

			L--;
			if(L<0)
				L=0;
			R++;
			if(R>=PData.Img->GetWidth()){
				R=PData.Img->GetWidth();
			}
			if(Y>0 && (Y-1)>=PData.BandMinY){
				if(*PData.LMaxY-(Y-1)<=PData.MaxSize){
					if(PickPours(L,R,Y-1 ,PData)==true){
						Ret=true;
					}
				}
			}
			if((Y+1)<PData.YLen && (Y+1)<PData.BandMaxY){
				if((Y+1)-*PData.LMaxY<=PData.MaxSize){
					if(PickPours(L,R,Y+1 ,PData)==true){
						Ret=true;
					}
				}
			}
			x=R;
		}
	}
	return Ret;
}


static	void	MakePickBand(int Left,int Right,int Y ,int BandNo ,struct PourFromImageStructN *PData)
{
	if((PData[BandNo].Mask==NULL || (GetBmpBit(PData[BandNo].Mask,Left,Y)!=0 && GetBmpBit(PData[BandNo].Mask,Right,Y)!=0)) 
	&& (GetBmpBit(PData[BandNo].TmpMap,Left,Y)==0 || GetBmpBit(PData[BandNo].TmpMap,Right,Y)==0)){
		if(PickPours(Left,Right,Y ,PData[BandNo])==true){
			QSort(PData[BandNo].BuffLines,PData[BandNo].NLen,sizeof(struct FlexLine),YSortFunc);
			if(BandNo>0){
				for(int i=0;i<PData[BandNo].NLen;i++){
					int	Y=PData[BandNo].BuffLines[i]._GetAbsY();
					if(Y>PData[BandNo].BandMinY)
						break;
					Left =PData[BandNo].BuffLines[i]._GetLeftX();
					Right=PData[BandNo].BuffLines[i]._GetRightX();
					MakePickBand(Left,Right,Y-1 ,BandNo-1 ,PData);
				}
			}
			if((BandNo+1)<PData[BandNo].BandCount){
				for(int i=PData[BandNo].NLen-1;i>=0;i--){
					int	Y=PData[BandNo].BuffLines[i]._GetAbsY();
					if((Y+1)<PData[BandNo].BandMaxY)
						break;
					Left =PData[BandNo].BuffLines[i]._GetLeftX();
					Right=PData[BandNo].BuffLines[i]._GetRightX();
					MakePickBand(Left,Right,Y+1 ,BandNo+1 ,PData);
				}
			}
		}
	}
}

void	FlexArea::PourFromImageLimitless(ImageBuffer &Image
						,BYTE **Mask
						,int StartX, int StartY
						,int PickupL ,int PickupH
						,void (*func)(void)
						,int MaxSize)
{
	int	L=0;
	int	R=0;

	int	LMaxSize=(MaxSize>=0)?MaxSize:max(Image.GetWidth(),Image.GetHeight());

	BYTE	*s=Image.GetY(StartY);
	for(int l=StartX;l>=0 && (StartX-l)<=LMaxSize;l--){
		if(s[l]<PickupL || PickupH<s[l]
		|| (Mask!=NULL && GetBmpBit(Mask,l,StartY)!=0)){
			break;
		}
		L=l;
	}
	for(int r=StartX;r<Image.GetWidth() && (r-StartX)<=LMaxSize && (r-L)<=LMaxSize;r++){
		if(s[r]<PickupL || PickupH<s[r]
		||  (Mask!=NULL && GetBmpBit(Mask,r,StartY)!=0)){
			break;
		}
		R=r;
	}

	int	BandHeight=2000;
	int	BandCount=(Image.GetHeight()+BandHeight-1)/BandHeight;

	struct	PourFromImageStructN	*PData=new struct PourFromImageStructN[BandCount];
	int	CIndex=StartY/BandHeight;

	int		LMinX	=L;
	int		LMaxX	=R;
	int		LMinY	=StartY;
	int		LMaxY	=StartY;
	int		XByte	=(Image.GetWidth()+7)/8;
	int		YLen	=Image.GetHeight();
	BYTE	**TmpMap=MakeMatrixBuff(XByte,YLen);

	for(int i=0;i<BandCount;i++){
		PData[i].Img=&Image;
		PData[i].DotPerLine		=Image.GetWidth();
		PData[i].XByte			=XByte;
		PData[i].YLen			=YLen;
		PData[i].TmpMap			=TmpMap;
		PData[i].Mask			=Mask;
		PData[i].MaxSize		=LMaxSize;
		PData[i].LMinX			=&LMinX;
		PData[i].LMaxX			=&LMaxX;
		PData[i].LMinY			=&LMinY;
		PData[i].LMaxY			=&LMaxY;
		PData[i].BandMinY		=i*BandHeight;
		PData[i].BandMaxY		=i*BandHeight+BandHeight;
		PData[i].BandCount		=BandCount;
		PData[i].PickupL		=PickupL;
		PData[i].PickupH		=PickupH;
		PData[i].ReEntCounter	=0;
		PData[i].func			=func;
		PData[i].AllocatedBuffLines	=100;
		PData[i].NLen			=0;
		PData[i].BuffLines		=new struct FlexLine[100];
	}
	MatrixBuffClear(TmpMap,0,XByte,YLen);
	MakePickBand(L,R,StartY ,CIndex ,PData);

	int	NLen=0;
	for(int i=0;i<BandCount;i++){
		NLen+=PData[i].NLen;
	}
	struct FlexLine	*FL=new struct FlexLine[NLen];
	int	n=0;
	for(int i=0;i<BandCount;i++){
		memcpy(&FL[n],PData[i].BuffLines,sizeof(struct FlexLine)*PData[i].NLen);
		delete	[]PData[i].BuffLines;
		n+=PData[i].NLen;
		
	}
	DeleteMatrixBuff(TmpMap,YLen);

	QSort(FL,n,sizeof(FL[0]),YSortFunc);
	SetFLine(FL,n);
	//Restruct();
}


#pragma	pack(push)
#pragma	pack(1)
struct XYDimTransform
{
	int	X,Y;
};
#pragma	pack(pop)

static	int	XYDimTransformFunc(const void *a ,const void *b)
{
	struct XYDimTransform	*pa=(struct XYDimTransform *)a;
	struct XYDimTransform	*pb=(struct XYDimTransform *)b;

	if(pa->Y<pb->Y)
		return -1;
	else
	if(pa->Y>pb->Y)
		return 1;
	if(pa->X<pb->X)
		return -1;
	else
	if(pa->X>pb->X)
		return 1;
	return 0;
}

FlexArea	FlexArea::Transform(TransformBase &Param)
{
	FlexArea	Ret;
	TransformAffin	*f=dynamic_cast<TransformAffin *>(&Param);
	if(f!=NULL){
		double d[6];
		if(::MakeTransformReverse(d,f->Param)==true){
			int	mx1=99999999;
			int	my1=99999999;
			int	mx2=-99999999;
			int	my2=-99999999;
			int	N=GetFLineLen();
			for(int i=0;i<N;i++){
				int x1=GetFLineLeftX (i);
				int x2=GetFLineRightX(i);
				int y =GetFLineAbsY  (i);
				for(int x=x1;x<x2;x++){
					double	X;
					double	Y;
					Param.Transform(x,y,X,Y);
					mx1=min((int)X,mx1);
					my1=min((int)Y,my1);
					mx2=max((int)X,mx2);
					my2=max((int)Y,my2);
				}
			}

			NPListPack<FlexLineList>	LList;
			int	NN=my2-my1+1;
			if(NN<8){
				for(int y=my1;y<=my2;y++){
					FlexLineList	*C=NULL;
					for(int x=mx1;x<=mx2;x++){
						int	Rx=x*d[0]+y*d[1]+d[2];
						int	Ry=x*d[3]+y*d[4]+d[5];
						if(IsInclude(Rx ,Ry)==true){
							if(C==NULL){
								C=new FlexLineList();
								C->y=y;
								C->x1=x;
								C->x2=x;
								LList.AppendList(C);
							}
							else{
								C->x2=x;
							}
						}
						else{
							C=NULL;
						}
					}
				}
			}
			else{
				#pragma omp parallel
				{
					#pragma omp for
					//for(int y=my1;y<=my2;y++){
					for(int i=0;i<NN;i++){
						int	y=my1+i;
						FlexLineList	*C=NULL;
						for(int x=mx1;x<=mx2;x++){
							int	Rx=x*d[0]+y*d[1]+d[2];
							int	Ry=x*d[3]+y*d[4]+d[5];
							if(IsInclude(Rx ,Ry)==true){
								if(C==NULL){
									C=new FlexLineList();
									C->y=y;
									C->x1=x;
									C->x2=x;
									#pragma omp critical
									{
										LList.AppendList(C);
									}
								}
								else{
									C->x2=x;
								}
							}
							else{
								C=NULL;
							}
						}
					}
				}
			}

			struct FlexLine	*FL=new struct FlexLine[LList.GetCount()];
			int	k=0;
			for(FlexLineList *q=LList.GetFirst();q!=NULL;q=q->GetNext(),k++){
				FL[k]._Set(q->x1, q->x2 ,q->y);
			}
			Ret.SetFLine(FL,k);
			Ret.Regulate();
		}
	}
	return Ret;
}

//========================================================================================

struct	PourFromImageStructBitImage
{
	BYTE	**TmpMap;
	BYTE	**SrcBitImage;
	int		DotPerLine;
	int		XByte;
	int		YLen;
	int		MaxBuffSize;
	int		StackLevel;
	int		LMinX,LMaxX;
	int		LMinY,LMaxY;
	int		ReEntCounter;
	void	(*func)(void);
};

static	int	PickPours(int Left,int Right,int Y ,struct FlexLine *BuffLines,struct	PourFromImageStructBitImage &PData)
{
	PData.StackLevel++;
	if(PData.StackLevel>MaxStackLevelInPour){
		return 0;
	}
	PData.ReEntCounter++;
	if((PData.ReEntCounter&0xFFF)==0 && PData.func!=NULL){
		PData.func();
	}

	BYTE	*b=PData.TmpMap[Y];
	int	x;
	int	L,R;
	int	Count=0;
	for(x=Left;x>0 && x>PData.LMinX;x--){
		if(PData.DotPerLine!=0 && x>=PData.DotPerLine){
			continue;
		}
		if(GetBmpBitOnY(PData.SrcBitImage[Y],x)==0
		|| GetBmpBitOnY(b,x)!=0){
			break;
		}
		Left=x;
	}
	for(x=Right;x<PData.LMaxX;x++){
		if(x<0){
			continue;
		}
		if(GetBmpBitOnY(PData.SrcBitImage[Y],x)==0
		|| GetBmpBitOnY(b,x)!=0){
			break;
		}
		Right=x;
	}

	for(x=Left;x<Right;x++){
		if(x<0){
			continue;
		}
		if(GetBmpBitOnY(PData.SrcBitImage[Y],x)!=0
		&& GetBmpBitOnY(b,x)==0){
			L=x;
			R=x;
			for(;x<Right;x++){
				if(GetBmpBitOnY(PData.SrcBitImage[Y],x)==0
				 || GetBmpBitOnY(b,x)!=0){
					break;
				}
			}
			R=x;
			if(PData.MaxBuffSize>0){
				BuffLines[Count]._SetLeftX(L);
				BuffLines[Count].SetNumb(R-L);
				BuffLines[Count]._SetAbsY(Y);
				for(int i=L;i<R;i++){
					SetBmpBitOnY1(b,i);
				}
				Count++;
				PData.MaxBuffSize--;

				if(PData.LMinX<=(L-1) && (L-1)<PData.LMaxX){
					L--;
				}
				if(L<0){
					L=0;
				}
				if(PData.LMinX<=(R+1) && (R+1)<PData.LMaxX){
					R++;
				}
				if(R>=PData.DotPerLine){
					R=PData.DotPerLine;
				}
				if(PData.MaxBuffSize>0){
					if(PData.LMinY<=(Y-1) && (Y-1)<PData.LMaxY){
						Count+=PickPours(L,R,Y-1 ,&BuffLines[Count],PData);
						PData.StackLevel--;
					}
				}
				if(PData.MaxBuffSize>0){
					if(PData.LMinY<=(Y+1) && (Y+1)<PData.LMaxY){
						Count+=PickPours(L,R,Y+1 ,&BuffLines[Count],PData);
						PData.StackLevel--;
					}
				}
			}
		}
	}
	return Count;
}

void	FlexArea::PourFromImage(BYTE **SrcBitImage ,int XByte ,int YLen
								,int StartX, int StartY
								,void (*func)(void)
								,int MaxBuffCount
								,int MaxSize)
{
	struct   FlexLine	*BuffLines=new struct FlexLine[MaxBuffCount];
	int	XLen=XByte*8;

	int	L=0,R=0;
	BYTE	*s=SrcBitImage[StartY];
	for(int x=StartX;x>=0;x--){
		if(GetBmpBitOnY(s,x)==0){
			L=x+1;
			break;
		}
	}
	for(int x=StartX;x<XLen;x++){
		if(GetBmpBitOnY(s,x)!=0){
			R=x-1;
			break;
		}
	}

	struct	PourFromImageStructBitImage	PData;

	PData.DotPerLine	=XLen;
	PData.XByte			=XByte;
	PData.YLen			=YLen;
	PData.TmpMap		=MakeMatrixBuff(PData.XByte,PData.YLen);
	PData.MaxBuffSize	=MaxBuffCount;
	PData.StackLevel	=0;
	PData.SrcBitImage	=SrcBitImage;
	PData.LMinX			=0;
	PData.LMaxX			=XLen;
	PData.LMinY			=0;
	PData.LMaxY			=YLen;
	PData.ReEntCounter	=0;
	PData.func			=func;
	MatrixBuffClear(PData.TmpMap,0,PData.XByte,PData.YLen);

	int	Count=PickPours(L,R,StartY,BuffLines,PData);
	DeleteMatrixBuff(PData.TmpMap,PData.YLen);

	struct FlexLine	*FL=new struct FlexLine[Count];
	memcpy(FL,BuffLines,sizeof(struct FlexLine)*Count);
	delete	[]BuffLines;

	QSort(FL,Count,sizeof(FL[0]),YSortFunc);
	SetFLine(FL,Count);
	//Restruct();
}
