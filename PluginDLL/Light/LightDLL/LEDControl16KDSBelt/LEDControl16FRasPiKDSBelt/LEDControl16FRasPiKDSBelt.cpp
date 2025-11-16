#include "LEDControl16FRasPiKDSBelt.h"
#include "ui_LEDControl16FRasPiKDSBelt.h"
#include <wiringPi.h>
#include <QFile>
#include "XTypeDef.h"
#include "XCriticalFunc.h"
#include "ShowLEDControl16GForm.h"
#include "LightDeviceStruct.h"

SocketClient::SocketClient(LEDControl16FRasPiKDSBelt *parent ,QTcpSocket *s)
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
        struct  KDSBeltPIOStruct  Data;
        if(DataLen==sizeof(Data)){
            if(Socket->read((char *)&Data,sizeof(Data))==sizeof(Data)){
                Parent->SendStartSequence(Data.RegStartSequence);
            }
        }
        else{
             QByteArray A=Socket->readAll();
        }
    }
    else if(Cmd=='F'){
        struct  KDSBeltPIOStruct  Data;
        if(DataLen==sizeof(Data)){
            if(Socket->read((char *)&Data,sizeof(Data))==sizeof(Data)){
                Parent->SendLineCount(Data.KDSBeltPIOFixedData.LineCountInFrame);
            }
        }
        else{
             QByteArray A=Socket->readAll();
        }
    }
    else if(Cmd=='B'){
        QByteArray Dummy=Socket->readAll();
        SendOut(-1,'B' ,(BYTE *)&Parent->GIOData.MotorPulseCounter ,sizeof(Parent->GIOData.MotorPulseCounter));
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
        SendOut(-1,'V' ,(BYTE *)"LEDControl16GIOPrn",19);
    }
    else if(Cmd=='U'){
        QByteArray Dummy=Socket->readAll();
        Parent->SendLightInfo(this);
    }
    else if(Cmd=='L'){
        Parent->GIOData.RealData.GOUT0=true;
        Parent->GIOData.RealData.GOUT1=true;
        Parent->GIOData.RealData.GOUT2=true;
        Parent->WriteGIO();
        Parent->StartLightTimer();
    }
    else if(Cmd=='l'){
        Parent->GIOData.RealData.GOUT0=false;
        Parent->GIOData.RealData.GOUT1=false;
        Parent->GIOData.RealData.GOUT2=false;
        Parent->WriteGIO();
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
static  QString     SettingGIOFileName="MiconFIOKDSSetting.dat";


LEDControl16FRasPiKDSBelt::LEDControl16FRasPiKDSBelt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LEDControl16FRasPiKDSBelt)
{
    ui->setupUi(this);
    
    InitialSignal();
    
    AllocCount  =100000;
    RingBuffer  =new struct  TimingData[AllocCount];
    RPoint      =0;
    WPoint      =-1;

    LightBoardCount =0;

    connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
    Server.listen(QHostAddress::Any,12777);

	memset(&GIOData,0,sizeof(GIOData));
    QFile   File(SettingGIOFileName);
    if(File.open(QIODevice::ReadOnly)==true){
        if(GIOData.Load(&File)==true){
        	SetGIODataToWindow();
        }
        if(::Load(&File,MaxLightingSec)==true){
            ui->spinBoxMaxLightingSec->setValue(MaxLightingSec);
        }
    }
    WriteInitial();

    AverageCounter  =0;
    AddedAverage    =0;
    SubFrameTriggerCounter  =0;

    ShowLEDControl16GForm   *F=new ShowLEDControl16GForm();
    F->show();

    TM.setInterval(100);
    TM.setSingleShot(false);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
    TM.start();

    MaxLightingSec=40;
    TimerLight.setInterval(MaxLightingSec*1000);
    TimerLight.setSingleShot(true);
    connect(&TimerLight,SIGNAL(timeout()),this,SLOT(SlotLightTimeOut()));

    on_toolButtonTestMode_clicked();
}

LEDControl16FRasPiKDSBelt::~LEDControl16FRasPiKDSBelt()
{
    delete ui;
    delete  []RingBuffer;
    RingBuffer=NULL;
}

