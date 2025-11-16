/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\INSPECTDATA.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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
	//ID‚Åíœ
	bool INSPECTDATADelete(QList<QByteArray> &DelKey);
	//bool INSPECTDATADelete(QStringList &DelKey, QStringList &NGJ);
	//ˆêğŒ‚ÅŒŸõíœ
	bool INSPECTDATATagSelectDele(QByteArray &sSelData, QByteArray &Parent);
	//bool INSPECTDATATagSelectDele(QString &sSelData, QString &Parent, QStringList &NGJData);
	//ƒŠƒXƒgƒA
	bool INSPECTDATARestore(QByteArray &Data);
    //bool INSPECTDATARestore(QStringList &List, QStringList &NGJ);
	//1ğŒŒŸõ‚ÅNG”‚ğ•Ô‚·
	//bool INSPECTDATASelect(QString &JYOUKEN, QString &Parent, QList<QByteArray> &List);	
	bool INSPECTDATASelect(QByteArray &JYOUKEN, QByteArray &Parent, QList<QByteArray> &List);
	//•¡”ğŒŒŸõ‚ÅNG”‚ğ•Ô‚·
	bool INSPECTDATATagToTagnotNG(QList<QByteArray> &TagList, QList<QByteArray> &List)	;
	///•¡”ğŒŒŸõ
	bool INSPECTDATATagSelect(QByteArray &sSelData, QByteArray &Parent, QList<QByteArray> &List);
	//•¡”ğŒ‚ÅŒŸõ‚µíœ
	bool INSPECTDATAtagtotagdel(QList<QByteArray> &TagList);
	//MasterID‚ÅLot‚ğŒŸõ‚·‚é
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