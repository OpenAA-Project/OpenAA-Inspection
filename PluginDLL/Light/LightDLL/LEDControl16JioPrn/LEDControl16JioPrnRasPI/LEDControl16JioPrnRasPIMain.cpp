#include "LEDControl16JioPrnRasPIMain.h"
#include "ui_LEDControl16JioPrnRasPIMain.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <QElapsedTimer>
#include <QFile>
#include "XTypeDef.h"
#include "XCriticalFunc.h"
#include "ShowLEDControl16JForm.h"
#include "LightDeviceStruct.h"
#include "JioTestModeDialog.h"
#include "AllocateIODialog.h"
#include <QMessageBox>
#include "TimingChartForm.h"


SocketClient::SocketClient(LEDControl16JioPrnRasPIMain *parent ,QTcpSocket *s)
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
        struct  JioFixedStruct  Data;
        if(DataLen==sizeof(Data)){
            if(Socket->read((char *)&Data,sizeof(Data))==sizeof(Data)){
                Parent->JioData.JioFixedData=Data;
            }
        }
        else{
             QByteArray A=Socket->readAll();
        }
    }
    else if(Cmd=='B'){
        QByteArray Dummy=Socket->readAll();
        SendOut(-1,'B' ,(BYTE *)&Parent->JioData.JioFixedData ,sizeof(Parent->JioData.JioFixedData));
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
        SendOut(-1,'V' ,(BYTE *)"LEDControl16JioPrn",19);
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

//=====================================================================
ThreadPollingComm::ThreadPollingComm(LEDControl16JioPrnRasPIMain *p,QObject *parent)
    :QThread(parent),Parent(p)
{
    Terminate=false;
    Counter =0;
}
void    ThreadPollingComm::Lock(void)
{
    AccessComm.lock();
}
void    ThreadPollingComm::Unlock(void)
{
    AccessComm.unlock();
}

void ThreadPollingComm::run()
{
    LEDControl16JioPrnRasPIMain  *P=dynamic_cast<LEDControl16JioPrnRasPIMain *>(parent());
    while(Terminate==false){
        //AccessComm.lock();
        //int RN=wiringPiSPIDataRW (P->GetSPIChannel(), SPIBuff, 0);
        //AccessComm.unlock();
        //if(RN>0){
        //    emit   SignalReceiveSPI(RN,SPIBuff);
        //}
        Parent->ReadIOUpdate();
        Counter++;
        usleep(500);
    }
}
void    LEDControl16JioPrnRasPIMain::SlotReceiveSPI(int CountCh,unsigned char ChBuff[])
{
}
//-------------------------------------------------------------------
static  QString     SettingJioFileName="MiconJioSetting.dat";
int		Error;


LEDControl16JioPrnRasPIMain::LEDControl16JioPrnRasPIMain(QWidget *parent) :
    QMainWindow(parent)
    ,RunPolling(this,this)
    ,ui(new Ui::LEDControl16JioPrnRasPIMain)
{
    ui->setupUi(this);
    if (wiringPiSetupGpio() < 0) {
       printf("GPIO ERROR\n");
       return;
   	}

    SPIChannel  =0;
    int SPISpeed    = 2000000;
    if(wiringPiSPISetup (SPIChannel, SPISpeed)<0){
        QMessageBox::critical(NULL,"SPI error","Error : wiringPiSPISetup");
        return;
    }
    LastPollingCounter  =RunPolling.Counter;

    AllocCount  =1000000;
    RingBuffer  =new struct  TimingData[AllocCount];
    RPoint      =0;
    WPoint      =-1;
    LastSubFrameTriggerCounter=0;
    ClearTiming();

    LightBoardCount =0;

    Server=new QTcpServer();
    if(!connect(Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()))){
    	Error++;
    }
    if(Server->listen(QHostAddress::Any,12777)==false){
    	Error++;
    }

    bool    Loaded=false;
	memset(&JioData,0,sizeof(JioData));
    QFile   File(SettingJioFileName);
    if(File.open(QIODevice::ReadOnly)==true){
        if(JioData.Load(&File)==true){
        	SetJioDataToWindow();
            Loaded=true;
        }
    }
	
	
   	InitialSignal();
    digitalWrite(8 , 1);    //SPI_CS
    unsigned char   SPIBuff[10];
    int Error=0;
    bool    SPI_OK;

    for(int i=0;i<100;i++){
    //Request DIPSW
        SPIBuff[0]=128;
        SPIBuff[1]=16;
        SPIBuff[2]=0x89;
        SPIBuff[3]=0xC7;
        SPIBuff[4]=0x07;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, SPIBuff, 4);
        digitalWrite(8 , 1);    //SPI_CS

        //QThread::msleep(10);
        if(SPIBuff[0]==0){
            DipSW_Jio=SPIBuff[2];
            break;
        }
    }
    ui->label_DipSW->setText(QString::number(DipSW_Jio));

    //Set LED ON
    SPIBuff[0]=0;       //Cmd
    SPIBuff[1]=8;
    SPIBuff[2]=1;       //Data1
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, SPIBuff, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    //Set LED Off
    SPIBuff[0]=0;
    SPIBuff[1]=8;
    SPIBuff[2]=0;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, SPIBuff, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    //Set LED ON
    SPIBuff[0]=0;       //Cmd
    SPIBuff[1]=8;
    SPIBuff[2]=1;       //Data1
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, SPIBuff, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    AverageCounter  =0;
    AddedAverage    =0;
    SubFrameTriggerCounter  =0;
    LastSubFrameTriggerCounter=0;
    WriteJioAllocation(DipSW_Jio);
    if(Loaded==true){
        WriteJio(DipSW_Jio);
    }

    ShowLEDControl16JForm   *F=new ShowLEDControl16JForm(this);
    F->WriteInitial();
    F->show();

    on_toolButtonTestMode_clicked();

    TM.setInterval(100);
    TM.setSingleShot(false);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
    TM.start();

    TimingForm  =new TimingChartForm(this);
    TimingForm->show();

    RunPolling.start();
}

