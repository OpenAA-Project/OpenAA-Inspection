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

/**
 * @brief データベース操作クラス
 *
 * データベースの接続／切断、SQLの発行等を行う。
 */
class clsDb: public QObject {
Q_OBJECT

public:
	clsDb(QObject *parent = 0);
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
	clsParamDef *prm;

	/**
	 * @brief コネクション文字列設定
	 */
	void setConnDef(const QString &def);

	/// 接続パラメータセット
	/**
	 * @brief DB接続パラメータセット
	 *
	 * 接続パラメータを設定する。
	 * @param QString _dbtyp   データベースタイプ
	 * @param QString _dbhost  データベースサーバホスト名
	 * @param QString _dbnam   データベース名
	 * @param QString _dbusr   データベースユーザ名
	 * @param QString _dbpwd   データベースパスワード
	 */
	void setPrm(const QString &_dbtyp, const QString &_dbhost, const QString &_dbnam,
			const QString &_dbusr, const QString &_dbpwd);

	/**
	 * @brief DB接続パラメータセット
	 *
	 * clsParamDefからDB接続パラメータを設定する。
	 */
	void setPrm();

	/**
	 * @brief DB接続
	 *
	 * 指定したコネクション名でDBに接続する。
	 * 接続先はDB接続パラメータで指定済みであること
	 * @param QString コネクション名
	 * @return bool
	 */
	bool Connect(QString nam="");

	/**
	 * @brief DB切断
	 *
	 * 接続中のDBを切断する。
	 * @return bool
	 */
	bool DisConnect();

	/**
	 * @brief 更新系SQL実行
	 *
	 * 指定した更新系SQLを実行する。
	 * @param QString sql
	 * @return void
	 */
	bool updExecSql(const QString &sql);

	/**
	 * @brief MAXID取得
	 *
	 * 指定テーブルのMAXIDを取得する
	 * @param QString
	 * @return QString
	 */
	QString maxId(const QString &tbl);

	/// クエリーモデル生成
	/**
	 * @brief クエリーモデル生成
	 *
	 * 指定SELECT文からQSqlQueryModelを生成する。
	 * @param QString sql
	 * @return QSqlQueryModel
	 */
	QSqlQueryModel *mkQueryModel(const QString &sql);

	/// リードレコード
	QSqlRecord rec;

	/**
	 * @brief SELECT実行
	 *
	 * 指定したSELECT文を実行し、結果をrecに格納する
	 * @param QString sql
	 * @return int 該当あり:0 該当なし:1 エラー:-1
	 */
	int readRec(const QString &sql);

	/// エラーメッセージ
	QString mess;

	/**
	 * @brief システム日付取得
	 *
	 * システム日付を取得し、yyyy-MM-ddで返却
	 * @parab bool 日付のみ:true 時間付き:false
	 */
	QString curDay(bool flgTime = false);

	/**
	 * @brief トランザクション開始
	 * @return bool
	 */
	bool beginTran();

	/**
	 * @brief トランザクション終了
	 * @return bool コミット:true ロールバック:false
	 */
	bool endTran(bool flg);

	/// エラーフラグ エラー時:false
	bool errflg;

	/**
	 * @brief TOPノード追加
	 *
	 * @param int no 順番（０固定)
	 * @param QString tag タグ名
	 * @param QString &parid topid
	 * @return bool
	 */
	bool addTopNode(int no, const QString &tag, QString &parid);

	/**
	 * @brief TOPノード属性追加
	 *
	 * topidで指定したノードの属性を追加する
	 * @param int no 順番
	 * @param const QString &topid
	 * @param const QString &tag 属性名
	 * @param const QString &val 属性値
	 * @return bool
	 */
	bool addTopAttr(int no, const QString &topid, const QString &tag, const QString &val);


	/**
	 * @brief 子ノード属性追加
	 *
	 * topidで指定したノードの子ノードを追加する
	 * @param int no 順番
	 * @param const QString &topid
	 * @param const QString &tag タグ名
	 * @param const QString &val 値
	 * @param QString &parid topid 追加した子ノードのID
	 * @return bool
	 */
	bool addSecNode(int no, const QString &topid, const QString &tag, const QString &val,
			QString &parid);

