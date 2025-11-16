/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPointer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
//---------------------------------------------------------------------------
#include <cmath>
#include "XPointer.h"
#include <memory.h>
#include <QMessageBox>
#include <QImage>
#include "swap.h"
#include <omp.h>
//---------------------------------------------------------------------------

BYTE    **  MakeMatrixBuff(int x ,int y)
{
    BYTE    **p=NULL;
    try{
        p=new BYTE*[y];
        for(int i=0;i<y;i++){
            p[i]=NULL;
            }
        for(int i=0;i<y;){
            int needY=AllocMemoryClusterY;
			if((i+needY)>y){
                needY=y-i;
			}
            BYTE    *q=new BYTE[x*needY];
            for(int k=0;k<needY;k++,i++){
                p[i]=q;
                q+=x;
                }
            }
        return(p);
        }
    catch(...){
		QMessageBox( "エラー"
					, "メモリーが確保できません"
					, QMessageBox::NoIcon
					, QMessageBox::Ok
					, QMessageBox::NoButton, QMessageBox::NoButton).exec();
        DeleteMatrixBuff(p,y);
        return(NULL);
        }
}

BYTE    **  MakeMatrixBuff(int xlen ,int ylen,BYTE Buff[],int BuffSize)
{
	if((xlen*ylen+ylen*((int)sizeof(BYTE **)))<BuffSize){
		BYTE	**YIndex=(BYTE	**)Buff;
		BYTE	*p= &Buff[ylen*sizeof(BYTE **)];
		for(int y=0;y<ylen;y++){
			YIndex[y]=p;
			p+=xlen;
		}
		return YIndex;
	}
	else{
		return MakeMatrixBuff(xlen,ylen);
	}
}
static	int	MatrixError=0;
void	DeleteMatrixBuff(BYTE **p,int y)
{
    if(p!=NULL){
        for(int i=0;i<y;i++){
            if((i%AllocMemoryClusterY)==0){
                if(p[i]!=NULL){
                    delete  []p[i];
					p[i]=NULL;
                }
				else{
					MatrixError++;
				}
            }
        }
        delete  []p;
    }
}

void	DeleteMatrixBuff(BYTE **p,BYTE Buff[],int y)
{
	if(p==(BYTE **)Buff)
		return;
	DeleteMatrixBuff(p,y);
}

void      MatrixBuffClear(BYTE **p ,BYTE d ,int x ,int y ,bool EnableThread)
{
    if(p!=NULL){
		if((y<8) || (x<64) || EnableThread==false){
			switch(x){
			case 0:	return;
			case 1:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*p[i]=0;
					}
				}
				return;
			case 2:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((unsigned short *)p[i])=0;
					}
				}
				return;
			case 3:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((unsigned short *)p[i])=0;
						*(p[i]+2)=0;
					}
				}
				return;
			case 4:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((DWORD *)p[i])=0;
					}
				}
				return;
			case 5:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((DWORD *)p[i])=0;
						*(p[i]+4)=0;
					}
				}
				return;
			case 6:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((DWORD *)p[i])=0;
						*((unsigned short *)(p[i]+4))=0;
					}
				}
				return;
			case 7:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((DWORD *)p[i])=0;
						*((unsigned short *)(p[i]+4))=0;
						*(p[i]+6)=0;
					}
				}
				return;
			case 8:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((QWORD *)p[i])=0;
					}
				}
				return;
			case 9:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((QWORD *)p[i])=0;
						*(p[i]+8)=0;
					}
				}
				return;
			case 10:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((QWORD *)p[i])=0;
						*((unsigned short *)(p[i]+8))=0;
					}
				}
				return;
			case 11:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((QWORD *)p[i])=0;
						*((unsigned short *)(p[i]+8))=0;
						*(p[i]+10)=0;
					}
				}
				return;
			case 12:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((QWORD *)p[i])=0;
						*((DWORD *)(p[i]+8))=0;
					}
				}
				return;
			case 13:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((QWORD *)p[i])=0;
						*((DWORD *)(p[i]+8))=0;
						*(p[i]+12)=0;
					}
				}
				return;
			case 14:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((QWORD *)p[i])=0;
						*((DWORD *)(p[i]+8))=0;
						*((unsigned short *)(p[i]+12))=0;
					}
				}
				return;
			case 15:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((QWORD *)p[i])=0;
						*((DWORD *)(p[i]+8))=0;
						*((unsigned short *)(p[i]+12))=0;
						*(p[i]+14)=0;
					}
				}
				return;
			case 16:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						*((QWORD *)p[i])=0;
						*((QWORD *)(p[i]+8))=0;
					}
				}
				return;
			default:
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						memset(p[i],d,x);
					}
				}
			}
		}
		else{
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int i=0;i<y;i++){
					if(p[i]!=NULL){
						memset(p[i],d,x);
					}
				}
			}
		}
	}
}

static	BYTE	BitMask1[]={ 0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01	};
static	BYTE	BitMask2[]={ 0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF	};

