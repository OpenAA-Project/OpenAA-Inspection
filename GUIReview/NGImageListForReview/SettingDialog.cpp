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

#include "NGImageListForReviewResource.h"
#include "SettingDialog.h"

SettingDialog::SettingDialog(QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pbOK, SIGNAL(clicked()), this, SLOT(SlotOKClicked()));
	connect(ui.pbCancel, SIGNAL(clicked()), this, SLOT(SlotCancelClicked()));
}

SettingDialog::~SettingDialog()
{
	QDialog::~QDialog();
}

void SettingDialog::setSortIndex(int index)
{
	if(index<0 || index>=ui.cbSortOrder->count()){
		return;
	}

	ui.cbSortOrder->setCurrentIndex(index);
}

void SettingDialog::setSortOrder(Review::OrderOfSortNG order)
{
	switch(order){
	case Review::OrderOfSortNG::_Order_FromTopLeftToRight:
		setSortIndex(0);
		break;
	case Review::OrderOfSortNG::_Order_FromBottomLeftToRight:
		setSortIndex(1);
		break;
	case Review::OrderOfSortNG::_Order_LibTypeLesser:
		setSortIndex(2);
		break;
	case Review::OrderOfSortNG::_Order_LibTypeGreater:
		setSortIndex(3);
		break;
	case Review::OrderOfSortNG::_Order_NGCauseLesser:
		setSortIndex(4);
		break;
	case Review::OrderOfSortNG::_Order_NGCauseGreater:
		setSortIndex(5);
		break;
	default:
		setSortIndex(0);
		break;
	}
}

void SettingDialog::SlotOKClicked()
{
	accept();
}

void SettingDialog::SlotCancelClicked()
{
	reject();
}