/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XImageProcess3.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XImageProcess.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XDot.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"
#include <omp.h>
#include "XImageExpand.h"
#include "XGeneralFunc.h"
#include <omp.h>

/*
	8ビット×2ビット矩形領域での計算
	開始座標は左上
*/
ShrinkingActionData::MaskInfo::MaskInfo(void)
{
	MaskCount1	=0;
	MaskCount2	=0;
	MaskCount3	=0;
}
ShrinkingActionData::MaskInfo::~MaskInfo(void)
{
	MaskCount1=0;
	MaskCount2=0;
	AndMask3=NULL;
	MaskCount3=0;
}
bool	ShrinkingActionData::MaskInfo::Save(QIODevice *f)
{
	BYTE	D[7];
	D[0]=OffsetX;
	D[1]=MaskCount1;
	D[2]=MaskCount2;
	D[3]=MaskCount3;
	D[4]=AndMask1;
	D[5]=0;
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
	OffsetX		=D[0];
	MaskCount1	=D[1];
	MaskCount2	=D[2];
	MaskCount3	=D[3];
	AndMask1	=D[4];
	//AndMask1[1]	=D[5];
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
static	int	TestDbgC=0;
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

	BYTE	M1=i;
	BYTE	M2=i>>8;
	for(int x=0;x<8;x++){
		for(int y=0;y<2;y++){
			if((y==0 && ((M1&(0x80>>x))==0))
			|| (y==1 && ((M2&(0x80>>x))==0))){
				for(int L=0;L<=Len;L++){
					int	x1=-sqrt((double)(Len*Len-L*L));
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
	MaskData[i].Mask=new struct ShrinkingActionData::MaskInfo[YLen];
	MaskData[i].MaskNumb=0;
	for(int y=0;y<YLen;y++){
		int xa;
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
		if(xa<=xb){
			int	C1=-1,C2=-1;
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

			int	s=MaskData[i].MaskNumb;
			//MaskData[i].Mask[s].OffsetY=y-Len;
			if(Found==false){
				MaskData[i].Mask[s].OffsetX=xa+X1;
				MaskData[i].Mask[s].MaskCount1=xb-xa+1;
				MaskData[i].Mask[s].MaskCount2=0;
				MaskData[i].Mask[s].MaskCount3=0;
				if(MaskData[i].Mask[s].MaskCount1==2){
					MaskData[i].Mask[s].MaskCount1=1;
					MaskData[i].Mask[s].MaskCount3=1;
					MaskData[i].Mask[s].AndMask1=~Buff[y][xa+0];
					MaskData[i].Mask[s].AndMask3=~Buff[y][xa+1];
				}
				else{
					for(int t=0;t<MaskData[i].Mask[s].MaskCount1 && t<2;t++){
						MaskData[i].Mask[s].AndMask1=~Buff[y][xa+t];
					}
					if(MaskData[i].Mask[s].MaskCount1==3){
						MaskData[i].Mask[s].MaskCount1=2;
						MaskData[i].Mask[s].MaskCount3=1;
						MaskData[i].Mask[s].AndMask3=~Buff[y][xa+2];
					}
				}
			}
			else{
				MaskData[i].Mask[s].OffsetX=xa+X1;
				MaskData[i].Mask[s].MaskCount1=C1-xa;
				if(MaskData[i].Mask[s].MaskCount1>0){
					for(int t=0;t<MaskData[i].Mask[s].MaskCount1 && t<2;t++){
						MaskData[i].Mask[s].AndMask1=~Buff[y][xa+t];
					}
				}
				MaskData[i].Mask[s].MaskCount2=C2-C1+1;
				MaskData[i].Mask[s].MaskCount3=xb-C2;
				if(MaskData[i].Mask[s].MaskCount3>0){
					MaskData[i].Mask[s].AndMask3=~Buff[y][xa+MaskData[i].Mask[s].MaskCount1+MaskData[i].Mask[s].MaskCount2];
				}
			}
			MaskData[i].MaskNumb++;
		}
	}
	DeleteMatrixBuff(Buff,BuffTmp,YLen);
}

void	ShrinkingPackInternalFunc8(int i ,int Len ,struct	ShrinkingActionData *MaskData)
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

	BYTE	M1=i;
	for(int x=0;x<8;x++){
		if((M1&(0x80>>x))==0){
			for(int L=0;L<=Len;L++){
				int	x1=-sqrt((double)(Len*Len-L*L));
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
	MaskData[i].Mask=new struct ShrinkingActionData::MaskInfo[YLen];
	MaskData[i].MaskNumb=0;
	for(int y=0;y<YLen;y++){
		int xa;
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
		if(xa<=xb){
			int	C1=-1,C2=-1;
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

			int	s=MaskData[i].MaskNumb;
			//MaskData[i].Mask[s].OffsetY=y-Len;
			if(Found==false){
				MaskData[i].Mask[s].OffsetX=xa+X1;
				MaskData[i].Mask[s].MaskCount1=xb-xa+1;
				MaskData[i].Mask[s].MaskCount2=0;
				MaskData[i].Mask[s].MaskCount3=0;
				for(int t=0;t<MaskData[i].Mask[s].MaskCount1 && t<2;t++){
					MaskData[i].Mask[s].AndMask1=~Buff[y][xa+t];
				}
				if(MaskData[i].Mask[s].MaskCount1==3){
					MaskData[i].Mask[s].MaskCount1=2;
					MaskData[i].Mask[s].MaskCount3=1;
					MaskData[i].Mask[s].AndMask3=~Buff[y][xa+2];
				}
			}
			else{
				MaskData[i].Mask[s].OffsetX=xa+X1;
				MaskData[i].Mask[s].MaskCount1=C1-xa;
				if(MaskData[i].Mask[s].MaskCount1>0){
					for(int t=0;t<MaskData[i].Mask[s].MaskCount1 && t<2;t++){
						MaskData[i].Mask[s].AndMask1=~Buff[y][xa+t];
					}
				}
				MaskData[i].Mask[s].MaskCount2=C2-C1+1;
				MaskData[i].Mask[s].MaskCount3=xb-C2;
				if(MaskData[i].Mask[s].MaskCount3>0){
					MaskData[i].Mask[s].AndMask3=~Buff[y][xa+MaskData[i].Mask[s].MaskCount1+MaskData[i].Mask[s].MaskCount2];
				}
			}
			MaskData[i].MaskNumb++;
		}
	}
	DeleteMatrixBuff(Buff,BuffTmp,YLen);
}

void	ShrinkingPackInternalFunc4(int i ,int Len ,struct	ShrinkingActionData *MaskData)
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

	if(i<16){
		BYTE	M1=i<<4;
		for(int x=0;x<4;x++){
			if((M1&(0x80>>x))==0){
				for(int L=0;L<=Len;L++){
					int	x1=-sqrt((double)(Len*Len-L*L));
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
		BYTE	M1=i&0xF;
		for(int x=4;x<8;x++){
			if((M1&(0x80>>x))==0){
				for(int L=0;L<=Len;L++){
					int	x1=-sqrt((double)(Len*Len-L*L));
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

	MaskData[i].Mask=new struct ShrinkingActionData::MaskInfo[YLen];
	MaskData[i].MaskNumb=0;
	for(int y=0;y<YLen;y++){
		int xa;
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
		if(xa<=xb){
			int	C1=-1,C2=-1;
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

			int	s=MaskData[i].MaskNumb;
			//MaskData[i].Mask[s].OffsetY=y-Len;
			if(Found==false){
				MaskData[i].Mask[s].OffsetX=xa+X1;
				MaskData[i].Mask[s].MaskCount1=xb-xa+1;
				MaskData[i].Mask[s].MaskCount2=0;
				MaskData[i].Mask[s].MaskCount3=0;
				for(int t=0;t<MaskData[i].Mask[s].MaskCount1 && t<2;t++){
					MaskData[i].Mask[s].AndMask1=~Buff[y][xa+t];
				}
				if(MaskData[i].Mask[s].MaskCount1==3){
					MaskData[i].Mask[s].MaskCount1=2;
					MaskData[i].Mask[s].MaskCount3=1;
					MaskData[i].Mask[s].AndMask3=~Buff[y][xa+2];
				}
			}
			else{
				MaskData[i].Mask[s].OffsetX=xa+X1;
				MaskData[i].Mask[s].MaskCount1=C1-xa;
				if(MaskData[i].Mask[s].MaskCount1>0){
					for(int t=0;t<MaskData[i].Mask[s].MaskCount1 && t<2;t++){
						MaskData[i].Mask[s].AndMask1=~Buff[y][xa+t];
					}
				}
				MaskData[i].Mask[s].MaskCount2=C2-C1+1;
				MaskData[i].Mask[s].MaskCount3=xb-C2;
				if(MaskData[i].Mask[s].MaskCount3>0){
					MaskData[i].Mask[s].AndMask3=~Buff[y][xa+MaskData[i].Mask[s].MaskCount1+MaskData[i].Mask[s].MaskCount2];
				}
			}
			MaskData[i].MaskNumb++;
		}
	}
	DeleteMatrixBuff(Buff,BuffTmp,YLen);
}

void	ShrinkingPackInternalFunc2(int i ,int Len ,struct	ShrinkingActionData *MaskData)
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

	int	SNumb=i/4;
	int	LeftBit=SNumb*2;
	BYTE	M1=(i&0x03)<<(6-LeftBit);
	for(int x=LeftBit;x<(LeftBit+2);x++){
		if((M1&(0x80>>x))==0){
			for(int L=0;L<=Len;L++){
				int	x1=-sqrt((double)(Len*Len-L*L));
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


	MaskData[i].Mask=new struct ShrinkingActionData::MaskInfo[YLen];
	MaskData[i].MaskNumb=0;
	for(int y=0;y<YLen;y++){
		int xa;
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
		if(xa<=xb){
			int	C1=-1,C2=-1;
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

			int	s=MaskData[i].MaskNumb;
			//MaskData[i].Mask[s].OffsetY=y-Len;
			if(Found==false){
				MaskData[i].Mask[s].OffsetX=xa+X1;
				MaskData[i].Mask[s].MaskCount1=xb-xa+1;
				MaskData[i].Mask[s].MaskCount2=0;
				MaskData[i].Mask[s].MaskCount3=0;
				for(int t=0;t<MaskData[i].Mask[s].MaskCount1 && t<2;t++){
					MaskData[i].Mask[s].AndMask1=~Buff[y][xa+t];
				}
				if(MaskData[i].Mask[s].MaskCount1==3){
					MaskData[i].Mask[s].MaskCount1=2;
					MaskData[i].Mask[s].MaskCount3=1;
					MaskData[i].Mask[s].AndMask3=~Buff[y][xa+2];
				}
			}
			else{
				MaskData[i].Mask[s].OffsetX=xa+X1;
				MaskData[i].Mask[s].MaskCount1=C1-xa;
				if(MaskData[i].Mask[s].MaskCount1>0){
					for(int t=0;t<MaskData[i].Mask[s].MaskCount1 && t<2;t++){
						MaskData[i].Mask[s].AndMask1=~Buff[y][xa+t];
					}
				}
				MaskData[i].Mask[s].MaskCount2=C2-C1+1;
				MaskData[i].Mask[s].MaskCount3=xb-C2;
				if(MaskData[i].Mask[s].MaskCount3>0){
					MaskData[i].Mask[s].AndMask3=~Buff[y][xa+MaskData[i].Mask[s].MaskCount1+MaskData[i].Mask[s].MaskCount2];
				}
			}
			MaskData[i].MaskNumb++;
		}
	}
	DeleteMatrixBuff(Buff,BuffTmp,YLen);
}

void	ShrinkingPackInternalFunc1(int i ,int Len ,struct	ShrinkingActionData *MaskData)
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

	int	LeftBit=i;
	int x=LeftBit;
	for(int L=0;L<=Len;L++){
		int	x1=-sqrt((double)(Len*Len-L*L));
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

	MaskData[i].Mask=new struct ShrinkingActionData::MaskInfo[YLen];
	MaskData[i].MaskNumb=0;
	for(int y=0;y<YLen;y++){
		int xa;
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
		if(xa<=xb){
			int	C1=-1,C2=-1;
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

			int	s=MaskData[i].MaskNumb;
			//MaskData[i].Mask[s].OffsetY=y-Len;
			if(Found==false){
				MaskData[i].Mask[s].OffsetX=xa+X1;
				MaskData[i].Mask[s].MaskCount1=xb-xa+1;
				MaskData[i].Mask[s].MaskCount2=0;
				MaskData[i].Mask[s].MaskCount3=0;
				for(int t=0;t<MaskData[i].Mask[s].MaskCount1 && t<2;t++){
					MaskData[i].Mask[s].AndMask1=~Buff[y][xa+t];
				}
				if(MaskData[i].Mask[s].MaskCount1==3){
					MaskData[i].Mask[s].MaskCount1=2;
					MaskData[i].Mask[s].MaskCount3=1;
					MaskData[i].Mask[s].AndMask3=~Buff[y][xa+2];
				}
			}
			else{
				MaskData[i].Mask[s].OffsetX=xa+X1;
				MaskData[i].Mask[s].MaskCount1=C1-xa;
				if(MaskData[i].Mask[s].MaskCount1>0){
					for(int t=0;t<MaskData[i].Mask[s].MaskCount1 && t<2;t++){
						MaskData[i].Mask[s].AndMask1=~Buff[y][xa+t];
					}
				}
				MaskData[i].Mask[s].MaskCount2=C2-C1+1;
				MaskData[i].Mask[s].MaskCount3=xb-C2;
				if(MaskData[i].Mask[s].MaskCount3>0){
					MaskData[i].Mask[s].AndMask3=~Buff[y][xa+MaskData[i].Mask[s].MaskCount1+MaskData[i].Mask[s].MaskCount2];
				}
			}
			MaskData[i].MaskNumb++;
		}
	}
	DeleteMatrixBuff(Buff,BuffTmp,YLen);
}

void	ShrinkingPack::Initial(int len)
{
	Len=len;
	if(MaskData!=NULL)
		delete	[]MaskData;

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
	}
	if(N==0){
		MaskData=NULL;
	}
	else{
		MaskData=new struct	ShrinkingActionData[N];
		for(int i=0;i<N;i++){
			if(MaskData[i].Load(f)==false)
				return false;
			//for(int j=0;j<MaskData[i].MaskNumb;j++){
			//	if(MaskData[i].Mask[j].MaskCount1>1){
			//		MaskData[i].Mask[j].MaskCount2+=MaskData[i].Mask[j].MaskCount1-1;
			//		MaskData[i].Mask[j].MaskCount1=1;
			//	}
			//}
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
	if(item->Len<DimNumb){
		Dim[item->Len]=item;
	}
	else{
		int	Len=item->Len*2;
		ShrinkingPack	**DimSub=new ShrinkingPack*[Len];
		for(int i=0;i<Len;i++){
			DimSub[i]=NULL;
		}
		for(int i=0;i<DimNumb;i++){
			DimSub[i]=Dim[i];
		}
		DimSub[item->Len]=item;
		delete	[]Dim;
		Dim=DimSub;
		DimNumb=Len;
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
	if(Numb<DimNumb && Dim[Numb]!=NULL){
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
	if(IsLoaded(Numb)==false){
		ShrinkingPack	*s=new ShrinkingPack;
		s->Initial(Numb);
		AppendListItem(s);
	}
	/*
	int	MaxD1=0;
	int	MaxD2=0;
	int	MaxD3=0;
	for(int i=1;i<DimNumb;i++){
		if(Dim[i]!=NULL){
			ShrinkingPack	&M=*Dim[i];
			for(int k=0;k<M.Len;k++){
				for(int h=0;h<M.MaskData[k].MaskNumb;h++){
					MaxD1=max(MaxD1,M.MaskData[k].Mask[h].MaskCount1);
					MaxD2=max(MaxD2,M.MaskData[k].Mask[h].MaskCount2);
					MaxD3=max(MaxD3,M.MaskData[k].Mask[h].MaskCount3);
				}
			}
		}
	}
	*/

	::ThinAreaN(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,*GetPack(Numb)
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
	if(IsLoaded(Numb)==false){
		ShrinkingPack	*s=new ShrinkingPack;
		s->Initial(Numb);
		AppendListItem(s);
	}
	::FatAreaN(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,*GetPack(Numb)
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
	if(Numb<=0){
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
	int	Start;
	if(X<0){
		Start=-X;
		X=0;
		Count-=Start;
	}
	else{
		Start=0;
	}
	if(X>=XByte){
		int	Dif=X-XByte;
		Count-=Dif;
	}

	BYTE	*dw=(BYTE	*)&(d[X]);
	BYTE	*sw=(BYTE	*)&(s[Start]);
	if(Count>=8){
		int	n=Count>>3;
		for(int i=0;i<n;i++){
			*((uint64 *)dw) &= *((uint64 *)sw);
			dw+=8;
			sw+=8;
		}
		n=n<<3;
		X+=n;
		Count-=n;
	}
	if(Count>=4){
		*((DWORD *)dw) &= *((DWORD *)sw);
		sw+=4;
		dw+=4;
		X+=4;
		Count-=4;
	}
	if(Count>=2){
		*((WORD *)dw) &= *((WORD *)sw);
		sw+=2;
		dw+=2;
		X+=2;
		Count-=2;
	}
	if(Count>=1){
		*dw &= *sw;
		X++;
	}
	return X;
}


inline	int	For0(int Count, BYTE *d ,int XByte, int X)
{
	if(X<0){
		Count+=X;
		X=0;
	}
	if(X>=XByte){
		int	Dif=X-XByte;
		Count-=Dif;
	}
	BYTE	*dw=(BYTE	*)&(d[X]);
	if(Count>=8){
		int	n=Count>>3;
		for(int i=0;i<n;i++){
			*((uint64*)dw) = 0;
			dw+=8;
		}
		n=n<<3;
		X+=n;
		Count-=n;
	}
	if(Count>=4){
		*((DWORD *)dw) = 0;
		dw+=4;
		X+=4;
		Count-=4;
	}
	if(Count>=2){
		*((WORD *)dw) = 0;
		dw+=2;
		X+=2;
		Count-=2;
	}
	if(Count>=1){
		*dw = 0;
		X++;
	}
	return X;
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

	for(int y=0;y<Numb;y+=2){
		for(int xb=xbyte-MerginByte;xb<xbyte-MerginByte;xb++){
			unsigned short	Index=(unsigned short)(bitoperation[y][xb])+(((unsigned short)bitoperation[y+1][xb])<<8);
			struct	ShrinkingActionData	&M=PTable.MaskData[Index];
			ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
			for(int i=0;i<M.MaskNumb;i++,MInfo++){
				int	Y=y-Numb+i;
				if(Y<0 || YLenDot<=Y)
					continue;
				BYTE	*d=bmpdata[Y];
				int		Counter1=MInfo->MaskCount1;
				int		X=xb+MInfo->OffsetX;
				//X=ForAnd(Counter1, d ,s,xbyte, X);
				if(Counter1>0){
					d[X] &= MInfo->AndMask1;
					X++;
				}
				int		Counter2=MInfo->MaskCount2;
				//X=For0(Counter2, d ,xbyte, X);
				for(int k=0;k<Counter2;k++){
					d[X]=0;
					X++;
				}
				int		Counter3=MInfo->MaskCount3;
				if(Counter3>0){
					d[X] &= MInfo->AndMask3;
				}
			}
		}
	}
	for(int y=YLenDot-Numb-2;y<Numb;y+=2){
		for(int xb=xbyte-MerginByte;xb<xbyte-MerginByte;xb++){
			unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
			if(y+1<YLenDot)
				Index+=(((unsigned short)bitoperation[y+1][xb])<<8);
			else
				Index+=0xFF00;
			struct	ShrinkingActionData	&M=PTable.MaskData[Index];
			ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
			for(int i=0;i<M.MaskNumb;i++,MInfo++){
				int	Y=y-Numb+i;
				if(Y<0 || YLenDot<=Y)
					continue;
				BYTE	*d=bmpdata[Y];
				int		Counter1=MInfo->MaskCount1;
				int		X=xb+MInfo->OffsetX;
				if(Counter1>0){
					d[X] &= MInfo->AndMask1;
					X++;
				}
				int		Counter2=MInfo->MaskCount2;
				for(int k=0;k<Counter2;k++){
					d[X]=0;
					X++;
				}
				int		Counter3=MInfo->MaskCount3;
				if(Counter3>0){
					d[X] &= MInfo->AndMask3;
				}
			}
		}
	}		
	int	N=(YLenDot-Numb-Numb-2)/2;
	if(N<32 || EnableThread==false){
		for(int y=0;y<YLenDot;y+=2){
			for(int xb=0;xb<MerginByte && xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
				if(y+1<YLenDot)
					Index+=(((unsigned short)bitoperation[y+1][xb])<<8);
				else
					Index+=0xFF00;
				struct	ShrinkingActionData	&M=PTable.MaskData[Index];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					int	Y=y-Numb+i;
					if(Y<0 || YLenDot<=Y)
						continue;
					BYTE	*d=bmpdata[Y];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						if(0<=X && X<xbyte)
							d[X] &= MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						if(0<=X && X<xbyte)
							d[X]=0;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						if(0<=X && X<xbyte)
							d[X] &= MInfo->AndMask3;
					}
				}
			}
			for(int xb=xbyte-MerginByte;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
				if(y+1<YLenDot)
					Index+=(((unsigned short)bitoperation[y+1][xb])<<8);
				else
					Index+=0xFF00;
				struct	ShrinkingActionData	&M=PTable.MaskData[Index];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					int	Y=y-Numb+i;
					if(Y<0 || YLenDot<=Y)
						continue;
					BYTE	*d=bmpdata[Y];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						if(0<=X && X<xbyte)
							d[X] &= MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						if(0<=X && X<xbyte)
							d[X]=0;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						if(0<=X && X<xbyte)
							d[X] &= MInfo->AndMask3;
					}
				}
			}
		}
		for(int y=Numb;y<YLenDot-Numb-2;y+=2){
			for(int xb=MerginByte;xb<xbyte-MerginByte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb])+(((unsigned short)bitoperation[y+1][xb])<<8);
				struct	ShrinkingActionData	&M=PTable.MaskData[Index];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					BYTE	*d=bmpdata[y-Numb+i];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						d[X] &= MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						d[X]=0;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						d[X] &= MInfo->AndMask3;
					}
				}
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int r=0;r<N;r++){
			//for(int r=0;r<N;r++){
				int	y=r*2;
				int	StartY=(y-Numb>=0)?0:-(y-Numb);
				for(int xb=0;xb<MerginByte && xb<xbyte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
					if(y+1<YLenDot)
						Index+=(((unsigned short)bitoperation[y+1][xb])<<8);
					else
						Index+=0xFF00;
					struct	ShrinkingActionData	&M=PTable.MaskData[Index];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=StartY;i<M.MaskNumb;i++,MInfo++){
						int	Y=y-Numb+i;
						if(YLenDot<=Y)
							break;
						int		X=xb+MInfo->OffsetX;
						BYTE	*d=bmpdata[Y];
						int		Counter1=MInfo->MaskCount1;
						//X=ForAnd(Counter1, d ,s,xbyte, X);
						if(Counter1>0){
							if(0<=X && X<xbyte)
								d[X] &= MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						//X=For0(Counter2, d ,xbyte, X);
						for(int k=0;k<Counter2;k++){
							if(0<=X && X<xbyte)
								d[X]=0;
							X++;
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							if(0<=X && X<xbyte)
								d[X] &= MInfo->AndMask3;
						}
					}
				}
				for(int xb=xbyte-MerginByte;xb<xbyte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
					if(y+1<YLenDot)
						Index+=(((unsigned short)bitoperation[y+1][xb])<<8);
					else
						Index+=0xFF00;
					struct	ShrinkingActionData	&M=PTable.MaskData[Index];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=StartY;i<M.MaskNumb;i++,MInfo++){
						int	Y=y-Numb+i;
						if(YLenDot<=Y)
							break;
						int		X=xb+MInfo->OffsetX;
						BYTE	*d=bmpdata[Y];
						int		Counter1=MInfo->MaskCount1;
						//X=ForAnd(Counter1, d ,s,xbyte, X);
						if(Counter1>0){
							if(0<=X && X<xbyte)
								d[X] &= MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						//X=For0(Counter2, d ,xbyte, X);
						for(int k=0;k<Counter2;k++){
							if(0<=X && X<xbyte)
								d[X]=0;
							X++;
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							if(0<=X && X<xbyte)
								d[X] &= MInfo->AndMask3;
						}
					}
				}
			}
		}
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int r=0;r<N;r++){
				int	y=r*2+Numb;
				for(int xb=MerginByte;xb<xbyte-MerginByte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb])+(((unsigned short)bitoperation[y+1][xb])<<8);
					struct	ShrinkingActionData	&M=PTable.MaskData[Index];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=0;i<M.MaskNumb;i++,MInfo++){
						int		X=xb+MInfo->OffsetX;
						BYTE	*d=bmpdata[y-Numb+i];
						int		Counter1=MInfo->MaskCount1;
						//X=ForAnd(Counter1, d ,s,xbyte, X);
						if(Counter1>0){
							d[X] &= MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						//X=For0(Counter2, d ,xbyte, X);
						//for(int k=0;k<Counter2;k++){
						//	d[X]=0;
						//	X++;
						//}
						switch(Counter2){
						case 0:	break;
						case 1:	d[X]=0;	X++;	break;
						case 2:	*((WORD *)&d[X])=0;	X+=2;	break;
						case 3:	*((WORD *)&d[X])=0;	d[X+2]=0;	X+=3;		break;
						case 4:	*((DWORD *)&d[X])=0;	X+=4;	break;
						case 5:	*((DWORD *)&d[X])=0;	d[X+4]=0;	X+=5;		break;
						case 6:	*((DWORD *)&d[X])=0;	*((WORD *)&d[X+4])=0;	X+=6;		break;
						case 7:	*((DWORD *)&d[X])=0;	*((WORD *)&d[X+4])=0;	d[X+6]=0;	X+=7;		break;
						case 8:	*((uint64*)&d[X])=0;	X+=8;		break;
						default:
							memset(&d[X],0,Counter2);
							X+=Counter2;
							//for(int k=0;k<Counter2;k++){
							//	d[X]=0;
							//	X++;
							//}
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							d[X] &= MInfo->AndMask3;
						}
					}
				}
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

	for(int y=0;y<Numb;y++){
		int	StartY=-(y-Numb);
		for(int xb=xbyte-MerginByte;xb<xbyte-MerginByte;xb++){
			unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
			struct	ShrinkingActionData	&M=PTable.MaskData[Index];
			ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
			for(int i=StartY;i<M.MaskNumb;i++,MInfo++){
				int	Y=y-Numb+i;
				if(YLenDot<=Y)
					break;
				BYTE	*d=bmpdata[Y];
				int		Counter1=MInfo->MaskCount1;
				int		X=xb+MInfo->OffsetX;
				if(Counter1>0){
					d[X] &= MInfo->AndMask1;
					X++;
				}
				int		Counter2=MInfo->MaskCount2;
				for(int k=0;k<Counter2;k++){
					d[X]=0;
					X++;
				}
				int		Counter3=MInfo->MaskCount3;
				if(Counter3>0){
					d[X] &= MInfo->AndMask3;
				}
			}
		}
	}
	for(int y=YLenDot-Numb-1;y<Numb;y++){
		int	StartY=(y-Numb>=0)?0:-(y-Numb);
		for(int xb=xbyte-MerginByte;xb<xbyte-MerginByte;xb++){
			unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
			struct	ShrinkingActionData	&M=PTable.MaskData[Index];
			ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
			for(int i=StartY;i<M.MaskNumb;i++,MInfo++){
				int	Y=y-Numb+i;
				if(YLenDot<=Y)
					break;
				BYTE	*d=bmpdata[Y];
				int		Counter1=MInfo->MaskCount1;
				int		X=xb+MInfo->OffsetX;
				if(Counter1>0){
					d[X] &= MInfo->AndMask1;
					X++;
				}
				int		Counter2=MInfo->MaskCount2;
				for(int k=0;k<Counter2;k++){
					d[X]=0;
					X++;
				}
				int		Counter3=MInfo->MaskCount3;
				if(Counter3>0){
					d[X] &= MInfo->AndMask3;
				}
			}
		}
	}		
	int	N=YLenDot-Numb-Numb-1;
	if(N<32 || EnableThread==false){
		for(int y=0;y<YLenDot;y++){
			for(int xb=0;xb<MerginByte && xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
				struct	ShrinkingActionData	&M=PTable.MaskData[Index];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=max(y-Numb,0);i<M.MaskNumb;i++,MInfo++){
					int	Y=y-Numb+i;
					if(Y<0 || YLenDot<=Y)
						continue;
					BYTE	*d=bmpdata[Y];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						if(0<=X && X<xbyte)
							d[X] &= MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						if(0<=X && X<xbyte)
							d[X]=0;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						if(0<=X && X<xbyte)
							d[X] &= MInfo->AndMask3;
					}
				}
			}
			for(int xb=xbyte-MerginByte;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
				struct	ShrinkingActionData	&M=PTable.MaskData[Index];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					int	Y=y-Numb+i;
					if(Y<0 || YLenDot<=Y)
						continue;
					BYTE	*d=bmpdata[Y];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						if(0<=X && X<xbyte)
							d[X] &= MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						if(0<=X && X<xbyte)
							d[X]=0;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						if(0<=X && X<xbyte)
							d[X] &= MInfo->AndMask3;
					}
				}
			}
		}
		for(int y=Numb;y<YLenDot-Numb-2;y++){
			for(int xb=MerginByte;xb<xbyte-MerginByte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
				struct	ShrinkingActionData	&M=PTable.MaskData[Index];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					BYTE	*d=bmpdata[y-Numb+i];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						d[X] &= MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						d[X]=0;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						d[X] &= MInfo->AndMask3;
					}
				}
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int r=0;r<N;r++){
			//for(int r=0;r<N;r++){
				int	y=r;
				int	StartY=(y-Numb>=0)?0:-(y-Numb);
				for(int xb=0;xb<MerginByte && xb<xbyte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
					struct	ShrinkingActionData	&M=PTable.MaskData[Index];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=StartY;i<M.MaskNumb;i++,MInfo++){
						int	Y=y-Numb+i;
						if(YLenDot<=Y)
							break;
						BYTE	*d=bmpdata[Y];
						int		Counter1=MInfo->MaskCount1;
						int		X=xb+MInfo->OffsetX;
						//X=ForAnd(Counter1, d ,s,xbyte, X);
						if(Counter1>0){
							if(0<=X && X<xbyte)
								d[X] &= MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						//X=For0(Counter2, d ,xbyte, X);
						for(int k=0;k<Counter2;k++){
							if(0<=X && X<xbyte)
								d[X]=0;
							X++;
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							if(0<=X && X<xbyte)
								d[X] &= MInfo->AndMask3;
						}
					}
				}
				for(int xb=xbyte-MerginByte;xb<xbyte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
					struct	ShrinkingActionData	&M=PTable.MaskData[Index];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=StartY;i<M.MaskNumb;i++,MInfo++){
						int	Y=y-Numb+i;
						if(YLenDot<=Y)
							break;
						BYTE	*d=bmpdata[Y];
						int		Counter1=MInfo->MaskCount1;
						int		X=xb+MInfo->OffsetX;
						//X=ForAnd(Counter1, d ,s,xbyte, X);
						if(Counter1>0){
							if(0<=X && X<xbyte)
								d[X] &= MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						//X=For0(Counter2, d ,xbyte, X);
						for(int k=0;k<Counter2;k++){
							if(0<=X && X<xbyte)
								d[X]=0;
							X++;
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							if(0<=X && X<xbyte)
								d[X] &= MInfo->AndMask3;
						}
					}
				}
			}
		}
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int r=0;r<N;r++){
				int	y=r+Numb;
				for(int xb=MerginByte;xb<xbyte-MerginByte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
					struct	ShrinkingActionData	&M=PTable.MaskData[Index];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=0;i<M.MaskNumb;i++,MInfo++){
						BYTE	*d=bmpdata[y-Numb+i];
						int		Counter1=MInfo->MaskCount1;
						int		X=xb+MInfo->OffsetX;
						//X=ForAnd(Counter1, d ,s,xbyte, X);
						if(Counter1>0){
							d[X] &= MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						//for(int k=0;k<Counter2;k++){
						//	d[X]=0;
						//	X++;
						//}
						switch(Counter2){
						case 0:	break;
						case 1:	d[X]=0;	X++;	break;
						case 2:	*((WORD *)&d[X])=0;	X+=2;	break;
						case 3:	*((WORD *)&d[X])=0;	d[X+2]=0;	X+=3;		break;
						case 4:	*((DWORD *)&d[X])=0;	X+=4;	break;
						case 5:	*((DWORD *)&d[X])=0;	d[X+4]=0;	X+=5;		break;
						case 6:	*((DWORD *)&d[X])=0;	*((WORD *)&d[X+4])=0;	X+=6;		break;
						case 7:	*((DWORD *)&d[X])=0;	*((WORD *)&d[X+4])=0;	d[X+6]=0;	X+=7;		break;
						case 8:	*((uint64*)&d[X])=0;	X+=8;		break;
						default:
							memset(&d[X],0,Counter2);
							X+=Counter2;
							//for(int k=0;k<Counter2;k++){
							//	d[X]=0;
							//	X++;
							//}
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							d[X] &= MInfo->AndMask3;
						}
					}
				}
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
}
static	void    ThinAreaN2(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
}
static	void    ThinAreaN1(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
}

void    FatAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
	if(Numb<=0){
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
				, Numb
				,PTable
				,ForceZone
				,EnableThread);
	}
	if(PTable.BitNumb==8){
		FatAreaN8(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				, Numb
				,PTable
				,ForceZone
				,EnableThread);
	}
	if(Allocbitoperation==true){
		DeleteMatrixBuff(bitoperation,YLenDot);
		bitoperation=NULL;
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

	for(int y=0;y<Numb;y+=2){
		for(int xb=xbyte-MerginByte;xb<xbyte-MerginByte;xb++){
			unsigned short	Index=(unsigned short)(bitoperation[y][xb])+(((unsigned short)bitoperation[y+1][xb])<<8);
			struct	ShrinkingActionData	&M=PTable.MaskData[(unsigned short)(~Index)];
			ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
			for(int i=0;i<M.MaskNumb;i++,MInfo++){
				int	Y=y-Numb+i;
				if(Y<0 || YLenDot<=Y)
					continue;
				BYTE	*d=bmpdata[Y];
				int		Counter1=MInfo->MaskCount1;
				int		X=xb+MInfo->OffsetX;
				if(Counter1>0){
					d[X] |= ~MInfo->AndMask1;
					X++;
				}
				int		Counter2=MInfo->MaskCount2;
				for(int k=0;k<Counter2;k++){
					d[X]=0xFF;
					X++;
				}
				int		Counter3=MInfo->MaskCount3;
				if(Counter3>0){
					d[X] |= ~MInfo->AndMask3;
				}
			}
		}
	}
	for(int y=YLenDot-Numb-2;y<Numb;y+=2){
		for(int xb=xbyte-MerginByte;xb<xbyte-MerginByte;xb++){
			unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
			if(y+1<YLenDot)
				Index+=(((unsigned short)bitoperation[y+1][xb])<<8);
			else
				Index+=0xFF00;
			struct	ShrinkingActionData	&M=PTable.MaskData[(unsigned short)(~Index)];
			ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
			for(int i=0;i<M.MaskNumb;i++,MInfo++){
				int	Y=y-Numb+i;
				if(Y<0 || YLenDot<=Y)
					continue;
				BYTE	*d=bmpdata[Y];
				int		Counter1=MInfo->MaskCount1;
				int		X=xb+MInfo->OffsetX;
				if(Counter1>0){
					d[X] |= ~MInfo->AndMask1;
					X++;
				}
				int		Counter2=MInfo->MaskCount2;
				for(int k=0;k<Counter2;k++){
					d[X]=0xFF;
					X++;
				}
				int		Counter3=MInfo->MaskCount3;
				if(Counter3>0){
					d[X] |= ~MInfo->AndMask3;
				}
			}
		}
	}		
	int	N=(YLenDot-Numb-Numb-2)/2;
	if(N<32 || EnableThread==false){
	//if(EnableThread==true){
		for(int y=0;y<YLenDot;y+=2){
			for(int xb=0;xb<MerginByte && xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
				if(y+1<YLenDot)
					Index+=(((unsigned short)bitoperation[y+1][xb])<<8);
				else
					Index+=0xFF00;
				struct	ShrinkingActionData	&M=PTable.MaskData[(unsigned short)(~Index)];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					int	Y=y-Numb+i;
					if(Y<0 || YLenDot<=Y)
						continue;
					BYTE	*d=bmpdata[Y];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						if(0<=X && X<xbyte)
							d[X] |= ~MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						if(0<=X && X<xbyte)
							d[X]=0xFF;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						if(0<=X && X<xbyte)
							d[X] |= ~MInfo->AndMask3;
					}
				}
			}
			for(int xb=xbyte-MerginByte;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
				if(y+1<YLenDot)
					Index+=(((unsigned short)bitoperation[y+1][xb])<<8);
				else
					Index+=0xFF00;
				struct	ShrinkingActionData	&M=PTable.MaskData[(unsigned short)(~Index)];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					int	Y=y-Numb+i;
					if(Y<0 || YLenDot<=Y)
						continue;
					BYTE	*d=bmpdata[Y];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						if(0<=X && X<xbyte)
							d[X] |= ~MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						if(0<=X && X<xbyte)
							d[X]=0xFF;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						if(0<=X && X<xbyte)
							d[X] |= ~MInfo->AndMask3;
					}
				}
			}
		}
		for(int y=Numb;y<YLenDot-Numb-2;y+=2){
			for(int xb=MerginByte;xb<xbyte-MerginByte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb])+(((unsigned short)bitoperation[y+1][xb])<<8);
				struct	ShrinkingActionData	&M=PTable.MaskData[(unsigned short)(~Index)];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					BYTE	*d=bmpdata[y-Numb+i];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						d[X] |= ~MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						d[X]=0xFF;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						d[X] |= ~MInfo->AndMask3;
					}
				}
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int r=0;r<N;r++){
			//for(int r=0;r<N;r++){
				int	y=r*2;
				for(int xb=0;xb<MerginByte && xb<xbyte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
					if(y+1<YLenDot)
						Index+=(((unsigned short)bitoperation[y+1][xb])<<8);
					else
						Index+=0xFF00u;
					struct	ShrinkingActionData	&M=PTable.MaskData[(unsigned short)(~Index)];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=0;i<M.MaskNumb;i++,MInfo++){
						int	Y=y-Numb+i;
						if(Y<0 || YLenDot<=Y)
							continue;
						BYTE	*d=bmpdata[Y];
						int		Counter1=MInfo->MaskCount1;
						int		X=xb+MInfo->OffsetX;
						if(Counter1>0){
							if(0<=X && X<xbyte)
								d[X] |= ~MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						for(int k=0;k<Counter2;k++){
							if(0<=X && X<xbyte)
								d[X]=0xFF;
							X++;
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							if(0<=X && X<xbyte)
								d[X] |= ~MInfo->AndMask3;
						}
					}
				}
				for(int xb=xbyte-MerginByte;xb<xbyte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
					if(y+1<YLenDot)
						Index+=(((unsigned short)bitoperation[y+1][xb])<<8);
					else
						Index+=0xFF00;
					struct	ShrinkingActionData	&M=PTable.MaskData[(unsigned short)(~Index)];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=0;i<M.MaskNumb;i++,MInfo++){
						int	Y=y-Numb+i;
						if(Y<0 || YLenDot<=Y)
							continue;
						BYTE	*d=bmpdata[Y];
						int		Counter1=MInfo->MaskCount1;
						int		X=xb+MInfo->OffsetX;
						if(Counter1>0){
							if(0<=X && X<xbyte)
								d[X] |= ~MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						for(int k=0;k<Counter2;k++){
							if(0<=X && X<xbyte)
								d[X]=0xFF;
							X++;
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							if(0<=X && X<xbyte)
								d[X] |= ~MInfo->AndMask3;
						}
					}
				}
			}
		}
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int r=0;r<N;r++){
				int	y=r*2+Numb;
				for(int xb=MerginByte;xb<xbyte-MerginByte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb])+(((unsigned short)bitoperation[y+1][xb])<<8);
					struct	ShrinkingActionData	&M=PTable.MaskData[(unsigned short)(~Index)];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=0;i<M.MaskNumb;i++,MInfo++){
						BYTE	*d=bmpdata[y-Numb+i];
						int		Counter1=MInfo->MaskCount1;
						int		X=xb+MInfo->OffsetX;
						if(Counter1>0){
							d[X] |= ~MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						//for(int k=0;k<Counter2;k++){
						//	d[X]=0xFF;
						//	X++;
						//}
						
						switch(Counter2){
						case 0:	break;
						case 1:	d[X]=0xFF;	X++;	break;
						case 2:	*((WORD *)&d[X])=0xFFFF;	X+=2;	break;
						case 3:	*((WORD *)&d[X])=0xFFFF;	d[X+2]=0xFF;	X+=3;		break;
						case 4:	*((DWORD *)&d[X])=0xFFFFFFFFuL;	X+=4;	break;
						case 5:	*((DWORD *)&d[X])=0xFFFFFFFFuL;	d[X+4]=0xFF;	X+=5;		break;
						case 6:	*((DWORD *)&d[X])=0xFFFFFFFFuL;	*((WORD *)&d[X+4])=0xFFFF;	X+=6;		break;
						case 7:	*((DWORD *)&d[X])=0xFFFFFFFFuL;	*((WORD *)&d[X+4])=0xFFFF;	d[X+6]=0xFF;	X+=7;		break;
						case 8:	*((uint64*)&d[X])=0xFFFFFFFFFFFFFFFFuLL;	X+=8;		break;
						default:
							memset(&d[X],0xFF,Counter2);
							X+=Counter2;
						}
						
			
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							d[X] |= ~MInfo->AndMask3;
						}
					}
				}
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

	for(int y=0;y<Numb;y++){
		for(int xb=xbyte-MerginByte;xb<xbyte-MerginByte;xb++){
			unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
			struct	ShrinkingActionData	&M=PTable.MaskData[((unsigned short)(~Index))&0xFF];
			ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
			for(int i=0;i<M.MaskNumb;i++,MInfo++){
				int	Y=y-Numb+i;
				if(Y<0 || YLenDot<=Y)
					continue;
				BYTE	*d=bmpdata[Y];
				int		Counter1=MInfo->MaskCount1;
				int		X=xb+MInfo->OffsetX;
				if(Counter1>0){
					d[X] |= ~MInfo->AndMask1;
					X++;
				}
				int		Counter2=MInfo->MaskCount2;
				for(int k=0;k<Counter2;k++){
					d[X]=0xFF;
					X++;
				}
				int		Counter3=MInfo->MaskCount3;
				if(Counter3>0){
					d[X] |= ~MInfo->AndMask3;
				}
			}
		}
	}
	for(int y=YLenDot-Numb-2;y<Numb;y++){
		for(int xb=xbyte-MerginByte;xb<xbyte-MerginByte;xb++){
			unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
			struct	ShrinkingActionData	&M=PTable.MaskData[((unsigned short)(~Index))&0xFF];
			ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
			for(int i=0;i<M.MaskNumb;i++,MInfo++){
				int	Y=y-Numb+i;
				if(Y<0 || YLenDot<=Y)
					continue;
				BYTE	*d=bmpdata[Y];
				int		Counter1=MInfo->MaskCount1;
				int		X=xb+MInfo->OffsetX;
				if(Counter1>0){
					d[X] |= ~MInfo->AndMask1;
					X++;
				}
				int		Counter2=MInfo->MaskCount2;
				for(int k=0;k<Counter2;k++){
					d[X]=0xFF;
					X++;
				}
				int		Counter3=MInfo->MaskCount3;
				if(Counter3>0){
					d[X] |= ~MInfo->AndMask3;
				}
			}
		}
	}		
	int	N=YLenDot-Numb-Numb-1;
	if(N<32 || EnableThread==false){
	//if(EnableThread==true){
		for(int y=0;y<YLenDot;y++){
			for(int xb=0;xb<MerginByte && xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
				struct	ShrinkingActionData	&M=PTable.MaskData[((unsigned short)(~Index))&0xFF];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					int	Y=y-Numb+i;
					if(Y<0 || YLenDot<=Y)
						continue;
					BYTE	*d=bmpdata[Y];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						if(0<=X && X<xbyte)
							d[X] |= ~MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						if(0<=X && X<xbyte)
							d[X]=0xFF;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						if(0<=X && X<xbyte)
							d[X] |= ~MInfo->AndMask3;
					}
				}
			}
			for(int xb=xbyte-MerginByte;xb<xbyte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
				struct	ShrinkingActionData	&M=PTable.MaskData[((unsigned short)(~Index))&0xFF];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					int	Y=y-Numb+i;
					if(Y<0 || YLenDot<=Y)
						continue;
					BYTE	*d=bmpdata[Y];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						if(0<=X && X<xbyte)
							d[X] |= ~MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						if(0<=X && X<xbyte)
							d[X]=0xFF;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						if(0<=X && X<xbyte)
							d[X] |= ~MInfo->AndMask3;
					}
				}
			}
		}
		for(int y=Numb;y<YLenDot-Numb-2;y++){
			for(int xb=MerginByte;xb<xbyte-MerginByte;xb++){
				unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
				struct	ShrinkingActionData	&M=PTable.MaskData[((unsigned short)(~Index))&0xFF];
				ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
				for(int i=0;i<M.MaskNumb;i++,MInfo++){
					BYTE	*d=bmpdata[y-Numb+i];
					int		Counter1=MInfo->MaskCount1;
					int		X=xb+MInfo->OffsetX;
					if(Counter1>0){
						d[X] |= ~MInfo->AndMask1;
						X++;
					}
					int		Counter2=MInfo->MaskCount2;
					for(int k=0;k<Counter2;k++){
						d[X]=0xFF;
						X++;
					}
					int		Counter3=MInfo->MaskCount3;
					if(Counter3>0){
						d[X] |= ~MInfo->AndMask3;
					}
				}
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int r=0;r<N;r++){
			//for(int r=0;r<N;r++){
				int	y=r;
				for(int xb=0;xb<MerginByte && xb<xbyte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
					struct	ShrinkingActionData	&M=PTable.MaskData[((unsigned short)(~Index))&0xFF];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=0;i<M.MaskNumb;i++,MInfo++){
						int	Y=y-Numb+i;
						if(Y<0 || YLenDot<=Y)
							continue;
						BYTE	*d=bmpdata[Y];
						int		Counter1=MInfo->MaskCount1;
						int		X=xb+MInfo->OffsetX;
						if(Counter1>0){
							if(0<=X && X<xbyte)
								d[X] |= ~MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						for(int k=0;k<Counter2;k++){
							if(0<=X && X<xbyte)
								d[X]=0xFF;
							X++;
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							if(0<=X && X<xbyte)
								d[X] |= ~MInfo->AndMask3;
						}
					}
				}
				for(int xb=xbyte-MerginByte;xb<xbyte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
					struct	ShrinkingActionData	&M=PTable.MaskData[((unsigned short)(~Index))&0xFF];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=0;i<M.MaskNumb;i++,MInfo++){
						int	Y=y-Numb+i;
						if(Y<0 || YLenDot<=Y)
							continue;
						BYTE	*d=bmpdata[Y];
						int		Counter1=MInfo->MaskCount1;
						int		X=xb+MInfo->OffsetX;
						if(Counter1>0){
							if(0<=X && X<xbyte)
								d[X] |= ~MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						for(int k=0;k<Counter2;k++){
							if(0<=X && X<xbyte)
								d[X]=0xFF;
							X++;
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							if(0<=X && X<xbyte)
								d[X] |= ~MInfo->AndMask3;
						}
					}
				}
			}
		}
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
			for(int r=0;r<N;r++){
				int	y=r+Numb;
				for(int xb=MerginByte;xb<xbyte-MerginByte;xb++){
					unsigned short	Index=(unsigned short)(bitoperation[y][xb]);
					struct	ShrinkingActionData	&M=PTable.MaskData[((unsigned short)(~Index))&0xFF];
					ShrinkingActionData::MaskInfo	*MInfo=M.Mask;
					for(int i=0;i<M.MaskNumb;i++,MInfo++){
						BYTE	*d=bmpdata[y-Numb+i];
						int		Counter1=MInfo->MaskCount1;
						int		X=xb+MInfo->OffsetX;
						if(Counter1>0){
							d[X] |= ~MInfo->AndMask1;
							X++;
						}
						int		Counter2=MInfo->MaskCount2;
						//for(int k=0;k<Counter2;k++){
						//	d[X]=0xFF;
						//	X++;
						//}
						
						switch(Counter2){
						case 0:	break;
						case 1:	d[X]=0xFF;	X++;	break;
						case 2:	*((WORD *)&d[X])=0xFFFF;	X+=2;	break;
						case 3:	*((WORD *)&d[X])=0xFFFF;	d[X+2]=0xFF;	X+=3;		break;
						case 4:	*((DWORD *)&d[X])=0xFFFFFFFFuL;	X+=4;	break;
						case 5:	*((DWORD *)&d[X])=0xFFFFFFFFuL;	d[X+4]=0xFF;	X+=5;		break;
						case 6:	*((DWORD *)&d[X])=0xFFFFFFFFuL;	*((WORD *)&d[X+4])=0xFFFF;	X+=6;		break;
						case 7:	*((DWORD *)&d[X])=0xFFFFFFFFuL;	*((WORD *)&d[X+4])=0xFFFF;	d[X+6]=0xFF;	X+=7;		break;
						case 8:	*((uint64*)&d[X])=0xFFFFFFFFFFFFFFFFuLL;	X+=8;		break;
						default:
							memset(&d[X],0xFF,Counter2);
							X+=Counter2;
						}
						int		Counter3=MInfo->MaskCount3;
						if(Counter3>0){
							d[X] |= ~MInfo->AndMask3;
						}
					}
				}
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
}
static	void	FatAreaN2(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
}
static	void	FatAreaN1(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,ShrinkingPack &PTable
				,FlexArea *ForceZone
				,bool EnableThread)
{
}