void    LEDControl16FRasPiKDSBelt::StartLightTimer(void)
{
    TimerLight.setInterval(MaxLightingSec*1000);
    TimerLight.start();
}
void    LEDControl16FRasPiKDSBelt::SlotLightTimeOut()
{
    GIOData.RealData.GOUT0=false;
    GIOData.RealData.GOUT1=false;
    GIOData.RealData.GOUT2=false;
    WriteGIO();
}

void	LEDControl16FRasPiKDSBelt::GetGIODataFromWindow(void)
{
    GIOData.KDSBeltPIOFixedData.MulInput			=ui->spinBoxMulInput		->value();
    GIOData.KDSBeltPIOFixedData.TriggerFilterMinOFF =ui->spinBoxMinOFF			->value();
    GIOData.KDSBeltPIOFixedData.TriggerFilterMinON	=ui->spinBoxMinON			->value();
    GIOData.KDSBeltPIOFixedData.LineCountInFrame    =ui->spinBoxLineCount       ->value();
    if(ui->toolButtonTestMode->isChecked()==true){
        GIOData.RealData.GOUT0  =ui->checkBoxoGOUT0 ->isChecked();
        GIOData.RealData.GOUT1  =ui->checkBoxoGOUT1 ->isChecked();
        GIOData.RealData.GOUT2  =ui->checkBoxoGOUT2 ->isChecked();
        GIOData.RealData.GOUT3  =ui->checkBoxoGOUT3 ->isChecked();
        GIOData.RealData.GOUT4  =ui->checkBoxoGOUT4 ->isChecked();
        GIOData.RealData.GOUT5  =ui->checkBoxoGOUT5 ->isChecked();
        GIOData.RealData.GOUT6  =ui->checkBoxoGOUT6 ->isChecked();
        GIOData.RealData.GOUT7  =ui->checkBoxoGOUT7 ->isChecked();
        GIOData.RealData.GOUT8  =ui->checkBoxoGOUT8 ->isChecked();
        GIOData.RealData.GOUT9  =ui->checkBoxoGOUT9 ->isChecked();
        GIOData.RealData.GOUT10 =ui->checkBoxoGOUT10->isChecked();
        GIOData.RealData.GOUT11 =ui->checkBoxoGOUT11->isChecked();
        GIOData.RealData.GOUT12 =ui->checkBoxoGOUT12->isChecked();
        GIOData.RealData.GOUT13 =ui->checkBoxoGOUT13->isChecked();
        GIOData.RealData.GOUT14 =ui->checkBoxoGOUT14->isChecked();
        GIOData.RealData.GOUT15 =ui->checkBoxoGOUT15->isChecked();

        GIOData.RealData.CamFrameTrigger=ui->checkBoxoCamFrameTrigger->isChecked();
        GIOData.RealData.CamLineTrigger =ui->checkBoxoCamLineTrigger ->isChecked();
        GIOData.RealData.CamOut0        =ui->checkBoxoCamOut0        ->isChecked();
        GIOData.RealData.CamOut1        =ui->checkBoxoCamOut1        ->isChecked();
    }


}
void	LEDControl16FRasPiKDSBelt::SetGIODataToWindow(void)
{
    ui->spinBoxMulInput         ->setValue(GIOData.KDSBeltPIOFixedData.MulInput		);
    ui->spinBoxMinOFF			->setValue(GIOData.KDSBeltPIOFixedData.TriggerFilterMinOFF	);
    ui->spinBoxMinON			->setValue(GIOData.KDSBeltPIOFixedData.TriggerFilterMinON	);
    ui->spinBoxLineCount        ->setValue(GIOData.KDSBeltPIOFixedData.LineCountInFrame     );
}

void LEDControl16FRasPiKDSBelt::on_pushButtonSendFrameTrigger_clicked()
{
	GetGIODataFromWindow();
    WriteGIO(DipSW_GIO);
}

void LEDControl16FRasPiKDSBelt::on_pushButtonSaveSetting_clicked()
{
    GetGIODataFromWindow();

    QFile   File(SettingGIOFileName);
    if(File.open(QIODevice::WriteOnly)==true){
        if(GIOData.Save(&File)==false){
            return;
        }
        MaxLightingSec  =ui->spinBoxMaxLightingSec->value();
        if(::Save(&File,MaxLightingSec)==false){
            return;
        }
    }
}

