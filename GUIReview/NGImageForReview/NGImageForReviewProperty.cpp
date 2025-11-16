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
