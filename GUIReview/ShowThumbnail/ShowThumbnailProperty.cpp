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

#include "ShowThumbnailResource.h"
#include "ShowThumbnailProperty.h"
#include "ShowThumbnail.h"
#include "../XGUIReviewGlobal.h"

// �ϐ����𕶎����ɕϊ������}�N��
#define ToStr(var) #var

PropertyBase<ShowThumbnail>::PropertyBase()
{
	initialize();
}

void PropertyBase<ShowThumbnail>::initialize()
{
	RowCount = 4;
	ColumnCount = 4;
	NGSignSize = 10;
	CheckMillSec = 0;
	InitialMoveMode = ShowThumbnail::_moveMode::PerPage;
	MasterPieceImageView	= false;
	ExpandThumbnailEnable	= true;
	ModeShowPageByPiece		= true;
	FKeyColorList = Review::getDefaultFKeyColorList();
	MasterPieceImageView = false;
	UncheckedColor	=Qt::gray;
	CheckedColor	=~Qt::green;
}

QString PropertyBase<ShowThumbnail>::baseName() const
{
	return ReviewGUI::Name::SettingFileBase;
}

QString PropertyBase<ShowThumbnail>::sectionName() const
{
	return ReviewGUI::Name::ShowThumbnail;
}

QString PropertyBase<ShowThumbnail>::filename() const
{
	return sectionName();
}

bool PropertyBase<ShowThumbnail>::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return false;
	}

	bool ok;
	int value;

	value = buffer.value(ToStr(RowCount)).toInt(&ok);
	if(ok==true && value>0){
		RowCount = value;
	}else{
		RowCount = 4;
	}

	value = buffer.value(ToStr(ColumnCount)).toInt(&ok);
	if(ok==true && value>0){
		ColumnCount = value;
	}else{
		ColumnCount = 4;
	}
	
	value = buffer.value(ToStr(NGSignSize)).toInt(&ok);
	if(ok==true && value>0){
		NGSignSize = value;
	}else{
		NGSignSize = 10;
	}

	value = buffer.value(ToStr(CheckMillSec)).toInt(&ok);
	if(ok==true && value>0){
		CheckMillSec = value;
	}else{
		CheckMillSec = 0;
	}

	InitialMoveMode = static_cast<ShowThumbnail::_moveMode>(buffer.value(ToStr(InitialMoveMode)).toInt());
	if(InitialMoveMode!=ShowThumbnail::_moveMode::PerThumbnail && InitialMoveMode!=ShowThumbnail::_moveMode::PerPage){
		InitialMoveMode = ShowThumbnail::_moveMode::PerThumbnail;
	}
	MasterPieceImageView = toBool(buffer.value(ToStr(MasterPieceImageView)));
	ExpandThumbnailEnable = toBool(buffer.value(ToStr(ExpandThumbnailEnable)));

	UncheckedColor		=toColor(buffer.value(ToStr(UncheckedColor)));
	CheckedColor		=toColor(buffer.value(ToStr(CheckedColor)));

	FKeyColorList		= toList<QColor>(buffer.value(ToStr(FKeyColorList)));
	ModeShowPageByPiece = toBool(buffer.value(ToStr(ModeShowPageByPiece)));
	return true;
}

SectionBuffer PropertyBase<ShowThumbnail>::toBuffer(void) const
{
	SectionBuffer ret;
	ret.setSectionName(sectionName());

	ret.setValue(ToStr(RowCount), QString::number(RowCount));
	ret.setValue(ToStr(ColumnCount), QString::number(ColumnCount));
	ret.setValue(ToStr(NGSignSize), QString::number(NGSignSize));
	ret.setValue(ToStr(CheckMillSec), QString::number(CheckMillSec));

	ret.setValue(ToStr(InitialMoveMode), QString::number(static_cast<int>(InitialMoveMode)));

	ret.setValue(ToStr(MasterPieceImageView), fromBool(MasterPieceImageView));
	ret.setValue(ToStr(ExpandThumbnailEnable), fromBool(ExpandThumbnailEnable));

	ret.setValue(ToStr(UncheckedColor)	, fromColor(UncheckedColor));
	ret.setValue(ToStr(CheckedColor)	, fromColor(CheckedColor));

	ret.setValue(ToStr(FKeyColorList), fromList(FKeyColorList));
	ret.setValue(ToStr(ModeShowPageByPiece), fromBool(ModeShowPageByPiece));
	return ret;
}

void PropertyBase<ShowThumbnail>::fromInstance(const ShowThumbnail *instance)
{
	*this = instance->getProperty();
}

void PropertyBase<ShowThumbnail>::toInstance(ShowThumbnail *instance) const
{
	instance->setProperty(*this);
}

PropertyBase<ShowThumbnail> &PropertyBase<ShowThumbnail>::operator=(const PropertyBase<ShowThumbnail> &other){
	fromBuffer( other.toBuffer() );
	return *this;
};