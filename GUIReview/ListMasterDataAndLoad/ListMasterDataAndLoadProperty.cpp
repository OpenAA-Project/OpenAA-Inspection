#include "ListMasterDataAndLoadResource.h"
#include "ListMasterDataAndLoadProperty.h"
#include "ListMasterDataAndLoad.h"
#include "../XGUIReviewGlobal.h"

#define ToStr(x) #x

ListMasterDataAndLoadProperty::PropertyBase()
{
	initialize();
}

void ListMasterDataAndLoadProperty::initialize()
{
	MachineIDFilter.clear();
}

QString ListMasterDataAndLoadProperty::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString ListMasterDataAndLoadProperty::sectionName() const
{
	return ReviewGUI::Name::ListMasterDataAndLoad;
}

QString ListMasterDataAndLoadProperty::filename() const
{
	return sectionName();
}

bool ListMasterDataAndLoadProperty::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	if(buffer.hasValue(ToStr(MachineIDFilter))==true){
		MachineIDFilter = toList<int>( buffer.value(ToStr(MachineIDFilter)) );
	}

	return true;
}

SectionBuffer ListMasterDataAndLoadProperty::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	ret.setValue( ToStr(MachineIDFilter), fromList<int>(MachineIDFilter) );

	return ret;
}

void ListMasterDataAndLoadProperty::fromInstance(const ListMasterDataAndLoad *instance)
{
	*this = instance->getProperty();
}

void ListMasterDataAndLoadProperty::toInstance(ListMasterDataAndLoad *instance) const
{
	instance->setProperty(*this);
}

ListMasterDataAndLoadProperty &ListMasterDataAndLoadProperty::operator=(const ListMasterDataAndLoadProperty &other){
	fromBuffer( other.toBuffer() );
	return *this;
}
