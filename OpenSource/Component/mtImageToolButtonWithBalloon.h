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

#ifndef MTIMAGETOOLBUTTONWITHBALLOON_H
#define MTIMAGETOOLBUTTONWITHBALLOON_H

#include <QToolButton>
#include "mtPushButtonWithBalloon.h"
#include "mtImageToolButton.h"

class mtImageToolButtonWithBalloon : public mtImageToolButton, public mtButtonWithBalloonBase
{
	Q_OBJECT

public:
	explicit	mtImageToolButtonWithBalloon(const QImage &_img, QWidget *parent);
	~mtImageToolButtonWithBalloon();

protected:
	virtual void mouseMoveEvent(QMouseEvent *event)	override;
	virtual void enterEvent(QEnterEvent *event)			override;
	virtual void closeEvent(QCloseEvent *event)		override;
	virtual void mousePressEvent(QMouseEvent *event)override;
	virtual	void mouseDoubleClickEvent(QMouseEvent *event)	override;
signals:
	void SignalEnter();
	void	RClick(QMouseEvent * event );
	void	LDoubleClick(QMouseEvent * event );
private slots:
	void SlotMessageMouseMove(int x, int y);

private:
	
};
#endif // MTIMAGETOOLBUTTONWITHBALLOON_H