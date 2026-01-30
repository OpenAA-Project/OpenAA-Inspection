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




#ifndef XMLSERVER_H
#define XMLSERVER_H

#include "servermain.h"
#include "ui_xmlserver.h"
#include "ui_settingform.h"
#include <QTcpServer>
#include <QHeaderView>
#include <QTextStream>

class XmlServer : public QWidget
{
    Q_OBJECT
	//ServerMain Maine;
public:
    XmlServer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~XmlServer();
    Ui::XmlServerClass ui;
	quint16 Port;
	int Timer;
	QTcpSocket *clientConnection;
signals:
	void SignalClose();
private:
	QTcpServer *tcpServer;		//�z�X�g��
	QString PPORT;				//�|�[�g��
	ServerBase *Base;			//SockBClass�p��
	QAbstractSocket *socket;	//connect�Ɏg�p
private slots:
	void Exit();
	void on_ENDB_clicked();
	void on_CutB_clicked();
	void on_CreateB_clicked();
	void on_SaveB_clicked();
	void on_Button_clicked();
	void sendFortune();
	void PortFileOpen(quint16 &PORT,int &TIMER);
};
#endif // XMLSERVER_H

