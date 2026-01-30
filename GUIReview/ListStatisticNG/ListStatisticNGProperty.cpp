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
#include "ListStatisticNGProperty.h"
#include "ListStatisticNG.h"
#include "XReviewCommon.h"
#include "../XGUIReviewGlobal.h"

#define ToStr(x) #x

ListStatisticNGProperty::PropertyBase()
{
	initialize();
}

void ListStatisticNGProperty::initialize()
{
	PriorityList = QVector<int>(12, 0).toList();
}

QString ListStatisticNGProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString ListStatisticNGProperty::sectionName() const
{
	return ReviewGUI::Name::ListStatisticNG;
}

QString ListStatisticNGProperty::filename() const
{
	return sectionName();
}

bool ListStatisticNGProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	PriorityList = toList<int>(buffer.value(ToStr(PriorityList)));

	Review::resize(12, PriorityList);

	for(int i=0; i<PriorityList.count(); i++){
		PriorityList[i] = i;
	}

	return true;
}

SectionBuffer ListStatisticNGProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	ret.setValue(ToStr(PriorityList), fromList<int>(PriorityList));

	return ret;
}

void ListStatisticNGProperty::fromInstance(const ListStatisticNG *instance)
{
	*this = instance->getProperty();
}

void ListStatisticNGProperty::toInstance(ListStatisticNG *instance) const
{
	instance->setProperty(*this);
}

ListStatisticNGProperty &ListStatisticNGProperty::operator=(const ListStatisticNGProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}