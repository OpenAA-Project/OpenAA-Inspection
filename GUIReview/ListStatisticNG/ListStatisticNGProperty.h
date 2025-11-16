#pragma once

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"

class ListStatisticNG;// このプロパティを保有するクラス

template<>
class PropertyBase<ListStatisticNG> : public AbstructProperty
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
	void fromInstance(const ListStatisticNG *instance);
	void toInstance(ListStatisticNG *instance) const;
	
public:// QObjectは=をサポートしない
	PropertyBase<ListStatisticNG> &operator=(const PropertyBase<ListStatisticNG> &other);

public:
	QList<int> PriorityList;
};

typedef PropertyBase<ListStatisticNG> ListStatisticNGProperty;// 名称変更
