#pragma once

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"

class LiveCameraAlgoNTSC;// このプロパティを保有するクラス

template<>
class PropertyBase<LiveCameraAlgoNTSC> : public AbstructProperty
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
	void fromInstance(const LiveCameraAlgoNTSC *instance);
	void toInstance(LiveCameraAlgoNTSC *instance) const;
	
public:// QObjectは=をサポートしない
	PropertyBase<LiveCameraAlgoNTSC> &operator=(const PropertyBase<LiveCameraAlgoNTSC> &other);

public:
};

typedef PropertyBase<LiveCameraAlgoNTSC> LiveCameraAlgoNTSCProperty;// 名称変更
