#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AutoReStart.h"
#include <QIODevice>
#include <QTimer>

class AutoReStartParam
{
public:
    QString ExeFileName;
    QString WorkingPath;
    QString Parameter;
    int     WaitingSecond;

	AutoReStartParam();
	~AutoReStartParam();

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};

class AutoReStart : public QMainWindow
{
    Q_OBJECT

    QTimer  TM;
    bool    StopMode;
public:
    AutoReStartParam    ParamData;

    AutoReStart(QWidget *parent = nullptr);
    ~AutoReStart();

private slots:
    void on_pushButtonStart_clicked();
    void on_toolButtonStop_triggered(QAction *arg1);
    void on_pushButtonParam_clicked();

    void    SlotDialTick();

private:
    Ui::AutoReStartClass ui;
};
