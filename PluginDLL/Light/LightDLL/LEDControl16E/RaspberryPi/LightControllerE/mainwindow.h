#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include "LightDeviceStruct.h"
#include "NListRPi.h"
#include "DeviceStruct.h"

namespace Ui {
class MainWindow;
}

class   MainWindow;
class   QTcpSocket;

struct  LightPacketData
{
    unsigned char   BoardNo;
    unsigned char   PatternNo;
    struct	LightBoard::LightPattern    PatternData;
};


class   SocketClient : public QObject ,public NPList<SocketClient>
{
    Q_OBJECT

    MainWindow  *Parent;
    struct  LightPacketData    Data;
    QTcpSocket              *Socket;
public:
    SocketClient(MainWindow *parent ,QTcpSocket *s);
    ~SocketClient(void);

private slots:
    void    SlotReadyRead();
    void    SlotDisconnected();
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTcpServer  Server;
    struct	LightBoard	BoardData[16];
    struct	EOIStruct	EIOData;
    int     DipSW_EIO;
    int     DipSW_E;
public:
    int BoardCount;
    int DipSWTable[16]; //Index=Borad number

public:
    QMutex                      AccessMutex;
    NPListPack<SocketClient>    ClientList;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void    DisconnectClient(SocketClient *s);
    void    ReceiveData(struct  LightPacketData &data);
    void    InitialSignal(void);
    void    WriteEIO(int DipSW);
    int     ReadBOardID(int DipSW);
    void    WriteEForBit(int DipSW ,int Brd);
    void    WriteELightData(int DipSW ,int Brd ,int PatternNoW);    //Execute after WriteEForBit
    void    WriteEOnOffData(int DipSW ,int brd ,int PatternNoW);    //Execute after WriteEForBit
    int     ReadEForBit(int DipSW ,int Brd);	//Return Motor counter
    bool    ReadELightData(int DipSW ,int brd ,int PatternNo);

    void    TestWriteE(int DipSW);
    void	AllON(bool ON);

    void    ShowCurrentData(void);
private:
    Ui::MainWindow *ui;

    void WriteRegister(int DipSW ,int Data[],int DataLen);
    void WriteRegister(int Data);
    void ReadRegister4Bit(int DipSW ,int Data[],int DataLen);
    void ReadRegister4Bit(int &Data);
    void DummyClock(void);
    int GetDipSW_InE(int boardnumber);
private slots:
    void    SlotNewConnection();
    void on_comboBoxBoard_currentIndexChanged(int index);
    void on_spinBoxPattern_valueChanged(int arg1);
};

#endif // MAINWINDOW_H
