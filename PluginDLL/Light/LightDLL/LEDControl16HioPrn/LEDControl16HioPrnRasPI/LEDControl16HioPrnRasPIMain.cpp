#include "LEDControl16HioPrnRasPIMain.h"
#include "ui_LEDControl16HioPrnRasPIMain.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <wiringPi.h>
#include <QElapsedTimer>
#include <QFile>
#include "XTypeDef.h"
#include "XCriticalFunc.h"
#include "ShowLEDControl16HForm.h"
#include "LightDeviceStruct.h"
#include "HioTestModeDialog.h"
#include "AllocateIODialog.h"

SocketClient::SocketClient(LEDControl16HioPrnRasPIMain *parent ,QTcpSocket *s)
{
    Parent=parent;
    Socket=s;

    connect(s,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
    connect(s,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
}

SocketClient::~SocketClient(void)
{
}

bool	SocketClient::SendOut(BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short DataLen)
{
    BYTE    Header[4];

    Header[0]=DipSW;
    Header[1]=Cmd;
    Header[2]=DataLen&0xFF;
    Header[3]=DataLen>>8;
    if(Socket->write((const char *)Header,4)!=4){
        return false;
    }
    if(Socket->write((const char *)Data,DataLen)!=DataLen){
        return false;
    }
    return true;
}

void    SocketClient::SlotReadyRead()
{
    BYTE    DipSW;
    BYTE    Cmd;
    unsigned short    DataLen;
    BYTE    Header[4];

    if(Socket->read((char *)Header,4)!=4){
        QByteArray A=Socket->readAll();
        return;
    }
    DipSW=Header[0];
    Cmd  =Header[1];
    DataLen=(unsigned short)(Header[2] + (Header[3]<<8));

    if(Cmd=='A'){
        struct  HioFixedStruct  Data;
        if(DataLen==sizeof(Data)){
            if(Socket->read((char *)&Data,sizeof(Data))==sizeof(Data)){
                Parent->HIOData.HioFixedData=Data;
            }
        }
        else{
             QByteArray A=Socket->readAll();
        }
    }
    else if(Cmd=='B'){
        QByteArray Dummy=Socket->readAll();
        SendOut(-1,'B' ,(BYTE *)&Parent->HIOData.HioFixedData ,sizeof(Parent->HIOData.HioFixedData));
    }
    else if(Cmd=='C'){
        QByteArray Dummy=Socket->readAll();
        int Len;
        if(Parent->RPoint<=Parent->WPoint){
            Len=Parent->WPoint-Parent->RPoint;
        }
        else{
            Len=(Parent->WPoint+Parent->AllocCount)-Parent->RPoint;
        }
        if(Len>=255)
            Len=255;
        BYTE    Data[12*256+10];
        Data[0]=Len;
        int R=1;
        for(int i=0;i<Len;i++){
            memcpy(&Data[R],&Parent->RingBuffer[Parent->RPoint],sizeof(struct TimingData));
            Parent->RPoint++;
            if(Parent->RPoint>=Parent->AllocCount){
                Parent->RPoint=0;
            }
            R+=sizeof(struct TimingData);
        }
        SendOut(-1,'C' ,Data ,(unsigned short)R);
    }
    else if(Cmd=='V'){
        QByteArray Dummy=Socket->readAll();
        SendOut(-1,'V' ,(BYTE *)"LEDControl16HIOPrn",19);
    }
    else if(Cmd=='U'){
        QByteArray Dummy=Socket->readAll();
        Parent->SendLightInfo(this);
    }
    int LeftLen=Socket->bytesAvailable();
    if(LeftLen>0){
        QByteArray Dummy=Socket->readAll();
    }
}

void    SocketClient::SlotDisconnected()
{
    Parent->DisconnectClient(this);
}

//-------------------------------------------------------------------
static  QString     SettingHIOFileName="MiconHIOSetting.dat";
int		Error;


LEDControl16HioPrnRasPIMain::LEDControl16HioPrnRasPIMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LEDControl16HioPrnRasPIMain)
{
    ui->setupUi(this);
    if (wiringPiSetupGpio() < 0) {
       printf("GPIO ERROR\n");
       return;
   	}
    
    AllocCount  =100000;
    RingBuffer  =new struct  TimingData[AllocCount];
    RPoint      =0;
    WPoint      =-1;

    LightBoardCount =0;

    Server=new QTcpServer();
    if(!connect(Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()))){
    	Error++;
    }
    if(Server->listen(QHostAddress::Any,12777)==false){
    	Error++;
    }

    bool    Loaded=false;
	memset(&HIOData,0,sizeof(HIOData));
    QFile   File(SettingHIOFileName);
    if(File.open(QIODevice::ReadOnly)==true){
        if(HIOData.Load(&File)==true){
        	SetHIODataToWindow();
            Loaded=true;
        }
    }
	
	
   	InitialSignal();


    QList<QSerialPortInfo>  CommList=QSerialPortInfo::availablePorts();

    if(CommList.count()>=2){
        QString CommName=CommList[1].portName();
        Sio=new QSerialPort();
        Sio->setPortName(CommName);

        Sio->setBaudRate(QSerialPort::Baud19200);
        Sio->setDataBits(QSerialPort::Data8);
        Sio->setParity(QSerialPort::NoParity);
        Sio->setStopBits(QSerialPort::OneStop);
        Sio->setFlowControl(QSerialPort::NoFlowControl);

        if(Sio->open(QIODevice::ReadWrite)==true){
            unsigned char   Data[10];
            unsigned char   Cmd;
            int             Len;
            if(SendUART1Packet(0x80,Data,0)==true){
                if(GetUART1Packet(&Cmd,Data,&Len ,10)==true){
                    DipSW_HIO=Data[0];
                    ui->label_DipSW->setText(QString::number(DipSW_HIO,16));
                }
            }
        }
    }
    AverageCounter  =0;
    AddedAverage    =0;
    SubFrameTriggerCounter  =0;
    LastSubFrameTriggerCounter=0;
    WriteHIOAllocation(DipSW_HIO);
    if(Loaded==true){
        WriteHIO(DipSW_HIO);
    }

    ShowLEDControl16HForm   *F=new ShowLEDControl16HForm(this);
    F->show();

    on_toolButtonTestMode_clicked();

    TM.setInterval(100);
    TM.setSingleShot(false);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
    TM.start();
}

