#ifndef CLTSIMULATOR_H
#define CLTSIMULATOR_H

#include <QWidget>
#include "ui_cltSimulator.h"

#include "clsMainThread.h"

class cltSimulator : public QWidget
{
    Q_OBJECT

public:
    cltSimulator(QWidget *parent = 0);
    ~cltSimulator();

public slots:
	void setTime(int col, double val);
	void setCntThr(int row, int col, double val);
	void showMess(QString mess);

private slots:
	void exitApp();
	void startExec();

private:
    Ui::cltSimulatorClass ui;

    int nResRow;

    clsMainThread *objMain;
    bool writeRes();
};

#endif // CLTSIMULATOR_H