LEDControl16JioPrnRasPIMain::~LEDControl16JioPrnRasPIMain()
{
    delete ui;

    RunPolling.Terminate=true;
    RunPolling.wait(1000);

    delete  []RingBuffer;
    RingBuffer=NULL;

    delete  TimingForm;
    TimingForm=NULL;
}

void    LEDControl16JioPrnRasPIMain::InitialSignal(void)
{
    pinMode(26,INPUT);  //OutSW
    pinMode(8,OUTPUT);  //SPI_CS
    pinMode(27,OUTPUT); //LED

    pinMode(16,OUTPUT); //FPGA_Reset
    pinMode(17,OUTPUT); //ExtDirect
    pinMode(18,OUTPUT); //LEDOut1
    pinMode(19,OUTPUT); //LEDOut2

    digitalWrite(8 , 1);    //SPI_CS
    digitalWrite(27, 1);
}

void	LEDControl16JioPrnRasPIMain::GetJioDataFromWindow(void)
{
    JioData.JioFixedData.ConveyerLength		=ui->spinBoxConveyerLength	->value();
    JioData.JioFixedData.GateOpenTerm		=ui->spinBoxGateOpenTerm	->value();
    JioData.JioFixedData.DelayedCountForStack=ui->spinBoxDelayedCountForStack   ->value();
    JioData.JioFixedData.MulInputA			=ui->spinBoxMulInputA		->value();
    JioData.JioFixedData.MulInputB			=ui->spinBoxMulInputB		->value();
    JioData.JioFixedData.MulInputC			=ui->spinBoxMulInputC		->value();
    JioData.JioFixedData.MulInputD			=ui->spinBoxMulInputD		->value();
    JioData.JioFixedData.TriggerFilterMinOFF=ui->spinBoxMinOFF			->value();
    JioData.JioFixedData.TriggerFilterMinON	=ui->spinBoxMinON			->value();
    JioData.JioFixedData.TriggerFilterWorkLen=ui->spinBoxWorkLen			->value();
    JioData.JioFixedData.DelayFrameTriggerA	=ui->spinBoxDelayFrameTriggerA	->value();
    JioData.JioFixedData.DelayFrameTriggerB	=ui->spinBoxDelayFrameTriggerB	->value();
    JioData.JioFixedData.DelayFrameTriggerC	=ui->spinBoxDelayFrameTriggerC	->value();
    JioData.JioFixedData.DelayFrameTriggerD	=ui->spinBoxDelayFrameTriggerD	->value();
    JioData.JioFixedData.ResultAAcceptStart	=ui->spinBoxResultAAcceptStart	->value();
    JioData.JioFixedData.ResultBAcceptStart	=ui->spinBoxResultBAcceptStart	->value();
    JioData.JioFixedData.ResultCAcceptStart	=ui->spinBoxResultCAcceptStart	->value();
    JioData.JioFixedData.ResultDAcceptStart	=ui->spinBoxResultDAcceptStart	->value();
    JioData.JioFixedData.ResultACloseAccept	=ui->spinBoxResultACloseAccept	->value();
    JioData.JioFixedData.ResultBCloseAccept	=ui->spinBoxResultBCloseAccept	->value();
    JioData.JioFixedData.ResultCCloseAccept	=ui->spinBoxResultCCloseAccept	->value();
    JioData.JioFixedData.ResultDCloseAccept	=ui->spinBoxResultDCloseAccept	->value();
    JioData.JioFixedData.TriggerDelayParameter	=ui->doubleSpinBoxTriggerDelayParameter	->value();

    JioData.JioFixedData.FlipFrameTriggerModeA  =ui->checkBoxFlipFrameTriggerA->isChecked();
    JioData.JioFixedData.FlipFrameTriggerModeB  =ui->checkBoxFlipFrameTriggerB->isChecked();
    JioData.JioFixedData.FlipFrameTriggerModeC  =ui->checkBoxFlipFrameTriggerC->isChecked();
    JioData.JioFixedData.FlipFrameTriggerModeD  =ui->checkBoxFlipFrameTriggerD->isChecked();

    JioData.JioFixedData.ModeOutResultError     =ui->checkBoxModeResultError->isChecked();

    if(ui->toolButtonTestMode->isChecked()==true){
        JioData.RealData.GOUT0  =ui->checkBoxoGOUT0 ->isChecked();
        JioData.RealData.GOUT1  =ui->checkBoxoGOUT1 ->isChecked();
        JioData.RealData.GOUT2  =ui->checkBoxoGOUT2 ->isChecked();
        JioData.RealData.GOUT3  =ui->checkBoxoGOUT3 ->isChecked();
        JioData.RealData.GOUT4  =ui->checkBoxoGOUT4 ->isChecked();
        JioData.RealData.GOUT5  =ui->checkBoxoGOUT5 ->isChecked();
        JioData.RealData.GOUT6  =ui->checkBoxoGOUT6 ->isChecked();
        JioData.RealData.GOUT7  =ui->checkBoxoGOUT7 ->isChecked();

        JioData.RealData.PIOAOUT.Bit0=ui->checkBoxPIOAOUT0->isChecked();
        JioData.RealData.PIOAOUT.Bit1=ui->checkBoxPIOAOUT1->isChecked();
        JioData.RealData.PIOAOUT.Bit2=ui->checkBoxPIOAOUT2->isChecked();
        JioData.RealData.PIOAOUT.Bit3=ui->checkBoxPIOAOUT3->isChecked();

        JioData.RealData.PIOBOUT.Bit0=ui->checkBoxPIOBOUT0->isChecked();
        JioData.RealData.PIOBOUT.Bit1=ui->checkBoxPIOBOUT1->isChecked();
        JioData.RealData.PIOBOUT.Bit2=ui->checkBoxPIOBOUT2->isChecked();
        JioData.RealData.PIOBOUT.Bit3=ui->checkBoxPIOBOUT3->isChecked();

        JioData.RealData.PIOCOUT.Bit0=ui->checkBoxPIOCOUT0->isChecked();
        JioData.RealData.PIOCOUT.Bit1=ui->checkBoxPIOCOUT1->isChecked();
        JioData.RealData.PIOCOUT.Bit2=ui->checkBoxPIOCOUT2->isChecked();
        JioData.RealData.PIOCOUT.Bit3=ui->checkBoxPIOCOUT3->isChecked();

        JioData.RealData.PIODOUT.Bit0=ui->checkBoxPIODOUT0->isChecked();
        JioData.RealData.PIODOUT.Bit1=ui->checkBoxPIODOUT1->isChecked();
        JioData.RealData.PIODOUT.Bit2=ui->checkBoxPIODOUT2->isChecked();
        JioData.RealData.PIODOUT.Bit3=ui->checkBoxPIODOUT3->isChecked();
    }
}
void	LEDControl16JioPrnRasPIMain::SetJioDataToWindow(void)
{
    ui->spinBoxConveyerLength       ->setValue(JioData.JioFixedData.ConveyerLength	);
    ui->spinBoxGateOpenTerm         ->setValue(JioData.JioFixedData.GateOpenTerm	);
    ui->spinBoxDelayedCountForStack	->setValue(JioData.JioFixedData.DelayedCountForStack	);

    ui->spinBoxMulInputA		->setValue(JioData.JioFixedData.MulInputA		);
    ui->spinBoxMulInputB		->setValue(JioData.JioFixedData.MulInputB		);
    ui->spinBoxMulInputC		->setValue(JioData.JioFixedData.MulInputC		);
    ui->spinBoxMulInputD		->setValue(JioData.JioFixedData.MulInputD		);
    ui->spinBoxMinOFF			->setValue(JioData.JioFixedData.TriggerFilterMinOFF	);
    ui->spinBoxMinON			->setValue(JioData.JioFixedData.TriggerFilterMinON	);
    ui->spinBoxWorkLen			->setValue(JioData.JioFixedData.TriggerFilterWorkLen);
    ui->spinBoxDelayFrameTriggerA	->setValue(JioData.JioFixedData.DelayFrameTriggerA);
    ui->spinBoxDelayFrameTriggerB	->setValue(JioData.JioFixedData.DelayFrameTriggerB);
    ui->spinBoxDelayFrameTriggerC	->setValue(JioData.JioFixedData.DelayFrameTriggerC);
    ui->spinBoxDelayFrameTriggerD	->setValue(JioData.JioFixedData.DelayFrameTriggerD);
    ui->spinBoxResultAAcceptStart	->setValue(JioData.JioFixedData.ResultAAcceptStart);
    ui->spinBoxResultBAcceptStart	->setValue(JioData.JioFixedData.ResultBAcceptStart);
    ui->spinBoxResultCAcceptStart	->setValue(JioData.JioFixedData.ResultCAcceptStart);
    ui->spinBoxResultDAcceptStart	->setValue(JioData.JioFixedData.ResultDAcceptStart);
    ui->spinBoxResultACloseAccept	->setValue(JioData.JioFixedData.ResultACloseAccept);
    ui->spinBoxResultBCloseAccept	->setValue(JioData.JioFixedData.ResultBCloseAccept);
    ui->spinBoxResultCCloseAccept	->setValue(JioData.JioFixedData.ResultCCloseAccept);
    ui->spinBoxResultDCloseAccept	->setValue(JioData.JioFixedData.ResultDCloseAccept);
    ui->doubleSpinBoxTriggerDelayParameter	->setValue(JioData.JioFixedData.TriggerDelayParameter);

    ui->checkBoxFlipFrameTriggerA->setChecked(JioData.JioFixedData.FlipFrameTriggerModeA);
    ui->checkBoxFlipFrameTriggerB->setChecked(JioData.JioFixedData.FlipFrameTriggerModeB);
    ui->checkBoxFlipFrameTriggerC->setChecked(JioData.JioFixedData.FlipFrameTriggerModeC);
    ui->checkBoxFlipFrameTriggerD->setChecked(JioData.JioFixedData.FlipFrameTriggerModeD);

    ui->checkBoxModeResultError->setChecked(JioData.JioFixedData.ModeOutResultError);
}
void LEDControl16JioPrnRasPIMain::on_pushButtonSendFrameTrigger_clicked()
{
	GetJioDataFromWindow();
    WriteJio(DipSW_Jio);
}