LEDControl16HioPrnRasPIMain::~LEDControl16HioPrnRasPIMain()
{
    delete ui;
    delete  []RingBuffer;
    RingBuffer=NULL;
}

void    LEDControl16HioPrnRasPIMain::InitialSignal(void)
{
    pinMode(2,INPUT);
    pinMode(3,OUTPUT);
    pinMode(27,OUTPUT);

    digitalWrite(3 , 0);

    digitalWrite(27, 1);
}

#define MaxReceivedMilisec  500
int ErrorPacketPos=0;

bool    LEDControl16HioPrnRasPIMain::GetUART1Packet(unsigned char *Cmd,unsigned char Data[],int *Len ,int MaxBuffLen)
{
    unsigned char   d;
    unsigned char   TBuff[100];
    unsigned char   Checksum=0;
    unsigned char   DataLen=0;
    int             i;
    int             Step=0;
    int             DPoint=0;

    if(Sio->isOpen()==false){
        return false;
    }

    while(Sio->waitForReadyRead(MaxReceivedMilisec)==true){
        int n=Sio->read((char *)TBuff,sizeof(TBuff));
        if(n==0){
            ErrorPacketPos=1;
            return false;
        }
        int np=0;
        while(n>0){
            if(Step==0){
                d=TBuff[np];
                if(d!=0x1E){
                    ErrorPacketPos=2;
                    return false;
                }
                Checksum=d;
                Step=1;
                n--;
                np++;
            }
            else if(Step==1){
                d=TBuff[np];
                *Cmd=d;
                Checksum^=d;
                Step=2;
                n--;
                np++;
            }
            else if(Step==2){
                d=TBuff[np];
                DataLen=d;
                Checksum^=d;
                Step=3;
                n--;
                np++;
            }
            else if(Step==3){
                if(DPoint<DataLen && DPoint<MaxBuffLen){
                    d=TBuff[np];
                    Data[DPoint]=d;
                    DPoint++;
                    Checksum^=d;
                    n--;
                    np++;
                }
                else{
                   Step=4;
                }
            }
            else if(Step==4){
                d=TBuff[np];
                if(Checksum!=d){
                    ErrorPacketPos=3;
                    return false;
                }
                *Len=DataLen;
                return true;
            }
        }
    }

    ErrorPacketPos=12;
    return false;
}

bool    LEDControl16HioPrnRasPIMain::SendUART1Packet(unsigned char Cmd,unsigned char Data[],unsigned char DataLen)
{
    unsigned char   d;
    unsigned char   Checksum;
    int             i;

    if(Sio->isOpen()==false){
        return false;
    }

    d=0x1E;
    Sio->write((const char *)&d,1);
    Checksum=d;

    d=Cmd;
    Sio->write((const char *)&d,1);
    Checksum^=d;

    d=DataLen;
    Sio->write((const char *)&d,1);
    Checksum^=d;

    for(i=0;i<DataLen;i++){
        d=Data[i];
        Checksum^=d;
    }
    if(DataLen>0){
        Sio->write((const char *)Data,DataLen);
    }
    Sio->write((const char *)&Checksum,1);
    Sio->waitForBytesWritten(1000);

    return true;
}

