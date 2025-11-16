/*
 * clsDbCtrl.h
 *
 *  Created on: 2010/03/23
 *      Author: cony
 */

#ifndef CLSDBCTRL_H_
#define CLSDBCTRL_H_

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>
#include <QMutex>
#include "NList.h"
#include "clsLog.h"
#include "clsDb.h"

/**
 * @brief DBファイル定義
 */
class clsDbDef : public NPList<clsDbDef> {
public:
	clsDbDef() {
		MstId = "";
		dDay = QDate::currentDate().toString("yyyyMMdd").toAscii();
		Mac = "";
		dbFile = "";
	}

	~clsDbDef() {
		MstId.clear();
		dDay.clear();
		Mac.clear();
		dbFile.clear();
	}
	QByteArray MstId;
	QByteArray dDay;
	QByteArray Mac;
	QByteArray dbFile;
};

/**
 * @brief DBマスタ制御クラス
 *
 * DBファイル選択制御を行う。
 * 本クラスはGetInstance()のみで生成される。
 */
class clsDbCtrl {
public:
	/**
	 * @brief DBマスタ制御インスタンス作成
	 */
	static clsDbCtrl *GetInstance() {
		static clsDbCtrl def;
		return &def;
	}

	/**
	 * @brief XML追加時DB選択
	 *
	 * 新規XML追加時のDB選択を行う。
	 * @param const QByteArray &MstId マスタID(XML分のテーブル名を使用)
	 * @param const QByteArray &Mac 装置番号
	 * @param const QByteArray &Day 検査日時(YYMMDDHHMISS）
	 */
	clsDbDef *addDb(const QByteArray &MstId, const QByteArray &Mac, const QByteArray &Day);

	/**
	 * @brief タグ追加DB選択
	 *
	 * 既存XMLにタグ追加時のDB選択を行う。
	 * @param const QByteArray &MstId マスタID(XML分のテーブル名を使用)
	 * @param const QByteArray &Mac 装置番号
	 * @param const QByteArray &Day 検査日時(YYMMDDHHMISS,ただし頭の0はない場合あり）
	 */
	clsDbDef *appendDb(const QByteArray &MstId, const QByteArray &Mac, const QByteArray &Day);

	/**
	 * @brief XML更新時DB選択
	 *
	 * マスタID、装置番号、検査日時よりDBを選択する。
	 * @param const QByteArray &MstId
	 * @param const QByteArray &Mac 装置番号
	 * @param const QByteArray &Day 検査日時(YYMMDDHHMISS,ただし頭の0はない場合あり）
	 */
	clsDbDef *updDb(const QByteArray &MstId, const QByteArray &Mac, const QByteArray &Day);

	clsDbDef *getPceDbDef(const QByteArray &MstId);

	/**
	 * @brief DB定義リスト作成
	 * DBマスタから条件に合うDBファイルリストを生成する。
	 * @param const QByteArray &dbWhr DBマスタ検索条件
	 * @param clsLog *log ログオブジェクトポインタ
	 */
	static NPListPack<clsDbDef> *mkDbLst(const QByteArray &dbWhr, clsLog *log);

	/// DB定義リスト
	NPListPack<clsDbDef> *lstDbDef;

	/**
	 * @brief DB定義セット
	 *
	 * clsDbオブジェクトにDB定義をセットする。
	 */
	void setDbDef(const clsDbDef *dbDef, clsDb *db);

	void debugDbDef(const clsDbDef *dbDef);

	bool setDbFile(const QByteArray &MstId, clsDb *db);

private:
	clsDbCtrl();
	virtual ~clsDbCtrl();

	clsParamDef *prm;
	clsDb *db;

	/**
	 * @brief DB定義追加
	 *
	 * @param const clsDbDef *dbDef
	 */
	bool addDbDef(const clsDbDef *dbDef, const QByteArray &dDay);

	bool appendReadDb(clsDbDef *dbDef);

	bool newDbDef(clsDbDef *dbDef);

	/**
	 * @brief DBファイル作成
	 *
	 * 新規DBファイルを作成し、テーブル定義を実行する。
	 * @param const clsDbDef *dbDef
	 */
	bool makeDbFile(const clsDbDef *dbDef);

	/// ロック
	void lock();

	/// アンロック
	void unlock();

	/**
	 * @brief DB日付チェック
	 *
	 * 現在の日付が最新DB日付＋ChgDbDayより大きければfalse
	 * @param const clsDbDef *dbDef
	 */
	bool chkDbDate(const clsDbDef *dbDef, const QByteArray &dDay="");

	QMutex mutex;

	QByteArray bindDay(const QByteArray &daytime);
	QByteArray mkDbFileName(const QByteArray &MstId, const QByteArray &Mac, const QByteArray &Day);
	QByteArray bindMac(const QByteArray &Mac);
};

#endif /* CLSDBCTRL_H_ */
