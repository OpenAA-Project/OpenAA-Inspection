#include "XUSBCameraExecuter.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"
#include "swap.h"
#include <omp.h>

#include "jpeglib.h"
#include "turbojpeg.h"
#define JPEG_INTERNALS

void WMFCamera::TransformImage_RGB24(ImageBuffer *Buff[]
									,const BYTE* aSrc
									,DWORD		SrcTotalBuffByte)
{
	if((MirrorX==false && MirrorY==false && RotationAngle==0)
	|| (MirrorX==true && MirrorY==true && RotationAngle==180)){
		for (int y = 0; y < aHeightInPixels; y++){
			RGBTRIPLE *srcPel = (RGBTRIPLE*)aSrc;
			BYTE	*R=Buff[0]->GetY(y);
			BYTE	*G=Buff[1]->GetY(y);
			BYTE	*B=Buff[2]->GetY(y);

			for (DWORD x = 0; x < aWidthInPixels; x++){
				*R=srcPel[x].rgbtRed;
				*G=srcPel[x].rgbtGreen;
				*B=srcPel[x].rgbtBlue;
				R++;
				G++;
				B++;
			}
			aSrc += aSrcStride;
		}
	}
	else
	if(MirrorX==true && MirrorY==false && RotationAngle==0){
		for (int y = 0; y < aHeightInPixels; y++){
			RGBTRIPLE *srcPel = (RGBTRIPLE*)aSrc;
			BYTE	*R=Buff[0]->GetY(y)+Buff[0]->GetWidth()-1;
			BYTE	*G=Buff[1]->GetY(y)+Buff[1]->GetWidth()-1;
			BYTE	*B=Buff[2]->GetY(y)+Buff[2]->GetWidth()-1;

			for (DWORD x = 0; x < aWidthInPixels; x++){
				*R=srcPel[x].rgbtRed;
				*G=srcPel[x].rgbtGreen;
				*B=srcPel[x].rgbtBlue;
				R--;
				G--;
				B--;
			}
			aSrc += aSrcStride;
		}
	}
	else
	if(MirrorX==false && MirrorY==true && RotationAngle==0){
		for (int y = 0; y < aHeightInPixels; y++){
			RGBTRIPLE *srcPel = (RGBTRIPLE*)aSrc;
			BYTE	*R=Buff[0]->GetY(+Buff[0]->GetHeight()-1-y);
			BYTE	*G=Buff[1]->GetY(+Buff[1]->GetHeight()-1-y);
			BYTE	*B=Buff[2]->GetY(+Buff[2]->GetHeight()-1-y);

			for (DWORD x = 0; x < aWidthInPixels; x++){
				*R=srcPel[x].rgbtRed;
				*G=srcPel[x].rgbtGreen;
				*B=srcPel[x].rgbtBlue;
				R++;
				G++;
				B++;
			}
			aSrc += aSrcStride;
		}
	}
}

void WMFCamera::TransformImage_RGB32(ImageBuffer *Buff[]
									,const BYTE* aSrc
									,DWORD		SrcTotalBuffByte)
{
	if((MirrorX==false && MirrorY==false && RotationAngle==0)
	|| (MirrorX==true && MirrorY==true && RotationAngle==180)){
		for (int y = 0; y < aHeightInPixels; y++){
			const BYTE* LSrc=aSrc;
			BYTE	*R=Buff[0]->GetY(y);
			BYTE	*G=Buff[1]->GetY(y);
			BYTE	*B=Buff[2]->GetY(y);

			for (DWORD x = 0; x < aWidthInPixels; x++){
				*R=LSrc[x];
				*G=LSrc[x+1];
				*B=LSrc[x+2];
				R++;
				G++;
				B++;
				LSrc+=4;
			}
			aSrc += aSrcStride;
		}
	}
	else
	if(MirrorX==true && MirrorY==false && RotationAngle==0){
		for (int y = 0; y < aHeightInPixels; y++){
			const BYTE* LSrc=aSrc;
			BYTE	*R=Buff[0]->GetY(y)+Buff[0]->GetWidth()-1;
			BYTE	*G=Buff[1]->GetY(y)+Buff[1]->GetWidth()-1;
			BYTE	*B=Buff[2]->GetY(y)+Buff[2]->GetWidth()-1;

			for (DWORD x = 0; x < aWidthInPixels; x++){
				*R=LSrc[x];
				*G=LSrc[x+1];
				*B=LSrc[x+2];
				R--;
				G--;
				B--;
				LSrc+=4;
			}
			aSrc += aSrcStride;
		}
	}
	else
	if(MirrorX==false && MirrorY==true && RotationAngle==0){
		for (int y = 0; y < aHeightInPixels; y++){
			const BYTE* LSrc=aSrc;
			BYTE	*R=Buff[0]->GetY(+Buff[0]->GetHeight()-1-y);
			BYTE	*G=Buff[1]->GetY(+Buff[1]->GetHeight()-1-y);
			BYTE	*B=Buff[2]->GetY(+Buff[2]->GetHeight()-1-y);

			for (DWORD x = 0; x < aWidthInPixels; x++){
				*R=LSrc[x];
				*G=LSrc[x+1];
				*B=LSrc[x+2];
				R++;
				G++;
				B++;
				LSrc+=4;
			}
			aSrc += aSrcStride;
		}
	}
}

