/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPointer.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XPointerH
#define XPointerH
//---------------------------------------------------------------------------
#include "NList.h"
#include "XTypeDef.h"
#include <QString>

#define AllocMemoryClusterY 100	//48

class	QImage;
class	QColor;

#define	IsNullPointer(v)	((v==NULL)?true:false)

#define	GetBmpBit(BmpMap,x,y)	((BmpMap[y])[(x)>>3]&(0x80>>((x)&7)))
#define	SetBmpBit1(BmpMap,x,y)	((BmpMap[y])[(x)>>3]|=(0x80>>((x)&7)))
#define	SetBmpBit0(BmpMap,x,y)	((BmpMap[y])[(x)>>3]&=~(0x80>>((x)&7)))

#define	GetBmpBitOnY(BmpMapOnY,x)	(BmpMapOnY[(x)>>3]&(0x80>>((x)&7)))
#define	SetBmpBitOnY1(BmpMapOnY,x)	(BmpMapOnY[(x)>>3]|=(0x80>>((x)&7)))
#define	SetBmpBitOnY0(BmpMapOnY,x)	(BmpMapOnY[(x)>>3]&=~(0x80>>((x)&7)))

void	SetBitLine1(BYTE *Point ,int BitPointX1, int BitPointX2);
void	SetBitLine0(BYTE *Point ,int BitPointX1, int BitPointX2);

void    InitialPointerBuff(void);
void    RemovePointerBuff(void *p);
void    AddPointerBuff(void *p);
void    ReleasePointerBuff(void);


BYTE    **MakeMatrixBuff(int x ,int y);
BYTE    **MakeMatrixBuff(int xlen ,int ylen,BYTE Buff[],int BuffSize);
void	DeleteMatrixBuff(BYTE **p,int y);
void	DeleteMatrixBuff(BYTE **p,BYTE Buff[],int y);

void    MatrixBuffClear	(BYTE **p ,BYTE d ,int x ,int y ,bool EnableThread=true);
void    MatrixBuffCopy	(BYTE **dst		,int dstX ,int dstY
						,const BYTE **src ,int srcX ,int srcY ,bool EnableThread=true);
void    MatrixBuffNotCopy(BYTE **dst		,int dstX ,int dstY
						,const BYTE **src ,int srcX ,int srcY ,bool EnableThread=true);
void    MatrixBuffAnd	(BYTE **dst ,const BYTE **src ,int XLen ,int YLen ,bool EnableThread=true);
void    MatrixBuffOr	(BYTE **dst ,const BYTE **src ,int XLen ,int YLen ,bool EnableThread=true);
void    MatrixBuffXor	(BYTE **dst ,const BYTE **src ,int XLen ,int YLen ,bool EnableThread=true);
void    MatrixBuffNot	(BYTE **dst ,int XLen ,int YLen ,bool EnableThread=true);
void    MatrixBuffNotAnd(BYTE **dst ,const BYTE **src ,int XLen ,int YLen ,bool EnableThread=true);

void    MatrixBuffBitOr	(BYTE **dst ,BYTE **src ,int XBitLen ,int YLen
						,int dx ,int dy ,bool EnableThread=true);
void    MatrixBuffBitAnd(BYTE **dst ,BYTE **src ,int XBitLen ,int YLen
						,int dx ,int dy ,bool EnableThread=true);

void    MatrixBuffBitOr	(BYTE **dst ,int XDstBitLen ,int YDstLen
						,BYTE **src ,int XSrcBitLen ,int YSrcLen
						,int dx ,int dy);
void    MatrixBuffBitAnd(BYTE **dst ,int XDstBitLen ,int YDstLen
						,BYTE **src ,int XSrcBitLen ,int YSrcLen
						,int dx ,int dy);

void    MatrixBuffBlockCopy(BYTE **dst		,int dstX ,int dstY
                          , const BYTE **src,int srcX ,int srcY
                          ,int minx, int miny ,int maxx ,int maxy
							 ,bool EnableThread=true);
void    MatrixBuffBlockClear(BYTE **dst ,int dstX ,int dstY
                            ,int minx, int miny ,int maxx ,int maxy
							 ,bool EnableThread=true);

void    MatrixBuffAndBlock	(BYTE **dst ,const BYTE **src ,int XLen ,int YLen
							 ,int minx, int miny ,int maxx ,int maxy
							  ,bool EnableThread=true);
void    MatrixBuffOrBlock	(BYTE **dst ,const BYTE **src ,int XLen ,int YLen
							 ,int minx, int miny ,int maxx ,int maxy
							  ,bool EnableThread=true);
void    MatrixBuffNotBlock	(BYTE **dst ,int XLen ,int YLen
							 ,int minx, int miny ,int maxx ,int maxy
							  ,bool EnableThread=true);

bool	GetMatrixBitZone(BYTE **Src,int XByte ,int YLen
						 ,int &X1,int &Y1,int &X2,int &Y2);
bool	HasBitInMatrixZone(BYTE **Src,int XByte ,int YLen
						 ,int X1,int Y1,int X2,int Y2);
void    MatrixBuffShiftBitCopy	(BYTE **dst		  ,int dstBitX ,int dstY
								,const BYTE **src ,int srcBitX ,int srcY
								,int ShiftX ,int ShiftY);

int64	GetBitCount(const BYTE **src ,int XByte ,int YLen);
void    MatrixBuffPickupFromWindow  (BYTE **dst	,int dstBitX ,int dstY
									,BYTE **src ,int srcBitX ,int srcY
									,int SrcX1,int SrcY1,int SrcX2,int SrcY2);

void	SavePNGFileByte(const QString &FileName ,BYTE **const src ,int XLen  ,int YLen);
void	SavePNGFileBit (const QString &FileName ,BYTE **const src ,int XByte ,int YLen);
void	SaveBmpFileByte(const QString &FileName ,BYTE **const src ,int XLen  ,int YLen);
void	SaveBmpFileBit (const QString &FileName ,BYTE **const src ,int XByte ,int YLen);

void	memBitcpy(BYTE **dst , QImage &SrcImage ,int XByte ,int YLen ,const QColor &Col);
void	memBitcpy(QImage &DstImage ,BYTE **src , int XByte ,int YLen ,const QColor &Col);

void	GetGravityCenter(BYTE **dst  ,int dstBitX ,int dstY
						,double &cx ,double &cy);
void	MakeImage(QImage &DstImage ,BYTE **src[3],int dstXLen ,int dstYLen);



#endif
 
