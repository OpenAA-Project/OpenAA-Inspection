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

#include "ListMasterDataAndLoadResource.h"
#include "ListMasterDataAndLoadProperty.h"
#include "ListMasterDataAndLoad.h"
#include "../XGUIReviewGlobal.h"

#define ToStr(x) #x

ListMasterDataAndLoadProperty::PropertyBase()
{
	initialize();
}

void ListMasterDataAndLoadProperty::initialize()
{
	MachineIDFilter.clear();
}

QString ListMasterDataAndLoadProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString ListMasterDataAndLoadProperty::sectionName() const
{
	return ReviewGUI::Name::ListMasterDataAndLoad;
}

QString ListMasterDataAndLoadProperty::filename() const
{
	return sectionName();
}

bool ListMasterDataAndLoadProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	if(buffer.hasValue(ToStr(MachineIDFilter))==true){
		MachineIDFilter = toList<int>( buffer.value(ToStr(MachineIDFilter)) );
	}

	return true;
}

SectionBuffer ListMasterDataAndLoadProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	ret.setValue( ToStr(MachineIDFilter), fromList<int>(MachineIDFilter) );

	return ret;
}

void ListMasterDataAndLoadProperty::fromInstance(const ListMasterDataAndLoad *instance)
{
	*this = instance->getProperty();
}

void ListMasterDataAndLoadProperty::toInstance(ListMasterDataAndLoad *instance) const
{
	instance->setProperty(*this);
}

ListMasterDataAndLoadProperty &ListMasterDataAndLoadProperty::operator=(const ListMasterDataAndLoadProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}