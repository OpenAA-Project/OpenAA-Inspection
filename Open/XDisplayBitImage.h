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



#if	!defined(XDISPLAYBITIMAGE_H)
#define	XDISPLAYBITIMAGE_H

#include <QImage>
#include <QColor>
#include "XTypeDef.h"

void	DrawBitImage(QImage &Pnt, const BYTE **Src ,int XLen ,int XByte ,int YLen
					,int movx ,int movy ,double ZoomRate
					,int OffsetX ,int OffsetY
					,const QColor &Col);

void	DrawBitImageOr(QImage &Pnt, const BYTE **Src ,int XLen ,int XByte ,int YLen
					,int movx ,int movy ,double ZoomRate
					,int OffsetX ,int OffsetY
					,const QColor &Col);
#endif