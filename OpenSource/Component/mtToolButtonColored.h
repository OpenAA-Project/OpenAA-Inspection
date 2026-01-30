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

#ifndef MTTOOLBUTTONCOLOERED_H
#define MTTOOLBUTTONCOLOERED_H

#include <QToolButton>
#include "mtButtonWithBalloon.h"
#include <QTimer>

class	mtToolButtonColored : public QToolButton,public mtButtonWithBalloonBase
{
    Q_OBJECT

	QColor	Col;
	QColor	PressedCol;
	bool	ColorDialogOnLClick;
	QTimer	TM;
	bool	Pressed;

public:
	explicit	mtToolButtonColored(bool ColorDialogOnLClick ,QWidget *parent = 0);
	explicit	mtToolButtonColored(bool ColorDialogOnLClick ,const QColor &col ,QWidget *parent = 0);
	~mtToolButtonColored(void);

	QColor	color(void)			const;
	void	setColor(const QColor &col);
	void	setColor(const QString &ColString);
	void	setPressedColor(const QColor &col);
	QColor	pressedColor(void)	const	{	return PressedCol;	}

signals:
	void	SignalEnter();
	void	colorChanged();
protected slots:
	void	SlotMessageMouseMove(int x ,int y);
	void	SlotTimeOut();
protected:
	virtual	void mousePressEvent ( QMouseEvent * event )	override;
	virtual void paintEvent ( QPaintEvent * event )			override;
	virtual void mouseMoveEvent ( QMouseEvent * event )		override;
	virtual void enterEvent ( QEnterEvent * event )				override;
	virtual void closeEvent ( QCloseEvent * event )			override;

};

#endif