void LEDControl16JioPrnRasPIMain::on_pushButtonSaveSetting_clicked()
{
    GetJioDataFromWindow();

    QFile   File(SettingJioFileName);
    if(File.open(QIODevice::WriteOnly)==true){
        if(JioData.Save(&File)==false){
            return;
        }
    }
}

void    LEDControl16JioPrnRasPIMain::SlotNewConnection()
{

    QTcpSocket *s=Server->nextPendingConnection ();
    SocketClient    *Sock=new SocketClient(this ,s);
    AccessMutex.lock();
    ClientList.AppendList(Sock);
    AccessMutex.unlock();

    //ui->checkBoxConnecting->setChecked(true);
}


void    LEDControl16JioPrnRasPIMain::DisconnectClient(SocketClient *s)
{
    AccessMutex.lock();
    ClientList.RemoveList(s);
    AccessMutex.unlock();
    s->deleteLater();

    //ui->checkBoxConnecting->setChecked(false);
}

void    LEDControl16JioPrnRasPIMain::ReceiveData(struct JioFixedStruct &data)
{
    JioData.JioFixedData=data;
    WriteJio(DipSW_Jio);
}

#define WaitMilisecForLight 50

int     LEDControl16JioPrnRasPIMain::ReadLightBoardID(int n)
{
    unsigned char	Data[50];

    Data[0]=21;  //Command
    Data[1]=8;
    Data[2]=0;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    QThread::msleep(WaitMilisecForLight);

    Data[0]=20;  //Command
    Data[1]=8;
    Data[2]=n;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    QThread::msleep(WaitMilisecForLight);

    for(int i=0;i<10;i++){
        Data[0]=168;    //Command
        Data[1]=32;
        Data[2]=0;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, Data, 6);
        digitalWrite(8 , 1);    //SPI_CS
        if(Data[0]==0)
            break;
    }
    if(Data[0]==0){
        if((Data[5] & 0xF0)!=0){
            return Data[5] & 0x0F;
        }
    }
    return -1;
}

