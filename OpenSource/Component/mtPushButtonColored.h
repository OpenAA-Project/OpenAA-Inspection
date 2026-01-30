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

#ifndef MTPUSHBUTTONCOLOERED_H
#define MTPUSHBUTTONCOLOERED_H

#include <QPushButton>
#include <QColor>

class	mtPushButtonColored : public QPushButton
{
    Q_OBJECT

	QColor	Col;

public:
	explicit	mtPushButtonColored(QWidget *parent = 0);
	explicit	mtPushButtonColored(const QColor &col ,QWidget *parent = 0);
	~mtPushButtonColored(void);

	QColor	color(void);
	void	setColor(const QColor &col);
	void	setColor(const QString &ColString);

private slots:
	void	SlotClicked();
signals:
	void	SignalClicked();
protected:
	virtual void	paintEvent ( QPaintEvent * event )	override;
};

#endif