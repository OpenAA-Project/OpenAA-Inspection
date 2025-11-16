#include "InputRectInMultiImageWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>
#include <QDebug>

InputRectInMultiImageWidget::InputRectInMultiImageWidget(QWidget *parent)
	:QWidget(parent),m_dragCurrentPosition(),m_dragging(DragState::DragIsNone),m_imageList(),m_outlineList(),m_mouseDragMode(MouseDragMode::ModeDefault),
	m_resultRect(),m_topLeft(0,0),m_zoomStep(0),m_zoomStepLimit(3),m_firstExpand(false),m_zoomStepDefault(0),m_rectAlpha(0xff),m_topPage(0)
{
	setMouseTracking(true);
}

QRect InputRectInMultiImageWidget::createRect(const QPoint &cooner1, const QPoint &cooner2)
{
	return QRect().united(QRect(cooner1, cooner1)).united(QRect(cooner2, cooner2));
}

void InputRectInMultiImageWidget::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);

	QPainter painter(this);
	static bool first = true;

	if(m_firstExpand==true && imageCount()!=0 && size().isValid()==true){
		m_firstExpand = false;

		int maxWidth = 0;
		int maxHeight = 0;
	
		for(int i=0; i<imageCount(); i++){
			maxWidth = qMax( maxWidth, image(i).width() + outline(i).x() );
			maxHeight = qMax( maxHeight, image(i).height() + outline(i).y() );
		}

		QSize canvasSize = size();
		QSize orgSize(maxWidth, maxHeight);
		QSize tempSize = orgSize;

		// 縮小が必要な時のみ
		if(canvasSize.width()<maxWidth && canvasSize.height()<maxHeight){
			tempSize.scale(canvasSize, Qt::KeepAspectRatio);

			int step=0;
			while(tempSize.width()*qPow(2, -step)<=orgSize.width() || tempSize.height()*qPow(2, -step)<=orgSize.height()){
				step--;
			}

			if(zoomStepLimit()<qAbs(step)){
				setZoomStepLimit(qAbs(step));
			}

			setZoomStep(step);
			setZoomStepDefault(step);
		}
	}

	QPen pen;
	pen.setColor(QColor(Qt::black));
	painter.fillRect(rect(), Qt::BrushStyle::SolidPattern);

	QPen edgePen;
	QBrush brush;
	QRect rect;

	switch(mouseDragMode()){
	case MouseDragMode::ModeDefault:
		paintEvent_ModeDefault(event, painter);
		break;
	case MouseDragMode::ModeMakeRect:
		paintEvent_ModeMakeRect(event, painter);
		break;
	case MouseDragMode::ModeShiftImage:
		paintEvent_ModeShiftImage(event, painter);
		break;
	default:
		// None
		break;
	}

	if(mouseDragMode()==MouseDragMode::ModeMakeRect && (dragState()==DragIsNone || dragState()==DragIsEnd)){
		QPen whitePen;
		whitePen.setColor(QColor(Qt::white));

		QPen oldPen = painter.pen();
		QBrush oldBrush = painter.brush();

		painter.setPen(whitePen);
		painter.drawLine(0, dragCurrentPosition().y(), width(), dragCurrentPosition().y());
		painter.drawLine(dragCurrentPosition().x(), 0, dragCurrentPosition().x(), height());

		painter.setPen(oldPen);
		painter.setBrush(oldBrush);
	}

	if(resultRect().isValid()==true){
		QPen cresultPen(QColor(150, 150, 210));
		QBrush cresultBrush(QColor(150, 150, 210, m_rectAlpha), Qt::BrushStyle::Dense4Pattern);
		painter.setPen(cresultPen);
		painter.setBrush(cresultBrush);

		QRect currentResult = resultRectReal();

		qreal currentZoomRateRate = zoomRate()/resultZoomRate();

		if(dragState()==DragState::DragIsNow && mouseDragMode()==MouseDragMode::ModeShiftImage){
			currentResult.moveTopLeft( currentResult.topLeft()*currentZoomRateRate - topLeft() + dragCurrentPosition() - dragStartPosition() );
		}else{
			currentResult.moveTopLeft( currentResult.topLeft()*currentZoomRateRate - topLeft() );
		}

		currentResult.setSize( currentResult.size() * currentZoomRateRate );

		painter.drawRect(currentResult);
	}

	QPen outlinePen;
	outlinePen.setColor(QColor(Qt::black));

	painter.setPen(outlinePen);
	painter.setBrush(Qt::BrushStyle::NoBrush);

	rect = this->rect();

	rect.setWidth( rect.width()-1 );
	rect.setHeight( rect.height()-1 );
	painter.drawRect(rect);
}

