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


#include "XTypeDef.h"
#include "XImageProcess.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XDot.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include "swap.h"
#include <omp.h>
#include "XImageExpand.h"
#include "XGeneralFunc.h"

/*
	8ビット×2ビット矩形領域での計算
	開始座標は左上
*/
ShrinkingActionData::MaskInfo::MaskInfo(void)
{
	OffsetX		=0;
	MaskCount1	=0;
	MaskCount2	=0;
	MaskCount3	=0;
	AndMask1[0]	=0xFF;
	AndMask1[1]	=0xFF;
	AndMask3	=0xFF;
}
ShrinkingActionData::MaskInfo::~MaskInfo(void)
{
	OffsetX		=0;
	MaskCount1	=0;
	MaskCount2	=0;
	MaskCount3	=0;
	AndMask1[0]	=0;
	AndMask1[1]	=0;
	AndMask3	=0;
}
bool	ShrinkingActionData::MaskInfo::Save(QIODevice *f)
{
	BYTE	D[7];
	D[0]=(BYTE)OffsetX;
	D[1]=MaskCount1;
	D[2]=MaskCount2;
	D[3]=MaskCount3;
	D[4]=AndMask1[0];
	D[5]=AndMask1[1];
	D[6]=AndMask3;

	if(f->write((const char *)D,7)!=7)
		return false;
	return true;
}

bool	ShrinkingActionData::MaskInfo::Load(QIODevice *f)
{
	BYTE	D[7];

	if(f->read((char *)D,7)!=7)
		return false;
	OffsetX		=(int8)D[0];
	MaskCount1	=D[1];
	MaskCount2	=D[2];
	MaskCount3	=D[3];
	AndMask1[0]	=D[4];
	AndMask1[1]	=D[5];
	AndMask3	=D[6];

	return true;
}

