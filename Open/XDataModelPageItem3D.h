/*
 * Copyright (C) 2025
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

#pragma once
#include "XDataModelPageItem.h"
#include "X3DCommon.h"
#include <QImage>

class	AlgorithmDrawAttr;

//=======================================================================================
class	AlgorithmItem3DPI : public AlgorithmItemPI
{
public:
	AlgorithmItem3DPI(void){}

	virtual	bool	GetColorForDraw(const Canvas3D &CInfo,AlgorithmDrawAttr *ModePoint
									,Point3D &CanvasPoint ,UVector3D &EyeLine
									,Reflection3D &RetReflection
									,Surface3D &RetSurface)	=0;

	virtual	bool	GetXYZ(Box3D &Area)=0;
};

class   AlgorithmInPage3DPI : public AlgorithmInPagePI
{
public:
	AlgorithmInPage3DPI(AlgorithmBase *parent);

	virtual	bool	GetColorForDraw(QImage &Img,const Canvas3D &CInfo,AlgorithmDrawAttr *ModePoint);
	QColor			MakeColor(const Reflection3D &R,const Surface3D &RetSurface);
};