void	SetBitLine1(BYTE *Point ,int x1, int x2)
{
	if(x1>x2)
		return;
	if(x1<0)
		x1=0;
	int	Xp1=x1>>3;
	int	Xp2=x2>>3;
	int	BitN1=x1&7;
	int	BitN2=x2&7;
	if(Xp1==Xp2){
		Point[Xp1] |= BitMask1[BitN1] & BitMask2[BitN2];
	}
	else{
		Point[Xp1] |= BitMask1[BitN1];
		for(int x=Xp1+1;x<Xp2;x++){
			Point[x]=0xFF;
		}
		Point[Xp2] |=BitMask2[BitN2];
	}
}
void	SetBitLine0(BYTE *Point ,int x1, int x2)
{
	if(x1>x2)
		return;
	if(x1<0)
		x1=0;
	int	Xp1=x1>>3;
	int	Xp2=x2>>3;
	int	BitN1=x1&7;
	int	BitN2=x2&7;
	if(Xp1==Xp2){
		Point[Xp1] &= ~(BitMask1[BitN1] & BitMask2[BitN2]);
	}
	else{
		Point[Xp1] &= ~(BitMask1[BitN1]);
		for(int x=Xp1+1;x<Xp2;x++){
			Point[x]=0x00;
		}
		Point[Xp2] &=~(BitMask2[BitN2]);
	}
}


void      MatrixBuffCopy(BYTE **dst			,int dstX ,int dstY
                       , const BYTE **src	,int srcX ,int srcY
					   ,bool EnableThread)
{
    if(dst!=NULL && src!=NULL){
        int y=min(dstY,srcY);
        int x=min(dstX,srcX);
		if((y<8) || (x<64) || EnableThread==false){
			switch(x){
			case 0:	return;
			case 1:
				for(int i=0;i<y;i++){
					*dst[i]=*src[i];
				}
				return;
			case 2:
				for(int i=0;i<y;i++){
					*((WORD *)dst[i])=*((WORD *)src[i]);
				}
				return;
			case 3:
				for(int i=0;i<y;i++){
					*((WORD *)dst[i])=*((WORD *)src[i]);
					*(dst[i]+2)=*(src[i]+2);
				}
				return;
			case 4:
				for(int i=0;i<y;i++){
					*((DWORD *)dst[i])=*((DWORD *)src[i]);
				}
				return;
			case 5:
				for(int i=0;i<y;i++){
					*((DWORD *)dst[i])=*((DWORD *)src[i]);
					*(dst[i]+4)=*(src[i]+4);
				}
				return;
			case 6:
				for(int i=0;i<y;i++){
					*((DWORD *)dst[i])=*((DWORD *)src[i]);
					*((WORD *)(dst[i]+4))=*((WORD *)(src[i]+4));
				}
				return;
			case 7:
				for(int i=0;i<y;i++){
					*((DWORD *)dst[i])=*((DWORD *)src[i]);
					*((WORD *)(dst[i]+4))=*((WORD *)(src[i]+4));
					*(dst[i]+6)=*(src[i]+6);
				}
				return;
			case 8:
				for(int i=0;i<y;i++){
					*((QWORD *)dst[i])=*((QWORD *)src[i]);
				}
				return;
			default:
				for(int i=0;i<y;i++){
					memcpy(dst[i],src[i],x);
				}
			}
		}
		else{
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int i=0;i<y;i++){
					memcpy(dst[i],src[i],x);
				}
            }
        }
	}
}

