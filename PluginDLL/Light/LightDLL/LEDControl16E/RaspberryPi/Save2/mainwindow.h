#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTcpServer>
//#include <QTcpSocket>
#include <QMutex>
#include "LightDeviceStruct.h"
#include "NListRPi.h"
#include "DeviceStruct.h"
#include "XCommFromPC.h"

namespace Ui {
class MainWindow;
}

class   MainWindow;
class   QTcpSocket;

class   SocketClient : public QObject ,public NPList<SocketClient>
{
    Q_OBJECT

    MainWindow  *Parent;
    //CamTriggerStruct    Data;
     //QTcpSocket         *Socket;
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
    //QTcpServer  Server;
    TriggerServer   Server;
public:
    struct	LightBoard	BoardData[16];
    struct	EOIStruct	EIOData;
    int     DipSW_EIO;
public:
    QMutex                      AccessMutex;
    NPListPack<SocketClient>    ClientList;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void    DisconnectClient(SocketClient *s);
    //void    ReceiveData(CamTriggerStruct &data);
    void    InitialSignal(void);
    void    WriteInitial(void);
    void    WriteEIO(int DipSW);
    void    WriteEIO();
    void    ReadEIO(int DipSW);
    void	ShowEIO(void);
    
    int     ReadBOardID(int DipSW);
    void    WriteEForBit(int DipSW ,int Brd);
    void    WriteELightData(int DipSW ,int Brd ,int PatternNoW);    //Execute after WriteEForBit
    void    WriteEOnOffData(int DipSW ,int brd ,int PatternNoW);    //Execute after WriteEForBit
    int     ReadEForBit(int DipSW ,int Brd);	//Return Motor counter
    bool    ReadELightData(int DipSW ,int brd ,int PatternNo);

    void    TestWriteE(int DipSW);
private:
    Ui::MainWindow *ui;

    void WriteRegister(int DipSW ,int Data[],int DataLen);
    void WriteRegister(int Data);
    void ReadRegister4Bit(int DipSW ,int Data[],int DataLen);
    void ReadRegister4Bit(int &Data);
    void DummyClock(void);
private slots:
    void    SlotNewConnection();
    void on_pushButtonSendEIO_clicked();
    void on_pushButtonReceiveEIO_clicked();
    void on_pushButtonSendFrameTrigger_clicked();
    void on_pushButtonSaveSetting_clicked();
    void on_pushButtonReset_clicked();

    void on_toolButtonFlapTopOK_clicked();
    void on_toolButtonFlapTopNG_clicked();
    void on_toolButtonFlapBottomOK_clicked();
    void on_toolButtonFlapBottomNG_clicked();
    void on_toolButtonFlapSwordOK_clicked();
    void on_toolButtonFlapSwordNG_clicked();
};

#endif // MAINWINDOW_H
