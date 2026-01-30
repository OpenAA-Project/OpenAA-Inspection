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

#include <QtGui>
#include <QGraphicsView>

class StretchImageGraphics : public QGraphicsView
{
	Q_OBJECT

public:
	StretchImageGraphics( QWidget *parent=0);
	~StretchImageGraphics();

public:
	void setImage(const QImage &img);
	void clearImage();
	QImage image(bool scaled=false, Qt::AspectRatioMode mode=Qt::IgnoreAspectRatio) const;

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;

private:
	QImage m_image;
};