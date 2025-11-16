#ifndef LEDCONTROL16JioPRNRASPIMAIN_H
#define LEDCONTROL16JioPRNRASPIMAIN_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QMutex>
#include <QTimer>
#include "NListRPi.h"
#include "DeviceStruct.h"
#include "XJioDefineSignal.h"

namespace Ui {
class LEDControl16JioPrnRasPIMain;
}
class LEDControl16JioPrnRasPIMain;
class QSerialPort;
class TimingChartForm;

class   SocketClient : public QObject ,public NPList<SocketClient>
{
    Q_OBJECT

    LEDControl16JioPrnRasPIMain  *Parent;
     QTcpSocket         *Socket;
public:
    SocketClient(LEDControl16JioPrnRasPIMain *parent ,QTcpSocket *s);
    ~SocketClient(void);

    bool	SendOut(BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short DataLen);

private slots:
    void    SlotReadyRead();
    void    SlotDisconnected();
};

#define MaxSize_SPIBuff 256

class   ThreadPollingComm : public QThread
{
    Q_OBJECT

    QMutex  AccessComm;
    LEDControl16JioPrnRasPIMain *Parent;
    unsigned char   SPIBuff[MaxSize_SPIBuff];
public:
    volatile    bool    Terminate;
    volatile    unsigned    int     Counter;

    ThreadPollingComm(LEDControl16JioPrnRasPIMain *p,QObject *parent);

    virtual void run()  override;

    void    Lock(void);
    void    Unlock(void);

signals:
    void    SignalReceiveSPI(int CountCh,unsigned char ChBuff[]);
};

class LEDControl16JioPrnRasPIMain : public QMainWindow
{
    Q_OBJECT
    QSerialPort     *Sio;
    
    int SPIChannel;
    ThreadPollingComm   RunPolling;
    QMutex              MutexPolling;
    QTcpServer  *Server;
public:
    int     DipSW_Jio;
private:
    QTimer  TM;
    int     AverageCounter;
    int     AddedAverage;
    int     SubFrameTriggerCounter;
    int     LastSubFrameTriggerCounter;
    TimingChartForm     *TimingForm;
public:
    struct  TimingData  *RingBuffer;
    int     AllocCount;
    int     RPoint;
    int     WPoint;
    int     LastWPoint;

    int     LightBoardCount;
    unsigned    int     LastPollingCounter;
    DWORD       LastComputerTime;
public:
    struct	JioStruct	JioData;
    struct JioPortDefinition	JIOPortName;
    QMutex                      AccessMutex;
    NPListPack<SocketClient>    ClientList;
    int     PointCount;
public:
    explicit LEDControl16JioPrnRasPIMain(QWidget *parent = nullptr);
    ~LEDControl16JioPrnRasPIMain();

	void    DisconnectClient(SocketClient *s);
    void    WriteJioTriggerPos(int DipSW);
    void    WriteJio(int DipSW);
    void    ReadJio(int DipSW);

    void    WriteJio_R(int DipSW);
    void    ReadJio_R(int DipSW);
    void    WriteJioAllocation(int DipSW);

    void	GetJioDataFromWindow(void);
    void	SetJioDataToWindow(void);
    
    void    SendLightInfo(SocketClient *s);
    void    ReceiveData(struct JioFixedStruct &data);

    int     GetSPIChannel(void) {   return SPIChannel;  }
    int     ReadLightBoardID(int n);
    int     ReadLightCurrentValue(int BrdNo,int LineNo);
    void    SendLightTargetValue(int BrdNo,int LineNo,int TargetValue);
    void    SendLightBoardON(int BrdNo,bool LightON);
    void    SendLightTestLEDON(int BrdNo,bool LightON);

    void    ReadIOUpdate();
    struct  TimingData	*FindTimingAhead(DWORD t);
    struct  TimingData	*GetTiming(int point);
    int     GetFirstTimingPoint(void);
    int     GetTimingCount(void);
    void    ClearTiming(void);

private slots:
    void on_pushButtonSendFrameTrigger_clicked();
    void on_pushButtonSaveSetting_clicked();
    void on_toolButtonTestMode_clicked();
    void    SlotNewConnection();
    void    SlotTimeOut();
    void on_toolButtonAllocateIO_clicked();
    void on_pushButtonReqOutPulse_clicked();
    void on_pushButtonClearOutPulse_clicked();
    void    SlotReceiveSPI(int CountCh,unsigned char ChBuff[]);
private:
    Ui::LEDControl16JioPrnRasPIMain *ui;

    void    InitialSignal(void);

    //bool    GetUART1Packet(unsigned char *Cmd,unsigned char Data[],int *Len ,int MaxBuffLen);
    //bool    SendUART1Packet(unsigned char Cmd,unsigned char Data[],unsigned char DataLen);
};

#endif // LEDCONTROL16JioPRNRASPIMAIN_H