void WMFCamera::TransformImage_YUY2(ImageBuffer *Buff[]
									,const BYTE* aSrc
									,DWORD		SrcTotalBuffByte)
{
	if(MirrorX==false && MirrorY==false && RotationAngle==0){
		for(int y=0;y<aHeightInPixels;y++){
			BYTE	*sR=Buff[0]->GetY(y);
			BYTE	*sG=Buff[1]->GetY(y);
			BYTE	*sB=Buff[2]->GetY(y);
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				*sR = YClip255(( Y2 + 409 * V + 128) >> 8);
				*sG = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				*sB = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				*(sR+1) = YClip255(( Y4 + 409 * V + 128) >> 8);
				*(sG+1) = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				*(sB+1) = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
				sR+=2;
				sG+=2;
				sB+=2;
			}
		}
	}
	else
	if(MirrorX==false && MirrorY==false && RotationAngle==90){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetHeight());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetWidth());
		//int	YN=MinYLen&0xFFE0;
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<MinXLen;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				BYTE	*sR1=Buff[0]->GetY(x);
				BYTE	*sG1=Buff[1]->GetY(x);
				BYTE	*sB1=Buff[2]->GetY(x);
				sR1[YN-y-1] = YClip255(( Y2 + 409 * V + 128) >> 8);
				sG1[YN-y-1] = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				sB1[YN-y-1] = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				BYTE	*sR2=Buff[0]->GetY(x+1);
				BYTE	*sG2=Buff[1]->GetY(x+1);
				BYTE	*sB2=Buff[2]->GetY(x+1);
				sR2[YN-y-1]= YClip255(( Y4 + 409 * V + 128) >> 8);
				sG2[YN-y-1]= YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				sB2[YN-y-1]= YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
			}
		}
	}
	else
	if(MirrorX==false && MirrorY==false && RotationAngle==180){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetWidth());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetHeight());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			BYTE	*sR=&Buff[0]->GetY(YN-y-1)[MinXLen-1];
			BYTE	*sG=&Buff[1]->GetY(YN-y-1)[MinXLen-1];
			BYTE	*sB=&Buff[2]->GetY(YN-y-1)[MinXLen-1];
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				*sR = YClip255(( Y2 + 409 * V + 128) >> 8);
				*sG = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				*sB = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				*(sR-1) = YClip255(( Y4 + 409 * V + 128) >> 8);
				*(sG-1) = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				*(sB-1) = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
				sR-=2;
				sG-=2;
				sB-=2;
			}
		}
	}
	else
	if(MirrorX==false && MirrorY==false && RotationAngle==270){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetHeight());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetWidth());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				BYTE	*sR1=Buff[0]->GetY(MinXLen-x-1);
				BYTE	*sG1=Buff[1]->GetY(MinXLen-x-1);
				BYTE	*sB1=Buff[2]->GetY(MinXLen-x-1);
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				sR1[y] = YClip255(( Y2 + 409 * V + 128) >> 8);
				sG1[y] = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				sB1[y] = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				BYTE	*sR2=Buff[0]->GetY(MinXLen-x-2);
				BYTE	*sG2=Buff[1]->GetY(MinXLen-x-2);
				BYTE	*sB2=Buff[2]->GetY(MinXLen-x-2);
				sR2[y] = YClip255(( Y4 + 409 * V + 128) >> 8);
				sG2[y] = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				sB2[y] = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
			}
		}
	}

	else
	if(MirrorX==true && MirrorY==false && RotationAngle==0){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetWidth());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetHeight());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			BYTE	*sR=&Buff[0]->GetY(y)[MinXLen-1];
			BYTE	*sG=&Buff[1]->GetY(y)[MinXLen-1];
			BYTE	*sB=&Buff[2]->GetY(y)[MinXLen-1];
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				*sR = YClip255(( Y2 + 409 * V + 128) >> 8);
				*sG = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				*sB = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				*(sR-1) = YClip255(( Y4 + 409 * V + 128) >> 8);
				*(sG-1) = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				*(sB-1) = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
				sR-=2;
				sG-=2;
				sB-=2;
			}
		}
	}
	else
	if(MirrorX==true && MirrorY==false && RotationAngle==90){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetHeight());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetWidth());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<MinXLen;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				BYTE	*sR1=Buff[0]->GetY(x);
				BYTE	*sG1=Buff[1]->GetY(x);
				BYTE	*sB1=Buff[2]->GetY(x);
				sR1[y] = YClip255(( Y2 + 409 * V + 128) >> 8);
				sG1[y] = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				sB1[y] = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				BYTE	*sR2=Buff[0]->GetY(x+1);
				BYTE	*sG2=Buff[1]->GetY(x+1);
				BYTE	*sB2=Buff[2]->GetY(x+1);
				sR2[y]= YClip255(( Y4 + 409 * V + 128) >> 8);
				sG2[y]= YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				sB2[y]= YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
			}
		}
	}
	else
	if(MirrorX==true && MirrorY==false && RotationAngle==180){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetWidth());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetHeight());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			BYTE	*sR=Buff[0]->GetY(YN-y-1);
			BYTE	*sG=Buff[1]->GetY(YN-y-1);
			BYTE	*sB=Buff[2]->GetY(YN-y-1);
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				*sR = YClip255(( Y2 + 409 * V + 128) >> 8);
				*sG = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				*sB = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				*(sR+1) = YClip255(( Y4 + 409 * V + 128) >> 8);
				*(sG+1) = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				*(sB+1) = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
				sR+=2;
				sG+=2;
				sB+=2;
			}
		}
	}
	else
	if(MirrorX==true && MirrorY==false && RotationAngle==270){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetHeight());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetWidth());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				BYTE	*sR1=Buff[0]->GetY(MinXLen-x-1);
				BYTE	*sG1=Buff[1]->GetY(MinXLen-x-1);
				BYTE	*sB1=Buff[2]->GetY(MinXLen-x-1);
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				sR1[YN-1-y] = YClip255(( Y2 + 409 * V + 128) >> 8);
				sG1[YN-1-y] = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				sB1[YN-1-y] = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				BYTE	*sR2=Buff[0]->GetY(MinXLen-x-2);
				BYTE	*sG2=Buff[1]->GetY(MinXLen-x-2);
				BYTE	*sB2=Buff[2]->GetY(MinXLen-x-2);
				sR2[YN-1-y] = YClip255(( Y4 + 409 * V + 128) >> 8);
				sG2[YN-1-y] = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				sB2[YN-1-y] = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
			}
		}
	}

	else
	if(MirrorX==false && MirrorY==true && RotationAngle==0){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetWidth());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetHeight());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			BYTE	*sR=Buff[0]->GetY(YN-1-y);
			BYTE	*sG=Buff[1]->GetY(YN-1-y);
			BYTE	*sB=Buff[2]->GetY(YN-1-y);
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				*sR = YClip255(( Y2 + 409 * V + 128) >> 8);
				*sG = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				*sB = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				*(sR+1) = YClip255(( Y4 + 409 * V + 128) >> 8);
				*(sG+1) = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				*(sB+1) = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
				sR+=2;
				sG+=2;
				sB+=2;
			}
		}
	}
	else
	if(MirrorX==false && MirrorY==true && RotationAngle==90){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetHeight());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetWidth());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<MinXLen;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				BYTE	*sR1=Buff[0]->GetY(MinXLen-1-x);
				BYTE	*sG1=Buff[1]->GetY(MinXLen-1-x);
				BYTE	*sB1=Buff[2]->GetY(MinXLen-1-x);
				sR1[YN-y-1] = YClip255(( Y2 + 409 * V + 128) >> 8);
				sG1[YN-y-1] = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				sB1[YN-y-1] = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				BYTE	*sR2=Buff[0]->GetY(MinXLen-2-x);
				BYTE	*sG2=Buff[1]->GetY(MinXLen-2-x);
				BYTE	*sB2=Buff[2]->GetY(MinXLen-2-x);
				sR2[YN-y-1]= YClip255(( Y4 + 409 * V + 128) >> 8);
				sG2[YN-y-1]= YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				sB2[YN-y-1]= YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
			}
		}
	}
	else
	if(MirrorX==false && MirrorY==true && RotationAngle==180){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetWidth());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetHeight());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			BYTE	*sR=&Buff[0]->GetY(y)[MinXLen-1];
			BYTE	*sG=&Buff[1]->GetY(y)[MinXLen-1];
			BYTE	*sB=&Buff[2]->GetY(y)[MinXLen-1];
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				*sR = YClip255(( Y2 + 409 * V + 128) >> 8);
				*sG = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				*sB = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				*(sR-1) = YClip255(( Y4 + 409 * V + 128) >> 8);
				*(sG-1) = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				*(sB-1) = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
				sR-=2;
				sG-=2;
				sB-=2;
			}
		}
	}
	else
	if(MirrorX==false && MirrorY==true && RotationAngle==270){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetHeight());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetWidth());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				BYTE	*sR1=Buff[0]->GetY(x);
				BYTE	*sG1=Buff[1]->GetY(x);
				BYTE	*sB1=Buff[2]->GetY(x);
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				sR1[y] = YClip255(( Y2 + 409 * V + 128) >> 8);
				sG1[y] = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				sB1[y] = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				BYTE	*sR2=Buff[0]->GetY(x+1);
				BYTE	*sG2=Buff[1]->GetY(x+1);
				BYTE	*sB2=Buff[2]->GetY(x+1);
				sR2[y] = YClip255(( Y4 + 409 * V + 128) >> 8);
				sG2[y] = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				sB2[y] = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
			}
		}
	}

	else
	if(MirrorX==true && MirrorY==true && RotationAngle==0){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetWidth());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetHeight());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			BYTE	*sR=&Buff[0]->GetY(YN-1-y)[MinXLen-1];
			BYTE	*sG=&Buff[1]->GetY(YN-1-y)[MinXLen-1];
			BYTE	*sB=&Buff[2]->GetY(YN-1-y)[MinXLen-1];
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				*sR = YClip255(( Y2 + 409 * V + 128) >> 8);
				*sG = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				*sB = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				*(sR-1) = YClip255(( Y4 + 409 * V + 128) >> 8);
				*(sG-1) = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				*(sB-1) = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
				sR-=2;
				sG-=2;
				sB-=2;
			}
		}
	}
	else
	if(MirrorX==true && MirrorY==true && RotationAngle==90){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetHeight());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetWidth());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<MinXLen;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				BYTE	*sR1=Buff[0]->GetY(MinXLen-1-x);
				BYTE	*sG1=Buff[1]->GetY(MinXLen-1-x);
				BYTE	*sB1=Buff[2]->GetY(MinXLen-1-x);
				sR1[y] = YClip255(( Y2 + 409 * V + 128) >> 8);
				sG1[y] = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				sB1[y] = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				BYTE	*sR2=Buff[0]->GetY(MinXLen-2-x);
				BYTE	*sG2=Buff[1]->GetY(MinXLen-2-x);
				BYTE	*sB2=Buff[2]->GetY(MinXLen-2-x);
				sR2[y]= YClip255(( Y4 + 409 * V + 128) >> 8);
				sG2[y]= YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				sB2[y]= YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
			}
		}
	}
	else
	if(MirrorX==true && MirrorY==true && RotationAngle==180){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetWidth());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetHeight());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			BYTE	*sR=Buff[0]->GetY(y);
			BYTE	*sG=Buff[1]->GetY(y);
			BYTE	*sB=Buff[2]->GetY(y);
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				*sR = YClip255(( Y2 + 409 * V + 128) >> 8);
				*sG = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				*sB = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				*(sR+1) = YClip255(( Y4 + 409 * V + 128) >> 8);
				*(sG+1) = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				*(sB+1) = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
				sR+=2;
				sG+=2;
				sB+=2;
			}
		}
	}
	else
	if(MirrorX==true && MirrorY==true && RotationAngle==270){
		int	MinXLen=min((int)aWidthInPixels,Buff[0]->GetHeight());
		int	MinYLen=min((int)aHeightInPixels,Buff[0]->GetWidth());
		int	YN=MinYLen;	//&0xFFE0;
		for(int y=0;y<YN;y++){
			const	BYTE	*d=&aSrc[y*aSrcStride];
			for(int x=0;x<aWidthInPixels;x+=2){
				BYTE	*sR1=Buff[0]->GetY(x);
				BYTE	*sG1=Buff[1]->GetY(x);
				BYTE	*sB1=Buff[2]->GetY(x);
				int	Y2=298*(*(d+0)-16);
				int	U=*(d+1)-128;
				int	Y4=298*(*(d+2)-16);
				int	V=*(d+3)-128;

				sR1[YN-1-y] = YClip255(( Y2 + 409 * V + 128) >> 8);
				sG1[YN-1-y] = YClip255(( Y2 - 100 * U - 208 * V + 128) >> 8);
				sB1[YN-1-y] = YClip255(( Y2 + 516 * U + 128) >> 8);
                // Y4に対するピクセルのRGB
				BYTE	*sR2=Buff[0]->GetY(x+1);
				BYTE	*sG2=Buff[1]->GetY(x+1);
				BYTE	*sB2=Buff[2]->GetY(x+1);
				sR2[YN-1-y] = YClip255(( Y4 + 409 * V + 128) >> 8);
				sG2[YN-1-y] = YClip255(( Y4 - 100 * U - 208 * V + 128) >> 8);
				sB2[YN-1-y] = YClip255(( Y4 + 516 * U + 128) >> 8);

				d+=4;
			}
		}
	}

}

