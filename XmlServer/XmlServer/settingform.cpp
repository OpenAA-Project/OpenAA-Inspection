/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XmlServer\XmlServer\settingform.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "settingform.h"
#include <QMessageBox>
extern	QString	CurrPath;

SettingForm::SettingForm(QWidget *parent)//QDialog
	//: QWidget(parent)
	:QDialog(parent)
{
	ui.setupUi(this);
}

//SettingForm::~SettingForm()
//{
//}
void SettingForm::on_pushButton_2_clicked()
{
	close();
}

void SettingForm::on_pushButton_clicked()
{
	QString sPort=ui.LEPort->text();
	QString sTime=ui.LETime->text();
	
	if (sPort.isEmpty()==true){
		QMessageBox::critical(0, QObject::tr("PortNumber is Null"),
		QObject::tr("Plese input PortNumber ") , QMessageBox::Ok,QMessageBox::NoButton);	
		return;
	}
	if (sTime.isEmpty()==true){
		QMessageBox::critical(0, QObject::tr("Timer is Null"),
		QObject::tr("Plese input Timer ") , QMessageBox::Ok,QMessageBox::NoButton);	
		return;
	}

	QString File=CurrPath+QString("\\XmlServer.dat");
	QFile datFile(File);//保存先・ファイル名の保存	
	if(datFile.open(QIODevice::WriteOnly )==true){
		QTextStream mystream(&datFile);
		mystream<<sPort<<Qt::endl;
		mystream<<sTime<<Qt::endl;
		datFile.close();
		QMessageBox::warning(0, QObject::tr("Be start up"),
		QObject::tr("It was changed. It is start-up. ") , QMessageBox::Ok,QMessageBox::NoButton);	
		close();
	}
}