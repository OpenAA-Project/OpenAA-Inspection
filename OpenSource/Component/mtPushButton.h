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

#ifndef mtPushButton_H
#define mtPushButton_H

#include <QPushButton>

class	mtPushButton : public QPushButton
{
    Q_OBJECT

	QColor	NormalCol;
	QColor	PushedCol;

public:
	explicit	mtPushButton(QWidget *parent = 0);
	explicit	mtPushButton(const QColor &normalcol,const QColor &pushedcol ,QWidget *parent = 0);

	QColor	NormalColor(void);
	QColor	PushedColor(void);
	void	setColor(const QColor &normalcol,const QColor &pushedcol);

signals:
	void	SignalRightClick();

protected:
	virtual	void mousePressEvent ( QMouseEvent * e )	override;
};

#endif