int     LEDControl16JioPrnRasPIMain::ReadLightCurrentValue(int BrdNo,int LineNo)
{
    unsigned char	Data[50];

    Data[0]=21;  //Command
    Data[1]=8;
    Data[2]=0;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    QThread::msleep(WaitMilisecForLight);

    Data[0]=22;  //Command
    Data[1]=8;
    Data[2]=(LineNo<<4)+BrdNo;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    QThread::msleep(WaitMilisecForLight);

    for(int i=0;i<10;i++){
        Data[0]=168;    //Command
        Data[1]=32;
        Data[2]=0;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, Data, 6);
        digitalWrite(8 , 1);    //SPI_CS
        if(Data[0]==0)
            break;
    }
    if(Data[0]==0){
        return (Data[4]<<8)+Data[5];
    }
    return -1;
}

void     LEDControl16JioPrnRasPIMain::SendLightTargetValue(int BrdNo,int LineNo,int TargetValue)
{
    unsigned char	Data[50];

    Data[0]=21;  //Command
    Data[1]=8;
    Data[2]=0;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    QThread::msleep(WaitMilisecForLight);

    Data[0]=23;  //Command
    Data[1]=24;
    Data[2]=(LineNo<<4)+BrdNo;
    Data[3]=(TargetValue>>8);
    Data[4]= TargetValue;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 5) ;
    digitalWrite(8 , 1);    //SPI_CS

    return;
}

void     LEDControl16JioPrnRasPIMain::SendLightBoardON(int BrdNo,bool LightON)
{
    unsigned char	Data[50];

    Data[0]=21;  //Command
    Data[1]=8;
    Data[2]=0;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    QThread::msleep(WaitMilisecForLight);

    Data[0]=24;  //Command
    Data[1]=8;
    if(LightON==true){
        Data[2]=0x10+BrdNo;
    }
    else {
        Data[2]=0x00+BrdNo;
    }
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 3) ;
    digitalWrite(8 , 1);    //SPI_CS
}
void    LEDControl16JioPrnRasPIMain::SendLightTestLEDON(int BrdNo,bool LightON)
{
    unsigned char	Data[50];

    Data[0]=21;  //Command
    Data[1]=8;
    Data[2]=0;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    QThread::msleep(WaitMilisecForLight);

    Data[0]=25;  //Command
    Data[1]=8;
    if(LightON==true){
        Data[2]=0x10+BrdNo;
    }
    else {
        Data[2]=0x00+BrdNo;
    }
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 3) ;
    digitalWrite(8 , 1);    //SPI_CS
}

