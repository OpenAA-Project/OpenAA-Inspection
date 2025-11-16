#include "mtImageSliderBase.h"
#include <QPainter>
#include <QMouseEvent>

#include "XImageBufferFunctions.h"
#include "XPointer.h"
#include "XImageProcess.h"

mtImageSliderBase::mtImageSliderBase()
{

}

mtImageSliderBase::~mtImageSliderBase()
{

}

void mtImageSliderBase::setImage() {
	int wid, hei;
	wid = imgBack.width();
	hei = imgBack.height();
	calcThresholdBack();
	QImage wimg=imgBack;
	imgBack.setAlphaChannel(imgBack);
	for( int j=0; j<hei; j++ ) {
		QRgb *pYLine	=(QRgb *)imgBack.scanLine(j);
		QRgb *wpYLine	=(QRgb *)wimg.scanLine(j);
		for( int i=0; i<wid; i++ ) {
//			if ( chkBit(i,j) == true ) {
			if ( qGray(*(wpYLine+i)) > 0 ) {
				*(pYLine+i)=*(wpYLine+i);
			}
		}
	}
	
	wid = imgSld.width();
	hei = imgSld.height();
	calcThresholdSld();
	wimg = imgSld;
	imgSld.setAlphaChannel(imgSld);
	for( int j=0; j<hei; j++ ) {
		QRgb *pYLine	=(QRgb *)imgSld.scanLine(j);
		QRgb *wpYLine	=(QRgb *)wimg.scanLine(j);
		for( int i=0; i<wid; i++ ) {
			if ( chkBitSld(i,j) == true ) {
				*(pYLine+i)=*(wpYLine+i);
			}
		}
	}
/*
	int wid, hei;
	wid = imgBack.width();
	hei = imgBack.height();
	calcThresholdBack();
	QImage wimg=imgBack;
	imgDrawBack = QImage(wid,hei,QImage::Format_ARGB32);

	imgDrawBack.setAlphaChannel(imgDrawBack);
	for( int j=0; j<hei; j++ ) {
		QRgb *pYLine  = (QRgb *)imgDrawBack.scanLine(j);
		QRgb *wpYLine = (QRgb *)wimg.scanLine(j);
		for( int i=0; i<wid; i++ ) {
			if ( chkBit(i,j) == true ) {
				*(pYLine+i) = *(wpYLine+i);
			} else {
				*(pYLine+i) = qRgba(0,0,0,0);
			}
		}
	}
	
	int swid, shei;
	swid = imgSld.width();
	shei = imgSld.height();
	calcThresholdSld();
	wimg = imgSld;
	imgDrawSld = QImage(swid,shei,QImage::Format_ARGB32);
	imgDrawSld.setAlphaChannel(imgDrawBack);
	for( int j=0; j<shei; j++ ) {
		QRgb *pYLine  = (QRgb *)imgDrawSld.scanLine(j);
		QRgb *wpYLine = (QRgb *)wimg.scanLine(j);
		for( int i=0; i<swid; i++ ) {
			if ( chkBitSld(i,j) == true ) {
				*(pYLine+i) = *(wpYLine+i);
			} else {
				*(pYLine+i) = qRgba(0,0,0,0);
			}
		}
	}
*/
}

bool mtImageSliderBase::calcThresholdBack() {
	QImage *img = &imgBack;
	int wid = img->width();
	int hei = img->height();
	int bitwid = (int)(wid/8);
	if ( wid%8 > 0 ) bitwid ++;
	int bithei = hei;

	BYTE	bitBufDim[10000];
	BYTE **bitBuf = MakeMatrixBuff(bitwid,bithei,bitBufDim,sizeof(bitBufDim));
	MatrixBuffClear(bitBuf,0,bitwid,bithei);

	for( int iy=0; iy<hei; iy++ ) {
		BYTE p = 0x00;
		int iXPnt = 0;
		int idx   = 0;
		for( int ix=0; ix<wid; ix++ ) {
			QRgb rgb = img->pixel(ix,iy);
			int r = qRed(rgb);
			int g = qGreen(rgb);
			int b = qBlue(rgb);
			int a = qAlpha(rgb);
			if ( (r > 200 && g > 200 && b > 200) || a == 0 ) {
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
	BYTE	tmpBufDim[10000];
	BYTE **tmp = MakeMatrixBuff(bitwid,bithei,tmpBufDim,sizeof(tmpBufDim));
	MatrixBuffCopy(tmp,wid,hei,(const BYTE **)bitBuf,bitwid,bithei);
	if ( PickupFlexArea(tmp,0,bitwid*8,bithei,fAreaList) == false ) {
		return false;
	}
	//int cnt = fAreaList.GetNumber();
	fAreaList.GetFirst()->MakeOutlineDot(xyArea);
	if(tmp!=(BYTE **)tmpBufDim){
		DeleteMatrixBuff(tmp,bithei);
	}
	if(bitBuf!=(BYTE **)bitBufDim){
		DeleteMatrixBuff(bitBuf,bithei);
	}
	return true;
}

bool mtImageSliderBase::chkBit(int x, int y) {
	if ( xyArea.IsInclude(x,y) == true ) {
		return true;
	}

	QRgb rgb = imgBack.pixel(x,y);
	if ( (qRed(rgb) < 200 || qGreen(rgb) < 200 || qBlue(rgb) < 200 ) ) {
		return true;
	}

	return false;
}

bool mtImageSliderBase::calcThresholdSld() {
	QImage *img = &imgSld;
	int wid = img->width();
	int hei = img->height();
	int bitwid = (int)(wid/8);
	if ( wid%8 > 0 ) bitwid ++;
	int bithei = hei;

	BYTE	bitBufDim[10000];
	BYTE **bitBuf = MakeMatrixBuff(bitwid,bithei,bitBufDim,sizeof(bitBufDim));
	MatrixBuffClear(bitBuf,0,bitwid,bithei);

	for( int iy=0; iy<hei; iy++ ) {
		BYTE p = 0x00;
		int iXPnt = 0;
		int idx   = 0;
		for( int ix=0; ix<wid; ix++ ) {
			QRgb rgb = img->pixel(ix,iy);
			int gray = qGray(rgb);
			int a = qAlpha(rgb);
			if ( gray == 0 || a == 0 ) {
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
	BYTE	tmpBufDim[10000];
	BYTE **tmp = MakeMatrixBuff(bitwid,bithei,tmpBufDim,sizeof(tmpBufDim));
	MatrixBuffCopy(tmp,wid,hei,(const BYTE **)bitBuf,bitwid,bithei);
	if ( PickupFlexArea(tmp,0,bitwid*8,bithei,fAreaListSld) == false ) {
		return false;
	}
	//int cnt = fAreaListSld.GetNumber();
	fAreaListSld.GetFirst()->MakeOutlineDot(xyAreaSld);
	if(tmp!=(BYTE **)tmpBufDim){
		DeleteMatrixBuff(tmp,bithei);
	}
	if(bitBuf!=(BYTE **)bitBufDim){
		DeleteMatrixBuff(bitBuf,bithei);
	}
	return true;
}

bool mtImageSliderBase::chkBitSld(int x, int y) {
	if ( xyAreaSld.IsInclude(x,y) == true ) {
		return true;
	}

	return false;
}
