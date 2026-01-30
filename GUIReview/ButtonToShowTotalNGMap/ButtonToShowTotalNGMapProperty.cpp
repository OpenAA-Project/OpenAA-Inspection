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

#include "ButtonToShowTotalNGMapResource.h"
#include "ButtonToShowTotalNGMapProperty.h"
#include "ButtonToShowTotalNGMap.h"
#include "../XGUIReviewGlobal.h"

#define ToStr(x) #x

ButtonToShowTotalNGMapProperty::PropertyBase()
{
	initialize();
}

void ButtonToShowTotalNGMapProperty::initialize()
{
	SplitCountX = 100;
	SplitCountY = 100;
	NGDrawColor = QColor(255, 0, 0);
	NGDrawSize = 5;
	NGDrawShape = 0;
	IgnoreErrorBoard = false;
}

QString ButtonToShowTotalNGMapProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString ButtonToShowTotalNGMapProperty::sectionName() const
{
	return ReviewGUI::Name::ButtonToShowTotalNGMap;
}

QString ButtonToShowTotalNGMapProperty::filename() const
{
	return sectionName();
}

bool ButtonToShowTotalNGMapProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	if(buffer.hasValue(ToStr(SplitCountX))==true){
		SplitCountX = buffer.value(ToStr(SplitCountX)).toInt();
	}
	if(buffer.hasValue(ToStr(SplitCountY))==true){
		SplitCountY = buffer.value(ToStr(SplitCountY)).toInt();
	}
	if(buffer.hasValue(ToStr(NGDrawColor))==true){
		NGDrawColor = toColor(buffer.value(ToStr(NGDrawColor)));
	}
	if(buffer.hasValue(ToStr(NGDrawSize))==true){
		NGDrawSize = buffer.value(ToStr(NGDrawSize)).toInt();
	}
	if(buffer.hasValue(ToStr(NGDrawShape))==true){
		NGDrawShape = buffer.value(ToStr(NGDrawShape)).toInt();
	}
	if(buffer.hasValue(ToStr(IgnoreErrorBoard))==true){
		IgnoreErrorBoard = toBool(buffer.value(ToStr(IgnoreErrorBoard)));
	}

	return true;
}

SectionBuffer ButtonToShowTotalNGMapProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	ret.setValue(ToStr(SplitCountX), QString::number(SplitCountX));
	ret.setValue(ToStr(SplitCountY), QString::number(SplitCountY));
	ret.setValue(ToStr(NGDrawColor), fromColor(NGDrawColor));
	ret.setValue(ToStr(NGDrawSize), QString::number(NGDrawSize));
	ret.setValue(ToStr(NGDrawShape), QString::number(NGDrawShape));
	ret.setValue(ToStr(IgnoreErrorBoard), fromBool(IgnoreErrorBoard));

	return ret;
}

void ButtonToShowTotalNGMapProperty::fromInstance(const ButtonToShowTotalNGMap *instance)
{
	*this = instance->getProperty();
}

void ButtonToShowTotalNGMapProperty::toInstance(ButtonToShowTotalNGMap *instance) const
{
	instance->setProperty(*this);
}

ButtonToShowTotalNGMapProperty &ButtonToShowTotalNGMapProperty::operator=(const ButtonToShowTotalNGMapProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}