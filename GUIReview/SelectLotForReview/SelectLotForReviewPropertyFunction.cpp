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

#include "SelectLotForReviewResource.h"
#include "ui_SelectLotForReviewPropertyForm.h"
#include "SelectLotForReview.h"
#include "SelectLotForReviewProperty.h"

void SelectLotForReview::setProperty(const SelectLotForReviewProperty &property)
{
	// ??????p?????[?^??X???????L?q????
	(*m_property) = property;
}

void SelectLotForReview::setPropertyToUi(const SelectLotForReviewProperty &property)
{
	// ??????p?????[?^????e??Ui????f???????L?q??????
	Ui::SelectLotForReviewPropertyClass *ui = getPropertyUi();
	ui->gbAutoShowResultLotLoadForm->setChecked(property.autoShowResultLoadLotForm);
	ui->cbShowOnlyError->setChecked(property.showOnlyHasError);
}

void SelectLotForReview::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void SelectLotForReview::setPropertyFromUi(SelectLotForReviewProperty &property)
{
	// ??????Ui????e???p?????[?^????f???????L?q???s????
	Ui::SelectLotForReviewPropertyClass *ui = getPropertyUi();
	property.autoShowResultLoadLotForm = ui->gbAutoShowResultLotLoadForm->isChecked();
	property.showOnlyHasError = ui->cbShowOnlyError->isChecked();
}

void SelectLotForReview::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void SelectLotForReview::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().save();
}

void SelectLotForReview::slot_propertyRejected()
{
	setPropertyToUi();
}

void SelectLotForReview::initProperty()
{
	setProperty(new SelectLotForReviewProperty);
	setPropertyUi(new Ui::SelectLotForReviewPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
	connect(getPropertyDialog(), SIGNAL(rejected()), this, SLOT(slot_propertyRejected()));
}