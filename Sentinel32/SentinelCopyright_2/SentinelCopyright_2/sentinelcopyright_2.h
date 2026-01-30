/*
 * Copyright (C) 2025
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

#ifndef SENTINELCOPYRIGHT_2_H
#define SENTINELCOPYRIGHT_2_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTimeEdit>
#include <QTranslator>
#include <QTextStream>
#include "ui_sentinelcopyright_2.h"
#include "spromeps.h"

class SentinelCopyright_2 : public QMainWindow
{
	Q_OBJECT

public:
	SentinelCopyright_2(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~SentinelCopyright_2();

private:
	Ui::SentinelCopyright_2Class ui;
	int SerialNumber;
	QByteArray SerialNumberArray;
	QByteArray SerialNumberArrayDecrypt;
	QByteArray SentinelDataArray;
	QString Copyright;
	QString Usabl;
	QString FileName;

private slots:
	bool FileOpen();
	bool FileLoad();
	void Decrypt();
	void Encrypt();
	bool SaveFile();
	bool SaveData();
	void on_pbOK_clicked();
	void on_pbEND_clicked();
};

#endif // SENTINELCOPYRIGHT_2_H