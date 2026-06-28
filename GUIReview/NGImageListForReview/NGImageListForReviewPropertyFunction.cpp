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
#include "ui_NGImageListForReviewPropertyForm.h"
#include "NGImageListForReview.h"
#include "NGImageListForReviewProperty.h"

void NGImageListForReview::setProperty(const NGImageListForReviewProperty &property)
{
	// ??????p?????[?^??X???????L?q????
	(*m_property) = property;
}

void NGImageListForReview::setPropertyToUi(const NGImageListForReviewProperty &property)
{
	// ??????p?????[?^????e??Ui????f???????L?q??????
	Ui::NGImageListForReviewPropertyClass *ui = getPropertyUi();

	ui->gbMoveHistoryOnLeftRightKey			->setChecked(property.isMoveHistoryOnLeftRightKey);
	ui->gbMoveHistoryOnEnterKey				->setChecked(property.isMoveHistoryOnEnterKey);
	ui->cbAllCheckOnMoveHistoryByLeftRightKey->setChecked(property.isAllCheckOnMoveHistoryByLeftRightKey);
	ui->cbAllCheckOnMoveHistoryByEnterKey	->setChecked(property.isAllCheckOnMoveHistoryByEnterKey);
	ui->cbIgnoreResultError					->setChecked(property.isIgnoreResultError);
	ui->cbAlwaysOperationPreviousEnable		->setChecked(property.isAlwaysPreviousOperationEnable);
}

void NGImageListForReview::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void NGImageListForReview::setPropertyFromUi(NGImageListForReviewProperty &property)
{
	// ??????Ui????e???p?????[?^????f???????L?q???s????
	Ui::NGImageListForReviewPropertyClass *ui = getPropertyUi();

	property.isMoveHistoryOnLeftRightKey			= ui->gbMoveHistoryOnLeftRightKey->isChecked();
	property.isMoveHistoryOnEnterKey				= ui->gbMoveHistoryOnEnterKey->isChecked();
	property.isAllCheckOnMoveHistoryByLeftRightKey	= ui->cbAllCheckOnMoveHistoryByLeftRightKey->isChecked();
	property.isAllCheckOnMoveHistoryByEnterKey		= ui->cbAllCheckOnMoveHistoryByEnterKey->isChecked();
	property.isIgnoreResultError					= ui->cbIgnoreResultError->isChecked();
	property.isAlwaysPreviousOperationEnable		= ui->cbAlwaysOperationPreviousEnable->isChecked();
}

void NGImageListForReview::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void NGImageListForReview::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().save();
}

void NGImageListForReview::initProperty()
{
	setProperty(new NGImageListForReviewProperty);
	setPropertyUi(new Ui::NGImageListForReviewPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}