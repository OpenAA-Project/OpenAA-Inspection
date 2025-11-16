#ifndef CLSDB_H
#define CLSDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QStringList>

#include "clsLog.h"

class clsTagAttrRec {
public:
	clsTagAttrRec(QString _tag){
		tag = _tag;
		arrItm.clear();
		arrTblCol.clear();
	}

	QString tag;
	QStringList arrItm;
	QStringList arrTblCol;
};

class clsDb : public QObject
{
	Q_OBJECT

public:
	clsDb(QObject *parent=0);
	~clsDb();

	/// データベース名
	QString dbnam;

	/// データベースタイプ
	QString dbtype;

	/// DBユーザ
	QString dbusr;

	/// DBパスワード
	QString dbpwd;

	/// DBホスト
	QString dbhost;

	clsLog *log;

	/// 接続パラメータセット
	/**
	 * 接続パラメータを設定する。
	 * @param QString _dbtyp   データベースタイプ
	 * @param QString _dbhost  データベースサーバホスト名
	 * @param QString _dbnam   データベース名
	 * @param QString _dbusr   データベースユーザ名
	 * @param QString _dbpwd   データベースパスワード
	 */
	void setPrm(QString _dbtyp, QString _dbhost, QString _dbnam, QString _dbusr, QString _dbpwd);
	void setPrm();

	bool initDb();

	/// 接続
	/**
	 * @return bool
	 */
	bool Connect();

	/// 切断
	/**
	 * @return bool
	 */
	bool DisConnect();

	/// 更新
	/**
	 * @param QString sql
	 * @return void
	 */
	bool updExecSql(QString sql);

	/// MAXID取得
	/**
	 * @param QString
	 * @return QString
	 */
	QString maxId(QString tbl);

	/// クエリーモデル生成
	/**
	 * @param QString sql
	 * @return QSqlQueryModel
	 */
	QSqlQueryModel *mkQueryModel(QString sql);

	QSqlRecord rec;
	int readRec(QString sql);

	QString mess;

    QString curDay(bool flgTime=false);
    int getInsId(QString tbl);

    /**
     * トランザクション開始
     * @return bool
     */
    bool beginTran();

    /**
     * トランザクション終了
     * @return bool
     */
    bool endTran(bool flg);

    bool errflg;

    bool addTopNode(int no, QString tag, QString &parid);
    bool addTopAttr(int no, QString topid, QString tag, QString val);
    bool addSecNode(int no, QString topid, QString tag, QString val, QString &parid);
    bool addSecAttr(int no, QString topid, QString nid, QString tag, QString val);
    int getMaxSrt(QString tbl, QString topid="");

    bool delTop(QString whr);
    bool delSec(QString whr);

    bool setTable(QString tbl);
    bool setTag(QString tag, int lvl);
    int tagLvl(QString tag);

	bool createSequence(QString name);

	clsTagAttrRec *recNgp;
	clsTagAttrRec *recNgi;
	clsTagAttrRec *getTagDef(QString tag);

private:
	/// データベースオブジェクト
	QSqlDatabase db;

	/// テーブルヘッダ
	QString tblHead;

	QStringList lstTagTop;
	QStringList lstTagSec;
	int nTagTop;
	int nTagSec;
	bool mkTagTopLst();
	bool mkTagSecLst();
	bool setTagLst(QString sql, QStringList &lst, int &nTag);
};

#endif // CLSDB_H