void    LEDControl16FRasPiKDSBelt::WriteInitial(void)
{
    DipSW_GIO=15;

    //TestWriteE(0);

    int data;
    for(int dipsw=0;dipsw<16;dipsw++){
        data=ReadBoardID(dipsw);
        if(data==10){
            DipSW_GIO=dipsw;
        }
    }
    GIOData.TestLEDReg=true;
    WriteGIO(DipSW_GIO);
    GIOData.TestLEDReg=false;
    WriteGIO(DipSW_GIO);
    GIOData.TestLEDReg=true;
    WriteGIO(DipSW_GIO);
}

void    LEDControl16FRasPiKDSBelt::SlotNewConnection()
{

    QTcpSocket *s=Server.nextPendingConnection ();
    SocketClient    *Sock=new SocketClient(this ,s);
    AccessMutex.lock();
    ClientList.AppendList(Sock);
    AccessMutex.unlock();

    //ui->checkBoxConnecting->setChecked(true);
}


void    LEDControl16FRasPiKDSBelt::DisconnectClient(SocketClient *s)
{
    AccessMutex.lock();
    ClientList.RemoveList(s);
    AccessMutex.unlock();
    s->deleteLater();

    //ui->checkBoxConnecting->setChecked(false);
}

void    LEDControl16FRasPiKDSBelt::ReceiveData(struct KDSBeltPIOFixedStruct &data)
{
    GIOData.KDSBeltPIOFixedData=data;
    WriteGIO(DipSW_GIO);
}
void    LEDControl16FRasPiKDSBelt::WriteGIO()
{
    WriteGIO(DipSW_GIO);
}
void    LEDControl16FRasPiKDSBelt::ReadGIO()
{
    ReadGIO(DipSW_GIO);
}
void LEDControl16FRasPiKDSBelt::WriteGIO(int DipSW)
{
    int	Data[50];

    Data[0]= (GIOData.RegLEDOut[0]==true?0x08:0)
            +(GIOData.RegLEDOut[1]==true?0x10:0)
            +(GIOData.TestMode==true?0x04:0)
            +(GIOData.TestLEDReg==true?0x02:0)
            +(GIOData.RegStartSequence==true?0x01:0);
    Data[1]= (GIOData.AD_CS ==true?0x04:0)
    		+(GIOData.AD_DIN==true?0x02:0)
    		+(GIOData.AD_CLK==true?0x01:0);
    Data[2]= (GIOData.RealData.GOUT0==true?0x01:0)
    		+(GIOData.RealData.GOUT1==true?0x02:0)
    		+(GIOData.RealData.GOUT2==true?0x04:0)
    		+(GIOData.RealData.GOUT3==true?0x08:0)
    		+(GIOData.RealData.GOUT4==true?0x10:0)
    		+(GIOData.RealData.GOUT5==true?0x20:0)
    		+(GIOData.RealData.GOUT6==true?0x40:0)
    		+(GIOData.RealData.GOUT7==true?0x80:0);
    Data[3]= (GIOData.RealData.GOUT8==true?0x01:0)
            +(GIOData.RealData.GOUT9==true?0x02:0)
            +(GIOData.RealData.GOUT10==true?0x04:0)
            +(GIOData.RealData.GOUT11==true?0x08:0)
            +(GIOData.RealData.GOUT12==true?0x10:0)
            +(GIOData.RealData.GOUT13==true?0x20:0)
            +(GIOData.RealData.GOUT14==true?0x40:0)
            +(GIOData.RealData.GOUT15==true?0x80:0);
    Data[4] = GIOData.KDSBeltPIOFixedData.MulInput & 0xFF;
    Data[5] =(GIOData.KDSBeltPIOFixedData.MulInput>>8) & 0xFF;
    Data[6] =((GIOData.KDSBeltPIOFixedData.MulInput>>16) & 0x0F);
    Data[7] = GIOData.KDSBeltPIOFixedData.TriggerFilterMinOFF & 0xFF;
    Data[8] =(GIOData.KDSBeltPIOFixedData.TriggerFilterMinOFF>>8) & 0xFF;
    Data[9] = GIOData.KDSBeltPIOFixedData.TriggerFilterMinON & 0xFF;
    Data[10]=(GIOData.KDSBeltPIOFixedData.TriggerFilterMinON>>8) & 0xFF;
    Data[11]=(GIOData.RealData.CamFrameTrigger==true?0x01:0)
            +(GIOData.RealData.CamLineTrigger==true?0x02:0)
            +(GIOData.RealData.CamOut0==true?0x04:0)
            +(GIOData.RealData.CamOut1==true?0x08:0);
    Data[12] = GIOData.KDSBeltPIOFixedData.LineCountInFrame & 0xFF;
    Data[13] =(GIOData.KDSBeltPIOFixedData.LineCountInFrame>>8) & 0xFF;
    Data[14] =((GIOData.KDSBeltPIOFixedData.LineCountInFrame>>16) & 0x0F);
    WriteRegister(DipSW ,Data,15);
}
void LEDControl16FRasPiKDSBelt::ReadGIO(int DipSW)
{
    int	Data[50];

    //Data[0]= (GIOData.RegLEDOut[0]==true?0x40:0)
    //        +(GIOData.RegLEDOut[1]==true?0x80:0)
    //        +(GIOData.TestMode==true?0x20:0)
    //        +(GIOData.TestLEDReg==true?0x10:0)
    //        +(GIOData.RMode&0x0F);

    //WriteRegister(DipSW ,Data,1);

    ReadRegister4Bit(DipSW ,Data ,18);
    GIOData.RealData.FASTIN0	=(Data[1]&0x01)!=0?true:false;
    GIOData.RealData.FASTIN1	=(Data[1]&0x02)!=0?true:false;
    GIOData.RealData.FASTIN2	=(Data[1]&0x04)!=0?true:false;
    GIOData.RealData.FASTIN3	=(Data[1]&0x08)!=0?true:false;
    GIOData.RealData.FASTIN4	=(Data[2]&0x01)!=0?true:false;
    GIOData.RealData.FASTIN5	=(Data[2]&0x02)!=0?true:false;
    GIOData.RealData.FASTIN6	=(Data[2]&0x04)!=0?true:false;
    GIOData.RealData.FASTIN7	=(Data[2]&0x08)!=0?true:false;
    GIOData.RealData.GIN0       =(Data[3]&0x01)!=0?true:false;
    GIOData.RealData.GIN1       =(Data[3]&0x02)!=0?true:false;
    GIOData.RealData.GIN2       =(Data[3]&0x04)!=0?true:false;
    GIOData.RealData.GIN3       =(Data[3]&0x08)!=0?true:false;
    GIOData.RealData.GIN4       =(Data[4]&0x01)!=0?true:false;
    GIOData.RealData.GIN5       =(Data[4]&0x02)!=0?true:false;
    GIOData.RealData.GIN6       =(Data[4]&0x04)!=0?true:false;
    GIOData.RealData.GIN7       =(Data[4]&0x08)!=0?true:false;
    GIOData.RealData.GIN8       =(Data[5]&0x01)!=0?true:false;
    GIOData.RealData.GIN9       =(Data[5]&0x02)!=0?true:false;
    GIOData.RealData.GIN10      =(Data[5]&0x04)!=0?true:false;
    GIOData.RealData.GIN11      =(Data[5]&0x08)!=0?true:false;
    GIOData.RealData.GIN12      =(Data[6]&0x01)!=0?true:false;
    GIOData.RealData.GIN13      =(Data[6]&0x02)!=0?true:false;
    GIOData.RealData.GIN14      =(Data[6]&0x04)!=0?true:false;
    GIOData.RealData.GIN15      =(Data[6]&0x08)!=0?true:false;
    GIOData.RealData.OuterSW    =((Data[7]&0x02)!=0)?true:false;
    GIOData.RealData.ExtDirect	=((Data[7]&0x04)!=0)?true:false;
	
    GIOData.MotorPulseCounter
                    = ((unsigned long)Data[8])
                    +(((unsigned long)Data[9])<<4)
                    +(((unsigned long)Data[10])<<8)
                    +(((unsigned long)Data[11])<<12)
                    +(((unsigned long)Data[12])<<16)
                    +(((unsigned long)Data[13])<<20)
                    +(((unsigned long)Data[14])<<24)
                    +(((unsigned long)Data[15])<<28);

}


