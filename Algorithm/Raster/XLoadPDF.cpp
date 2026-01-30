/*
 * Copyright (C) 2022
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

#include <QBuffer>
#include <QString>
#include <omp.h>

#include "XRaster.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XRasterPacket.h"
#include "swap.h"
#include <omp.h>

#include "XFlexArea.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XGUIRasterPacket.h"
#include "XUndo.h"
#include "XCrossObj.h"
#include <float.h>
#include "XBitImageProcessor.h"

bool	RasterInPage::LoadPDF(RasterFileLayer *f,const QByteArray &Data)
{
	RasterPDFItem	*Item=new RasterPDFItem();
	Item->SetParent(this);
	FlexArea	Area;
	Area.SetRectangle(0,0,GetDotPerLine(),GetMaxLines());
	Item->SetArea(Area);
	AppendItem(Item);
	Item->LoadPDF(f,Data);

	return true;
}