void      MatrixBuffNotCopy(BYTE **dst			,int dstX ,int dstY
							, const BYTE **src	,int srcX ,int srcY
							,bool EnableThread)
{
    if(dst!=NULL && src!=NULL){
        int yn=min(dstY,srcY);
        int xn=min(dstX,srcX);
		if((yn<8) || (xn<16) || EnableThread==false){
			for(int y=0;y<yn;y++){
				int	xn8=xn>>3;
				int	x=0;
				uint64	*s1=(uint64	*)&src[y][0];
				uint64	*d1=(uint64	*)&dst[y][0];
				for(x=0;x<xn8;x++){
					d1[x]=~s1[x];
				}
				x<<=3;
				if((xn&0x4)!=0){
					*(uint32 *)&dst[y][x]=~*(uint32 *)&src[y][x];
					x+=4;
				}
				if((xn&0x2)!=0){
					*(ushort *)&dst[y][x]=~*(ushort *)&src[y][x];
					x+=2;
				}
				if((xn&0x1)!=0){
					dst[y][x]=~src[y][x];
					x+=1;
				}
			}
		}
		else{
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<yn;y++){
					int	xn8=xn>>3;
					int	x=0;
					uint64	*s1=(uint64	*)&src[y][0];
					uint64	*d1=(uint64	*)&dst[y][0];
					for(x=0;x<xn8;x++){
						d1[x]=~s1[x];
					}
					x<<=3;
					if((xn&0x4)!=0){
						*(uint32 *)&dst[y][x]=~*(uint32 *)&src[y][x];
						x+=4;
					}
					if((xn&0x2)!=0){
						*(ushort *)&dst[y][x]=~*(ushort *)&src[y][x];
						x+=2;
					}
					if((xn&0x1)!=0){
						dst[y][x]=~src[y][x];
						x+=1;
					}
				}
            }
        }
	}
}
void	MatrixBuffBlockCopy(BYTE **dst		,int dstX ,int dstY
                          , const BYTE **src,int srcX ,int srcY
                          ,int minx, int miny ,int maxx ,int maxy
						  ,bool EnableThread)
{
    if(dst!=NULL && src!=NULL){
		if(minx<0){
            minx=0;
		}
		if((minx>dstX) || (minx>srcX)){
            return;
		}
		if(miny<0){
            miny=0;
		}
		if((miny>dstY) || (miny>srcY)){
            return;
		}
		if(maxx<0){
            return;
		}
		if(maxx>=dstX){
            maxx=dstX-1;
		}
		if(maxx>=srcX){
            maxx=srcX-1;
		}
		if(maxy<0){
            return;
		}
		if(maxy>=dstY){
            maxy=dstY-1;
		}
		if(maxy>=srcY){
            maxy=srcY-1;
		}

        int xlen=maxx-minx;
		if(xlen<32 || EnableThread==false){
			for(int y=miny;y<maxy;y++){
				memcpy(&dst[y][minx],&src[y][minx],xlen);
			}
		}
		else{
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=miny;y<maxy;y++){
					memcpy(&dst[y][minx],&src[y][minx],xlen);
				}
            }
        }
	}
}
void    MatrixBuffBlockClear(BYTE **dst ,int dstX ,int dstY
                           ,int minx, int miny ,int maxx ,int maxy
						   ,bool EnableThread)
{
    if(dst!=NULL){
		if(minx<0){
            minx=0;
		}
		if(minx>dstX){
            return;
		}
		if(miny<0){
            miny=0;
		}
		if(miny>dstY){
            return;
		}
		if(maxx<0){
            return;
		}
		if(maxx>=dstX){
            maxx=dstX-1;
		}
		if(maxy<0){
            return;
		}
		if(maxy>=dstY){
            maxy=dstY-1;
		}

        int xlen=maxx-minx;
		int	ylen=maxy-miny;
		if((ylen<4) || (xlen<16) || EnableThread==false){
			for(int y=miny;y<maxy;y++){
				memset(&dst[y][minx],0,xlen);
			}
		}
		else{
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=miny;y<maxy;y++){
					memset(&dst[y][minx],0,xlen);
				}
            }
        }
	}
}
void    MatrixBuffAnd(BYTE **dst ,const BYTE **src ,int XLen ,int YLen ,bool EnableThread)
{
	if(XLen<=0 || YLen<=0)
		return;
	int	XLenQWord=XLen>>3;
	int	XLen8	 =XLen&7;
	if(XLenQWord>32 && YLen>=16 && EnableThread==true){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				int64	*sq=(int64 *)src[y];
				int64	*dq=(int64 *)dst[y];
				for(int x=0;x<XLenQWord;x++,sq++,dq++){
					*dq &= *sq;
				}

				BYTE	*s=(BYTE *)sq;
				BYTE	*d=(BYTE *)dq;
				for(int x=0;x<XLen8;x++,s++,d++){
					*d &= *s;
				}
			}
		}
	}
	else{
		for(int y=0;y<YLen;y++){
			int64	*sq=(int64 *)src[y];
			int64	*dq=(int64 *)dst[y];
			for(int x=0;x<XLenQWord;x++,sq++,dq++){
				*dq &= *sq;
			}

			BYTE	*s=(BYTE *)sq;
			BYTE	*d=(BYTE *)dq;
			for(int x=0;x<XLen8;x++,s++,d++){
				*d &= *s;
			}
		}
	}
}
void    MatrixBuffOr (BYTE **dst ,const BYTE **src ,int XLen ,int YLen ,bool EnableThread)
{
	if(XLen<=0 || YLen<=0)
		return;
	int	XLenQWord=XLen>>3;
	int	XLen8	 =XLen&7;
	if(XLenQWord>32 && YLen>=16 && EnableThread==true){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				int64	*sq=(int64 *)src[y];
				int64	*dq=(int64 *)dst[y];
				for(int x=0;x<XLenQWord;x++,sq++,dq++){
					*dq |= *sq;
				}

				BYTE	*s=(BYTE *)sq;
				BYTE	*d=(BYTE *)dq;
				for(int x=0;x<XLen8;x++,s++,d++){
					*d |= *s;
				}
			}
		}
	}
	else{
		for(int y=0;y<YLen;y++){
			int64	*sq=(int64 *)src[y];
			int64	*dq=(int64 *)dst[y];
			for(int x=0;x<XLenQWord;x++,sq++,dq++){
				*dq |= *sq;
			}

			BYTE	*s=(BYTE *)sq;
			BYTE	*d=(BYTE *)dq;
			for(int x=0;x<XLen8;x++,s++,d++){
				*d |= *s;
			}
		}
	}
}
void    MatrixBuffBitOr (BYTE **dst ,BYTE **src ,int XBitLen ,int YLen ,int dx ,int dy,bool EnableThread)
{
	int	MinY=max(0,dy)-dy;
	int	MaxY=min(YLen,YLen+dy)-dy;

	int	NLen=MaxY-MinY;
	int	XByte=(XBitLen>>3);
	int	TopBit;
	int	RBit;
	int	TopDestIndex;
	int	XByteLoopCount;
	int	MaxXByteLoopCount;
	if(dx>0){
		TopBit	=(dx)&7;
		RBit	=8-(dx&7);
		TopDestIndex=dx>>3;
		XByteLoopCount=(XBitLen>>3)-TopDestIndex-1;
		if(TopDestIndex+XByteLoopCount>(XBitLen>>3)){
			XByteLoopCount=(XBitLen>>3)-TopDestIndex;
		}
	}
	else{
		TopBit	=(-dx)&7;
		RBit	=8-((-dx)&7);
		TopDestIndex=(-dx)>>3;
		XByteLoopCount=(XBitLen>>3)-TopDestIndex-1;
		MaxXByteLoopCount=min((int)XByteLoopCount,(int)(XBitLen>>3)-1);
	}
	//#pragma omp parallel
	//{
	//	#pragma omp for
		for(int i=0;i<NLen;i++){
			int	y=MinY+i;
		//for(int y=MinY;y<MaxY;y++){
			BYTE	*s=(BYTE *)src[y];
			BYTE	*d=(BYTE *)dst[y+dy];

			if(dx>0){
				if(0<=TopDestIndex && TopDestIndex<XByte){
					d[TopDestIndex] |= (s[0]>>TopBit);
				}
				for(int x=1;x<XByteLoopCount;x++){
					d[TopDestIndex+x] |= (s[x]>>TopBit) + (s[x-1]<<RBit);
				}
			}
			else{
				for(int x=1;x<MaxXByteLoopCount;x++){
					d[x] |= (s[x+TopDestIndex]<<TopBit) + (s[x+TopDestIndex+1]>>RBit);
				}
				if(0<=MaxXByteLoopCount && MaxXByteLoopCount<XByte){
					d[MaxXByteLoopCount] |= (s[MaxXByteLoopCount+TopDestIndex]<<TopBit);
				}
			}
		}
	//}
}

