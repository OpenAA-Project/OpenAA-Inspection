/*
 * clsLog.h
 *
 *  Created on: 2009/11/08
 *      Author: cony
 */

#ifndef CLSLOG_H_
#define CLSLOG_H_

#include <QObject>
#include <QtNetwork>

class clsLog : public QObject {
	Q_OBJECT
public:
	clsLog(QString _logDir) {
		logDir = _logDir;
	}

	void startLog(QString addr);
	void log(QString mess, int lvl=1);

	static const int CLSLOG_DEBUG = 4;
	static const int CLSLOG_WARNING = 3;
	static const int CLSLOG_INFO = 2;
	static const int CLSLOG_FAITAL = 1;
	static const int CLSLOG_NOLOG = 0;

private:
	QString fnam;
	QString logDir;
};

#endif /* CLSLOG_H_ */
