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

#ifndef LOGINTEGRATORLIB_H
#define LOGINTEGRATORLIB_H
#include "logintegratorlib_global.h"
#include "LogIntegrator_pack.h"
#include "logerrdialog.h"
#include "LogIntegratorUtil.h"
#include <QObject>
#include <QString>
#include <QFile>

const int MAX_LOTNOLENGTH = 10;
const int MAX_KOHENNO     = 30;

class clsLogResult;
class clsLogResultContainer;
class clsLogItem;
class clsLogItemContainer;
class clsLogIntegratorLib;

class clsLogIntegratorLib : public QObject
{
	Q_OBJECT

public :
	clsLogIntegratorLib(){}

	void setPath1(QString src);
	void setPath2(QString src);
	void setLotNo(QString src);
	void setBaseNo(QString src);
	void setOutPath(QString src);

	bool makeLogIntegrate();
	bool outLog();

	bool errChk();
	void showErrDialog();
	void ClearErrDialogLogs(void);

	void makeErrLog();
	void showErrLog();
	bool IsErrLog();
	void ClearErrLog();
	bool outErrLog(QString Date);

	LogErrDialog dialog;

signals:
	void UpdateSignal(int Value);

private :
	QString Path1;
	QString Path2;
	QStringList SaveDateListPath1;
	QStringList SaveDateListPath2;
	QString LotNo;
	QString BaseNo;

	int ItemCount;

	QString OutPath;
	QString OutTime;

	clsLogItemContainer LogList;
	clsLogItemContainer ErrList;
	clsLogItemContainer SuccList;
	clsLogItemContainer AllErrList;

	bool searchSaveDate(void);
	QStringList searchLot(QString fPath);
	bool readLot(QString fPath);
	bool readBase(QString fPath);
	bool readLog(QString fPath);

	QFile file;
	bool writeLogLoop(QString fPath);
	bool writeLogHeader();
	bool writeLog(clsLogItem *rec);
	QString makeOutLogFileName(QString fPath);

	void addErrList(clsLogItem *src);
	void addSuccList(clsLogItem *src);

	bool writeErrLogLoop(QString fPath,QString Date);
	QString makeOutErrLogFileName(QString fPath,QString Date);
	bool writeErrLogHeader();
	bool writeErrLog(clsLogItem *rec);
};


#endif // LOGINTEGRATORLIB_H