void InputRectInMultiImageWidget::mousePressEvent(QMouseEvent *event)
{
	//switch(dragState()){
	//case DragState::DragIsNone:
	//	break;
	//case DragState::DragIsNow:
	//	break;
	//case DragState::DragIsEnd:
	//	break;
	//default:
	//	break;
	//}
	switch(mouseDragMode()){
	case MouseDragMode::ModeDefault:
		mousePressEvent_ModeDefault(event);
		break;
	case MouseDragMode::ModeMakeRect:
		mousePressEvent_ModeMakeRect(event);
		break;
	case MouseDragMode::ModeShiftImage:
		mousePressEvent_ModeShiftImage(event);
		break;
	default:
		// None
		break;
	}
}

void InputRectInMultiImageWidget::mouseMoveEvent(QMouseEvent *event)
{
	switch(mouseDragMode()){
	case MouseDragMode::ModeDefault:
		mouseMoveEvent_ModeDefault(event);
		break;
	case MouseDragMode::ModeMakeRect:
		mouseMoveEvent_ModeMakeRect(event);
		break;
	case MouseDragMode::ModeShiftImage:
		mouseMoveEvent_ModeShiftImage(event);
		break;
	default:
		// None
		break;
	}
}

void InputRectInMultiImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
	//switch(dragState()){
	//case DragState::DragIsNone:
	//	break;
	//case DragState::DragIsNow:
	//	break;
	//case DragState::DragIsEnd:
	//	break;
	//default:
	//	break;
	//}

	switch(mouseDragMode()){
	case MouseDragMode::ModeDefault:
		mouseReleaseEvent_ModeDefault(event);
		break;
	case MouseDragMode::ModeMakeRect:
		mouseReleaseEvent_ModeMakeRect(event);
		break;
	case MouseDragMode::ModeShiftImage:
		mouseReleaseEvent_ModeShiftImage(event);
		break;
	default:
		// None
		break;
	}
}

void InputRectInMultiImageWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	switch(mouseDragMode()){
	case MouseDragMode::ModeDefault:
		mouseDoubleClickEvent_ModeDefault(event);
		break;
	case MouseDragMode::ModeMakeRect:
		mouseDoubleClickEvent_ModeMakeRect(event);
		break;
	case MouseDragMode::ModeShiftImage:
		mouseDoubleClickEvent_ModeShiftImage(event);
		break;
	default:
		break;
	}
}

void InputRectInMultiImageWidget::wheelEvent(QWheelEvent *event)
{
	switch(mouseDragMode()){
	case ModeDefault:
		wheelEvent_ModeDefault(event);
		break;
	case ModeMakeRect:
		wheelEvent_ModeMakeRect(event);
		break;
	case ModeShiftImage:
		wheelEvent_ModeShiftImage(event);
		break;
	default:
		break;
	}

}

void InputRectInMultiImageWidget::setImageList(const QList<QImage> &images, const QList<QPoint> &outlines)
{
	m_imageList = images;
	m_outlineList = outlines;

	if(images.count()>outlines.count()){
		int sum = 0;
		for(int i=0; i<outlines.count(); i++){
			sum += images[i].width();
		}

		for(int i=outlines.count(); i<images.count(); i++){
			m_outlineList << QPoint(sum, 0);
			sum += images[i].width();
		}
	}
}

void InputRectInMultiImageWidget::setTopLeft(const QPoint &topLeft)
{
	m_topLeft = topLeft;
}

bool InputRectInMultiImageWidget::setZoomStep(qint32 step)
{
	qint32 value = qBound(-((qint32)(zoomStepLimit())), step, (qint32)zoomStepLimit());

	if(value==step){
		m_zoomStep = value;
		return true;
	}else{
		return false;
	}
}

bool InputRectInMultiImageWidget::zoomStepIn()
{
	return setZoomStep( zoomStep() + 1 );
}

bool InputRectInMultiImageWidget::zoomStepOut()
{
	return setZoomStep( zoomStep() - 1 );
}

void InputRectInMultiImageWidget::setZoomStepLimit(quint32 stepLimit)
{
	m_zoomStepLimit = stepLimit;
}

void InputRectInMultiImageWidget::setMouseDragMode(MouseDragMode mode)
{
	if(m_mouseDragMode!=mode){
		m_mouseDragMode = mode;
	}
}

