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

#include "GUIReviewOpenResource.h"
#include "StretchImageGraphics.h"

StretchImageGraphics::StretchImageGraphics(QWidget *parent)
	:QGraphicsView(parent),m_image()
{}

StretchImageGraphics::~StretchImageGraphics()
{}

void StretchImageGraphics::setImage(const QImage &img)
{
	m_image = img;
	viewport()->update();
}

void StretchImageGraphics::clearImage()
{
	m_image = QImage();
	viewport()->update();
}

QImage StretchImageGraphics::image(bool scaled, Qt::AspectRatioMode mode) const
{
	if(scaled==false){
		return m_image;
	}

	return m_image.scaled(viewport()->size(), mode);
}

void StretchImageGraphics::paintEvent(QPaintEvent *event)
{
	QGraphicsView::paintEvent(event);
	if(m_image.isNull()==true){
		return;
	}

	QPainter painter(viewport());

	QImage img = m_image.scaled(viewport()->size(), Qt::KeepAspectRatio);

	int x = (viewport()->width() - img.width())/2;
	int y = (viewport()->height() - img.height())/2;

	painter.drawImage(x, y, img);
}