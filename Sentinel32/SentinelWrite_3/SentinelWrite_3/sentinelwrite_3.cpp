/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinel\SentinelWrite_3\SentinelWrite_3\sentinelwrite_3.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <windows.h>
#include "spromeps.h"
#include "sentinelwrite_3.h"
#include "sentinel_PnDid.h"

SentinelWrite_3::SentinelWrite_3(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
	QTranslator translator;
	translator.load(":/sentinelwrite_3_ja");
	qApp->installTranslator(&translator);
	ui.setupUi(this);

	// Widget Size
	setFixedSize(430, 211);

	// Widget Title
	setWindowTitle(tr("Copyright Validation Code Writing"));

	//TableWidget HeaderTitle
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << tr("Copyright Code") << tr("Usable Years"));

	// Button Text
//	ui.pbFILEOPEN->setText(tr("File Open"));
//	ui.pbINSERT->setText(tr("Append"));
//	ui.pbDELETE->setText(tr("Delete"));
//	ui.pbEND->setText(tr("End"));

	// Button Enable
	ui.pbFILEOPEN->setEnabled(true);
//	ui.pbINSERT->setEnabled(false);
	ui.pbINSERT->setEnabled(true);
//	ui.pbDELETE->setEnabled(false);
	ui.pbDELETE->setEnabled(true);
	ui.pbEND->setEnabled(true);

	// Label
//	ui.tCpyright->setText(tr("Copyright Code"));
//	ui.tUsableyears->setText(tr("Usable Years"));
//	ui.tCerealNo->setText(tr("Serial Number"));

	IsInitialized = 0;
	ApiPacket = &ApiPack;
}

SentinelWrite_3::~SentinelWrite_3()
{
}

bool SentinelWrite_3::SentinelLogin()
{
	if (0 < IsInitialized)
		return true;

    SP_STATUS status;

	status = RNBOsproFormatPacket(ApiPacket, sizeof(ApiPack));

	if (SP_SUCCESS != status)
	{
		QMessageBox::information(this, "Sentinel API Error", "FormatPacket failed\n");
		return false;
	}

	status = RNBOsproInitialize(ApiPacket);

	if (SP_SUCCESS != status)
	{
		QMessageBox::information(this, "Sentinel API Error", "Initialize failed\n");
		return false;
	}

	return true;
}

bool SentinelWrite_3::Session()
{
	SP_STATUS status;

    status = RNBOsproFindFirstUnit(ApiPacket, DeveloperID);

	if (SP_SUCCESS != status)
	{
		QMessageBox::information(this, "Sentinel API Error", "FindFirstUnit failed\n");
		return false;
	}

    status = RNBOsproFindNextUnit(ApiPacket);

	if (SP_SUCCESS == status)
	{
		QMessageBox::information(this, "Sentinel API Error", "Please insert only one\n");
		return false;
	}

    status = RNBOsproFindFirstUnit(ApiPacket, DeveloperID);

	if (SP_SUCCESS != status)
	{
		QMessageBox::information(this, "Sentinel API Error", "FindFirstUnit failed\n");
		return false;
	}

	return true;
}