qreal InputRectInMultiImageWidget::zoomRate() const
{
	qreal zoom = 1.0;

	if(zoomStep()==0){
		// Zero
	}else if(zoomStep()>0){
		// Plus
		for(int i=0; i<zoomStep(); i++){
			zoom *= stepRate();
		}
	}else{
		// Minus
		for(int i=0; i>zoomStep(); i--){
			zoom /= stepRate();
		}
	}

	return zoom;
}

void InputRectInMultiImageWidget::setDragState(DragState nowDrag)
{
	m_dragging = nowDrag;
}

void InputRectInMultiImageWidget::setDragStartPosition(const QPoint &position)
{
	m_dragStartPosision = position;
}

void InputRectInMultiImageWidget::setDragCurrentPosition(const QPoint &position)
{
	m_dragCurrentPosition = position;
}

void InputRectInMultiImageWidget::calcResultRect()
{
	QPoint viewDragStartPosition = (dragStartPosition() + topLeft()) / zoomRate();
	QPoint viewDragCurrentPosition = (dragCurrentPosition() + topLeft()) / zoomRate();

	QRect rect = createRect(viewDragStartPosition, viewDragCurrentPosition);

	rect.setWidth( rect.width() );
	rect.setHeight( rect.height() );

	setResultRect(rect);
	setResultZoom(zoomRate());
}

void InputRectInMultiImageWidget::setResultRect(const QRect &rect)
{
	m_resultRect = rect;
}

void InputRectInMultiImageWidget::setResultZoom(qreal zoom)
{
	m_resultZoomRate = zoom;
}

void InputRectInMultiImageWidget::clearResultRect()
{
	m_resultRect = QRect();
}

void InputRectInMultiImageWidget::paintImage(QPainter &painter, const QPoint &imageZoomedTopLeft)
{
	QPoint imageTopLeft = imageZoomedTopLeft / zoomRate();// top left position on no zoom
	QRect viewRect( imageTopLeft, size() / zoomRate() );// view port for window on no zoom

	QList<int> pageList;
	for(int i=0; i<imageList().count(); i++){
		if(i!=m_topPage){
			pageList << i;
		}
	}
	pageList.push_front(m_topPage);

	for(int i=0; i<pageList.count(); i++){
		const QImage &img = image(pageList[i]);// image as draw
		QRect imgRect( outline(pageList[i]), img.size() );// rect of image with outline

		if(imgRect.intersects(viewRect)==true){// Do image must draw ?
			QRect inter = imgRect.intersected(viewRect);// a piece of image to draw on window with outline

			QRect copyRect = inter;
			copyRect.moveTopLeft(inter.topLeft() - outline(pageList[i]) );// remove outline, this rect is on the raw image
			
			QPixmap pix;
			if(zoomRate()>=1.0){
				pix = QPixmap::fromImage(img.copy(copyRect));// copy the piece image
				pix = pix.scaled(pix.size()*zoomRate(), Qt::KeepAspectRatio);// scaling to current zoom
			}else{
				QImage drawImage = QImage(copyRect.size() * zoomRate(), img.format());
				
				const QRgb *rgb = (QRgb*)img.bits();
				QRgb *drgb = (QRgb*)drawImage.bits();

				const qreal skipRate = 1.0/zoomRate();
				const int owid = img.width();
				const int hei = drawImage.height();
				const int wid = drawImage.width();
			
				//#pragma omp for
				for(int y=0; y<hei; y++){
					const int sy = int(copyRect.topLeft().y()*owid + y*owid*skipRate);// コピー元
					const int dy = y*wid;// コピー先
					for(int x=0; x<wid; x++){
						const int sx = int(copyRect.topLeft().x() + x*skipRate);
						drgb[dy + x] = rgb[sy + sx];
					}
				}

				//QImage tempImg = img.scaled(img.size() * zoomRate(), Qt::KeepAspectRatio);
				//QRect expCopyRect = copyRect;
				//expCopyRect.moveTopLeft( copyRect.topLeft() * zoomRate() );
				//expCopyRect.setSize( copyRect.size() * zoomRate() );
				//pix = QPixmap::fromImage(tempImg.copy(expCopyRect));

				pix = QPixmap::fromImage(drawImage);
			}

			painter.drawPixmap(inter.topLeft()*zoomRate() - imageZoomedTopLeft, pix);// draw to window
		}
	}
}

// paintEvent parts
void InputRectInMultiImageWidget::paintEvent_ModeDefault(QPaintEvent *, QPainter &painter)
{
	paintImage(painter, topLeft());
}

