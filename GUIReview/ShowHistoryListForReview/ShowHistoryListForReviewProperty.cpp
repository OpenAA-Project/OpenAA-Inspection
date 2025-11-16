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
