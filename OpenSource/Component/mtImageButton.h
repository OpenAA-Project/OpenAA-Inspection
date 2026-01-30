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

#ifndef MTIMAGEBUTTON_H
#define MTIMAGEBUTTON_H

#include "mtImageButtonBase.h"
#include <QAbstractButton>
#include <QImage>
#include <QTimer>
#include <QPushButton>

class mtImageButton : public QPushButton, public mtImageButtonBase
{
	Q_OBJECT
	QTimer	TM;
public:
	explicit	mtImageButton(const QImage &_img, QWidget *parent);
	~mtImageButton();

protected:
	int nDrawX;
	int nDrawY;

	virtual void paintEvent(QPaintEvent *evt)			override;
	virtual void mousePressEvent(QMouseEvent *evt)		override;
	virtual void mouseReleaseEvent(QMouseEvent *evt)	override;

signals:
	void SignalClicked();

public slots:
	void	click ();
	virtual	void SlotClicked(bool checked);
	void	TimeOutOneShot();
};

#endif // MTIMAGEBUTTON_H