	/**
	 * @brief 子ノード属性追加
	 *
	 * nidで指定したノードの属性を追加する
	 * @param int no 順番
	 * @param const QString &topid
	 * @param const QString &nid
	 * @param const QString &tag 属性名
	 * @param const QString &val 属性値
	 * @return bool
	 */
	bool addSecAttr(int no, const QString &topid, const QString &nid, const QString &tag,
			const QString &val);

	/**
	 * @brief ソート順取得
	 *
	 * 指定テーブルのソート順を取得する
	 * @param const QString &tbl テーブル名
	 * @param QString topid=""
	 */
	int getMaxSrt(const QString &tbl, QString topid = "");

	// INSERTプリペア
	QSqlQuery *queryTop;
	QSqlQuery *queryTopAttr;
	QSqlQuery *querySec;
	QSqlQuery *querySecAttr;
	QSqlQuery **arrQueryFixIns;
	int nFixInsCnt;

	/**
	 * @brief INSERTプリペア作成
	 */
	bool makePrepare();

	/**
	 * @brief トップノード削除
	 */
	bool delTop(const QString &whr);

	/**
	 * @brief 子ノード削除
	 */
	bool delSec(const QString &whr);

	/**
	 * @brief テーブル名セット
	 *
	 * テーブル名をセットする。
	 * テーブルが作成されていない場合は作成する。
	 */
	bool setTable(const QString &tbl);

	/**
	 * @brief タグ名保存
	 */
	bool setTag(const QString &tag, int lvl);

	/**
	 * @brief タグレベル取得
	 */
	int tagLvl(const QString &tag);

	/**
	 * @brief シーケンス作成
	 *
	 * 指定テーブルのシーケンスを作成する
	 */
	bool createSequence(const QString &name);

	/**
	 * @brief データベースファイル作成
	 */
	static bool createDb(QString dbusr, QString dbpwd, QString dbpath);

	/**
	 * @brief 初期テーブル作成
	 */
	bool mkInitTbl();

	/**
	 * @brief 固定タグ設定取得
	 */
	clsTagAttrRec *getTagDef(QString tag);

	/**
	 * @brief 固定タグ属性追加
	 */
	bool addFixAttr(const QString &topid, const QString &nid, int idx, const QList<QByteArray> &lstAttr);

	/**
	 * @brief DBマスタテーブル作成
	 */
	bool mkMasterTbl();

	QString connNam;
	QString curDbNam;
	QString connDef;

	/**
	 * @brief クエリー作成
	 *
	 * 指定SQL文からQSqlQueryを作成する
	 * @param const QString sql
	 * @return QSqlQuery *
	 */
	QSqlQuery *mkSqlQuery(const QString &sql);
	QSqlQuery *openedQuery;

	/**
	 * @brief クエリーオープン
	 *
	 * 作成したクエリーをオープンする
	 * @param QSqlQuery *
	 * @return bool
	 */
	bool openQuery(QSqlQuery *query=NULL);

	/**
	 * @brief 次レコード取得
	 *
	 * オープンしたクエリーから１行取り出す。
	 * @param QSqlQuery *
	 * @return int 該当あり:0 該当なし:1 エラー:-1
	 */
	int next(QSqlQuery *query=NULL);

	/**
	 * @brief クエリークローズ
	 *
	 * 作成したクエリーを開放する
	 * @param QSqlQuery *
	 */
	void closeQuery(QSqlQuery *query=NULL);

	/**
	 * @brief 値取得
	 *
	 * 取り出した行から指定した値を取得する
	 * @param const QString &itm カラム名
	 * @param QSqlQuery *
	 * @return QByteArray
	 */
	QByteArray queryValue(const QString &itm, QSqlQuery *query=NULL);

	/**
	 * @brief クエリー実行
	 *
	 * 作成した更新クエリーを実行する
	 * @param QSqlQuery *
	 * @return bool
	 */
	bool execQuery(QSqlQuery *query=NULL);

	/// テーブルヘッダ
	QString tblHead;

	bool isConnected();
private:
	/// データベースオブジェクト
	QSqlDatabase db;

	QStringList lstTagTop;
	QStringList lstTagSec;
	int nTagTop;
	int nTagSec;
	bool mkTagTopLst();
	bool mkTagSecLst();
	bool setTagLst(const QString &sql, QStringList &lst, int &nTag);

	bool createIndex(QString tbl, QString col, QString nam);
	bool createView(QString tbl);

	bool getDatabase(const QString &nam);
	bool mkDatabase(const QString &nam);
};

#endif // CLSDB_H
