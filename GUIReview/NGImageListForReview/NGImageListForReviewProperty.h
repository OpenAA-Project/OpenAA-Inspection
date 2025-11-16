#pragma once

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"

class NGImageListForReview;// このプロパティを保有するクラス

template<>
class PropertyBase<NGImageListForReview> : public AbstructProperty
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
	void fromInstance(const NGImageListForReview *instance);
	void toInstance(NGImageListForReview *instance) const;
	
public:// QObjectは=をサポートしない
	PropertyBase<NGImageListForReview> &operator=(const PropertyBase<NGImageListForReview> &other);

public:
	bool isMoveHistoryOnLeftRightKey;
	bool isAllCheckOnMoveHistoryByLeftRightKey;

	bool isMoveHistoryOnEnterKey;
	bool isAllCheckOnMoveHistoryByEnterKey;

	bool isIgnoreResultError;
	bool isAlwaysPreviousOperationEnable;
};

typedef PropertyBase<NGImageListForReview> NGImageListForReviewProperty;// 名称変更
