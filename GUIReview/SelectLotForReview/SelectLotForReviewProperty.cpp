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