void LEDControl16JioPrnRasPIMain::WriteJioTriggerPos(int DipSW)
{
    unsigned char	Data[50];

    MutexPolling.lock();
    int	DelayFrameTriggerA=JioData.JioFixedData.DelayFrameTriggerA - SubFrameTriggerCounter;
    int	DelayFrameTriggerB=JioData.JioFixedData.DelayFrameTriggerB - SubFrameTriggerCounter;
    int	DelayFrameTriggerC=JioData.JioFixedData.DelayFrameTriggerC - SubFrameTriggerCounter;
    int	DelayFrameTriggerD=JioData.JioFixedData.DelayFrameTriggerD - SubFrameTriggerCounter;

    Data[0]=4;  //Command
    Data[1]=64;
    Data[9]=DelayFrameTriggerA;
    Data[8]=DelayFrameTriggerA>>8;
    Data[7]=DelayFrameTriggerB;
    Data[6]=DelayFrameTriggerB>>8;
    Data[5]=DelayFrameTriggerC;
    Data[4]=DelayFrameTriggerC>>8;
    Data[3]=DelayFrameTriggerD;
    Data[2]=DelayFrameTriggerD>>8;

    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 10) ;
    digitalWrite(8 , 1);    //SPI_CS

    MutexPolling.unlock();
}
void LEDControl16JioPrnRasPIMain::WriteJio(int DipSW)
{
    unsigned char	Data[50];

    WriteJioTriggerPos(DipSW);

    MutexPolling.lock();
    Data[0]=1;  //Command
    Data[1]=64;
    Data[9]=JioData.JioFixedData.MulInputA;
    Data[8]=JioData.JioFixedData.MulInputA>>8;
    Data[7]=JioData.JioFixedData.MulInputB;
    Data[6]=JioData.JioFixedData.MulInputB>>8;
    Data[5]=JioData.JioFixedData.MulInputC;
    Data[4]=JioData.JioFixedData.MulInputC>>8;
    Data[3]=JioData.JioFixedData.MulInputD;
    Data[2]=JioData.JioFixedData.MulInputD>>8;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 10) ;
    digitalWrite(8 , 1);    //SPI_CS

    Data[0]=3;  //Command
    Data[1]=48;
    Data[7]=JioData.JioFixedData.TriggerFilterMinOFF;
    Data[6]=JioData.JioFixedData.TriggerFilterMinOFF>>8;
    Data[5]=JioData.JioFixedData.TriggerFilterMinON;
    Data[4]=JioData.JioFixedData.TriggerFilterMinON>>8;
    Data[3]=JioData.JioFixedData.TriggerFilterWorkLen;
    Data[2]=JioData.JioFixedData.TriggerFilterWorkLen>>8;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 8) ;
    digitalWrite(8 , 1);    //SPI_CS


    Data[0]=2;  //Command
    Data[1]=48;
    unsigned int    SelectEnc=JioData.JioFixedData.SelectEncA
                            +(JioData.JioFixedData.SelectEncB<<3)
                            +(JioData.JioFixedData.SelectEncC<<6)
                            +(JioData.JioFixedData.SelectEncD<<9);
    Data[4]=SelectEnc;
    Data[3]=(SelectEnc>>8)
            +((JioData.JioFixedData.FlipFrameTriggerModeA==true)?0x10:0)
            +((JioData.JioFixedData.FlipFrameTriggerModeB==true)?0x20:0)
            +((JioData.JioFixedData.FlipFrameTriggerModeC==true)?0x40:0)
            +((JioData.JioFixedData.FlipFrameTriggerModeD==true)?0x80:0);
    Data[2]=JioData.JioFixedData.SelectTriggerIn;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 5) ;
    digitalWrite(8 , 1);    //SPI_CS

    Data[0]=6;  //Command
    Data[1]=32;
    Data[5]=JioData.JioFixedData.ConveyerLength;
    Data[4]=JioData.JioFixedData.ConveyerLength>>8;
    Data[3]=JioData.JioFixedData.GateOpenTerm;
    Data[2]=JioData.JioFixedData.GateOpenTerm>>8;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 6) ;
    digitalWrite(8 , 1);    //SPI_CS

    Data[0]=7;  //Command
    Data[1]=8;
    Data[2]=(JioData.ResetCounter==true)?1:0;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 3) ;
    digitalWrite(8 , 1);    //SPI_CS

    /*
    Data[0]=JioData.JioFixedData.ResultAAcceptStart;
    Data[1]=JioData.JioFixedData.ResultAAcceptStart>>8;
    Data[2]=JioData.JioFixedData.ResultBAcceptStart;
    Data[3]=JioData.JioFixedData.ResultBAcceptStart>>8;
    Data[4]=JioData.JioFixedData.ResultCAcceptStart;
    Data[5]=JioData.JioFixedData.ResultCAcceptStart>>8;
    Data[6]=JioData.JioFixedData.ResultDAcceptStart;
    Data[7]=JioData.JioFixedData.ResultDAcceptStart>>8;
    Data[8]=JioData.JioFixedData.ResultACloseAccept;
    Data[9]=JioData.JioFixedData.ResultACloseAccept>>8;
    Data[10]=JioData.JioFixedData.ResultBCloseAccept;
    Data[11]=JioData.JioFixedData.ResultBCloseAccept>>8;
    Data[12]=JioData.JioFixedData.ResultCCloseAccept;
    Data[13]=JioData.JioFixedData.ResultCCloseAccept>>8;
    Data[14]=JioData.JioFixedData.ResultDCloseAccept;
    Data[15]=JioData.JioFixedData.ResultDCloseAccept>>8;

    SendUART1Packet(0x81,Data,16);
    */

    Data[0]=9;  //Command
    Data[1]=16;
    Data[3]=JioData.JioFixedData.DelayedCountForStack;
    Data[2]=JioData.JioFixedData.DelayedCountForStack>>8;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 4) ;
    digitalWrite(8 , 1);    //SPI_CS
    MutexPolling.unlock();
}
void LEDControl16JioPrnRasPIMain::WriteJioAllocation(int DipSW)
{
    unsigned char	Data[50];

    MutexPolling.lock();
    Data[0]=8;  //Command
    Data[1]=64;
    Data[9]=JioData.AllocateGOut[0];
    Data[8]=JioData.AllocateGOut[1];
    Data[7]=JioData.AllocateGOut[2];
    Data[6]=JioData.AllocateGOut[3];
    Data[5]=JioData.AllocateGOut[4];
    Data[4]=JioData.AllocateGOut[5];
    Data[3]=JioData.AllocateGOut[6];
    Data[2]=JioData.AllocateGOut[7];
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 10) ;
    digitalWrite(8 , 1);    //SPI_CS
    MutexPolling.unlock();
}

void LEDControl16JioPrnRasPIMain::WriteJio_R(int DipSW)
{
    unsigned char	Data[50];

    MutexPolling.lock();
    Data[0]=0;  //Command
    Data[1]=8;
    Data[2]=(JioData.TestMode==true?0x02:0)
           +(JioData.TestLEDReg==true?0x01:0)
           +(JioData.JioFixedData.ModeOutResultError==true?0x04:0) ;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 10) ;
    digitalWrite(8 , 1);    //SPI_CS


    Data[0]=5;  //Command
    Data[1]=24;
    Data[4]=(JioData.TRGAOUT&0x0F) + (JioData.TRGBOUT<<4);
    Data[3]=(JioData.TRGCOUT&0x0F) + (JioData.TRGDOUT<<4);
    Data[2]= (JioData.RealData.GOUT0==true?0x01:0)
            +(JioData.RealData.GOUT1==true?0x02:0)
            +(JioData.RealData.GOUT2==true?0x04:0)
            +(JioData.RealData.GOUT3==true?0x08:0)
            +(JioData.RealData.GOUT4==true?0x10:0)
            +(JioData.RealData.GOUT5==true?0x20:0)
            +(JioData.RealData.GOUT6==true?0x40:0)
            +(JioData.RealData.GOUT7==true?0x80:0);
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 5) ;
    digitalWrite(8 , 1);    //SPI_CS

    Data[0]=11;  //Command
    Data[1]=64;
    Data[9]= JioData.RealData.PIOAOUT.Data0;
    Data[8]= JioData.RealData.PIOAOUT.Data1;
    Data[7]= JioData.RealData.PIOBOUT.Data0;
    Data[6]= JioData.RealData.PIOBOUT.Data1;
    Data[5]= JioData.RealData.PIOCOUT.Data0;
    Data[4]= JioData.RealData.PIOCOUT.Data1;
    Data[3]= JioData.RealData.PIODOUT.Data0;
    Data[2]= JioData.RealData.PIODOUT.Data1;
    digitalWrite(8 , 0);    //SPI_CS
    wiringPiSPIDataRW    (SPIChannel, Data, 10) ;
    digitalWrite(8 , 1);    //SPI_CS
    MutexPolling.unlock();
}

