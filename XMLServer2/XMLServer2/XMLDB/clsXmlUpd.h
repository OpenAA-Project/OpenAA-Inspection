/*
 * clsXmlUpd.h
 *
 *  Created on: 2009/11/20
 *      Author: cony
 */

#ifndef CLSXMLUPD_H_
#define CLSXMLUPD_H_

#include <QObject>
#include <QIODevice>
#include <QDomElement>
#include <QDomDocument>
#include <QStringList>

#include "clsDb.h"
#include "clsLog.h"
#include "clsDbCtrl.h"
#include "clsXmlWhereLex.h"
#include "clsXmlReadSql.h"

/**
 * @brief XML操作クラス
 */
class clsXmlUpd {
public:
	clsXmlUpd();
	virtual ~clsXmlUpd();

	clsXmlReadSql *readSql;

	/**
	 * @brief 検索系SQL解析
	 */
	bool lexSelSql(const QByteArray &sql);

	/**
	 * @brief 更新系SQL解析
	 */
	bool lexUpdSql(const QByteArray &sql);

	/**
	 * @brief XML文パース
	 */
	bool parse(const QByteArray &buf);

	/**
	 * @brief XML追加
	 */
	bool addXml();

	/**
	 * @brief タグ追加
	 */
	bool appendXml();

	/**
	 * @brief XML削除
	 */
	bool deleteXml();

	bool updateXml();

	/**
	 * @brief XML文検索
	 *
	 * @param int idx 1の場合、最初の１件リターン
	 */
	bool searchXml(int idx=-1);
	QList<QByteArray> lstResult;
	QList<QByteArray> lstResultId;
	int nResCnt;

	/**
	 * @brief 次XML文検索
	 *
	 * searchXml(1)でリードした次の行（XML）を取得する
	 */
	bool nextXml(const QString &id);

	QList<QByteArray> lstDbFile;

	/**
	 * @brief XML文検索
	 *
	 * 全DBファイルを対象にXML文を検索する
	 */
	bool allSearchXml(int idx=-1);

	/**
	 * @brief 次XML文検索
	 *
	 * allSearchXml(1)でリードした次の行（XML）を取得する
	 */
	bool allNextXml(const QString &id, const QByteArray &dbFile);

	/**
	 * @brief XML文リード
	 *
	 * 指定したtopidからXML文をリードする
	 */
	bool readXml(QString topid);

	/**
	 * @brief XML文変換
	 *
	 * XML文をテキストに変換する
	 */
	QByteArray toString();

	QString errMess;
	clsDb *db;

	QString mkWhere(QString whrbuf);
	QString mkSelSql(QString whrbuf);

	void clearObj();

	bool getDbKey(QByteArray &mac, QByteArray &day);

	clsLog *log;
	int nParPort;
private:
	clsDbCtrl *dbCtrl;

	QDomDocument *doc;

	QString topid;
	QString chldid;
	bool addAttr(QDomNamedNodeMap lst, int lvl);
	bool addChildNode(int srt,QDomNode node);
	bool addFixAttr(int idx, QDomNamedNodeMap lst, int lvl);

	bool updChildNode(const QString &topid, const QDomNode &node);
	bool updAttr(const QString &topid, QDomNamedNodeMap lst, int lvl);
	bool updFixAttr(const QString &topid, int idx, QDomNamedNodeMap lst, int lvl);

	void clearDoc();
	void clearSql();

	bool getChildTagAttr(QString topid, QString tag, QDomElement &child);

	QByteArray bindTblMstId(const QByteArray &tbl);
	QByteArray bndInitDay();
};

#endif /* CLSXMLUPD_H_ */
