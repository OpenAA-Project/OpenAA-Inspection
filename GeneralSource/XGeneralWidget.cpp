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

#include "XTypeDef.h"
#include "XGeneralWidget.h"
#include <QMouseEvent>

QPushButtonWithRightClick::QPushButtonWithRightClick(const QIcon &icon, const QString &text, QWidget *parent)
	:QPushButton(icon,text, parent)
{
}
QPushButtonWithRightClick::QPushButtonWithRightClick(const QString &text, QWidget *parent)
	:QPushButton(text, parent)
{
}
QPushButtonWithRightClick::QPushButtonWithRightClick(QWidget *parent)
	:QPushButton(parent)
{
}

void QPushButtonWithRightClick::mouseReleaseEvent(QMouseEvent *e)
{
	QPushButton::mouseReleaseEvent(e);
	if(e->button() == Qt::RightButton){
		emit	RightClicked();
	}
}

//================================================================================================

QToolButtonWithRightClick::QToolButtonWithRightClick(QWidget *parent)
	:QToolButton(parent)
{
}

void QToolButtonWithRightClick::mouseReleaseEvent(QMouseEvent *e)
{
	QToolButton::mouseReleaseEvent(e);
	if(e->button() == Qt::RightButton){
		emit	RightClicked();
	}

}

//================================================================================================

QCheckBoxWithRightClick::QCheckBoxWithRightClick(const QString &text, QWidget *parent)
	:QCheckBox(text,parent)
{
}

QCheckBoxWithRightClick::QCheckBoxWithRightClick(QWidget *parent)
	:QCheckBox(parent)
{
}

void QCheckBoxWithRightClick::mouseReleaseEvent(QMouseEvent *e)
{
	QCheckBox::mouseReleaseEvent(e);
	if(e->button() == Qt::RightButton){
		emit	RightClicked();
	}
}

//================================================================================================

QRadioButtonWithRightClick::QRadioButtonWithRightClick(const QString &text, QWidget *parent)
	:QRadioButton(text,parent)
{
}

QRadioButtonWithRightClick::QRadioButtonWithRightClick(QWidget *parent)
	:QRadioButton(parent)
{
}

void QRadioButtonWithRightClick::mouseReleaseEvent(QMouseEvent *e)
{
	QRadioButton::mouseReleaseEvent(e);
	if(e->button() == Qt::RightButton){
		emit	RightClicked();
	}
}

//================================================================================================

QComboBoxWithRightClick::QComboBoxWithRightClick(QWidget *parent)
	:QComboBox(parent)
{
}

void QComboBoxWithRightClick::mouseReleaseEvent(QMouseEvent *e)
{
	QComboBox::mouseReleaseEvent(e);
	if(e->button() == Qt::RightButton){
		emit	RightClicked();
	}
}

//================================================================================================

QTableWidgetWithRightClick::QTableWidgetWithRightClick(int rows, int columns, QWidget *parent)
	:QTableWidget(rows, columns, parent)
{
}
QTableWidgetWithRightClick::QTableWidgetWithRightClick(QWidget *parent)
	:QTableWidget(parent)
{
}

void QTableWidgetWithRightClick::mousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::RightButton){
		QPoint	P=event->pos();
		QTableWidget::mousePressEvent(event);
		QTableWidgetItem *cell=itemAt(P);
		if(cell!=NULL){
			emit	rightclicked(cell);
		}
	}
	else{
		QTableWidget::mousePressEvent(event);
	}
}

//================================================================================================

QListWidgetWithRightClick::QListWidgetWithRightClick(QWidget *parent)
	:QListWidget(parent)
{
}

void QListWidgetWithRightClick::mousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::RightButton){
		QPoint	P=event->pos();
		QListWidget::mousePressEvent(event);
		QListWidgetItem *cell=itemAt(P);
		if(cell!=NULL){
			emit	rightclicked(cell);
		}
	}
	else{
		QListWidget::mousePressEvent(event);
	}
}

//================================================================================================

QTreeWidgetWithRightClick::QTreeWidgetWithRightClick(QWidget *parent)
	:QTreeWidget(parent)
{
}

void QTreeWidgetWithRightClick::mousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::RightButton){
		QPoint	P=event->pos();
		QTreeWidget::mousePressEvent(event);
		QTreeWidgetItem *cell=itemAt(P);
		if(cell!=NULL){
			emit	rightclicked(cell);
		}
	}
	else{
		QTreeWidget::mousePressEvent(event);
	}
}