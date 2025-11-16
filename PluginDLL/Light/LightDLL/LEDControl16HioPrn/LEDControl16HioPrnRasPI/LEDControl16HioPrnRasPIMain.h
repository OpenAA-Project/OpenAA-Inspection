#ifndef LEDCONTROL16HIOPRNRASPIMAIN_H
#define LEDCONTROL16HIOPRNRASPIMAIN_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include <QTimer>
#include "NListRPi.h"
#include "DeviceStruct.h"

namespace Ui {
class LEDControl16HioPrnRasPIMain;
}
class LEDControl16HioPrnRasPIMain;
class QSerialPort;

class   SocketClient : public QObject ,public NPList<SocketClient>
{
    Q_OBJECT

    LEDControl16HioPrnRasPIMain  *Parent;
     QTcpSocket         *Socket;
public:
    SocketClient(LEDControl16HioPrnRasPIMain *parent ,QTcpSocket *s);
    ~SocketClient(void);

    bool	SendOut(BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short DataLen);

private slots:
    void    SlotReadyRead();
    void    SlotDisconnected();
};


class LEDControl16HioPrnRasPIMain : public QMainWindow
{
    Q_OBJECT
    QSerialPort     *Sio;
    
    QTcpServer  *Server;
public:
    int     DipSW_HIO;
private:
    QTimer  TM;
    int     AverageCounter;
    int     AddedAverage;
    int     SubFrameTriggerCounter;
    int     LastSubFrameTriggerCounter;

public:
    struct  TimingData  *RingBuffer;
    int     AllocCount;
    int     RPoint;
    int     WPoint;

    int     LightBoardCount;

public:
    struct	HioStruct	HIOData;

    QMutex                      AccessMutex;
    NPListPack<SocketClient>    ClientList;
    
public:
    explicit LEDControl16HioPrnRasPIMain(QWidget *parent = nullptr);
    ~LEDControl16HioPrnRasPIMain();

	void    DisconnectClient(SocketClient *s);
    void    WriteHIOTriggerPos(int DipSW);
    void    WriteHIO(int DipSW);
    void    ReadHIO(int DipSW);

    void    WriteHIO_R(int DipSW);
    void    ReadHIO_R(int DipSW);
    void    WriteHIOAllocation(int DipSW);

    void	GetHIODataFromWindow(void);
    void	SetHIODataToWindow(void);
    
    void    SendLightInfo(SocketClient *s);
    void    ReceiveData(struct HioFixedStruct &data);
private slots:
    void on_pushButtonSendFrameTrigger_clicked();
    void on_pushButtonSaveSetting_clicked();
    void on_toolButtonTestMode_clicked();
    void    SlotNewConnection();
    void    SlotTimeOut();
    void on_toolButtonAllocateIO_clicked();

    void on_pushButtonReqOutPulse_clicked();

    void on_pushButtonClearOutPulse_clicked();

private:
    Ui::LEDControl16HioPrnRasPIMain *ui;

    void    InitialSignal(void);

    bool    GetUART1Packet(unsigned char *Cmd,unsigned char Data[],int *Len ,int MaxBuffLen);
    bool    SendUART1Packet(unsigned char Cmd,unsigned char Data[],unsigned char DataLen);
};

#endif // LEDCONTROL16HIOPRNRASPIMAIN_H
