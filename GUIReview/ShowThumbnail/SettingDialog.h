/*
 * Copyright (C) 2014
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

#include <QDialog>

#include "ui_SettingForm.h"

class SettingDialog : public QDialog
{
	Q_OBJECT

public:
	SettingDialog(int rowCount, int columnCount, int NGSignSize, QWidget *parent=NULL);

public:
	void setValue(int rowCount, int columnCount);
	void setValue(int NGSignSize);
	void setViewMasterCheck(bool check);
	QPair<int, int> getRowColumnCount(){ return QPair<int, int>(ui.sbRowCount->value(), ui.sbColumnCount->value()); };
	int getNGSignSize(){ return ui.sbNGSingSize->value(); };
	void setCurrentSortOrder(int index){ m_currentSortOrderIndex = index; ui.cbSortOrder->setCurrentIndex(index); };

public slots:
	void slotValueChanged();
	void slotValueChangedNG();
	void slotOKClicked();

signals:
	void valueChanged(int rowCount, int columnCount);
	void valueChanged(int NGSize);
	void changeCheckedMasterVisible(int state);
	void sortOrderChanged(int index);

public:
	Ui::SettingClass ui;
	int m_currentSortOrderIndex;
};