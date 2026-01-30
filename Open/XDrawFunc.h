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

#if	!defined(XDRAWFUNC_H)
#define	XDRAWFUNC_H

#include <QPainter>
#include "XTypeDef.h"

void	DrawArrow(double StartX ,double StartY ,double EndX ,double EndY
				 ,QPainter &Pnt ,int movx ,int movy ,double ZoomRate ,int SizeOfArrowMark=10);

void	DrawArrow(double StartX ,double StartY ,double EndX ,double EndY
				 ,QPainter &Pnt ,int movx ,int movy ,double ZoomRate
				 ,int x1,int y1 ,int x2 ,int y2
				 ,int SizeOfArrowMark=10);

#endif
