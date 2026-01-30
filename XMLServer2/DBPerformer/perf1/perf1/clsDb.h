/*
 * Copyright (C) 2012
 * Author : Masatoshi Sasai ,MEGATRADE corporation
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

class clsDb : public QObject
{
	Q_OBJECT

public:
	clsDb(QObject *parent=0);
	~clsDb();

	/// �f�[�^�x�[�X��
	QString dbnam;

	/// �f�[�^�x�[�X�^�C�v
	QString dbtype;

	/// DB���[�U
	QString dbusr;

	/// DB�p�X���[�h
	QString dbpwd;

	/// DB�z�X�g
	QString dbhost;

	clsLog *log;

	/// �ڑ��p�����[�^�Z�b�g
	/**
	 * �ڑ��p�����[�^���ݒ肷���B
	 * @param QString _dbtyp   �f�[�^�x�[�X�^�C�v
	 * @param QString _dbhost  �f�[�^�x�[�X�T�[�o�z�X�g��
	 * @param QString _dbnam   �f�[�^�x�[�X��
	 * @param QString _dbusr   �f�[�^�x�[�X���[�U��
	 * @param QString _dbpwd   �f�[�^�x�[�X�p�X���[�h
	 */
	void setPrm(QString _dbtyp, QString _dbhost, QString _dbnam, QString _dbusr, QString _dbpwd);
	void setPrm();

	bool initDb();

	/// �ڑ�
	/**
	 * @return bool
	 */
	bool Connect();

	/// �ؒf
	/**
	 * @return bool
	 */
	bool DisConnect();

	/// �X�V
	/**
	 * @param QString sql
	 * @return void
	 */
	bool updExecSql(QString sql);

	/// MAXID�擾
	/**
	 * @param QString
	 * @return QString
	 */
	QString maxId(QString tbl);

	/// �N�G���[���f������
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
     * �g�����U�N�V�����J�n
     * @return bool
     */
    bool beginTran();

    /**
     * �g�����U�N�V�����I��
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

private:
	/// �f�[�^�x�[�X�I�u�W�F�N�g
	QSqlDatabase db;

	/// �e�[�u���w�b�_
	QString tblHead;

	QStringList lstTagTop;
	QStringList lstTagSec;
	int nTagTop;
	int nTagSec;
	bool mkTagTopLst();
	bool mkTagSecLst();
	bool setTagLst(QString sql, QStringList &lst, int &nTag);

	bool createIndex(QString tbl, QString col, QString nam);
};

#endif // CLSDB_H