void    LEDControl16FRasPiKDSBelt::SlotTimeOut()
{
    ReadGIO(DipSW_GIO);

    if(WPoint<0 || memcmp(&GIOData.RealData,&RingBuffer[WPoint].RealData,sizeof(GIOData.RealData))!=0){
        WPoint++;
        if(WPoint>=AllocCount){
            WPoint=0;
        }
        RingBuffer[WPoint].CurrentMiliSec =::GetComputerMiliSec();
        RingBuffer[WPoint].RealData=GIOData.RealData;
    }
    
    ui->checkBoxGIN0 ->setChecked(GIOData.RealData.GIN0);
    ui->checkBoxGIN1 ->setChecked(GIOData.RealData.GIN1);
    ui->checkBoxGIN2 ->setChecked(GIOData.RealData.GIN2);
    ui->checkBoxGIN3 ->setChecked(GIOData.RealData.GIN3);
    ui->checkBoxGIN4 ->setChecked(GIOData.RealData.GIN4);
    ui->checkBoxGIN5 ->setChecked(GIOData.RealData.GIN5);
    ui->checkBoxGIN6 ->setChecked(GIOData.RealData.GIN6);
    ui->checkBoxGIN7 ->setChecked(GIOData.RealData.GIN7);
    ui->checkBoxGIN8 ->setChecked(GIOData.RealData.GIN8);
    ui->checkBoxGIN9 ->setChecked(GIOData.RealData.GIN9);
    ui->checkBoxGIN10->setChecked(GIOData.RealData.GIN10);
    ui->checkBoxGIN11->setChecked(GIOData.RealData.GIN11);
    ui->checkBoxGIN12->setChecked(GIOData.RealData.GIN12);
    ui->checkBoxGIN13->setChecked(GIOData.RealData.GIN13);
    ui->checkBoxGIN14->setChecked(GIOData.RealData.GIN14);
    ui->checkBoxGIN15->setChecked(GIOData.RealData.GIN15);

    ui->checkBoxFASTIN0 ->setChecked(GIOData.RealData.FASTIN0);
    ui->checkBoxFASTIN1 ->setChecked(GIOData.RealData.FASTIN1);
    ui->checkBoxFASTIN2 ->setChecked(GIOData.RealData.FASTIN2);
    ui->checkBoxFASTIN3 ->setChecked(GIOData.RealData.FASTIN3);
    ui->checkBoxFASTIN4 ->setChecked(GIOData.RealData.FASTIN4);
    ui->checkBoxFASTIN5 ->setChecked(GIOData.RealData.FASTIN5);
    ui->checkBoxFASTIN6 ->setChecked(GIOData.RealData.FASTIN6);
    ui->checkBoxFASTIN7 ->setChecked(GIOData.RealData.FASTIN7);

    if(ui->toolButtonTestMode->isChecked()==false){
        ui->checkBoxoGOUT0 ->setChecked(GIOData.RealData.GOUT0);
        ui->checkBoxoGOUT1 ->setChecked(GIOData.RealData.GOUT1);
        ui->checkBoxoGOUT2 ->setChecked(GIOData.RealData.GOUT2);
        ui->checkBoxoGOUT3 ->setChecked(GIOData.RealData.GOUT3);
        ui->checkBoxoGOUT4 ->setChecked(GIOData.RealData.GOUT4);
        ui->checkBoxoGOUT5 ->setChecked(GIOData.RealData.GOUT5);
        ui->checkBoxoGOUT6 ->setChecked(GIOData.RealData.GOUT6);
        ui->checkBoxoGOUT7 ->setChecked(GIOData.RealData.GOUT7);
        ui->checkBoxoGOUT8 ->setChecked(GIOData.RealData.GOUT8);
        ui->checkBoxoGOUT9 ->setChecked(GIOData.RealData.GOUT9);
        ui->checkBoxoGOUT10->setChecked(GIOData.RealData.GOUT10);
        ui->checkBoxoGOUT11->setChecked(GIOData.RealData.GOUT11);
        ui->checkBoxoGOUT12->setChecked(GIOData.RealData.GOUT12);
        ui->checkBoxoGOUT13->setChecked(GIOData.RealData.GOUT13);
        ui->checkBoxoGOUT14->setChecked(GIOData.RealData.GOUT14);
        ui->checkBoxoGOUT15->setChecked(GIOData.RealData.GOUT15);

        ui->checkBoxoCamFrameTrigger->setChecked(GIOData.RealData.CamFrameTrigger);
        ui->checkBoxoCamLineTrigger ->setChecked(GIOData.RealData.CamLineTrigger);
        ui->checkBoxoCamOut0        ->setChecked(GIOData.RealData.CamOut0);
        ui->checkBoxoCamOut1        ->setChecked(GIOData.RealData.CamOut1);
    }

    QString s=QString::number(GIOData.MotorPulseCounter);
    ui->labelMotorPulseCounter->setText(s);

    AddedAverage  +=GIOData.MotorPulseCounter;
    AverageCounter++;
    if(AverageCounter>=10){
        int AvrCounter=AddedAverage/AverageCounter;
        AddedAverage=0;
        AverageCounter=0;
        if(AvrCounter>100){
        }
    }
}

