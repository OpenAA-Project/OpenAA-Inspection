/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XmlServer\XmlServer\xmlserver.h
** Author : YYYYYYYYYY
****************************************************************************-**/



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
	QTcpServer *tcpServer;		//ホスト名
	QString PPORT;				//ポート名
	ServerBase *Base;			//SockBClass継承
	QAbstractSocket *socket;	//connectに使用
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