bool SentinelWrite_3::GetSentinelID()
{
	RB_WORD rCell = 0;
	RB_WORD rData;
	RB_BYTE rAccessCode;
	SP_STATUS status;

	status = RNBOsproExtendedRead(ApiPacket, rCell, &rData, &rAccessCode);

	if (SP_SUCCESS != status)
	{
		QMessageBox::information(this, "Sentinel API Error", "ExtendedRead failed\n");
		return false;
	}

	SerialNumber = (int)rData;

	for (int ict = 8; ict < 64; ict++)
	{
		status = RNBOsproExtendedRead(ApiPacket, (RB_WORD)ict, &rData, &rAccessCode);

		if (SP_SUCCESS != status)
		{
			QMessageBox::information(this, "Sentinel API Error", "ExtendedRead failed\n");
			return false;
		}

		MemCell[ict - 8] = rData;
	}

	QString WidgetString;
	WidgetString.clear();

	for (int ict = 0; ict < 56; ict++)
	{
		if (0 == MemCell[ict])
			continue;

		unsigned char uctmp;
		int itmp;

		itmp = (MemCell[ict] ^ DeveloperID) & 0xffff; // 復号
		uctmp = (itmp >> 8) & 0xff;
		WidgetString.append(uctmp);
		uctmp = itmp & 0xff;
		WidgetString.append(uctmp);
	}

	while (0 < ui.tableWidget->rowCount())
		ui.tableWidget->removeRow(ui.tableWidget->rowCount() - 1);

	ui.tableWidget->setRowCount(0);
	ui.tableWidget->setColumnCount(0);

	ui.tableWidget->setColumnCount(2);
	int isize = WidgetString.size();
	int irow = 0;
	QTableWidgetItem* item;

	for (int ict = 0; ict < isize; ict += 16)
	{
		ui.tableWidget->setRowCount(irow + 1);
		item = new QTableWidgetItem(WidgetString.mid(ict, 8));
		ui.tableWidget->setItem(irow, 0, item);
		item = new QTableWidgetItem(WidgetString.mid(ict + 8, 8));
		ui.tableWidget->setItem(irow, 1, item);
		irow++;
	}

	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << tr("Copyright Code") << tr("Usable Years"));
	ui.tableWidget->setCurrentCell(-1, -1);
	return true;
}

bool SentinelWrite_3::FileOpen()
{
	FileName = QFileDialog::getOpenFileName(this, "Open", /**/"", /**/"");

	if (FileName.isEmpty())
		return false;
	else
		return true;
}

bool SentinelWrite_3::FileLoad()
{
    if (!QFile::exists(FileName))
        return false;

	QFile file(FileName);

	if (!file.open(QFile::ReadOnly))
        return false;

	SentinelDataArray.clear();
	SentinelDataArray = file.readAll();
	file.close();

#if 0 // debug write
	QMessageBox::information(this, /**/"", QString().append(SentinelDataArray));
#endif

	return true;
}

void SentinelWrite_3::Decrypt()
{
	Serial.clear();
	Copyright.clear();
	Usabl.clear();

	int isize = SentinelDataArray.size();

	if (20 != isize)
		return;

	int icont = isize / 2; // odd : n - 1
	SentinelDataArrayDecrypt.clear();
//	SentinelDataArrayDecrypt.append(QString("--------------------"));

	for (int i = 0; i < icont; i++)
	{
		unsigned char uctmp;
		int itmp;

		uctmp = SentinelDataArray[i * 2];
		itmp = ((int)uctmp << 8) & 0xff00;
		uctmp = SentinelDataArray[i * 2 + 1];
		itmp |= (int)uctmp & 0xff;

		itmp = (itmp ^ DeveloperID) & 0xffff; // 復号

		uctmp = (itmp >> 8) & 0xff;
		SentinelDataArrayDecrypt[i * 2] = uctmp;
		uctmp = itmp & 0xff;
		SentinelDataArrayDecrypt[i * 2 + 1] = uctmp;
	}

	Serial = SentinelDataArrayDecrypt.mid(0, 4);
	Copyright = SentinelDataArrayDecrypt.mid(4, 8);
	Usabl = SentinelDataArrayDecrypt.mid(12, 8);

#if 0 // debug write
	QMessageBox::information(this, /**/"", QString().append(SentinelDataArrayDecrypt));
#endif
}

