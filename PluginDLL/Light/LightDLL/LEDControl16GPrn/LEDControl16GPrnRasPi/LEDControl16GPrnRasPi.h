#ifndef LEDCONTROL16GPRNRASPI_H
#define LEDCONTROL16GPRNRASPI_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include <QThread>
#include <QTimer>
#include "NListRPi.h"
#include "DeviceStruct.h"
#include "XGioDefineSignal.h"

namespace Ui {
class LEDControl16GPrnRasPi;
}
class LEDControl16GPrnRasPi;
class TimingChartForm;
class ShowLEDControl16GForm;

class   SocketClient : public QObject ,public NPList<SocketClient>
{
    Q_OBJECT

    LEDControl16GPrnRasPi  *Parent;
     QTcpSocket         *Socket;
public:
    SocketClient(LEDControl16GPrnRasPi *parent ,QTcpSocket *s);
    ~SocketClient(void);

    bool	SendOut(BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short DataLen);

private slots:
    void    SlotReadyRead();
    void    SlotDisconnected();
};

class ThreadIORead : public QThread
{
    LEDControl16GPrnRasPi   *PiParent;
public:
    volatile    bool    Terminated;
    ThreadIORead(LEDControl16GPrnRasPi *p,QObject *parent);

    virtual void    run()   override;
};

class LEDControl16GPrnRasPi : public QMainWindow
{
    Q_OBJECT
    QTcpServer  Server;

    QTimer  TM;
    int     LastSubFrameTriggerCounter;
    int     AverageCounter;
    qint64  AddedAverage;
    int     SubFrameTriggerCounter;
    int     SubResultOutCounter16;
    TimingChartForm     *TimingForm;
    ShowLEDControl16GForm   *LightF;
public:
    int     DipSW_GIO;
    struct  TimingData  *RingBuffer;
    int     AllocCount;
    int     WPoint;
    int     LastWPoint;
    int     PointCount;

    int     LightBoardCount;

public:
    QMutex                      IOMutex;
    struct	GioStruct	GIOData;
    struct GioPortDefinition	GIOPortName;

    QMutex                      AccessMutex;
    NPListPack<SocketClient>    ClientList;

    ThreadIORead    *ThreadIOReadInst;
    
    explicit LEDControl16GPrnRasPi(QWidget *parent = nullptr);
    ~LEDControl16GPrnRasPi();

    void    DisconnectClient(SocketClient *s);
    void    ReceiveData(struct GioFixedStruct &data);

    void    WriteInitial(void);
    void    WriteGIO(int DipSW);
    void    WriteGIO(void);
    void    ReadGIO(int DipSW);
    void    WriteGForBit(int DipSW ,int Brd);
    int     ReadGForBit(int DipSW ,int Brd);	//Return Motor counter

    void    TestWriteE(int DipSW);

    void    SendLightInfo(SocketClient *s);
    void	GetGIODataFromWindow(void);
    void	SetGIODataToWindow(void);
    
    struct  TimingData	*FindTimingAhead(DWORD t);
	struct  TimingData	*GetTiming(int point);
    int     GetFirstTimingPoint(void);
    int     GetTimingCount(void);
    void    ClearTiming(void);
    void    ReadIOUpdate();

private slots:
    void on_pushButtonSendFrameTrigger_clicked();
    void on_pushButtonSaveSetting_clicked();
    void    SlotNewConnection();
    void    SlotTimeOut();
    void on_toolButtonTestMode_clicked();

    void on_pushButtonResetCounter_clicked();

private:
    Ui::LEDControl16GPrnRasPi *ui;
    
    void InitialSignal(void);
    
};

#endif // LEDCONTROL16GPRNRASPI_H
