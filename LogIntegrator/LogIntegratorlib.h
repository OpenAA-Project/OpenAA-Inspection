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
