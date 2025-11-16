#pragma once

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"

class ListMasterDataAndLoad;// このプロパティを保有するクラス

template<>
class PropertyBase<ListMasterDataAndLoad> : public AbstructProperty
{
public:
	PropertyBase();

public:
	void initialize();

public:
	QString baseName() const;
	QString sectionName() const;
	QString filename() const;

public:
	bool fromBuffer(const SectionBuffer &buffer);
	SectionBuffer toBuffer(void) const;
	void fromInstance(const ListMasterDataAndLoad *instance);
	void toInstance(ListMasterDataAndLoad *instance) const;
	
public:// QObjectは=をサポートしない
	PropertyBase<ListMasterDataAndLoad> &operator=(const PropertyBase<ListMasterDataAndLoad> &other);

public:
	QList<int> MachineIDFilter;
};

typedef PropertyBase<ListMasterDataAndLoad> ListMasterDataAndLoadProperty;// 名称変更
