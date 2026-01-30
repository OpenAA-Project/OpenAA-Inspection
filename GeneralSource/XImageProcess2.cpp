/*
 * Copyright (C) 2026
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

#include "XTypeDef.h"
#include <cmath>
#include "XPointer.h"
#include "XImageProcess.h"
#include "XImageProcess2.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include "swap.h"
#include "omp.h"
#include "XFlexArea.h"

bool	PickupFlexArea(		 BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount,bool Multithread)
{
	return PickupFlexArea((const BYTE **)Bmp ,XByte ,XLen,YLen ,FPack ,MaxAreaCount,Multithread);
}

bool	PickupFlexArea(		 BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack 
					,int AreaX1 ,int AreaY1 ,int AreaX2 ,int AreaY2
					,int MaxAreaCount,bool Multithread)
{
	return PickupFlexArea((const BYTE **)Bmp ,XByte ,XLen,YLen ,FPack 
					,AreaX1 ,AreaY1 ,AreaX2 ,AreaY2
					,MaxAreaCount,Multithread);
}

struct	LineNotchPosition
{
	int	S1,H1;
	int	S2,H2;
	int	Count;
};


bool    MakeHough(BYTE **BmpMap,BYTE **DestMap
				  ,int FreqDots
				  ,int XLen,int YLen
				  ,int HoughResolution)
//�n�t�ϊ��ŁA�������̃h�b�g�������o
{
	int	HNumb=XLen*2;
	int	WNumb=HoughResolution;
	DWORD	**TmpH=new DWORD*[HNumb];
	for(int y=0;y<HNumb;y++){
		TmpH[y]=new DWORD[WNumb];
		memset(TmpH[y],0,sizeof(DWORD)*WNumb);
	}
	double	*CosTable=new double[WNumb];
	double	*SinTable=new double[WNumb];
	for(int s=0;s<WNumb;s++){
		double	sita=M_PI/(double)WNumb;
		CosTable[s]=cos(sita);
		SinTable[s]=sin(sita);
	}

    for(int y=0;y<YLen;y++){
		BYTE	*d=BmpMap[y];
        for(int x=0;x<XLen;x++){
			if((d[x>>3] & (0x80>>(x&7)))!=0){
				for(int s=0;s<WNumb;s++){
					double	L=x*CosTable[s]+y*SinTable[s];
					if(0<=L && L<HNumb){
						(*(TmpH[(int)L]+s))++;
					}
				}
            }
        }
	}
	const int	LineNotchPositionDimMax=1000;
	struct	LineNotchPosition	LineNotchPositionDimXY[LineNotchPositionDimMax];
	int	CounterXY=0;
	for(int s=WNumb/2-10;s<WNumb/2+10;s++){
		for(int h=0;h<HNumb;h++){
			if(*(TmpH[h]+s)>FreqDots){
				int	i;
				for(i=0;i<CounterXY;i++){
					if(LineNotchPositionDimXY[i].S1<=s && LineNotchPositionDimXY[i].H1<=h && s<=LineNotchPositionDimXY[i].S2 && h<=LineNotchPositionDimXY[i].H2){
						if(LineNotchPositionDimXY[i].S1==s)
							LineNotchPositionDimXY[i].S1=s-1;
						if(LineNotchPositionDimXY[i].S2==s)
							LineNotchPositionDimXY[i].S2=s+1;
						if(LineNotchPositionDimXY[i].H1==h)
							LineNotchPositionDimXY[i].H1=h-1;
						if(LineNotchPositionDimXY[i].H2==h)
							LineNotchPositionDimXY[i].H2=h+1;
						LineNotchPositionDimXY[i].Count+=*(TmpH[h]+s);
						break;
					}
				}
				if(i>=CounterXY && CounterXY<LineNotchPositionDimMax){
					LineNotchPositionDimXY[CounterXY].S1=s-1;
					LineNotchPositionDimXY[CounterXY].H1=h-1;
					LineNotchPositionDimXY[CounterXY].S2=s+1;
					LineNotchPositionDimXY[CounterXY].H2=h+1;
					LineNotchPositionDimXY[CounterXY].Count=*(TmpH[h]+s);
					CounterXY++;
				}
			}
		}
	}
	for(int y=0;y<HNumb;y++){
		memset(TmpH[y],0,sizeof(DWORD)*WNumb);
	}
    for(int y=0;y<YLen;y++){
		BYTE	*d=BmpMap[y];
        for(int x=0;x<XLen;x++){
			if((d[x>>3] & (0x80>>(x&7)))!=0){
				for(int s=0;s<WNumb;s++){
					double	L=y*CosTable[s]+x*SinTable[s];
					if(0<=L && L<HNumb){
						(*(TmpH[(int)L]+s))++;
					}
				}
            }
        }
	}
	struct	LineNotchPosition	LineNotchPositionDimYX[LineNotchPositionDimMax];
	int	CounterYX=0;
	for(int s=WNumb/2-10;s<WNumb/2+10;s++){
		for(int h=0;h<HNumb;h++){
			if(*(TmpH[h]+s)>FreqDots){
				int	i;
				for(i=0;i<CounterYX;i++){
					if(LineNotchPositionDimYX[i].S1<=s && LineNotchPositionDimYX[i].H1<=h && s<=LineNotchPositionDimYX[i].S2 && h<=LineNotchPositionDimYX[i].H2){
						if(LineNotchPositionDimYX[i].S1==s)
							LineNotchPositionDimYX[i].S1=s-1;
						if(LineNotchPositionDimYX[i].S2==s)
							LineNotchPositionDimYX[i].S2=s+1;
						if(LineNotchPositionDimYX[i].H1==h)
							LineNotchPositionDimYX[i].H1=h-1;
						if(LineNotchPositionDimYX[i].H2==h)
							LineNotchPositionDimYX[i].H2=h+1;
						LineNotchPositionDimYX[i].Count+=*(TmpH[h]+s);
						break;
					}
				}
				if(i>=CounterYX && CounterYX<LineNotchPositionDimMax){
					LineNotchPositionDimYX[CounterYX].S1=s-1;
					LineNotchPositionDimYX[CounterYX].H1=h-1;
					LineNotchPositionDimYX[CounterYX].S2=s+1;
					LineNotchPositionDimYX[CounterYX].H2=h+1;
					LineNotchPositionDimYX[CounterYX].Count=*(TmpH[h]+s);
					CounterYX++;
				}
			}
		}
	}

    for(int y=0;y<YLen;y++){
		BYTE	*d=DestMap[y];
		BYTE	*s=BmpMap[y];
        for(int x=0;x<XLen;x++){
			if((s[x>>3] & (0x80>>(x&7)))!=0){
				int	i;
				for(i=0;i<CounterXY;i++){
					int	se=(LineNotchPositionDimXY[i].S1+LineNotchPositionDimXY[i].S2)/2;
					double	L=x*CosTable[se]+y*SinTable[se];
					if(LineNotchPositionDimXY[i].H1<=L && L<=LineNotchPositionDimXY[i].H2)
						break;
				}
				if(i>=CounterXY){
					for(i=0;i<CounterYX;i++){
						int	se=(LineNotchPositionDimYX[i].S1+LineNotchPositionDimYX[i].S2)/2;
						double	L=y*CosTable[se]+x*SinTable[se];
						if(LineNotchPositionDimYX[i].H1<=L && L<=LineNotchPositionDimYX[i].H2)
							break;
					}
					if(i>=CounterYX){
						//d[x>>3] |= 0x80>>(x&7);
					}
					else{
						d[x>>3] |= 0x80>>(x&7);
					}
				}
				else{
					d[x>>3] |= 0x80>>(x&7);
				}
			}
		}
	}

	delete	[]CosTable;
	delete	[]SinTable;
	for(int y=0;y<HNumb;y++){
		delete	[]TmpH[y];
	}
	delete	[]TmpH;

	return true;
}

void    NarrowizeLine(BYTE **Bmp ,BYTE **Tmp ,int XLen , int YLen)
//	�א���
{
	int	XByte	=(XLen+7)/8;
	MatrixBuffCopy(Tmp					,XByte,YLen
                 , (const BYTE **)Bmp	,XByte,YLen);

	bool	ChangedFlag;
	do{
		ChangedFlag=false;
		int N=YLen-2;
		for(int i=0;i<N;i++){
			int	y=i+1;
			for(int x=1;x<XLen-1;x++){
	            BYTE	D=GetBmpBit(Bmp,x,y);
				if(D!=0){
		            int	D0=GetBmpBit(Bmp,x-1,y-1);
		            int	D1=GetBmpBit(Bmp,x  ,y-1);
			        int	D2=GetBmpBit(Bmp,x+1,y-1);
				    int	D3=GetBmpBit(Bmp,x-1,y  );
					int	D4=GetBmpBit(Bmp,x+1,y  );
		            int	D5=GetBmpBit(Bmp,x-1,y+1);
		            int	D6=GetBmpBit(Bmp,x  ,y+1);
		            int	D7=GetBmpBit(Bmp,x+1,y+1);
					if((D0==0 && D1==0 && D2==0
					 && D5!=0 && D6!=0 && D7!=0)
					|| (D0==0 && D1==0
					 && D3==0          && D4!=0
					 &&          D6!=0)
					|| (D0==0          && D2!=0
					 && D3==0          && D4!=0
					 && D5==0          && D7!=0)){
						ChangedFlag=true;
						SetBmpBit0(Tmp,x,y);
					}
				}
			}
		}
		MatrixBuffCopy(Bmp					,XByte,YLen
		             , (const BYTE **)Tmp	,XByte,YLen);

		for(int i=0;i<N;i++){
			int	y=YLen-2-i;
			for(int x=XLen-2;x>=1;x--){
	            BYTE	D=GetBmpBit(Bmp,x,y);
				if(D!=0){
		            int	D0=GetBmpBit(Bmp,x-1,y-1);
		            int	D1=GetBmpBit(Bmp,x  ,y-1);
			        int	D2=GetBmpBit(Bmp,x+1,y-1);
				    int	D3=GetBmpBit(Bmp,x-1,y  );
					int	D4=GetBmpBit(Bmp,x+1,y  );
		            int	D5=GetBmpBit(Bmp,x-1,y+1);
		            int	D6=GetBmpBit(Bmp,x  ,y+1);
		            int	D7=GetBmpBit(Bmp,x+1,y+1);
					if((D0!=0 && D1!=0 && D2!=0
					 && D5==0 && D6==0 && D7==0)
					|| (         D1!=0
					 && D3!=0          && D4==0
					 &&          D6==0 && D7==0)
					|| (D0!=0          && D2==0
					 && D3!=0          && D4==0
					 && D5!=0          && D7==0)){
						ChangedFlag=true;
						SetBmpBit0(Tmp,x,y);
					}
				}
			}
		}
		MatrixBuffCopy(Bmp					,XByte,YLen
		             , (const BYTE **)Tmp	,XByte,YLen);

		for(int i=0;i<N;i++){
			int	y=i+1;
			for(int x=XLen-2;x>=1;x--){
	            BYTE	D=GetBmpBit(Bmp,x,y);
				if(D!=0){
		            int	D0=GetBmpBit(Bmp,x-1,y-1);
		            int	D1=GetBmpBit(Bmp,x  ,y-1);
			        int	D2=GetBmpBit(Bmp,x+1,y-1);
				    int	D3=GetBmpBit(Bmp,x-1,y  );
					int	D4=GetBmpBit(Bmp,x+1,y  );
		            int	D5=GetBmpBit(Bmp,x-1,y+1);
		            int	D6=GetBmpBit(Bmp,x  ,y+1);
		            int	D7=GetBmpBit(Bmp,x+1,y+1);
					if((D0!=0          && D2==0
					 && D3!=0          && D4==0
					 && D5!=0          && D7==0)
					|| (         D1==0 && D2==0
					 && D3!=0          && D4==0
					 &&		     D6!=0         )
					|| (D0==0 && D1==0 && D2==0
					&& D5!=0 && D6!=0 && D7!=0)){
						ChangedFlag=true;
						SetBmpBit0(Tmp,x,y);
					}
				}
			}
		}
		MatrixBuffCopy(Bmp					,XByte,YLen
		             , (const BYTE **)Tmp	,XByte,YLen);

		for(int i=0;i<N;i++){
			int	y=YLen-2-i;
			for(int x=1;x<XLen-1;x++){
	            BYTE	D=GetBmpBit(Bmp,x,y);
				if(D!=0){
		            int	D0=GetBmpBit(Bmp,x-1,y-1);
		            int	D1=GetBmpBit(Bmp,x  ,y-1);
			        int	D2=GetBmpBit(Bmp,x+1,y-1);
				    int	D3=GetBmpBit(Bmp,x-1,y  );
					int	D4=GetBmpBit(Bmp,x+1,y  );
		            int	D5=GetBmpBit(Bmp,x-1,y+1);
		            int	D6=GetBmpBit(Bmp,x  ,y+1);
		            int	D7=GetBmpBit(Bmp,x+1,y+1);
					if((D0==0          && D2!=0
					 && D3==0          && D4!=0
					 && D5==0          && D7!=0)
					|| (         D1!=0
					 && D3==0          && D4!=0
					 && D5==0 && D6==0         )
					|| (D0!=0 && D1!=0 && D2!=0
					 && D5==0 && D6==0 && D7==0)){
						ChangedFlag=true;
						SetBmpBit0(Tmp,x,y);
					}
				}
			}
		}
		MatrixBuffCopy(Bmp					,XByte,YLen
		             , (const BYTE **)Tmp	,XByte,YLen);
	}while(ChangedFlag==true);

}

#pragma	pack(push,1)
struct	PickupLinesStruct
{
	BYTE	**BmpMap;
	int XLen;
	int YLen;
	int	Index;
};
#pragma	pack(pop)

static	void	PickupLinesInner(struct	PickupLinesStruct &Data,int x,int y 
								 ,TreeLine *CurrentTree)
{
	TreePointList *Current=new TreePointList();
	SetBmpBit0(Data.BmpMap,x,y);
	Current->SetXY(x,y);
	CurrentTree->AppendList(Current);

	int		Index=Data.Index;
	Data.Index++;
	for(int i=0;i<8;i++){
		switch((Index+i)%8){
			case 0:
				if(0<y){
					if(0<x && (GetBmpBit(Data.BmpMap,x-1,y-1)!=0)){
						if(Current->GetNext()==NULL){
							PickupLinesInner(Data,x-1,y-1 ,CurrentTree);
						}
						else{
							PickupLinesInner(Data,x-1,y-1 ,&Current->GetOtherNode());
						}
					}
				}
				break;
			case 1:
				if(0<y){
					if(GetBmpBit(Data.BmpMap,x,y-1)!=0){
						if(Current->GetNext()==NULL){
							PickupLinesInner(Data,x,y-1 ,CurrentTree);
						}
						else{
							PickupLinesInner(Data,x,y-1 ,&Current->GetOtherNode());
						}
					}
				}
				break;
			case 2:
				if(0<y){
					if((x+1)<Data.XLen && (GetBmpBit(Data.BmpMap,x+1,y-1)!=0)){
						if(Current->GetNext()==NULL){
							PickupLinesInner(Data,x+1,y-1 ,CurrentTree);
						}
						else{
							PickupLinesInner(Data,x+1,y-1 ,&Current->GetOtherNode());
						}
					}
				}
				break;
			case 3:
				if(0<x && (GetBmpBit(Data.BmpMap,x-1,y)!=0)){
					if(Current->GetNext()==NULL){
						PickupLinesInner(Data,x-1,y ,CurrentTree);
					}
					else{
						PickupLinesInner(Data,x-1,y ,&Current->GetOtherNode());
					}
				}
				break;
			case 4:
				if((x+1)<Data.XLen && (GetBmpBit(Data.BmpMap,x+1,y)!=0)){
					if(Current->GetNext()==NULL){
						PickupLinesInner(Data,x+1,y ,CurrentTree);
					}
					else{
						PickupLinesInner(Data,x+1,y ,&Current->GetOtherNode());
					}
				}
				break;
			case 5:
				if((y+1)<Data.YLen){
					if(0<x && (GetBmpBit(Data.BmpMap,x-1,y+1)!=0)){
						if(Current->GetNext()==NULL){
							PickupLinesInner(Data,x-1,y+1 ,CurrentTree);
						}
						else{
							PickupLinesInner(Data,x-1,y+1 ,&Current->GetOtherNode());
						}
					}
				}
				break;
			case 6:
				if((y+1)<Data.YLen){
					if(GetBmpBit(Data.BmpMap,x,y+1)!=0){
						if(Current->GetNext()==NULL){
							PickupLinesInner(Data,x,y+1 ,CurrentTree);
						}
						else{
							PickupLinesInner(Data,x,y+1 ,&Current->GetOtherNode());
						}
					}
				}
				break;
			case 7:
				if((y+1)<Data.YLen){
					if((x+1)<Data.XLen && (GetBmpBit(Data.BmpMap,x+1,y+1)!=0)){
						if(Current->GetNext()==NULL){
							PickupLinesInner(Data,x+1,y+1 ,CurrentTree);
						}
						else{
							PickupLinesInner(Data,x+1,y+1 ,&Current->GetOtherNode());
						}
					}
				}
				break;
		}
	}
}

void	PickupLines(BYTE **BmpMap, int XLen , int YLen
					,TreesContainer &XYCluster)
//�א������ꂽ�r�b�g�摜�������������o��
{
	struct	PickupLinesStruct	Data;
	Data.BmpMap=BmpMap;
	Data.XLen=XLen;
	Data.YLen=YLen;
	Data.Index=0;

	for(int y=0;y<YLen;y++){
		for(int x=0;x<XLen;x++){
			if(GetBmpBit(BmpMap,x,y)!=0){
				TreeLine *CurrentTree=new TreeLine();
				PickupLinesInner(Data,x,y ,CurrentTree);
//				CurrentTree->DeleteNoise(2);
				XYCluster.AppendList(CurrentTree);
			}
		}
	}
}


#pragma	pack(push)
#pragma	pack(1)

struct	PickupFlexAreaStruct
{
	int32	AbsY;
	int32	LeftX;
	int32	Numb;
	int32	Code;
};

struct	PickupFlexAreaStructPointer
{
	int32	DimPoint;
	int32	Count;
	struct	PickupFlexAreaStruct	*DimPointer;
};

#pragma	pack(pop)

inline	bool	IsNearby(const struct PickupFlexAreaStruct &s1 ,const struct PickupFlexAreaStruct &s2)
{
	if((s1.LeftX+s1.Numb)<s2.LeftX){
		return false;
	}
	if((s2.LeftX+s2.Numb)<s1.LeftX){
		return false;
	}
	return true;
}

#pragma	pack(push)
#pragma	pack(1)
struct	PickupFlexAreaRDim
{
	struct PickupFlexAreaStruct			*LDim;
	struct	PickupFlexAreaStructPointer	*YPointer;
	int		YLen;
	int		AreaCode;
	int		FPointerCount;
	struct PickupFlexAreaStruct			**FPointer;
	int		ReEntrantCount;
};
#pragma	pack(pop)

#pragma	pack(push)
#pragma	pack(1)
struct	PickupFlexAreaRDimAreaY
{
	struct PickupFlexAreaStruct			*LDim;
	struct	PickupFlexAreaStructPointer	*YPointer;
	int		YLen;
	int		AreaY1,AreaY2;
	int		AreaCode;
	int		FPointerCount;
	struct PickupFlexAreaStruct			**FPointer;
	int		ReEntrantCount;
	bool	LimitY1;
	bool	LimitY2;
};
#pragma	pack(pop)

#pragma	pack(push)
#pragma	pack(1)
struct	PickupFlexAreaRDimPartial
{
	struct PickupFlexAreaStruct			*LDim;
	struct	PickupFlexAreaStructPointer	*YPointer;
	int		YLen;
	int		AreaX1,AreaY1,AreaX2,AreaY2;
	int		AreaCode;
	int		FPointerCount;
	struct PickupFlexAreaStruct			**FPointer;
	int		ReEntrantCount;
};
#pragma	pack(pop)

static	bool	RecursivePickupFlexArea(struct	PickupFlexAreaRDim &PData ,struct PickupFlexAreaStruct *SPoint)
{
	int	L=SPoint->AbsY;
	int	N;
	int j;
	struct	PickupFlexAreaStruct	*s;
	bool	Ret=false;

	PData.ReEntrantCount++;

	if(SPoint->Code==-1){
		PData.FPointer[PData.FPointerCount]=SPoint;
		PData.FPointerCount++;
		SPoint->Code=PData.AreaCode;
	}

	if(L>0){
		N=PData.YPointer[L-1].Count;
		s=PData.YPointer[L-1].DimPointer;
		for(j=0;j<N;j++,s++){
			if(s->Code==-1){
				if(IsNearby(*SPoint,*s)==true){
					RecursivePickupFlexArea(PData,s);
					Ret=true;
				}
			}
		}
	}
	if((L+1)<PData.YLen){
		N=PData.YPointer[L+1].Count;
		s=PData.YPointer[L+1].DimPointer;
		for(j=0;j<N;j++,s++){
			if(s->Code==-1){
				if(IsNearby(*SPoint,*s)==true){
					RecursivePickupFlexArea(PData,s);
					Ret=true;
				}
			}
		}
	}
	PData.ReEntrantCount--;
	return Ret;
}

static	bool	RecursivePickupFlexArea(struct	PickupFlexAreaRDimAreaY &PData ,struct PickupFlexAreaStruct *SPoint)
{
	int	L=SPoint->AbsY-PData.AreaY1;
	int	N;
	int j;
	struct	PickupFlexAreaStruct	*s;
	bool	Ret=false;

	PData.ReEntrantCount++;
	if(SPoint->Code==-1){
		PData.FPointer[PData.FPointerCount]=SPoint;
		PData.FPointerCount++;
		SPoint->Code=PData.AreaCode;
	}

	if(L>0){
		N=PData.YPointer[L-1].Count;
		s=PData.YPointer[L-1].DimPointer;
		for(j=0;j<N;j++,s++){
			if(s->Code==-1){
				if(IsNearby(*SPoint,*s)==true){
					RecursivePickupFlexArea(PData,s);
					Ret=true;
				}
			}
		}
	}
	if((L+1)<PData.AreaY2-PData.AreaY1){
		N=PData.YPointer[L+1].Count;
		s=PData.YPointer[L+1].DimPointer;
		for(j=0;j<N;j++,s++){
			if(s->Code==-1){
				if(IsNearby(*SPoint,*s)==true){
					RecursivePickupFlexArea(PData,s);
					Ret=true;
				}
			}
		}
	}
	PData.ReEntrantCount--;
	return Ret;
}

static	bool	RecursivePickupFlexArea(struct	PickupFlexAreaRDimPartial &PData ,struct PickupFlexAreaStruct *SPoint)
{
	int	L=SPoint->AbsY-PData.AreaY1;
	int	N;
	int j;
	struct	PickupFlexAreaStruct	*s;
	bool	Ret=false;

	PData.ReEntrantCount++;
	if(SPoint->Code==-1){
		PData.FPointer[PData.FPointerCount]=SPoint;
		PData.FPointerCount++;
		SPoint->Code=PData.AreaCode;
	}

	if(L>0){
		N=PData.YPointer[L-1].Count;
		s=PData.YPointer[L-1].DimPointer;
		for(j=0;j<N;j++,s++){
			if(s->Code==-1){
				if(IsNearby(*SPoint,*s)==true){
					RecursivePickupFlexArea(PData,s);
					Ret=true;
				}
			}
		}
	}
	if((L+1)<PData.AreaY2-PData.AreaY1){
		N=PData.YPointer[L+1].Count;
		s=PData.YPointer[L+1].DimPointer;
		for(j=0;j<N;j++,s++){
			if(s->Code==-1){
				if(IsNearby(*SPoint,*s)==true){
					RecursivePickupFlexArea(PData,s);
					Ret=true;
				}
			}
		}
	}
	PData.ReEntrantCount--;
	return Ret;
}

bool	PickupFlexAreaPartial(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount,bool Multithread)
{
	const	int	__MaxDimCount=10000;

	int		MaxDimCount=__MaxDimCount;
	struct	PickupFlexAreaStruct	LDim[__MaxDimCount];
	int								LDimCount;
	struct	PickupFlexAreaStructPointer	YPointerDim[__MaxDimCount];

	struct	PickupFlexAreaStruct		*LDimPointer=LDim;
	struct	PickupFlexAreaStructPointer	*YPointer;
	
	struct	PickupFlexAreaStruct		*FPointerDim[__MaxDimCount];
	struct	PickupFlexAreaStruct		**FPointer=FPointerDim;
	PureFlexAreaList					*PureFlexAreaListDim[__MaxDimCount];
	PureFlexAreaList					**PureFlexAreaListPointer=PureFlexAreaListDim;
	int									MaxPureFlexAreaListPointerCount=__MaxDimCount;
	int									PureFlexAreaListPointerCount=0;
	
	if(YLen>=MaxDimCount){
		YPointer=new struct PickupFlexAreaStructPointer[YLen];
	}
	else{
		YPointer	=YPointerDim;
	}
	XLen=min(XLen,XByte*8);

	LDimCount=0;
	for(int y=0;y<YLen;y++){
		const BYTE	*b=Bmp[y];
		YPointer[y].DimPoint=LDimCount;
		YPointer[y].Count=0;
		int		Offset=0;
		for(int x=0;x<XLen;x+=8,Offset++){
			if(b[Offset]==0){
				continue;
			}
			BYTE	Mask=0x80;
			for(int r=0;r<8;r++,Mask>>=1){
				if((b[Offset] & Mask)!=0){
					LDimPointer[LDimCount].AbsY		=y;
					LDimPointer[LDimCount].LeftX	=x+r;
					LDimPointer[LDimCount].Numb		=1;
					LDimPointer[LDimCount].Code		=-1;
					int x2=x;
					Mask>>=1;
					r++;
					for(;;){
						for(;r<8;r++,Mask>>=1){
							if((b[Offset] & Mask)==0){
								goto	FoundBitEnd;
							}
						}
						Mask=0x80;
						r=0;
						do{
							Offset++;
							x2+=8;
							if(x2>=XLen){
								goto	FoundBitEnd;
							}
						}while(b[Offset]==0xFF);
					}
FoundBitEnd:
					LDimPointer[LDimCount].Numb	=x2+r-LDimPointer[LDimCount].LeftX;
					x=x2;

					//_heapchk();

					LDimCount++;
					YPointer[y].Count++;
					if(LDimCount>=MaxDimCount){
						MaxDimCount=MaxDimCount*2;
						struct PickupFlexAreaStruct	*LDimPointer2=new struct PickupFlexAreaStruct[MaxDimCount];
						int	h;
						for(h=0;h<LDimCount;h++){
							LDimPointer2[h]=LDimPointer[h];
						}
						//_heapchk();

						//memcpy(LDimPointer2,LDimPointer,sizeof(LDimPointer[0])*LDimCount);
						if(LDimPointer!=LDim){
							delete	[]LDimPointer;
						}
						LDimPointer=LDimPointer2;
					}
					if(x>=XLen){
						break;
					}
				}
			}
		}
	}

	for(int y=0;y<YLen;y++){
		YPointer[y].DimPointer=&LDimPointer[YPointer[y].DimPoint];
	}

	if(LDimCount>=__MaxDimCount){
		FPointer	=new struct	PickupFlexAreaStruct*[LDimCount];
	}

	int	AreaCode=0;
	for(int i=0;i<LDimCount;i++){
		if(LDimPointer[i].Code==-1){
			struct	PickupFlexAreaRDim	PData;
			PData.LDim		=LDimPointer;
			PData.YLen		=YLen;
			PData.YPointer	=YPointer;
			PData.AreaCode	=AreaCode;
			PData.FPointer	=FPointer;
			PData.FPointerCount=0;
			PData.ReEntrantCount=0;
			RecursivePickupFlexArea(PData,&LDimPointer[i]);

			bool	RetMode;
			do{
				RetMode=false;
				for(int j=0;j<PData.FPointerCount;j++){
					if(RecursivePickupFlexArea(PData,PData.FPointer[j])==true){
						RetMode=true;
					}
				}
			}while(RetMode==true);

			if(PData.FPointerCount>0){
				struct FlexLine	*L=new struct FlexLine[PData.FPointerCount];
				for(int j=0;j<PData.FPointerCount;j++){
					L[j]._LeftX	=FPointer[j]->LeftX;
					L[j]._Numb	=FPointer[j]->Numb;
					L[j]._AbsY	=FPointer[j]->AbsY;
				}
				//_heapchk();
				PureFlexAreaList	*k=new PureFlexAreaList();
				k->SetFLineOnly(L,PData.FPointerCount);
			
				PureFlexAreaListPointer[PureFlexAreaListPointerCount]=k;
				PureFlexAreaListPointerCount++;
				if(PureFlexAreaListPointerCount>=MaxPureFlexAreaListPointerCount){
					MaxPureFlexAreaListPointerCount*=2;
					PureFlexAreaList	**PureFlexAreaListPointer2=new PureFlexAreaList*[MaxPureFlexAreaListPointerCount];
					int	h;
					for(h=0;h<PureFlexAreaListPointerCount;h++){
						PureFlexAreaListPointer2[h]=PureFlexAreaListPointer[h];
					}
					for(;h<MaxPureFlexAreaListPointerCount;h++){
						PureFlexAreaListPointer2[h]=NULL;
					}
					//memcpy(PureFlexAreaListPointer2,PureFlexAreaListPointer,sizeof(PureFlexAreaListPointer[0])*PureFlexAreaListPointerCount);
					if(PureFlexAreaListPointer!=PureFlexAreaListDim){
						delete	[]PureFlexAreaListPointer;
					}
					PureFlexAreaListPointer=PureFlexAreaListPointer2;
				}
			}
			AreaCode++;
			if(MaxAreaCount>=0 && AreaCode>=MaxAreaCount){
				break;
			}
		}
	}

	//if(Multithread==true && LDimCount>5000 && AreaCode>32){
	if(Multithread==true && LDimCount>500 && AreaCode>32){
		#pragma omp parallel
		{
			#pragma omp for schedule(dynamic)
			for(int i=0;i<PureFlexAreaListPointerCount;i++){
				PureFlexAreaListPointer[i]->Regulate();
			}
		}
	}
	else{
		for(int i=0;i<PureFlexAreaListPointerCount;i++){
			PureFlexAreaListPointer[i]->Regulate();
		}
	}

	for(int i=0;i<PureFlexAreaListPointerCount;i++){
		FPack.AppendList(PureFlexAreaListPointer[i]);
	}
	if(LDimPointer!=LDim){
		delete	[]LDimPointer;
	}
	if(YPointer!=YPointerDim){
		delete	[]YPointer;
	}
	if(FPointer!=FPointerDim){
		delete	[]FPointer;
	}
	if(PureFlexAreaListPointer!=PureFlexAreaListDim){
		delete	[]PureFlexAreaListPointer;
	}
	return true;
}

bool	PickupFlexAreaPartial(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack 
							,int AreaX1 ,int AreaY1 ,int AreaX2 ,int AreaY2
							,int MaxAreaCount,bool Multithread)
{
	const	int	__MaxDimCount=10000;

	int		MaxDimCount=__MaxDimCount;
	struct	PickupFlexAreaStruct	LDim[__MaxDimCount];
	int								LDimCount;
	struct	PickupFlexAreaStructPointer	YPointerDim[__MaxDimCount];

	struct	PickupFlexAreaStruct		*LDimPointer=LDim;
	struct	PickupFlexAreaStructPointer	*YPointer;
	
	struct	PickupFlexAreaStruct		*FPointerDim[__MaxDimCount];
	struct	PickupFlexAreaStruct		**FPointer=FPointerDim;
	PureFlexAreaList					*PureFlexAreaListDim[__MaxDimCount];
	PureFlexAreaList					**PureFlexAreaListPointer=PureFlexAreaListDim;
	int									MaxPureFlexAreaListPointerCount=__MaxDimCount;
	int									PureFlexAreaListPointerCount=0;
	
	if(AreaY2-AreaY1>=MaxDimCount){
		YPointer=new struct PickupFlexAreaStructPointer[YLen];
	}
	else{
		YPointer	=YPointerDim;
	}
	XLen=min(XLen,XByte*8);

	LDimCount=0;

	int	Lx1=AreaX1&0xFFF8;
	int	Lx2=min((AreaX2+7)&0xFFF8,XLen);
	int	Ly1=max(AreaY1,0);
	int	Ly2=min(AreaY2,YLen);

	for(int y=Ly1;y<Ly2;y++){

		const BYTE	*b=Bmp[y];
		YPointer[y-Ly1].DimPoint=LDimCount;
		YPointer[y-Ly1].Count=0;
		int		Offset=Lx1>>3;
		for(int x=Lx1;x<Lx2;x+=8,Offset++){
			if(x<AreaX1)
				continue;
			if(AreaX2<=x)
				break;

			if(b[Offset]==0){
				continue;
			}
			BYTE	Mask=0x80;
			for(int r=0;r<8;r++,Mask>>=1){
				if((b[Offset] & Mask)!=0){
					LDimPointer[LDimCount].AbsY		=y;
					LDimPointer[LDimCount].LeftX	=x+r;
					LDimPointer[LDimCount].Numb		=1;
					LDimPointer[LDimCount].Code		=-1;
					int x2=x;
					Mask>>=1;
					r++;
					for(;;){
						for(;r<8;r++,Mask>>=1){
							if((b[Offset] & Mask)==0){
								goto	FoundBitEnd;
							}
						}
						Mask=0x80;
						r=0;
						do{
							Offset++;
							x2+=8;
							if(x2>=Lx2){
								goto	FoundBitEnd;
							}
						}while(b[Offset]==0xFF);
					}
FoundBitEnd:
					LDimPointer[LDimCount].Numb	=x2+r-LDimPointer[LDimCount].LeftX;
					x=x2;

					//_heapchk();

					LDimCount++;
					YPointer[y-Ly1].Count++;
					if(LDimCount>=MaxDimCount){
						MaxDimCount=MaxDimCount*2;
						struct PickupFlexAreaStruct	*LDimPointer2=new struct PickupFlexAreaStruct[MaxDimCount];
						int	h;
						for(h=0;h<LDimCount;h++){
							LDimPointer2[h]=LDimPointer[h];
						}
						//_heapchk();

						//memcpy(LDimPointer2,LDimPointer,sizeof(LDimPointer[0])*LDimCount);
						if(LDimPointer!=LDim){
							delete	[]LDimPointer;
						}
						LDimPointer=LDimPointer2;
					}
					if(x>=Lx2){
						break;
					}
				}
			}
		}
	}

	int	N=0;
	for(int y=Ly1;y<Ly2;y++){
		YPointer[N].DimPointer=&LDimPointer[YPointer[N].DimPoint];
		N++;
	}

	if(LDimCount>=__MaxDimCount){
		FPointer	=new struct	PickupFlexAreaStruct*[LDimCount];
	}

	int	AreaCode=0;
	for(int i=0;i<LDimCount;i++){
		if(LDimPointer[i].Code==-1){
			struct	PickupFlexAreaRDimPartial	PData;
			PData.LDim		=LDimPointer;
			PData.YLen		=YLen;
			PData.AreaX1	=Lx1;
			PData.AreaY1	=Ly1;
			PData.AreaX2	=Lx2;
			PData.AreaY2	=Ly2;
			PData.YPointer	=YPointer;
			PData.AreaCode	=AreaCode;
			PData.FPointer	=FPointer;
			PData.FPointerCount=0;
			PData.ReEntrantCount=0;
			RecursivePickupFlexArea(PData,&LDimPointer[i]);

			bool	RetMode;
			do{
				RetMode=false;
				for(int j=0;j<PData.FPointerCount;j++){
					if(RecursivePickupFlexArea(PData,PData.FPointer[j])==true){
						RetMode=true;
					}
				}
			}while(RetMode==true);

			if(PData.FPointerCount>0){
				struct FlexLine	*L=new struct FlexLine[PData.FPointerCount];
				for(int j=0;j<PData.FPointerCount;j++){
					L[j]._LeftX	=FPointer[j]->LeftX;
					L[j]._Numb	=FPointer[j]->Numb;
					L[j]._AbsY	=FPointer[j]->AbsY;
				}
				//_heapchk();

				PureFlexAreaList	*k=new PureFlexAreaList();
				k->SetFLineOnly(L,PData.FPointerCount);
				PureFlexAreaListPointer[PureFlexAreaListPointerCount]=k;
				PureFlexAreaListPointerCount++;
				if(PureFlexAreaListPointerCount>=MaxPureFlexAreaListPointerCount){
					MaxPureFlexAreaListPointerCount*=2;
					PureFlexAreaList	**PureFlexAreaListPointer2=new PureFlexAreaList*[MaxPureFlexAreaListPointerCount];
					int	h;
					for(h=0;h<PureFlexAreaListPointerCount;h++){
						PureFlexAreaListPointer2[h]=PureFlexAreaListPointer[h];
					}
					for(;h<MaxPureFlexAreaListPointerCount;h++){
						PureFlexAreaListPointer2[h]=NULL;
					}
					//memcpy(PureFlexAreaListPointer2,PureFlexAreaListPointer,sizeof(PureFlexAreaListPointer[0])*PureFlexAreaListPointerCount);
					if(PureFlexAreaListPointer!=PureFlexAreaListDim){
						delete	[]PureFlexAreaListPointer;
					}
					PureFlexAreaListPointer=PureFlexAreaListPointer2;
				}
			}
			AreaCode++;
			if(MaxAreaCount>=0 && AreaCode>=MaxAreaCount){
				break;
			}
		}
	}

	//if(Multithread==true && LDimCount>5000 && AreaCode>32){
	if(Multithread==true && LDimCount>500 && AreaCode>32){
		#pragma omp parallel
		{
			#pragma omp for schedule(dynamic)
			for(int i=0;i<PureFlexAreaListPointerCount;i++){
				PureFlexAreaListPointer[i]->Regulate();
			}
		}
	}
	else{
		for(int i=0;i<PureFlexAreaListPointerCount;i++){
			PureFlexAreaListPointer[i]->Regulate();
		}
	}

	for(int i=0;i<PureFlexAreaListPointerCount;i++){
		FPack.AppendList(PureFlexAreaListPointer[i]);
	}
	if(LDimPointer!=LDim){
		delete	[]LDimPointer;
	}
	if(YPointer!=YPointerDim){
		delete	[]YPointer;
	}
	if(FPointer!=FPointerDim){
		delete	[]FPointer;
	}
	if(PureFlexAreaListPointer!=PureFlexAreaListDim){
		delete	[]PureFlexAreaListPointer;
	}
	return true;
}
bool	PickupFlexAreaA(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount,bool Multithread)
{
	if(YLen<40000)
		return PickupFlexAreaPartial(Bmp ,XByte ,XLen,YLen ,FPack ,MaxAreaCount,Multithread);
	bool	Ret=true;
	int	N=YLen/30000;

	BYTE	**tmpBmp=new BYTE *[60000];
	const BYTE	**tBmp=(const BYTE	**)tmpBmp;
	for(int i=0;i<N;i++){
		int	tYLen=30000;
		int	AddedY=i*30000;
		if(i==N-1)
			tYLen=YLen-AddedY;
		for(int n=0;n<tYLen;n++){
			int	y=AddedY+n;
			tBmp[n]=Bmp[y];
		}
		PureFlexAreaListContainer tFPack;
		if(PickupFlexAreaPartial(tBmp ,XByte ,XLen,tYLen ,tFPack ,MaxAreaCount,Multithread)==false)
			Ret=false;
		PureFlexAreaList *a;
		while((a=tFPack.GetFirst())!=NULL){
			tFPack.RemoveList(a);
			a->MoveToNoClip(0,AddedY);
			FPack.AppendList(a);
		}
	}
	delete	[]tmpBmp;
	return Ret;
}


bool	PickupFlexAreaB(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount,bool Multithread)
{
	const	int	__MaxDimCount=10000;

	int		MaxDimCount=__MaxDimCount;
	struct	PickupFlexAreaStruct	LDim[__MaxDimCount];
	int								LDimCount;
	struct	PickupFlexAreaStructPointer	YPointerDim[__MaxDimCount];

	struct	PickupFlexAreaStruct		*LDimPointer=LDim;
	struct	PickupFlexAreaStructPointer	*YPointer;
	
	struct	PickupFlexAreaStruct		*FPointerDim[__MaxDimCount];
	struct	PickupFlexAreaStruct		**FPointer=FPointerDim;
	
	if(YLen>=MaxDimCount){
		YPointer=new struct PickupFlexAreaStructPointer[YLen];
	}
	else{
		YPointer	=YPointerDim;
	}
	XLen=min(XLen,XByte*8);

	LDimCount=0;
	for(int y=0;y<YLen;y++){
		const BYTE	*b=Bmp[y];
		YPointer[y].DimPoint=LDimCount;
		YPointer[y].Count=0;
		int		Offset=0;
		for(int x=0;x<XLen;x+=8,Offset++){
			if(b[Offset]==0){
				continue;
			}
			BYTE	Mask=0x80;
			for(int r=0;r<8;r++,Mask>>=1){
				if((b[Offset] & Mask)!=0){
					LDimPointer[LDimCount].AbsY		=y;
					LDimPointer[LDimCount].LeftX	=x+r;
					LDimPointer[LDimCount].Numb		=1;
					LDimPointer[LDimCount].Code		=-1;
					int x2=x;
					Mask>>=1;
					r++;
					for(;;){
						for(;r<8;r++,Mask>>=1){
							if((b[Offset] & Mask)==0){
								goto	FoundBitEnd;
							}
						}
						Mask=0x80;
						r=0;
						do{
							Offset++;
							x2+=8;
							if(x2>=XLen){
								goto	FoundBitEnd;
							}
						}while(b[Offset]==0xFF);
					}
FoundBitEnd:
					LDimPointer[LDimCount].Numb	=x2+r-LDimPointer[LDimCount].LeftX;
					x=x2;

					//_heapchk();

					LDimCount++;
					YPointer[y].Count++;
					if(LDimCount>=MaxDimCount){
						MaxDimCount=MaxDimCount*2;
						struct PickupFlexAreaStruct	*LDimPointer2=new struct PickupFlexAreaStruct[MaxDimCount];
						int	h;
						for(h=0;h<LDimCount;h++){
							LDimPointer2[h]=LDimPointer[h];
						}
						//_heapchk();

						//memcpy(LDimPointer2,LDimPointer,sizeof(LDimPointer[0])*LDimCount);
						if(LDimPointer!=LDim){
							delete	[]LDimPointer;
						}
						LDimPointer=LDimPointer2;
					}
					if(x>=XLen){
						break;
					}
				}
			}
		}
	}

	for(int y=0;y<YLen;y++){
		YPointer[y].DimPointer=&LDimPointer[YPointer[y].DimPoint];
	}
	int	TopY=-1,BottomY=-1;
	for(int y=0;y<YLen;y++){
		if(YPointer[y].Count>0){
			TopY=y;
			break;
		}
	}
	for(int y=YLen-1;y>=0;y--){
		if(YPointer[y].Count>0){
			BottomY=y;
			break;
		}
	}
	if(TopY<0 || BottomY<0){
		if(LDimPointer!=LDim){
			delete	[]LDimPointer;
		}
		if(YPointer!=YPointerDim){
			delete	[]YPointer;
		}
		return true;
	}

	if(LDimCount>=__MaxDimCount){
		FPointer	=new struct	PickupFlexAreaStruct*[LDimCount];
	}

	int	LastY=TopY;
	int	LastI=0;
	for(int	AreaCode=0;;AreaCode++){
		int	h=0;
		for(int y=LastY;y<=BottomY;y++){
			for(int i=LastI;i<YPointer[y].Count;i++){
				if(YPointer[y].DimPointer[i].Code==-1){
					FPointer[h]=&YPointer[y].DimPointer[i];
					FPointer[h]->Code=AreaCode;
					LastY=y;
					LastI=i;
					h++;
					goto	PNext;
				}
			}
			y++;
			if(y<=BottomY){
				for(int i=0;i<YPointer[y].Count;i++){
					if(YPointer[y].DimPointer[i].Code==-1){
						FPointer[h]=&YPointer[y].DimPointer[i];
						FPointer[h]->Code=AreaCode;
						LastY=y;
						LastI=i;
						h++;
						goto	PNext;
					}
				}
			}
		}
PNext:;
		if(h==0)
			break;

		int	LastH;
		do{
			LastH=h;
			for(int t=0;t<h;t++){
				int	y=FPointer[t]->AbsY;
				if(y==BottomY || YPointer[y+1].Count==0){
					break;
				}
				y++;
				for(int i=0;i<YPointer[y].Count;i++){
					if(YPointer[y].DimPointer[i].Code==-1 && IsNearby(*FPointer[t],YPointer[y].DimPointer[i])==true){
						FPointer[h]=&YPointer[y].DimPointer[i];
						FPointer[h]->Code=AreaCode;
						h++;
					}
				}
			}
			for(int t=0;t<h;t++){
				int	y=FPointer[t]->AbsY;
				if(y>TopY){
					if(YPointer[y-1].Count==0){
						break;
					}
					y--;
					for(int i=0;i<YPointer[y].Count;i++){
						if(YPointer[y].DimPointer[i].Code==-1 && IsNearby(*FPointer[t],YPointer[y].DimPointer[i])==true){
							FPointer[h]=&YPointer[y].DimPointer[i];
							FPointer[h]->Code=AreaCode;
							h++;
						}
					}
				}
			}
		}while(LastH!=h);

		if(h>0){
			struct FlexLine	*L=new struct FlexLine[h];
			for(int j=0;j<h;j++){
				L[j]._LeftX	=FPointer[j]->LeftX;
				L[j]._Numb	=FPointer[j]->Numb;
				L[j]._AbsY	=FPointer[j]->AbsY;
			}
			//_heapchk();

			PureFlexAreaList	*k=new PureFlexAreaList();
			k->SetFLineOnly(L,h);
			FPack.AppendList(k);
		}
		if(AreaCode==MaxAreaCount){
			break;
		}
	}

	if(LDimPointer!=LDim){
		delete	[]LDimPointer;
	}
	if(YPointer!=YPointerDim){
		delete	[]YPointer;
	}
	if(FPointer!=FPointerDim){
		delete	[]FPointer;
	}

	PureFlexAreaList					*PureFlexAreaListDim[__MaxDimCount];
	PureFlexAreaList					**PureFlexAreaListPointer=PureFlexAreaListDim;
	//int									MaxPureFlexAreaListPointerCount=__MaxDimCount;
	int									PureFlexAreaListPointerCount;

	PureFlexAreaListPointerCount=FPack.GetCount();
	if(PureFlexAreaListPointerCount>__MaxDimCount){
		PureFlexAreaListPointer=new PureFlexAreaList*[PureFlexAreaListPointerCount];
	}
	int	t=0;
	for(PureFlexAreaList *k=FPack.GetFirst();k!=NULL;k=k->GetNext()){
		PureFlexAreaListPointer[t]=k;
		t++;
	}

	//if(Multithread==true && LDimCount>5000 && AreaCode>32){
	if(Multithread==true && LDimCount>500 && PureFlexAreaListPointerCount>32){
		#pragma omp parallel
		{
			#pragma omp for schedule(dynamic)
			for(int i=0;i<PureFlexAreaListPointerCount;i++){
				PureFlexAreaListPointer[i]->Regulate();
			}
		}
	}
	else{
		for(int i=0;i<PureFlexAreaListPointerCount;i++){
			PureFlexAreaListPointer[i]->Regulate();
		}
	}


	if(PureFlexAreaListPointer!=PureFlexAreaListDim){
		delete	[]PureFlexAreaListPointer;
	}
	return true;
}
bool	PickupFlexArea(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount,bool Multithread)
{
	if(YLen<40000)
		return PickupFlexAreaA(Bmp ,XByte ,XLen,YLen ,FPack ,MaxAreaCount,Multithread);
	else
		return PickupFlexAreaB(Bmp ,XByte ,XLen,YLen ,FPack ,MaxAreaCount,Multithread);
}

bool	PickupFlexAreaA(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack 
					,int AreaX1 ,int AreaY1 ,int AreaX2 ,int AreaY2
					,int MaxAreaCount,bool Multithread)
{
	if(YLen<40000)
		return PickupFlexAreaPartial(Bmp ,XByte ,XLen,YLen ,FPack ,AreaX1 ,AreaY1 ,AreaX2 ,AreaY2,MaxAreaCount,Multithread);
	bool	Ret=true;
	int	N=YLen/30000;
	BYTE	**tmpBmp=new BYTE *[60000];
	const BYTE	**tBmp=(const BYTE	**)tmpBmp;
	for(int i=0;i<N;i++){
		int	tYLen=30000;
		int	AddedY=i*30000;
		if(i==N-1)
			tYLen=YLen-AddedY;
		for(int n=0;n<tYLen;n++){
			int	y=AddedY+n;
			tBmp[n]=Bmp[y];
		}
		PureFlexAreaListContainer tFPack;
		if(PickupFlexAreaPartial(tBmp ,XByte ,XLen,tYLen ,tFPack ,AreaX1 ,AreaY1 ,AreaX2 ,AreaY2,MaxAreaCount,Multithread)==false)
			Ret=false;
		PureFlexAreaList *a;
		while((a=tFPack.GetFirst())!=NULL){
			tFPack.RemoveList(a);
			a->MoveToNoClip(0,AddedY);
			FPack.AppendList(a);
		}
	}
	delete	[]tmpBmp;
	return Ret;
}


bool	PickupFlexAreaB(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack 
					,int AreaX1 ,int AreaY1 ,int AreaX2 ,int AreaY2
					,int MaxAreaCount,bool Multithread)
{
	const	int	__MaxDimCount=10000;

	int		MaxDimCount=__MaxDimCount;
	struct	PickupFlexAreaStruct	LDim[__MaxDimCount];
	int								LDimCount;
	struct	PickupFlexAreaStructPointer	YPointerDim[__MaxDimCount];

	struct	PickupFlexAreaStruct		*LDimPointer=LDim;
	struct	PickupFlexAreaStructPointer	*YPointer;
	
	struct	PickupFlexAreaStruct		*FPointerDim[__MaxDimCount];
	struct	PickupFlexAreaStruct		**FPointer=FPointerDim;
	
	if(AreaY2-AreaY1>=MaxDimCount){
		YPointer=new struct PickupFlexAreaStructPointer[YLen];
	}
	else{
		YPointer	=YPointerDim;
	}
	XLen=min(XLen,XByte*8);

	LDimCount=0;
	int	Lx1=AreaX1&0xFFF8;
	int	Lx2=min((AreaX2+7)&0xFFF8,XLen);
	int	Ly1=max(AreaY1,0);
	int	Ly2=min(AreaY2,YLen);

	for(int y=Ly1;y<Ly2;y++){
		const BYTE	*b=Bmp[y];
		YPointer[y-Ly1].DimPoint=LDimCount;
		YPointer[y-Ly1].Count=0;
		int		Offset=Lx1>>3;
		for(int x=Lx1;x<Lx2;x+=8,Offset++){
			if(x<AreaX1)
				continue;
			if(AreaX2<=x)
				break;

			if(b[Offset]==0){
				continue;
			}
			BYTE	Mask=0x80;
			for(int r=0;r<8;r++,Mask>>=1){
				if((b[Offset] & Mask)!=0){
					LDimPointer[LDimCount].AbsY		=y;
					LDimPointer[LDimCount].LeftX	=x+r;
					LDimPointer[LDimCount].Numb		=1;
					LDimPointer[LDimCount].Code		=-1;
					int x2=x;
					Mask>>=1;
					r++;
					for(;;){
						for(;r<8;r++,Mask>>=1){
							if((b[Offset] & Mask)==0){
								goto	FoundBitEnd;
							}
						}
						Mask=0x80;
						r=0;
						do{
							Offset++;
							x2+=8;
							if(x2>=XLen){
								goto	FoundBitEnd;
							}
						}while(b[Offset]==0xFF);
					}
FoundBitEnd:
					LDimPointer[LDimCount].Numb	=x2+r-LDimPointer[LDimCount].LeftX;
					x=x2;

					//_heapchk();

					LDimCount++;
					YPointer[y-Ly1].Count++;
					if(LDimCount>=MaxDimCount){
						MaxDimCount=MaxDimCount*2;
						struct PickupFlexAreaStruct	*LDimPointer2=new struct PickupFlexAreaStruct[MaxDimCount];
						int	h;
						for(h=0;h<LDimCount;h++){
							LDimPointer2[h]=LDimPointer[h];
						}
						//_heapchk();

						//memcpy(LDimPointer2,LDimPointer,sizeof(LDimPointer[0])*LDimCount);
						if(LDimPointer!=LDim){
							delete	[]LDimPointer;
						}
						LDimPointer=LDimPointer2;
					}
					if(x>=XLen){
						break;
					}
				}
			}
		}
	}

	int	N=0;
	for(int y=Ly1;y<Ly2;y++){
		YPointer[N].DimPointer=&LDimPointer[YPointer[N].DimPoint];
		N++;
	}
	int	TopY=-1,BottomY=-1;
	for(int y=Ly1;y<Ly2;y++){
		if(YPointer[y-Ly1].Count>0){
			TopY=y;
			break;
		}
	}
	for(int y=Ly2-1;y>=Ly1;y--){
		if(YPointer[y-Ly1].Count>0){
			BottomY=y;
			break;
		}
	}
	if(TopY<0 || BottomY<0){
		if(LDimPointer!=LDim){
			delete	[]LDimPointer;
		}
		if(YPointer!=YPointerDim){
			delete	[]YPointer;
		}
		return true;
	}

	if(LDimCount>=__MaxDimCount){
		FPointer	=new struct	PickupFlexAreaStruct*[LDimCount];
	}

	int	LastY=TopY;
	int	LastI=0;
	for(int	AreaCode=0;;AreaCode++){
		int	h=0;
		for(int y=LastY;y<=BottomY;y++){
			for(int i=LastI;i<YPointer[y-Ly1].Count;i++){
				if(YPointer[y-Ly1].DimPointer[i].Code==-1){
					FPointer[h]=&YPointer[y-Ly1].DimPointer[i];
					FPointer[h]->Code=AreaCode;
					LastY=y;
					LastI=i;
					h++;
					goto	PNext;
				}
			}
			y++;
			if(y<=BottomY){
				for(int i=0;i<YPointer[y-Ly1].Count;i++){
					if(YPointer[y-Ly1].DimPointer[i].Code==-1){
						FPointer[h]=&YPointer[y-Ly1].DimPointer[i];
						FPointer[h]->Code=AreaCode;
						LastY=y;
						LastI=i;
						h++;
						goto	PNext;
					}
				}
			}
		}
PNext:;
		if(h==0)
			break;

		int	LastH;
		do{
			LastH=h;
			for(int t=0;t<h;t++){
				int	y=FPointer[t]->AbsY;
				if(y==BottomY || YPointer[y+1-Ly1].Count==0){
					break;
				}
				y++;
				for(int i=0;i<YPointer[y-Ly1].Count;i++){
					if(YPointer[y-Ly1].DimPointer[i].Code==-1 && IsNearby(*FPointer[t],YPointer[y-Ly1].DimPointer[i])==true){
						FPointer[h]=&YPointer[y-Ly1].DimPointer[i];
						FPointer[h]->Code=AreaCode;
						h++;
					}
				}
			}
			for(int t=0;t<h;t++){
				int	y=FPointer[t]->AbsY;
				if(y>TopY){
					if(YPointer[y-1-Ly1].Count==0){
						break;
					}
					y--;
					for(int i=0;i<YPointer[y-Ly1].Count;i++){
						if(YPointer[y-Ly1].DimPointer[i].Code==-1 && IsNearby(*FPointer[t],YPointer[y-Ly1].DimPointer[i])==true){
							FPointer[h]=&YPointer[y-Ly1].DimPointer[i];
							FPointer[h]->Code=AreaCode;
							h++;
						}
					}
				}
			}
		}while(LastH!=h);

		if(h>0){
			struct FlexLine	*L=new struct FlexLine[h];
			for(int j=0;j<h;j++){
				L[j]._LeftX	=FPointer[j]->LeftX;
				L[j]._Numb	=FPointer[j]->Numb;
				L[j]._AbsY	=FPointer[j]->AbsY;
			}
			//_heapchk();

			PureFlexAreaList	*k=new PureFlexAreaList();
			k->SetFLineOnly(L,h);
			FPack.AppendList(k);
		}
		if(AreaCode==MaxAreaCount){
			break;
		}
	}

	if(LDimPointer!=LDim){
		delete	[]LDimPointer;
	}
	if(YPointer!=YPointerDim){
		delete	[]YPointer;
	}
	if(FPointer!=FPointerDim){
		delete	[]FPointer;
	}

	PureFlexAreaList					*PureFlexAreaListDim[__MaxDimCount];
	PureFlexAreaList					**PureFlexAreaListPointer=PureFlexAreaListDim;
	//int									MaxPureFlexAreaListPointerCount=__MaxDimCount;
	int									PureFlexAreaListPointerCount;

	PureFlexAreaListPointerCount=FPack.GetCount();
	if(PureFlexAreaListPointerCount>__MaxDimCount){
		PureFlexAreaListPointer=new PureFlexAreaList*[PureFlexAreaListPointerCount];
	}
	int	t=0;
	for(PureFlexAreaList *k=FPack.GetFirst();k!=NULL;k=k->GetNext()){
		PureFlexAreaListPointer[t]=k;
		t++;
	}

	//if(Multithread==true && LDimCount>5000 && AreaCode>32){
	if(Multithread==true && LDimCount>500 && PureFlexAreaListPointerCount>32){
		#pragma omp parallel
		{
			#pragma omp for schedule(dynamic)
			for(int i=0;i<PureFlexAreaListPointerCount;i++){
				PureFlexAreaListPointer[i]->Regulate();
			}
		}
	}
	else{
		for(int i=0;i<PureFlexAreaListPointerCount;i++){
			PureFlexAreaListPointer[i]->Regulate();
		}
	}


	if(PureFlexAreaListPointer!=PureFlexAreaListDim){
		delete	[]PureFlexAreaListPointer;
	}
	return true;
}

bool	PickupFlexArea(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack
					,int AreaX1 ,int AreaY1 ,int AreaX2 ,int AreaY2
					,int MaxAreaCount,bool Multithread)
{
	if(YLen<40000)
		return PickupFlexAreaA(Bmp ,XByte ,XLen,YLen ,FPack , AreaX1 , AreaY1 , AreaX2 , AreaY2,MaxAreaCount,Multithread);
	else
		return PickupFlexAreaB(Bmp ,XByte ,XLen,YLen ,FPack , AreaX1 , AreaY1 , AreaX2 , AreaY2,MaxAreaCount,Multithread);
}


bool	PickupFlexAreaWhole(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount,bool Multithread)
{
	return PickupFlexAreaPartial(Bmp ,XByte ,XLen,YLen ,FPack ,MaxAreaCount,Multithread);
}

bool	PickupFlexOneArea(BYTE **Bmp ,int XByte ,int XLen,int YLen 
						,int LocalX ,int LocalY
						,FlexArea &FArea)
{
	const	int	__MaxDimCount=10000;

	int		MaxDimCount=__MaxDimCount;
	struct	PickupFlexAreaStruct	LDim[__MaxDimCount];
	int								LDimCount;
	struct	PickupFlexAreaStructPointer	YPointerDim[__MaxDimCount];

	struct	PickupFlexAreaStruct		*LDimPointer=LDim;
	struct	PickupFlexAreaStructPointer	*YPointer;
	
	struct	PickupFlexAreaStruct		*FPointerDim[__MaxDimCount];
	struct	PickupFlexAreaStruct		**FPointer=FPointerDim;
	//PureFlexAreaList					*PureFlexAreaListDim[__MaxDimCount];
	
	if(YLen>=MaxDimCount){
		YPointer=new struct PickupFlexAreaStructPointer[YLen];
	}
	else{
		YPointer	=YPointerDim;
	}

	if(LocalX<0 || XLen<=LocalX || LocalY<0 || YLen<=LocalY)
		return false;


	LDimCount=0;
	for(int y=0;y<YLen;y++){
		BYTE	*b=Bmp[y];
		YPointer[y].DimPoint=LDimCount;
		YPointer[y].Count=0;
		int		Offset=0;
		for(int x=0;x<XLen;x+=8,Offset++){
			if(b[Offset]==0){
				continue;
			}
			BYTE	Mask=0x80;
			for(int r=0;r<8;r++,Mask>>=1){
				if((b[Offset] & Mask)!=0){
					LDimPointer[LDimCount].AbsY		=y;
					LDimPointer[LDimCount].LeftX	=x+r;
					LDimPointer[LDimCount].Numb		=1;
					LDimPointer[LDimCount].Code		=-1;
					int x2=x;
					Mask>>=1;
					r++;
					for(;;){
						for(;r<8;r++,Mask>>=1){
							if((b[Offset] & Mask)==0){
								goto	FoundBitEnd;
							}
						}
						Mask=0x80;
						r=0;
						do{
							Offset++;
							x2+=8;
							if(x2>=XLen){
								goto	FoundBitEnd;
							}
						}while(b[Offset]==0xFF);
					}
FoundBitEnd:
					LDimPointer[LDimCount].Numb	=x2+r-LDimPointer[LDimCount].LeftX;
					x=x2;

					LDimCount++;
					YPointer[y].Count++;
					if(LDimCount>=MaxDimCount){
						MaxDimCount=MaxDimCount*2;
						struct PickupFlexAreaStruct	*LDimPointer2=new struct PickupFlexAreaStruct[MaxDimCount];
						memcpy(LDimPointer2,LDimPointer,sizeof(LDimPointer[0])*LDimCount);
						if(LDimPointer!=LDim){
							delete	[]LDimPointer;
						}
						LDimPointer=LDimPointer2;
					}
					if(x>=XLen){
						break;
					}
				}
			}
		}
	}
	for(int y=0;y<YLen;y++){
		YPointer[y].DimPointer=&LDimPointer[YPointer[y].DimPoint];
	}

	if(LDimCount>=__MaxDimCount){
		FPointer	=new struct	PickupFlexAreaStruct*[LDimCount];
	}

	int	IndexI;
	for(IndexI=0;IndexI<LDimCount;IndexI++){
		if(LDimPointer[IndexI].AbsY==LocalY && LDimPointer[IndexI].LeftX<=LocalX && LocalX<=(LDimPointer[IndexI].LeftX+LDimPointer[IndexI].Numb)){
			break;
		}
	}
	if(IndexI>=LDimCount)
		return false;


	int	AreaCode=0;

	struct	PickupFlexAreaRDim	PData;
	PData.LDim		=LDimPointer;
	PData.YLen		=YLen;
	PData.YPointer	=YPointer;
	PData.AreaCode	=AreaCode;
	PData.FPointer	=FPointer;
	PData.FPointerCount=0;
	PData.ReEntrantCount=0;
	RecursivePickupFlexArea(PData,&LDimPointer[IndexI]);

	bool	RetMode;
	do{
		RetMode=false;
		for(int j=0;j<PData.FPointerCount;j++){
			if(RecursivePickupFlexArea(PData,PData.FPointer[j])==true){
				RetMode=true;
			}
		}
	}while(RetMode==true);

	if(PData.FPointerCount>0){
		struct FlexLine	*L=new struct FlexLine[PData.FPointerCount];
		int N=0;
		for(int j=0;j<PData.FPointerCount;j++){
			L[N]._LeftX	=FPointer[j]->LeftX;
			L[N]._Numb	=FPointer[j]->Numb;
			L[N]._AbsY	=FPointer[j]->AbsY;
			N++;
		}
		FArea.SetFLineOnly(L,N);
		FArea.Regulate();
	}
	if(LDimPointer!=LDim){
		delete	[]LDimPointer;
	}
	if(YPointer!=YPointerDim){
		delete	[]YPointer;
	}
	if(FPointer!=FPointerDim){
		delete	[]FPointer;
	}

	return true;
}

//=============================================

int		PickupFlexAreaFastDimPartial(BYTE ** Bmp ,int XByte ,int XLen,int YLen 
							,FlexAreaFastDimPack &FPackDim
							,int Y1,int Y2
							,int MinDotCount);

class FlexAreaFastPointerDim
{
	FlexAreaFast *Pointer[200];
	int			CountOfPointer;
public:
	FlexAreaFastPointerDim()
	{
		CountOfPointer=0;
	}
	void	AddPointer(FlexAreaFast *P)
	{
		if(0<=CountOfPointer && CountOfPointer<sizeof(Pointer)/sizeof(Pointer[0])){
			Pointer[CountOfPointer]=P;
			CountOfPointer++;
		}
	}
	int		GetCountOfPointer()
	{
		return	CountOfPointer;
	}
	FlexAreaFast*	GetPointer(int Index)
	{
		return	Pointer[Index];
	}
	void	ClearPointer(int Index)
	{
		if(0<=Index && Index<CountOfPointer){
			Pointer[Index]=NULL;
		}
	}
	void	SetPointer(int Index ,FlexAreaFast *P)
	{
		if(0<=Index && Index<CountOfPointer){
			Pointer[Index]=P;
		}
	}
};


int		PickupFlexAreaFastDim(BYTE **Bmp ,int XByte ,int XLen,int YLen 
							,FlexAreaFastDimPack &RetPackDim 
							,int MinDotCount,bool Multithread)
{
	int	MaxLinesCount=1000;
	if(YLen<MaxLinesCount){
		return PickupFlexAreaFastDimPartial(Bmp ,XByte ,XLen,YLen 
									,RetPackDim 
									,0,YLen
									,MinDotCount);
	}
	int	N = (YLen+MaxLinesCount-1)/MaxLinesCount;
	int	DCounter[1000];
	FlexAreaFastDimPack	*FPackDim=new FlexAreaFastDimPack[N];
	int	Counter=0;
	if(Multithread==true){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<N;i++){
				int	Y1=i*MaxLinesCount;
				int	Y2=(i+1)*MaxLinesCount;
				if(Y2>YLen)
					Y2=YLen;
				DCounter[i]=PickupFlexAreaFastDimPartial(Bmp ,XByte ,XLen,YLen 
									,FPackDim[i]
									,Y1,Y2
									,MinDotCount);
			}
		}
	}
	else{
		for(int i=0;i<N;i++){
			int	Y1=i*MaxLinesCount;
			int	Y2=(i+1)*MaxLinesCount;
			if(Y2>YLen)
				Y2=YLen;
			DCounter[i]=PickupFlexAreaFastDimPartial(Bmp ,XByte ,XLen,YLen 
								,FPackDim[i]
								,Y1,Y2
								,MinDotCount);
		}
	}

	FlexAreaFastPointerDim	MaxYPointerDim[N];
	FlexAreaFastPointerDim	MinYPointerDim[N];

	for(int i=0;i<N-1;i++){
		int	Y2=(i+1)*MaxLinesCount;
		FlexAreaFast	*Upper[1000];
		for(int u=0;u<DCounter[i];u++){
			FlexAreaFast &p = (FPackDim[i])[u];
			if(p.GetMaxY()==Y2){
				MaxYPointerDim[i].AddPointer(&p);
			}
		}
		FlexAreaFast	*Lower[1000];
		int	Y1=i*MaxLinesCount;
		for(int d=0;d<DCounter[i];d++){
			FlexAreaFast &p = (FPackDim[i])[d];
			if(p.GetMinY()==Y1){
				MinYPointerDim[i].AddPointer(&p);
			}
		}
	}
	for(int i=0;i<N-1;i++){
		int	Y2=(i+1)*MaxLinesCount;
		for(int u=0;u<MaxYPointerDim[i].GetCountOfPointer();u++){
			FlexAreaFast *uP = MaxYPointerDim[i].GetPointer(u);
			if(uP==NULL)
				continue;
			int	UIndexStart ,UIndexEnd;
			uP->FindIndex(Y2-1 ,UIndexStart ,UIndexEnd);
			for(int d=0;d<MinYPointerDim[i+1].GetCountOfPointer();d++){
				FlexAreaFast *dP = MinYPointerDim[i+1].GetPointer(d);
				if(dP==NULL)
					continue;
				int	DIndexStart ,DIndexEnd;
				dP->FindIndex(Y2 ,DIndexStart ,DIndexEnd);
				for(int k=UIndexStart;k<=UIndexEnd;k++){
					int	UX1 = uP->GetFLineLeftX(k);
					int	UX2 = uP->GetFLineRightX(k);
					for(int j=DIndexStart;j<=DIndexEnd;j++){
						int	DX1 = dP->GetFLineLeftX(j);
						int	DX2 = dP->GetFLineRightX(j);
						if((UX1<=DX1 && DX1<=UX2)
						|| (UX1<=DX2 && DX2<=UX2)
						|| (DX1<=UX1 && UX1<=DX2)){
							(*uP) += *(dP);
							dP->Clear();
							MaxYPointerDim[i].ClearPointer(u);
							int j=i+1;
							for(int m = 0;m<MaxYPointerDim[j].GetCountOfPointer();m++){
								FlexAreaFast *tP = MaxYPointerDim[j].GetPointer(m);
								if(tP==dP){
									MaxYPointerDim[j].SetPointer(m,uP);
								}
							}
						}
					}
				}
			}
		}
	}




	int	RetCounter=0;
	if(MinDotCount==0){
		for(int i=0;i<N;i++){
			FlexAreaFastDimPack	*SrcD=&FPackDim[i];
			for(int u=0;u<DCounter[i];u++){
				FlexAreaFast	&s=(*SrcD)[u];
				int	c = s.GetPatternByte();
				if(c>0){
					RetPackDim[RetCounter]=s;
					RetCounter++;
				}
			}
		}
	}
	else{
		for(int i=0;i<N;i++){
			FlexAreaFastDimPack	*SrcD=&FPackDim[i];
			for(int u=0;u<DCounter[i];u++){
				FlexAreaFast	&s=(*SrcD)[u];
				int	c = s.GetPatternByte();
				if(c>=MinDotCount){
					RetPackDim[RetCounter]=s;
					RetCounter++;
				}
			}
		}
	}


	delete[]FPackDim;



	return Counter;
}




int		PickupFlexAreaFastDimPartial(BYTE **Bmp ,int XByte ,int XLen,int YLen 
							,FlexAreaFastDimPack &RetPackDim
							,int Y1,int Y2
							,int MinDotCount)
{
	const	int	__MaxDimCount=10000;

	int		MaxDimCount=__MaxDimCount;
	struct	PickupFlexAreaStruct	LDim[__MaxDimCount];
	int								LDimCount;
	struct	PickupFlexAreaStructPointer	YPointerDim[__MaxDimCount];

	struct	PickupFlexAreaStruct		*LDimPointer=LDim;
	struct	PickupFlexAreaStructPointer	*YPointer;
	
	struct	PickupFlexAreaStruct		*FPointerDim[__MaxDimCount];
	struct	PickupFlexAreaStruct		**FPointer=FPointerDim;
	PureFlexAreaList					*PureFlexAreaListDim[__MaxDimCount];
	//PureFlexAreaList					**PureFlexAreaListPointer=PureFlexAreaListDim;
	//int									MaxPureFlexAreaListPointerCount=__MaxDimCount;
	//int									PureFlexAreaListPointerCount=0;
	
	int	Yn=Y2-Y1;
	if(YLen>=Yn){
		YPointer=new struct PickupFlexAreaStructPointer[Yn];
	}
	else{
		YPointer	=YPointerDim;
	}
	XLen=min(XLen,XByte*8);

	LDimCount=0;
	int	n=0;
	for(int y=Y1;y<YLen && y<Y2;y++,n++){
		const BYTE	*b=Bmp[y];
		YPointer[n].DimPoint=LDimCount;
		YPointer[n].Count=0;
		int		Offset=0;
		for(int x=0;x<XLen;x+=8,Offset++){
			if(b[Offset]==0){
				continue;
			}
			BYTE	Mask=0x80;
			for(int r=0;r<8;r++,Mask>>=1){
				if((b[Offset] & Mask)!=0){
					LDimPointer[LDimCount].AbsY		=y;
					LDimPointer[LDimCount].LeftX	=x+r;
					LDimPointer[LDimCount].Numb		=1;
					LDimPointer[LDimCount].Code		=-1;
					int x2=x;
					Mask>>=1;
					r++;
					for(;;){
						for(;r<8;r++,Mask>>=1){
							if((b[Offset] & Mask)==0){
								goto	FoundBitEnd;
							}
						}
						Mask=0x80;
						r=0;
						do{
							Offset++;
							x2+=8;
							if(x2>=XLen){
								goto	FoundBitEnd;
							}
						}while(b[Offset]==0xFF);
					}
FoundBitEnd:
					LDimPointer[LDimCount].Numb	=x2+r-LDimPointer[LDimCount].LeftX;
					x=x2;

					//_heapchk();

					LDimCount++;
					YPointer[n].Count++;
					if(LDimCount>=MaxDimCount){
						MaxDimCount=MaxDimCount*2;
						struct PickupFlexAreaStruct	*LDimPointer2=new struct PickupFlexAreaStruct[MaxDimCount];
						int	h;
						for(h=0;h<LDimCount;h++){
							LDimPointer2[h]=LDimPointer[h];
						}
						//_heapchk();

						//memcpy(LDimPointer2,LDimPointer,sizeof(LDimPointer[0])*LDimCount);
						if(LDimPointer!=LDim){
							delete	[]LDimPointer;
						}
						LDimPointer=LDimPointer2;
					}
					if(x>=XLen){
						break;
					}
				}
			}
		}
	}

	for(int n=0;n<Yn;n++){
		YPointer[n].DimPointer=&LDimPointer[YPointer[n].DimPoint];
	}

	if(LDimCount>=__MaxDimCount){
		FPointer	=new struct	PickupFlexAreaStruct*[LDimCount];
	}

	int	AreaCode=0;
	for(int i=0;i<LDimCount;i++){
		if(LDimPointer[i].Code==-1){
			struct	PickupFlexAreaRDimAreaY	PData;
			PData.LDim		=LDimPointer;
			PData.YLen		=YLen;
			PData.AreaY1	=Y1;
			PData.AreaY2	=Y2;
			PData.YPointer	=YPointer;
			PData.AreaCode	=AreaCode;
			PData.FPointer	=FPointer;
			PData.FPointerCount=0;
			PData.ReEntrantCount=0;
			PData.LimitY1	=false;
			PData.LimitY2	= false;
			RecursivePickupFlexArea(PData,&LDimPointer[i]);

			bool	RetMode;
			do{
				RetMode=false;
				for(int j=0;j<PData.FPointerCount;j++){
					if(RecursivePickupFlexArea(PData,PData.FPointer[j])==true){
						RetMode=true;
					}
				}
			}while(RetMode==true);

			if(PData.FPointerCount>0){
				FlexAreaFast	&S=RetPackDim[AreaCode];
				S.Clear();
				struct FlexLine	*L;
				if(PData.FPointerCount<=MAXFlexAreaFastLines){
					L=S.GetFLinesDim();
				}
				else{
					L=new struct FlexLine[PData.FPointerCount];
				}
				S.SetFLineLen(PData.FPointerCount);
				for(int j=0;j<PData.FPointerCount;j++){
					L[j]._LeftX	=FPointer[j]->LeftX;
					L[j]._Numb	=FPointer[j]->Numb;
					L[j]._AbsY	=FPointer[j]->AbsY;
				}
				if(PData.FPointerCount>MAXFlexAreaFastLines){
					S.SetFLinesPointer(L);
				}
				S.Regulate();
				if(MinDotCount==0){
					if(S.GetPatternByte()>0){
						AreaCode++;
					}
					else{
						S.Clear();
					}
				}
				else{
					if(S.GetPatternByte()>=MinDotCount){
						AreaCode++;
					}
					else{
						S.Clear();
					}
				}
			}
		}
	}

	if(LDimPointer!=LDim){
		delete	[]LDimPointer;
	}
	if(YPointer!=YPointerDim){
		delete	[]YPointer;
	}
	if(FPointer!=FPointerDim){
		delete	[]FPointer;
	}
	//if(PureFlexAreaListPointer!=PureFlexAreaListDim){
	//	delete	[]PureFlexAreaListPointer;
	//}
	return AreaCode;
}

//====================================================================================
#pragma	pack(push)
#pragma	pack(1)

struct	PickupFlexAreaStruct_s
{
	short	AbsY;
	short	LeftX;
	short	Numb;
	short	Code;
};

struct	PickupFlexAreaStructPointer_s
{
	short	DimPoint;
	short	Count;
	struct	PickupFlexAreaStruct_s	*DimPointer;
};

#pragma	pack(pop)

inline	bool	IsNearby(const struct PickupFlexAreaStruct_s &s1 ,const struct PickupFlexAreaStruct_s &s2)
{
	if((s1.LeftX+s1.Numb)<s2.LeftX){
		return false;
	}
	if((s2.LeftX+s2.Numb)<s1.LeftX){
		return false;
	}
	return true;
}

#pragma	pack(push)
#pragma	pack(1)
struct	PickupFlexAreaRDim_s
{
	struct	PickupFlexAreaStruct_s			*LDim;
	struct	PickupFlexAreaStructPointer_s	*YPointer;
	short	YLen;
	short	AreaCode;
	short	FPointerCount;
	struct	PickupFlexAreaStruct_s			**FPointer;
	int		ReEntrantCount;
};
#pragma	pack(pop)

static	bool	RecursivePickupFlexArea(struct	PickupFlexAreaRDim_s &PData ,struct PickupFlexAreaStruct_s *SPoint)
{
	short	L=SPoint->AbsY;
	int	N;
	int j;
	struct	PickupFlexAreaStruct_s	*s;
	bool	Ret=false;

	PData.ReEntrantCount++;
	if(SPoint->Code==-1){
		PData.FPointer[PData.FPointerCount]=SPoint;
		PData.FPointerCount++;
		SPoint->Code=PData.AreaCode;
	}

	if(L>0){
		N=PData.YPointer[L-1].Count;
		s=PData.YPointer[L-1].DimPointer;
		for(j=0;j<N;j++,s++){
			if(s->Code==-1){
				if(IsNearby(*SPoint,*s)==true){
					RecursivePickupFlexArea(PData,s);
					Ret=true;
				}
			}
		}
	}
	if((L+1)<PData.YLen){
		N=PData.YPointer[L+1].Count;
		s=PData.YPointer[L+1].DimPointer;
		for(j=0;j<N;j++,s++){
			if(s->Code==-1){
				if(IsNearby(*SPoint,*s)==true){
					RecursivePickupFlexArea(PData,s);
					Ret=true;
				}
			}
		}
	}
	PData.ReEntrantCount--;
	return Ret;
}

bool	PickupFlexAreaPartial_s(BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount,bool Multithread)
{
	const	int	__MaxDimCount=10000;

	int		MaxDimCount=__MaxDimCount;
	struct	PickupFlexAreaStruct_s	LDim[__MaxDimCount];
	int								LDimCount;
	struct	PickupFlexAreaStructPointer_s	YPointerDim[__MaxDimCount];

	struct	PickupFlexAreaStruct_s		*LDimPointer=LDim;
	struct	PickupFlexAreaStructPointer_s	*YPointer;
	
	struct	PickupFlexAreaStruct_s		*FPointerDim[__MaxDimCount];
	struct	PickupFlexAreaStruct_s		**FPointer=FPointerDim;
	PureFlexAreaList					*PureFlexAreaListDim[__MaxDimCount];
	PureFlexAreaList					**PureFlexAreaListPointer=PureFlexAreaListDim;
	int									MaxPureFlexAreaListPointerCount=__MaxDimCount;
	int									PureFlexAreaListPointerCount=0;
	
	if(YLen>=MaxDimCount){
		YPointer=new struct PickupFlexAreaStructPointer_s[YLen];
	}
	else{
		YPointer	=YPointerDim;
	}
	XLen=min(XLen,XByte*8);

	LDimCount=0;
	for(int y=0;y<YLen;y++){
		BYTE	*b=Bmp[y];
		YPointer[y].DimPoint=LDimCount;
		YPointer[y].Count=0;
		int		Offset=0;
		for(int x=0;x<XLen;x+=8,Offset++){
			if(b[Offset]==0){
				continue;
			}
			BYTE	Mask=0x80;
			for(int r=0;r<8;r++,Mask>>=1){
				if((b[Offset] & Mask)!=0){
					LDimPointer[LDimCount].AbsY		=y;
					LDimPointer[LDimCount].LeftX	=x+r;
					LDimPointer[LDimCount].Numb		=1;
					LDimPointer[LDimCount].Code		=-1;
					int x2=x;
					Mask>>=1;
					r++;
					for(;;){
						for(;r<8;r++,Mask>>=1){
							if((b[Offset] & Mask)==0){
								goto	FoundBitEnd;
							}
						}
						Mask=0x80;
						r=0;
						do{
							Offset++;
							x2+=8;
							if(x2>=XLen){
								goto	FoundBitEnd;
							}
						}while(b[Offset]==0xFF);
					}
FoundBitEnd:
					LDimPointer[LDimCount].Numb	=x2+r-LDimPointer[LDimCount].LeftX;
					x=x2;

					//_heapchk();

					LDimCount++;
					YPointer[y].Count++;
					if(LDimCount>=MaxDimCount){
						MaxDimCount=MaxDimCount*2;
						struct PickupFlexAreaStruct_s	*LDimPointer2=new struct PickupFlexAreaStruct_s[MaxDimCount];
						int	h;
						for(h=0;h<LDimCount;h++){
							LDimPointer2[h]=LDimPointer[h];
						}
						//_heapchk();

						//memcpy(LDimPointer2,LDimPointer,sizeof(LDimPointer[0])*LDimCount);
						if(LDimPointer!=LDim){
							delete	[]LDimPointer;
						}
						LDimPointer=LDimPointer2;
					}
					if(x>=XLen){
						break;
					}
				}
			}
		}
	}

	for(int y=0;y<YLen;y++){
		YPointer[y].DimPointer=&LDimPointer[YPointer[y].DimPoint];
	}

	if(LDimCount>=__MaxDimCount){
		FPointer	=new struct	PickupFlexAreaStruct_s*[LDimCount];
	}

	int	AreaCode=0;
	for(int i=0;i<LDimCount;i++){
		if(LDimPointer[i].Code==-1){
			struct	PickupFlexAreaRDim_s	PData;
			PData.LDim		=LDimPointer;
			PData.YLen		=YLen;
			PData.YPointer	=YPointer;
			PData.AreaCode	=AreaCode;
			PData.FPointer	=FPointer;
			PData.FPointerCount=0;
			PData.ReEntrantCount=0;
			RecursivePickupFlexArea(PData,&LDimPointer[i]);

			bool	RetMode;
			do{
				RetMode=false;
				for(int j=0;j<PData.FPointerCount;j++){
					if(RecursivePickupFlexArea(PData,PData.FPointer[j])==true){
						RetMode=true;
					}
				}
			}while(RetMode==true);

			if(PData.FPointerCount>0){
				struct FlexLine	*L=new struct FlexLine[PData.FPointerCount];
				for(int j=0;j<PData.FPointerCount;j++){
					L[j]._LeftX	=FPointer[j]->LeftX;
					L[j]._Numb	=FPointer[j]->Numb;
					L[j]._AbsY	=FPointer[j]->AbsY;
				}
				//_heapchk();

				PureFlexAreaList	*k=new PureFlexAreaList();
				k->SetFLineOnly(L,PData.FPointerCount);
				PureFlexAreaListPointer[PureFlexAreaListPointerCount]=k;
				PureFlexAreaListPointerCount++;
				if(PureFlexAreaListPointerCount>=MaxPureFlexAreaListPointerCount){
					MaxPureFlexAreaListPointerCount*=2;
					PureFlexAreaList	**PureFlexAreaListPointer2=new PureFlexAreaList*[MaxPureFlexAreaListPointerCount];
					int	h;
					for(h=0;h<PureFlexAreaListPointerCount;h++){
						PureFlexAreaListPointer2[h]=PureFlexAreaListPointer[h];
					}
					for(;h<MaxPureFlexAreaListPointerCount;h++){
						PureFlexAreaListPointer2[h]=NULL;
					}
					//memcpy(PureFlexAreaListPointer2,PureFlexAreaListPointer,sizeof(PureFlexAreaListPointer[0])*PureFlexAreaListPointerCount);
					if(PureFlexAreaListPointer!=PureFlexAreaListDim){
						delete	[]PureFlexAreaListPointer;
					}
					PureFlexAreaListPointer=PureFlexAreaListPointer2;
				}
			}
			AreaCode++;
			if(MaxAreaCount>=0 && AreaCode>=MaxAreaCount){
				break;
			}
		}
	}

	//if(Multithread==true && LDimCount>5000 && AreaCode>32){
	if(Multithread==true && LDimCount>500 && AreaCode>32){
		#pragma omp parallel
		{
			#pragma omp for schedule(dynamic)
			for(int i=0;i<PureFlexAreaListPointerCount;i++){
				PureFlexAreaListPointer[i]->Regulate();
			}
		}
	}
	else{
		for(int i=0;i<PureFlexAreaListPointerCount;i++){
			PureFlexAreaListPointer[i]->Regulate();
		}
	}

	for(int i=0;i<PureFlexAreaListPointerCount;i++){
		FPack.AppendList(PureFlexAreaListPointer[i]);
	}
	if(LDimPointer!=LDim){
		delete	[]LDimPointer;
	}
	if(YPointer!=YPointerDim){
		delete	[]YPointer;
	}
	if(FPointer!=FPointerDim){
		delete	[]FPointer;
	}
	if(PureFlexAreaListPointer!=PureFlexAreaListDim){
		delete	[]PureFlexAreaListPointer;
	}
	return true;
}

bool	PickupFlexArea_s(BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount,bool Multithread)
{
	if(YLen<40000)
		return PickupFlexAreaPartial_s(Bmp ,XByte ,XLen,YLen ,FPack ,MaxAreaCount,Multithread);
	bool	Ret=true;
	int	N=YLen/30000;
	BYTE	**tBmp=new BYTE *[60000];
	for(int i=0;i<N;i++){
		int	tYLen=30000;
		int	AddedY=i*30000;
		if(i==N-1)
			tYLen=YLen-AddedY;
		for(int n=0;n<tYLen;n++){
			int	y=AddedY+n;
			tBmp[n]=Bmp[y];
		}
		PureFlexAreaListContainer tFPack;
		if(PickupFlexAreaPartial_s(tBmp ,XByte ,XLen,tYLen ,tFPack ,MaxAreaCount,Multithread)==false)
			Ret=false;
		PureFlexAreaList *a;
		while((a=tFPack.GetFirst())!=NULL){
			tFPack.RemoveList(a);
			a->MoveToNoClip(0,AddedY);
			FPack.AppendList(a);
		}
	}
	delete[]tBmp;
	return Ret;
}

bool	PickupFlexAreaWhole_s(BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount,bool Multithread)
{
	return PickupFlexAreaPartial_s(Bmp ,XByte ,XLen,YLen ,FPack ,MaxAreaCount,Multithread);
}

bool	PickupFlexOneArea_s(BYTE **Bmp ,int XByte ,int XLen,int YLen 
						,int LocalX ,int LocalY
						,FlexArea &FArea)
{
	const	int	__MaxDimCount=10000;

	int		MaxDimCount=__MaxDimCount;
	struct	PickupFlexAreaStruct_s	LDim[__MaxDimCount];
	int								LDimCount;
	struct	PickupFlexAreaStructPointer_s	YPointerDim[__MaxDimCount];

	struct	PickupFlexAreaStruct_s		*LDimPointer=LDim;
	struct	PickupFlexAreaStructPointer_s	*YPointer;
	
	struct	PickupFlexAreaStruct_s		*FPointerDim[__MaxDimCount];
	struct	PickupFlexAreaStruct_s		**FPointer=FPointerDim;
	//PureFlexAreaList					*PureFlexAreaListDim[__MaxDimCount];
	
	if(YLen>=MaxDimCount){
		YPointer=new struct PickupFlexAreaStructPointer_s[YLen];
	}
	else{
		YPointer	=YPointerDim;
	}

	if(LocalX<0 || XLen<=LocalX || LocalY<0 || YLen<=LocalY)
		return false;


	LDimCount=0;
	for(int y=0;y<YLen;y++){
		BYTE	*b=Bmp[y];
		YPointer[y].DimPoint=LDimCount;
		YPointer[y].Count=0;
		int		Offset=0;
		for(int x=0;x<XLen;x+=8,Offset++){
			if(b[Offset]==0){
				continue;
			}
			BYTE	Mask=0x80;
			for(int r=0;r<8;r++,Mask>>=1){
				if((b[Offset] & Mask)!=0){
					LDimPointer[LDimCount].AbsY		=y;
					LDimPointer[LDimCount].LeftX	=x+r;
					LDimPointer[LDimCount].Numb		=1;
					LDimPointer[LDimCount].Code		=-1;
					int x2=x;
					Mask>>=1;
					r++;
					for(;;){
						for(;r<8;r++,Mask>>=1){
							if((b[Offset] & Mask)==0){
								goto	FoundBitEnd;
							}
						}
						Mask=0x80;
						r=0;
						do{
							Offset++;
							x2+=8;
							if(x2>=XLen){
								goto	FoundBitEnd;
							}
						}while(b[Offset]==0xFF);
					}
FoundBitEnd:
					LDimPointer[LDimCount].Numb	=x2+r-LDimPointer[LDimCount].LeftX;
					x=x2;

					LDimCount++;
					YPointer[y].Count++;
					if(LDimCount>=MaxDimCount){
						MaxDimCount=MaxDimCount*2;
						struct PickupFlexAreaStruct_s	*LDimPointer2=new struct PickupFlexAreaStruct_s[MaxDimCount];
						memcpy(LDimPointer2,LDimPointer,sizeof(LDimPointer[0])*LDimCount);
						if(LDimPointer!=LDim){
							delete	[]LDimPointer;
						}
						LDimPointer=LDimPointer2;
					}
					if(x>=XLen){
						break;
					}
				}
			}
		}
	}
	for(int y=0;y<YLen;y++){
		YPointer[y].DimPointer=&LDimPointer[YPointer[y].DimPoint];
	}

	if(LDimCount>=__MaxDimCount){
		FPointer	=new struct	PickupFlexAreaStruct_s*[LDimCount];
	}

	int	IndexI;
	for(IndexI=0;IndexI<LDimCount;IndexI++){
		if(LDimPointer[IndexI].AbsY==LocalY && LDimPointer[IndexI].LeftX<=LocalX && LocalX<=(LDimPointer[IndexI].LeftX+LDimPointer[IndexI].Numb)){
			break;
		}
	}
	if(IndexI>=LDimCount)
		return false;


	int	AreaCode=0;

	struct	PickupFlexAreaRDim_s	PData;
	PData.LDim		=LDimPointer;
	PData.YLen		=YLen;
	PData.YPointer	=YPointer;
	PData.AreaCode	=AreaCode;
	PData.FPointer	=FPointer;
	PData.FPointerCount=0;
	PData.ReEntrantCount=0;
	RecursivePickupFlexArea(PData,&LDimPointer[IndexI]);

	bool	RetMode;
	do{
		RetMode=false;
		for(int j=0;j<PData.FPointerCount;j++){
			if(RecursivePickupFlexArea(PData,PData.FPointer[j])==true){
				RetMode=true;
			}
		}
	}while(RetMode==true);

	struct FlexLine	*L=new struct FlexLine[PData.FPointerCount];
	int N=0;
	for(int j=0;j<PData.FPointerCount;j++){
		L[N]._LeftX	=FPointer[j]->LeftX;
		L[N]._Numb	=FPointer[j]->Numb;
		L[N]._AbsY	=FPointer[j]->AbsY;
		N++;
	}
	FArea.SetFLineOnly(L,N);
	FArea.Regulate();

	if(LDimPointer!=LDim){
		delete	[]LDimPointer;
	}
	if(YPointer!=YPointerDim){
		delete	[]YPointer;
	}
	if(FPointer!=FPointerDim){
		delete	[]FPointer;
	}

	return true;
}

bool	PickupFlexAreaFast(BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount)
{
	if(YLen<200){
		return PickupFlexArea(Bmp ,XByte ,XLen,YLen ,FPack ,MaxAreaCount);
	}
	int	N;
	#pragma omp parallel
	{
		N=omp_get_num_threads()*4;
	}
	if(N>100)
		N=100;
	int	YLenDiv=YLen/N;
	PureFlexAreaListContainer TmpFPack[100];
	PureFlexAreaListContainer TmpFPackTop[100];
	PureFlexAreaListContainer TmpFPackBottom[100];
	PureFlexAreaListContainer TmpFPackTopBottom[100];
	#pragma omp parallel
	{
		#pragma omp for schedule(dynamic)
		for(int i=0;i<N;i++){
			int	YTop=i*YLenDiv;
			PickupFlexArea(&Bmp[YTop] ,XByte ,XLen,YLenDiv ,TmpFPack[i] ,MaxAreaCount);
			for(PureFlexAreaList *g=TmpFPack[i].GetFirst();g!=NULL;g=g->GetNext()){
				g->MoveToNoClip(0,YTop);
			}
			int	YBottom=YTop+YLenDiv-2;
			YTop=i*YLenDiv+2;
			for(PureFlexAreaList *g=TmpFPack[i].GetFirst();g!=NULL;){
				PureFlexAreaList *GNext=g->GetNext();
				if(g->GetMinY()<=YTop){
					TmpFPack[i].RemoveList(g);
					if(g->GetMaxY()>=YBottom){
						TmpFPackTopBottom[i].AppendList(g);
					}
					else{
						TmpFPackTop[i].AppendList(g);
					}
				}
				else if(g->GetMaxY()>=YBottom){
					TmpFPack[i].RemoveList(g);
					TmpFPackBottom[i].AppendList(g);
				}
				g=GNext;
			}
		}
	}
	for(int i=0;i<N;i++){
		PureFlexAreaList *f;
		FPack.AddMove(TmpFPack[i]);

		while((f=TmpFPackBottom[i].GetFirst())!=NULL){
			TmpFPackBottom[i].RemoveList(f);
			for(int j=i+1;j<N;j++){
				int	YBottom=j*YLenDiv-2;
				if (f->GetMaxY()<YBottom){
					break;
				}
				for(PureFlexAreaList *g=TmpFPackTop[j].GetFirst();g!=NULL;){
					PureFlexAreaList *GNext=g->GetNext();
					if(f->CheckOverlap(g)==true){
						TmpFPackTop[j].RemoveList(g);
						*((FlexArea *)f)+=*((FlexArea *)g);
						delete	g;
					}
					g=GNext;
				}
				for(PureFlexAreaList *g=TmpFPackTopBottom[j].GetFirst();g!=NULL;){
					PureFlexAreaList *GNext=g->GetNext();
					if(f->CheckOverlap(g)==true){
						TmpFPackTopBottom[j].RemoveList(g);
						*((FlexArea *)f)+=*((FlexArea *)g);
						delete	g;
					}
					g=GNext;
				}
			}
			FPack.AppendList(f);
		}
		while((f=TmpFPackTopBottom[i].GetFirst())!=NULL){
			TmpFPackTopBottom[i].RemoveList(f);
			for(int j=i+1;j<N;j++){
				int	YBottom=j*YLenDiv-2;
				if (f->GetMaxY()<YBottom){
					break;
				}
				for(PureFlexAreaList *g=TmpFPackTop[j].GetFirst();g!=NULL;){
					PureFlexAreaList *GNext=g->GetNext();
					if(f->CheckOverlap(g)==true){
						TmpFPackTop[j].RemoveList(g);
						*((FlexArea *)f)+=*((FlexArea *)g);
						delete	g;
					}
					g=GNext;
				}
				for(PureFlexAreaList *g=TmpFPackTopBottom[j].GetFirst();g!=NULL;){
					PureFlexAreaList *GNext=g->GetNext();
					if(f->CheckOverlap(g)==true){
						TmpFPackTopBottom[j].RemoveList(g);
						*((FlexArea *)f)+=*((FlexArea *)g);
						delete	g;
					}
					g=GNext;
				}
			}
			FPack.AppendList(f);
		}
		FPack.AddMove(TmpFPackTop[i]);
	}
	return true;		
}