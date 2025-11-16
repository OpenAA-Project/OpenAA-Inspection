/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XmlServer\XmlServer\serverbase.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SERVERBASE_H
#define SERVERBASE_H

#include "xmlapi.h"
#include <QStringList>
#include "MTXMLLib.h"
#include <QThread>

class ServerBase;
class XmlAPI;
class MemReadThread : public QThread
{
	Q_OBJECT

public:
	MemReadThread();
	~MemReadThread();
	
	XMLMainStock *RStock;
	QString RDB;
	int RDBNo;
signals:
	void MemRead();

protected:
	void run();

private:

};
class MemDeleteThread : public QThread
{
	Q_OBJECT

public:
	MemDeleteThread();
	~MemDeleteThread();

	//QString DData;
	QString DDB;
	int DDBNo;
	XMLMainStock *DStock;
	ServerBase *DBase;		//<ServerMain>Class:ServerBaseの継承
signals:
	void MemDelete();
protected:
	void run();
private:
};

class ServerBase : public QObject
{
	Q_OBJECT

public:
	ServerBase();

	int iSeverNo;	        //<Server_Start>
	QList <int> buffSize;//<Server_UpApp>
	
	XmlAPI *xmlClient[1000];//多数使用
	XmlAPI *xml;
	unsigned long Server_GetSize(QList<QByteArray> &List) ;
	bool Server_LastLotData(QList<QByteArray> InList, QByteArray &RetEID);
	void Server_LastLotGet(QByteArray &Info, QString &RetEID);
	bool Server_DBXML(QList<QByteArray> &InList, QList<QByteArray> &RetList);
	bool Server_FileGet(QList<QByteArray> &List, QList<QByteArray> &RetFile, QList<QByteArray> &RetData);
	bool Server_FileLoad(QList<QByteArray> &List);
	//基本処理
	//スタート<DBを渡して、クライアント番号とDB番号を渡す>
	//bool Server_Start(QByteArray &DataBase, int &Client, int &DB);
	int Server_MasterStart(QList<QByteArray> &List, int &iClient, int &iDB);
	//新規作成
	bool Server_Create(QList<QByteArray> &List);
	//挿入
	bool Server_Insert(QList<QByteArray> &List);
	//LotIDと名称を返す
	bool Server_LotGet(QList<QByteArray> &List, QList<QByteArray> &RetLotList);

	//QByteArrayでIntとQStringを返す
	void Server_Str(QByteArray &Str, QString &RetStr);
	//XMLの番号を返す
	int Server_XnmNum(const char *DB);
	//ファイル名文字列のみ取得
	void Server_FileName(const char *FileName, char *RetFile);
	
	void Server_GetData(QByteArray &Info, QString &RetDAY, QString &RetMAC);
	//リストア
	bool Server_Restore(QList<QByteArray> &List);
    //NGJの情報取得
	//void XMLGetData(QString &Info, QString &NGJ);
	//検査データ数
	bool Server_Count(QList<QByteArray> &List, int &Count);
	
	//検索
	bool Server_Select(QList<QByteArray> &List, unsigned long &Count, XMLElement **RetAns);	
	void Server_Resvalue(char *Target, char *buffer, qint64 &ElementID, char *Retbuff);//(char *Target, XMLElement *RetAns, char *Retbuff);
	//NGを個数で返す処理
	void  Server_NGsyori(qint64 &ID, char *buff, char *buffer);
	//全てのデータを返す
	void  Server_Normalsyori(qint64 &ID, char *buff, char *buffer);
	//IDで削除
	bool Server_Delete(QList<QByteArray> &List);	
	
	//検査データ用特別処理
	bool Server_UpApp(QList<QByteArray> &List);
	//XmlLotを取得
	void Server_XmlLotGetData(QByteArray &Info, QString &RetLotID, QString &RetLotName);
	//Xml Time&Master&Lotを取得
	//void Server_XmlTimMasLotGetData(QString &Info, QString &RetTIM, QString &RetMID, QString &RetLID);


	//ファイルの作成
	bool Server_CreateFile(QString &DBName);
	//追加
	bool Server_Append(QList<QByteArray> &List);
	//保存
	bool Server_Save(QString &DBNum, QString &DBName); 

	//終了
	void Server_Close(int &cNum);	
	bool Server_End(QString &Target, int &DBNum, QString &DBName);
	//Noのエラー
	bool Server_NumError(int &iClientNum);
    //リペアで使用
	bool Server_TagDel(QList<QByteArray> &List);
	bool Server_FileDelete(QList<QByteArray> &List);
	//TagLsitの削除
	void DeleteTagList();

	bool Deletesyori(int &cNum, int &Num, qint64 &ID, QList<QByteArray> &RetNGJ);
	MemReadThread   *MemRead[1000];
	MemDeleteThread *MemDelete[1000];
	void Sever_EndCheck();
private:
	//QList<int> ThredList;
	//他クラスの定義
	
	XMLElement		*Element;
	XMLElement		*Answer;
	XMLElement		*wxAnswer;
	int iXMLmain;       	//<Server_Create>	
	char *UpAppSize[1000];//<Server_UpApp>
	char *UpAppXML[1000];//<Server_UpApp>						
	char *RestoreXML;		//<Server_Restore>
	QString LotID;//<Selectsyori>
	QString LotName;//<Selectsyori>
	QList<XMLTag*>	MatchTagList;//多数使用
};

#endif // SOCKB_H
