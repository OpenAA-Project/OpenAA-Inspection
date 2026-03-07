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

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QPainter>

class ImageWidget : public QWidget
{
public:
	ImageWidget(QWidget *parent=NULL, Qt::WindowFlags f=Qt::WindowFlags())
		:QWidget(parent, f),m_aspectRatioMode(Qt::IgnoreAspectRatio),m_isExpandMode(false),m_pix(),m_topLeft(0,0){};

protected:
	virtual void paintEvent(QPaintEvent *event)	override
	{
		QWidget::paintEvent(event);

		if(pixmap().isNull()==false){
			QPainter painter(this);
			if(isExpandMode()==false){
				painter.drawPixmap(topLeft(), pixmap());
			}else{
				QPixmap pix = pixmap().scaled(size(), aspectRatioMode());
				painter.drawPixmap(topLeft(), pix);
			}
		}
	};

public:
	void setExpandMode(bool expand){ m_isExpandMode = expand; };
	bool isExpandMode() const { return m_isExpandMode; };

	void setAspectRatioMode(Qt::AspectRatioMode mode){ m_aspectRatioMode = mode; };
	Qt::AspectRatioMode aspectRatioMode() const { return m_aspectRatioMode; };

	void setImage(const QPixmap &pix, bool redraw=true){ m_pix = pix; if(redraw){ update(); } };
	void setImage(const QImage &image, bool redraw=true){ setImage(QPixmap::fromImage(image), redraw); };
	QPixmap pixmap() const { return m_pix; };
	
	void setTopLeft(const QPoint &pos){ m_topLeft = pos; };
	void setTopLeft(int x, int y){ setTopLeft(QPoint(x,y)); };
	QPoint topLeft() const { return m_topLeft; };

private:
	bool m_isExpandMode;
	Qt::AspectRatioMode m_aspectRatioMode;
	QPixmap m_pix;
	QPoint m_topLeft;
};