void	LEDControl16HioPrnRasPIMain::GetHIODataFromWindow(void)
{
    HIOData.HioFixedData.ConveyerLength		=ui->spinBoxConveyerLength	->value();
    HIOData.HioFixedData.GateOpenTerm		=ui->spinBoxGateOpenTerm	->value();
    HIOData.HioFixedData.MulInputA			=ui->spinBoxMulInputA		->value();
    HIOData.HioFixedData.MulInputB			=ui->spinBoxMulInputB		->value();
    HIOData.HioFixedData.MulInputC			=ui->spinBoxMulInputC		->value();
    HIOData.HioFixedData.MulInputD			=ui->spinBoxMulInputD		->value();
    HIOData.HioFixedData.TriggerFilterMinOFF=ui->spinBoxMinOFF			->value();
    HIOData.HioFixedData.TriggerFilterMinON	=ui->spinBoxMinON			->value();
    HIOData.HioFixedData.TriggerFilterWorkLen=ui->spinBoxWorkLen			->value();
    HIOData.HioFixedData.DelayFrameTriggerA	=ui->spinBoxDelayFrameTriggerA	->value();
    HIOData.HioFixedData.DelayFrameTriggerB	=ui->spinBoxDelayFrameTriggerB	->value();
    HIOData.HioFixedData.DelayFrameTriggerC	=ui->spinBoxDelayFrameTriggerC	->value();
    HIOData.HioFixedData.DelayFrameTriggerD	=ui->spinBoxDelayFrameTriggerD	->value();
    HIOData.HioFixedData.ResultAAcceptStart	=ui->spinBoxResultAAcceptStart	->value();
    HIOData.HioFixedData.ResultBAcceptStart	=ui->spinBoxResultBAcceptStart	->value();
    HIOData.HioFixedData.ResultCAcceptStart	=ui->spinBoxResultCAcceptStart	->value();
    HIOData.HioFixedData.ResultDAcceptStart	=ui->spinBoxResultDAcceptStart	->value();
    HIOData.HioFixedData.ResultACloseAccept	=ui->spinBoxResultACloseAccept	->value();
    HIOData.HioFixedData.ResultBCloseAccept	=ui->spinBoxResultBCloseAccept	->value();
    HIOData.HioFixedData.ResultCCloseAccept	=ui->spinBoxResultCCloseAccept	->value();
    HIOData.HioFixedData.ResultDCloseAccept	=ui->spinBoxResultDCloseAccept	->value();
    HIOData.HioFixedData.TriggerDelayParameter	=ui->doubleSpinBoxTriggerDelayParameter	->value();

    HIOData.HioFixedData.FlipFrameTriggerModeA  =ui->checkBoxFlipFrameTriggerA->isChecked();
    HIOData.HioFixedData.FlipFrameTriggerModeB  =ui->checkBoxFlipFrameTriggerB->isChecked();
    HIOData.HioFixedData.FlipFrameTriggerModeC  =ui->checkBoxFlipFrameTriggerC->isChecked();
    HIOData.HioFixedData.FlipFrameTriggerModeD  =ui->checkBoxFlipFrameTriggerD->isChecked();

    if(ui->toolButtonTestMode->isChecked()==true){
        HIOData.RealData.GOUT0  =ui->checkBoxoGOUT0 ->isChecked();
        HIOData.RealData.GOUT1  =ui->checkBoxoGOUT1 ->isChecked();
        HIOData.RealData.GOUT2  =ui->checkBoxoGOUT2 ->isChecked();
        HIOData.RealData.GOUT3  =ui->checkBoxoGOUT3 ->isChecked();
        HIOData.RealData.GOUT4  =ui->checkBoxoGOUT4 ->isChecked();
        HIOData.RealData.GOUT5  =ui->checkBoxoGOUT5 ->isChecked();
        HIOData.RealData.GOUT6  =ui->checkBoxoGOUT6 ->isChecked();
        HIOData.RealData.GOUT7  =ui->checkBoxoGOUT7 ->isChecked();

        HIOData.RealData.PIOAOUT0=ui->checkBoxPIOAOUT0->isChecked();
        HIOData.RealData.PIOAOUT1=ui->checkBoxPIOAOUT1->isChecked();
        HIOData.RealData.PIOAOUT2=ui->checkBoxPIOAOUT2->isChecked();
        HIOData.RealData.PIOAOUT3=ui->checkBoxPIOAOUT3->isChecked();

        HIOData.RealData.PIOBOUT0=ui->checkBoxPIOBOUT0->isChecked();
        HIOData.RealData.PIOBOUT1=ui->checkBoxPIOBOUT1->isChecked();
        HIOData.RealData.PIOBOUT2=ui->checkBoxPIOBOUT2->isChecked();
        HIOData.RealData.PIOBOUT3=ui->checkBoxPIOBOUT3->isChecked();

        HIOData.RealData.PIOCOUT0=ui->checkBoxPIOCOUT0->isChecked();
        HIOData.RealData.PIOCOUT1=ui->checkBoxPIOCOUT1->isChecked();
        HIOData.RealData.PIOCOUT2=ui->checkBoxPIOCOUT2->isChecked();
        HIOData.RealData.PIOCOUT3=ui->checkBoxPIOCOUT3->isChecked();

        HIOData.RealData.PIODOUT0=ui->checkBoxPIODOUT0->isChecked();
        HIOData.RealData.PIODOUT1=ui->checkBoxPIODOUT1->isChecked();
        HIOData.RealData.PIODOUT2=ui->checkBoxPIODOUT2->isChecked();
        HIOData.RealData.PIODOUT3=ui->checkBoxPIODOUT3->isChecked();
    }
}
void	LEDControl16HioPrnRasPIMain::SetHIODataToWindow(void)
{
    ui->spinBoxConveyerLength	->setValue(HIOData.HioFixedData.ConveyerLength	);
    ui->spinBoxGateOpenTerm		->setValue(HIOData.HioFixedData.GateOpenTerm	);
    ui->spinBoxMulInputA		->setValue(HIOData.HioFixedData.MulInputA		);
    ui->spinBoxMulInputB		->setValue(HIOData.HioFixedData.MulInputB		);
    ui->spinBoxMulInputC		->setValue(HIOData.HioFixedData.MulInputC		);
    ui->spinBoxMulInputD		->setValue(HIOData.HioFixedData.MulInputD		);
    ui->spinBoxMinOFF			->setValue(HIOData.HioFixedData.TriggerFilterMinOFF	);
    ui->spinBoxMinON			->setValue(HIOData.HioFixedData.TriggerFilterMinON	);
    ui->spinBoxWorkLen			->setValue(HIOData.HioFixedData.TriggerFilterWorkLen);
    ui->spinBoxDelayFrameTriggerA	->setValue(HIOData.HioFixedData.DelayFrameTriggerA);
    ui->spinBoxDelayFrameTriggerB	->setValue(HIOData.HioFixedData.DelayFrameTriggerB);
    ui->spinBoxDelayFrameTriggerC	->setValue(HIOData.HioFixedData.DelayFrameTriggerC);
    ui->spinBoxDelayFrameTriggerD	->setValue(HIOData.HioFixedData.DelayFrameTriggerD);
    ui->spinBoxResultAAcceptStart	->setValue(HIOData.HioFixedData.ResultAAcceptStart);
    ui->spinBoxResultBAcceptStart	->setValue(HIOData.HioFixedData.ResultBAcceptStart);
    ui->spinBoxResultCAcceptStart	->setValue(HIOData.HioFixedData.ResultCAcceptStart);
    ui->spinBoxResultDAcceptStart	->setValue(HIOData.HioFixedData.ResultDAcceptStart);
    ui->spinBoxResultACloseAccept	->setValue(HIOData.HioFixedData.ResultACloseAccept);
    ui->spinBoxResultBCloseAccept	->setValue(HIOData.HioFixedData.ResultBCloseAccept);
    ui->spinBoxResultCCloseAccept	->setValue(HIOData.HioFixedData.ResultCCloseAccept);
    ui->spinBoxResultDCloseAccept	->setValue(HIOData.HioFixedData.ResultDCloseAccept);
    ui->doubleSpinBoxTriggerDelayParameter	->setValue(HIOData.HioFixedData.TriggerDelayParameter);

    ui->checkBoxFlipFrameTriggerA->setChecked(HIOData.HioFixedData.FlipFrameTriggerModeA);
    ui->checkBoxFlipFrameTriggerB->setChecked(HIOData.HioFixedData.FlipFrameTriggerModeB);
    ui->checkBoxFlipFrameTriggerC->setChecked(HIOData.HioFixedData.FlipFrameTriggerModeC);
    ui->checkBoxFlipFrameTriggerD->setChecked(HIOData.HioFixedData.FlipFrameTriggerModeD);
}
void LEDControl16HioPrnRasPIMain::on_pushButtonSendFrameTrigger_clicked()
{
	GetHIODataFromWindow();
    WriteHIO(DipSW_HIO);
}