void LEDControl16JioPrnRasPIMain::ReadJio(int DipSW)
{
    unsigned char	Data[50];

    MutexPolling.lock();
    for(int i=0;i<10;i++){
        Data[0]=132;
        Data[1]=64;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, Data, 10);
        digitalWrite(8 , 1);    //SPI_CS
        if(Data[0]==0)
            break;
    }
    if(Data[0]==0){
        int	DelayFrameTriggerA=(int)Data[9]+(int)(Data[8]<<8);
        int	DelayFrameTriggerB=(int)Data[7]+(int)(Data[6]<<8);
        int	DelayFrameTriggerC=(int)Data[5]+(int)(Data[4]<<8);
        int	DelayFrameTriggerD=(int)Data[3]+(int)(Data[2]<<8);
        JioData.JioFixedData.DelayFrameTriggerA= DelayFrameTriggerA- SubFrameTriggerCounter;
        JioData.JioFixedData.DelayFrameTriggerB= DelayFrameTriggerB- SubFrameTriggerCounter;
        JioData.JioFixedData.DelayFrameTriggerC= DelayFrameTriggerC- SubFrameTriggerCounter;
    }

    for(int i=0;i<10;i++){
        Data[0]=129;
        Data[1]=32;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, Data, 10);
        digitalWrite(8 , 1);    //SPI_CS
        if(Data[0]==0)
            break;
    }
    if(Data[0]==0){
        JioData.JioFixedData.MulInputA=(unsigned long)Data[9]+(unsigned long)(Data[8]<<8);
        JioData.JioFixedData.MulInputB=(unsigned long)Data[7]+(unsigned long)(Data[6]<<8);
        JioData.JioFixedData.MulInputC=(unsigned long)Data[5]+(unsigned long)(Data[4]<<8);
        JioData.JioFixedData.MulInputD=(unsigned long)Data[3]+(unsigned long)(Data[2]<<8);
    }

    for(int i=0;i<10;i++){
        Data[0]=131;
        Data[1]=32;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, Data, 8);
        digitalWrite(8 , 1);    //SPI_CS
        if(Data[0]==0)
            break;
    }
    if(Data[0]==0){
        JioData.JioFixedData.TriggerFilterMinOFF    =(unsigned long)Data[7]+(unsigned long)(Data[6]<<8);
        JioData.JioFixedData.TriggerFilterMinON     =(unsigned long)Data[5]+(unsigned long)(Data[4]<<8);
        JioData.JioFixedData.TriggerFilterWorkLen   =(unsigned long)Data[3]+(unsigned long)(Data[2]<<8);
    }
    MutexPolling.unlock();
}


void LEDControl16JioPrnRasPIMain::ReadJio_R(int DipSW)
{
    unsigned char	Data[50];

    MutexPolling.lock();
    for(int i=0;i<10;i++){
        Data[0]=133;
        Data[1]=32;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, Data, 5);
        digitalWrite(8 , 1);    //SPI_CS
        if(Data[0]==0)
            break;
    }
    if(Data[0]==0){
        JioData.TRGAOUT         = Data[4]&0xF;
        JioData.TRGBOUT         =(Data[4]>>4)&0x0F;
        JioData.TRGCOUT         = Data[3]&0x0F;
        JioData.TRGDOUT         =(Data[3]>>4)&0x0F;
        JioData.RealData.GOUT0	=(Data[2]&0x01)!=0?true:false;
        JioData.RealData.GOUT1	=(Data[2]&0x02)!=0?true:false;
        JioData.RealData.GOUT2	=(Data[2]&0x04)!=0?true:false;
        JioData.RealData.GOUT3	=(Data[2]&0x08)!=0?true:false;
        JioData.RealData.GOUT4	=(Data[2]&0x10)!=0?true:false;
        JioData.RealData.GOUT5	=(Data[2]&0x20)!=0?true:false;
        JioData.RealData.GOUT6	=(Data[2]&0x40)!=0?true:false;
        JioData.RealData.GOUT7	=(Data[2]&0x80)!=0?true:false;
    }

    for(int i=0;i<10;i++){
        Data[0]=140;
        Data[1]=48;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, Data, 8);
        digitalWrite(8 , 1);    //SPI_CS
        if(Data[0]==0)
            break;
    }
    if(Data[0]==0){
        JioData.RealData.GIN0	=(Data[7]&0x01)!=0?true:false;
        JioData.RealData.GIN1	=(Data[7]&0x02)!=0?true:false;
        JioData.RealData.GIN2	=(Data[7]&0x04)!=0?true:false;
        JioData.RealData.GIN3	=(Data[7]&0x08)!=0?true:false;
        JioData.RealData.TRGIN0	=(Data[7]&0x10)!=0?true:false;
        JioData.RealData.TRGIN1	=(Data[7]&0x20)!=0?true:false;
        JioData.RealData.TRGIN2	=(Data[7]&0x40)!=0?true:false;
        JioData.RealData.TRGIN3	=(Data[7]&0x80)!=0?true:false;

        JioData.RealData.PIOAIN.Data=Data[6];
        JioData.RealData.PIOBIN.Data=Data[5];
        JioData.RealData.PIOCIN.Data=Data[4];
        JioData.RealData.PIODIN.Data=Data[3];

        JioData.RealData.GOUT0	=(Data[2]&0x01)!=0?true:false;
        JioData.RealData.GOUT1	=(Data[2]&0x02)!=0?true:false;
        JioData.RealData.GOUT2	=(Data[2]&0x04)!=0?true:false;
        JioData.RealData.GOUT3	=(Data[2]&0x08)!=0?true:false;
        JioData.RealData.GOUT4	=(Data[2]&0x10)!=0?true:false;
        JioData.RealData.GOUT5	=(Data[2]&0x20)!=0?true:false;
        JioData.RealData.GOUT6	=(Data[2]&0x40)!=0?true:false;
        JioData.RealData.GOUT7	=(Data[2]&0x80)!=0?true:false;
    }

    for(int i=0;i<10;i++){
        Data[0]=146;
        Data[1]=48;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, Data, 8);
        digitalWrite(8 , 1);    //SPI_CS
        if(Data[0]==0)
            break;
    }
    if(Data[0]==0){
        JioData.MotorPulseCounter
                        = ((unsigned long)Data[7])
                        +(((unsigned long)Data[6])<<8)
                        +(((unsigned long)Data[5])<<16);
        JioData.MotorPulseCounter2
                        = ((unsigned long)Data[4])
                        +(((unsigned long)Data[3])<<8)
                        +(((unsigned long)Data[2])<<16);
    }

    for(int i=0;i<10;i++){
        Data[0]=142;
        Data[1]=48;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, Data, 8);
        digitalWrite(8 , 1);    //SPI_CS
        if(Data[0]==0)
            break;
    }
    if(Data[0]==0){
        JioData.TotalCount
                        = ((unsigned long)Data[7])
                        +(((unsigned long)Data[6])<<8)
                        +(((unsigned long)Data[5])<<16);
        JioData.OKCount
                        = ((unsigned long)Data[4])
                        +(((unsigned long)Data[3])<<8)
                        +(((unsigned long)Data[2])<<16);
    }

    for(int i=0;i<10;i++){
        Data[0]=143;
        Data[1]=48;
        digitalWrite(8 , 0);    //SPI_CS
        wiringPiSPIDataRW    (SPIChannel, Data, 8);
        digitalWrite(8 , 1);    //SPI_CS
        if(Data[0]==0)
            break;
    }
    if(Data[0]==0){
        JioData.NGCount
                        = ((unsigned long)Data[7])
                        +(((unsigned long)Data[6])<<8)
                        +(((unsigned long)Data[5])<<16);
        JioData.TMCount
                        = ((unsigned long)Data[4])
                        +(((unsigned long)Data[3])<<8)
                        +(((unsigned long)Data[2])<<16);
    }
    //JioData.RealData.OuterSW    =((Data[16]&0x02)!=0)?true:false;
    //JioData.RealData.ExtDirect	=((Data[16]&0x04)!=0)?true:false;
    MutexPolling.unlock();
}

