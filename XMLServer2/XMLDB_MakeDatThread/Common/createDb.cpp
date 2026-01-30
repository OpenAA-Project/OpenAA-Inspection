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