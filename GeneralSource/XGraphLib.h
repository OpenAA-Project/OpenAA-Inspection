/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGraphLib.h
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
#ifndef XGraphLibH
#define XGraphLibH
/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
#include <QtGui>
#include "XGrobalData.h"
#include "XDataInLayer.h"



/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/

class	MakeBitmapDataInLayer;


class  MakeBitmapDataInPage
{
public:
    ImageBuffer             *BuffLayer;
    int     Page;   //データ上のページ（仮想ページも含む）
                    //－１のとき、ページ判定しない
	int						OutlineOffsetX;
	int						OutlineOffsetY;
    int						OffsetX,OffsetY;
	MakeBitmapDataInLayer	*Parent;

	MakeBitmapDataInPage(void);

	void    SetMaster(void);
    void    SetLoaded(void);
};

class  MakeBitmapDataInLayer
{
public:
    DataInLayerAttrStruct   *BuffLayerAttr;
	MakeBitmapDataInPage	*BuffPage;

	int		MaxPages;
	int		LayerNumb;
	BYTE	*ColTable;

	MakeBitmapDataInLayer(void);
	~MakeBitmapDataInLayer(void);

	void	Set(int _MaxPages);

	void    SetMaster(void);
    void    SetLoaded(void);
};


class  MakeBitmapData
{
public:
	MakeBitmapDataInLayer	*GBuff;
    int                     BuffLayerNumb;

    MakeBitmapData(int MaxLayer ,int MaxPages);
    ~MakeBitmapData(void);

	void    SetMaster(void);
    void    SetLoaded(void);
};


void	MakeBitmap(QImage *m ,MakeBitmapData &Data
					,int bitmapx ,int bitmapy
					,int movx ,int movy ,double ZoomRate);
                            
void	DrawLine(QImage *m ,QRgb c ,int x1, int y1 ,int x2 ,int y2);
void	DrawBitArea(BYTE **Area ,int XLen, int XByte ,int YLen
					,QImage *canvas,QRgb c
					,int bitmapx ,int bitmapy
					,int movx ,int movy ,double ZoomRate
					,int OffsetX ,int OffsetY);
bool   CheckZoomRate(double ZoomRate);
bool   RCheckZoomRate(double ZoomRate);


#endif
