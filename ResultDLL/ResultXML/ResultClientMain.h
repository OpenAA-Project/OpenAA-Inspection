/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\clientmain.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef RESULTCLIENTMAIN_H
#define RESULTCLIENTMAIN_H

#include <QTcpSocket>
#include <QMessageBox>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "XGeneralSocket.h"


class ClientMain : public QObject
{
	Q_OBJECT

	GeneralSocketClient	*ClientInst;

public:
    ClientMain(QObject *parent ,const QString &sHost, const QString &sPort);
    ~ClientMain(void);

	bool ConnectFlag;
	static	QByteArray sClientNo ;		//サーバーから割り振られたクライアント番号
	//QTcpSocket *socket;//Socket

	//サーバ接続
	bool Client_Connect(QByteArray &sMsg);	
	//サーバ接続&クライアント番号取得
	bool Client_Start(const QByteArray &FileName, QByteArray &sMsg, int &Client);
	//リストア
	bool Client_Restore(const QByteArray &Data, const QByteArray &DATABASE, QByteArray &sMsg);
	//検査データ数
	bool Client_Count(const QList<QByteArray> &TagList, const QByteArray &sDBName,  int &Count);
	//XMLファイル作成
	bool Client_Create( const QByteArray &sDBName, QByteArray &sMsg );
	//データ挿入
	bool Client_Insert( const QList<QByteArray> &sInsertXml, const QByteArray &sDBName, QByteArray &sMsg );
	//データ削除
	bool Client_Delete(const QList<QByteArray> &DelKey, const QByteArray &sDBName, QByteArray &sMsg);
	//一件検索条件での削除
	bool Client_TagSelectDele		(const QByteArray &sSelData, const QByteArray &DATABASE, const QByteArray &Parent, QByteArray &sMsg);
	bool Client_TagDel				( const QByteArray &sQueryNo, const QByteArray &sDeleteTag, const QByteArray &sUpdateTag, const QByteArray &sDBName, QByteArray &sMsg);
	//複数検索条件での削除
	bool Client_TagtoTagDel			(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName,  QByteArray &sMsg);
	//データ更新
	bool Client_Update				(const QByteArray &sQueryNo, const QByteArray &sUpXml, const QByteArray &sDBName, QByteArray &sMsg, const QByteArray &ClientNo);
	//複数検索条件でNG数を返す
	bool Client_TagToTagnotNG		(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);	
	bool Client_TagToTagnotNGDesc	(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);	
	//一件検索条件でNG数を返す
	bool Client_TagnotNG			(const QByteArray &sQueryXml, const QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList);
	bool Client_TagnotNGDesc		(const QByteArray &sQueryXml, const QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList);
	
	bool Client_SelectGet(QList<QByteArray> &selList);
	bool Client_TagtoTagCunt		(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName, QByteArray &sMsg, QByteArray &Cunt);
	
	bool Client_UpApp				(const QByteArray &sTagsel, const QByteArray &sUpXml, const QByteArray &sDBName, QByteArray &sMsg );
	bool Client_UP(QString Tagsel, QByteArray sQueryNo, QByteArray sUpXml, QByteArray sDBName, QByteArray  &sMsg );

	bool Client_Select				( const QByteArray &sQueryXml, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);//検索
	bool Client_SelectDesc			( const QByteArray &sQueryXml, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);//検索
	bool Client_SelectNotNG			( const QByteArray &sQueryXml, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);
	bool Client_SelectNotNGDesc		( const QByteArray &sQueryXml, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);
	bool Client_TagSelect			( const QByteArray &sQueryXml, const QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList);
	bool Client_TagSelectDesc		( const QByteArray &sQueryXml, const QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &selList);
	bool Client_TagToTagSelectDesc	(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);//TagSelect
	bool Client_TagToTagSelect		(const QList<QByteArray> &sQueryXmlList, const QByteArray &sDBName, QByteArray &sMsg, QList<QByteArray> &selList);//TagSelect
	//Masterで送ってLotを返す
	bool Client_MasterToLot			(const QByteArray &Master, const QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &List);
	bool Client_MasterToLotDesc		(const QByteArray &Master,const  QByteArray &sDBName, const QByteArray &Parent, QByteArray &sMsg, QList<QByteArray> &List);	
	bool Client_Close(QByteArray &sMsg);//サーバ切断
	bool Client_LotGetClose(QByteArray &Msg);

#if 1 // 20091112
	bool Client_RestoreStart(const QByteArray &FileName, QByteArray &sMsg, int &Client, QByteArray &LID, QByteArray &LNM);
#endif
	bool Client_MasterStart(const QByteArray &FileName, QByteArray &sMsg, int &Client);
	bool Client_MasterInsert(const QByteArray &DBName, const QByteArray &XmlMaster, QByteArray &sMsg);
	bool Client_MasterUpApp(const QByteArray &DBName, const QByteArray &Tagsel, const QByteArray &UpXml, QByteArray &sMsg);

	bool Client_LotGet(const QByteArray &Path, const QByteArray &Master, QByteArray &Msg, QList<QByteArray> &RetList);

	bool Client_InspectStart(const QByteArray &FileName, const QByteArray &LotID, QByteArray &LotName, QByteArray &sMsg, int &Client);
	QByteArray Str;//SelectGetで使用
	bool Client_FileDelete	(const QByteArray &File, QByteArray &Msg);
	bool Client_FileGet		(const QByteArray &File, QList<QByteArray> &RetFile, QList<QByteArray> &RetList, QByteArray &Msg);
	bool Client_FileLoad	(const QByteArray &File, QByteArray &Data, QByteArray &Msg);
	bool Client_DBXML		(const QList<QByteArray> &List, QList<QByteArray> &RetList, QByteArray &Msg);
	bool Client_LastLotData	(const QByteArray &DBName, qint64 &InspectionID);

//signals:
	//void SignalDisconnect();
private:
	bool Client_Get(QByteArray &sError);//データ取得
	void Client_Send();		//データ送信
	QByteArray block;		//送信データサイズ
	quint16 blockSize;		//取得データサイズ
    QString Host;			//ホスト名
	QString Port;			//ポート名
	QByteArray sDBName;		//XMLDBファイル名
	QList<QByteArray> sInlist;	//取得データ
	QList<QByteArray> sOutlist;	//送信データ

};
const int iTimeout=5 * 100000 ; //サーバからの接続待ち時間

#endif
