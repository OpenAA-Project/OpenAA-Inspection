/*
 * Copyright (C) 2017
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

#include "ShowThumbnailResource.h"
#include "SettingDialog.h"

SettingDialog::SettingDialog(int rowCount, int columnCount, int NGSignSize, QWidget *parent)
:QDialog(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	setModal(false);

	ui.sbRowCount->setValue(rowCount);
	ui.sbColumnCount->setValue(columnCount);
	ui.sbNGSingSize->setValue(NGSignSize);

	connect(ui.sbRowCount, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged()));
	connect(ui.sbColumnCount, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged()));
	connect(ui.sbNGSingSize, SIGNAL(valueChanged(int)), this, SLOT(slotValueChangedNG()));
	connect(ui.cbMasterVisible, SIGNAL(stateChanged(int)), this, SIGNAL(changeCheckedMasterVisible(int)));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(slotOKClicked()));
}

void SettingDialog::setValue(int rowCount, int columnCount)
{
	if(ui.sbRowCount->value()!=rowCount || ui.sbColumnCount->value()!=columnCount){
		ui.sbRowCount->setValue(rowCount);
		ui.sbColumnCount->setValue(columnCount);
	}
}

void SettingDialog::setValue(int NGSingSize)
{
	if(ui.sbNGSingSize->value()!=NGSingSize){
		ui.sbNGSingSize->setValue(NGSingSize);
	}
}

void SettingDialog::setViewMasterCheck(bool check)
{
	if(ui.cbMasterVisible->isChecked()!=check){
		ui.cbMasterVisible->setChecked(check);
	}
}

void SettingDialog::slotValueChanged()
{
	emit valueChanged(ui.sbRowCount->value(), ui.sbColumnCount->value());
}

void SettingDialog::slotValueChangedNG()
{
	emit valueChanged(ui.sbNGSingSize->value());
}

void SettingDialog::slotOKClicked()
{
	if(m_currentSortOrderIndex!=ui.cbSortOrder->currentIndex()){
		emit sortOrderChanged(ui.cbSortOrder->currentIndex());
		m_currentSortOrderIndex = ui.cbSortOrder->currentIndex();
	}
}