void LEDControl16HioPrnRasPIMain::on_pushButtonSaveSetting_clicked()
{
    GetHIODataFromWindow();

    QFile   File(SettingHIOFileName);
    if(File.open(QIODevice::WriteOnly)==true){
        if(HIOData.Save(&File)==false){
            return;
        }
    }
}

void    LEDControl16HioPrnRasPIMain::SlotNewConnection()
{

    QTcpSocket *s=Server->nextPendingConnection ();
    SocketClient    *Sock=new SocketClient(this ,s);
    AccessMutex.lock();
    ClientList.AppendList(Sock);
    AccessMutex.unlock();

    //ui->checkBoxConnecting->setChecked(true);
}


void    LEDControl16HioPrnRasPIMain::DisconnectClient(SocketClient *s)
{
    AccessMutex.lock();
    ClientList.RemoveList(s);
    AccessMutex.unlock();
    s->deleteLater();

    //ui->checkBoxConnecting->setChecked(false);
}

void    LEDControl16HioPrnRasPIMain::ReceiveData(struct HioFixedStruct &data)
{
    HIOData.HioFixedData=data;
    WriteHIO(DipSW_HIO);
}

void LEDControl16HioPrnRasPIMain::WriteHIOTriggerPos(int DipSW)
{
    unsigned char	Data[50];

    int	DelayFrameTriggerA=HIOData.HioFixedData.DelayFrameTriggerA - SubFrameTriggerCounter;
    int	DelayFrameTriggerB=HIOData.HioFixedData.DelayFrameTriggerB - SubFrameTriggerCounter;
    int	DelayFrameTriggerC=HIOData.HioFixedData.DelayFrameTriggerC - SubFrameTriggerCounter;
    int	DelayFrameTriggerD=HIOData.HioFixedData.DelayFrameTriggerD - SubFrameTriggerCounter;

    Data[0]=DelayFrameTriggerA;
    Data[1]=DelayFrameTriggerA>>8;
    Data[2]=DelayFrameTriggerB;
    Data[3]=DelayFrameTriggerB>>8;
    Data[4]=DelayFrameTriggerC;
    Data[5]=DelayFrameTriggerC>>8;
    Data[6]=DelayFrameTriggerD;
    Data[7]=DelayFrameTriggerD>>8;
    SendUART1Packet(0x40+0,Data,8);

}
void LEDControl16HioPrnRasPIMain::WriteHIO(int DipSW)
{
    unsigned char	Data[50];

    WriteHIOTriggerPos(DipSW);

    Data[0]=HIOData.HioFixedData.MulInputA;
    Data[1]=HIOData.HioFixedData.MulInputA>>8;
    Data[2]=HIOData.HioFixedData.MulInputB;
    Data[3]=HIOData.HioFixedData.MulInputB>>8;
    Data[4]=HIOData.HioFixedData.MulInputC;
    Data[5]=HIOData.HioFixedData.MulInputC>>8;
    Data[6]=HIOData.HioFixedData.MulInputD;
    Data[7]=HIOData.HioFixedData.MulInputD>>8;
    SendUART1Packet(0x40+1,Data,8);

    Data[0]=HIOData.HioFixedData.TriggerFilterMinOFF;
    Data[1]=HIOData.HioFixedData.TriggerFilterMinOFF>>8;
    Data[2]=HIOData.HioFixedData.TriggerFilterMinON;
    Data[3]=HIOData.HioFixedData.TriggerFilterMinON>>8;
    SendUART1Packet(0x40+2,Data,4);

    Data[0] =((HIOData.HioFixedData.FlipFrameTriggerModeA==true)?0x01:0)
            +((HIOData.HioFixedData.FlipFrameTriggerModeB==true)?0x02:0)
            +((HIOData.HioFixedData.FlipFrameTriggerModeC==true)?0x04:0)
            +((HIOData.HioFixedData.FlipFrameTriggerModeD==true)?0x08:0);
    SendUART1Packet(0x40+14,Data,1);

    Data[0]=HIOData.HioFixedData.TriggerFilterWorkLen;
    Data[1]=HIOData.HioFixedData.TriggerFilterWorkLen>>8;
    Data[2]=HIOData.HioFixedData.ConveyerLength;
    Data[3]=HIOData.HioFixedData.ConveyerLength>>8;
    Data[4]=HIOData.HioFixedData.GateOpenTerm;
    Data[5]=HIOData.HioFixedData.GateOpenTerm>>8;
    SendUART1Packet(0x40+7,Data,6);

    Data[0]=(HIOData.ResetCounter==true)?1:0;
    SendUART1Packet(0x40+8,Data,1);

    Data[0]=HIOData.HioFixedData.ResultAAcceptStart;
    Data[1]=HIOData.HioFixedData.ResultAAcceptStart>>8;
    Data[2]=HIOData.HioFixedData.ResultBAcceptStart;
    Data[3]=HIOData.HioFixedData.ResultBAcceptStart>>8;
    Data[4]=HIOData.HioFixedData.ResultCAcceptStart;
    Data[5]=HIOData.HioFixedData.ResultCAcceptStart>>8;
    Data[6]=HIOData.HioFixedData.ResultDAcceptStart;
    Data[7]=HIOData.HioFixedData.ResultDAcceptStart>>8;
    Data[8]=HIOData.HioFixedData.ResultACloseAccept;
    Data[9]=HIOData.HioFixedData.ResultACloseAccept>>8;
    Data[10]=HIOData.HioFixedData.ResultBCloseAccept;
    Data[11]=HIOData.HioFixedData.ResultBCloseAccept>>8;
    Data[12]=HIOData.HioFixedData.ResultCCloseAccept;
    Data[13]=HIOData.HioFixedData.ResultCCloseAccept>>8;
    Data[14]=HIOData.HioFixedData.ResultDCloseAccept;
    Data[15]=HIOData.HioFixedData.ResultDCloseAccept>>8;

    SendUART1Packet(0x81,Data,16);
}
void LEDControl16HioPrnRasPIMain::WriteHIOAllocation(int DipSW)
{
    unsigned char	Data[50];
    for(int i=0;i<8;i++){
        Data[i]=HIOData.AllocateGOut[i];
    }
    SendUART1Packet(0x40+6,Data,8);
}

