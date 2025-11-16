#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_YasukawaMotoCom.h"

class OperationForm;
class IOForm;

class YasukawaMotoCom : public QMainWindow
{
    Q_OBJECT

public:
    short   MachineID;
private:
    QTimer  TM;
    bool    CommandMemorizeTorque;
    double  MemorizedTorque[16];
    unsigned long   MemorizedTime;
    bool    OnWorking;
    OperationForm   *Operation;
    IOForm          *IO;
public:
    YasukawaMotoCom(QWidget *parent = nullptr);
    ~YasukawaMotoCom();

    bool    StopMeasure(void);
    bool    StartMeasure(void);
    bool    WaitWhileMoving(void);
private slots:
    void on_pushButtonOpen_clicked();
    void on_toolButtonServoON_clicked();
    void on_toolButtonHoldON_clicked();
    void on_pushButtonGetStatus_clicked();
    void    SlotTimeOut();
    void on_pushButtonMovRel_clicked();

    void on_pushButtonStop_clicked();

private:
    Ui::YasukawaMotoComClass ui;

};

