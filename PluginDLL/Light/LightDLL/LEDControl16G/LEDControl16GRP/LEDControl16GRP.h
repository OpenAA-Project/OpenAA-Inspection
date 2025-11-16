#ifndef LEDCONTROL16GRP_H
#define LEDCONTROL16GRP_H

#include <QMainWindow>
#include <QIODevice>
#include "LightDeviceStruct.h"
#include <QMutex>
#include "NListRPi.h"
#include "XCommFromPC.h"
#include "DeviceStruct.h"

namespace Ui {
class LEDControl16GRP;
}

class   LEDControl16GRP;
class   QTcpSocket;

#define MaxDipSW    16

class   SocketClient : public QObject ,public NPList<SocketClient>
{
    Q_OBJECT

    LEDControl16GRP *Parent;
    QTcpSocket      *Socket;
public:
    SocketClient(LEDControl16GRP *parent ,QTcpSocket *s);
    ~SocketClient(void);

private slots:
    void    SlotReadyRead();
    void    SlotDisconnected();
};

class LEDControl16GRP : public QMainWindow
{
    Q_OBJECT

    TriggerServer  Server;
public:
    LightBoard  BoardData[MaxBoardCount];
    int         BoardCount;

    struct	EOIStruct	EIOData;
    int     DipSW_EIO;

    QMutex                      AccessMutex;
    NPListPack<SocketClient>    ClientList;
    
    char	BoardName[33];
    
public:
    explicit LEDControl16GRP(QWidget *parent = nullptr);
    ~LEDControl16GRP();

    void    DisconnectClient(SocketClient *s);
    //void    ReceiveData(CamTriggerStruct &data);
    void    InitialSignal(void);
    void    WriteInitial(void);
    void    WriteEIO(int DipSW);
    void    WriteEIO();
    void    ReadEIO(int DipSW);
    void	ShowEIO(void);

    int     ReadBOardID(int DipSW);

	void	ReqBoardName(void);
	void	SetTestLED(int DipSW ,bool b);
	void	SetAllOn(int DipSW ,bool OnMode);
	void	SetAllCurrentPattern(int DipSW ,int PatternNo);
	
private slots:
    void    SlotNewConnection();
    void on_listWidgetDipSW_currentRowChanged(int currentRow);
    void on_spinBoxPatternNo_valueChanged(int arg1);
    void on_listWidgetDipSW_doubleClicked(const QModelIndex &index);
    void on_toolButtonAllON_clicked();
    void on_toolButtonSave_clicked();
    void on_pushButtonUpdate_clicked();

private:
    Ui::LEDControl16GRP *ui;

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

};

#endif // LEDCONTROL16GRP_H
