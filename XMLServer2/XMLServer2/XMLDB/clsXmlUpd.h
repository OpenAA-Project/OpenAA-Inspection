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
 * @brief XML�����N���X
 */
class clsXmlUpd {
public:
	clsXmlUpd();
	virtual ~clsXmlUpd();

	clsXmlReadSql *readSql;

	/**
	 * @brief �����nSQL����
	 */
	bool lexSelSql(const QByteArray &sql);

	/**
	 * @brief �X�V�nSQL����
	 */
	bool lexUpdSql(const QByteArray &sql);

	/**
	 * @brief XML���p�[�X
	 */
	bool parse(const QByteArray &buf);

	/**
	 * @brief XML�ǉ�
	 */
	bool addXml();

	/**
	 * @brief �^�O�ǉ�
	 */
	bool appendXml();

	/**
	 * @brief XML�폜
	 */
	bool deleteXml();

	bool updateXml();

	/**
	 * @brief XML������
	 *
	 * @param int idx 1�̏ꍇ�A�ŏ��̂P�����^�[��
	 */
	bool searchXml(int idx=-1);
	QList<QByteArray> lstResult;
	QList<QByteArray> lstResultId;
	int nResCnt;

	/**
	 * @brief ��XML������
	 *
	 * searchXml(1)�Ń��[�h�������̍s�iXML�j���擾����
	 */
	bool nextXml(const QString &id);

	QList<QByteArray> lstDbFile;

	/**
	 * @brief XML������
	 *
	 * �SDB�t�@�C�����Ώۂ�XML������������
	 */
	bool allSearchXml(int idx=-1);

	/**
	 * @brief ��XML������
	 *
	 * allSearchXml(1)�Ń��[�h�������̍s�iXML�j���擾����
	 */
	bool allNextXml(const QString &id, const QByteArray &dbFile);

	/**
	 * @brief XML�����[�h
	 *
	 * �w�肵��topid����XML�������[�h����
	 */
	bool readXml(QString topid);

	/**
	 * @brief XML���ϊ�
	 *
	 * XML�����e�L�X�g�ɕϊ�����
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