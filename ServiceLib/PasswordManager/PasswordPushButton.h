#pragma once

#include <QPushButton>
#include <QEvent>

#include "PasswordMimeData.h"

class PasswordPushButton : public QPushButton
{
public:
	PasswordPushButton(QWidget *parent=0);
	
//以下3つの関数はオーバーライド必須
protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);
};