int	YClip16k(int n)	{	return (n<65536)?n:65535;	}

void	WMFCamera::MakeMonochrome(ImageBuffer *Buff[])
{
	int	Xn=Buff[0]->GetWidth();
	int	Yn=Buff[0]->GetHeight();
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<Yn;y++){
			BYTE	*sR=Buff[0]->GetY(y);
			BYTE	*sG=Buff[1]->GetY(y);
			BYTE	*sB=Buff[2]->GetY(y);
			for(int x=0;x<Xn;x++){
				//int	c=YClip255(*sR*0.3+*sG*0.59 + *sB*0.11);
				int	c=YClip16k(*sR*76+*sG*151+*sB*285)>>8;
				*sR=c;
				*sG=c;
				*sB=c;
				sR++;
				sG++;
				sB++;
			}
		}
	}
}


void WMFCamera::TransformImage_MJPG(ImageBuffer *Buff[]
									,const BYTE* aSrc
									,DWORD		SrcTotalBuffByte)
{
	int	width;
	int	height;
	int jpegSubsamp;
	int	jpegColorspace;
	int n1=tjDecompressHeader3(DecHndle
		,aSrc,SrcTotalBuffByte
		,&width
        ,&height
		,&jpegSubsamp
        ,&jpegColorspace);

	int	n2=tjDecompress2(DecHndle
		,aSrc,SrcTotalBuffByte
        ,MJPegTmpBuff
		,width,0,height
		,TJPF_RGB, TJFLAG_FASTDCT);


	/*
	static	bool	PSwotch=false;
	if(PSwotch==true){
		QFile	File("TestMJPG.jpg");
		File.open(QIODevice::WriteOnly);
		File.write((char *)CamData.Buffer,BuffSize);
	}
	*/
	if(n1==0 && n2==0){
		BYTE	*buffer = MJPegTmpBuff;
		int	XByte3=width*3;
		if(MirrorX==false && MirrorY==false && RotationAngle==0){
			int	MinXLen=min(width,Buff[0]->GetWidth());
			int	MinYLen=min(height,Buff[0]->GetHeight());
			int	YN=MinYLen;	//&0xFFE0;
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];

					BYTE	*d0=Buff[0]->GetY(y);
					BYTE	*d1=Buff[1]->GetY(y);
					BYTE	*d2=Buff[2]->GetY(y);
					for (int x = 0; x < MinXLen; x++){
						*d0 = *(row  );
						*d1 = *(row+1);
						*d2 = *(row+2);
						row+=3;
						d0++;
						d1++;
						d2++;
					}
				}
			//}
		}
		else
		if(MirrorX==false && MirrorY==false && RotationAngle==90){
			int	MinXLen=min(width,Buff[0]->GetHeight());
			int	MinYLen=min(height,Buff[0]->GetWidth());
			int	YN=MinYLen;	//&0xFFE0;
			if(Buff[0]->IsDepended()==true){
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					int	Y=YN-y-1;
					JSAMPROW row = &buffer[y*XByte3];
					for (int x = 0; x < MinXLen; x++){
						BYTE	*d0=Buff[0]->GetY(x);
						BYTE	*d1=Buff[1]->GetY(x);
						BYTE	*d2=Buff[2]->GetY(x);
						d0[Y] = *(row  );
						d1[Y] = *(row+1);
						d2[Y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
			else{
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					int	Y=YN-y-1;
					JSAMPROW row = &buffer[y*XByte3];
					for (int x = 0; x < MinXLen; x++){
						BYTE	*d0=Buff[0]->GetYWithoutDepended(x);
						BYTE	*d1=Buff[1]->GetYWithoutDepended(x);
						BYTE	*d2=Buff[2]->GetYWithoutDepended(x);
						d0[Y] = *(row  );
						d1[Y] = *(row+1);
						d2[Y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
		}
		else
		if(MirrorX==false && MirrorY==false && RotationAngle==180){
			int	MinXLen=min(width,Buff[0]->GetWidth());
			int	MinYLen=min(height,Buff[0]->GetHeight());
			int	YN=MinYLen;	//&0xFFE0;
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];

					BYTE	*d0=&Buff[0]->GetY(YN-y-1)[MinXLen-1];
					BYTE	*d1=&Buff[1]->GetY(YN-y-1)[MinXLen-1];
					BYTE	*d2=&Buff[2]->GetY(YN-y-1)[MinXLen-1];
					for (int x = 0; x < MinXLen; x++){
						*d0 = *(row  );
						*d1 = *(row+1);
						*d2 = *(row+2);
						row+=3;
						d0--;
						d1--;
						d2--;
					}
				}
			//}
		}
		else
		if(MirrorX==false && MirrorY==false && RotationAngle==270){
			int	MinXLen=min(width,Buff[0]->GetHeight());
			int	MinYLen=min(height,Buff[0]->GetWidth());
			int	YN=MinYLen;	//&0xFFE0;
			if(Buff[0]->IsDepended()==true){
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];
					int	X=MinXLen-1;
					for (int x = 0; x < MinXLen; x++,X--){
						BYTE	*d0=Buff[0]->GetY(X);
						BYTE	*d1=Buff[1]->GetY(X);
						BYTE	*d2=Buff[2]->GetY(X);
						d0[y] = *(row  );
						d1[y] = *(row+1);
						d2[y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
			else{
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];
					int	X=MinXLen-1;
					for (int x = 0; x < MinXLen; x++,X--){
						BYTE	*d0=Buff[0]->GetYWithoutDepended(X);
						BYTE	*d1=Buff[1]->GetYWithoutDepended(X);
						BYTE	*d2=Buff[2]->GetYWithoutDepended(X);
						d0[y] = *(row  );
						d1[y] = *(row+1);
						d2[y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
		}

		else
		if(MirrorX==true && MirrorY==false && RotationAngle==0){
			int	MinXLen=min(width,Buff[0]->GetWidth());
			int	MinYLen=min(height,Buff[0]->GetHeight());
			int	YN=MinYLen;	//&0xFFE0;
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];

					BYTE	*d0=&Buff[0]->GetY(y)[MinXLen-1];
					BYTE	*d1=&Buff[1]->GetY(y)[MinXLen-1];
					BYTE	*d2=&Buff[2]->GetY(y)[MinXLen-1];
					for (int x = 0; x < MinXLen; x++){
						*d0 = *(row  );
						*d1 = *(row+1);
						*d2 = *(row+2);
						row+=3;
						d0--;
						d1--;
						d2--;
					}
				}
			//}
		}
		else
		if(MirrorX==true && MirrorY==false && RotationAngle==90){
			int	MinXLen=min(width,Buff[0]->GetHeight());
			int	MinYLen=min(height,Buff[0]->GetWidth());
			int	YN=MinYLen;	//&0xFFE0;
			if(Buff[0]->IsDepended()==true){
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					int	Y=YN-y-1;
					JSAMPROW row = &buffer[y*XByte3];
					int	X=MinXLen-1;
					for (int x = 0; x < MinXLen; x++,X--){
						BYTE	*d0=Buff[0]->GetY(X);
						BYTE	*d1=Buff[1]->GetY(X);
						BYTE	*d2=Buff[2]->GetY(X);
						d0[Y] = *(row  );
						d1[Y] = *(row+1);
						d2[Y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
			else{
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					int	Y=YN-y-1;
					JSAMPROW row = &buffer[y*XByte3];
					int	X=MinXLen-1;
					for (int x = 0; x < MinXLen; x++,X--){
						BYTE	*d0=Buff[0]->GetYWithoutDepended(X);
						BYTE	*d1=Buff[1]->GetYWithoutDepended(X);
						BYTE	*d2=Buff[2]->GetYWithoutDepended(X);
						d0[Y] = *(row  );
						d1[Y] = *(row+1);
						d2[Y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
		}
		else
		if(MirrorX==true && MirrorY==false && RotationAngle==180){
			int	MinXLen=min(width,Buff[0]->GetWidth());
			int	MinYLen=min(height,Buff[0]->GetHeight());
			int	YN=MinYLen;	//&0xFFE0;
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];

					BYTE	*d0=Buff[0]->GetY(YN-y-1);
					BYTE	*d1=Buff[1]->GetY(YN-y-1);
					BYTE	*d2=Buff[2]->GetY(YN-y-1);
					for (int x = 0; x < MinXLen; x++){
						*d0 = *(row  );
						*d1 = *(row+1);
						*d2 = *(row+2);
						row+=3;
						d0++;
						d1++;
						d2++;
					}
				}
			//}
		}
		else
		if(MirrorX==true && MirrorY==false && RotationAngle==270){
			int	MinXLen=min(width,Buff[0]->GetHeight());
			int	MinYLen=min(height,Buff[0]->GetWidth());
			int	YN=MinYLen;	//&0xFFE0;
			if(Buff[0]->IsDepended()==true){
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];
					for (int x = 0; x < MinXLen; x++){
						BYTE	*d0=Buff[0]->GetY(x);
						BYTE	*d1=Buff[1]->GetY(x);
						BYTE	*d2=Buff[2]->GetY(x);
						d0[y] = *(row  );
						d1[y] = *(row+1);
						d2[y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
			else{
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];
					for (int x = 0; x < MinXLen; x++){
						BYTE	*d0=Buff[0]->GetYWithoutDepended(x);
						BYTE	*d1=Buff[1]->GetYWithoutDepended(x);
						BYTE	*d2=Buff[2]->GetYWithoutDepended(x);
						d0[y] = *(row  );
						d1[y] = *(row+1);
						d2[y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
		}

		else
		if(MirrorX==false && MirrorY==true && RotationAngle==0){
			int	MinXLen=min(width,Buff[0]->GetWidth());
			int	MinYLen=min(height,Buff[0]->GetHeight());
			int	YN=MinYLen;	//&0xFFE0;
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];

					BYTE	*d0=Buff[0]->GetY(YN-y-1);
					BYTE	*d1=Buff[1]->GetY(YN-y-1);
					BYTE	*d2=Buff[2]->GetY(YN-y-1);
					for (int x = 0; x < MinXLen; x++){
						*d0 = *(row  );
						*d1 = *(row+1);
						*d2 = *(row+2);
						row+=3;
						d0++;
						d1++;
						d2++;
					}
				}
			//}
		}
		else
		if(MirrorX==false && MirrorY==true && RotationAngle==90){
			int	MinXLen=min(width,Buff[0]->GetHeight());
			int	MinYLen=min(height,Buff[0]->GetWidth());
			int	YN=MinYLen;	//&0xFFE0;
			if(Buff[0]->IsDepended()==true){
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					//int	Y=YN-y-1;
					int	Y=y;
					JSAMPROW row = &buffer[y*XByte3];
					//int	X=MinXLen-1;
					int	X=0;
					for (int x = 0; x < MinXLen; x++,X++){
						BYTE	*d0=Buff[0]->GetY(X);
						BYTE	*d1=Buff[1]->GetY(X);
						BYTE	*d2=Buff[2]->GetY(X);
						d0[Y] = *(row  );
						d1[Y] = *(row+1);
						d2[Y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
			else{
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					//int	Y=YN-y-1;
					int	Y=y;
					JSAMPROW row = &buffer[y*XByte3];
					//int	X=MinXLen-1;
					int	X=0;
					for (int x = 0; x < MinXLen; x++,X++){
						BYTE	*d0=Buff[0]->GetYWithoutDepended(X);
						BYTE	*d1=Buff[1]->GetYWithoutDepended(X);
						BYTE	*d2=Buff[2]->GetYWithoutDepended(X);
						d0[Y] = *(row  );
						d1[Y] = *(row+1);
						d2[Y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
		}
		else
		if(MirrorX==false && MirrorY==true && RotationAngle==180){
			int	MinXLen=min(width,Buff[0]->GetWidth());
			int	MinYLen=min(height,Buff[0]->GetHeight());
			int	YN=MinYLen;	//&0xFFE0;
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];

					BYTE	*d0=&Buff[0]->GetY(y)[MinXLen-1];
					BYTE	*d1=&Buff[1]->GetY(y)[MinXLen-1];
					BYTE	*d2=&Buff[2]->GetY(y)[MinXLen-1];
					for (int x = 0; x < MinXLen; x++){
						*d0 = *(row  );
						*d1 = *(row+1);
						*d2 = *(row+2);
						row+=3;
						d0--;
						d1--;
						d2--;
					}
				}
			//}
		}
		else
		if(MirrorX==false && MirrorY==true && RotationAngle==270){
			int	MinXLen=min(width,Buff[0]->GetHeight());
			int	MinYLen=min(height,Buff[0]->GetWidth());
			int	YN=MinYLen;	//&0xFFE0;
			if(Buff[0]->IsDepended()==true){
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					int	Y=YN-y-1;
					JSAMPROW row = &buffer[y*XByte3];
					int	X=MinXLen-1;
					for (int x = 0; x < MinXLen; x++,X--){
						BYTE	*d0=Buff[0]->GetY(X);
						BYTE	*d1=Buff[1]->GetY(X);
						BYTE	*d2=Buff[2]->GetY(X);
						d0[Y] = *(row  );
						d1[Y] = *(row+1);
						d2[Y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
			else{
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					int	Y=YN-y-1;
					JSAMPROW row = &buffer[y*XByte3];
					int	X=MinXLen-1;
					for (int x = 0; x < MinXLen; x++,X--){
						BYTE	*d0=Buff[0]->GetYWithoutDepended(X);
						BYTE	*d1=Buff[1]->GetYWithoutDepended(X);
						BYTE	*d2=Buff[2]->GetYWithoutDepended(X);
						d0[Y] = *(row  );
						d1[Y] = *(row+1);
						d2[Y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
		}

		else
		if(MirrorX==true && MirrorY==true && RotationAngle==0){
			int	MinXLen=min(width,Buff[0]->GetWidth());
			int	MinYLen=min(height,Buff[0]->GetHeight());
			int	YN=MinYLen;	//&0xFFE0;
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];

					BYTE	*d0=&Buff[0]->GetY(YN-y-1)[MinXLen-1];
					BYTE	*d1=&Buff[1]->GetY(YN-y-1)[MinXLen-1];
					BYTE	*d2=&Buff[2]->GetY(YN-y-1)[MinXLen-1];
					for (int x = 0; x < MinXLen; x++){
						*d0 = *(row  );
						*d1 = *(row+1);
						*d2 = *(row+2);
						row+=3;
						d0--;
						d1--;
						d2--;
					}
				}
			//}
		}
		else
		if(MirrorX==true && MirrorY==true && RotationAngle==90){
			int	MinXLen=min(width,Buff[0]->GetHeight());
			int	MinYLen=min(height,Buff[0]->GetWidth());
			int	YN=MinYLen;	//&0xFFE0;
			if(Buff[0]->IsDepended()==true){
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];
					int	X=MinXLen-1;
					for (int x = 0; x < MinXLen; x++,X--){
						BYTE	*d0=Buff[0]->GetY(X);
						BYTE	*d1=Buff[1]->GetY(X);
						BYTE	*d2=Buff[2]->GetY(X);
						d0[y] = *(row  );
						d1[y] = *(row+1);
						d2[y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
			else{
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];
					int	X=MinXLen-1;
					for (int x = 0; x < MinXLen; x++,X--){
						BYTE	*d0=Buff[0]->GetYWithoutDepended(X);
						BYTE	*d1=Buff[1]->GetYWithoutDepended(X);
						BYTE	*d2=Buff[2]->GetYWithoutDepended(X);
						d0[y] = *(row  );
						d1[y] = *(row+1);
						d2[y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
		}
		else
		if(MirrorX==true && MirrorY==true && RotationAngle==180){
			int	MinXLen=min(width,Buff[0]->GetWidth());
			int	MinYLen=min(height,Buff[0]->GetHeight());
			int	YN=MinYLen;	//&0xFFE0;
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					JSAMPROW row = &buffer[y*XByte3];

					BYTE	*d0=Buff[0]->GetY(y);
					BYTE	*d1=Buff[1]->GetY(y);
					BYTE	*d2=Buff[2]->GetY(y);
					for (int x = 0; x < MinXLen; x++){
						*d0 = *(row  );
						*d1 = *(row+1);
						*d2 = *(row+2);
						row+=3;
						d0++;
						d1++;
						d2++;
					}
				}
			//}
		}
		else
		if(MirrorX==true && MirrorY==true && RotationAngle==270){
			int	MinXLen=min(width,Buff[0]->GetHeight());
			int	MinYLen=min(height,Buff[0]->GetWidth());
			int	YN=MinYLen;	//&0xFFE0;
			if(Buff[0]->IsDepended()==true){
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					int	Y=YN-y-1;
					JSAMPROW row = &buffer[y*XByte3];
					for (int x = 0; x < MinXLen; x++){
						BYTE	*d0=Buff[0]->GetY(x);
						BYTE	*d1=Buff[1]->GetY(x);
						BYTE	*d2=Buff[2]->GetY(x);
						d0[Y] = *(row  );
						d1[Y] = *(row+1);
						d2[Y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
			else{
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
				for (int y = 0; y < YN; y++) {
					int	Y=YN-y-1;
					JSAMPROW row = &buffer[y*XByte3];
					for (int x = 0; x < MinXLen; x++){
						BYTE	*d0=Buff[0]->GetYWithoutDepended(x);
						BYTE	*d1=Buff[1]->GetYWithoutDepended(x);
						BYTE	*d2=Buff[2]->GetYWithoutDepended(x);
						d0[Y] = *(row  );
						d1[Y] = *(row+1);
						d2[Y] = *(row+2);
						row+=3;
					}
				}
			//}
			}
		}
	}
}
