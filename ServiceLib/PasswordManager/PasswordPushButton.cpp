/*
 * Copyright (C) 2023
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

#include "XTypeDef.h"
#include "PasswordPushButton.h"
#include <QMouseEvent>

PasswordPushButton::PasswordPushButton(QWidget *parent)
:QPushButton(parent)
{
	setAcceptDrops(true);
}

void PasswordPushButton::dragEnterEvent(QDragEnterEvent *event)
{
	if(event->mimeData()->hasFormat("Password")){
		event->setDropAction(Qt::LinkAction);
		event->accept();
	}
}

void PasswordPushButton::dragMoveEvent(QDragMoveEvent *event)
{
	if(event->mimeData()->hasFormat("Password")){
		event->setDropAction(Qt::LinkAction);
		event->accept();
	}
}

void PasswordPushButton::dropEvent(QDropEvent *event)
{
	if(event->mimeData()->hasFormat("Password")){
		const PasswordMimeData *mimeData = qobject_cast<const PasswordMimeData *>(event->mimeData());

		if(!mimeData)return;

		QString myName = PasswordFileOperator::createItemName(this);

		myName = text() + "@" + myName + " - " + objectName();

		mimeData->DragFrame->addItem(myName);
	}
}
