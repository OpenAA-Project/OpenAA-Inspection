#include "mtImageSlider.h"

#include <QPainter>

mtImageSlider::mtImageSlider(const QImage &img1, const QImage &img2, QWidget *parent)
	: QWidget(parent)
{
	bMouse = false;

	imgSld  = img1;
	imgBack = img2;
	nDrawX = imgBack.width()/2;
	minValue = 1;
	maxValue = 5;
	value = 3;
	nSideDiv = 7;
	nStartX = 27;
	nDivX = 63;

	setImage();
	resize(imgBack.width(),imgBack.height());
}

mtImageSlider::mtImageSlider(int _minValue, int _maxValue, const QImage &img1, const QImage &img2, QWidget *parent)
	: QWidget(parent)
{
	bMouse = false;

	imgSld  = img1;
	imgBack = img2;
	nDrawX = imgBack.width()/2;
	minValue = _minValue;
	maxValue = _maxValue;
	value = (maxValue+minValue)/2;
	nSideDiv = 7;
//	nStartX = 27;
//	nDivX = 63;
	nStartX = 25;
	nDivX = 32;

	setImage();
	resize(imgBack.width(),imgBack.height());
}

mtImageSlider::mtImageSlider(int _minValue, int _maxValue, int _nSideDiv, int _nStartX, int _nDivX, const QImage &img1, const QImage &img2, QWidget *parent)
	: QWidget(parent)
{
	bMouse = false;

	imgSld  = img1;
	imgBack = img2;
	nDrawX = imgBack.width()/2;
	minValue = _minValue;
	maxValue = _maxValue;
	value = (maxValue+minValue)/2;
	nSideDiv = _nSideDiv;
	nStartX = _nStartX;
	nDivX = _nDivX;

	setImage();
	resize(imgBack.width(),imgBack.height());
}

mtImageSlider::~mtImageSlider()
{

}

void mtImageSlider::paintEvent(QPaintEvent *evt) {
	QPainter pnt2(this);
	pnt2.drawImage(0,0,imgBack);

	//int wid = imgBack.width();
	int x = nDrawX - (imgSld.width()/2);
	pnt2.drawImage(x,0,imgSld);
/*
	QPainter pnt2(this);
	pnt2.drawImage(0,0,imgDrawBack);

	int wid = imgDrawBack.width();
	int x = nDrawX - (imgSld.width()/2);
	pnt2.drawImage(x,0,imgDrawSld);
*/
}

void mtImageSlider::mousePressEvent(QMouseEvent *evt) {
	int x = evt->pos().x();
	int y = evt->pos().y();
	if ( y > imgSld.height() ) {
		return;
	}
	bMouse = true;
	if ( chkMoveSize(x) == true ) {
		nDrawX= x;
		repaint();
	}
}

void mtImageSlider::mouseReleaseEvent(QMouseEvent *evt) {
	bMouse = false;
	calcValueTick();
	chgValueTick();
	emit valueChanged();
}

void mtImageSlider::mouseMoveEvent(QMouseEvent *evt) {
	if ( bMouse == true ) {
		int val = evt->pos().x();
		if ( chkMoveSize( val ) == true ) {
			nDrawX = evt->pos().x();
			repaint();
		}
	}
}

bool mtImageSlider::chkMoveSize(int x) {
	int wid = imgSld.width()/2;
	//int nMax = imgBack.width();
	if ( x+wid > imgBack.width()-nSideDiv ) {
		return false;
	}
	if ( x-wid < nSideDiv ) {
		return false;
	}
	return true;
}
/*
void mtImageSlider::setMinimum(int _minValue) {
	minValue = _minValue;
}

void mtImageSlider::setMaximum(int _maxValue) {
	maxValue = _maxValue;
}
*/
void mtImageSlider::setValue(int _value) {
	if ( _value < minValue || _value > maxValue ) {
		return;
	}
	value = _value;
	chgValueTick();
}
/*
int mtImageSlider::Value() {
	return value;
}
*/
void mtImageSlider::setImgAxis(int _nStart, int _nDiv) {
	nStartX = _nStart;
	nDivX   = _nDiv;
	chgValueTick();
}

void mtImageSlider::chgValueTick() {
	int nStartPnt = value - minValue;
	nDrawX = nDivX*nStartPnt+nStartX;
	repaint();
}

void mtImageSlider::calcValueTick() {
	int nPnt  = (nDrawX-nStartX)/nDivX;
	double dd = (double)(nDrawX-nStartX)/nDivX;
	if ( dd-nPnt > 0.5 ) {
		nPnt ++;
	}
	value = nPnt+minValue;
}