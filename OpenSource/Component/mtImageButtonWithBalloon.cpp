#include "mtImageButtonWithBalloon.h"
#include <QMouseEvent>

mtImageButtonWithBalloon::mtImageButtonWithBalloon(const QImage &_img, QWidget *parent)
	: mtImageButton(_img,parent)
{
	setMouseTracking(true);
}

mtImageButtonWithBalloon::~mtImageButtonWithBalloon()
{

}

void mtImageButtonWithBalloon::closeEvent(QCloseEvent *event) {
	mtButtonWithBalloonBase::Close();
}

void mtImageButtonWithBalloon::mousePressEvent(QMouseEvent *event) {
	mtButtonWithBalloonBase::MousePressEvent();
	mtImageButton::mousePressEvent(event);
}

void mtImageButtonWithBalloon::mouseMoveEvent(QMouseEvent *event) {
	mtButtonWithBalloonBase::MouseMoveEvent(event);
}

void mtImageButtonWithBalloon::enterEvent(QEnterEvent *event) {
	mtButtonWithBalloonBase::EnterEvent(this);
}

void mtImageButtonWithBalloon::SlotMessageMouseMove(int x, int y) {
	closeBalloon();
}