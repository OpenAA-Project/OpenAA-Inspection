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

#include "ShowHistoryListForReviewResource.h"
#include "ShowHistoryListForReviewProperty.h"
#include "ShowHistoryListForReview.h"
#include "../XGUIReviewGlobal.h"

ShowHistoryListForReviewProperty::PropertyBase()
{}

void ShowHistoryListForReviewProperty::initialize()
{
}

QString ShowHistoryListForReviewProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString ShowHistoryListForReviewProperty::sectionName() const
{
	return ReviewGUI::Name::ShowHistoryListForReview;
}

QString ShowHistoryListForReviewProperty::filename() const
{
	return sectionName();
}

bool ShowHistoryListForReviewProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	return true;
}

SectionBuffer ShowHistoryListForReviewProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	return ret;
}

void ShowHistoryListForReviewProperty::fromInstance(const ShowHistoryListForReview *instance)
{
	*this = instance->getProperty();
}

void ShowHistoryListForReviewProperty::toInstance(ShowHistoryListForReview *instance) const
{
	instance->setProperty(*this);
}

ShowHistoryListForReviewProperty &ShowHistoryListForReviewProperty::operator=(const ShowHistoryListForReviewProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}