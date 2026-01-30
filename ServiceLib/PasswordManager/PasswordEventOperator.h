/*
 * Copyright (C) 2012
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