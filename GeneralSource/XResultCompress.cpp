/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XResultCompress.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "ServiceLibResource.h"
#include <QtGui>
#include <QColor>
#include "XResult.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include <omp.h>
#include "swap.h"
#include <png.h>
#include "XImagePNG.h"


bool	NGImage::CompressImage(DataInPage *PData ,int quality)
{
	int	LByte=GetHeight()*GetWidth()*3;
	BYTE	*TmpLinearBuff;
	BYTE	TmpLinearBuffDim[500*500*3];

	int	AllocatedLinearBuffSize=LByte;
	if(LByte>sizeof(TmpLinearBuffDim)){
		TmpLinearBuff=new BYTE[AllocatedLinearBuffSize];
	}
	else{
		TmpLinearBuff=TmpLinearBuffDim;
	}

	if(CompressedPtn!=NULL){
		delete	[]CompressedPtn;
	}
	CompressedPtn=new BYTE[AllocatedLinearBuffSize];

	BYTE	*p=TmpLinearBuff;
	if(PData->GetLayerNumb()==1 && SrcImage[0]!=NULL){
		for(int y=0;y<GetHeight();y++){
			BYTE	*src=SrcImage[0][y];
			for(int x=0;x<GetWidth();x++ ,src++){
				*(p+0)=*src;
				*(p+1)=*src;
				*(p+2)=*src;
				p+=3;
			}
		}
	}
	else if(PData->GetLayerNumb()==2 && SrcImage[0]!=NULL && SrcImage[1]!=NULL){
		for(int y=0;y<GetHeight();y++){
			BYTE	*src0=SrcImage[0][y];
			BYTE	*src1=SrcImage[1][y];
			for(int x=0;x<GetWidth();x++ ,src0++,src1++){
				*(p+0)=*src0;
				*(p+1)=*src0;
				*(p+2)=*src1;
				p+=3;
			}
		}
	}
	else if(PData->GetLayerNumb()>=3 && SrcImage[0]!=NULL && SrcImage[1]!=NULL && SrcImage[2]!=NULL){
		for(int y=0;y<GetHeight();y++){
			BYTE	*src0=SrcImage[0][y];
			BYTE	*src1=SrcImage[1][y];
			BYTE	*src2=SrcImage[2][y];
			for(int x=0;x<GetWidth();x++ ,src0++,src1++,src2++){
				*(p+0)=*src0;
				*(p+1)=*src1;
				*(p+2)=*src2;
				p+=3;
			}
		}
	}

	png_image png;
	memset(&png, 0, sizeof(png));
	png.version = PNG_IMAGE_VERSION;

	// •K—v‚Èî•ñ‚ðÝ’è
	png.width  = GetWidth();
	png.height = GetHeight();
	png.format = PNG_FORMAT_RGB;
	uint32_t stride = PNG_IMAGE_ROW_STRIDE(png);

	png_alloc_size_t	memory_bytes;


	//int	Res1=png_image_write_to_file(&png, "kaga.png", 0, Buffer, stride, NULL);
	memory_bytes=AllocatedLinearBuffSize;

	int	Res2=png_image_write_to_memory(&png, CompressedPtn,
										&memory_bytes, 0
										,TmpLinearBuff, stride, NULL);

	PtnByte=memory_bytes;


	/*
	QImage	Image(GetWidth(),GetHeight(),QImage::Format_RGB32);
	if(PData->GetLayerNumb()==1 && SrcImage[0]!=NULL){
		for(int y=0;y<GetHeight();y++){
			BYTE	*src=SrcImage[0][y];
			QRgb	*dst=(QRgb *)Image.scanLine(y);
			for(int x=0;x<GetWidth();x++ ,src++,dst++){
				*dst=qRgb(*src ,*src ,*src);
			}
		}
	}
	else if(PData->GetLayerNumb()==2 && SrcImage[0]!=NULL && SrcImage[1]!=NULL){
		for(int y=0;y<GetHeight();y++){
			BYTE	*src0=SrcImage[0][y];
			BYTE	*src1=SrcImage[1][y];
			QRgb	*dst=(QRgb *)Image.scanLine(y);
			for(int x=0;x<GetWidth();x++ ,src0++,src1++,dst++){
				*dst=qRgb(*src0 ,*src0 ,*src1);
			}
		}
	}
	else if(PData->GetLayerNumb()>=3 && SrcImage[0]!=NULL && SrcImage[1]!=NULL && SrcImage[2]!=NULL){
		for(int y=0;y<GetHeight();y++){
			BYTE	*src0=SrcImage[0][y];
			BYTE	*src1=SrcImage[1][y];
			BYTE	*src2=SrcImage[2][y];
			QRgb	*dst=(QRgb *)Image.scanLine(y);
			for(int x=0;x<GetWidth();x++ ,src0++,src1++,src2++,dst++){
				*dst=qRgb(*src0 ,*src1 ,*src2);
			}
		}
	}
	else
		return false;
	*/
//	QBuffer	Buff;
//	Buff.open(QIODevice::ReadWrite);
//	Image.save(&Buff,/**/"PNG",quality);
//	PtnByte=Buff.size();
//	if(CompressedPtn!=NULL){
//		delete	[]CompressedPtn;
//	}
//	CompressedPtn=new BYTE[PtnByte];
//	Buff.seek(0);
//	Buff.read((char *)CompressedPtn,PtnByte);

	if(TmpLinearBuff!=TmpLinearBuffDim){
		delete	[]TmpLinearBuff;
	}

	SuccessCompress=true;
	return true;
}