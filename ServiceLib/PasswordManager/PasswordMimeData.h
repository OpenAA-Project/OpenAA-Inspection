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
		myFormats << "Password";//独自フォーマット
	};

// QMimeDataの仮想関数のオーバーライド
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