void LEDControl16HioPrnRasPIMain::WriteHIO_R(int DipSW)
{
    unsigned char	Data[50];

    Data[0]=(HIOData.TestMode==true?0x01:0)
           +(HIOData.TestLEDReg==true?0x02:0);
    SendUART1Packet(0x40+3,Data,1);

    Data[0]= (HIOData.RealData.GOUT0==true?0x01:0)
            +(HIOData.RealData.GOUT1==true?0x02:0)
            +(HIOData.RealData.GOUT2==true?0x04:0)
            +(HIOData.RealData.GOUT3==true?0x08:0)
            +(HIOData.RealData.GOUT4==true?0x10:0)
            +(HIOData.RealData.GOUT5==true?0x20:0)
            +(HIOData.RealData.GOUT6==true?0x40:0)
            +(HIOData.RealData.GOUT7==true?0x80:0);
    SendUART1Packet(0x40+4,Data,1);

    Data[0]=(HIOData.TRGAOUT&0x0F) + (HIOData.TRGBOUT<<4);
    Data[1]=(HIOData.TRGCOUT&0x0F) + (HIOData.TRGDOUT<<4);
    SendUART1Packet(0x40+5,Data,2);


    Data[0]= (HIOData.RealData.PIOAOUT0==true?0x01:0)
            +(HIOData.RealData.PIOAOUT1==true?0x02:0)
            +(HIOData.RealData.PIOBOUT0==true?0x04:0)
            +(HIOData.RealData.PIOBOUT1==true?0x08:0)
            +(HIOData.RealData.PIOCOUT0==true?0x10:0)
            +(HIOData.RealData.PIOCOUT1==true?0x20:0)
            +(HIOData.RealData.PIODOUT0==true?0x40:0)
            +(HIOData.RealData.PIODOUT1==true?0x80:0);
    SendUART1Packet(0x40+15,Data,1);
}

