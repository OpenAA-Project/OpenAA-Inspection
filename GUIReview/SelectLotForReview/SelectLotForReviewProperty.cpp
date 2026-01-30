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
#include "SelectLotForReviewProperty.h"
#include "SelectLotForReview.h"
#include "../XGUIReviewGlobal.h"

#define ToStr(x) #x

SelectLotForReviewProperty::PropertyBase()
{
	initialize();
}

void SelectLotForReviewProperty::initialize()
{
	autoShowResultLoadLotForm = true;
}

QString SelectLotForReviewProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString SelectLotForReviewProperty::sectionName() const
{
	return ReviewGUI::Name::SelectLotForReview;
}

QString SelectLotForReviewProperty::filename() const
{
	return sectionName();
}

bool SelectLotForReviewProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	if(buffer.hasValue(ToStr(autoShowResultLoadLotForm))==true){
		autoShowResultLoadLotForm = toBool(buffer.value(ToStr(autoShowResultLoadLotForm)));
	}
	if(buffer.hasValue(ToStr(showOnlyHasError))==true){
		showOnlyHasError = toBool(buffer.value(ToStr(showOnlyHasError)));
	}

	return true;
}

SectionBuffer SelectLotForReviewProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	ret.setValue(ToStr(autoShowResultLoadLotForm), fromBool(autoShowResultLoadLotForm));
	ret.setValue(ToStr(showOnlyHasError), fromBool(showOnlyHasError));

	return ret;
}

void SelectLotForReviewProperty::fromInstance(const SelectLotForReview *instance)
{
	*this = instance->getProperty();
}

void SelectLotForReviewProperty::toInstance(SelectLotForReview *instance) const
{
	instance->setProperty(*this);
}

SelectLotForReviewProperty &SelectLotForReviewProperty::operator=(const SelectLotForReviewProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}