bool SentinelWrite_3::WriteSentinel()
{
	for (int ict = 0; ict < 56; ict++)
		MemCellWrite[ict] = 0;

	int ipos = 0;

	for (int ict = 0; ict < ui.tableWidget->rowCount(); ict++)
	{
		QByteArray tmpArray;
		unsigned char uctmp;

		tmpArray.clear();
		tmpArray.append(ui.tableWidget->item(ict, 0)->text());

		for (int ict2 = 0; ict2 < 8; ict2 += 2)
		{
			uctmp = tmpArray[ict2];
			MemCellWrite[ipos] = ((RB_WORD)uctmp << 8) & 0xff00;
			uctmp = tmpArray[ict2 + 1];
			MemCellWrite[ipos] |= (RB_WORD)uctmp & 0xff;
			MemCellWrite[ipos] = (MemCellWrite[ipos] ^ DeveloperID) & 0xffff; // 暗号
			++ipos;
		}

		tmpArray.clear();
		tmpArray.append(ui.tableWidget->item(ict, 1)->text());

		for (int ict2 = 0; ict2 < 8; ict2 += 2)
		{
			uctmp = tmpArray[ict2];
			MemCellWrite[ipos] = ((RB_WORD)uctmp << 8) & 0xff00;
			uctmp = tmpArray[ict2 + 1];
			MemCellWrite[ipos] |= (RB_WORD)uctmp & 0xff;
			MemCellWrite[ipos] = (MemCellWrite[ipos] ^ DeveloperID) & 0xffff; // 暗号
			++ipos;
		}
	}

    SP_STATUS status;

	for (int ict = 8; ict < 64; ict++)
	{
		status = RNBOsproOverwrite(ApiPacket, WritePassWord, OverWritePassWord1, OverWritePassWord2, (RB_WORD)ict, MemCellWrite[ict - 8], (RB_BYTE)1);

		if (SP_SUCCESS != status)
		{
			QMessageBox::information(this, "Sentinel API Error", "Overwrite failed\n");
			return false;
		}
	}

	return true;
}

void SentinelWrite_3::on_pbFILEOPEN_clicked()
{
	ui.pbFILEOPEN->setEnabled(false);
	ui.pbINSERT->setEnabled(false);
	ui.pbDELETE->setEnabled(false);
	ui.pbEND->setEnabled(false);

	Sleep(100);

	if (true == SentinelLogin())
		if (true == Session())
			if (true == GetSentinelID())
			{
				QMessageBox::information(this, "Open File", tr("Please Open Sentinel Copyright File"));

				if (false == FileOpen())
				{
					QMessageBox::information(this, "File Open Error", "Select Not File");
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return;
				}

				if (false == FileLoad())
				{
					QMessageBox::information(this, "File Read Error", "Not File Read");
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return;
				}

				Decrypt();

				bool boo;

				if (SerialNumber != Serial.toInt(&boo, 16))
				{
#if 0 // debug write
					QMessageBox::information(this, QString().setNum(SerialNumber), QString().setNum(Serial.toInt()));
#endif

					QMessageBox::information(this, "Serial Code Error", tr("The Serial Code Is Not Suitable"));
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return;
				}

				boo = false;

				for (int ict = 0; ict < ui.tableWidget->rowCount(); ict++)
				{
					QString tmpString;

					tmpString.clear();
					tmpString.append(ui.tableWidget->item(ict, 0)->text());

					if (Copyright == tmpString)
					{
						boo = true;
						break;
					}
				}

				if (false == boo)
				{
					ui.lCopyright->setText(Copyright);
					ui.lUsableYears->setText(Usabl.mid(0, 4) + "/" + Usabl.mid(4, 2) + "/" + Usabl.mid(6, 2));
					ui.lSerialNo->setText(Serial);
				}
				else
				{
					ui.lCopyright->setText(/**/"");
					ui.lUsableYears->setText(/**/"");
					ui.lSerialNo->setText(/**/"");
					QMessageBox::information(this, "Copyright Code Error", tr("It Has Already Broken Out"));
				}
			}

	ui.pbFILEOPEN->setEnabled(true);
	ui.pbINSERT->setEnabled(true);
	ui.pbDELETE->setEnabled(true);
	ui.pbEND->setEnabled(true);
}