void    MatrixBuffBitAnd(BYTE **dst ,BYTE **src ,int XBitLen ,int YLen ,int dx ,int dy ,bool EnableThread)
{
	int	MinY=max(0,dy)-dy;
	int	MaxY=min(YLen,YLen+dy)-dy;

	int	NLen=MaxY-MinY;
	int	XByte=(XBitLen>>3);

	int	TopBit;
	int	RBit;
	int	TopDestIndex;
	int	XByteLoopCount;
	int	MaxXByteLoopCount=0;
	if(dx>0){
		TopBit	=(dx)&7;
		RBit	=8-(dx&7);
		TopDestIndex=XByte;
		XByteLoopCount=XByte-TopDestIndex-1;
		if(TopDestIndex+XByteLoopCount>XByte){
			XByteLoopCount=XByte-TopDestIndex;
		}
	}
	else{
		TopBit	=(-dx)&7;
		RBit	=8-((-dx)&7);
		TopDestIndex=(-dx)>>3;
		XByteLoopCount=XByte-TopDestIndex-1;
		MaxXByteLoopCount=min((int)XByteLoopCount,(int)XByte-1);
		if(MaxXByteLoopCount+TopDestIndex>=XByte){
			MaxXByteLoopCount=XByte-TopDestIndex-1;
		}
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<NLen;i++){
			int	y=MinY+i;
		//for(int y=MinY;y<MaxY;y++){
			BYTE	*s=(BYTE *)src[y];
			BYTE	*d=(BYTE *)dst[y+dy];

			if(dx>0){
				if(0<=TopDestIndex && TopDestIndex<XByte){
					d[TopDestIndex] &= (s[0]>>TopBit);
				}
				for(int x=1;x<XByteLoopCount;x++){
					d[TopDestIndex+x] &= (s[x]>>TopBit) + (s[x-1]<<RBit);
				}
			}
			else{
				for(int x=1;x<MaxXByteLoopCount;x++){
					d[x] &= (s[x+TopDestIndex]<<TopBit) + (s[x+TopDestIndex+1]>>RBit);
				}
				if(0<=MaxXByteLoopCount && MaxXByteLoopCount<XByte){
					d[MaxXByteLoopCount] &= (s[MaxXByteLoopCount+TopDestIndex]<<TopBit);
				}
			}
		}
	}
}
void    MatrixBuffBitOr	(BYTE **dst ,int XDstBitLen ,int YDstLen
						,BYTE **src ,int XSrcBitLen ,int YSrcLen
						,int dx ,int dy)
{
	for(int y=0;y<YSrcLen;y++){
		int	Y=y+dy;
		if(Y<0)
			continue;
		if(Y>=YDstLen)
			break;
		BYTE	*s=src[y];
		BYTE	*d=dst[Y];
		for(int x=0;x<XSrcBitLen;x++){
			int	X=x+dx;
			if(X<0)
				continue;
			if(X>=XDstBitLen)
				break;
			if(GetBmpBitOnY(s,x)!=0)
				SetBmpBitOnY1(d,X);
		}
	}
}
void    MatrixBuffBitAnd(BYTE **dst ,int XDstBitLen ,int YDstLen
						,BYTE **src ,int XSrcBitLen ,int YSrcLen
						,int dx ,int dy)
{
	for(int y=0;y<YSrcLen;y++){
		int	Y=y+dy;
		if(Y<0)
			continue;
		if(Y>=YDstLen)
			break;
		BYTE	*s=src[y];
		BYTE	*d=dst[Y];
		for(int x=0;x<XSrcBitLen;x++){
			int	X=x+dx;
			if(X<0)
				continue;
			if(X>=XDstBitLen)
				break;
			if(GetBmpBitOnY(s,x)==0)
				SetBmpBitOnY0(d,X);
		}
	}
}

