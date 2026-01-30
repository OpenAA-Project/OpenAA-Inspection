/*
 * Copyright (C) 2025
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

#ifndef MTIMAGEBUTTONWITHBALLOON_H
#define MTIMAGEBUTTONWITHBALLOON_H

#include <QImage>
#include "mtImageButton.h"
#include "mtPushButtonWithBalloon.h"

class mtImageButtonWithBalloon : public mtImageButton ,public mtButtonWithBalloonBase
{
	Q_OBJECT

public:
	explicit	mtImageButtonWithBalloon(const QImage &_img, QWidget *parent);
	~mtImageButtonWithBalloon();

protected:
	virtual void mouseMoveEvent(QMouseEvent *event)	override;
	virtual void enterEvent(QEnterEvent *event)			override;
	virtual void closeEvent(QCloseEvent *event)		override;
	virtual void mousePressEvent(QMouseEvent *event)override;

signals:
	void SignalEnter();

private slots:
	void SlotMessageMouseMove(int x, int y);

private:
	
};

#endif // MTIMAGEBUTTONWITHBALLOON_H