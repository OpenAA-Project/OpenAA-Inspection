/*
 * createDb.cpp
 *
 *  Created on: 2010/01/15
 *      Author: cony
 */

#include "clsDb.h"
#include <ibase.h>

#include <QDebug>

bool clsDb::createDb(QString dbpath) {
	QString sql = "CREATE DATABASE '" + dbpath + "' ";
	sql += "USER '"+dbusr+"' PASSWORD '"+dbpwd+"' ";
	sql += "PAGE_SIZE=16384";

	qDebug() << sql;

	ISC_STATUS_ARRAY status;
	isc_db_handle databaseHandle = NULL;
	isc_tr_handle transactionHandle = NULL;

	unsigned short g_nFbDialect = SQL_DIALECT_V6;
	if (isc_dsql_execute_immediate(status, &databaseHandle, &transactionHandle,
			0, sql.toStdString().c_str(), g_nFbDialect, NULL)) {
		SQLCODE = isc_sqlcode(status);
		return false;
	}

	isc_commit_transaction(status, &transactionHandle);
	if (databaseHandle != NULL) {
		ISC_STATUS_ARRAY status;
		isc_detach_database(status, &databaseHandle);
	}

	return true;
}
