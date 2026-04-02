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

#if	!defined(XINTERPOLATION_H)
#define	XINTERPOLATION_H

class ImageBuffer;
class FlexArea;
#include "XTypeDef.h"

void	InterpolateEllipse(ImageBuffer &Img , FlexArea &CircleArea
							,double &Cx,double &Cy
							,double &Rx,double &Ry
							,double Precision=0.001);
/*
	Interpolate ellipse from CircleArea in Img, and return center and radius of the ellipse.
*/

bool	MakeInterpolatedLine(double x[] ,double y[] ,int N
							 ,double &A,double &B,double &C);
/*
	Make interpolated line from N points (x[i],y[i]) , and return A,B,C of the line equation Ax+By+C=0.
*/

bool	AnalizeInterpolatedLine(double x[] ,double y[] ,int N
								 ,double A,double B,double C
								,double &RetMaxSeparation
								,double &RetVarietySeparatedDistanceFromLine
								,double RetStartPointOnLine[2]
								,double RetEndPointOnLine[2]);

#endif