void    LEDControl16FRasPiKDSBelt::SendLightInfo(SocketClient *s)
{
    BYTE    Data[100];
    Data[0]=LightBoardCount;
    s->SendOut(-1,'U',Data ,1);
}

void    LEDControl16FRasPiKDSBelt::InitialSignal(void)
{
    if (wiringPiSetupGpio() < 0) {
        printf("GPIO ERROR\n");
        return;
    }
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(14,OUTPUT);
    pinMode(15,OUTPUT);
    pinMode(16,OUTPUT);
    pinMode(17,OUTPUT);


    pinMode(22,INPUT);
    pinMode(23,INPUT);
    pinMode(24,INPUT);
    pinMode(25,INPUT);
    pinMode(27,OUTPUT);

    pullUpDnControl(22,PUD_DOWN);
    pullUpDnControl(23,PUD_DOWN);
    pullUpDnControl(24,PUD_DOWN);
    pullUpDnControl(25,PUD_DOWN);

    digitalWrite(2 , 0);
    digitalWrite(3 , 0);
    digitalWrite(4 , 0);
    digitalWrite(5 , 0);
    digitalWrite(6 , 0);
    digitalWrite(7 , 0);
    digitalWrite(8 , 0);
    digitalWrite(9 , 0);
    digitalWrite(11, 0);
    digitalWrite(12, 0);
    digitalWrite(13, 0);
    digitalWrite(14, 0);
    digitalWrite(15, 0);
    digitalWrite(16, 0);
    digitalWrite(17, 0);


    digitalWrite(27, 1);

    digitalWrite(21, 1);
    delay(1000);
    digitalWrite(21, 0);

    digitalWrite(10, 1);    //Reset
    delay(1000);
    digitalWrite(10, 0);    //Reset Off
}

