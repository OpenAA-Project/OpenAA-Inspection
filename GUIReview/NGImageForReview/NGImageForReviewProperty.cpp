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
#include "NGImageForReviewProperty.h"
#include "NGImageForReview.h"
#include "../XGUIReviewGlobal.h"

#define ToStr(x) #x

NGImageForReviewProperty::PropertyBase()
{
	initialize();
}

void NGImageForReviewProperty::initialize()
{
	rotate = Review::Rotate::Rotate_0;
	BlankImageOnCopyMaster	=true;
}

QString NGImageForReviewProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString NGImageForReviewProperty::sectionName() const
{
	return ReviewGUI::Name::NGImageForReview;
}

QString NGImageForReviewProperty::filename() const
{
	return sectionName();
}

bool NGImageForReviewProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	if(buffer.hasValue(ToStr(rotate))==true){
		rotate = Review::toRotateFromInt(buffer.value(ToStr(rotate)).toInt());
	}
	if(buffer.hasValue(ToStr(isMoveHistoryOnLeftRightKey))){
		BlankImageOnCopyMaster = toBool(buffer.value(ToStr(BlankImageOnCopyMaster)));
	}

	return true;
}

SectionBuffer NGImageForReviewProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	ret.setValue(ToStr(rotate), QString::number(Review::toIntFromRotate(rotate)));
	ret.setValue(ToStr(BlankImageOnCopyMaster), fromBool(BlankImageOnCopyMaster));
	return ret;
}

void NGImageForReviewProperty::fromInstance(const NGImageForReview *instance)
{
	*this = instance->getProperty();
}

void NGImageForReviewProperty::toInstance(NGImageForReview *instance) const
{
	instance->setProperty(*this);
}

NGImageForReviewProperty &NGImageForReviewProperty::operator=(const NGImageForReviewProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}