ShrinkingActionData::ShrinkingActionData(void)
{
	Mask=NULL;
	MaskNumb=0;
}
ShrinkingActionData::~ShrinkingActionData(void)
{
	if(Mask!=NULL)
		delete	[]Mask;
	Mask=NULL;
	MaskNumb=0;
}
bool	ShrinkingActionData::Save(QIODevice *f)
{
	if(::Save(f,MaskNumb)==false)
		return false;
	for(int i=0;i<MaskNumb;i++){
		if(Mask[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	ShrinkingActionData::Load(QIODevice *f)
{
	if(::Load(f,MaskNumb)==false)
		return false;
	if(Mask!=NULL)
		delete	[]Mask;
	Mask=NULL;
	if(MaskNumb!=0){
		Mask=new struct MaskInfo[MaskNumb];
		for(int i=0;i<MaskNumb;i++){
			if(Mask[i].Load(f)==false)
				return false;
		}
	}
	return true;
}

ShrinkingPack::ShrinkingPack(void)
{
	Len=0;
	BitNumb=16;
	MaskData=NULL;
}
ShrinkingPack::~ShrinkingPack(void)
{
	if(MaskData!=NULL)
		delete	[]MaskData;
	MaskData=NULL;
}

static	void	BuildMaskInfoFromBuff(BYTE **Buff, int X1, int XByte, int YLen, struct ShrinkingActionData &Dst)
{
	int	LastNonZeroY=-1;
	for(int y=YLen-1;y>=0;y--){
		for(int x=0;x<XByte;x++){
			if(Buff[y][x]!=0){
				LastNonZeroY=y;
				break;
			}
		}
		if(LastNonZeroY>=0){
			break;
		}
	}
	if(LastNonZeroY<0){
		Dst.Mask=NULL;
		Dst.MaskNumb=0;
		return;
	}

	int	ValidYLen=LastNonZeroY+1;
	Dst.Mask=new struct ShrinkingActionData::MaskInfo[ValidYLen];
	Dst.MaskNumb=(unsigned short)ValidYLen;

	for(int y=0;y<ValidYLen;y++){
		int	xa;
		for(xa=0;xa<XByte;xa++){
			if(Buff[y][xa]!=0){
				break;
			}
		}
		int	xb;
		for(xb=XByte-1;xb>=0;xb--){
			if(Buff[y][xb]!=0){
				break;
			}
		}
		ShrinkingActionData::MaskInfo	&Info=Dst.Mask[y];
		if(xa>xb){
			Info.OffsetX	=0;
			Info.MaskCount1	=0;
			Info.MaskCount2	=0;
			Info.MaskCount3	=0;
			Info.AndMask1[0]=0xFF;
			Info.AndMask1[1]=0xFF;
			Info.AndMask3	=0xFF;
			continue;
		}

		int		C1=-1,C2=-1;
		bool	Found=false;
		for(int t=xa;t<=xb;t++){
			if(Buff[y][t]==0xFF){
				C1=t;
				Found=true;
				break;
			}
		}
		if(Found==true){
			for(int t=C1;t<=xb;t++){
				if(Buff[y][t]!=0xFF){
					break;
				}
				C2=t;
			}
		}

		Info.OffsetX=(int8)(xa+X1);
		if(Found==false){
			int	TotalCount=xb-xa+1;
			Info.MaskCount2=0;
			if(TotalCount==1){
				Info.MaskCount1	=1;
				Info.MaskCount3	=0;
				Info.AndMask1[0]=(BYTE)(~Buff[y][xa]);
				Info.AndMask1[1]=0xFF;
				Info.AndMask3	=0xFF;
			}
			else if(TotalCount==2){
				Info.MaskCount1	=1;
				Info.MaskCount3	=1;
				Info.AndMask1[0]=(BYTE)(~Buff[y][xa]);
				Info.AndMask1[1]=0xFF;
				Info.AndMask3	=(BYTE)(~Buff[y][xa+1]);
			}
			else{
				// TotalCount == 3
				Info.MaskCount1	=2;
				Info.MaskCount3	=1;
				Info.AndMask1[0]=(BYTE)(~Buff[y][xa]);
				Info.AndMask1[1]=(BYTE)(~Buff[y][xa+1]);
				Info.AndMask3	=(BYTE)(~Buff[y][xa+2]);
			}
		}
		else{
			int	Count1=C1-xa;
			if(Count1>2){
				Count1=2;
			}
			Info.MaskCount1=(BYTE)Count1;
			Info.AndMask1[0]=0xFF;
			Info.AndMask1[1]=0xFF;
			for(int t=0;t<Count1;t++){
				Info.AndMask1[t]=(BYTE)(~Buff[y][xa+t]);
			}
			Info.MaskCount2=(BYTE)(C2-C1+1);
			int	Count3=xb-C2;
			if(Count3>1){
				Count3=1;
			}
			Info.MaskCount3=(BYTE)Count3;
			if(Count3>0){
				Info.AndMask3=(BYTE)(~Buff[y][C2+1]);
			}
			else{
				Info.AndMask3=0xFF;
			}
		}
	}
}

void	ShrinkingPackInternalFunc16(int i ,int Len ,struct	ShrinkingActionData *MaskData)
{
	int	X1=(-((Len+7)>>3));
	int	Y1=-Len;
	int	X2=((Len+7)>>3);
	int	Y2=Len+1;

	int	XByte=(X2-X1+1);
	int	YLen=Y2-Y1+1;
	int	AddedXBit=((Len+7)>>3)<<3;

	BYTE	BuffTmp[16384];
	BYTE    **Buff=MakeMatrixBuff(XByte,YLen,BuffTmp,16384);
	MatrixBuffClear	(Buff ,0 ,XByte,YLen);

	BYTE	M1=(BYTE)(i & 0xFF);
	BYTE	M2=(BYTE)((i>>8) & 0xFF);
	for(int x=0;x<8;x++){
		for(int y=0;y<2;y++){
			if((y==0 && ((M1&(0x80>>x))==0))
			|| (y==1 && ((M2&(0x80>>x))==0))){
				for(int L=0;L<=Len;L++){
					int	x1=-(int)sqrt((double)(Len*Len-L*L));
					int	x2=-x1;

					BYTE	*B1=Buff[Len+y-L];
					for(int t=x1;t<=x2;t++){
						SetBmpBitOnY1(B1,x+t+AddedXBit);
					}
					BYTE	*B2=Buff[Len+y+L];
					for(int t=x1;t<=x2;t++){
						SetBmpBitOnY1(B2,x+t+AddedXBit);
					}
				}
			}
		}
	}
	BuildMaskInfoFromBuff(Buff, X1, XByte, YLen, MaskData[i]);
	DeleteMatrixBuff(Buff,BuffTmp,YLen);
}

void	ShrinkingPackInternalFunc8(int i ,int Len ,struct	ShrinkingActionData *MaskData)
{
	int	X1=(-((Len+7)>>3));
	int	Y1=-Len;
	int	X2=((Len+7)>>3);
	int	Y2=Len;

	int	XByte=(X2-X1+1);
	int	YLen=Y2-Y1+1;
	int	AddedXBit=((Len+7)>>3)<<3;

	BYTE	BuffTmp[16384];
	BYTE    **Buff=MakeMatrixBuff(XByte,YLen,BuffTmp,16384);
	MatrixBuffClear	(Buff ,0 ,XByte,YLen);

	BYTE	M1=(BYTE)(i & 0xFF);
	for(int x=0;x<8;x++){
		if((M1&(0x80>>x))==0){
			for(int L=0;L<=Len;L++){
				int	x1=-(int)sqrt((double)(Len*Len-L*L));
				int	x2=-x1;

				BYTE	*B1=Buff[Len-L];
				for(int t=x1;t<=x2;t++){
					SetBmpBitOnY1(B1,x+t+AddedXBit);
				}
				BYTE	*B2=Buff[Len+L];
				for(int t=x1;t<=x2;t++){
					SetBmpBitOnY1(B2,x+t+AddedXBit);
				}
			}
		}
	}
	BuildMaskInfoFromBuff(Buff, X1, XByte, YLen, MaskData[i]);
	DeleteMatrixBuff(Buff,BuffTmp,YLen);
}

void	ShrinkingPackInternalFunc4(int i ,int Len ,struct	ShrinkingActionData *MaskData)
{
	int	X1=(-((Len+7)>>3));
	int	Y1=-Len;
	int	X2=((Len+7)>>3);
	int	Y2=Len;

	int	XByte=(X2-X1+1);
	int	YLen=Y2-Y1+1;
	int	AddedXBit=((Len+7)>>3)<<3;

	BYTE	BuffTmp[16384];
	BYTE    **Buff=MakeMatrixBuff(XByte,YLen,BuffTmp,16384);
	MatrixBuffClear	(Buff ,0 ,XByte,YLen);

	if(i<16){
		BYTE	M1=(BYTE)(i<<4);
		for(int x=0;x<4;x++){
			if((M1&(0x80>>x))==0){
				for(int L=0;L<=Len;L++){
					int	x1=-(int)sqrt((double)(Len*Len-L*L));
					int	x2=-x1;

					BYTE	*B1=Buff[Len-L];
					for(int t=x1;t<=x2;t++){
						SetBmpBitOnY1(B1,x+t+AddedXBit);
					}
					BYTE	*B2=Buff[Len+L];
					for(int t=x1;t<=x2;t++){
						SetBmpBitOnY1(B2,x+t+AddedXBit);
					}
				}
			}
		}
	}
	else{
		BYTE	M1=(BYTE)(i&0xF);
		for(int x=4;x<8;x++){
			if((M1&(0x80>>x))==0){
				for(int L=0;L<=Len;L++){
					int	x1=-(int)sqrt((double)(Len*Len-L*L));
					int	x2=-x1;

					BYTE	*B1=Buff[Len-L];
					for(int t=x1;t<=x2;t++){
						SetBmpBitOnY1(B1,x+t+AddedXBit);
					}
					BYTE	*B2=Buff[Len+L];
					for(int t=x1;t<=x2;t++){
						SetBmpBitOnY1(B2,x+t+AddedXBit);
					}
				}
			}
		}
	}

	BuildMaskInfoFromBuff(Buff, X1, XByte, YLen, MaskData[i]);
	DeleteMatrixBuff(Buff,BuffTmp,YLen);
}

void	ShrinkingPackInternalFunc2(int i ,int Len ,struct	ShrinkingActionData *MaskData)
{
	int	X1=(-((Len+7)>>3));
	int	Y1=-Len;
	int	X2=((Len+7)>>3);
	int	Y2=Len;

	int	XByte=(X2-X1+1);
	int	YLen=Y2-Y1+1;
	int	AddedXBit=((Len+7)>>3)<<3;

	BYTE	BuffTmp[16384];
	BYTE    **Buff=MakeMatrixBuff(XByte,YLen,BuffTmp,16384);
	MatrixBuffClear	(Buff ,0 ,XByte,YLen);

	int	SNumb=i/4;
	int	LeftBit=SNumb*2;
	BYTE	M1=(BYTE)((i&0x03)<<(6-LeftBit));
	for(int x=LeftBit;x<(LeftBit+2);x++){
		if((M1&(0x80>>x))==0){
			for(int L=0;L<=Len;L++){
				int	x1=-(int)sqrt((double)(Len*Len-L*L));
				int	x2=-x1;
				BYTE	*B1=Buff[Len-L];
				for(int t=x1;t<=x2;t++){
					SetBmpBitOnY1(B1,x+t+AddedXBit);
				}
				BYTE	*B2=Buff[Len+L];
				for(int t=x1;t<=x2;t++){
					SetBmpBitOnY1(B2,x+t+AddedXBit);
				}
			}
		}
	}

	BuildMaskInfoFromBuff(Buff, X1, XByte, YLen, MaskData[i]);
	DeleteMatrixBuff(Buff,BuffTmp,YLen);
}

void	ShrinkingPackInternalFunc1(int i ,int Len ,struct	ShrinkingActionData *MaskData)
{
	int	X1=(-((Len+7)>>3));
	int	Y1=-Len;
	int	X2=((Len+7)>>3);
	int	Y2=Len;

	int	XByte=(X2-X1+1);
	int	YLen=Y2-Y1+1;
	int	AddedXBit=((Len+7)>>3)<<3;

	BYTE	BuffTmp[16384];
	BYTE    **Buff=MakeMatrixBuff(XByte,YLen,BuffTmp,16384);
	MatrixBuffClear	(Buff ,0 ,XByte,YLen);

	int	LeftBit=i;
	int	x=LeftBit;
	for(int L=0;L<=Len;L++){
		int	x1=-(int)sqrt((double)(Len*Len-L*L));
		int	x2=-x1;
		BYTE	*B1=Buff[Len-L];
		for(int t=x1;t<=x2;t++){
			SetBmpBitOnY1(B1,x+t+AddedXBit);
		}
		BYTE	*B2=Buff[Len+L];
		for(int t=x1;t<=x2;t++){
			SetBmpBitOnY1(B2,x+t+AddedXBit);
		}
	}

	BuildMaskInfoFromBuff(Buff, X1, XByte, YLen, MaskData[i]);
	DeleteMatrixBuff(Buff,BuffTmp,YLen);
}

void	ShrinkingPack::Initial(int len)
{
	Len=len;
	if(MaskData!=NULL){
		delete	[]MaskData;
		MaskData=NULL;
	}
	if(Len<=0){
		BitNumb=0;
		return;
	}

	int	N;
	if(Len<60){
		N=65536;
		BitNumb=16;
	}
	else if(Len<150){
		N=256;
		BitNumb=8;
	}
	else if(Len<200){
		N=32;
		BitNumb=4;
	}
	else if(Len<250){
		N=16;
		BitNumb=2;
	}
	else{
		N=8;
		BitNumb=1;
	}

	MaskData=new struct	ShrinkingActionData[N];

	if(BitNumb==16){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<N;i++){
				ShrinkingPackInternalFunc16(i ,Len ,MaskData);
			}
		}
	}
	else if(BitNumb==8){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<N;i++){
				ShrinkingPackInternalFunc8(i ,Len ,MaskData);
			}
		}
	}
	else if(BitNumb==4){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<N;i++){
				ShrinkingPackInternalFunc4(i ,Len ,MaskData);
			}
		}
	}
	else if(BitNumb==2){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<N;i++){
				ShrinkingPackInternalFunc2(i ,Len ,MaskData);
			}
		}
	}
	else if(BitNumb==1){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<N;i++){
				ShrinkingPackInternalFunc1(i ,Len ,MaskData);
			}
		}
	}
}
	
