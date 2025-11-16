#ifndef CONTROLLightGFORM_H
#define CONTROLLightGFORM_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include "LightDeviceStruct.h"
#include "NListRPi.h"

namespace Ui {
class ControlLightGForm;
}


class   ControlLightGForm;
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

    ControlLightGForm  *Parent;
    struct  LightPacketData    Data;
    QTcpSocket              *Socket;
public:
    SocketClient(ControlLightGForm *parent ,QTcpSocket *s);
    ~SocketClient(void);

private slots:
    void    SlotReadyRead();
    void    SlotDisconnected();
};

class ControlLightGForm : public QWidget
{
    Q_OBJECT
    
    QTcpServer  *Server;
    struct	LightBoard	*BoardData;
    int     DipSW_E;
public:
    int BoardCount;
    int DipSWTable[16]; //Index=Borad number

public:
    //QMutex                      AccessMutex;
    NPListPack<SocketClient>    ClientList;

    explicit ControlLightGForm(QWidget *parent = 0);
    ~ControlLightGForm();

    void    DisconnectClient(SocketClient *s);
    void    ReceiveData(struct  LightPacketData &data);

    void    WriteEIO(int DipSW);
    int     ReadBoardID(int DipSW);
    void    WriteEForBit(int DipSW ,int Brd);
    void    WriteELightData(int DipSW ,int Brd ,int PatternNoW);    //Execute after WriteEForBit
    void    WriteEOnOffData(int DipSW ,int brd ,int PatternNoW);    //Execute after WriteEForBit
    int     ReadEForBit(int DipSW ,int Brd);	//Return Motor counter
    bool    ReadELightData(int DipSW ,int brd ,int PatternNo);

    void    TestWriteE(int DipSW);
    void	AllON(bool ON);

    void    ShowCurrentData(void);

private slots:
    void on_comboBoxBoard_currentIndexChanged(int index);
    void on_spinBoxPattern_valueChanged(int arg1);
    void    SlotNewConnection();

private:
    Ui::ControlLightGForm *ui;

    void WriteRegister(int DipSW ,int Data[],int DataLen);
    void WriteRegister(int Data);
    void ReadRegister4Bit(int DipSW ,int Data[],int DataLen);
    void ReadRegister4Bit(int &Data);
    void DummyClock(void);
    int GetDipSW_InE(int boardnumber);
};

#endif // CONTROLLightGFORM_H
