/*
 * clsXMLDB_Front.h
 *
 *  Created on: 2009/12/19
 *      Author: cony
 */

#ifndef CLSXMLDB_FRONT_H_
#define CLSXMLDB_FRONT_H_

#include <QObject>
#include <QString>
#include <QStringList>

#include "clsXmlUpd.h"
#include "clsDb.h"

/**
 * @brief XML操作コマンド実行フロントエンドクラス
 */
class clsXMLDB_Front : public QObject {
	Q_OBJECT
public:
	clsXMLDB_Front(clsDb *db, int port, QObject *par=0);
	virtual ~clsXMLDB_Front();

	/**
	 * @brief XML検索
	 *
	 * 指定SQLでXMLを検索し、ヒットした全件を返す
	 * @param const QByteArray &sql
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool searchAllXml(const QByteArray &sql, QByteArray &retByte);

	/**
	 * @brief XML検索
	 *
	 * 指定SQLでXMLを検索し、ヒットした行から１行を返す
	 * @param const QByteArray &sql
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool searchFirstXml(const QByteArray &sql, QByteArray &retByte);

	/**
	 * @brief 次XML検索
	 *
	 * searchFirstXml()で検索された行から次の行を返す
	 * @param const QByteArray &sql
	 * @param const QByteArray &id 次の行のtopid
	 * @param const QByteArray &dbFile 次の行が格納されているDBファイル名
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool readXml(const QByteArray &sql, const QByteArray id, const QByteArray &dbFile, QByteArray &retByte);

	/**
	 * @brief XML検索
	 *
	 * 指定SQLでXMLを検索し、ヒットした全件を返す
	 * テーブル名が_allのときコールされる
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool searchAllXmlA(QByteArray &retByte);

	/**
	 * @brief XML検索
	 *
	 * 指定SQLでXMLを検索し、ヒットした行から１行を返す
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool searchFirstXmlA(QByteArray &retByte);

	/**
	 * @brief 次XML検索
	 *
	 * searchFirstXmlA()で検索された行から次の行を返す
	 * @param const QByteArray &id 次の行のtopid
	 * @param const QByteArray &dbFile 次の行が格納されているDBファイル名
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool readXmlA(const QByteArray &id, const QByteArray &dbFile, QByteArray &retByte);

	/**
	 * @brief XML文追加
	 *
	 * 指定SQLからXML文を追加する
	 * @param const QByteArray &sql
	 * @return bool
	 */
	bool addXml(const QByteArray &sql);

	/**
	 * @brief XML文へタグ追加
	 *
	 * 指定SQLから特定されるXML文にタグを追加する
	 * @param const QByteArray &sql
	 * @return bool
	 */
	bool appendXml(const QByteArray &sql);

	/**
	 * @brief XML文上書き
	 *
	 * 指定SQLから特定されるXML文を上書きする
	 * @param const QByteArray &sql
	 * @return bool
	 */
	bool updateXml(const QByteArray &sql);

	/**
	 * @brief XML文作成
	 *
	 * 指定SQLから特定されるXML文を削除する
	 * @param const QByteArray &sql
	 * @return bool
	 */
	bool deleteXml(const QByteArray &sql);

	QString errorString() {
		return errMess;
	}

	void setLogObj(clsLog *log) {
		if ( db != NULL ) {
			db->log = log;
		}
		if ( objXml != NULL ) {
			objXml->log = log;
		}
	}

	QString connNam;

	int nParPort;
	clsDb *db;

	void drawMstId(const QByteArray &MstId);
private:
	clsXmlUpd *objXml;
	QObject *par;

	void makeObj();
	void cleanObj();

	QString errMess;

	bool makeReturnByteArray(QString cmd, QString buf, QByteArray &retByte);
	QString fixStrBnd(QString buf, int len);
	void fixStrBnd(QByteArray &buf, int len);
};
#endif /* CLSXMLDB_FRONT_H_ */
