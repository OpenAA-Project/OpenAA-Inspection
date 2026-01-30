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



#ifndef XGraphLibH
#define XGraphLibH
#include <QtGui>
#include "XGrobalData.h"
#include "XDataInLayer.h"



/*----------------------------------------------------------------------------*/
//  1.���{�ꖼ
//
//  2.�T�v
//
//  3.�@�\����
//
//  4.���l
//
/*----------------------------------------------------------------------------*/

class	MakeBitmapDataInLayer;


class  MakeBitmapDataInPage
{
public:
    ImageBuffer             *BuffLayer;
    int     Page;   //�f�[�^���̃y�[�W�i���z�y�[�W���܂ށj
                    //�|�P�̂Ƃ��A�y�[�W���肵�Ȃ�
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