#pragma once

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"

class ShowVRSOperation;// このプロパティを保有するクラス

template<>
class PropertyBase<ShowVRSOperation> : public AbstructProperty
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
	void fromInstance(const ShowVRSOperation *instance);
	void toInstance(ShowVRSOperation *instance) const;
	
public:// QObjectは=をサポートしない
	PropertyBase<ShowVRSOperation> &operator=(const PropertyBase<ShowVRSOperation> &other);

public:
	int moveLength;
	int ZDistanceStep;
	bool ReverseX;
	bool ReverseY;
};

typedef PropertyBase<ShowVRSOperation> ShowVRSOperationProperty;// 名称変更
