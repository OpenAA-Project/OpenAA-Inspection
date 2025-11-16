#include "IOForm.h"
#include "ui_IOForm.h"
#include "YasukawaMotoCom.h"
#include "XMotorCommon.h"
#include "XGeneralFunc.h"
#include <QLocalSocket>
#include <QFile>

IOForm::IOForm(YasukawaMotoCom *P,QWidget *parent) :
    QWidget(parent),Parent(P),
    ui(new Ui::IOForm)
{
    ui->setupUi(this);
    ui->tableWidget     ->setRowCount(64);
    ui->tableWidgetByte ->setRowCount(64);

    Socket=NULL;
    connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
    Server.listen(/**/"Robot");
}

IOForm::~IOForm()
{
    delete ui;
}
void    IOForm::SlotNewConnection()
{
    Socket=Server.nextPendingConnection();
    connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
}

void    IOForm::SlotReadyRead()
{
    QByteArray  Data;
    Data=Socket->readAll();

    QBuffer   File(&Data);
    File.open(QIODevice::ReadWrite);
    int XPos,YPos,ZPos,Dx,Dy;
    ::Load(&File,XPos);
    ::Load(&File,YPos);
    ::Load(&File,ZPos);
    ::Load(&File,Dx);
    ::Load(&File,Dy);

    unsigned char DimData[32];
    DimData[0]=abs(XPos);
    DimData[1]=abs(YPos);
    DimData[2]=abs(ZPos);
    DimData[3]=abs(Dx);
    DimData[4]=abs(Dy);
    DimData[5]=  ((XPos>=0)?0:0x01)
                +((YPos>=0)?0:0x02)
                +((ZPos>=0)?0:0x04)
                +((Dx>=0)?0:0x08)
                +((Dy>=0)?0:0x10);

    WriteData(DimData);
}

void IOForm::on_pushButtonWrite_clicked()
{
    int Data[6];
    for(int row=0;row<6;row++){
        QString s=GetDataToTable(ui->tableWidget, 0, row);
        Data[row]=s.toInt();
    }
    WriteData(Data);
}

void IOForm::WriteData(int Data[6])
{
    short   MachineID=Parent->MachineID;
    unsigned char value[32];
    memset(value,0,sizeof(value));
    for(int row=0;row<6;row++){
        int d=Data[row];
        value[row*4+0]=(d>>0)&0xFF;
        value[row*4+1]=(d>>8)&0xFF;
        value[row*4+2]=(d>>16)&0xFF;
        value[row*4+3]=(d>>24)&0xFF;
    }
    if(MotoWriteIO(MachineID ,0 ,value)==true){
    }
}
void IOForm::WriteData(unsigned char Data[32])
{
    short   MachineID=Parent->MachineID;
    if(MotoWriteIO(MachineID ,0 ,Data)==true){
    }
}

void IOForm::on_pushButtonRead_clicked()
{
    short   MachineID=Parent->MachineID;
    unsigned char value[64];
    if(MotoReadIO(MachineID ,0 ,value)==true){
        for(int row=0;row<6;row++){
            int d=(value[row*4+0]<<0)
                + (value[row*4+1]<<8)
                + (value[row*4+2]<<16)
                + (value[row*4+3]<<24);
            ::SetDataToTable(ui->tableWidget, 0, row, QString::number(d),Qt::ItemIsEditable);
        }
    }
}

void IOForm::on_pushButtonWriteByte_clicked()
{
    unsigned char Data[32];
    for(int row=0;row<32;row++){
        QString s=GetDataToTable(ui->tableWidgetByte, 0, row);
        Data[row]=s.toInt();
    }
    WriteData(Data);
}

void IOForm::on_pushButtonReadByte_clicked()
{
    short   MachineID=Parent->MachineID;
    unsigned char value[64];
    if(MotoReadIO(MachineID ,0 ,value)==true){
        for(int row=0;row<32;row++){
            ::SetDataToTable(ui->tableWidgetByte, 0, row, QString::number(value[row]),Qt::ItemIsEditable);
        }
    }
}

