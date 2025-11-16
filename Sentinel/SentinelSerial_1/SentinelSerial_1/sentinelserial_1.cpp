/*******************************************************************************
** Copyright (C) 2005-2009 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Sentinel\SentinelSerial_1\SentinelSerial_1\sentinelserial_1.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <windows.h>
#include "spromeps.h"
#include "sentinelserial_1.h"
#include "sentinel_PnDid.h"

SentinelSerial_1::SentinelSerial_1(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
	QTranslator translator;
	translator.load(":/sentinelserial_1_ja");
	qApp->installTranslator(&translator);
	ui.setupUi(this);

	// Widget Size
//	setFixedSize(198, 130);
//	setWindowTitle (tr("Sentinel Serial File Out"));
//	ui.label->setText(tr("Is the preparation for Sentinel good?"));
//	ui.pbYES->setText(tr("YES"));
//	ui.pbNO->setText(tr("NO"));

	IsInitialized = 0;
	ApiPacket = &ApiPack;
}

SentinelSerial_1::~SentinelSerial_1()
{
}

bool SentinelSerial_1::SentinelLogin()
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

bool SentinelSerial_1::Session()
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

bool SentinelSerial_1::GetSentinelID()
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
	return true;
}

void SentinelSerial_1::Encrypt()
{
	int itmp;

	itmp = (SerialNumber ^ DeveloperID) & 0xffff; // ˆÃ†

	SerialNumberArray.clear();
	SerialNumberArray = QByteArray::number(itmp, 16);
	SerialNumberArray = SerialNumberArray.rightJustified(4, '0');
}

bool SentinelSerial_1::SaveFile()
{
	FileName = QFileDialog::getSaveFileName(this, "Save", "/SentinelSerialNumber", /**/"");

	if (FileName.isEmpty())
        return false;
    else
        return true;
}

bool SentinelSerial_1::SaveData()
{
    QFile file(FileName);

	if (!file.open(QFile::WriteOnly))
	{
        QMessageBox::warning(this, tr("MDI"), tr("Cannot Write File %1:\n%2.").arg(FileName).arg(file.errorString()));
        return false;
    }

	file.write(SerialNumberArray);
	file.close();
    return true;
}

void SentinelSerial_1::on_pbYES_clicked()
{
	if (true == SentinelLogin())
		if (true == Session())
			if (true == GetSentinelID())
			{
				Encrypt();

				if (true == SaveFile())
					if (true == SaveData())
					{
						RNBOsproReleaseLicense(ApiPacket, 0, 0);
						close();
					}
			}
}

void SentinelSerial_1::on_pbNO_clicked()
{
	close();
}