void    MatrixBuffXor (BYTE **dst ,const BYTE **src ,int XLen ,int YLen,bool EnableThread)
{
	if(XLen<=0 || YLen<=0)
		return;
	int	XLenQWord=XLen>>3;
	int	XLen8	 =XLen&7;
	if(XLenQWord>32 && YLen>=16 && EnableThread==true){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				int64	*sq=(int64 *)src[y];
				int64	*dq=(int64 *)dst[y];
				for(int x=0;x<XLenQWord;x++,sq++,dq++){
					*dq ^= *sq;
				}

				BYTE	*s=(BYTE *)sq;
				BYTE	*d=(BYTE *)dq;
				for(int x=0;x<XLen8;x++,s++,d++){
					*d ^= *s;
				}
			}
		}
	}
	else{
		for(int y=0;y<YLen;y++){
			int64	*sq=(int64 *)src[y];
			int64	*dq=(int64 *)dst[y];
			for(int x=0;x<XLenQWord;x++,sq++,dq++){
				*dq ^= *sq;
			}

			BYTE	*s=(BYTE *)sq;
			BYTE	*d=(BYTE *)dq;
			for(int x=0;x<XLen8;x++,s++,d++){
				*d ^= *s;
			}
		}
	}
}
void    MatrixBuffNot(BYTE **dst ,int XLen ,int YLen,bool EnableThread)
{
	if(XLen<=0 || YLen<=0)
		return;
	int	XLenQWord=XLen>>3;
	int	XLen8	 =XLen&7;
	if(XLenQWord>32 && YLen>=16 && EnableThread==true){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				int64	*dq=(int64 *)dst[y];
				for(int x=0;x<XLenQWord;x++,dq++){
					*dq = ~*dq;
				}
				BYTE	*d=(BYTE *)dq;
				for(int x=0;x<XLen8;x++,d++){
					*d = ~*d;
				}
			}
		}
	}
	else{
		for(int y=0;y<YLen;y++){
			int64	*dq=(int64 *)dst[y];
			for(int x=0;x<XLenQWord;x++,dq++){
				*dq = ~*dq;
			}
			BYTE	*d=(BYTE *)dq;
			for(int x=0;x<XLen8;x++,d++){
				*d = ~*d;
			}
		}
	}
}

void    MatrixBuffNotAnd(BYTE **dst ,const BYTE **src ,int XLen ,int YLen ,bool EnableThread)
{
	if(XLen<=0 || YLen<=0)
		return;
	int	XLenQWord=XLen>>3;
	int	XLen8	 =XLen&7;
	if(XLenQWord>32 && YLen>=16 && EnableThread==true){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				int64	*sq=(int64 *)src[y];
				int64	*dq=(int64 *)dst[y];
				for(int x=0;x<XLenQWord;x++,sq++,dq++){
					*dq &= ~*sq;
				}

				BYTE	*s=(BYTE *)sq;
				BYTE	*d=(BYTE *)dq;
				for(int x=0;x<XLen8;x++,s++,d++){
					*d &= ~*s;
				}
			}
		}
	}
	else{
		for(int y=0;y<YLen;y++){
			int64	*sq=(int64 *)src[y];
			int64	*dq=(int64 *)dst[y];
			for(int x=0;x<XLenQWord;x++,sq++,dq++){
				*dq &= ~*sq;
			}

			BYTE	*s=(BYTE *)sq;
			BYTE	*d=(BYTE *)dq;
			for(int x=0;x<XLen8;x++,s++,d++){
				*d &= ~*s;
			}
		}
	}
}

void    MatrixBuffAndBlock(BYTE **dst ,const BYTE **src ,int XLen ,int YLen
							,int minx, int miny ,int maxx ,int maxy
							,bool EnableThread)
{
	if(minx<0){
		minx=0;
	}
	if(maxx>XLen){
		maxx=XLen;
	}
	if(miny<0){
		miny=0;
	}
	if(maxy>YLen){
		maxy=YLen;
	}
	if(EnableThread==true){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=miny;y<maxy;y++){
				BYTE	*s=(BYTE *)src[y]+minx;
				BYTE	*d=(BYTE *)dst[y]+minx;
				for(int x=minx;x<maxx;x++,s++,d++){
					*d &= *s;
				}
			}
		}
	}
	else{
		for(int y=miny;y<maxy;y++){
			BYTE	*s=(BYTE *)src[y]+minx;
			BYTE	*d=(BYTE *)dst[y]+minx;
			for(int x=minx;x<maxx;x++,s++,d++){
				*d &= *s;
			}
		}
	}
}
void    MatrixBuffOrBlock (BYTE **dst ,const BYTE **src ,int XLen ,int YLen
							,int minx, int miny ,int maxx ,int maxy
							,bool EnableThread)
{
	if(minx<0){
		minx=0;
	}
	if(maxx>XLen){
		maxx=XLen;
	}
	if(miny<0){
		miny=0;
	}
	if(maxy>YLen){
		maxy=YLen;
	}
	if(EnableThread==true){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=miny;y<maxy;y++){
				BYTE	*s=(BYTE *)src[y]+minx;
				BYTE	*d=(BYTE *)dst[y]+minx;
				for(int x=minx;x<maxx;x++,s++,d++){
					*d |= *s;
				}
			}
		}
	}
	else{
		for(int y=miny;y<maxy;y++){
			BYTE	*s=(BYTE *)src[y]+minx;
			BYTE	*d=(BYTE *)dst[y]+minx;
			for(int x=minx;x<maxx;x++,s++,d++){
				*d |= *s;
			}
		}
	}
}
void    MatrixBuffNotBlock(BYTE **dst ,int XLen ,int YLen
							,int minx, int miny ,int maxx ,int maxy
							,bool EnableThread)
{
	if(minx<0){
		minx=0;
	}
	if(maxx>XLen){
		maxx=XLen;
	}
	if(miny<0){
		miny=0;
	}
	if(maxy>YLen){
		maxy=YLen;
	}
	if(EnableThread==true){
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int y=miny;y<maxy;y++){
				BYTE	*d=(BYTE *)dst[y]+minx;
				for(int x=minx;x<maxx;x++,d++){
					*d = ~*d;
				}
			}
		}
	}
	else{
		for(int y=miny;y<maxy;y++){
			BYTE	*d=(BYTE *)dst[y]+minx;
			for(int x=minx;x<maxx;x++,d++){
				*d = ~*d;
			}
		}
	}
}

