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

#include "NGImageForReviewResource.h"
#include "ui_NGImageForReviewPropertyForm.h"
#include "NGImageForReview.h"
#include "NGImageForReviewProperty.h"

void NGImageForReview::setProperty(const NGImageForReviewProperty &property)
{
	// ??????p?????[?^??X???????L?q????
	(*m_property) = property;
}

void NGImageForReview::setPropertyToUi(const NGImageForReviewProperty &property)
{
	// ??????p?????[?^????e??Ui????f???????L?q??????
	Ui::NGImageForReviewPropertyClass *m_ui = getPropertyUi();
	m_ui->cbRotate->setCurrentIndex(static_cast<int>(property.rotate));
	m_ui->checkBoxBlankImageOnCopyMaster	->setChecked(property.BlankImageOnCopyMaster);
}

void NGImageForReview::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void NGImageForReview::setPropertyFromUi(NGImageForReviewProperty &property)
{
	// ??????Ui????e???p?????[?^????f???????L?q???s????
	Ui::NGImageForReviewPropertyClass *m_ui = getPropertyUi();
	property.rotate					= static_cast<Review::Rotate>(m_ui->cbRotate->currentIndex());
	property.BlankImageOnCopyMaster	=m_ui->checkBoxBlankImageOnCopyMaster->isChecked();
}

void NGImageForReview::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void NGImageForReview::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().save();
}

void NGImageForReview::initProperty()
{
	setProperty(new NGImageForReviewProperty);
	setPropertyUi(new Ui::NGImageForReviewPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	connect(getPropertyUi()->cbRotate, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_propertyModified()));
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}