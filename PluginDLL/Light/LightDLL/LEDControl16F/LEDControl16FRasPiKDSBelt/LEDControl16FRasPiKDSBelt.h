#ifndef LEDControl16FRasPiKDSBelt_H
#define LEDControl16FRasPiKDSBelt_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include <QTimer>
#include "NListRPi.h"
#include "DeviceStruct.h"

namespace Ui {
class LEDControl16FRasPiKDSBelt;
}
class LEDControl16FRasPiKDSBelt;

class   SocketClient : public QObject ,public NPList<SocketClient>
{
    Q_OBJECT

    LEDControl16FRasPiKDSBelt  *Parent;
     QTcpSocket         *Socket;
public:
    SocketClient(LEDControl16FRasPiKDSBelt *parent ,QTcpSocket *s);
    ~SocketClient(void);

    bool	SendOut(BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short DataLen);

private slots:
    void    SlotReadyRead();
    void    SlotDisconnected();
};

class LEDControl16FRasPiKDSBelt : public QMainWindow
{
    Q_OBJECT
    QTcpServer  Server;
    int     DipSW_GIO;

    QTimer  TM;
    int     AverageCounter;
    int     AddedAverage;
    int     SubFrameTriggerCounter;

public:
    struct  TimingData  *RingBuffer;
    int     AllocCount;
    int     RPoint;
    int     WPoint;

    int     LightBoardCount;

public:
    struct	KDSBeltPIOStruct	GIOData;

    QMutex                      AccessMutex;
    NPListPack<SocketClient>    ClientList;
    
    explicit LEDControl16FRasPiKDSBelt(QWidget *parent = nullptr);
    ~LEDControl16FRasPiKDSBelt();

    void    DisconnectClient(SocketClient *s);
    void    ReceiveData(struct KDSBeltPIOFixedStruct &data);

    void    WriteInitial(void);
    void    WriteGIO(int DipSW);
    void    ReadGIO(int DipSW);

    void    WriteGForBit(int DipSW ,int Brd);
    int     ReadGForBit(int DipSW ,int Brd);	//Return Motor counter

    void    TestWriteE(int DipSW);


    void    SendLightInfo(SocketClient *s);

private slots:
    void on_pushButtonSendFrameTrigger_clicked();
    void on_pushButtonSaveSetting_clicked();
    void    SlotNewConnection();
    void    SlotTimeOut();

    void on_toolButtonTestMode_clicked();

private:
    Ui::LEDControl16FRasPiKDSBelt *ui;
    
    void InitialSignal(void);
    
    void	GetGIODataFromWindow(void);
    void	SetGIODataToWindow(void);
};

#endif // LEDControl16FRasPiKDSBelt_H
