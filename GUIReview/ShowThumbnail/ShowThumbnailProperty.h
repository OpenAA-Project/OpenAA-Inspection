/*
 * Copyright (C) 2018
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

public:// QObject��=���T�|�[�g���Ȃ�
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