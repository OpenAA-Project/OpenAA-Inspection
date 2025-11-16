#include <mfapi.h>
#include "XLibWMF.h"
#include "LibWMFCamera.h"
#include "XCriticalFunc.h"

ConversionFunction gFormatConversions[] =
{
	{	MFVideoFormat_RGB32	, TransformImage_RGB32	,_EMT_RGB32	},
	{	MFVideoFormat_RGB24	, TransformImage_RGB24	,_EMT_RGB24	},
	{	MFVideoFormat_YUY2	, TransformImage_YUY2	,_EMT_YUY2	},
	{	MFVideoFormat_NV12	, TransformImage_NV12	,_EMT_NV12	},
	{	MFVideoFormat_MJPG	, TransformImage_MJPG	,_EMT_MJPG	},
	{	MFVideoFormat_Base	, NULL					,_EMT_None	}
};

static	DWORD	eLCTime[200];
static	int		eLCCounter=0;

void	SetTimeSpan(DWORD tt1)
{
	eLCTime[eLCCounter]=::GetComputerMiliSec()-tt1;
	eLCCounter++;
	if(eLCCounter>=sizeof(eLCTime)/sizeof(eLCTime[0]))
		eLCCounter=0;
}


__forceinline BYTE Clip(int aClr)
{
	return (BYTE)(aClr < 0 ? 0 : (aClr > 255 ? 255 : aClr));
}

__forceinline RGBQUAD ConvertYCrCbToRGB(
	int aY,
	int aCr,
	int aCb
	)
{
	RGBQUAD rgbq;

	int c = aY - 16;
	int d = aCb - 128;
	int e = aCr - 128;

	rgbq.rgbRed = Clip((298 * c + 409 * e + 128) >> 8);
	rgbq.rgbGreen = Clip((298 * c - 100 * d - 208 * e + 128) >> 8);
	rgbq.rgbBlue = Clip((298 * c + 516 * d + 128) >> 8);

	return rgbq;
}





void TransformImage_NV12(
	LibWMFCamera *Cam
	,ImageBuffer *Buff[]
	,const BYTE* aSrc
	,LONG        aSrcStride
	,DWORD       aWidthInPixels
	,DWORD       aHeightInPixels
	,DWORD		SrcTotalBuffByte
	,bool		MirrorX
	,bool		MirrorY
	,int		RotationAngle
	)
{
}
	/*
	const BYTE* bitsY = aSrc;
	const BYTE* bitsCb = bitsY + (aHeightInPixels * aSrcStride);
	const BYTE* bitsCr = bitsCb + 1;

	for (UINT y = 0; y < aHeightInPixels; y += 2)
	{
		const BYTE* lineY1 = bitsY;
		const BYTE* lineY2 = bitsY + aSrcStride;
		const BYTE* lineCr = bitsCr;
		const BYTE* lineCb = bitsCb;

		LPBYTE dibLine1 = aDst;
		LPBYTE dibLine2 = aDst + aDstStride;

		for (UINT x = 0; x < aWidthInPixels; x += 2)
		{
			int  y0 = (int)lineY1[0];
			int  y1 = (int)lineY1[1];
			int  y2 = (int)lineY2[0];
			int  y3 = (int)lineY2[1];
			int  cb = (int)lineCb[0];
			int  cr = (int)lineCr[0];

			RGBQUAD r = ConvertYCrCbToRGB(y0, cr, cb);
			dibLine1[0] = r.rgbBlue;
			dibLine1[1] = r.rgbGreen;
			dibLine1[2] = r.rgbRed;
			dibLine1[3] = 0; // Alpha

			r = ConvertYCrCbToRGB(y1, cr, cb);
			dibLine1[4] = r.rgbBlue;
			dibLine1[5] = r.rgbGreen;
			dibLine1[6] = r.rgbRed;
			dibLine1[7] = 0; // Alpha

			r = ConvertYCrCbToRGB(y2, cr, cb);
			dibLine2[0] = r.rgbBlue;
			dibLine2[1] = r.rgbGreen;
			dibLine2[2] = r.rgbRed;
			dibLine2[3] = 0; // Alpha

			r = ConvertYCrCbToRGB(y3, cr, cb);
			dibLine2[4] = r.rgbBlue;
			dibLine2[5] = r.rgbGreen;
			dibLine2[6] = r.rgbRed;
			dibLine2[7] = 0; // Alpha

			lineY1 += 2;
			lineY2 += 2;
			lineCr += 2;
			lineCb += 2;

			dibLine1 += 8;
			dibLine2 += 8;
		}

		aDst += (2 * aDstStride);
		bitsY += (2 * aSrcStride);
		bitsCr += aSrcStride;
		bitsCb += aSrcStride;
	}
}
*/

