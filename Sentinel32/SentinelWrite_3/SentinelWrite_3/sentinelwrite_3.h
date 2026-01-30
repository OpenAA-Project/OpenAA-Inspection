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