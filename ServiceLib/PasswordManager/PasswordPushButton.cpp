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