void LEDControl16HioPrnRasPIMain::ReadHIO(int DipSW)
{
    unsigned char	Data[50];
    unsigned char   Cmd;
    int             DataLen;

    Data[0]=8;
    SendUART1Packet(0x20+0,Data,1);
    if(GetUART1Packet(&Cmd,Data,&DataLen ,16)==true){
        int	DelayFrameTriggerA=(int)Data[0]+(int)(Data[1]<<8);
        int	DelayFrameTriggerB=(int)Data[2]+(int)(Data[3]<<8);
        int	DelayFrameTriggerC=(int)Data[4]+(int)(Data[5]<<8);
        int	DelayFrameTriggerD=(int)Data[6]+(int)(Data[7]<<8);
        HIOData.HioFixedData.DelayFrameTriggerA= DelayFrameTriggerA- SubFrameTriggerCounter;
        HIOData.HioFixedData.DelayFrameTriggerB= DelayFrameTriggerB- SubFrameTriggerCounter;
        HIOData.HioFixedData.DelayFrameTriggerC= DelayFrameTriggerC- SubFrameTriggerCounter;
    }

    Data[0]=8;
    SendUART1Packet(0x20+1,Data,1);
    if(GetUART1Packet(&Cmd,Data,&DataLen ,16)==true){
        HIOData.HioFixedData.MulInputA=(unsigned long)Data[0]+(unsigned long)(Data[1]<<8);
        HIOData.HioFixedData.MulInputB=(unsigned long)Data[2]+(unsigned long)(Data[3]<<8);
        HIOData.HioFixedData.MulInputC=(unsigned long)Data[4]+(unsigned long)(Data[5]<<8);
        HIOData.HioFixedData.MulInputD=(unsigned long)Data[6]+(unsigned long)(Data[7]<<8);
    }

    Data[0]=4;
    SendUART1Packet(0x20+2,Data,1);
    if(GetUART1Packet(&Cmd,Data,&DataLen ,16)==true){
        HIOData.HioFixedData.TriggerFilterMinOFF=(unsigned long)Data[0]+(unsigned long)(Data[1]<<8);
        HIOData.HioFixedData.TriggerFilterMinON =(unsigned long)Data[2]+(unsigned long)(Data[3]<<8);
    }
}


void LEDControl16HioPrnRasPIMain::ReadHIO_R(int DipSW)
{
    unsigned char	Data[50];
    unsigned char   Cmd;
    int             DataLen;

    Data[0]=1;
    SendUART1Packet(0x20+4,Data,1);
    if(GetUART1Packet(&Cmd,Data,&DataLen ,16)==true){
        HIOData.RealData.GOUT0	=(Data[0]&0x01)!=0?true:false;
        HIOData.RealData.GOUT1	=(Data[0]&0x02)!=0?true:false;
        HIOData.RealData.GOUT2	=(Data[0]&0x04)!=0?true:false;
        HIOData.RealData.GOUT3	=(Data[0]&0x08)!=0?true:false;
        HIOData.RealData.GOUT4	=(Data[0]&0x10)!=0?true:false;
        HIOData.RealData.GOUT5	=(Data[0]&0x20)!=0?true:false;
        HIOData.RealData.GOUT6	=(Data[0]&0x40)!=0?true:false;
        HIOData.RealData.GOUT7	=(Data[0]&0x80)!=0?true:false;
    }

    Data[0]=2;
    SendUART1Packet(0x20+5,Data,1);
    if(GetUART1Packet(&Cmd,Data,&DataLen ,16)==true){
        HIOData.TRGAOUT         =Data[0]&0xF;
        HIOData.TRGBOUT         =(Data[0]>>4)&0x0F;
        HIOData.TRGCOUT         =Data[1]&0x0F;
        HIOData.TRGDOUT         =(Data[1]>>4)&0x0F;
    }

    Data[0]=2;
    SendUART1Packet(0x20+6,Data,1);
    if(GetUART1Packet(&Cmd,Data,&DataLen ,16)==true){
        HIOData.RealData.PIOAIN0=(Data[0]&0x01)!=0?true:false;
        HIOData.RealData.PIOAIN1=(Data[0]&0x02)!=0?true:false;
        HIOData.RealData.PIOAIN2=(Data[0]&0x04)!=0?true:false;
        HIOData.RealData.PIOAIN3=(Data[0]&0x08)!=0?true:false;
        HIOData.RealData.PIOBIN0=(Data[0]&0x10)!=0?true:false;
        HIOData.RealData.PIOBIN1=(Data[0]&0x20)!=0?true:false;
        HIOData.RealData.PIOBIN2=(Data[0]&0x40)!=0?true:false;
        HIOData.RealData.PIOBIN3=(Data[0]&0x80)!=0?true:false;
        HIOData.RealData.PIOCIN0=(Data[1]&0x01)!=0?true:false;
        HIOData.RealData.PIOCIN1=(Data[1]&0x02)!=0?true:false;
        HIOData.RealData.PIOCIN2=(Data[1]&0x04)!=0?true:false;
        HIOData.RealData.PIOCIN3=(Data[1]&0x08)!=0?true:false;
        HIOData.RealData.PIODIN0=(Data[1]&0x10)!=0?true:false;
        HIOData.RealData.PIODIN1=(Data[1]&0x20)!=0?true:false;
        HIOData.RealData.PIODIN2=(Data[1]&0x40)!=0?true:false;
        HIOData.RealData.PIODIN3=(Data[1]&0x80)!=0?true:false;
    }
    Data[0]=1;
    SendUART1Packet(0x20+10,Data,1);
    if(GetUART1Packet(&Cmd,Data,&DataLen ,16)==true){
        HIOData.RealData.TRGIN0	=(Data[0]&0x01)!=0?true:false;
        HIOData.RealData.TRGIN1	=(Data[0]&0x02)!=0?true:false;
        HIOData.RealData.TRGIN2	=(Data[0]&0x04)!=0?true:false;
        HIOData.RealData.TRGIN3	=(Data[0]&0x08)!=0?true:false;
        HIOData.RealData.GIN0	=(Data[0]&0x10)!=0?true:false;
        HIOData.RealData.GIN1	=(Data[0]&0x20)!=0?true:false;
        HIOData.RealData.GIN2	=(Data[0]&0x40)!=0?true:false;
        HIOData.RealData.GIN3	=(Data[0]&0x80)!=0?true:false;
    }
    Data[0]=6;
    SendUART1Packet(0x20+12,Data,1);
    if(GetUART1Packet(&Cmd,Data,&DataLen ,16)==true){
        HIOData.MotorPulseCounter
                        = ((unsigned long)Data[0])
                        +(((unsigned long)Data[1])<<8)
                        +(((unsigned long)Data[2])<<16);
        HIOData.MotorPulseCounter2
                        = ((unsigned long)Data[3])
                        +(((unsigned long)Data[4])<<8)
                        +(((unsigned long)Data[5])<<16);
    }

    Data[0]=12;
    SendUART1Packet(0x20+9,Data,1);
    if(GetUART1Packet(&Cmd,Data,&DataLen ,16)==true){
        HIOData.TotalCount
                        = ((unsigned long)Data[0])
                        +(((unsigned long)Data[1])<<8)
                        +(((unsigned long)Data[2])<<16);
        HIOData.OKCount
                        = ((unsigned long)Data[3])
                        +(((unsigned long)Data[4])<<8)
                        +(((unsigned long)Data[5])<<16);
        HIOData.NGCount
                        = ((unsigned long)Data[6])
                        +(((unsigned long)Data[7])<<8)
                        +(((unsigned long)Data[8])<<16);
        HIOData.TMCount
                        = ((unsigned long)Data[9])
                        +(((unsigned long)Data[10])<<8)
                        +(((unsigned long)Data[11])<<16);
    }
    //HIOData.RealData.OuterSW    =((Data[16]&0x02)!=0)?true:false;
    //HIOData.RealData.ExtDirect	=((Data[16]&0x04)!=0)?true:false;
}

