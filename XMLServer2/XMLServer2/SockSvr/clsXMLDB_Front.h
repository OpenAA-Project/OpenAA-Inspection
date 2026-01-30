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


#ifndef CLSXMLDB_FRONT_H_
#define CLSXMLDB_FRONT_H_

#include <QObject>
#include <QString>
#include <QStringList>

#include "clsXmlUpd.h"
#include "clsDb.h"

/**
 * @brief XML�����R�}���h���s�t�����g�G���h�N���X
 */
class clsXMLDB_Front : public QObject {
	Q_OBJECT
public:
	clsXMLDB_Front(clsDb *db, int port, QObject *par=0);
	virtual ~clsXMLDB_Front();

	/**
	 * @brief XML����
	 *
	 * �w��SQL��XML���������A�q�b�g�����S�����Ԃ�
	 * @param const QByteArray &sql
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool searchAllXml(const QByteArray &sql, QByteArray &retByte);

	/**
	 * @brief XML����
	 *
	 * �w��SQL��XML���������A�q�b�g�����s�����P�s���Ԃ�
	 * @param const QByteArray &sql
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool searchFirstXml(const QByteArray &sql, QByteArray &retByte);

	/**
	 * @brief ��XML����
	 *
	 * searchFirstXml()�Ō������ꂽ�s���玟�̍s���Ԃ�
	 * @param const QByteArray &sql
	 * @param const QByteArray &id ���̍s��topid
	 * @param const QByteArray &dbFile ���̍s���i�[�����Ă���DB�t�@�C����
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool readXml(const QByteArray &sql, const QByteArray id, const QByteArray &dbFile, QByteArray &retByte);

	/**
	 * @brief XML����
	 *
	 * �w��SQL��XML���������A�q�b�g�����S�����Ԃ�
	 * �e�[�u������_all�̂Ƃ��R�[��������
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool searchAllXmlA(QByteArray &retByte);

	/**
	 * @brief XML����
	 *
	 * �w��SQL��XML���������A�q�b�g�����s�����P�s���Ԃ�
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool searchFirstXmlA(QByteArray &retByte);

	/**
	 * @brief ��XML����
	 *
	 * searchFirstXmlA()�Ō������ꂽ�s���玟�̍s���Ԃ�
	 * @param const QByteArray &id ���̍s��topid
	 * @param const QByteArray &dbFile ���̍s���i�[�����Ă���DB�t�@�C����
	 * @param QByteArray &retByte
	 * @return bool
	 */
	bool readXmlA(const QByteArray &id, const QByteArray &dbFile, QByteArray &retByte);

	/**
	 * @brief XML���ǉ�
	 *
	 * �w��SQL����XML�����ǉ�����
	 * @param const QByteArray &sql
	 * @return bool
	 */
	bool addXml(const QByteArray &sql);

	/**
	 * @brief XML���փ^�O�ǉ�
	 *
	 * �w��SQL�������肳����XML���Ƀ^�O���ǉ�����
	 * @param const QByteArray &sql
	 * @return bool
	 */
	bool appendXml(const QByteArray &sql);

	/**
	 * @brief XML���㏑��
	 *
	 * �w��SQL�������肳����XML�����㏑������
	 * @param const QByteArray &sql
	 * @return bool
	 */
	bool updateXml(const QByteArray &sql);

	/**
	 * @brief XML���쐬
	 *
	 * �w��SQL�������肳����XML�����폜����
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