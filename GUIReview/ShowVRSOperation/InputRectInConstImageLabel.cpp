/*
 * Copyright (C) 2017
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ShowVRSOperationResource.h"
#include "InputRectInConstImageLabel.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

InputRectInConstImageLabel::InputRectInConstImageLabel(QWidget *parent)
	:QLabel(parent),m_activeRect(),m_dragCurrentPosition(0,0),m_dragging(DragState::DragIsNone),m_dragStartPosision(0,0),m_resultRect(),m_topLeft(0,0)
{
	setAlignment(Qt::AlignLeft | Qt::AlignTop);
	setMouseTracking(true);
}

void InputRectInConstImageLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);

	QPainter painter(this);

	if(pixmap().isNull()==false){
		painter.drawPixmap(0, 0, pixmap());
	}

	QPen edgePen;
	QBrush brush;
	QRect rect;

	switch(dragState()){
	case DragState::DragIsNone:
		// None
		break;
	case DragState::DragIsNow:
		edgePen.setColor(QColor(210, 150, 150));
			
		brush.setColor(QColor(210, 150, 150));
		brush.setStyle(Qt::BrushStyle::Dense4Pattern);

		painter.setPen(edgePen);
		painter.setBrush(brush);

		painter.drawRect(currentActiveRect());
			
		break;
	case DragState::DragIsEnd:
		// None
		break;
	default:
		// None
		break;
	}

	if(resultRect().isValid()==true){
		QPen cresultPen(QColor(150, 150, 210));
		QBrush cresultBrush(QColor(150, 150, 210), Qt::BrushStyle::Dense4Pattern);
		painter.setPen(cresultPen);
		painter.setBrush(cresultBrush);

		painter.drawRect(resultRect());
	}
	
	if(dragState()==DragIsNone || dragState()==DragIsEnd){
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
}

void InputRectInConstImageLabel::mouseMoveEvent(QMouseEvent *event)
{
	QLabel::mouseMoveEvent(event);

	setDragCurrentPosition(event->pos());
	update();
}


void InputRectInConstImageLabel::mousePressEvent(QMouseEvent *event)
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
		update();
		break;
	case DragState::DragIsNow:
		if((event->buttons() & Qt::MouseButton::LeftButton)!=0){
			setDragState(DragState::DragIsEnd);
			
			setDragCurrentPosition(event->pos());

			updateResultRect();

		}else if((event->buttons() & Qt::MouseButton::RightButton)!=0){
			setDragState(DragState::DragIsEnd);
		}
		update();
		break;
	case DragState::DragIsEnd:
		if((event->buttons() & Qt::MouseButton::LeftButton)!=0){
			setDragState(DragState::DragIsNow);
			setDragStartPosition(event->pos());
			setDragCurrentPosition(event->pos());

		}else if((event->buttons() & Qt::MouseButton::RightButton)!=0){
			setDragState(DragState::DragIsNone);
			setResultRect(QRect());
		}

		update();
		break;
	default:
		break;
	}
}

void InputRectInConstImageLabel::setResultRect(const QRect &rect){
	m_resultRect = rect;
	setResultNormalizationRect(
		QRectF(resultRect().left()/(qreal)activeRect().width(),
		resultRect().top()/(qreal)activeRect().height(),
		resultRect().width()/(qreal)activeRect().width(),
		resultRect().height()/(qreal)activeRect().height())
		);
}

QRectF InputRectInConstImageLabel::resultNormalizationRect() const {
	debugOut();
	if(m_resultNormalizationRect.isValid()==true){
		return m_resultNormalizationRect;
	}else{
		return QRectF(
			resultRect().left()/(qreal)activeRect().width(),
			resultRect().top()/(qreal)activeRect().height(),
			resultRect().width()/(qreal)activeRect().width(),
			resultRect().height()/(qreal)activeRect().height()
			);
	}
}

void InputRectInConstImageLabel::debugOut() const
{
	//qDebug() << "DragStartPosision" << m_dragStartPosision;
	//qDebug() << "DragCurrentPosition" << m_dragCurrentPosition;
	//qDebug() << "ActiveRect" << activeRect();
	//qDebug() << "ResultRect" << m_resultRect;
	//qDebug() << "ResultNormalizedRect" << m_resultNormalizationRect;
	//qDebug() << "";
}