void InputRectInMultiImageWidget::paintEvent_ModeMakeRect(QPaintEvent *event, QPainter &painter)
{
	paintEvent_ModeDefault(event, painter);

	QPen edgePen;
	QBrush brush;
	QRect rect;

	QPen whitePen;
	whitePen.setColor(QColor(Qt::white));

	//QPen oldPen = painter.pen();
	//QBrush oldBrush = painter.brush();

	//painter.setPen(whitePen);
	//painter.drawLine(0, dragCurrentPosition().y(), width(), dragCurrentPosition().y());
	//painter.drawLine(dragCurrentPosition().x(), 0, dragCurrentPosition().x(), height());

	//painter.setPen(oldPen);
	//painter.setBrush(oldBrush);

	switch(dragState()){
	case DragState::DragIsNone:
		// None
		break;
	case DragState::DragIsNow:
		edgePen.setColor(QColor(210, 150, 150));
			
		brush.setColor(QColor(210, 150, 150, m_rectAlpha));
		brush.setStyle(Qt::BrushStyle::Dense4Pattern);

		painter.setPen(edgePen);
		painter.setBrush(brush);

		painter.drawRect(createRect(dragStartPosition(), dragCurrentPosition()));
			
		break;
	case DragState::DragIsEnd:
		//rect = resultRect();

		//rect.setWidth( rect.width() * zoomRate() );
		//rect.setHeight( rect.height() * zoomRate() );

		//rect.setTopLeft( topLeft() + (rect.topLeft() - topLeft())*zoomRate() );
		//	
		//edgePen.setColor(QColor(210, 150, 150));
		//	
		//brush.setColor(QColor(210, 150, 150));
		//brush.setStyle(Qt::BrushStyle::Dense4Pattern);

		//painter.setPen(edgePen);
		//painter.setBrush(brush);

		//painter.drawRect( rect );

		break;
	default:
		// None
		break;
	}
}

void InputRectInMultiImageWidget::paintEvent_ModeShiftImage(QPaintEvent *event, QPainter &painter)
{

	switch(dragState()){
	case DragState::DragIsNone:
		paintImage(painter, topLeft());
		break;
	case DragState::DragIsNow:
		paintImage(painter, topLeft()-dragCurrentPosition()+dragStartPosition());
		break;
	case DragState::DragIsEnd:
		paintImage(painter, topLeft());
		break;
	default:
		// Nothing
		break;
	}
		
	//QRect copyRect;

	//switch(dragState()){
	//case DragState::DragIsNone:
	//	copyRect.setTopLeft(QPoint(topLeft().x()/zoomRate(), topLeft().y()/zoomRate()));
	//	copyRect.setSize(QSize(width()/zoomRate(), height()/zoomRate()));
	//	break;
	//case DragState::DragIsNow:
	//	copyRect.setTopLeft(QPoint((topLeft()-dragCurrentPosition()+dragStartPosition()).x()/zoomRate(), (topLeft()-dragCurrentPosition()+dragStartPosition()).y()/zoomRate()));
	//	copyRect.setSize(QSize(width()/zoomRate(), height()/zoomRate()));
	//	break;
	//case DragState::DragIsEnd:
	//	copyRect.setTopLeft(QPoint(topLeft().x()/zoomRate(), topLeft().y()/zoomRate()));
	//	copyRect.setSize(QSize(width()/zoomRate(), height()/zoomRate()));
	//	break;
	//default:
	//	// Nothing
	//	break;
	//}
	
	//QPixmap pix = QPixmap::fromImage(image().copy(copyRect));
	//pix = pix.scaled(size(), Qt::KeepAspectRatio);
	//painter.drawPixmap(0, 0, pix);
}

// mousePressEvent parts
void InputRectInMultiImageWidget::mousePressEvent_ModeDefault(QMouseEvent *event)
{
}

void InputRectInMultiImageWidget::mousePressEvent_ModeMakeRect(QMouseEvent *event)
{
	switch(dragState()){
	case DragState::DragIsNone:
		if((event->buttons() & Qt::MouseButton::LeftButton)!=0){
			setDragState(DragState::DragIsNow);

			setDragStartPosition(event->pos());
			setDragCurrentPosition(event->pos());

		}else if((event->buttons() & Qt::MouseButton::RightButton)!=0){
			// None
		}
		break;
	case DragState::DragIsNow:
		if((event->buttons() & Qt::MouseButton::LeftButton)!=0){
			setDragState(DragState::DragIsEnd);
			
			setDragCurrentPosition(event->pos());
			calcResultRect();
			emit rectCreated(resultRect());

		}else if((event->buttons() & Qt::MouseButton::RightButton)!=0){
			setDragState(DragState::DragIsEnd);
		}
		break;
	case DragState::DragIsEnd:
		if((event->buttons() & Qt::MouseButton::LeftButton)!=0){
			setDragState(DragState::DragIsNow);
			setDragStartPosition(event->pos());
			setDragCurrentPosition(event->pos());
		}else if((event->buttons() & Qt::MouseButton::RightButton)!=0){
			setDragState(DragState::DragIsNone);
		}
		break;
	default:
		break;
	}
	update();

}

