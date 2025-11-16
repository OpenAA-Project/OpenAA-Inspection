/*
 * createDb.cpp
 *
 *  Created on: 2010/01/15
 *      Author: cony
 */

#include "clsDb.h"
#include <ibase.h>

#include <QDebug>

#include <crtdbg.h>
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

bool clsDb::createDb(QString dbusr, QString dbpwd, QString dbpath) {
	QString sql = "CREATE DATABASE '" + dbpath + "' ";
	sql += "USER '"+dbusr+"' PASSWORD '"+dbpwd+"' ";
	sql += "PAGE_SIZE=16384";

	qDebug() << sql;

	ISC_STATUS_ARRAY status;
	isc_db_handle databaseHandle = NULL;
	isc_tr_handle transactionHandle = NULL;

	unsigned short g_nFbDialect = SQL_DIALECT_V6;
	if (isc_dsql_execute_immediate(status, &databaseHandle, &transactionHandle,
			0, (char *)sql.toStdString().c_str(), g_nFbDialect, NULL)) {
		return false;
	}

	isc_commit_transaction(status, &transactionHandle);
	if (databaseHandle != NULL) {
		ISC_STATUS_ARRAY status;
		isc_detach_database(status, &databaseHandle);
	}

	return true;
}