void    LEDControl16HioPrnRasPIMain::SlotTimeOut()
{
    ReadHIO_R(DipSW_HIO);

    if(WPoint<0 || memcmp(&HIOData.RealData,&RingBuffer[WPoint].RealData,sizeof(HIOData.RealData))!=0){
        WPoint++;
        if(WPoint>=AllocCount){
            WPoint=0;
        }
        RingBuffer[WPoint].CurrentMiliSec =::GetComputerMiliSec();
        RingBuffer[WPoint].RealData=HIOData.RealData;
    }
    int n=ui->progressBar->value();
    n++;
    if(n>=ui->progressBar->maximum())
        n=0;
    ui->progressBar->setValue(n);
    
    ui->checkBoxGIN0 ->setChecked(HIOData.RealData.GIN0);
    ui->checkBoxGIN1 ->setChecked(HIOData.RealData.GIN1);
    ui->checkBoxGIN2 ->setChecked(HIOData.RealData.GIN2);
    ui->checkBoxGIN3 ->setChecked(HIOData.RealData.GIN3);
    
    ui->checkBoxTRGIN0 ->setChecked(HIOData.RealData.TRGIN0);
    ui->checkBoxTRGIN1 ->setChecked(HIOData.RealData.TRGIN1);
    ui->checkBoxTRGIN2 ->setChecked(HIOData.RealData.TRGIN2);
    ui->checkBoxTRGIN3 ->setChecked(HIOData.RealData.TRGIN3);
    
    ui->checkBoxPIOAIN0->setChecked(HIOData.RealData.PIOAIN0);
    ui->checkBoxPIOAIN1->setChecked(HIOData.RealData.PIOAIN1);
    ui->checkBoxPIOAIN2->setChecked(HIOData.RealData.PIOAIN2);
    ui->checkBoxPIOAIN3->setChecked(HIOData.RealData.PIOAIN3);
    
    ui->checkBoxPIOBIN0->setChecked(HIOData.RealData.PIOBIN0);
    ui->checkBoxPIOBIN1->setChecked(HIOData.RealData.PIOBIN1);
    ui->checkBoxPIOBIN2->setChecked(HIOData.RealData.PIOBIN2);
    ui->checkBoxPIOBIN3->setChecked(HIOData.RealData.PIOBIN3);
    
    ui->checkBoxPIOCIN0->setChecked(HIOData.RealData.PIOCIN0);
    ui->checkBoxPIOCIN1->setChecked(HIOData.RealData.PIOCIN1);
    ui->checkBoxPIOCIN2->setChecked(HIOData.RealData.PIOCIN2);
    ui->checkBoxPIOCIN3->setChecked(HIOData.RealData.PIOCIN3);
    
    ui->checkBoxPIODIN0->setChecked(HIOData.RealData.PIODIN0);
    ui->checkBoxPIODIN1->setChecked(HIOData.RealData.PIODIN1);
    ui->checkBoxPIODIN2->setChecked(HIOData.RealData.PIODIN2);
    ui->checkBoxPIODIN3->setChecked(HIOData.RealData.PIODIN3);

    if(ui->toolButtonTestMode->isChecked()==false){
        ui->checkBoxoGOUT0->setChecked(HIOData.RealData.GOUT0);
        ui->checkBoxoGOUT1->setChecked(HIOData.RealData.GOUT1);
        ui->checkBoxoGOUT2->setChecked(HIOData.RealData.GOUT2);
        ui->checkBoxoGOUT3->setChecked(HIOData.RealData.GOUT3);

        ui->checkBoxPIOAOUT0->setChecked(HIOData.RealData.PIOAOUT0);
        ui->checkBoxPIOAOUT1->setChecked(HIOData.RealData.PIOAOUT1);
        ui->checkBoxPIOAOUT2->setChecked(HIOData.RealData.PIOAOUT2);
        ui->checkBoxPIOAOUT3->setChecked(HIOData.RealData.PIOAOUT3);

        ui->checkBoxPIOBOUT0->setChecked(HIOData.RealData.PIOBOUT0);
        ui->checkBoxPIOBOUT1->setChecked(HIOData.RealData.PIOBOUT1);
        ui->checkBoxPIOBOUT2->setChecked(HIOData.RealData.PIOBOUT2);
        ui->checkBoxPIOBOUT3->setChecked(HIOData.RealData.PIOBOUT3);

        ui->checkBoxPIOCOUT0->setChecked(HIOData.RealData.PIOCOUT0);
        ui->checkBoxPIOCOUT1->setChecked(HIOData.RealData.PIOCOUT1);
        ui->checkBoxPIOCOUT2->setChecked(HIOData.RealData.PIOCOUT2);
        ui->checkBoxPIOCOUT3->setChecked(HIOData.RealData.PIOCOUT3);

        ui->checkBoxPIODOUT0->setChecked(HIOData.RealData.PIODOUT0);
        ui->checkBoxPIODOUT1->setChecked(HIOData.RealData.PIODOUT1);
        ui->checkBoxPIODOUT2->setChecked(HIOData.RealData.PIODOUT2);
        ui->checkBoxPIODOUT3->setChecked(HIOData.RealData.PIODOUT3);
    }
    else{
        GetHIODataFromWindow();
        WriteHIO_R(DipSW_HIO);
    }

    QString s=QString::number(HIOData.MotorPulseCounter);
    ui->labelMotorPulseCounter->setText(s);

    QString s2=QString::number(HIOData.MotorPulseCounter2);
    ui->labelMotorPulseCounter2->setText(s2);

    AddedAverage  +=HIOData.MotorPulseCounter;
    AverageCounter++;
    if(AverageCounter>=10){
        int AvrCounter=AddedAverage/AverageCounter;
        AddedAverage=0;
        AverageCounter=0;
        if(AvrCounter>100){
            SubFrameTriggerCounter=HIOData.HioFixedData.TriggerDelayParameter/AvrCounter;
            int dS=LastSubFrameTriggerCounter-SubFrameTriggerCounter;
            if(dS<-20 || 20<dS){
                WriteHIOTriggerPos(DipSW_HIO);
                LastSubFrameTriggerCounter=SubFrameTriggerCounter;
                ui->label_SubFrameTriggerCounter->setText(QString::number(SubFrameTriggerCounter));
            }
        }
    }
}
void    LEDControl16HioPrnRasPIMain::SendLightInfo(SocketClient *s)
{
    BYTE    Data[100];
    Data[0]=LightBoardCount;
    s->SendOut(-1,'U',Data ,1);
}

