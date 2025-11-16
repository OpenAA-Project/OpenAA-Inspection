/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XmlServer\XmlServer\servermain.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SARVERMAIN_H
#define SARVERMAIN_H

#include "serverbase.h"
#include <QTcpSocket>
#include <QMessageBox>
#include  <QTimer>
#include "xmlserver.h"
#include "ui_xmlserver.h"

class ServerMain : public QObject
{
	Q_OBJECT

public:
	ServerMain 	( QTcpSocket *clientConnection,ServerBase *SBases,Ui::XmlServerClass &ui);
	~ServerMain();

	QTimer *timer;			//<ServerMain>
	int iTime;				//<ServerMain>	
	int iWatchClient[1000];	//<StartClient><ClientWatch>
#if 0 // 20090803
	double MaxSize;			//<ServerMain>	
#else
	unsigned int MaxSize;			//<ServerMain>	
#endif
	int myTimerID;			//<StartClient>
	void Server_Cont(QByteArray &CNum);
	//void Server_Disconnect();
	void CutB_clicked(QByteArray &CNum);
	void Filesyori(QByteArray &Data);
private:
	Ui::XmlServerClass uii;
	
	ServerBase *Base;		//<ServerMain>Class:ServerBaseの継承
	QTcpSocket *socket;		//<ServerMain>ソケット通信

	QList<QByteArray> InList;//<Server_Get>取得データ
	quint16 blockSize;		//<Server_Get>取得データサイズ
	QList<QByteArray> OutList;//<Server_Send>送信データ
	//QList<int> RetNo;
	//bool TheadRet(int &No, int &Number);

private slots:

	//設定時間経過してもアクセスがなければ切断
	void TimerWatch();
	//データ取得
	void Server_Get();
	//データ送信
	void Server_Send();

	//Server画面表示(上)
	void SaveWidgetShow(QString &DB, int &DBNum);
	void SaveWidgetDelete(int &DBNum);
	//Server画面表示(下)
	void WidgetShow(QString &DB, int &Cilent, int &DBNum);
	//アクセス時間の更新
	void StartClient(int &Client);
	//アクセスクライアントの監視
	void ClientWatch(int &Client);
	
	//下画面の更新
	bool WidgetDelete(int &Cilent);	
	//通信サイズに分けて送る
	void SelectFirst(char *Buffer, char *Retbuff);
	//Selet時繰り返し処理
	void Selectsyori(char *Target,char *Buffer, qint64 &ElementID );//(XMLElement *RetAns, char *Target);
	void TimerClose(QByteArray &CNum);
};
	const int Timeout = 5 * 100000; //接続待ち時間
#endif // SOCKA_H