bool	ShrinkingPack::Save(QIODevice *f)
{
	if(::Save(f,Len)==false)
		return false;
	if(::Save(f,BitNumb)==false)
		return false;
	int32	N;
	if(MaskData!=NULL){
		if(BitNumb==16)
			N=65536;
		else if(BitNumb==8)
			N=256;
		else if(BitNumb==4)
			N=32;
		else if(BitNumb==2)
			N=16;
		else if(BitNumb==1)
			N=8;
		else 
			N=0;
	}
	else
		N=0;
	if(::Save(f,N)==false)
		return false;

	for(int i=0;i<N;i++){
		if(MaskData[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	ShrinkingPack::Load(QIODevice *f)
{
	if(::Load(f,Len)==false)
		return false;
	if(::Load(f,BitNumb)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	if(MaskData!=NULL){
		delete	[]MaskData;
		MaskData=NULL;
	}
	if(N<=0){
		MaskData=NULL;
	}
	else{
		MaskData=new struct	ShrinkingActionData[N];
		for(int i=0;i<N;i++){
			if(MaskData[i].Load(f)==false)
				return false;
		}
	}
	return true;
}
ShrinkingPackContainer::ShrinkingPackContainer(void)
{
	DimNumb=100;
	Dim=new ShrinkingPack*[DimNumb];
	for(int i=0;i<DimNumb;i++){
		Dim[i]=NULL;
	}
}
ShrinkingPackContainer::~ShrinkingPackContainer(void)
{
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
	DimNumb=0;
}
ShrinkingPack	*ShrinkingPackContainer::Create(void)
{
	return new ShrinkingPack;
}
void	ShrinkingPackContainer::AppendListItem(ShrinkingPack *item)
{
	if(item!=NULL && item->Len>=0){
		if(item->Len<DimNumb){
			Dim[item->Len]=item;
		}
		else{
			int	NewLen=max(item->Len+1, DimNumb*2);
			ShrinkingPack	**DimSub=new ShrinkingPack*[NewLen];
			for(int i=0;i<NewLen;i++){
				DimSub[i]=NULL;
			}
			for(int i=0;i<DimNumb;i++){
				DimSub[i]=Dim[i];
			}
			DimSub[item->Len]=item;
			delete	[]Dim;
			Dim=DimSub;
			DimNumb=NewLen;
		}
	}
	NPListPackSaveLoad<ShrinkingPack>::AppendListItem(item);
}
void	ShrinkingPackContainer::Clear(void)
{
	RemoveAll();
	for(int i=0;i<DimNumb;i++){
		Dim[i]=NULL;
	}
}
bool	ShrinkingPackContainer::IsLoaded(int Numb)
{
	if(0<=Numb && Numb<DimNumb && Dim[Numb]!=NULL){
		return true;
	}
	return false;
}
ShrinkingPack	*ShrinkingPackContainer::GetPack(int numb)
{
	if(numb<=0)
		return NULL;
	if(numb<DimNumb && Dim[numb]!=NULL){
		return Dim[numb];
	}
	ShrinkingPack	*s=new ShrinkingPack;
	s->Initial(numb);
	AppendListItem(s);
	return Dim[numb];
}
bool   ShrinkingPackContainer::ThinAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,FlexArea *ForceZone
				,bool EnableThread)
{
	if(Numb<=0){
		return true;
	}
	ShrinkingPack	*P=GetPack(Numb);
	if(P==NULL){
		return false;
	}
	::ThinAreaN(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,*P
				,ForceZone
				,EnableThread);
	return true;
}
bool    ShrinkingPackContainer::FatAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,FlexArea *ForceZone
				,bool EnableThread)
{
	if(Numb<=0){
		return true;
	}
	ShrinkingPack	*P=GetPack(Numb);
	if(P==NULL){
		return false;
	}
	::FatAreaN(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,*P
				,ForceZone
				,EnableThread);
	return true;
}

bool	 ShrinkingPackContainer::SaveDefault(const QString &FileName)
{
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==false)
		return false;
	return Save(&File);
}

bool	 ShrinkingPackContainer::LoadDefault(const QString &FileName)
{
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==false)
		return false;
	return Load(&File);
}

//====================================================================
static	void    ThinAreaN16(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread);
static	void    ThinAreaN8(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread);
static	void    ThinAreaN4(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread);
static	void    ThinAreaN2(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread);
static	void    ThinAreaN1(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread);

static	void	FatAreaN16(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread);
static	void	FatAreaN8(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread);
static	void	FatAreaN4(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread);
static	void	FatAreaN2(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread);
static	void	FatAreaN1(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread);

void    ThinAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	if(Numb<=0 || xbyte<=0 || YLenDot<=0){
		return;
	}
	if(Numb==1){
		ThinArea(bmpdata
				,bitoperation
				,xbyte ,YLenDot ,ForceZone
				,EnableThread);
		return;
	}
	if(Numb==2){
		ThinAreaN(bmpdata
				,bitoperation
				,xbyte ,YLenDot
				,2
				,ForceZone
				,EnableThread);
		return;
	}

	bool	Allocbitoperation=false;
	if(bitoperation==NULL){
		bitoperation=MakeMatrixBuff(xbyte,YLenDot);
		Allocbitoperation=true;
	}

	MatrixBuffCopy(bitoperation				,xbyte,YLenDot
                  ,(const BYTE **)bmpdata	,xbyte,YLenDot);

	if(PTable.BitNumb==16){
		ThinAreaN16(bmpdata
					,bitoperation
					,xbyte ,YLenDot 
					,Numb
					,PTable
					,ForceZone
					,EnableThread);
	}
	else if(PTable.BitNumb==8){
		ThinAreaN8(bmpdata
					,bitoperation
					,xbyte ,YLenDot 
					,Numb
					,PTable
					,ForceZone
					,EnableThread);
	}
	else if(PTable.BitNumb==4){
		ThinAreaN4(bmpdata
					,bitoperation
					,xbyte ,YLenDot 
					,Numb
					,PTable
					,ForceZone
					,EnableThread);
	}
	else if(PTable.BitNumb==2){
		ThinAreaN2(bmpdata
					,bitoperation
					,xbyte ,YLenDot 
					,Numb
					,PTable
					,ForceZone
					,EnableThread);
	}
	else if(PTable.BitNumb==1){
		ThinAreaN1(bmpdata
					,bitoperation
					,xbyte ,YLenDot 
					,Numb
					,PTable
					,ForceZone
					,EnableThread);
	}

	if(Allocbitoperation==true){
		DeleteMatrixBuff(bitoperation,YLenDot);
		bitoperation=NULL;
	}
}