void    LEDControl16JioPrnRasPIMain::SlotTimeOut()
{
    //ReadJio_R(DipSW_Jio);

    if(WPoint<0 || memcmp(&JioData.RealData,&RingBuffer[WPoint].RealData,sizeof(JioData.RealData))!=0){
        WPoint++;
        if(WPoint>=AllocCount){
            WPoint=0;
        }
        RingBuffer[WPoint].CurrentMiliSec =::GetComputerMiliSec();
        RingBuffer[WPoint].RealData=JioData.RealData;
    }
    int n=ui->progressBar->value();
    n++;
    if(n>=ui->progressBar->maximum())
        n=0;
    ui->progressBar->setValue(n);
    
    ui->checkBoxGIN0 ->setChecked(JioData.RealData.GIN0);
    ui->checkBoxGIN1 ->setChecked(JioData.RealData.GIN1);
    ui->checkBoxGIN2 ->setChecked(JioData.RealData.GIN2);
    ui->checkBoxGIN3 ->setChecked(JioData.RealData.GIN3);
    
    ui->checkBoxTRGIN0 ->setChecked(JioData.RealData.TRGIN0);
    ui->checkBoxTRGIN1 ->setChecked(JioData.RealData.TRGIN1);
    ui->checkBoxTRGIN2 ->setChecked(JioData.RealData.TRGIN2);
    ui->checkBoxTRGIN3 ->setChecked(JioData.RealData.TRGIN3);
    
    ui->checkBoxPIOAIN0->setChecked(JioData.RealData.PIOAIN.Bit0);
    ui->checkBoxPIOAIN1->setChecked(JioData.RealData.PIOAIN.Bit1);
    ui->checkBoxPIOAIN2->setChecked(JioData.RealData.PIOAIN.Bit2);
    ui->checkBoxPIOAIN3->setChecked(JioData.RealData.PIOAIN.Bit3);
    
    ui->checkBoxPIOBIN0->setChecked(JioData.RealData.PIOBIN.Bit0);
    ui->checkBoxPIOBIN1->setChecked(JioData.RealData.PIOBIN.Bit1);
    ui->checkBoxPIOBIN2->setChecked(JioData.RealData.PIOBIN.Bit2);
    ui->checkBoxPIOBIN3->setChecked(JioData.RealData.PIOBIN.Bit3);
    
    ui->checkBoxPIOCIN0->setChecked(JioData.RealData.PIOCIN.Bit0);
    ui->checkBoxPIOCIN1->setChecked(JioData.RealData.PIOCIN.Bit1);
    ui->checkBoxPIOCIN2->setChecked(JioData.RealData.PIOCIN.Bit2);
    ui->checkBoxPIOCIN3->setChecked(JioData.RealData.PIOCIN.Bit3);
    
    ui->checkBoxPIODIN0->setChecked(JioData.RealData.PIODIN.Bit0);
    ui->checkBoxPIODIN1->setChecked(JioData.RealData.PIODIN.Bit1);
    ui->checkBoxPIODIN2->setChecked(JioData.RealData.PIODIN.Bit2);
    ui->checkBoxPIODIN3->setChecked(JioData.RealData.PIODIN.Bit3);

    if(ui->toolButtonTestMode->isChecked()==false){
        ui->checkBoxoGOUT0->setChecked(JioData.RealData.GOUT0);
        ui->checkBoxoGOUT1->setChecked(JioData.RealData.GOUT1);
        ui->checkBoxoGOUT2->setChecked(JioData.RealData.GOUT2);
        ui->checkBoxoGOUT3->setChecked(JioData.RealData.GOUT3);

        ui->checkBoxPIOAOUT0->setChecked(JioData.RealData.PIOAOUT.Bit0);
        ui->checkBoxPIOAOUT1->setChecked(JioData.RealData.PIOAOUT.Bit1);
        ui->checkBoxPIOAOUT2->setChecked(JioData.RealData.PIOAOUT.Bit2);
        ui->checkBoxPIOAOUT3->setChecked(JioData.RealData.PIOAOUT.Bit3);

        ui->checkBoxPIOBOUT0->setChecked(JioData.RealData.PIOBOUT.Bit0);
        ui->checkBoxPIOBOUT1->setChecked(JioData.RealData.PIOBOUT.Bit1);
        ui->checkBoxPIOBOUT2->setChecked(JioData.RealData.PIOBOUT.Bit2);
        ui->checkBoxPIOBOUT3->setChecked(JioData.RealData.PIOBOUT.Bit3);

        ui->checkBoxPIOCOUT0->setChecked(JioData.RealData.PIOCOUT.Bit0);
        ui->checkBoxPIOCOUT1->setChecked(JioData.RealData.PIOCOUT.Bit1);
        ui->checkBoxPIOCOUT2->setChecked(JioData.RealData.PIOCOUT.Bit2);
        ui->checkBoxPIOCOUT3->setChecked(JioData.RealData.PIOCOUT.Bit3);

        ui->checkBoxPIODOUT0->setChecked(JioData.RealData.PIODOUT.Bit0);
        ui->checkBoxPIODOUT1->setChecked(JioData.RealData.PIODOUT.Bit1);
        ui->checkBoxPIODOUT2->setChecked(JioData.RealData.PIODOUT.Bit2);
        ui->checkBoxPIODOUT3->setChecked(JioData.RealData.PIODOUT.Bit3);
    }
    else{
        GetJioDataFromWindow();
        WriteJio_R(DipSW_Jio);
    }

    QString s=QString::number(JioData.MotorPulseCounter);
    ui->labelMotorPulseCounter->setText(s);

    QString s2=QString::number(JioData.MotorPulseCounter2);
    ui->labelMotorPulseCounter2->setText(s2);

    AddedAverage  +=JioData.MotorPulseCounter;
    AverageCounter++;
    if(AverageCounter>=10){
        unsigned    int tCounter=RunPolling.Counter;
        unsigned    int SCount=tCounter-LastPollingCounter;
        LastPollingCounter  =tCounter;

        DWORD  ts=GetComputerMiliSec();
        DWORD   SpanMilisec=ts-LastComputerTime;
        LastComputerTime=ts;
        if(SpanMilisec!=0){
            double  AccessPerSec=((double)SCount)*1000.0/((double)SpanMilisec);
            ui->label_AccessPerSec->setText(QString::number(AccessPerSec,'f',1));
        }

        int AvrCounter=AddedAverage/AverageCounter;
        AddedAverage=0;
        AverageCounter=0;
        if(AvrCounter>100){
            SubFrameTriggerCounter=JioData.JioFixedData.TriggerDelayParameter/AvrCounter;
            int dS=LastSubFrameTriggerCounter-SubFrameTriggerCounter;
            if(dS<-20 || 20<dS){
                WriteJioTriggerPos(DipSW_Jio);
                LastSubFrameTriggerCounter=SubFrameTriggerCounter;
                ui->label_SubFrameTriggerCounter->setText(QString::number(SubFrameTriggerCounter));
            }
        }
    }
    TimingForm->RepaintSignals();
}
void    LEDControl16JioPrnRasPIMain::SendLightInfo(SocketClient *s)
{
    BYTE    Data[100];
    Data[0]=LightBoardCount;
    s->SendOut(-1,'U',Data ,1);
}

