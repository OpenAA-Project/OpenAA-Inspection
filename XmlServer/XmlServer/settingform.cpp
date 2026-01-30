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
	QFile datFile(File);//�ۑ����E�t�@�C�����̕ۑ�	
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