inline	int	ForAnd(int Count, BYTE *d ,BYTE *s,int XByte, int X)
{
	int	Start=0;
	if(X<0){
		Start=-X;
		Count-=Start;
		X=0;
	}
	if(X>=XByte || Count<=0){
		return X;
	}
	if(X+Count>XByte){
		Count=XByte-X;
	}
	for(int i=0;i<Count;i++){
		d[X+i] &= s[Start+i];
	}
	return X+Count;
}


inline	int	For0(int Count, BYTE *d ,int XByte, int X)
{
	if(X<0){
		Count+=X;
		X=0;
	}
	if(X>=XByte || Count<=0){
		return X;
	}
	if(X+Count>XByte){
		Count=XByte-X;
	}
	memset(&d[X],0,Count);
	return X+Count;
}

static inline void	ApplyThinMaskFast(BYTE **bmpdata, int baseY, int xb, const ShrinkingActionData &M)
{
	const ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
	for(int i=0;i<M.MaskNumb;i++,MInfo++){
		int	Counter1=MInfo->MaskCount1;
		int	Counter2=MInfo->MaskCount2;
		int	Counter3=MInfo->MaskCount3;
		if((Counter1 | Counter2 | Counter3)==0){
			continue;
		}
		BYTE	*d=bmpdata[baseY+i];
		int		X=xb+(int)MInfo->OffsetX;
		for(int t=0;t<Counter1;t++){
			d[X] &= MInfo->AndMask1[t];
			X++;
		}
		if(Counter2>0){
			memset(&d[X],0,Counter2);
			X+=Counter2;
		}
		if(Counter3>0){
			d[X] &= MInfo->AndMask3;
		}
	}
}

