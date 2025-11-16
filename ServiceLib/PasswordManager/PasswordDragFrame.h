#pragma once

#include <QApplication>
#include <QFrame>
#include <QFileInfo>
#include <QTextStream>
#include <QPainter>
#include <QPixmap>
//#include <QGlobal.h>
#include <QMouseEvent>
#include <QStringList>

#include "PasswordMimeData.h"//専用MimeData
#include "PasswordFileOperator.h"

//ドラッグ用クラス
class PasswordDragFrame : public QFrame
{
	Q_OBJECT

public:
	PasswordDragFrame(QWidget *parent);
//以下2つの関数はオーバーライド必須
protected:
	virtual	void mousePressEvent( QMouseEvent *event )	override;
	virtual	void mouseMoveEvent( QMouseEvent *event )	override;
	virtual	void paintEvent(QPaintEvent*)				override;

public:
	void setPasswordFileOperator(PasswordFileOperator *pfo);
	QString PasswordFilePath();
private:
	QString m_FilePath;
	void startDrag();
	QPoint startPos;
public:
	PasswordFileOperator *m_pfo;
public:
	void addItem(QString ItemName);
};
