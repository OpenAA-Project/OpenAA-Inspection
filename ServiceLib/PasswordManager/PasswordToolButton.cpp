#include "XTypeDef.h"
#include "PasswordToolButton.h"
#include <QMouseEvent>

PasswordToolButton::PasswordToolButton(QWidget *parent)
:QToolButton(parent)
{
	setAcceptDrops(true);
}

void PasswordToolButton::dragEnterEvent(QDragEnterEvent *event)
{
	if(event->mimeData()->hasFormat("Password")){
		event->setDropAction(Qt::LinkAction);
		event->accept();
	}
}

void PasswordToolButton::dragMoveEvent(QDragMoveEvent *event)
{
	if(event->mimeData()->hasFormat("Password")){
		event->setDropAction(Qt::LinkAction);
		event->accept();
	}
}

void PasswordToolButton::dropEvent(QDropEvent *event)
{
	if(event->mimeData()->hasFormat("Password")){
		const PasswordMimeData *mimeData = qobject_cast<const PasswordMimeData *>(event->mimeData());

		if(!mimeData)return;

		QString myName = PasswordFileOperator::createItemName(this);

		myName = text() + "@" + myName + " - " + objectName();

		mimeData->DragFrame->addItem(myName);
	}
}

