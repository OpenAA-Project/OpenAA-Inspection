#include "InputRectInMultiImageDialog.h"

#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>

InputRectInMultiImageDialog::InputRectInMultiImageDialog(QWidget *parent)
	:QDialog(parent)
{
	m_ui.setupUi(this);
	m_ui.rbShiftImage->setChecked(true);
	m_ui.rbCreateRect->setChecked(false);
	m_ui.wCanvas->setMouseDragMode(InputRectInMultiImageWidget::MouseDragMode::ModeShiftImage);
}

void InputRectInMultiImageDialog::setImageList(const QList<QImage> &imageList, const QList<QPoint> &outlineList)
{
	m_ui.wCanvas->setImageList(imageList, outlineList);
}

//void InputRectInMultiImageDialog::on_rbDefault_toggled(bool checked)
//{
//	if(checked==true){
//		m_ui.wCanvas->setMouseDragMode(InputRectInMultiImageWidget::MouseDragMode::ModeDefault);
//	}
//}

void InputRectInMultiImageDialog::on_rbCreateRect_toggled(bool checked)
{
	if(checked==true){
		m_ui.wCanvas->setMouseDragMode(InputRectInMultiImageWidget::MouseDragMode::ModeMakeRect);
	}
}

void InputRectInMultiImageDialog::on_rbShiftImage_toggled(bool checked)
{
	if(checked==true){
		m_ui.wCanvas->setMouseDragMode(InputRectInMultiImageWidget::MouseDragMode::ModeShiftImage);
	}
}

QRect InputRectInMultiImageDialog::resultRect() const
{
	return canvas()->resultRect();
}

void InputRectInMultiImageDialog::setZoomStepLimit(quint32 limitCount)
{
	canvas()->setZoomStepLimit(limitCount);
}

void InputRectInMultiImageDialog::setZoomStep(int step)
{
	canvas()->setZoomStep(step);
}

void InputRectInMultiImageDialog::zoomStepIn()
{
	canvas()->zoomStepIn();
}

void InputRectInMultiImageDialog::zoomStepOut()
{
	canvas()->zoomStepOut();
}

void InputRectInMultiImageDialog::setResultRect(const QRect &rect, qreal zoomRate)
{
	canvas()->setResultRect(rect);
	canvas()->setResultZoom(zoomRate);
}

void InputRectInMultiImageDialog::setTopPage(qint32 page)
{
	canvas()->setTopPage(page);
}

void InputRectInMultiImageDialog::keyPressEvent(QKeyEvent *event)
{
	QDialog::keyPressEvent(event);

	if(event->key()==Qt::Key_Control){
		bool ch = m_ui.rbCreateRect->isChecked();
		m_ui.rbCreateRect->setChecked(!ch);
		m_ui.rbShiftImage->setChecked(ch);
		m_ui.wCanvas->update();
	}
}
