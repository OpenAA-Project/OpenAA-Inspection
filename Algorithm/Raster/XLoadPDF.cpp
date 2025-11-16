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
