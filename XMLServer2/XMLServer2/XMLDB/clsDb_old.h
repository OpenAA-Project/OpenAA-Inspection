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

/**
 * @brief �f�[�^�x�[�X�����N���X
 *
 * �f�[�^�x�[�X�̐ڑ��^�ؒf�ASQL�̔��s�����s���B
 */
class clsDb: public QObject {
Q_OBJECT

public:
	clsDb(QObject *parent = 0);
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
	clsParamDef *prm;

	/**
	 * @brief �R�l�N�V�����������ݒ�
	 */
	void setConnDef(const QString &def);

	/// �ڑ��p�����[�^�Z�b�g
	/**
	 * @brief DB�ڑ��p�����[�^�Z�b�g
	 *
	 * �ڑ��p�����[�^���ݒ肷���B
	 * @param QString _dbtyp   �f�[�^�x�[�X�^�C�v
	 * @param QString _dbhost  �f�[�^�x�[�X�T�[�o�z�X�g��
	 * @param QString _dbnam   �f�[�^�x�[�X��
	 * @param QString _dbusr   �f�[�^�x�[�X���[�U��
	 * @param QString _dbpwd   �f�[�^�x�[�X�p�X���[�h
	 */
	void setPrm(const QString &_dbtyp, const QString &_dbhost, const QString &_dbnam,
			const QString &_dbusr, const QString &_dbpwd);

	/**
	 * @brief DB�ڑ��p�����[�^�Z�b�g
	 *
	 * clsParamDef����DB�ڑ��p�����[�^���ݒ肷���B
	 */
	void setPrm();

	/**
	 * @brief DB�ڑ�
	 *
	 * �w�肵���R�l�N�V��������DB�ɐڑ������B
	 * �ڑ�����DB�ڑ��p�����[�^�Ŏw���ς݂ł��邱��
	 * @param QString �R�l�N�V������
	 * @return bool
	 */
	bool Connect(QString nam="");

	/**
	 * @brief DB�ؒf
	 *
	 * �ڑ�����DB���ؒf�����B
	 * @return bool
	 */
	bool DisConnect();

	/**
	 * @brief �X�V�nSQL���s
	 *
	 * �w�肵���X�V�nSQL�����s�����B
	 * @param QString sql
	 * @return void
	 */
	bool updExecSql(const QString &sql);

	/**
	 * @brief MAXID�擾
	 *
	 * �w���e�[�u����MAXID���擾����
	 * @param QString
	 * @return QString
	 */
	QString maxId(const QString &tbl);

	/// �N�G���[���f������
	/**
	 * @brief �N�G���[���f������
	 *
	 * �w��SELECT������QSqlQueryModel�𐶐������B
	 * @param QString sql
	 * @return QSqlQueryModel
	 */
	QSqlQueryModel *mkQueryModel(const QString &sql);

	/// ���[�h���R�[�h
	QSqlRecord rec;

	/**
	 * @brief SELECT���s
	 *
	 * �w�肵��SELECT�������s���A���ʂ�rec�Ɋi�[����
	 * @param QString sql
	 * @return int �Y������:0 �Y���Ȃ�:1 �G���[:-1
	 */
	int readRec(const QString &sql);

	/// �G���[���b�Z�[�W
	QString mess;

	/**
	 * @brief �V�X�e�����t�擾
	 *
	 * �V�X�e�����t���擾���Ayyyy-MM-dd�ŕԋp
	 * @parab bool ���t�̂�:true ���ԕt��:false
	 */
	QString curDay(bool flgTime = false);

	/**
	 * @brief �g�����U�N�V�����J�n
	 * @return bool
	 */
	bool beginTran();

	/**
	 * @brief �g�����U�N�V�����I��
	 * @return bool �R�~�b�g:true ���[���o�b�N:false
	 */
	bool endTran(bool flg);

	/// �G���[�t���O �G���[��:false
	bool errflg;

	/**
	 * @brief TOP�m�[�h�ǉ�
	 *
	 * @param int no ���ԁi�O�Œ�)
	 * @param QString tag �^�O��
	 * @param QString &parid topid
	 * @return bool
	 */
	bool addTopNode(int no, const QString &tag, QString &parid);

	/**
	 * @brief TOP�m�[�h�����ǉ�
	 *
	 * topid�Ŏw�肵���m�[�h�̑������ǉ�����
	 * @param int no ����
	 * @param const QString &topid
	 * @param const QString &tag ������
	 * @param const QString &val �����l
	 * @return bool
	 */
	bool addTopAttr(int no, const QString &topid, const QString &tag, const QString &val);


