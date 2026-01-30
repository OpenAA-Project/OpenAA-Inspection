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
