/*
 * Copyright (C) 2025
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

#include <QMetaObject>
#include <QMimeData>
#include <QStringList>

#include "PasswordManager.h"

class PasswordDragFrame;

class PasswordMimeData : public QMimeData
{
	Q_OBJECT

public:
	PasswordMimeData(){
		myFormats << "Password";//�Ǝ��t�H�[�}�b�g
	};

// QMimeData�̉��z�֐��̃I�[�o�[���C�h
public:
	QStringList formats() const{return myFormats;};
protected:
	QVariant retrieveData(const QString &format, QMetaType preferredType) const{
		if(format=="Password"){
			return QString("Password");
		} else {
			return QMimeData::retrieveData(format, preferredType);
		}
	};
public:
	void setDragFrame(PasswordDragFrame *frame){
		DragFrame = frame;
	};
public:
	QStringList		myFormats;
	PasswordDragFrame *DragFrame;
};