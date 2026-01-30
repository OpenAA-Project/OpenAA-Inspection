/*
 * Copyright (C) 2012
 * Author : cony
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
 * @brief DB�t�@�C�����`
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
 * @brief DB�}�X�^�����N���X
 *
 * DB�t�@�C���I�𐧌����s���B
 * �{�N���X��GetInstance()�݂̂Ő����������B
 */
class clsDbCtrl {
public:
	/**
	 * @brief DB�}�X�^�����C���X�^���X�쐬
	 */
	static clsDbCtrl *GetInstance() {
		static clsDbCtrl def;
		return &def;
	}

	/**
	 * @brief XML�ǉ���DB�I��
	 *
	 * �V�KXML�ǉ�����DB�I�����s���B
	 * @param const QByteArray &MstId �}�X�^ID(XML���̃e�[�u�������g�p)
	 * @param const QByteArray &Mac ���u�ԍ�
	 * @param const QByteArray &Day ��������(YYMMDDHHMISS�j
	 */
	clsDbDef *addDb(const QByteArray &MstId, const QByteArray &Mac, const QByteArray &Day);

	/**
	 * @brief �^�O�ǉ�DB�I��
	 *
	 * ����XML�Ƀ^�O�ǉ�����DB�I�����s���B
	 * @param const QByteArray &MstId �}�X�^ID(XML���̃e�[�u�������g�p)
	 * @param const QByteArray &Mac ���u�ԍ�
	 * @param const QByteArray &Day ��������(YYMMDDHHMISS,����������0�͂Ȃ��ꍇ�����j
	 */
	clsDbDef *appendDb(const QByteArray &MstId, const QByteArray &Mac, const QByteArray &Day);

	/**
	 * @brief XML�X�V��DB�I��
	 *
	 * �}�X�^ID�A���u�ԍ��A������������DB���I�������B
	 * @param const QByteArray &MstId
	 * @param const QByteArray &Mac ���u�ԍ�
	 * @param const QByteArray &Day ��������(YYMMDDHHMISS,����������0�͂Ȃ��ꍇ�����j
	 */
	clsDbDef *updDb(const QByteArray &MstId, const QByteArray &Mac, const QByteArray &Day);

	clsDbDef *getPceDbDef(const QByteArray &MstId);

	/**
	 * @brief DB���`���X�g�쐬
	 * DB�}�X�^���������ɍ���DB�t�@�C�����X�g�𐶐������B
	 * @param const QByteArray &dbWhr DB�}�X�^��������
	 * @param clsLog *log ���O�I�u�W�F�N�g�|�C���^
	 */
	static NPListPack<clsDbDef> *mkDbLst(const QByteArray &dbWhr, clsLog *log);

	/// DB���`���X�g
	NPListPack<clsDbDef> *lstDbDef;

	/**
	 * @brief DB���`�Z�b�g
	 *
	 * clsDb�I�u�W�F�N�g��DB���`���Z�b�g�����B
	 */
	void setDbDef(const clsDbDef *dbDef, clsDb *db);

	void debugDbDef(const clsDbDef *dbDef);

	bool setDbFile(const QByteArray &MstId, clsDb *db);

	bool chkDbFileName(const clsDbDef *dbDef, clsDb *db);

private:
	clsDbCtrl();
	virtual ~clsDbCtrl();

	clsParamDef *prm;
	clsDb *db;

	/**
	 * @brief DB���`�ǉ�
	 *
	 * @param const clsDbDef *dbDef
	 */
	bool addDbDef(const clsDbDef *dbDef, const QByteArray &dDay);

	bool appendReadDb(clsDbDef *dbDef);

	bool newDbDef(clsDbDef *dbDef);

	/**
	 * @brief DB�t�@�C���쐬
	 *
	 * �V�KDB�t�@�C�����쐬���A�e�[�u�����`�����s�����B
	 * @param const clsDbDef *dbDef
	 */
	bool makeDbFile(const clsDbDef *dbDef);

	/// ���b�N
	void lock();

	/// �A�����b�N
	void unlock();

	/**
	 * @brief DB���t�`�F�b�N
	 *
	 * ���݂̓��t���ŐVDB���t�{ChgDbDay�����傫������false
	 * @param const clsDbDef *dbDef
	 */
	bool chkDbDate(const clsDbDef *dbDef, const QByteArray &dDay="");

	QMutex mutex;

	QByteArray bindDay(const QByteArray &daytime);
	QByteArray mkDbFileName(const QByteArray &MstId, const QByteArray &Mac, const QByteArray &Day);
	QByteArray bindMac(const QByteArray &Mac);
};

#endif /* CLSDBCTRL_H_ */