#pragma once

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"

class ButtonToShowTotalNGMap;// このプロパティを保有するクラス

template<>
class PropertyBase<ButtonToShowTotalNGMap> : public AbstructProperty
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
	void fromInstance(const ButtonToShowTotalNGMap *instance);
	void toInstance(ButtonToShowTotalNGMap *instance) const;
	
public:// QObjectは=をサポートしない
	PropertyBase<ButtonToShowTotalNGMap> &operator=(const PropertyBase<ButtonToShowTotalNGMap> &other);

public:
	int SplitCountX;
	int SplitCountY;
	QColor NGDrawColor;
	int NGDrawSize;
	int NGDrawShape;
	bool IgnoreErrorBoard;
};

typedef PropertyBase<ButtonToShowTotalNGMap> ButtonToShowTotalNGMapProperty;// 名称変更