static	int	SearchTop(BYTE **Src,int XByte ,int YLen)
{
	for(int y=0;y<YLen;y++){
		BYTE	*s=Src[y];
		for(int x=0;x<XByte;x++){
			if(s[x]!=0){
				return y;
			}
		}
	}
	return YLen;
}
static	int	SearchBottom(BYTE **Src,int XByte ,int YLen)
{
	for(int y=YLen-1;y>=0;y--){
		BYTE	*s=Src[y];
		for(int x=0;x<XByte;x++){
			if(s[x]!=0){
				return y;
			}
		}
	}
	return -1;
}

static	int	SearchLeft(BYTE **Src,int XByte ,int YLen)
{
	for(int xb=0;xb<XByte;xb++){
		for(int y=0;y<YLen;y++){
			BYTE	*s=Src[y];
			if(s[xb]!=0){
				for(int x=0;x<8;x++){
					if((s[xb] & (0x80>>(x&7)))!=0){
						return xb*8+x;
					}
				}
			}
		}
	}
	return XByte*8;
}
static	int	SearchRight(BYTE **Src,int XByte ,int YLen)
{
	for(int xb=XByte-1;xb>=0;xb--){
		for(int y=0;y<YLen;y++){
			BYTE	*s=Src[y];
			if(s[xb]!=0){
				for(int x=7;x>=0;x--){
					if((s[xb] & (0x80>>(x&7)))!=0){
						return xb*8+x;
					}
				}
			}
		}
	}
	return -1;
}

bool	GetMatrixBitZone(BYTE **Src,int XByte ,int YLen
						,int &X1,int &Y1,int &X2,int &Y2)
{
	Y1=SearchTop(Src,XByte ,YLen);
	X1=SearchLeft(Src,XByte ,YLen);
	X2=SearchRight(Src,XByte ,YLen);
	Y2=SearchBottom(Src,XByte ,YLen);
	if((Y1==YLen) && (X1==XByte*8) && X2==-1 && Y2==-1){
		return false;
	}
	return true;
}
bool	HasBitInMatrixZone(BYTE **Src,int XByte ,int YLen
						 ,int X1,int Y1,int X2,int Y2)
{
	if(X1<0)
		X1=0;
	if(Y1<0)
		Y1=0;
	if(Y2>=YLen)
		Y2=YLen-1;
	if(X2>=(XByte<<3))
		X2=(XByte<<3)-1;
	if(X1>X2 || Y1>Y2)
		return false;

	int	LeftBit=8-(X1&7);
	BYTE	LeftMask=0xFF<<LeftBit;
	LeftMask =~LeftMask;
	int	RightBit=((X2+1)&7);
	BYTE	RightMask=0xFF>>RightBit;
	RightMask=~RightMask;
	int	XLen=X2-X1+1 - LeftBit - RightBit;
	int	X2Point=(X2+1)>>3;
	if(RightBit==0){
		RightMask=0xFF;
		XLen--;
		X2Point--;
	}
	if(XLen>=0){
		int	RepeatN=XLen>>3;
		int	FirstPoint=(X1+LeftBit)>>3;
		int	X1Point=X1>>3;
		
		for(int y=Y1;y<=Y2 && y<YLen;y++){
			BYTE	*s=Src[y];
			if((s[X1Point]&LeftMask)!=0)
				return true;
			for(int x=0;x<RepeatN;x++){
				if((s[FirstPoint+x])!=0)
					return true;
			}
			if((s[X2Point]&RightMask)!=0)
				return true;
		}
	}
	else{
		int	X1Point=X1>>3;
		BYTE	BMask=LeftMask&RightMask;
		for(int y=Y1;y<=Y2 && y<YLen;y++){
			if(((Src[y])[X1Point]&BMask)!=0)
				return true;
		}
	}
	return false;
}

