#include "CameraUSBStandard.h"
#include "jpeglib.h"
#include "turbojpeg.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include "XCameraDLL.h"
#include "SettingCameraDialog.h"
#include "XMainSchemeMemory.h"
#include "swap.h"
#include <mfapi.h>
#include "XLibWMF.h"
#include "LibWMFCamera.h"
#include <omp.h>


void TransformImage_RGB24(
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

void TransformImage_RGB32(
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
	if((MirrorX==false && MirrorY==false && RotationAngle==0)
	|| (MirrorX==true && MirrorY==true && RotationAngle==180)){
		aHeightInPixels	=min((int)aHeightInPixels,Buff[0]->GetHeight());
		aWidthInPixels	=min((int)aWidthInPixels ,Buff[0]->GetWidth());
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
		aHeightInPixels	=min((int)aHeightInPixels,Buff[0]->GetHeight());
		aWidthInPixels	=min((int)aWidthInPixels ,Buff[0]->GetWidth());
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
		aHeightInPixels	=min((int)aHeightInPixels,Buff[0]->GetHeight());
		aWidthInPixels	=min((int)aWidthInPixels ,Buff[0]->GetWidth());
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

//void	MakeYUY2(USBStandardData &CamData ,int Xn ,int Yn ,ImageBuffer *Buff[]
//				,bool MirrorX ,bool MirrorY
//				,int RotationAngle)
void TransformImage_YUY2(
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
	if(MirrorX==false && MirrorY==false && RotationAngle==0){
		aHeightInPixels	=min((int)aHeightInPixels,Buff[0]->GetHeight());
		aWidthInPixels	=min((int)aWidthInPixels ,Buff[0]->GetWidth());
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

void	MakeMonochrome(ImageBuffer *Buff[])
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