void LEDControl16JioPrnRasPIMain::on_toolButtonTestMode_clicked()
{
    JioData.TestMode    =ui->toolButtonTestMode->isChecked();

    if(JioData.TestMode==true){
        ui->widgetTestMode->setEnabled(true);
    }
    else{
        ui->widgetTestMode->setEnabled(false);
    }
    WriteJio_R(DipSW_Jio);
}

void LEDControl16JioPrnRasPIMain::on_toolButtonAllocateIO_clicked()
{
    AllocateIODialog    D(this);
    if(D.exec()==true){
        WriteJioAllocation(DipSW_Jio);
    }
}

void LEDControl16JioPrnRasPIMain::on_pushButtonReqOutPulse_clicked()
{
    /*
    unsigned char	Data[50];

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
    */
}

void LEDControl16JioPrnRasPIMain::on_pushButtonClearOutPulse_clicked()
{
    /*
    unsigned char	Data[50];
    Data[0]= 1;
    SendUART1Packet(0x40+8,Data,1);
    Data[0]= 0;
    SendUART1Packet(0x40+8,Data,1);
    */
}
struct  TimingData	*LEDControl16JioPrnRasPIMain::FindTimingAhead(DWORD t)
{
    int n=PointCount;
    for(int i=WPoint-1;i>=0 && n>=0;i--,n--){
        if(RingBuffer[i].CurrentMiliSec<=t){
            return &RingBuffer[i];
        }
    }
    for(int i=AllocCount-1;i>=0 && n>=0;i--,n--){
        if(RingBuffer[i].CurrentMiliSec<=t){
            return &RingBuffer[i];
        }
    }
    return NULL;
}

struct  TimingData	*LEDControl16JioPrnRasPIMain::GetTiming(int point)
{
    while(point<0){
        point+=AllocCount;
    }
    while(AllocCount<=point){
        point-=AllocCount;
    }
    return &RingBuffer[point];
}
int     LEDControl16JioPrnRasPIMain::GetFirstTimingPoint(void)
{
    int     k=WPoint-PointCount;
    if(k<0)
        k+=AllocCount;
    return k;
}
int     LEDControl16JioPrnRasPIMain::GetTimingCount(void)
{
    return PointCount;
}

void    LEDControl16JioPrnRasPIMain::ClearTiming(void)
{
    PointCount  =0;
    WPoint      =0;
    LastWPoint  =-1;
}
void    LEDControl16JioPrnRasPIMain::ReadIOUpdate()
{
    ReadJio_R(DipSW_Jio);

    if(LastWPoint<0 || memcmp(&JioData.RealData,&RingBuffer[LastWPoint].RealData,sizeof(JioData.RealData))!=0){
        if(TimingForm->GetSamplingMode()==true){
            MutexPolling.lock();
            RingBuffer[WPoint].CurrentMiliSec =::GetComputerMiliSec();
             RingBuffer[WPoint].RealData=JioData.RealData;
            MutexPolling.unlock();
            LastWPoint=WPoint;
            WPoint++;
            PointCount++;
            if(WPoint>=AllocCount){
                WPoint=0;
            }
            if(PointCount>AllocCount){
                PointCount=AllocCount;
            }
        }
    }
}