void InputRectInMultiImageWidget::mousePressEvent_ModeShiftImage(QMouseEvent *event)
{
	switch(dragState()){
	case DragState::DragIsNone:
	case DragState::DragIsNow:
	case DragState::DragIsEnd:
		setDragState(DragState::DragIsNow);
		setDragStartPosition(event->pos());
		setDragCurrentPosition(event->pos());
		update();
		break;
	default:
		break;
	}
}

// mouseMoveEvent parts
void InputRectInMultiImageWidget::mouseMoveEvent_ModeDefault(QMouseEvent *event)
{
	setDragCurrentPosition(event->pos());
}

void InputRectInMultiImageWidget::mouseMoveEvent_ModeMakeRect(QMouseEvent *event)
{
	setDragCurrentPosition(event->pos());
	update();
	//switch(dragState()){
	//case DragState::DragIsNone:
	//	break;
	//case DragState::DragIsNow:
	//	update();
	//	break;
	//case DragState::DragIsEnd:
	//	update();
	//	break;
	//default:
	//	break;
	//}
}

void InputRectInMultiImageWidget::mouseMoveEvent_ModeShiftImage(QMouseEvent *event)
{
	setDragCurrentPosition(event->pos());
	switch(dragState()){
	case DragState::DragIsNone:
		break;
	case DragState::DragIsNow:
		update();
		break;
	case DragState::DragIsEnd:
		break;
	default:
		break;
	}
}

// mouseReleaseEvent parts
void InputRectInMultiImageWidget::mouseReleaseEvent_ModeDefault(QMouseEvent *event)
{
}

void InputRectInMultiImageWidget::mouseReleaseEvent_ModeMakeRect(QMouseEvent *event)
{}

void InputRectInMultiImageWidget::mouseReleaseEvent_ModeShiftImage(QMouseEvent *event)
{
	switch(dragState()){
	case DragState::DragIsNone:
		break;
	case DragState::DragIsNow:
		setDragState(DragState::DragIsEnd);
		setTopLeft( topLeft() - event->pos() + dragStartPosition());
		update();
		break;
	case DragState::DragIsEnd:
		break;
	default:
		break;
	}
}

// mouseDoubleClickEvent parts
void InputRectInMultiImageWidget::mouseDoubleClickEvent_ModeDefault(QMouseEvent *event)
{
	update();
}

void InputRectInMultiImageWidget::mouseDoubleClickEvent_ModeMakeRect(QMouseEvent *event)
{
	if((event->buttons() & Qt::MouseButton::RightButton)!=0){
		setDragState(DragState::DragIsNone);
		update();
	}
}

void InputRectInMultiImageWidget::mouseDoubleClickEvent_ModeShiftImage(QMouseEvent *event)
{
	if((event->buttons() & Qt::MouseButton::RightButton)!=0){
		setDragState(DragState::DragIsNone);
		setTopLeft(QPoint(0,0));
		setZoomStep(zoomStepDefault());
		update();
	}
}

// wheelEvent parts
void InputRectInMultiImageWidget::wheelEvent_ModeDefault(QWheelEvent *event)
{}

void InputRectInMultiImageWidget::wheelEvent_ModeMakeRect(QWheelEvent *event)
{
	if(event->delta()>0){
		m_rectAlpha = qBound(0, m_rectAlpha + 16, 255);
	}else{
		m_rectAlpha = qBound(0, m_rectAlpha - 16, 255);
	}
	update();
}

void InputRectInMultiImageWidget::wheelEvent_ModeShiftImage(QWheelEvent *event)
{
	QPoint tl;
	if(event->delta()>0){
		if(zoomStepIn()==true){

			QPoint currentTopLeft	= topLeft();
			QPoint wheelPoint		= topLeft() + event->pos();
			qreal expandVal			= stepRate();

			tl = (expandVal - 1)*wheelPoint + topLeft();

			setTopLeft( tl );
			update(rect());
		}
	}else{
		if(zoomStepOut()==true){
			QPoint currentTopLeft	= topLeft();
			QPoint wheelPoint		= topLeft() + event->pos();
			qreal expandVal			= stepRate();
			
			tl = (1/expandVal - 1)*wheelPoint + topLeft();

			setTopLeft( tl );
			update(rect());
		}
	}
}
