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
