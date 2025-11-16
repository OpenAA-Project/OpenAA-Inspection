#pragma once

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"

class ShowHistoryListForReview;

template<>
class PropertyBase<ShowHistoryListForReview> : public AbstructProperty
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
	void fromInstance(const ShowHistoryListForReview *instance);
	void toInstance(ShowHistoryListForReview *instance) const;
	
public:// QObjectは=をサポートしない
	PropertyBase<ShowHistoryListForReview> &operator=(const PropertyBase<ShowHistoryListForReview> &other);

public:
};

typedef PropertyBase<ShowHistoryListForReview> ShowHistoryListForReviewProperty;// 名称変更
