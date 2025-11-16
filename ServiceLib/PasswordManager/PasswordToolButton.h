#pragma once

#include <QToolButton>

#include "PasswordMimeData.h"

class PasswordToolButton : public QToolButton
{
public:
	PasswordToolButton(QWidget *parent=0);
	
//以下3つの関数はオーバーライド必須
protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);
};