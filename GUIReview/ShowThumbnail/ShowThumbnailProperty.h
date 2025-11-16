#pragma once

#include "ShowThumbnail.h"
#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"

template<>
class PropertyBase<ShowThumbnail> : public AbstructProperty
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
	void fromInstance(const ShowThumbnail *instance);
	void toInstance(ShowThumbnail *instance) const;

public:// QObjectは=をサポートしない
	PropertyBase<ShowThumbnail> &operator=(const PropertyBase<ShowThumbnail> &other);

public:
	int RowCount;
	int ColumnCount;
	int NGSignSize;
	int CheckMillSec;
	ShowThumbnail::_moveMode InitialMoveMode;
	bool MasterPieceImageView;
	bool ExpandThumbnailEnable;
	bool	ModeShowPageByPiece;
	QColor			UncheckedColor;
	QColor			CheckedColor;
	QList<QColor> FKeyColorList;
};

typedef PropertyBase<ShowThumbnail> ShowThumbnailProperty;