	/**
	 * @brief �q�m�[�h�����ǉ�
	 *
	 * topid�Ŏw�肵���m�[�h�̎q�m�[�h���ǉ�����
	 * @param int no ����
	 * @param const QString &topid
	 * @param const QString &tag �^�O��
	 * @param const QString &val �l
	 * @param QString &parid topid �ǉ������q�m�[�h��ID
	 * @return bool
	 */
	bool addSecNode(int no, const QString &topid, const QString &tag, const QString &val,
			QString &parid);

	/**
	 * @brief �q�m�[�h�����ǉ�
	 *
	 * nid�Ŏw�肵���m�[�h�̑������ǉ�����
	 * @param int no ����
	 * @param const QString &topid
	 * @param const QString &nid
	 * @param const QString &tag ������
	 * @param const QString &val �����l
	 * @return bool
	 */
	bool addSecAttr(int no, const QString &topid, const QString &nid, const QString &tag,
			const QString &val);

	/**
	 * @brief �\�[�g���擾
	 *
	 * �w���e�[�u���̃\�[�g�����擾����
	 * @param const QString &tbl �e�[�u����
	 * @param QString topid=""
	 */
	int getMaxSrt(const QString &tbl, QString topid = "");

	// INSERT�v���y�A
	QSqlQuery *queryTop;
	QSqlQuery *queryTopAttr;
	QSqlQuery *querySec;
	QSqlQuery *querySecAttr;
	QSqlQuery **arrQueryFixIns;
	int nFixInsCnt;

	/**
	 * @brief INSERT�v���y�A�쐬
	 */
	bool makePrepare();

	/**
	 * @brief �g�b�v�m�[�h�폜
	 */
	bool delTop(const QString &whr);

	/**
	 * @brief �q�m�[�h�폜
	 */
	bool delSec(const QString &whr);

	/**
	 * @brief �e�[�u�����Z�b�g
	 *
	 * �e�[�u�������Z�b�g�����B
	 * �e�[�u�����쐬�����Ă��Ȃ��ꍇ�͍쐬�����B
	 */
	bool setTable(const QString &tbl);

	/**
	 * @brief �^�O���ۑ�
	 */
	bool setTag(const QString &tag, int lvl);

	/**
	 * @brief �^�O���x���擾
	 */
	int tagLvl(const QString &tag);

	/**
	 * @brief �V�[�P���X�쐬
	 *
	 * �w���e�[�u���̃V�[�P���X���쐬����
	 */
	bool createSequence(const QString &name);

	/**
	 * @brief �f�[�^�x�[�X�t�@�C���쐬
	 */
	static bool createDb(QString dbusr, QString dbpwd, QString dbpath);

	/**
	 * @brief �����e�[�u���쐬
	 */
	bool mkInitTbl();

	/**
	 * @brief �Œ��^�O�ݒ��擾
	 */
	clsTagAttrRec *getTagDef(QString tag);

	/**
	 * @brief �Œ��^�O�����ǉ�
	 */
	bool addFixAttr(const QString &topid, const QString &nid, int idx, const QList<QByteArray> &lstAttr);

	/**
	 * @brief DB�}�X�^�e�[�u���쐬
	 */
	bool mkMasterTbl();

	QString connNam;
	QString curDbNam;
	QString connDef;

	/**
	 * @brief �N�G���[�쐬
	 *
	 * �w��SQL������QSqlQuery���쐬����
	 * @param const QString sql
	 * @return QSqlQuery *
	 */
	QSqlQuery *mkSqlQuery(const QString &sql);
	QSqlQuery *openedQuery;

	/**
	 * @brief �N�G���[�I�[�v��
	 *
	 * �쐬�����N�G���[���I�[�v������
	 * @param QSqlQuery *
	 * @return bool
	 */
	bool openQuery(QSqlQuery *query=NULL);

	/**
	 * @brief �����R�[�h�擾
	 *
	 * �I�[�v�������N�G���[�����P�s�����o���B
	 * @param QSqlQuery *
	 * @return int �Y������:0 �Y���Ȃ�:1 �G���[:-1
	 */
	int next(QSqlQuery *query=NULL);

	/**
	 * @brief �N�G���[�N���[�Y
	 *
	 * �쐬�����N�G���[���J������
	 * @param QSqlQuery *
	 */
	void closeQuery(QSqlQuery *query=NULL);

	/**
	 * @brief �l�擾
	 *
	 * �����o�����s�����w�肵���l���擾����
	 * @param const QString &itm �J������
	 * @param QSqlQuery *
	 * @return QByteArray
	 */
	QByteArray queryValue(const QString &itm, QSqlQuery *query=NULL);

	/**
	 * @brief �N�G���[���s
	 *
	 * �쐬�����X�V�N�G���[�����s����
	 * @param QSqlQuery *
	 * @return bool
	 */
	bool execQuery(QSqlQuery *query=NULL);

	/// �e�[�u���w�b�_
	QString tblHead;

private:
	/// �f�[�^�x�[�X�I�u�W�F�N�g
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