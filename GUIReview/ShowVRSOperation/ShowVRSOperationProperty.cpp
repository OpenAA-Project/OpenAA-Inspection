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
#include "ShowVRSOperationProperty.h"
#include "ShowVRSOperation.h"
#include "../XGUIReviewGlobal.h"

#define ToStr(x) #x

ShowVRSOperationProperty::PropertyBase()
{
	initialize();
}

void ShowVRSOperationProperty::initialize()
{
	moveLength = 0;
	ZDistanceStep = 0;
	ReverseX = false;
	ReverseY = false;
}

QString ShowVRSOperationProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString ShowVRSOperationProperty::sectionName() const
{
	return ReviewGUI::Name::ShowVRSOperation;
}

QString ShowVRSOperationProperty::filename() const
{
	return sectionName();
}

bool ShowVRSOperationProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	if(buffer.hasValue(ToStr(moveLength))==true){
		moveLength = buffer.value(ToStr(moveLength)).toInt();
	}
	
	if(buffer.hasValue(ToStr(ZDistanceStep))==true){
		ZDistanceStep = buffer.value(ToStr(ZDistanceStep)).toInt();
	}
	
	if(buffer.hasValue(ToStr(ReverseX))==true){
		ReverseX = toBool(buffer.value(ToStr(ReverseX)));
	}

	if(buffer.hasValue(ToStr(ReverseY))==true){
		ReverseY = toBool(buffer.value(ToStr(ReverseY)));
	}

	return true;
}

SectionBuffer ShowVRSOperationProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	ret.setValue(ToStr(moveLength), QString::number(moveLength));
	ret.setValue(ToStr(ZDistanceStep), QString::number(ZDistanceStep));
	ret.setValue(ToStr(ReverseX), fromBool(ReverseX));
	ret.setValue(ToStr(ReverseY), fromBool(ReverseY));

	return ret;
}

void ShowVRSOperationProperty::fromInstance(const ShowVRSOperation *instance)
{
	*this = instance->getProperty();
}

void ShowVRSOperationProperty::toInstance(ShowVRSOperation *instance) const
{
	instance->setProperty(*this);
}

ShowVRSOperationProperty &ShowVRSOperationProperty::operator=(const ShowVRSOperationProperty &other)
{
	fromBuffer( other.toBuffer() );
	return *this;
}