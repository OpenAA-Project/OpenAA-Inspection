#ifndef XMLDB_MAKEDATTHREAD_H
#define XMLDB_MAKEDATTHREAD_H

#include <QWidget>
#include "ui_xmldb_makedatthread.h"

#include "clsMakeDat.h"

class XMLDB_MakeDatThread : public QWidget
{
    Q_OBJECT

public:
    XMLDB_MakeDatThread(QWidget *parent = 0);
    ~XMLDB_MakeDatThread();

private slots:
	void exitApp();
	void execMakeDat();
	void showMess1(QString mess,bool bWait);
	void showMess2(QString mess,bool bWait);

private:
    Ui::XMLDB_MakeDatThreadClass ui;

    clsMakeDat *thrMakeDat1;
    clsMakeDat *thrMakeDat2;
    void clearMakeDatObj();

    int nRow1;
    int nRow2;
    void setResRow(int nRow, QTableWidget *wid, double dMax, double dMin, double dAvg, double dCnt, double dSum);
};

#endif // XMLDB_MAKEDATTHREAD_H
