/*
 * Copyright (C) 2023
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



#ifndef INSPECTDATA_H
#define INSPECTDATA_H

#include "clientmain.h"
#include "Progressbar.h"

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QtSql>
#include <QtSql/QSqlQuery>
class ClientMain;

class INSPECTDATA : public QObject
{
  Q_OBJECT
public slots:
		void DisconnectMessage();
public:

    INSPECTDATA();
	QSqlQueryModel *model;
	Progressbar *PBdialog;
	ClientMain *xmlCont;
	QString HOST;
	QString PORT;
	QByteArray Msg;
	void Test();
	bool INSPECTDATAFileDBXML(QList<QByteArray> List, QList<QByteArray> &RetList);
	bool INSPECTDATAistSelect(QList<QByteArray> &RetList);
	bool INSPECTDATATagToTagSelect(QList<QByteArray> &sSelData, QList<QByteArray> &List);
	//bool INSPECTDATATagToTagSelect(QStringList &sSelData, QString &Parent, QStringList &List);
	//ID�ō폜
	bool INSPECTDATADelete(QList<QByteArray> &DelKey);
	//bool INSPECTDATADelete(QStringList &DelKey, QStringList &NGJ);
	//�������Ō����폜
	bool INSPECTDATATagSelectDele(QByteArray &sSelData, QByteArray &Parent);
	//bool INSPECTDATATagSelectDele(QString &sSelData, QString &Parent, QStringList &NGJData);
	//���X�g�A
	bool INSPECTDATARestore(QByteArray &Data);
    //bool INSPECTDATARestore(QStringList &List, QStringList &NGJ);
	//1����������NG�����Ԃ�
	//bool INSPECTDATASelect(QString &JYOUKEN, QString &Parent, QList<QByteArray> &List);	
	bool INSPECTDATASelect(QByteArray &JYOUKEN, QByteArray &Parent, QList<QByteArray> &List);
	//��������������NG�����Ԃ�
	bool INSPECTDATATagToTagnotNG(QList<QByteArray> &TagList, QList<QByteArray> &List)	;
	///������������
	bool INSPECTDATATagSelect(QByteArray &sSelData, QByteArray &Parent, QList<QByteArray> &List);
	//���������Ō������폜
	bool INSPECTDATAtagtotagdel(QList<QByteArray> &TagList);
	//MasterID��Lot����������
	bool INSPECTDATAMasterToLot(QByteArray &Master, QByteArray &Parent, QList<QByteArray> &List);
	
	bool LOTCUNT(QList<QByteArray> &TagList, QByteArray &Cunt);
	bool INSPECTDATAcount(QList<QByteArray> &TagList, int &Count);

	bool INSPECTDATALotGet(QByteArray &Path, QByteArray &Master, QList<QByteArray> &RetList);
	
	bool INSPECTDATAConnect();

#if 1 // 20091112
	int RestoreINSPECTDATA(QByteArray &StartSyori, QByteArray &LID, QByteArray &LNM);
#endif
	int StartINSPECTDATA(QByteArray &StartSyori);

	bool INSPECTDATAFileDelete(QByteArray &File);
	bool INSPECTDATAClose();

	bool INSPECTDATAFileGet(QByteArray &File, QList<QByteArray> &RetFile, QList<QByteArray> &RetData);
	bool INSPECTDATAFileLoad(QByteArray &File, QByteArray &Data);
	int FirstConnect();
private:

};

#endif // INSPECTDATA_H