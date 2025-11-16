#ifndef CLSLOG_H
#define CLSLOG_H

#include <QObject>

class clsLog : public QObject
{
	Q_OBJECT

public:
	clsLog(QObject *parent);
	~clsLog();

	//void startLog(QTcpSocket *sock);
	//void startLog(QString addr);
	void log(QString mess, int lvl=1);

	static const int CLSLOG_DEBUG = 4;
	static const int CLSLOG_WARNING = 3;
	static const int CLSLOG_INFO = 2;
	static const int CLSLOG_FAITAL = 1;
	static const int CLSLOG_NOLOG = 0;

private:
	QString fnam;
};

#endif // CLSLOG_H
