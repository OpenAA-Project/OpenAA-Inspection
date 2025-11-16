/*
 * XMLServerHandle.h
 *
 *  Created on: 2009/12/14
 *      Author: cony
 */

#ifndef XMLSERVERHANDLE_H_
#define XMLSERVERHANDLE_H_

#include <QtNetwork>
#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QObject>

#include "XMLServerHandlePrivate.h"

class XMLServerHandle : public XMLServerHandlePrivate {
	Q_OBJECT
public:
	XMLServerHandle(QObject *par=0);
	virtual ~XMLServerHandle();

	bool Connect();
	bool DisConnect();
	bool GetStatus();

	bool selectXml(const QString &sql, QStringList &lst);
	bool openXml(const QString &sql, QString &buf);
	bool nextXml(QString &buf);

	bool addXml(const QString &sql);
	bool appendXml(const QString &sql);
	bool updateXml(const QString &sql);
	bool deleteXml(const QString &sql);

	int getCurrentPort() {
		return svrPort;
	}

	QString getErrorMess() {
		return errMess;
	}

private:
	QString rcvBufLex(QString cmd);
	bool SndRcv(QString cmd, QString mess);
	QString rcvBuf;

	QString svsql;
	QStringList lstHit;
	QStringList lstDbFile;
	int nHitCnt;
	int nCurIdx;

	bool mkLstDb(const QString &src);
};

/**
 * @brief XMLサーバ接続
 *
 * XMLサーバへの接続を生成する。
 * @param const QString &IPAddress サーバアドレス
 * @param int port サーバポート番号
 * @param unsigned long WaitingTime タイムアウト値
 * @return XMLServerHandle * サーバ接続子
 */
XMLServerHandle *XML_Connect(const QString &IPAddress,int port, unsigned long WaitingTime);

/**
 * @brief XMLリード
 *
 * 指定SQL文からXMLを検索し、ヒットしたXML文をすべてQStringListに格納する。
 * @param XMLServerHandle *Handle サーバ接続子
 * @param const QString &SelectStr 検索SQL文
 * @param QStringList &RetStringList 検索結果リスト
 * @return bool true:成功時（該当なしの場合でもtrue）、false：エラー時
 */
bool XML_Select(XMLServerHandle *Handle,const QString &SelectStr,QStringList &RetStringList);

/**
 * @brief XMLリード(First)
 *
 * 指定SQL文からXMLを検索し、ヒットしたXML文のうち最初のものをQStringに格納する。<br>
 * 該当なしの場合はRetStringに空文字がセットされる。
 * @param XMLServerHandle *Handle サーバ接続子
 * @param const QString &SelectStr 検索SQL文
 * @param QString &RetString 検索結果
 * @return bool true:成功時（該当なしの場合でもtrue）、false：エラー時
 */
bool XML_SelectFirst(XMLServerHandle *Handle,const QString &SelectStr,QString &RetString);

/**
 * @brief XMLリード(Next)
 *
 * XML_SelectFirstから次のXMLを検索し、該当があればRetStringに格納する。<br>
 * 該当なしの場合はRetStringに空文字がセットされる。
 * @param XMLServerHandle *Handle サーバ接続子
 * @param QString &RetString 検索結果
 * @return bool true:成功時（該当なしの場合でもtrue）、false：エラー時
 */
bool XML_SelectNext(XMLServerHandle *Handle, QString &RetString);

/**
 * @brief XML追加
 *
 * 指定SQL文からXML文を新規作成する。
 * @param XMLServerHandle *Handle サーバ接続子
 * @param const QString &InsertedString 検索SQL文
 * @return bool true:成功時、false：エラー時
 */
bool XML_Insert(XMLServerHandle *Handle,const QString &InsertedString);

/**
 * @brief XML追加（Append)
 *
 * 指定SQL文から該当するXML文に対してXMLタグを追加する。
 * @param XMLServerHandle *Handle サーバ接続子
 * @param const QString &InsertedString 検索SQL文
 * @return bool true:成功時、false：エラー時
 */
bool XML_Append(XMLServerHandle *Handle,const QString &InsertedString);

/**
 * @brief XML更新
 *
 * 指定SQL文からXMLを検索し、該当すれば最初に見つかったXML文全体を更新する。
 * @param XMLServerHandle *Handle サーバ接続子
 * @param const QString &UpdatedString 検索SQL文
 * @return bool true:成功時（該当なしの場合でもtrue）、false：エラー時
 */
bool XML_Update(XMLServerHandle *Handle,const QString &UpdatedString);

/**
 * @brief XML削除
 *
 * 指定SQL文からXMLを検索し、該当するXML文を削除する。
 * @param XMLServerHandle *Handle サーバ接続子
 * @param const QString &DeletedString 検索SQL文
 * @return bool true:成功時（該当なしの場合でもtrue）、false：エラー時
 */
bool XML_Delete(XMLServerHandle *Handle,const QString &DeletedString);

/**
 * @brief XMLサーバ切断
 *
 * XMLサーバへの接続を切断する。
 * @param XMLServerHandle *Handle サーバ接続子
 * @return bool true:成功時（該当なしの場合でもtrue）、false：エラー時
 */
bool XML_Close(XMLServerHandle *Handle);

/**
 * @brief XMLサーバ状態取得
 *
 * XMLサーバへの接続の状態を取得する。
 * @param XMLServerHandle *Handle サーバ接続子
 * @param bool &RetOpened true:接続中、false:未接続
 * @return bool true:成功時、false：エラー時
 */
bool XML_GetState(XMLServerHandle *Handle,bool &RetOpened);
#endif /* XMLSERVERHANDLE_H_ */