static inline void	ApplyThinMaskSafe(BYTE **bmpdata, int xbyte, int YLenDot, int baseY, int xb, const ShrinkingActionData &M)
{
	const ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
	for(int i=0;i<M.MaskNumb;i++,MInfo++){
		int	Y=baseY+i;
		if(Y<0){
			continue;
		}
		if(Y>=YLenDot){
			break;
		}
		int	Counter1=MInfo->MaskCount1;
		int	Counter2=MInfo->MaskCount2;
		int	Counter3=MInfo->MaskCount3;
		if((Counter1 | Counter2 | Counter3)==0){
			continue;
		}
		BYTE	*d=bmpdata[Y];
		int		X=xb+(int)MInfo->OffsetX;
		for(int t=0;t<Counter1;t++){
			if(0<=X && X<xbyte){
				d[X] &= MInfo->AndMask1[t];
			}
			X++;
		}
		if(Counter2>0){
			int	XStart=(X<0)?0:X;
			int	XEnd  =((X+Counter2)>xbyte)?xbyte:(X+Counter2);
			if(XStart<XEnd){
				memset(&d[XStart],0,XEnd-XStart);
			}
			X+=Counter2;
		}
		if(Counter3>0){
			if(0<=X && X<xbyte){
				d[X] &= MInfo->AndMask3;
			}
		}
	}
}

