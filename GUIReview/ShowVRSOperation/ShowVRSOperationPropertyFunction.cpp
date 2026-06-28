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

#include "ShowVRSOperationResource.h"
#include "ui_ShowVRSOperationPropertyForm.h"
#include "ShowVRSOperation.h"
#include "ShowVRSOperationProperty.h"

void ShowVRSOperation::setProperty(const ShowVRSOperationProperty &property)
{
	// ??????p?????[?^??X???????L?q????
	(*m_property) = property;
}

void ShowVRSOperation::setPropertyToUi(const ShowVRSOperationProperty &property)
{
	// ??????p?????[?^????e??Ui????f???????L?q??????
	Ui::ShowVRSOperationPropertyClass *pui = getPropertyUi();

	pui->sbInitialMoveLength->setValue(property.moveLength);
	pui->sbZDistanceStep->setValue(property.ZDistanceStep);
	ui.sbMoveLength->setValue(property.moveLength);
	ui.cbXReverse->setChecked(property.ReverseX);
	ui.cbYReverse->setChecked(property.ReverseY);
}

void ShowVRSOperation::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void ShowVRSOperation::setPropertyFromUi(ShowVRSOperationProperty &property)
{
	// ??????Ui????e???p?????[?^????f???????L?q???s????
	Ui::ShowVRSOperationPropertyClass *pui = getPropertyUi();

	property.moveLength = ui.sbMoveLength->value();
	property.ZDistanceStep = pui->sbZDistanceStep->value();
	property.ReverseX = ui.cbXReverse->isChecked();
	property.ReverseY = ui.cbYReverse->isChecked();
}

void ShowVRSOperation::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void ShowVRSOperation::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().save();
}

void ShowVRSOperation::initProperty()
{
	setProperty(new ShowVRSOperationProperty);
	setPropertyUi(new Ui::ShowVRSOperationPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}

void ShowVRSOperation::updateMoveLength(int value)
{
	ShowVRSOperationProperty pro;
	pro = getProperty();
	pro.moveLength = value;
	setProperty(pro);
	pro.save();
}

void ShowVRSOperation::updateZDistanceStep(int value)
{
	ShowVRSOperationProperty pro;
	pro = getProperty();
	pro.ZDistanceStep = value;
	setProperty(pro);
	pro.save();
}