int64		GetBitCount(const BYTE **src ,int XByte ,int YLen)
{
	static	int		BitTable[256];
	static	bool	CreatedTable=false;

	if(CreatedTable==false){
		for(int i=0;i<256;i++){
			BitTable[i]= ((i>>0)&0x01)
						+((i>>1)&0x01)
						+((i>>2)&0x01)
						+((i>>3)&0x01)
						+((i>>4)&0x01)
						+((i>>5)&0x01)
						+((i>>6)&0x01)
						+((i>>7)&0x01);
		}
		CreatedTable=true;
	}
	int64	DotCount=0;
	for(int y=0;y<YLen;y++){
		const	BYTE	*s=src[y];
		for(int x=0;x<XByte;x++){
			int	n=s[x];
			DotCount+=BitTable[n];
		}
	}
	return DotCount;
}

void    MatrixBuffPickupFromWindow  (BYTE **dst	,int dstBitX ,int dstY
									,BYTE **src ,int srcBitX ,int srcY
									,int SrcX1,int SrcY1,int SrcX2,int SrcY2)
{
	for(int y=max(0,SrcY1);y<SrcY2;y++){
		if(y>=srcY)
			break;
		int	Dy=y-SrcY1;
		if(Dy<0 || Dy>=dstY)
			continue;
		BYTE	*s=src[y];
		BYTE	*d=dst[Dy];
		for(int x=max(SrcX1,0);x<SrcX2;x++){
			if(x>=srcBitX)
				break;
			int	Dx=x-SrcX1;
			if(Dx<0 || Dx>=dstBitX)
				continue;
			if(GetBmpBitOnY(s,x)!=0)
				SetBmpBitOnY1(d,Dx);
			else
				SetBmpBitOnY0(d,Dx);
		}
	}
}

void    MatrixBuffShiftBitCopy	(BYTE **dst		  ,int dstBitX ,int dstY
								,const BYTE **src ,int srcBitX ,int srcY
								,int ShiftX ,int ShiftY)
{
	for(int y=0;y<srcY;y++){
		int	Y=y+ShiftY;
		if(Y<0 || Y>=dstY)
			continue;
		const BYTE	*s=src[y];
		BYTE	*d=dst[y];
		for(int x=0;x<srcBitX;x++){
			int	X=x+ShiftX;
			if(X<0 || X>=dstBitX)
				continue;
			if(GetBmpBitOnY(s,x)==0)
				SetBmpBitOnY0(d,X);
			else
				SetBmpBitOnY1(d,X);
		}
	}
}

void	SavePNGFileByte(const QString &FileName ,BYTE **const src ,int XLen ,int YLen)
{
	QImage	Img(XLen,YLen,QImage::Format_ARGB32);
	for(int y=0;y<YLen;y++){
		const BYTE	*s=src[y];
		QRgb	*d=(QRgb *)Img.scanLine(y);
		for(int x=0;x<XLen;x++){
			d[x]=qRgba(s[x],s[x],s[x],255);
		}
	}
	Img.save(FileName,"PNG");
}
void	SavePNGFileBit (const QString &FileName ,BYTE **const src ,int XByte ,int YLen)
{
	int	XLen=XByte*8;
	QImage	Img(XLen,YLen,QImage::Format_ARGB32);
	for(int y=0;y<YLen;y++){
		const BYTE	*s=src[y];
		QRgb	*d=(QRgb *)Img.scanLine(y);
		for(int x=0;x<XLen;x++){
			if(GetBmpBitOnY(s,x)!=0){
				d[x]=qRgba(255,255,255,255);
			}
			else{
				d[x]=qRgba(0,0,0,255);
			}
		}
	}
	Img.save(FileName,"PNG");
}

void	SaveBmpFileByte(const QString &FileName ,BYTE **const src ,int XLen ,int YLen)
{
	QImage	Img(XLen,YLen,QImage::Format_ARGB32);
	for(int y=0;y<YLen;y++){
		const BYTE	*s=src[y];
		QRgb	*d=(QRgb *)Img.scanLine(y);
		for(int x=0;x<XLen;x++){
			d[x]=qRgba(s[x],s[x],s[x],255);
		}
	}
	Img.save(FileName,/**/"BMP");
}
void	SaveBmpFileBit (const QString &FileName ,BYTE **const src ,int XByte ,int YLen)
{
	int	XLen=XByte*8;
	QImage	Img(XLen,YLen,QImage::Format_ARGB32);
	for(int y=0;y<YLen;y++){
		const BYTE	*s=src[y];
		QRgb	*d=(QRgb *)Img.scanLine(y);
		for(int x=0;x<XLen;x++){
			if(GetBmpBitOnY(s,x)!=0){
				d[x]=qRgba(255,255,255,255);
			}
			else{
				d[x]=qRgba(0,0,0,255);
			}
		}
	}
	Img.save(FileName,/**/"BMP");
}

