#ifndef MANUALOPERATIONDIALOG_H
#define MANUALOPERATIONDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QTcpServer>
#include "XTypeDef.h"

namespace Ui {
class ManualOperationDialog;
}

#pragma	pack(push)
#pragma	pack(4)
struct MotionValue
{
    unsigned short	Axis;
    double  TargetPos;
    double  Velocity;
};

struct MotionLinkPos
{
    double  TargetPos[6];
    double  Velocity;
};

struct MotionTarget
{
    int ID;
    double  TargetPos[6];
    double  JointVelocity;
    double  TrajectoryVelocity;
    double  OrientationVelocity;
};

#pragma	pack(pop)

class ManualOperationDialog : public QDialog
{
    Q_OBJECT

    QTcpSocket  Sock    ;
    QTcpServer  Server  ;
    QTcpSocket  *SensSocket;

    double  CurrentPos[32];
    double  CurrentTorque[32];
    bool    ServoON   ;
    bool    ErrorOccur;
    bool    AlarmOccur;
    QString OwnIP;
public:
    explicit ManualOperationDialog(QWidget *parent = nullptr);
    ~ManualOperationDialog();
signals:
    void    SignalRefreshCurrent();

private slots:
    void on_pushButtonConnect_clicked();
    void    SlotNewConnection();
    void    SlotSockReceive();
    void    SlotSensSockReceive();
    void    SlotRefreshCurrent();

    void on_toolButtonServoON_clicked();
    void on_toolButtonHoldON_clicked();
    void on_pushButtonPlus100X_clicked();
    void on_pushButtonMinus100X_clicked();
    void on_pushButtonPlus10X_clicked();
    void on_pushButtonMinus10X_clicked();
    void on_pushButtonPlus1X_clicked();
    void on_pushButtonMinus1X_clicked();
    void on_pushButtonPlus100Y_clicked();
    void on_pushButtonMinus100Y_clicked();
    void on_pushButtonPlus10Y_clicked();
    void on_pushButtonMinus10Y_clicked();
    void on_pushButtonPlus1Y_clicked();
    void on_pushButtonMinus1Y_clicked();
    void on_pushButtonPlus100Z_clicked();
    void on_pushButtonMinus100Z_clicked();
    void on_pushButtonPlus10Z_clicked();
    void on_pushButtonMinus10Z_clicked();
    void on_pushButtonPlus1Z_clicked();
    void on_pushButtonMinus1Z_clicked();
    void on_pushButtonPlus100R_clicked();
    void on_pushButtonMinus100R_clicked();
    void on_pushButtonPlus10R_clicked();
    void on_pushButtonMinus10R_clicked();
    void on_pushButtonPlus1R_clicked();
    void on_pushButtonMinus1R_clicked();
    void on_pushButtonPlus100B_clicked();
    void on_pushButtonMinus100B_clicked();
    void on_pushButtonPlus10B_clicked();
    void on_pushButtonMinus10B_clicked();
    void on_pushButtonPlus1B_clicked();
    void on_pushButtonMinus1B_clicked();
    void on_pushButtonPlus100T_clicked();
    void on_pushButtonMinus100T_clicked();
    void on_pushButtonPlus10T_clicked();
    void on_pushButtonMinus10T_clicked();
    void on_pushButtonPlus1T_clicked();
    void on_pushButtonMinus1T_clicked();
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDelLine_clicked();
    void on_pushButtonRun_clicked();

    void on_pushButtonStop_clicked();
private:
    Ui::ManualOperationDialog *ui;

    void SendCommand(int Cmd, BYTE *Data ,int DataLen);
};

#endif // MANUALOPERATIONDIALOG_H
