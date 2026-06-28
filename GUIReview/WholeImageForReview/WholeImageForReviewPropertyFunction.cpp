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

#include "WholeImageForReviewResource.h"
#include "ui_WholeImageForReviewPropertyForm.h"
#include "WholeImageForReview.h"
#include "WholeImageForReviewProperty.h"

void WholeImageForReview::setProperty(const WholeImageForReviewProperty &property)
{
	//// ??????p?????[?^??X???????L?q????
	//// ?c?????????
	//setOrientation(property.viewFrontBackOrientation, property.viewPhaseOrientation);

	//// ????NGNail????S??\???\?????????
	//setNGCrossView(property.viewNGNailCross);

	//// NG??????\?????????
	//setNGPointView(property.viewNGPoint);

	//// ????NGNail???\?????????
	//setOnlyCurrentNGNailRectView(property.viewOnlyCurrentNail);

	(*m_property) = property;

	setPropertyToDisplay();
}

void WholeImageForReview::setPropertyToUi(const WholeImageForReviewProperty &property)
{
	// ??????p?????[?^????e??Ui????f???????L?q??????
	Ui::WholeImageForReviewPropertyClass *ui = getPropertyUi();
	bool isHoriaontal = (property.viewFrontBackOrientation==Qt::Horizontal);
	ui->rbFrontBackHoriaontal->setChecked(isHoriaontal);
	ui->rbFrontBackVertical->setChecked(!isHoriaontal);

	isHoriaontal = (property.viewPhaseOrientation==Qt::Horizontal);
	ui->rbPhaseHoriaontal->setChecked(isHoriaontal);
	ui->rbPhaseVertical->setChecked(!isHoriaontal);

	ui->cbNGNailCrossView->setChecked(property.viewNGNailCross);
	ui->cbNGPointView->setChecked(property.viewNGPoint);
	ui->cbOnlyCurrentNailView->setChecked(property.viewOnlyCurrentNail);
	ui->cbFrontRotation->setCurrentIndex(static_cast<int>(property.viewFrontRotation));
	ui->cbBackRotation->setCurrentIndex(static_cast<int>(property.viewBackRotation));
}

void WholeImageForReview::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void WholeImageForReview::setPropertyFromUi(WholeImageForReviewProperty &property)
{
	// ??????Ui????e???p?????[?^????f???????L?q???s????
	Ui::WholeImageForReviewPropertyClass *ui = getPropertyUi();
	property.viewFrontBackOrientation = (ui->rbFrontBackHoriaontal->isChecked() ? Qt::Horizontal : Qt::Vertical);
	property.viewPhaseOrientation = (ui->rbPhaseHoriaontal->isChecked() ? Qt::Horizontal : Qt::Vertical);
	property.viewNGNailCross = ui->cbNGNailCrossView->isChecked();
	property.viewNGPoint = ui->cbNGPointView->isChecked();
	property.viewOnlyCurrentNail = ui->cbOnlyCurrentNailView->isChecked();
	property.viewFrontRotation = static_cast<Review::Rotate>(ui->cbFrontRotation->currentIndex());
	property.viewBackRotation = static_cast<Review::Rotate>(ui->cbBackRotation->currentIndex());
}

void WholeImageForReview::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void WholeImageForReview::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().save();
	updateGUI();
}

void WholeImageForReview::initProperty()
{
	setProperty(new WholeImageForReviewProperty);
	setPropertyUi(new Ui::WholeImageForReviewPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
	connect(getPropertyUi()->pbApply, SIGNAL(clicked()), this, SLOT(slot_propertyModified()));
}