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

#include "ui_VRSJoyForm.h"

#include "RadioButtonSelectWidget.h"

class VRSJoyForm : public QWidget
{
	Q_OBJECT

public:
	VRSJoyForm(QWidget *parent);

protected:
	virtual	void paintEvent(QPaintEvent *)		override;
	virtual	void mousePressEvent(QMouseEvent *)	override;
	virtual	void mouseMoveEvent(QMouseEvent *)	override;
	virtual	void enterEvent(QEvent *)			override;
	virtual	void leaveEvent(QEvent *)			override;
	virtual	void resizeEvent(QResizeEvent *)	override;
	virtual	void moveEvent(QMoveEvent *)		override;
	virtual	void wheelEvent(QWheelEvent *)		override;

private slots:
	void setRate(int);

signals:
	void joyout(qreal x, qreal y);// x,y is -1..1, 0 is center.

private:
	Ui::VRSJoyClass ui;
	bool m_isMouseOnView;
	QPoint m_currentPoint;
	quint32 m_maxValue;
	bool m_isXReverse;
	bool m_isYReverse;
	RadioButtonSelectWidget m_rateSelector;
	quint32 m_rate;

public:
	quint32 maxValue() const { return m_maxValue; };
	void setMaxValue(quint32 value){ m_maxValue = value; };
	bool isXReverse() const { return m_isXReverse; };
	void setXReverse(bool reverse){ m_isXReverse = reverse; };
	bool isYReverse() const { return m_isYReverse; };
	void setYReverse(bool reverse){ m_isYReverse = reverse; };

private:
	bool isMouseOnView() const { return m_isMouseOnView; };
	void setMouseOnView(bool ison){ m_isMouseOnView = ison; };
	QPoint currentPoint() const { return m_currentPoint; };
	void setCurrentPoint(const QPoint &pos){ m_currentPoint = pos; };
};