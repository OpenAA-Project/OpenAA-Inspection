#include "ListStatisticNGResource.h"
#include "ListStatisticNGProperty.h"
#include "ListStatisticNG.h"
#include "XReviewCommon.h"
#include "../XGUIReviewGlobal.h"

#define ToStr(x) #x

ListStatisticNGProperty::PropertyBase()
{
	initialize();
}

void ListStatisticNGProperty::initialize()
{
	PriorityList = QVector<int>(12, 0).toList();
}

QString ListStatisticNGProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString ListStatisticNGProperty::sectionName() const
{
	return ReviewGUI::Name::ListStatisticNG;
}

QString ListStatisticNGProperty::filename() const
{
	return sectionName();
}

bool ListStatisticNGProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	PriorityList = toList<int>(buffer.value(ToStr(PriorityList)));

	Review::resize(12, PriorityList);

	for(int i=0; i<PriorityList.count(); i++){
		PriorityList[i] = i;
	}

	return true;
}

SectionBuffer ListStatisticNGProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	ret.setValue(ToStr(PriorityList), fromList<int>(PriorityList));

	return ret;
}

void ListStatisticNGProperty::fromInstance(const ListStatisticNG *instance)
{
	*this = instance->getProperty();
}

void ListStatisticNGProperty::toInstance(ListStatisticNG *instance) const
{
	instance->setProperty(*this);
}

ListStatisticNGProperty &ListStatisticNGProperty::operator=(const ListStatisticNGProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}
