/*
 * Copyright (C) 2020
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CONTROLFIOFORM_H
#define CONTROLFIOFORM_H

#include <QWidget>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include <QTimer>
#include "NListRPi.h"
#include "DeviceStruct.h"

namespace Ui {
class ControlFIOForm;
}
class   ControlFIOForm;
class   QTcpSocket;

class   IOSocketClient : public QObject ,public NPList<IOSocketClient>
{
    Q_OBJECT

    ControlFIOForm  *Parent;
    //CamTriggerStruct    Data;
     QTcpSocket         *Socket;
public:
    IOSocketClient(ControlFIOForm *parent ,QTcpSocket *s);
    ~IOSocketClient(void);

private slots:
    void    SlotReadyRead();
    void    SlotDisconnected();
};

class ControlFIOForm : public QWidget
{
    Q_OBJECT
    QTcpServer  Server;
    struct	EOIStruct	EIOData;
    int     DipSW_EIO;
    QTimer  TM;
    int     AverageCounter;
    int     AddedAverage;
    int     SubFrameTriggerCounter;
public:
    QMutex                      AccessMutex;
    NPListPack<IOSocketClient>    ClientList;

    explicit ControlFIOForm(QWidget *parent = 0);
    ~ControlFIOForm();

    void    DisconnectClient(IOSocketClient *s);
    //void    ReceiveData(CamTriggerStruct &data);

    void    WriteInitial(void);
    void    WriteEIO(int DipSW);
    void    ReadEIO(int DipSW);
    int     ReadBoardID(int DipSW);
    void    WriteEForBit(int DipSW ,int Brd);
    void    WriteELightData(int DipSW ,int Brd ,int PatternNoW);    //Execute after WriteEForBit
    void    WriteEOnOffData(int DipSW ,int brd ,int PatternNoW);    //Execute after WriteEForBit
    int     ReadEForBit(int DipSW ,int Brd);	//Return Motor counter
    bool    ReadELightData(int DipSW ,int brd ,int PatternNo);

    void    TestWriteE(int DipSW);

    void    ReadInput(int DipSW ,unsigned int &Data);
    void    ReadMotorCounter(int DipSW,unsigned int &Data);

private slots:
    void    SlotNewConnection();
    void on_pushButtonSendFrameTrigger_clicked();
    void on_pushButtonSaveSetting_clicked();
    void on_pushButtonReset_clicked();
    void on_toolButtonFlapOK_clicked();
    void on_toolButtonFlapNG_clicked();
    void on_pushButtonReceiveEIO_clicked();
    void on_toolButtonTopOK_clicked();
    void on_toolButtonTopNG_clicked();
    void on_toolButtonBottomOK_clicked();
    void on_toolButtonBottomNG_clicked();

    void    SlotTimeOut();

private:
    Ui::ControlFIOForm *ui;

    void WriteRegister(int DipSW ,int Data[],int DataLen);
    void WriteRegister(int Data);
    void ReadRegister4Bit(int DipSW ,int Data[],int DataLen);
    void ReadRegister4Bit(int &Data);
    void DummyClock(void);
};

#endif // CONTROLFIOFORM_H