void	memBitcpy(BYTE **dst , QImage &SrcImage ,int XByte ,int YLen ,const QColor &Col)
{
	int	MXLen=min(XByte*8,SrcImage.width());
	int	MYLen=min(YLen,SrcImage.height());

	if(SrcImage.depth()==8){
		BYTE	C=Col.red();
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int y=0;y<MYLen;y++){
				BYTE	*s=SrcImage.scanLine(y);
				BYTE	*d=dst[y];
				for(int x=0;x<MXLen;x++){
					if(s[x]==C)
						SetBmpBitOnY1(d,x);
					else
						SetBmpBitOnY0(d,x);
				}
			}
		}
	}
	else if(SrcImage.depth()==24){
		BYTE	R=Col.red();
		BYTE	G=Col.green();
		BYTE	B=Col.blue();
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int y=0;y<MYLen;y++){
				BYTE	*s=SrcImage.scanLine(y);
				BYTE	*d=dst[y];
				for(int x=0;x<MXLen;x++){
					if(s[0]==R && s[1]==G && s[2]==B){
						SetBmpBitOnY1(d,x);
					}
					else{
						SetBmpBitOnY0(d,x);
					}
					s+=3;
				}
			}
		}
	}
	else if(SrcImage.depth()==32){
		QRgb	C=Col.rgba();
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int y=0;y<MYLen;y++){
				QRgb	*s=(QRgb *)SrcImage.scanLine(y);
				BYTE	*d=dst[y];
				for(int x=0;x<MXLen;x++){
					if(s[x]==C)
						SetBmpBitOnY1(d,x);
					else
						SetBmpBitOnY0(d,x);
				}
			}
		}
	}
}
void	memBitcpy(QImage &DstImage ,BYTE **src , int XByte ,int YLen ,const QColor &Col)
{
	int	MXLen=min(XByte*8,DstImage.width());
	int	MYLen=min(YLen,DstImage.height());

	if(DstImage.depth()==8){
		BYTE	C=Col.red();
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int y=0;y<MYLen;y++){
				BYTE	*s=src[y];
				BYTE	*d=DstImage.scanLine(y);
				for(int x=0;x<MXLen;x++){
					if(GetBmpBitOnY(s,x)!=0)
						d[x]=C;
					else
						d[x]=0;
				}
			}
		}
	}
	else if(DstImage.depth()==24){
		BYTE	R=Col.red();
		BYTE	G=Col.green();
		BYTE	B=Col.blue();
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int y=0;y<MYLen;y++){
				BYTE	*s=src[y];
				BYTE	*d=DstImage.scanLine(y);
				for(int x=0;x<MXLen;x++){
					if(GetBmpBitOnY(s,x)!=0){
						d[x  ]=R;
						d[x+1]=G;
						d[x+2]=B;
					}
					else{
						d[x  ]=0;
						d[x+1]=0;
						d[x+2]=0;
					}
				}
				d+=3;
			}
		}
	}
	else if(DstImage.depth()==32){
		QRgb	C=Col.rgba();
		QRgb	Black=Qt::black;
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int y=0;y<MYLen;y++){
				BYTE	*s=src[y];
				QRgb	*d=(QRgb *)DstImage.scanLine(y);
				for(int x=0;x<MXLen;x++){
					if(GetBmpBitOnY(s,x)!=0)
						d[x]=C;
					else
						d[x]=Black;
				}
			}
		}
	}
}


void	GetGravityCenter(BYTE **Src  ,int XByte ,int YLen
						,double &cx ,double &cy)
{
	double	AddedX=0.0;
	double	AddedY=0.0;
	double	N=0;
	for(int y=0;y<YLen;y++){
		BYTE	*s=Src[y];
		for(int x=0;x<XByte;x++){
			if(GetBmpBitOnY(s,x)!=0){
				AddedX+=x;
				AddedY+=y;
				N+=1.0;
			}
		}
	}
	if(N>0.0){
		cx=AddedX/N;
		cy=AddedY/N;
	}
}
void	MakeImage(QImage &DstImage ,BYTE **src[3],int dstXLen ,int dstYLen)
{
	if(DstImage.width()!=dstXLen || DstImage.height()!=dstYLen 
	|| (DstImage.format()!=QImage::Format_RGB32 && DstImage.format()!=QImage::Format_ARGB32)){
		DstImage=QImage(dstXLen,dstYLen,QImage::Format_RGB32);
	}
	int	LayerNumb=0;
	for(int layer=0;layer<3;layer++){
		if(src[layer]==NULL)
			break;
		LayerNumb++;
	}
	if(LayerNumb==1){
		for(int y=0;y<dstYLen;y++){
			QRgb *d=(QRgb *)DstImage.scanLine(y);
			BYTE	*s0=src[0][y];
			for(int x=0;x<dstXLen;x++){
				d[x]=qRgb(s0[x],s0[x],s0[x]);
			}
		}
	}
	else
	if(LayerNumb==2){
		for(int y=0;y<dstYLen;y++){
			QRgb *d=(QRgb *)DstImage.scanLine(y);
			BYTE	*s0=src[0][y];
			BYTE	*s1=src[1][y];
			for(int x=0;x<dstXLen;x++){
				d[x]=qRgb(s0[x],s0[x],s1[x]);
			}
		}
	}
	else
	if(LayerNumb==3){
		for(int y=0;y<dstYLen;y++){
			QRgb *d=(QRgb *)DstImage.scanLine(y);
			BYTE	*s0=src[0][y];
			BYTE	*s1=src[1][y];
			BYTE	*s2=src[2][y];
			for(int x=0;x<dstXLen;x++){
				d[x]=qRgb(s0[x],s1[x],s2[x]);
			}
		}
	}
}