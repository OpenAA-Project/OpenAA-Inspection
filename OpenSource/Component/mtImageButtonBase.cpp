#include "mtImageButtonBase.h"
#include <QPainter>
#include <QMouseEvent>

#include "XImageBufferFunctions.h"
#include "XPointer.h"
#include "XImageProcess.h"

mtImageButtonBase::mtImageButtonBase()
{
	InvertMode	=false;
	wImg		=NULL;
	BtnState	=Default;
}

void mtImageButtonBase::setInvertMode(bool b)
{
	InvertMode=b;
	setImage();
}
void mtImageButtonBase::setFaceImage(const QImage &_img)
{
	img=_img;
	setImage();
}

void mtImageButtonBase::setImage() 
{
	if(img.isNull()==false){
		int wid, hei;
		wid = img.width();
		hei = img.height();

		calcThreshold();
	/*	for( int j=0; j<hei; j++ ) {
			QRgb *pYLine=(QRgb *)img.scanLine(j);
			for( int i=0; i<wid; i++ ) {
	//			QRgb rgb = img.pixel(i,j);
				if ( chkBit(i,j) == false ) {
	//				img.setPixel(i,j,qRgba(0,0,0,0));
					*(pYLine+i)=qRgba(0,0,0,0);
				}
			}
		}
	*/
		if(InvertMode==false){
			QImage wimg=img;
			img.setAlphaChannel(img);
			for( int j=0; j<hei; j++ ) {
				QRgb *pYLine	=(QRgb *)img.scanLine(j);
				QRgb *wpYLine	=(QRgb *)wimg.scanLine(j);
				for( int i=0; i<wid; i++ ) {
					if ( chkBit(i,j) == true ) {
		//			if ( qGray(*(wpYLine+i)) > 0 ) {
						*(pYLine+i)=*(wpYLine+i);
					}
				}
			}
			PressedImg=img;
		}
		else{
			/*
			QImage wimg=img;
			PressedImg=img;
			QRgb ThresholdColor=img.pixel(0,0);
			for( int j=0; j<hei; j++ ) {
				QRgb *pYLine	=(QRgb *)PressedImg.scanLine(j);
				QRgb *wpYLine	=(QRgb *)wimg.scanLine(j);
				for( int i=0; i<wid; i++ ) {
					if ( ThresholdColor== *(wpYLine+i) ) {
						*(pYLine+i)=qRgb(255,0,0);
					}
				}
			}
			*/
			QImage wimg;
			wimg	  =img.convertToFormat(QImage::Format_ARGB32);
			PressedImg=wimg;
			wimg.fill((uint)qRgba(255,0,0,120));
			QPainter	pnt(&PressedImg);
			pnt.drawImage(0,0,wimg);
		}


	//	img.setAlphaChannel(img);
	//	img=img.alphaChannel().createAlphaMask();
	//	img.createMaskFromColor(qRgba(0,0,0,0));
	}
}

bool mtImageButtonBase::calcThreshold() 
{
	if(img.isNull()==false){
		int wid = img.width();
		int hei = img.height();
		int bitwid = (int)(wid/8);
		if ( wid%8 > 0 ) bitwid ++;
		int bithei = hei;
		BYTE	bitBufDim[10000];
		BYTE **bitBuf = MakeMatrixBuff(bitwid,bithei,bitBufDim,sizeof(bitBufDim));
		MatrixBuffClear(bitBuf,0,bitwid,bithei);

		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for
			for( int iy=0; iy<hei; iy++ ) {
				BYTE p = 0x00;
				int iXPnt = 0;
				int idx   = 0;
				for( int ix=0; ix<wid; ix++ ) {
					QRgb rgb = img.pixel(ix,iy);
					int r = qRed(rgb);
					int g = qGreen(rgb);
					int b = qBlue(rgb);
					int a = qAlpha(rgb);
					if ( (r == 0 && g == 0 && b == 0) || a == 0 ) {
						p = p << 1;
					} else {
						p = (p<<1)|0x01;
					}
					idx ++;
					if ( idx >= 8 ) {
						bitBuf[iy][iXPnt] = p;
						iXPnt ++;
						idx = 0;
						p = 0x00;
					}
				}
				if ( idx > 0 ) {
					p = p<<(8-idx);
					bitBuf[iy][iXPnt] = p;
				}
			}
		//}
			
		BYTE	tmpBufDim[10000];
		BYTE **tmp = MakeMatrixBuff(bitwid,bithei,tmpBufDim,sizeof(tmpBufDim));
		MatrixBuffCopy(tmp,wid,hei,(const BYTE **)bitBuf,bitwid,bithei);
		if ( PickupFlexArea(tmp,bitwid,bitwid*8,bithei,fAreaList) == false ) {
			DeleteMatrixBuff(tmp,bithei);
			DeleteMatrixBuff(bitBuf,bithei);
			return false;
		}
		if(fAreaList.GetFirst()!=NULL){
			fAreaList.GetFirst()->MakeOutlineDot(xyArea);
		}
		if(tmp!=(BYTE **)tmpBufDim){
			DeleteMatrixBuff(tmp,bithei);
		}
		if(bitBuf!=(BYTE **)bitBufDim){
			DeleteMatrixBuff(bitBuf,bithei);
		}
	}
	return true;
}

bool mtImageButtonBase::chkBit(int x, int y) 
{
	if ( xyArea.IsInclude(x,y) == false ) {
		return false;
	}
	return true;
}

mtImageButtonBase::~mtImageButtonBase()
{
}
