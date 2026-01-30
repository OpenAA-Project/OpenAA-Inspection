/*
 * Copyright (C) 2023
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

#ifndef MTIMAGEBUTTONCOLORED_H
#define MTIMAGEBUTTONCOLORED_H

#include "mtImageButton.h"
#include <QImage>

class mtImageButtonColored : public mtImageButton
{
	Q_OBJECT

public:
	explicit	mtImageButtonColored(const QImage &_img, const QColor &_col, QWidget *parent);
	explicit	mtImageButtonColored(const QImage &_img, QWidget *parent);
	~mtImageButtonColored();

	QColor color()	const;
	void setColor(const QColor &col);
	void setColor(const QString &ColString);

protected:
	QImage img2;
	QColor Col;
	float nBlend_Alfa;

private:
	void setImageCombine();
};

#endif // MTIMAGEBUTTONCOLORED_H