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
#include <QPainter>

class StretchImageWidget : public QWidget
{
	Q_OBJECT

public:
	StretchImageWidget(QWidget *parent=NULL, const QImage &image=QImage()):QWidget(parent),m_image(image){};

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override{
		QWidget::paintEvent(event);

		QPainter painter(this);
		QImage sImage = image();
		sImage = sImage.scaled(size(), Qt::KeepAspectRatio);
		painter.drawImage(0, 0, sImage);
	};

public:
	void setImage(const QImage &image){ m_image = image; };
	QImage image(void) const { return m_image; };

signals:
	void requireUpdateImage();

public:
	QImage m_image;
};