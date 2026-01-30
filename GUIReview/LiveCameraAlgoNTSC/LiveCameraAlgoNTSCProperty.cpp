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

#include "LiveCameraAlgoNTSCResource.h"
#include "LiveCameraAlgoNTSCProperty.h"
#include "LiveCameraAlgoNTSC.h"
#include "../XGUIReviewGlobal.h"

LiveCameraAlgoNTSCProperty::PropertyBase()
{}

void LiveCameraAlgoNTSCProperty::initialize()
{
}

QString LiveCameraAlgoNTSCProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString LiveCameraAlgoNTSCProperty::sectionName() const
{
	return ReviewGUI::Name::ListStatisticNG;
}

QString LiveCameraAlgoNTSCProperty::filename() const
{
	return sectionName();
}

bool LiveCameraAlgoNTSCProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	return true;
}

SectionBuffer LiveCameraAlgoNTSCProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	return ret;
}

void LiveCameraAlgoNTSCProperty::fromInstance(const LiveCameraAlgoNTSC *instance)
{
	*this = instance->getProperty();
}

void LiveCameraAlgoNTSCProperty::toInstance(LiveCameraAlgoNTSC *instance) const
{
	instance->setProperty(*this);
}

LiveCameraAlgoNTSCProperty &LiveCameraAlgoNTSCProperty::operator=(const LiveCameraAlgoNTSCProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}