void SentinelWrite_3::on_pbINSERT_clicked()
{
	ui.pbFILEOPEN->setEnabled(false);
	ui.pbINSERT->setEnabled(false);
	ui.pbDELETE->setEnabled(false);
	ui.pbEND->setEnabled(false);

	Sleep(100);

	if (true == SentinelLogin())
		if (true == Session())
			if (true == GetSentinelID())
			{
				if (true == ui.lSerialNo->text().isEmpty())
				{
					QMessageBox::information(this, "Select Error", tr("Unkuown Sentinel Serial Data"));
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return;
				}

				bool boo;

				if (SerialNumber != ui.lSerialNo->text().toInt(&boo, 16))
				{
					QMessageBox::information(this, "Select Error", tr("Error Sentinel Serial Data"));
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return;
				}

				boo = false;

				for (int ict = 0; ict < ui.tableWidget->rowCount(); ict++)
					if (ui.tableWidget->item(ict, 0)->text() == ui.lCopyright->text())
					{
						boo = true;
						break;
					}

				if (true == boo)
				{
					QMessageBox::information(this, "Insert Error", tr("It Has Already Broken Out"));
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return;
				}

				if (6 < ui.tableWidget->rowCount())
				{
					QMessageBox::information(this, "Sentinel Information", tr("Sentinel Data Full"));
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return ;
				}

				QTableWidgetItem* item;

				ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);
				item = new QTableWidgetItem(Copyright);
				ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 0, item);
				item = new QTableWidgetItem(Usabl);
				ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 1, item);

				if (true == WriteSentinel())
					GetSentinelID();
			}

	ui.pbFILEOPEN->setEnabled(true);
	ui.pbINSERT->setEnabled(true);
	ui.pbDELETE->setEnabled(true);
	ui.pbEND->setEnabled(true);
}

void SentinelWrite_3::on_pbDELETE_clicked()
{
	int icr = ui.tableWidget->currentRow();

	ui.pbFILEOPEN->setEnabled(false);
	ui.pbINSERT->setEnabled(false);
	ui.pbDELETE->setEnabled(false);
	ui.pbEND->setEnabled(false);

	Sleep(100);

	if (true == SentinelLogin())
		if (true == Session())
			if (true == GetSentinelID())
			{
#if 0
				// Copyright が同じファイルが削除には必要(コピーライトがテーブルに在ると読めないのでファイルオープン時の修正が必要)
				if (true == ui.lSerialNo->text().isEmpty())
				{
					QMessageBox::information(this, "Select Error", tr("Unkuown Sentinel Serial Data\n"));
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return;
				}

				bool boo;

				if (SerialNumber != ui.lSerialNo->text().toInt(&boo, 16))
				{
					QMessageBox::information(this, "Select Error", tr("Error Sentinel Serial Data\n"));
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return;
				}

				boo = false;

				for (int ict = 0; ict < ui.tableWidget->rowCount(); ict++)
					if (ui.tableWidget->item(ict, 0)->text() == ui.lCopyright->text())
					{
						boo = true;
						break;
					}

				if (false == boo)
				{
					QMessageBox::information(this, "Delete Error", tr("Unmatch Copyright Code"));
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return;
				}
#endif

				// TableWidgetのデータを選択しているかの確認
				if (-1 == icr)
				{
					QMessageBox::information(this, "Select Error", tr("Delete Data Not Select\n"));
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
					return;
				}

#if 0 // debug write
				QMessageBox::information(this, "Select Row", QString::number(icr));
#endif

				//TableWidgetのデータの削除
				ui.tableWidget->removeRow(icr);

				if (true == WriteSentinel())
					GetSentinelID();
			}

	ui.pbFILEOPEN->setEnabled(true);
	ui.pbINSERT->setEnabled(true);
	ui.pbDELETE->setEnabled(true);
	ui.pbEND->setEnabled(true);
}

void SentinelWrite_3::on_pbEND_clicked()
{
	close();
}
