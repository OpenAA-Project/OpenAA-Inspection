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
