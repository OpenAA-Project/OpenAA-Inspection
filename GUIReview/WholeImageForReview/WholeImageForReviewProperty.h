/*
 * Copyright (C) 2012
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

#include "XGUIPacketForDLL.h"
#include "XReviewPropertyBase.h"
#include "XReviewCommon.h"

class WholeImageForReview;// ���̃v���p�e�B���ۗL�����N���X

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

public:// QObject��=���T�|�[�g���Ȃ�
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

typedef PropertyBase<WholeImageForReview> WholeImageForReviewProperty;// ���̕ύX