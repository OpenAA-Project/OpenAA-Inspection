#include "mtImageToolButtonWithBalloon.h"

mtImageToolButtonWithBalloon::mtImageToolButtonWithBalloon(const QImage &_img, QWidget *parent)
	: mtImageToolButton(_img,parent)
{
	setMouseTracking(true);
}

mtImageToolButtonWithBalloon::~mtImageToolButtonWithBalloon()
{

}

void mtImageToolButtonWithBalloon::closeEvent(QCloseEvent *event) {
	mtButtonWithBalloonBase::Close();
}

void mtImageToolButtonWithBalloon::mousePressEvent(QMouseEvent *event) 
{
	mtButtonWithBalloonBase::MousePressEvent();
	mtImageToolButton::mousePressEvent(event);
	if(event->button()==Qt::RightButton){
		emit	RClick(event);
	}
}
void mtImageToolButtonWithBalloon::mouseDoubleClickEvent(QMouseEvent *event)
{
	mtImageToolButton::mouseDoubleClickEvent(event);
	emit	LDoubleClick(event);
}

void mtImageToolButtonWithBalloon::mouseMoveEvent(QMouseEvent *event) {
	mtButtonWithBalloonBase::MouseMoveEvent(event);
}

void mtImageToolButtonWithBalloon::enterEvent(QEnterEvent *event) {
	mtButtonWithBalloonBase::EnterEvent(this);
}

void mtImageToolButtonWithBalloon::SlotMessageMouseMove(int x, int y) {
	closeBalloon();
}
