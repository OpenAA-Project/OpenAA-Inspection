/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\connection.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QSqlDriver>
//#include <qsql_ibase.h>
#include "TransDatabaseLib.h"
#include <QDir>
#include "qsql_ibase_p.h"

static bool createConnection(QString strPath="")
{
     QSqlDatabase db;
	QSqlDriver	*Drv=new QIBaseDriver();
	//QSqlDriver	*Drv=new TrSqlDriver();

    db=QSqlDatabase::addDatabase(Drv);
//	QFile	mfile("/Regulus64v2/save.dat");

	QDir::setCurrent(QCoreApplication::applicationDirPath());

	QFile	mfile;
	if(strPath.isEmpty()==true){
		mfile.setFileName("save.dat");
	}
	else{
		mfile.setFileName(strPath);
	}

	if(mfile.open(QIODevice::ReadOnly)==true){
		QTextStream mystream(&mfile);
		QString myString;
		QString hostport;
		int i=1;
		while (mystream.atEnd()==0){
			myString=mystream.readLine();
			switch(i){
			case 1:					
				hostport=myString;	//hostname
				break;
			case 2:
				db.setDatabaseName(myString);
				break;
			case 3:
				db.setUserName(myString);			//username
				break;
			case 4:
				db.setPassword(myString);		//password
				break;
			case 6:
				hostport+=/**/"/"+myString;	//hostname/portnumber
				db.setHostName(hostport);
			//	db.setPort(myString.toInt());			
				break;
			}
			i++;
		}
	}else{
		QMessageBox::critical(0, QObject::tr("Cannot open file"),
		QObject::tr("Cannot open save.dat\n"
					"Click Cancel to exit."), QMessageBox::Cancel,
					QMessageBox::NoButton);
		return false;
	}

    if (!db.open()) {
		QMessageBox::critical(0, QObject::tr("Cannot open database"),
		QObject::tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel,
                     QMessageBox::NoButton);
        return false;
    }
    return true;
}

#endif
