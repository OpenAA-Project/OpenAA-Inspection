/*
 * Copyright (C) 2012
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

#include "ui_SettingDialog.h"

#include "ReviewStructureItems.h"

class SettingDialog : public QDialog
{
	Q_OBJECT

public:
	SettingDialog(QWidget *parent=NULL);
	~SettingDialog();

public:
	void setSortOrder(Review::OrderOfSortNG order);
	void setSortIndex(int index);
	Review::OrderOfSortNG getSortOrder() const { return (Review::OrderOfSortNG)(getSortIndex()); };
	int getSortIndex() const { return ui.cbSortOrder->currentIndex(); };

public slots:
	void SlotOKClicked();
	void SlotCancelClicked();

private:
	Ui::SettingDialogClass ui;

	int m_oldIndex;
};