void LEDControl16FRasPiKDSBelt::on_toolButtonTestMode_clicked()
{
    GIOData.TestMode    =ui->toolButtonTestMode->isChecked();

    if(GIOData.TestMode==true){
        ui->widgetTestMode->setEnabled(true);
    }
    else{
        ui->widgetTestMode->setEnabled(false);
    }
}

void LEDControl16FRasPiKDSBelt::SendStartSequence(bool b)
{
    GIOData.RegStartSequence=b;
    ui->toolButtonStartSequence->setChecked(b);
    on_toolButtonStartSequence_clicked();
}

void LEDControl16FRasPiKDSBelt::on_toolButtonStartSequence_clicked()
{
    int	Data[50];

    GIOData.RegStartSequence=(ui->toolButtonStartSequence->isChecked()==true)?true:false;
    Data[0]= (GIOData.RegLEDOut[0]==true?0x08:0)
            +(GIOData.RegLEDOut[1]==true?0x10:0)
            +(GIOData.TestMode==true?0x04:0)
            +(GIOData.TestLEDReg==true?0x02:0)
            +(GIOData.RegStartSequence==true?0x01:0);


    WriteRegister(DipSW_GIO ,Data,1);
}
void    LEDControl16FRasPiKDSBelt::SendLineCount(int MaxLines)
{
    ui->spinBoxLineCount->setValue(MaxLines);
    WriteGIO(DipSW_GIO);
}
