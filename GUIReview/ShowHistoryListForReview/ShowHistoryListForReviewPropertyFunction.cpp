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

#include "ShowHistoryListForReviewResource.h"
#include "ui_ShowHistoryListForReviewPropertyForm.h"
#include "ShowHistoryListForReview.h"
#include "ShowHistoryListForReviewProperty.h"

void ShowHistoryListForReview::setProperty(const ShowHistoryListForReviewProperty &property)
{
	// �����Ƀp�����[�^�ύX�̑Ή����L�q����
	(*m_property) = property;
}

void ShowHistoryListForReview::setPropertyToUi(const ShowHistoryListForReviewProperty &property)
{
	// �����Ƀp�����[�^�̓��e��Ui�ɔ��f�������L�q������
	Ui::ShowHistoryListForReviewPropertyClass *ui = getPropertyUi();
}

void ShowHistoryListForReview::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void ShowHistoryListForReview::setPropertyFromUi(ShowHistoryListForReviewProperty &property)
{
	// ������Ui�̓��e���p�����[�^�ɔ��f�������L�q���s����
	Ui::ShowHistoryListForReviewPropertyClass *ui = getPropertyUi();
}

void ShowHistoryListForReview::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void ShowHistoryListForReview::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void ShowHistoryListForReview::initProperty()
{
	setProperty(new ShowHistoryListForReviewProperty);
	setPropertyUi(new Ui::ShowHistoryListForReviewPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}