void LEDControl16HioPrnRasPIMain::on_toolButtonTestMode_clicked()
{
    HIOData.TestMode    =ui->toolButtonTestMode->isChecked();

    if(HIOData.TestMode==true){
        ui->widgetTestMode->setEnabled(true);
    }
    else{
        ui->widgetTestMode->setEnabled(false);
    }
    WriteHIO_R(DipSW_HIO);
}

void LEDControl16HioPrnRasPIMain::on_toolButtonAllocateIO_clicked()
{
    AllocateIODialog    D(this);
    if(D.exec()==true){
        WriteHIOAllocation(DipSW_HIO);
    }
}

void LEDControl16HioPrnRasPIMain::on_pushButtonReqOutPulse_clicked()
{
    unsigned char	Data[50];
    unsigned char   Cmd;
    int             DataLen;

    Data[0]=12;
    SendUART1Packet(0x20+8,Data,1);
    if(GetUART1Packet(&Cmd,Data,&DataLen ,16)==true){
        unsigned long	OutPulseCountAOK=(unsigned long)Data[0]+(unsigned long)(Data[1]<<8)+(((unsigned long)Data[2])<<16);
        unsigned long	OutPulseCountANG=(unsigned long)Data[3]+(unsigned long)(Data[4]<<8)+(((unsigned long)Data[5])<<16);
        unsigned long	OutPulseCountBOK=(unsigned long)Data[6]+(unsigned long)(Data[7]<<8)+(((unsigned long)Data[8])<<16);
        unsigned long	OutPulseCountBNG=(unsigned long)Data[9]+(unsigned long)(Data[10]<<8)+(((unsigned long)Data[11])<<16);
        ui->spinBoxOutPulseAOK->setValue(OutPulseCountAOK);
        ui->spinBoxOutPulseANG->setValue(OutPulseCountANG);
        ui->spinBoxOutPulseBOK->setValue(OutPulseCountBOK);
        ui->spinBoxOutPulseBNG->setValue(OutPulseCountBNG);
    }
}

void LEDControl16HioPrnRasPIMain::on_pushButtonClearOutPulse_clicked()
{
    unsigned char	Data[50];
    Data[0]= 1;
    SendUART1Packet(0x40+8,Data,1);
    Data[0]= 0;
    SendUART1Packet(0x40+8,Data,1);
}
