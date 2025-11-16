#pragma once

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"

class SelectLotForReview;// このプロパティを保有するクラス

template<>
class PropertyBase<SelectLotForReview> : public AbstructProperty
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
	void fromInstance(const SelectLotForReview *instance);
	void toInstance(SelectLotForReview *instance) const;

public:// QObjectは=をサポートしない
	PropertyBase<SelectLotForReview> &operator=(const PropertyBase<SelectLotForReview> &other);

public:
	bool autoShowResultLoadLotForm;
	bool showOnlyHasError;
};

typedef PropertyBase<SelectLotForReview> SelectLotForReviewProperty;// 名称変更
