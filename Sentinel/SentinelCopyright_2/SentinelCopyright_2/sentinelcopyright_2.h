/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinel\SentinelCopyright_2\SentinelCopyright_2\sentinelcopyright_2.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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
