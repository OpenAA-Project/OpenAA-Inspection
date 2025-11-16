#pragma once

#include <QObject>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QList>
#include <QByteArray>
#include <QLocale>
#include <QMouseEvent>
#include <QMessageBox>
#include <QVector>


#include "PasswordPushButton.h"
#include "InputPasswordFormDialog.h"


#include "PasswordFileOperator.h"

class PasswordEventOperator : public QWidget
{
	Q_OBJECT

public:
	PasswordEventOperator(QWidget *parent=0);
public:
	void addButton(QPushButton **btn);
	void addButton(PasswordPushButton *btn);
public slots:
	static void update();
	static void setUnsealPassword(bool unseal){m_forceUnseal = unseal;};
private:
	bool tryAccess(QAbstractButton *btn, QEvent *event);
private:
	void copyPropaty(QPushButton *dest, QPushButton *source);
	static QString PasswordFilePath();
	static QString CreatePasswordObjectName(QObject *obj);
protected:
	bool eventFilter(QObject *obj, QEvent *event);
private:
	static PasswordFileOperator m_pfo;
	static QVector<bool> m_unsealItems;
	static bool m_isLoaded;
	static bool m_forceUnseal;
};
