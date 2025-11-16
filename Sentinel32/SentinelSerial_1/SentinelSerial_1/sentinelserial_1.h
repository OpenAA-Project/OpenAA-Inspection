/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinel\SentinelSerial_1\SentinelSerial_1\sentinelserial_1.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SENTINELSERIAL_1_H
#define SENTINELSERIAL_1_H

#include <QWidget>
#include <QFileDialog>
#include <QDomNode>
#include <QMessageBox>
#include <QTranslator>
#include "ui_sentinelserial_1.h"
#include "spromeps.h"

class SentinelSerial_1 : public QMainWindow
{
	Q_OBJECT

public:
	SentinelSerial_1(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~SentinelSerial_1();

private:
	Ui::SentinelSerial_1Class ui;
	int SerialNumber;
	QByteArray SerialNumberArray;
	QString FileName;

	RB_BYTE IsInitialized;			/* Will help to release the Memory if the pkt has been initialized. */
	RB_SPRO_APIPACKET ApiPack;		/* SuperPro packet      */
	RBP_SPRO_APIPACKET ApiPacket;

private slots:
	bool SentinelLogin();
	bool Session();
	bool GetSentinelID();
	void Encrypt();
	bool SaveFile();
	bool SaveData();
	void on_pbYES_clicked();
	void on_pbNO_clicked();
};

#endif // SENTINELSERIAL_1_H

