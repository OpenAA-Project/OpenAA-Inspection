/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinel\SentinelCopyright_2\SentinelCopyright_2\sentinelcopyright_2.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <windows.h>
#include "spromeps.h"
#include "sentinelcopyright_2.h"
#include "sentinel_PnDid.h"

SentinelCopyright_2::SentinelCopyright_2(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
	QTranslator translator;
	translator.load(":/sentinelcopyright_2_ja");
	qApp->installTranslator(&translator);
	ui.setupUi(this);

	// Widget Size
//	setFixedSize(212, 189);
//	setWindowTitle (tr("Copyright File Out"));
//	ui.dateEdit->setDate(QDate::currentDate());
//	ui.lCopyright->setText(tr("Set Copyright Attestation Number(8Digit)"));
//	ui.lUsable->setText(tr("Usable Years"));
//	ui.pbOK->setText(tr("OK"));
//	ui.pbEND->setText(tr("END"));
}

SentinelCopyright_2::~SentinelCopyright_2()
{
}

bool SentinelCopyright_2::FileOpen()
{
	FileName = QFileDialog::getOpenFileName(this, "Open", /**/"", /**/"");

	if (FileName.isEmpty())
		return false;
	else
		return true;
}

bool SentinelCopyright_2::FileLoad()
{
    if (!QFile::exists(FileName))
        return false;

	QFile file(FileName);

	if (!file.open(QFile::ReadOnly))
        return false;

	SerialNumberArray.clear();
	SerialNumberArray = file.readAll();
	file.close();
    return true;
}

void SentinelCopyright_2::Decrypt()
{
	bool boo;

	SerialNumber = SerialNumberArray.toInt(&boo, 16);
	SerialNumber = (SerialNumber ^ DeveloperID) & 0xffff; // ï°çá

	SerialNumberArrayDecrypt.clear();
	SerialNumberArrayDecrypt = QByteArray::number(SerialNumber, 16);
	SerialNumberArrayDecrypt = SerialNumberArrayDecrypt.rightJustified(4, '0');
}

void SentinelCopyright_2::Encrypt()
{
	SentinelDataArray.clear();
	SentinelDataArray.append(SerialNumberArrayDecrypt); // 4 char
	SentinelDataArray.append(Copyright); // 8 char
	SentinelDataArray.append(Usabl); // 8 char

	int isize = SentinelDataArray.size();
	int icont = isize / 2; // odd : n - 1

	for (int i = 0; i < icont; i++)
	{
		unsigned char uctmp;
		int itmp;

		uctmp = SentinelDataArray[i * 2];
		itmp = ((int)uctmp << 8) & 0xff00;
		uctmp = SentinelDataArray[i * 2 + 1];
		itmp |= (int)uctmp & 0xff;

		itmp = (itmp ^ DeveloperID) & 0xffff; // à√çÜ

		uctmp = (itmp >> 8) & 0xff;
		SentinelDataArray[i * 2] = uctmp;
		uctmp = itmp & 0xff;
		SentinelDataArray[i * 2 + 1] = uctmp;
	}
}

bool SentinelCopyright_2::SaveFile()
{
	FileName = QFileDialog::getSaveFileName(this, "Save", "Copyright", /**/"");

	if (FileName.isEmpty())
		return false;
	else
		return true;
}

bool SentinelCopyright_2::SaveData()
{
	QFile file(FileName);

	if (!file.open(QFile::WriteOnly ))
	{
		QMessageBox::warning(this, tr("MDI"), tr("Cannot Write File %1:\n%2.").arg(FileName).arg(file.errorString()));
		return false;
    }

	file.write(SentinelDataArray);
	file.close();
	return true;
}

void SentinelCopyright_2::on_pbOK_clicked()
{
	if (true == ui.lineEdit->text().isEmpty())
	{
		QMessageBox::information(this, "Data Error", "Data Null");
		return;
	}

	if(8 != ui.lineEdit->text().size())
	{
		QMessageBox::information(this, "Data Error", "Eight Digit Input");
		return;
	}

	if (QDate::currentDate() >= ui.dateEdit->date())
	{
		QMessageBox::information(this, "Date Error", "Usable Years Error");
		return;
	}

	QMessageBox::information(this, "Open File", tr("Open The Sentinel Serial File"));

	if (false == FileOpen())
	{
		QMessageBox::information(this, "File Open Error", "Select Not File");
		return;
	}

	Copyright = ui.lineEdit->text();
	Usabl = ui.dateEdit->date().toString("yyyyMMdd");

	if (false == FileLoad())
	{
		QMessageBox::information(this, "File Read Error", "Not File Read");
		return;
	}

	Decrypt();
	Encrypt();

	QMessageBox::information(this, "Save File", tr("Save The Sentinel Lisence File"));

	if (true == SaveFile())
		if (true == SaveData())
			close();
}

void SentinelCopyright_2::on_pbEND_clicked()
{
	close();
}