static inline void	ApplyFatMaskFast(BYTE **bmpdata, int baseY, int xb, const ShrinkingActionData &M)
{
	const ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
	for(int i=0;i<M.MaskNumb;i++,MInfo++){
		int	Counter1=MInfo->MaskCount1;
		int	Counter2=MInfo->MaskCount2;
		int	Counter3=MInfo->MaskCount3;
		if((Counter1 | Counter2 | Counter3)==0){
			continue;
		}
		BYTE	*d=bmpdata[baseY+i];
		int		X=xb+(int)MInfo->OffsetX;
		for(int t=0;t<Counter1;t++){
			d[X] |= (BYTE)(~MInfo->AndMask1[t]);
			X++;
		}
		if(Counter2>0){
			memset(&d[X],0xFF,Counter2);
			X+=Counter2;
		}
		if(Counter3>0){
			d[X] |= (BYTE)(~MInfo->AndMask3);
		}
	}
}

static inline void	ApplyFatMaskSafe(BYTE **bmpdata, int xbyte, int YLenDot, int baseY, int xb, const ShrinkingActionData &M)
{
	const ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
	for(int i=0;i<M.MaskNumb;i++,MInfo++){
		int	Y=baseY+i;
		if(Y<0){
			continue;
		}
		if(Y>=YLenDot){
			break;
		}
		int	Counter1=MInfo->MaskCount1;
		int	Counter2=MInfo->MaskCount2;
		int	Counter3=MInfo->MaskCount3;
		if((Counter1 | Counter2 | Counter3)==0){
			continue;
		}
		BYTE	*d=bmpdata[Y];
		int		X=xb+(int)MInfo->OffsetX;
		for(int t=0;t<Counter1;t++){
			if(0<=X && X<xbyte){
				d[X] |= (BYTE)(~MInfo->AndMask1[t]);
			}
			X++;
		}
		if(Counter2>0){
			int	XStart=(X<0)?0:X;
			int	XEnd  =((X+Counter2)>xbyte)?xbyte:(X+Counter2);
			if(XStart<XEnd){
				memset(&d[XStart],0xFF,XEnd-XStart);
			}
			X+=Counter2;
		}
		if(Counter3>0){
			if(0<=X && X<xbyte){
				d[X] |= (BYTE)(~MInfo->AndMask3);
			}
		}
	}
}

static	void    ThinAreaN16RowRange(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,int rStart, int rEnd
				,int SafeStartR, int SafeEndR
				,int MerginByte)
{
	int	LeftEndX	=min(MerginByte, xbyte);
	int	RightStartX	=max(MerginByte, xbyte-MerginByte);

	for(int r=rStart;r<rEnd;r++){
		int	y=r*2;
		if(SafeStartR<=r && r<SafeEndR){
			const BYTE	*s0=bitoperation[y];
			const BYTE	*s1=bitoperation[y+1];
			int			baseY=y-Numb;

			for(int xb=0;xb<LeftEndX;xb++){
				unsigned short	Index=(unsigned short)s0[xb] | (((unsigned short)s1[xb])<<8);
				if(Index==0xFFFFu)
					continue;
				ApplyThinMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[Index]);
			}
			for(int xb=MerginByte;xb<RightStartX;xb++){
				unsigned short	Index=(unsigned short)s0[xb] | (((unsigned short)s1[xb])<<8);
				if(Index==0xFFFFu)
					continue;
				ApplyThinMaskFast(bmpdata, baseY, xb, PTable.MaskData[Index]);
			}
			for(int xb=RightStartX;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)s0[xb] | (((unsigned short)s1[xb])<<8);
				if(Index==0xFFFFu)
					continue;
				ApplyThinMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[Index]);
			}
		}
		else{
			const BYTE	*s0=bitoperation[y];
			const BYTE	*s1=(y+1<YLenDot)?bitoperation[y+1]:NULL;
			int			baseY=y-Numb;

			for(int xb=0;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)s0[xb];
				if(s1!=NULL)
					Index |= (((unsigned short)s1[xb])<<8);
				else
					Index |= 0xFF00u;
				if(Index==0xFFFFu)
					continue;
				ApplyThinMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[Index]);
			}
		}
	}
}

static	void    ThinAreaN16(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	int	MerginByte=(Numb+7)>>3;
	int	TotalR=(YLenDot+1)/2;
	int	SafeStartR=min(TotalR, (Numb+1)/2);
	int	SafeEndR  =max(SafeStartR, min(TotalR, (YLenDot-Numb-1)/2));

	int	BandR=max(Numb+2, 16);
	int	BandCount=(TotalR+BandR-1)/BandR;

	if(BandCount<4 || EnableThread==false){
		ThinAreaN16RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
							,0, TotalR, SafeStartR, SafeEndR, MerginByte);
	}
	else{
		// 2-pass striped parallelization to guarantee zero write-overlap between threads
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int b=0;b<BandCount;b+=2){
				int	rStart=b*BandR;
				int	rEnd  =min(TotalR, rStart+BandR);
				ThinAreaN16RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
									,rStart, rEnd, SafeStartR, SafeEndR, MerginByte);
			}
			#pragma omp for schedule(static)
			for(int b=1;b<BandCount;b+=2){
				int	rStart=b*BandR;
				int	rEnd  =min(TotalR, rStart+BandR);
				ThinAreaN16RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
									,rStart, rEnd, SafeStartR, SafeEndR, MerginByte);
			}
		}
	}
}

