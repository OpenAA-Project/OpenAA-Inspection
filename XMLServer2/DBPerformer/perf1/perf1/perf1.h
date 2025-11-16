#ifndef PERF1_H
#define PERF1_H

#include <QWidget>
#include "ui_perf1.h"
#include "clsExecIns.h"

class perf1 : public QWidget
{
	Q_OBJECT

public:
	perf1(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~perf1();

	clsExecIns *objThr;

private slots:
	void exitWin();
	void execStart();
	void drawExecAns(double,double,double,double,double,int);

private:
	Ui::perf1Class ui;
	int nCurCnt;
};

#endif // PERF1_H
