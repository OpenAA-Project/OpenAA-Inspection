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
#include "WholeImageForReviewProperty.h"
#include "WholeImageForReview.h"
#include "../XGUIReviewGlobal.h"

// �ϐ����𕶎����ɕϊ������}�N��
#define ToStr(var) #var

WholeImageForReviewProperty::PropertyBase()
{
	initialize();
}

void WholeImageForReviewProperty::initialize()
{
	viewFrontBackOrientation = Qt::Vertical;
	viewPhaseOrientation = Qt::Horizontal;
	viewNGNailCross = false;
	viewNGPoint = true;
	viewOnlyCurrentNail = true;
	viewFrontRotation = Review::Rotate::Rotate_0;
	viewBackRotation = Review::Rotate::Rotate_0;
}

QString WholeImageForReviewProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString WholeImageForReviewProperty::sectionName() const
{
	return ReviewGUI::Name::WholeImageForReview;
}

QString WholeImageForReviewProperty::filename() const
{
	return sectionName();
}

bool WholeImageForReviewProperty::fromBuffer(const SectionBuffer &buffer){
	if(sectionName()!=buffer.sectionName()){
		return false;
	}
	
	viewFrontBackOrientation = static_cast<Qt::Orientation>(buffer.value(ToStr(viewFrontBackOrientation)).toInt());
	viewPhaseOrientation = static_cast<Qt::Orientation>(buffer.value(ToStr(viewPhaseOrientation)).toInt());
	viewNGNailCross = toBool(buffer.value(ToStr(viewNGNailCross)));
	viewNGPoint = toBool(buffer.value(ToStr(viewNGPoint)));
	viewOnlyCurrentNail = toBool(buffer.value(ToStr(viewOnlyCurrentNail)));
	viewFrontRotation = static_cast<Review::Rotate>(buffer.value(ToStr(viewFrontRotation)).toInt());
	viewBackRotation = static_cast<Review::Rotate>(buffer.value(ToStr(viewBackRotation)).toInt());

	return true;
}

SectionBuffer WholeImageForReviewProperty::toBuffer(void) const {
	SectionBuffer ret;

	ret.setSectionName(sectionName());
	ret.setValue(ToStr(viewFrontBackOrientation), QString::number(viewFrontBackOrientation));
	ret.setValue(ToStr(viewPhaseOrientation), QString::number(viewPhaseOrientation));
	ret.setValue(ToStr(viewNGNailCross), fromBool(viewNGNailCross));
	ret.setValue(ToStr(viewNGPoint), fromBool(viewNGPoint));
	ret.setValue(ToStr(viewOnlyCurrentNail), fromBool(viewOnlyCurrentNail));
	ret.setValue(ToStr(viewFrontRotation), QString::number(static_cast<int>(viewFrontRotation)));
	ret.setValue(ToStr(viewBackRotation), QString::number(static_cast<int>(viewBackRotation)));

	return ret;
}

void WholeImageForReviewProperty::fromInstance(const WholeImageForReview *instance)
{
	(*this) = instance->getProperty();
}
void WholeImageForReviewProperty::toInstance(WholeImageForReview *instance) const
{
	instance->setProperty(*this);
}

WholeImageForReviewProperty &WholeImageForReviewProperty::operator=(const WholeImageForReviewProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}