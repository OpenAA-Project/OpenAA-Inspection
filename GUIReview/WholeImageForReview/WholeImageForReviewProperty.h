#pragma once

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"
#include "XReviewCommon.h"

class WholeImageForReview;// このプロパティを保有するクラス

template<>
class PropertyBase<WholeImageForReview> : public AbstructProperty
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
	void fromInstance(const WholeImageForReview *instance);
	void toInstance(WholeImageForReview *instance) const;

public:// QObjectは=をサポートしない
	PropertyBase<WholeImageForReview> &operator=(const PropertyBase<WholeImageForReview> &other);

public:
	Qt::Orientation viewFrontBackOrientation;
	Qt::Orientation viewPhaseOrientation;
	bool viewNGNailCross;
	bool viewNGPoint;
	bool viewOnlyCurrentNail;
	Review::Rotate viewFrontRotation;
	Review::Rotate viewBackRotation;
};

typedef PropertyBase<WholeImageForReview> WholeImageForReviewProperty;// 名称変更
