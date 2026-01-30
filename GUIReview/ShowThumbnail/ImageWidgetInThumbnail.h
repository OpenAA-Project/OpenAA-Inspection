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
#include <QPixmap>
#include <QList>
#include "ReviewStructureItems.h"

class ImageWidgetInThumbnail : public QWidget
{
	Q_OBJECT

public:
	ImageWidgetInThumbnail(QWidget *parent=NULL);
	~ImageWidgetInThumbnail();

public:
	void setPixmap(QPixmap pix){ m_pixmap = pix; };
	QPixmap pixmap(void){ return m_pixmap; };

	void setPoints(QList<ReviewNGPoint> points){ m_points = points; };
	void setTopLeftPoint(QPoint pos){ TopLeftPos = pos; };
	QList<ReviewNGPoint> points(void){ return m_points; };

	void setRound(int round){ m_round = round; };
	int round(void){ return m_round; };

	void setRoundColor(QColor color){ m_color = color; };
	QColor roundColor(void){ return m_color; };

	void setDrawNGSingEnable(bool enable){ if(m_isDrawNGSingEnable!=enable){ m_isDrawNGSingEnable = enable; update(); }; };
	bool isDrawNGSingEnable() const { return m_isDrawNGSingEnable; };

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;

public:
	QPixmap m_pixmap;
	QList<ReviewNGPoint> m_points;
	QPoint TopLeftPos;
	int m_round;
	QColor m_color;
	bool m_isDrawNGSingEnable;
};