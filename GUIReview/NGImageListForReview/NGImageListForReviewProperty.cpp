#include "NGImageListForReviewResource.h"
#include "NGImageListForReviewProperty.h"
#include "NGImageListForReview.h"
#include "../XGUIReviewGlobal.h"

#define ToStr(x) #x

NGImageListForReviewProperty::PropertyBase()
{
	initialize();
}

void NGImageListForReviewProperty::initialize()
{
	isAllCheckOnMoveHistoryByLeftRightKey = false;
	isAllCheckOnMoveHistoryByEnterKey = false;

	isMoveHistoryOnLeftRightKey = true;
	isMoveHistoryOnEnterKey = true;

	isIgnoreResultError = true;
	isAlwaysPreviousOperationEnable = true;
}

QString NGImageListForReviewProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString NGImageListForReviewProperty::sectionName() const
{
	return ReviewGUI::Name::NGImageListForReview;
}

QString NGImageListForReviewProperty::filename() const
{
	return sectionName();
}

bool NGImageListForReviewProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	if(buffer.hasValue(ToStr(isMoveHistoryOnLeftRightKey))){
		isMoveHistoryOnLeftRightKey = toBool(buffer.value(ToStr(isMoveHistoryOnLeftRightKey)));
	}

	if(buffer.hasValue(ToStr(isMoveHistoryOnEnterKey))){
		isMoveHistoryOnEnterKey = toBool(buffer.value(ToStr(isMoveHistoryOnEnterKey)));
	}

	if(buffer.hasValue(ToStr(isAllCheckOnMoveHistoryByLeftRightKey))){
		isAllCheckOnMoveHistoryByLeftRightKey = toBool(buffer.value(ToStr(isAllCheckOnMoveHistoryByLeftRightKey)));
	}

	if(buffer.hasValue(ToStr(isAllCheckOnMoveHistoryByEnterKey))){
		isAllCheckOnMoveHistoryByEnterKey = toBool(buffer.value(ToStr(isAllCheckOnMoveHistoryByEnterKey)));
	}

	if(buffer.hasValue(ToStr(isIgnoreResultError))){
		isIgnoreResultError = toBool(buffer.value(ToStr(isIgnoreResultError)));
	}

	if(buffer.hasValue(ToStr(isAlwaysPreviousOperationEnable))){
		isAlwaysPreviousOperationEnable = toBool(buffer.value(ToStr(isAlwaysPreviousOperationEnable)));
	}

	return true;
}

SectionBuffer NGImageListForReviewProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	ret.setValue(ToStr(isMoveHistoryOnLeftRightKey), fromBool(isMoveHistoryOnLeftRightKey));
	ret.setValue(ToStr(isMoveHistoryOnEnterKey), fromBool(isMoveHistoryOnEnterKey));
	ret.setValue(ToStr(isAllCheckOnMoveHistoryByLeftRightKey), fromBool(isAllCheckOnMoveHistoryByLeftRightKey));
	ret.setValue(ToStr(isAllCheckOnMoveHistoryByEnterKey), fromBool(isAllCheckOnMoveHistoryByEnterKey));
	ret.setValue(ToStr(isIgnoreResultError), fromBool(isIgnoreResultError));
	ret.setValue(ToStr(isAlwaysPreviousOperationEnable), fromBool(isAlwaysPreviousOperationEnable));
	return ret;
}

void NGImageListForReviewProperty::fromInstance(const NGImageListForReview *instance)
{
	*this = instance->getProperty();
}

void NGImageListForReviewProperty::toInstance(NGImageListForReview *instance) const
{
	instance->setProperty(*this);
}

NGImageListForReviewProperty &NGImageListForReviewProperty::operator=(const NGImageListForReviewProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}
