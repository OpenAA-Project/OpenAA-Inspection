#include "ShowVRSOperationResource.h"
#include "VRSJoyForm.h"

#include <QPaintEvent>
#include <QPainter>
#include <qmath.h>

#include "XReviewCommon.h"

VRSJoyForm::VRSJoyForm(QWidget *parent)
	:QWidget(parent),m_isMouseOnView(false),m_currentPoint(),m_maxValue(0),m_isXReverse(false),m_isYReverse(false),m_rateSelector(parent),m_rate(1)
{
	ui.setupUi(this);
	setMouseTracking(true);
	QSize fixSize(300,300);
	resize(fixSize);
	setFixedSize(fixSize);

	m_rateSelector.setWindowFlags((windowFlags() & ~(Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint | Qt::WindowTitleHint)) | Qt::CustomizeWindowHint | Qt::Window);

	connect(&m_rateSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(setRate(int)));

	QStringList rateStrList;
	rateStrList << /**/"1/1" << /**/"1/2" << /**/"1/4" << /**/"1/8" << /**/"1/16";
	m_rateSelector.setRadioList(rateStrList);
	m_rateSelector.show();
}

void VRSJoyForm::setRate(int r)
{
	m_rate = r;
}

void VRSJoyForm::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);

	QPainter painter(this);

	painter.fillRect(rect(), Qt::white);

	QPen blackPen;
	blackPen.setColor(QColor(Qt::black));

	painter.setPen(blackPen);
	painter.drawLine(rect().center().x(), 0, rect().center().x(), height());
	painter.drawLine(0, rect().center().y(), width(), rect().center().y());

	if(isMouseOnView()==true){
		QPen redPen;
		redPen.setColor(QColor(Qt::red));

		QPoint pos = currentPoint();

		painter.setPen(redPen);
		painter.drawLine(rect().center(), pos);

		painter.setPen(blackPen);

		qreal x_rate = pos.x() / (qreal)width();
		qreal y_rate = pos.y() / (qreal)height();

		qreal x = 2*x_rate - 1;
		qreal y = 2*y_rate - 1;

		if(isXReverse()==true){
			x = -x;
		}
		if(isYReverse()==true){
			y = -y;
		}

		x /= qPow(2, m_rate);

		QString posStr = QString(/**/"%1,%2").arg(x*maxValue()).arg(y*maxValue());
		int wid = painter.fontMetrics().width(posStr);
		int hei = painter.fontMetrics().height();

		QPoint topLeft(pos.x()-wid/2, pos.y()-hei);

		if(topLeft.x()<0){
			topLeft.setX(0);
		}else if(topLeft.x()+wid>width()){
			topLeft.setX(width()-wid);
		}

		if(topLeft.y()<0){
			topLeft.setY(0);
		}else if(topLeft.y()+hei>height()){
			topLeft.setY(height()-hei);
		}

		painter.drawText(topLeft, posStr);
	}
}

void VRSJoyForm::mousePressEvent(QMouseEvent *event)
{
	qreal x_rate = event->pos().x() / (qreal)width();
	qreal y_rate = event->pos().y() / (qreal)height();

	qreal x = 2*x_rate - 1;
	qreal y = 2*y_rate - 1;

	x /= qPow(2, m_rate);
	y /= qPow(2, m_rate);

	emit joyout(x, y);
}

void VRSJoyForm::mouseMoveEvent(QMouseEvent *event)
{
	setCurrentPoint(event->pos());
	update();
}

void VRSJoyForm::enterEvent(QEvent *event)
{
	setMouseOnView(true);
	update();
}

void VRSJoyForm::leaveEvent(QEvent *event)
{
	setMouseOnView(false);
	update();
}

void VRSJoyForm::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	m_rateSelector.move(frameGeometry().topRight());
}

void VRSJoyForm::moveEvent(QMoveEvent *event)
{
	QWidget::moveEvent(event);
	
	m_rateSelector.move(frameGeometry().topRight());
}

void VRSJoyForm::wheelEvent(QWheelEvent *event)
{
	QWidget::wheelEvent(event);

	if(m_rateSelector.count()<=1){
		return;
	}
	if(event->delta()>0){
		if(Review::isBetween(1, m_rateSelector.currentIndex(), m_rateSelector.count())==true){
			m_rateSelector.setCurrentIndex(m_rateSelector.currentIndex()-1);
		}
	}else{
		if(Review::isBetween(0, m_rateSelector.currentIndex(), m_rateSelector.count()-1)==true){
			m_rateSelector.setCurrentIndex(m_rateSelector.currentIndex()+1);
		}
	}
}