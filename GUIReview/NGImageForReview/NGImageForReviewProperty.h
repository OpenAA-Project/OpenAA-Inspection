#pragma once

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"

#include "XReviewCommon.h"

class NGImageForReview;// このプロパティを保有するクラス

template<>
class PropertyBase<NGImageForReview> : public AbstructProperty
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
	void fromInstance(const NGImageForReview *instance);
	void toInstance(NGImageForReview *instance) const;
	
public:// QObjectは=をサポートしない
	PropertyBase<NGImageForReview> &operator=(const PropertyBase<NGImageForReview> &other);

public:
	Review::Rotate rotate;
	bool	showMessageMissNGImage;
	bool	BlankImageOnCopyMaster;
};

typedef PropertyBase<NGImageForReview> NGImageForReviewProperty;// 名称変更