static	void    ThinAreaN8RowRange(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,int yStart, int yEnd
				,int SafeStartY, int SafeEndY
				,int MerginByte)
{
	int	LeftEndX	=min(MerginByte, xbyte);
	int	RightStartX	=max(MerginByte, xbyte-MerginByte);

	for(int y=yStart;y<yEnd;y++){
		const BYTE	*s0=bitoperation[y];
		int			baseY=y-Numb;
		if(SafeStartY<=y && y<SafeEndY){
			for(int xb=0;xb<LeftEndX;xb++){
				unsigned short	Index=(unsigned short)s0[xb];
				if(Index==0xFFu)
					continue;
				ApplyThinMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[Index]);
			}
			for(int xb=MerginByte;xb<RightStartX;xb++){
				unsigned short	Index=(unsigned short)s0[xb];
				if(Index==0xFFu)
					continue;
				ApplyThinMaskFast(bmpdata, baseY, xb, PTable.MaskData[Index]);
			}
			for(int xb=RightStartX;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)s0[xb];
				if(Index==0xFFu)
					continue;
				ApplyThinMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[Index]);
			}
		}
		else{
			for(int xb=0;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)s0[xb];
				if(Index==0xFFu)
					continue;
				ApplyThinMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[Index]);
			}
		}
	}
}

static	void    ThinAreaN8(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	int	MerginByte=(Numb+7)>>3;
	int	SafeStartY=min(YLenDot, Numb);
	int	SafeEndY  =max(SafeStartY, min(YLenDot, YLenDot-Numb));

	int	BandY=max(2*Numb+2, 32);
	int	BandCount=(YLenDot+BandY-1)/BandY;

	if(BandCount<4 || EnableThread==false){
		ThinAreaN8RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
							,0, YLenDot, SafeStartY, SafeEndY, MerginByte);
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int b=0;b<BandCount;b+=2){
				int	yStart=b*BandY;
				int	yEnd  =min(YLenDot, yStart+BandY);
				ThinAreaN8RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
									,yStart, yEnd, SafeStartY, SafeEndY, MerginByte);
			}
			#pragma omp for schedule(static)
			for(int b=1;b<BandCount;b+=2){
				int	yStart=b*BandY;
				int	yEnd  =min(YLenDot, yStart+BandY);
				ThinAreaN8RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
									,yStart, yEnd, SafeStartY, SafeEndY, MerginByte);
			}
		}
	}
}

static	void    ThinAreaN4(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	::ThinAreaN(bmpdata, bitoperation, xbyte, YLenDot, Numb, ForceZone, EnableThread);
}
static	void    ThinAreaN2(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	::ThinAreaN(bmpdata, bitoperation, xbyte, YLenDot, Numb, ForceZone, EnableThread);
}
static	void    ThinAreaN1(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	::ThinAreaN(bmpdata, bitoperation, xbyte, YLenDot, Numb, ForceZone, EnableThread);
}

void    FatAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	if(Numb<=0 || xbyte<=0 || YLenDot<=0){
		return;
	}
	if(Numb==1){
		FatArea(bmpdata
				,bitoperation
				,xbyte ,YLenDot ,ForceZone
				,EnableThread);
		return;
	}
	if(Numb==2){
		FatAreaN(bmpdata
				,bitoperation
				,xbyte ,YLenDot
				,2
				,ForceZone
				,EnableThread);
		return;
	}

	bool	Allocbitoperation=false;
	if(bitoperation==NULL){
		bitoperation=MakeMatrixBuff(xbyte,YLenDot);
		Allocbitoperation=true;
	}

	MatrixBuffCopy(bitoperation				,xbyte,YLenDot
                  ,(const BYTE **)bmpdata	,xbyte,YLenDot);

	if(PTable.BitNumb==16){
		FatAreaN16(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,PTable
				,ForceZone
				,EnableThread);
	}
	else if(PTable.BitNumb==8){
		FatAreaN8(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,PTable
				,ForceZone
				,EnableThread);
	}
	else if(PTable.BitNumb==4){
		FatAreaN4(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,PTable
				,ForceZone
				,EnableThread);
	}
	else if(PTable.BitNumb==2){
		FatAreaN2(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,PTable
				,ForceZone
				,EnableThread);
	}
	else if(PTable.BitNumb==1){
		FatAreaN1(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,PTable
				,ForceZone
				,EnableThread);
	}
	if(Allocbitoperation==true){
		DeleteMatrixBuff(bitoperation,YLenDot);
		bitoperation=NULL;
	}
}

