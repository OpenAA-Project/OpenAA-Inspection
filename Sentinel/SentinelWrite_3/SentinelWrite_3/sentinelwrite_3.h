/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinel\SentinelWrite_3\SentinelWrite_3\sentinelwrite_3.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SentinelWRITE_3_H
#define SentinelWRITE_3_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDomNode>
#include <QMessageBox>
#include <QTranslator>
#include "ui_sentinelwrite_3.h"
#include "spromeps.h"

class SentinelWrite_3 : public QMainWindow
{
	Q_OBJECT

public:
	SentinelWrite_3(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~SentinelWrite_3();

private:
	Ui::SentinelWrite_3Class ui;
	int SerialNumber;
	QByteArray SentinelDataArray;
	QByteArray SentinelDataArrayDecrypt;
	QString Copyright;
	QString Usabl;
	QString Serial;
	QString FileName;
	RB_WORD MemCell[56];
	RB_WORD MemCellWrite[56];

	RB_BYTE IsInitialized;			/* Will help to release the Memory if the pkt has been initialized. */
	RB_SPRO_APIPACKET ApiPack;		/* SuperPro packet      */
	RBP_SPRO_APIPACKET ApiPacket;

private slots:
	bool SentinelLogin();
	bool Session();
	bool GetSentinelID();
	bool FileOpen();
	bool FileLoad();
	void Decrypt();
	bool WriteSentinel();
	void on_pbFILEOPEN_clicked();
	void on_pbINSERT_clicked();
	void on_pbDELETE_clicked();
	void on_pbEND_clicked();
};

#endif // SentinelWRITE_3_H
