/*
 * Copyright (C) 2022
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

#pragma once

#include <QLabel>
#include <QRect>
#include <QRectF>
#include <QMouseEvent>
#include <QWidget>
#include <QPaintEvent>
#include <QPoint>

class InputRectInConstImageLabel : public QLabel
{
public:
	typedef enum {
		DragIsNone,
		DragIsNow,
		DragIsEnd
	} DragState;

public:
	InputRectInConstImageLabel(QWidget *parent=NULL);

public:
	static QRect makeRect(const QPoint &p1, const QPoint &p2){ return QRect(p1, p1).united( QRect(p2,p2) ); };

	QRect resultRect() const { return m_resultRect; };
	void setResultRect(const QRect &rect);
	QRect currentActiveRect() const { return makeRect(dragStartPosition(), dragCurrentPosition()).intersected(activeRect()); };
	void updateResultRect(){ setResultRect(currentActiveRect()); };

	QRectF resultNormalizationRect() const;
	void setResultNormalizationRect(const QRectF &rect) { m_resultNormalizationRect = rect; };
	
	void debugOut() const;

protected:
	virtual	void paintEvent(QPaintEvent *)		override;
	virtual	void mousePressEvent(QMouseEvent *)	override;
	virtual	void mouseMoveEvent(QMouseEvent *)	override;

private:
	void paintEvent_ModeMakeRect(QPaintEvent *, QPainter &);

	void mousePressEvent_ModeMakeRect(QMouseEvent *);
	
	void mouseReleaseEvent_ModeMakeRect(QMouseEvent *);
	
	void mouseMoveEvent_ModeMakeRect(QMouseEvent *);
	
	void mouseDoubleClickEvent_ModeMakeRect(QMouseEvent *);
	
	void wheelEvent_ModeMakeRect(QWheelEvent *);

private:
	DragState dragState() const { return m_dragging; };
	void setDragState(DragState state){ m_dragging = state; };

	QPoint dragStartPosition() const { return m_dragStartPosision; };
	void setDragStartPosition(QPoint point) { m_dragStartPosision = point; };

	QPoint dragCurrentPosition() const { return m_dragCurrentPosition; };
	void setDragCurrentPosition(QPoint point) { m_dragCurrentPosition = point; };

	QRect activeRect() const
	{
		if(pixmap()==NULL || pixmap()->isNull()==true){
			return rect();
		}else{
			return QRect(QPoint(0,0), pixmap()->size());
		}
	};

private:
	QPoint m_topLeft;
	DragState m_dragging;
	QPoint m_dragStartPosision;
	QPoint m_dragCurrentPosition;
	QRect m_resultRect;
	QRectF m_resultNormalizationRect;
	QRect m_activeRect;
};