static	void	FatAreaN16RowRange(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,int rStart, int rEnd
				,int SafeStartR, int SafeEndR
				,int MerginByte)
{
	int	LeftEndX	=min(MerginByte, xbyte);
	int	RightStartX	=max(MerginByte, xbyte-MerginByte);

	for(int r=rStart;r<rEnd;r++){
		int	y=r*2;
		if(SafeStartR<=r && r<SafeEndR){
			const BYTE	*s0=bitoperation[y];
			const BYTE	*s1=bitoperation[y+1];
			int			baseY=y-Numb;

			for(int xb=0;xb<LeftEndX;xb++){
				unsigned short	Index=(unsigned short)s0[xb] | (((unsigned short)s1[xb])<<8);
				if(Index==0x0000u)
					continue;
				ApplyFatMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[(unsigned short)(~Index)]);
			}
			for(int xb=MerginByte;xb<RightStartX;xb++){
				unsigned short	Index=(unsigned short)s0[xb] | (((unsigned short)s1[xb])<<8);
				if(Index==0x0000u)
					continue;
				ApplyFatMaskFast(bmpdata, baseY, xb, PTable.MaskData[(unsigned short)(~Index)]);
			}
			for(int xb=RightStartX;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)s0[xb] | (((unsigned short)s1[xb])<<8);
				if(Index==0x0000u)
					continue;
				ApplyFatMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[(unsigned short)(~Index)]);
			}
		}
		else{
			const BYTE	*s0=bitoperation[y];
			const BYTE	*s1=(y+1<YLenDot)?bitoperation[y+1]:NULL;
			int			baseY=y-Numb;

			for(int xb=0;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)s0[xb];
				if(s1!=NULL)
					Index |= (((unsigned short)s1[xb])<<8);
				if(Index==0x0000u)
					continue;
				ApplyFatMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[(unsigned short)(~Index)]);
			}
		}
	}
}

static	void	FatAreaN16(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	int	MerginByte=(Numb+7)>>3;
	int	TotalR=(YLenDot+1)/2;
	int	SafeStartR=min(TotalR, (Numb+1)/2);
	int	SafeEndR  =max(SafeStartR, min(TotalR, (YLenDot-Numb-1)/2));

	int	BandR=max(Numb+2, 16);
	int	BandCount=(TotalR+BandR-1)/BandR;

	if(BandCount<4 || EnableThread==false){
		FatAreaN16RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
							,0, TotalR, SafeStartR, SafeEndR, MerginByte);
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int b=0;b<BandCount;b+=2){
				int	rStart=b*BandR;
				int	rEnd  =min(TotalR, rStart+BandR);
				FatAreaN16RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
									,rStart, rEnd, SafeStartR, SafeEndR, MerginByte);
			}
			#pragma omp for schedule(static)
			for(int b=1;b<BandCount;b+=2){
				int	rStart=b*BandR;
				int	rEnd  =min(TotalR, rStart+BandR);
				FatAreaN16RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
									,rStart, rEnd, SafeStartR, SafeEndR, MerginByte);
			}
		}
	}
}

static	void	FatAreaN8RowRange(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,int yStart, int yEnd
				,int SafeStartY, int SafeEndY
				,int MerginByte)
{
	int	LeftEndX	=min(MerginByte, xbyte);
	int	RightStartX	=max(MerginByte, xbyte-MerginByte);

	for(int y=yStart;y<yEnd;y++){
		const BYTE	*s0=bitoperation[y];
		int			baseY=y-Numb;
		if(SafeStartY<=y && y<SafeEndY){
			for(int xb=0;xb<LeftEndX;xb++){
				unsigned short	Index=(unsigned short)s0[xb];
				if(Index==0x00u)
					continue;
				ApplyFatMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[((unsigned short)(~Index))&0xFFu]);
			}
			for(int xb=MerginByte;xb<RightStartX;xb++){
				unsigned short	Index=(unsigned short)s0[xb];
				if(Index==0x00u)
					continue;
				ApplyFatMaskFast(bmpdata, baseY, xb, PTable.MaskData[((unsigned short)(~Index))&0xFFu]);
			}
			for(int xb=RightStartX;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)s0[xb];
				if(Index==0x00u)
					continue;
				ApplyFatMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[((unsigned short)(~Index))&0xFFu]);
			}
		}
		else{
			for(int xb=0;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)s0[xb];
				if(Index==0x00u)
					continue;
				ApplyFatMaskSafe(bmpdata, xbyte, YLenDot, baseY, xb, PTable.MaskData[((unsigned short)(~Index))&0xFFu]);
			}
		}
	}
}

static	void	FatAreaN8(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	int	MerginByte=(Numb+7)>>3;
	int	SafeStartY=min(YLenDot, Numb);
	int	SafeEndY  =max(SafeStartY, min(YLenDot, YLenDot-Numb));

	int	BandY=max(2*Numb+2, 32);
	int	BandCount=(YLenDot+BandY-1)/BandY;

	if(BandCount<4 || EnableThread==false){
		FatAreaN8RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
							,0, YLenDot, SafeStartY, SafeEndY, MerginByte);
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int b=0;b<BandCount;b+=2){
				int	yStart=b*BandY;
				int	yEnd  =min(YLenDot, yStart+BandY);
				FatAreaN8RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
									,yStart, yEnd, SafeStartY, SafeEndY, MerginByte);
			}
			#pragma omp for schedule(static)
			for(int b=1;b<BandCount;b+=2){
				int	yStart=b*BandY;
				int	yEnd  =min(YLenDot, yStart+BandY);
				FatAreaN8RowRange(bmpdata, bitoperation, xbyte, YLenDot, Numb, PTable
									,yStart, yEnd, SafeStartY, SafeEndY, MerginByte);
			}
		}
	}
}

static	void	FatAreaN4(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	::FatAreaN(bmpdata, bitoperation, xbyte, YLenDot, Numb, ForceZone, EnableThread);
}
static	void	FatAreaN2(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	::FatAreaN(bmpdata, bitoperation, xbyte, YLenDot, Numb, ForceZone, EnableThread);
}
static	void	FatAreaN1(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	::FatAreaN(bmpdata, bitoperation, xbyte, YLenDot, Numb, ForceZone, EnableThread);
}