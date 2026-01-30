/*
 * Copyright (C) 2014
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

#include <QStackedWidget>
#include <QGridLayout>

#include "Thumbnail.h"

// �y�[�W�ꖇ��
// �P����QGridLayout�������A�S�̂ɕ\������
// 
class ThumbnailPage : public QWidget
{
public:
	ThumbnailPage(QWidget *parent=NULL)
		:QWidget(parent)
	{
		mainLayout = new QGridLayout(this);
		mainLayout->setSpacing(6);
		mainLayout->setObjectName(QString::fromUtf8(/**/"mainLayout"));
	};
	~ThumbnailPage(){
		delete mainLayout;
	};

	void addThumnail(Thumbnail *item){
		mainLayout->addWidget(item, item->getRow(), item->getColumn(), 1, 1);
	};

	void removeThumbnail(Thumbnail *item){
		mainLayout->removeWidget(item);
	};

	int count() const { return mainLayout->count(); };

	inline const Thumbnail *item(int index) const {
		return dynamic_cast<Thumbnail *>(mainLayout->itemAt(index)->widget());
	};

	inline Thumbnail *item(int index) {
		return dynamic_cast<Thumbnail *>(mainLayout->itemAt(index)->widget());
	};

private:
	QGridLayout *mainLayout;
};