#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CheckInstall.h"
#include <QThread>

class CheckInstall;

class CheckInstall : public QMainWindow
{
    Q_OBJECT

    CheckInstall *Thread;
public:
    CheckInstall(QWidget *parent = Q_NULLPTR);

    void    StartThread(void);
    void    StopThread(void);

private:
    Ui::CheckInstallClass ui;

private slots:
    void    SlotUpdateProgressBar(int n);
};

class CheckThread : public QThread
{
    Q_OBJECT

    volatile    bool    Terminated;
    CheckInstall    *Parent;
public:
	CheckThread(CheckInstall *p);
	~CheckThread(void);

    void    SetTerminate(bool b);

private:
    virtual void    run()   override;

signals:
    void    SignalUpdateProgressBar(int n);
};

