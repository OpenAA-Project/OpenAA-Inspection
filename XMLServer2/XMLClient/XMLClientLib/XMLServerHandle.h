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


#ifndef XMLSERVERHANDLE_H_
#define XMLSERVERHANDLE_H_

#include <QtNetwork>
#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QObject>

#include "XMLServerHandlePrivate.h"

class XMLServerHandle : public XMLServerHandlePrivate {
	Q_OBJECT
public:
	XMLServerHandle(QObject *par=0);
	virtual ~XMLServerHandle();

	bool Connect();
	bool DisConnect();
	bool GetStatus();

	bool selectXml(const QString &sql, QStringList &lst);
	bool openXml(const QString &sql, QString &buf);
	bool nextXml(QString &buf);

	bool addXml(const QString &sql);
	bool appendXml(const QString &sql);
	bool updateXml(const QString &sql);
	bool deleteXml(const QString &sql);

	int getCurrentPort() {
		return svrPort;
	}

	QString getErrorMess() {
		return errMess;
	}

private:
	QString rcvBufLex(QString cmd);
	bool SndRcv(QString cmd, QString mess);
	QString rcvBuf;

	QString svsql;
	QStringList lstHit;
	QStringList lstDbFile;
	int nHitCnt;
	int nCurIdx;

	bool mkLstDb(const QString &src);
};

/**
 * @brief XML�T�[�o�ڑ�
 *
 * XML�T�[�o�ւ̐ڑ��𐶐������B
 * @param const QString &IPAddress �T�[�o�A�h���X
 * @param int port �T�[�o�|�[�g�ԍ�
 * @param unsigned long WaitingTime �^�C���A�E�g�l
 * @return XMLServerHandle * �T�[�o�ڑ��q
 */
XMLServerHandle *XML_Connect(const QString &IPAddress,int port, unsigned long WaitingTime);

/**
 * @brief XML���[�h
 *
 * �w��SQL������XML���������A�q�b�g����XML�������ׂ�QStringList�Ɋi�[�����B
 * @param XMLServerHandle *Handle �T�[�o�ڑ��q
 * @param const QString &SelectStr ����SQL��
 * @param QStringList &RetStringList �������ʃ��X�g
 * @return bool true:�������i�Y���Ȃ��̏ꍇ�ł�true�j�Afalse�F�G���[��
 */
bool XML_Select(XMLServerHandle *Handle,const QString &SelectStr,QStringList &RetStringList);

/**
 * @brief XML���[�h(First)
 *
 * �w��SQL������XML���������A�q�b�g����XML���̂����ŏ��̂��̂�QString�Ɋi�[�����B<br>
 * �Y���Ȃ��̏ꍇ��RetString�ɋ󕶎����Z�b�g�������B
 * @param XMLServerHandle *Handle �T�[�o�ڑ��q
 * @param const QString &SelectStr ����SQL��
 * @param QString &RetString ��������
 * @return bool true:�������i�Y���Ȃ��̏ꍇ�ł�true�j�Afalse�F�G���[��
 */
bool XML_SelectFirst(XMLServerHandle *Handle,const QString &SelectStr,QString &RetString);

/**
 * @brief XML���[�h(Next)
 *
 * XML_SelectFirst���玟��XML���������A�Y����������RetString�Ɋi�[�����B<br>
 * �Y���Ȃ��̏ꍇ��RetString�ɋ󕶎����Z�b�g�������B
 * @param XMLServerHandle *Handle �T�[�o�ڑ��q
 * @param QString &RetString ��������
 * @return bool true:�������i�Y���Ȃ��̏ꍇ�ł�true�j�Afalse�F�G���[��
 */
bool XML_SelectNext(XMLServerHandle *Handle, QString &RetString);

/**
 * @brief XML�ǉ�
 *
 * �w��SQL������XML�����V�K�쐬�����B
 * @param XMLServerHandle *Handle �T�[�o�ڑ��q
 * @param const QString &InsertedString ����SQL��
 * @return bool true:�������Afalse�F�G���[��
 */
bool XML_Insert(XMLServerHandle *Handle,const QString &InsertedString);

/**
 * @brief XML�ǉ��iAppend)
 *
 * �w��SQL�������Y������XML���ɑ΂���XML�^�O���ǉ������B
 * @param XMLServerHandle *Handle �T�[�o�ڑ��q
 * @param const QString &InsertedString ����SQL��
 * @return bool true:�������Afalse�F�G���[��
 */
bool XML_Append(XMLServerHandle *Handle,const QString &InsertedString);

/**
 * @brief XML�X�V
 *
 * �w��SQL������XML���������A�Y�������΍ŏ��Ɍ�������XML���S�̂��X�V�����B
 * @param XMLServerHandle *Handle �T�[�o�ڑ��q
 * @param const QString &UpdatedString ����SQL��
 * @return bool true:�������i�Y���Ȃ��̏ꍇ�ł�true�j�Afalse�F�G���[��
 */
bool XML_Update(XMLServerHandle *Handle,const QString &UpdatedString);

/**
 * @brief XML�폜
 *
 * �w��SQL������XML���������A�Y������XML�����폜�����B
 * @param XMLServerHandle *Handle �T�[�o�ڑ��q
 * @param const QString &DeletedString ����SQL��
 * @return bool true:�������i�Y���Ȃ��̏ꍇ�ł�true�j�Afalse�F�G���[��
 */
bool XML_Delete(XMLServerHandle *Handle,const QString &DeletedString);

/**
 * @brief XML�T�[�o�ؒf
 *
 * XML�T�[�o�ւ̐ڑ����ؒf�����B
 * @param XMLServerHandle *Handle �T�[�o�ڑ��q
 * @return bool true:�������i�Y���Ȃ��̏ꍇ�ł�true�j�Afalse�F�G���[��
 */
bool XML_Close(XMLServerHandle *Handle);

/**
 * @brief XML�T�[�o���Ԏ擾
 *
 * XML�T�[�o�ւ̐ڑ��̏��Ԃ��擾�����B
 * @param XMLServerHandle *Handle �T�[�o�ڑ��q
 * @param bool &RetOpened true:�ڑ����Afalse:���ڑ�
 * @return bool true:�������Afalse�F�G���[��
 */
bool XML_GetState(XMLServerHandle *Handle,bool &RetOpened);
#endif /* XMLSERVERHANDLE_H_ */