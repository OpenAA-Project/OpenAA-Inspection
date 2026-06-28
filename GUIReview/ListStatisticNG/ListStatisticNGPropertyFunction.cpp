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

#include "ListStatisticNGResource.h"
#include "ui_ListStatisticNGPropertyForm.h"
#include "ListStatisticNG.h"
#include "ListStatisticNGProperty.h"
#include "XReviewCommon.h"

void ListStatisticNG::setProperty(const ListStatisticNGProperty &property)
{
	// ??????p?????[?^??X???????L?q????
	(*m_property) = property;
}

void ListStatisticNG::setPropertyToUi(const ListStatisticNGProperty &property)
{
	// ??????p?????[?^????e??Ui????f???????L?q??????
	Ui::ListStatisticNGPropertyClass *ui = getPropertyUi();
	ui->listFKeyPriority->clear();

	QStringList fkeyStrList = getFKeyDefinedNames(true);

	for(int i=0; i<fkeyStrList.count(); i++){
		fkeyStrList[i] = QString(/**/"[F%1]:").arg(i+1, 2, 10, QChar('0')) + fkeyStrList[i];
	}

	QStringList list = Review::sortByPriority(property.PriorityList, fkeyStrList);
	ui->listFKeyPriority->addItems(list);
}

void ListStatisticNG::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void ListStatisticNG::setPropertyFromUi(ListStatisticNGProperty &property)
{
	// ??????Ui????e???p?????[?^????f???????L?q???s????
	Ui::ListStatisticNGPropertyClass *ui = getPropertyUi();

	property.PriorityList.clear();

	QList<int> list;
	QStringList strList = getFKeyDefinedNames(true);
}

void ListStatisticNG::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void ListStatisticNG::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().save();
}

void ListStatisticNG::initProperty()
{
	setProperty(new ListStatisticNGProperty);
	setPropertyUi(new Ui::ListStatisticNGPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
}