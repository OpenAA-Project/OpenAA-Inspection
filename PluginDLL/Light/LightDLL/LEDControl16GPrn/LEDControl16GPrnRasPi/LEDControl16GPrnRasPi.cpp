#include "LEDControl16GPrnRasPi.h"
#include "ui_LEDControl16GPrnRasPi.h"
#include <wiringPi.h>
#include <QFile>
#include "XTypeDef.h"
#include "XCriticalFunc.h"
#include "ShowLEDControl16GForm.h"
#include "LightDeviceStruct.h"
#include "GioTestModeDialog.h"
#include "TimingChartForm.h"

SocketClient::SocketClient(LEDControl16GPrnRasPi *parent ,QTcpSocket *s)
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
        struct  GioFixedStruct  Data;
        if(DataLen==sizeof(Data)){
            if(Socket->read((char *)&Data,sizeof(Data))==sizeof(Data)){
                Parent->GIOData.GioFixedData=Data;
            }
        }
        else{
             QByteArray A=Socket->readAll();
        }
    }
    else if(Cmd=='B'){
        QByteArray Dummy=Socket->readAll();
        SendOut(-1,'B' ,(BYTE *)&Parent->GIOData.GioFixedData ,sizeof(Parent->GIOData.GioFixedData));
    }
    else if(Cmd=='C'){
        QByteArray Dummy=Socket->readAll();
        int Len=Parent->PointCount;
        if(Len>=255)
            Len=255;
        BYTE    Data[12*256+10];
        Data[0]=Len;
        int R=1;
        int     P=Parent->GetFirstTimingPoint();
        for(int i=0;i<Len;i++){
            struct  TimingData	*k=Parent->GetTiming(P+i);
            memcpy(&Data[R],k,sizeof(struct TimingData));
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
ThreadIORead::ThreadIORead(LEDControl16GPrnRasPi *p,QObject *parent)
    :QThread(parent),PiParent(p)
{
    Terminated=false;
}

void    ThreadIORead::run()
{
    while(Terminated==false){
        PiParent->ReadIOUpdate();
        usleep(100);
    }
}

//-------------------------------------------------------------------
static  QString     SettingGIOFileName="MiconFIOSetting.dat";
int		Error;

LEDControl16GPrnRasPi::LEDControl16GPrnRasPi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LEDControl16GPrnRasPi),Server(this)
{
    ui->setupUi(this);
    
     if (wiringPiSetupGpio() < 0) {
        printf("GPIO ERROR\n");
        return;
    }
    LastSubFrameTriggerCounter=0;
    AllocCount  =100000;
    RingBuffer  =new struct  TimingData[AllocCount];
    ClearTiming();

    LightBoardCount =0;

    if(!connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()))){
    	Error++;
    }
    if(Server.listen(QHostAddress::Any,12777)==false){
    	Error++;
    }

	memset(&GIOData,0,sizeof(GIOData));
    QFile   File(SettingGIOFileName);
    if(File.open(QIODevice::ReadOnly)==true){
        if(GIOData.Load(&File)==true){
        	SetGIODataToWindow();
        }
    }
    InitialSignal();
    WriteInitial();
    GIOData.ResetCounter=false;
    AverageCounter  =0;
    AddedAverage    =0;
    SubFrameTriggerCounter  =0;

    LightF=new ShowLEDControl16GForm(this);
    LightF->show();

    on_toolButtonTestMode_clicked();

    TimingForm  =new TimingChartForm(this);
    TimingForm->show();


    ThreadIOReadInst=new ThreadIORead(this,this);
    ThreadIOReadInst->start();

    TM.setInterval(30);
    TM.setSingleShot(false);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
    TM.start();
}

LEDControl16GPrnRasPi::~LEDControl16GPrnRasPi()
{
    delete ui;
    delete  []RingBuffer;
    RingBuffer=NULL;

    delete  TimingForm;
    TimingForm=NULL;
}


void	LEDControl16GPrnRasPi::GetGIODataFromWindow(void)
{
    GIOData.GioFixedData.ConveyerLength		=ui->spinBoxConveyerLength	->value();
    GIOData.GioFixedData.GateOpenTerm		=ui->spinBoxGateOpenTerm	->value();
    GIOData.GioFixedData.MulInputA			=ui->spinBoxMulInputA		->value();
    GIOData.GioFixedData.MulInputB			=ui->spinBoxMulInputB		->value();
    GIOData.GioFixedData.TriggerFilterMinOFF=ui->spinBoxMinOFF			->value();
    GIOData.GioFixedData.TriggerFilterMinON	=ui->spinBoxMinON			->value();
    GIOData.GioFixedData.DelayFrameTriggerA	=ui->spinBoxDelayFrameTriggerA	->value();
    GIOData.GioFixedData.DelayFrameTriggerB	=ui->spinBoxDelayFrameTriggerB	->value();
    GIOData.GioFixedData.DelayFrameTriggerC	=ui->spinBoxDelayFrameTriggerC	->value();
    GIOData.GioFixedData.DelayFrameTriggerD	=ui->spinBoxDelayFrameTriggerD	->value();
    GIOData.GioFixedData.DefDelayedCount	=ui->spinBoxDefDelayedCount	->value();
    GIOData.GioFixedData.TriggerDelayParameter	=ui->doubleSpinBoxTriggerDelayParameter	->value();
    GIOData.GioFixedData.ResultOutParameter     =ui->doubleSpinBoxResultOutParameter	->value();

    GIOData.GioFixedData.FlipFrameTriggerModeA  =ui->checkBoxFlipFrameTriggerA->isChecked();
    GIOData.GioFixedData.FlipFrameTriggerModeB  =ui->checkBoxFlipFrameTriggerB->isChecked();
    GIOData.GioFixedData.FlipFrameTriggerModeC  =ui->checkBoxFlipFrameTriggerC->isChecked();
    GIOData.GioFixedData.FlipFrameTriggerModeD  =ui->checkBoxFlipFrameTriggerD->isChecked();

    if(ui->toolButtonTestMode->isChecked()==true){
        GIOData.RealData.GOUT0  =ui->checkBoxoGOUT0 ->isChecked();
        GIOData.RealData.GOUT1  =ui->checkBoxoGOUT1 ->isChecked();
        GIOData.RealData.GOUT2  =ui->checkBoxoGOUT2 ->isChecked();
        GIOData.RealData.GOUT3  =ui->checkBoxoGOUT3 ->isChecked();
        GIOData.RealData.GOUT4  =ui->checkBoxoGOUT4 ->isChecked();
        GIOData.RealData.GOUT5  =ui->checkBoxoGOUT5 ->isChecked();
        GIOData.RealData.GOUT6  =ui->checkBoxoGOUT6 ->isChecked();
        GIOData.RealData.GOUT7  =ui->checkBoxoGOUT7 ->isChecked();

        GIOData.RealData.PIOAOUT0=ui->checkBoxPIOAOUT0->isChecked();
        GIOData.RealData.PIOAOUT1=ui->checkBoxPIOAOUT1->isChecked();
        GIOData.RealData.PIOAOUT2=ui->checkBoxPIOAOUT2->isChecked();
        GIOData.RealData.PIOAOUT3=ui->checkBoxPIOAOUT3->isChecked();

        GIOData.RealData.PIOBOUT0=ui->checkBoxPIOBOUT0->isChecked();
        GIOData.RealData.PIOBOUT1=ui->checkBoxPIOBOUT1->isChecked();
        GIOData.RealData.PIOBOUT2=ui->checkBoxPIOBOUT2->isChecked();
        GIOData.RealData.PIOBOUT3=ui->checkBoxPIOBOUT3->isChecked();

        GIOData.RealData.PIOCOUT0=ui->checkBoxPIOCOUT0->isChecked();
        GIOData.RealData.PIOCOUT1=ui->checkBoxPIOCOUT1->isChecked();
        GIOData.RealData.PIOCOUT2=ui->checkBoxPIOCOUT2->isChecked();
        GIOData.RealData.PIOCOUT3=ui->checkBoxPIOCOUT3->isChecked();

        GIOData.RealData.PIODOUT0=ui->checkBoxPIODOUT0->isChecked();
        GIOData.RealData.PIODOUT1=ui->checkBoxPIODOUT1->isChecked();
        GIOData.RealData.PIODOUT2=ui->checkBoxPIODOUT2->isChecked();
        GIOData.RealData.PIODOUT3=ui->checkBoxPIODOUT3->isChecked();

        GIOData.TRGAOUT =((ui->checkBoxTRGAOUT0->isChecked()==true)?0x01:0)
                        +((ui->checkBoxTRGAOUT1->isChecked()==true)?0x02:0)
                        +((ui->checkBoxTRGAOUT2->isChecked()==true)?0x04:0)
                        +((ui->checkBoxTRGAOUT3->isChecked()==true)?0x08:0);
        GIOData.TRGBOUT =((ui->checkBoxTRGBOUT0->isChecked()==true)?0x01:0)
                        +((ui->checkBoxTRGBOUT1->isChecked()==true)?0x02:0)
                        +((ui->checkBoxTRGBOUT2->isChecked()==true)?0x04:0)
                        +((ui->checkBoxTRGBOUT3->isChecked()==true)?0x08:0);
        GIOData.TRGCOUT =((ui->checkBoxTRGCOUT0->isChecked()==true)?0x01:0)
                        +((ui->checkBoxTRGCOUT1->isChecked()==true)?0x02:0)
                        +((ui->checkBoxTRGCOUT2->isChecked()==true)?0x04:0)
                        +((ui->checkBoxTRGCOUT3->isChecked()==true)?0x08:0);
        GIOData.TRGDOUT =((ui->checkBoxTRGDOUT0->isChecked()==true)?0x01:0)
                        +((ui->checkBoxTRGDOUT1->isChecked()==true)?0x02:0)
                        +((ui->checkBoxTRGDOUT2->isChecked()==true)?0x04:0)
                        +((ui->checkBoxTRGDOUT3->isChecked()==true)?0x08:0);
    }
}
void	LEDControl16GPrnRasPi::SetGIODataToWindow(void)
{
    ui->spinBoxConveyerLength	->setValue(GIOData.GioFixedData.ConveyerLength	);
    ui->spinBoxGateOpenTerm		->setValue(GIOData.GioFixedData.GateOpenTerm	);
    ui->spinBoxMulInputA		->setValue(GIOData.GioFixedData.MulInputA		);
    ui->spinBoxMulInputB		->setValue(GIOData.GioFixedData.MulInputB		);
    ui->spinBoxMinOFF			->setValue(GIOData.GioFixedData.TriggerFilterMinOFF	);
    ui->spinBoxMinON			->setValue(GIOData.GioFixedData.TriggerFilterMinON	);
    ui->spinBoxDelayFrameTriggerA	->setValue(GIOData.GioFixedData.DelayFrameTriggerA);
    ui->spinBoxDelayFrameTriggerB	->setValue(GIOData.GioFixedData.DelayFrameTriggerB);
    ui->spinBoxDelayFrameTriggerC	->setValue(GIOData.GioFixedData.DelayFrameTriggerC);
    ui->spinBoxDelayFrameTriggerD	->setValue(GIOData.GioFixedData.DelayFrameTriggerD);
    ui->spinBoxDefDelayedCount	->setValue(GIOData.GioFixedData.DefDelayedCount);
    ui->doubleSpinBoxTriggerDelayParameter	->setValue(GIOData.GioFixedData.TriggerDelayParameter);
    ui->doubleSpinBoxResultOutParameter     ->setValue(GIOData.GioFixedData.ResultOutParameter);

    ui->checkBoxFlipFrameTriggerA->setChecked(GIOData.GioFixedData.FlipFrameTriggerModeA);
    ui->checkBoxFlipFrameTriggerB->setChecked(GIOData.GioFixedData.FlipFrameTriggerModeB);
    ui->checkBoxFlipFrameTriggerC->setChecked(GIOData.GioFixedData.FlipFrameTriggerModeC);
    ui->checkBoxFlipFrameTriggerD->setChecked(GIOData.GioFixedData.FlipFrameTriggerModeD);

    ui->checkBoxTRGAOUT0->setChecked(((GIOData.TRGAOUT&0x01)!=0)?true:false);
    ui->checkBoxTRGAOUT1->setChecked(((GIOData.TRGAOUT&0x02)!=0)?true:false);
    ui->checkBoxTRGAOUT2->setChecked(((GIOData.TRGAOUT&0x04)!=0)?true:false);
    ui->checkBoxTRGAOUT3->setChecked(((GIOData.TRGAOUT&0x08)!=0)?true:false);
    ui->checkBoxTRGBOUT0->setChecked(((GIOData.TRGBOUT&0x01)!=0)?true:false);
    ui->checkBoxTRGBOUT1->setChecked(((GIOData.TRGBOUT&0x02)!=0)?true:false);
    ui->checkBoxTRGBOUT2->setChecked(((GIOData.TRGBOUT&0x04)!=0)?true:false);
    ui->checkBoxTRGBOUT3->setChecked(((GIOData.TRGBOUT&0x08)!=0)?true:false);
    ui->checkBoxTRGCOUT0->setChecked(((GIOData.TRGCOUT&0x01)!=0)?true:false);
    ui->checkBoxTRGCOUT1->setChecked(((GIOData.TRGCOUT&0x02)!=0)?true:false);
    ui->checkBoxTRGCOUT2->setChecked(((GIOData.TRGCOUT&0x04)!=0)?true:false);
    ui->checkBoxTRGCOUT3->setChecked(((GIOData.TRGCOUT&0x08)!=0)?true:false);
    ui->checkBoxTRGDOUT0->setChecked(((GIOData.TRGDOUT&0x01)!=0)?true:false);
    ui->checkBoxTRGDOUT1->setChecked(((GIOData.TRGDOUT&0x02)!=0)?true:false);
    ui->checkBoxTRGDOUT2->setChecked(((GIOData.TRGDOUT&0x04)!=0)?true:false);
    ui->checkBoxTRGDOUT3->setChecked(((GIOData.TRGDOUT&0x08)!=0)?true:false);
}

void LEDControl16GPrnRasPi::on_pushButtonSendFrameTrigger_clicked()
{
	GetGIODataFromWindow();
    WriteGIO(DipSW_GIO);
}

void LEDControl16GPrnRasPi::on_pushButtonSaveSetting_clicked()
{
    GetGIODataFromWindow();

    QFile   File(SettingGIOFileName);
    if(File.open(QIODevice::WriteOnly)==true){
        if(GIOData.Save(&File)==false){
            return;
        }
    }
}

void    LEDControl16GPrnRasPi::WriteInitial(void)
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

void    LEDControl16GPrnRasPi::SlotNewConnection()
{

    QTcpSocket *s=Server.nextPendingConnection ();
    SocketClient    *Sock=new SocketClient(this ,s);
    AccessMutex.lock();
    ClientList.AppendList(Sock);
    AccessMutex.unlock();

    //ui->checkBoxConnecting->setChecked(true);
}


void    LEDControl16GPrnRasPi::DisconnectClient(SocketClient *s)
{
    AccessMutex.lock();
    ClientList.RemoveList(s);
    AccessMutex.unlock();
    s->deleteLater();

    //ui->checkBoxConnecting->setChecked(false);
}

void    LEDControl16GPrnRasPi::ReceiveData(struct GioFixedStruct &data)
{
    GIOData.GioFixedData=data;
    WriteGIO(DipSW_GIO);
}
void LEDControl16GPrnRasPi::WriteGIO(void)
{
    WriteGIO(DipSW_GIO);
}
void LEDControl16GPrnRasPi::WriteGIO(int DipSW)
{
    int	Data[50];

    IOMutex.lock();

    Data[0]= (GIOData.RegLEDOut[0]==true?0x40:0)
            +(GIOData.RegLEDOut[1]==true?0x80:0)
            +(GIOData.TestMode==true?0x20:0)
            +(GIOData.TestLEDReg==true?0x10:0)
            +(GIOData.RMode&0x0F);
    Data[1]= (GIOData.AD_CS ==true?0x08:0)
            +(GIOData.AD_DIN==true?0x04:0)
            +(GIOData.AD_CLK==true?0x02:0)
            +(GIOData.ResetCounter==true?0x01:0);
    Data[2]= (GIOData.RealData.GOUT0==true?0x01:0)
    		+(GIOData.RealData.GOUT1==true?0x02:0)
    		+(GIOData.RealData.GOUT2==true?0x04:0)
    		+(GIOData.RealData.GOUT3==true?0x08:0)
    		+(GIOData.RealData.GOUT4==true?0x10:0)
    		+(GIOData.RealData.GOUT5==true?0x20:0)
    		+(GIOData.RealData.GOUT6==true?0x40:0)
    		+(GIOData.RealData.GOUT7==true?0x80:0);
    Data[3]= (GIOData.RealData.PIOAOUT0==true?0x01:0)
    		+(GIOData.RealData.PIOAOUT1==true?0x02:0)
    		+(GIOData.RealData.PIOAOUT2==true?0x04:0)
    		+(GIOData.RealData.PIOAOUT3==true?0x08:0)
    		+(GIOData.RealData.PIOBOUT0==true?0x10:0)
    		+(GIOData.RealData.PIOBOUT1==true?0x20:0)
    		+(GIOData.RealData.PIOBOUT2==true?0x40:0)
    		+(GIOData.RealData.PIOBOUT3==true?0x80:0);
    Data[4]= (GIOData.RealData.PIOCOUT0==true?0x01:0)
    		+(GIOData.RealData.PIOCOUT1==true?0x02:0)
    		+(GIOData.RealData.PIOCOUT2==true?0x04:0)
    		+(GIOData.RealData.PIOCOUT3==true?0x08:0)
    		+(GIOData.RealData.PIODOUT0==true?0x10:0)
    		+(GIOData.RealData.PIODOUT1==true?0x20:0)
    		+(GIOData.RealData.PIODOUT2==true?0x40:0)
    		+(GIOData.RealData.PIODOUT3==true?0x80:0);
    Data[5]=(GIOData.TRGAOUT&0x0F) + (GIOData.TRGBOUT<<4);
    Data[6]=(GIOData.TRGCOUT&0x0F) + (GIOData.TRGDOUT<<4);
    Data[7] = GIOData.GioFixedData.MulInputA & 0xFF;
    Data[8] =(GIOData.GioFixedData.MulInputA>>8) & 0xFF;
    Data[9] =((GIOData.GioFixedData.MulInputA>>16) & 0x0F) + (GIOData.ModePulseHalfA==true?0x10:0);
    Data[10]= GIOData.GioFixedData.MulInputB & 0xFF;
    Data[11]=(GIOData.GioFixedData.MulInputB>>8) & 0xFF;
    Data[12]=((GIOData.GioFixedData.MulInputB>>16) & 0x0F) + (GIOData.ModePulseHalfB==true?0x10:0);
    Data[13]= GIOData.GioFixedData.TriggerFilterMinOFF & 0xFF;
    Data[14]=(GIOData.GioFixedData.TriggerFilterMinOFF>>8) & 0xFF;
    Data[15]= GIOData.GioFixedData.TriggerFilterMinON & 0xFF;
    Data[16]=(GIOData.GioFixedData.TriggerFilterMinON>>8) & 0xFF;

    int	DelayFrameTriggerA=GIOData.GioFixedData.DelayFrameTriggerA - SubFrameTriggerCounter;
    int	DelayFrameTriggerB=GIOData.GioFixedData.DelayFrameTriggerB - SubFrameTriggerCounter;
    int	DelayFrameTriggerC=GIOData.GioFixedData.DelayFrameTriggerC - SubFrameTriggerCounter;
    int	DelayFrameTriggerD=GIOData.GioFixedData.DelayFrameTriggerD - SubFrameTriggerCounter;

   	Data[17]= DelayFrameTriggerA & 0xFF;
    Data[18]=(DelayFrameTriggerA>>8) & 0xFF;
   	Data[19]= DelayFrameTriggerB & 0xFF;
    Data[20]=(DelayFrameTriggerB>>8) & 0xFF;
   	Data[21]= DelayFrameTriggerC & 0xFF;
    Data[22]=(DelayFrameTriggerC>>8) & 0xFF;
   	Data[23]= DelayFrameTriggerD & 0xFF;
    Data[24]=(DelayFrameTriggerD>>8) & 0xFF;


    //int	ResultAAcceptStart=GIOData.GioFixedData.ResultAAcceptStart - SubFrameTriggerCounter16;
    //int	ResultACloseAccept=GIOData.GioFixedData.ResultAAcceptStart - SubFrameTriggerCounter16;
    //int	ResultBAcceptStart=GIOData.GioFixedData.ResultBAcceptStart - SubFrameTriggerCounter16;
    //int	ResultBCloseAccept=GIOData.GioFixedData.ResultBAcceptStart - SubFrameTriggerCounter16;
    //int	ResultCAcceptStart=GIOData.GioFixedData.ResultCAcceptStart - SubFrameTriggerCounter16;
    //int	ResultCCloseAccept=GIOData.GioFixedData.ResultCAcceptStart - SubFrameTriggerCounter16;
    //int	ResultDAcceptStart=GIOData.GioFixedData.ResultDAcceptStart - SubFrameTriggerCounter16;
    //int	ResultDCloseAccept=GIOData.GioFixedData.ResultDAcceptStart - SubFrameTriggerCounter16;

    int	DefDelayedCount=GIOData.GioFixedData.DefDelayedCount + SubResultOutCounter16;

    Data[25]= DefDelayedCount & 0xFF;
    Data[26]=(DefDelayedCount>>8) & 0xFF;

    int	ConveyerLength	=GIOData.GioFixedData.ConveyerLength - SubResultOutCounter16;
    int	GateOpenTerm	=GIOData.GioFixedData.GateOpenTerm;
	
    Data[27]= ConveyerLength & 0xFF;
    Data[28]=(ConveyerLength>>8) & 0xFF;
    Data[29]=0;
    Data[30]= GateOpenTerm & 0xFF;
    Data[31]=(GateOpenTerm>>8) & 0xFF;

    Data[32]=((GIOData.GioFixedData.FlipFrameTriggerModeA==true)?0x01:0)
            +((GIOData.GioFixedData.FlipFrameTriggerModeB==true)?0x02:0)
            +((GIOData.GioFixedData.FlipFrameTriggerModeC==true)?0x04:0)
            +((GIOData.GioFixedData.FlipFrameTriggerModeD==true)?0x08:0);

    WriteRegister(DipSW ,Data,33);
    IOMutex.unlock();
}
void LEDControl16GPrnRasPi::ReadGIO(int DipSW)
{
    int	Data[50];

    GIOData.RMode=0;
    //Data[0]= (GIOData.RegLEDOut[0]==true?0x40:0)
    //        +(GIOData.RegLEDOut[1]==true?0x80:0)
    //        +(GIOData.TestMode==true?0x20:0)
    //        +(GIOData.TestLEDReg==true?0x10:0)
    //        +(GIOData.RMode&0x0F);

    //WriteRegister(DipSW ,Data,1);
    IOMutex.lock();
    ReadRegister4Bit(DipSW ,Data ,48);

    GIOData.RealData.TRGIN0	=(Data[1]&0x01)!=0?true:false;
   	GIOData.RealData.TRGIN1	=(Data[1]&0x02)!=0?true:false;
    GIOData.RealData.TRGIN2	=(Data[1]&0x04)!=0?true:false;
    GIOData.RealData.TRGIN3	=(Data[1]&0x08)!=0?true:false;
    GIOData.RealData.PIOAIN0=(Data[2]&0x01)!=0?true:false;
    GIOData.RealData.PIOAIN1=(Data[2]&0x02)!=0?true:false;
    GIOData.RealData.PIOAIN2=(Data[2]&0x04)!=0?true:false;
    GIOData.RealData.PIOAIN3=(Data[2]&0x08)!=0?true:false;
    GIOData.RealData.PIOBIN0=(Data[3]&0x01)!=0?true:false;
    GIOData.RealData.PIOBIN1=(Data[3]&0x02)!=0?true:false;
    GIOData.RealData.PIOBIN2=(Data[3]&0x04)!=0?true:false;
    GIOData.RealData.PIOBIN3=(Data[3]&0x08)!=0?true:false;
    GIOData.RealData.PIOCIN0=(Data[4]&0x01)!=0?true:false;
    GIOData.RealData.PIOCIN1=(Data[4]&0x02)!=0?true:false;
    GIOData.RealData.PIOCIN2=(Data[4]&0x04)!=0?true:false;
    GIOData.RealData.PIOCIN3=(Data[4]&0x08)!=0?true:false;
    GIOData.RealData.PIODIN0=(Data[5]&0x01)!=0?true:false;
    GIOData.RealData.PIODIN1=(Data[5]&0x02)!=0?true:false;
    GIOData.RealData.PIODIN2=(Data[5]&0x04)!=0?true:false;
    GIOData.RealData.PIODIN3=(Data[5]&0x08)!=0?true:false;
    GIOData.RealData.GIN0	=(Data[6]&0x01)!=0?true:false;
    GIOData.RealData.GIN1	=(Data[6]&0x02)!=0?true:false;
    GIOData.RealData.GIN2	=(Data[6]&0x04)!=0?true:false;
    GIOData.RealData.GIN3	=(Data[6]&0x08)!=0?true:false;
    GIOData.RealData.GOUT0	=(Data[7]&0x01)!=0?true:false;
    GIOData.RealData.GOUT1	=(Data[7]&0x02)!=0?true:false;
    GIOData.RealData.GOUT2	=(Data[7]&0x04)!=0?true:false;
    GIOData.RealData.GOUT3	=(Data[7]&0x08)!=0?true:false;
    GIOData.RealData.GOUT4	=(Data[8]&0x01)!=0?true:false;
    GIOData.RealData.GOUT5	=(Data[8]&0x02)!=0?true:false;
    GIOData.RealData.GOUT6	=(Data[8]&0x04)!=0?true:false;
    GIOData.RealData.GOUT7	=(Data[8]&0x08)!=0?true:false;
    GIOData.RealData.PIOAOUT0=(Data[9]&0x01)!=0?true:false;
    GIOData.RealData.PIOAOUT1=(Data[9]&0x02)!=0?true:false;
    GIOData.RealData.PIOAOUT2=(Data[9]&0x04)!=0?true:false;
    GIOData.RealData.PIOAOUT3=(Data[9]&0x08)!=0?true:false;
    GIOData.RealData.PIOBOUT0=(Data[10]&0x01)!=0?true:false;
    GIOData.RealData.PIOBOUT1=(Data[10]&0x02)!=0?true:false;
    GIOData.RealData.PIOBOUT2=(Data[10]&0x04)!=0?true:false;
    GIOData.RealData.PIOBOUT3=(Data[10]&0x08)!=0?true:false;
    GIOData.RealData.PIOCOUT0=(Data[11]&0x01)!=0?true:false;
    GIOData.RealData.PIOCOUT1=(Data[11]&0x02)!=0?true:false;
    GIOData.RealData.PIOCOUT2=(Data[11]&0x04)!=0?true:false;
    GIOData.RealData.PIOCOUT3=(Data[11]&0x08)!=0?true:false;
    GIOData.RealData.PIODOUT0=(Data[12]&0x01)!=0?true:false;
    GIOData.RealData.PIODOUT1=(Data[12]&0x02)!=0?true:false;
    GIOData.RealData.PIODOUT2=(Data[12]&0x04)!=0?true:false;
    GIOData.RealData.PIODOUT3=(Data[12]&0x08)!=0?true:false;
    GIOData.TRGAOUT         =Data[13];
    GIOData.TRGBOUT         =Data[14];
    GIOData.TRGCOUT         =Data[15];
    GIOData.TRGDOUT         =Data[16];
    GIOData.AD_DOUT         =((Data[17]&0x01)!=0)?true:false;
    GIOData.RealData.OuterSW    =((Data[17]&0x02)!=0)?true:false;
    GIOData.RealData.ExtDirect	=((Data[17]&0x04)!=0)?true:false;
	
    GIOData.MotorPulseCounter
                    = ((unsigned long)Data[18])
                    +(((unsigned long)Data[19])<<4)
                    +(((unsigned long)Data[20])<<8)
                    +(((unsigned long)Data[21])<<12)
                    +(((unsigned long)Data[22])<<16);
    GIOData.MotorPulseCounter2
                    = ((unsigned long)Data[23])
                    +(((unsigned long)Data[24])<<4)
                    +(((unsigned long)Data[25])<<8)
                    +(((unsigned long)Data[26])<<12)
                    +(((unsigned long)Data[27])<<16);

    GIOData.TotalCount
                    = ((unsigned long)Data[28])
                    +(((unsigned long)Data[29])<<4)
                    +(((unsigned long)Data[30])<<8)
                    +(((unsigned long)Data[31])<<12)
                    +(((unsigned long)Data[32])<<16);
    GIOData.OKCount
                    = ((unsigned long)Data[33])
                    +(((unsigned long)Data[34])<<4)
                    +(((unsigned long)Data[35])<<8)
                    +(((unsigned long)Data[36])<<12)
                    +(((unsigned long)Data[37])<<16);
    GIOData.NGCount
                    = ((unsigned long)Data[38])
                    +(((unsigned long)Data[39])<<4)
                    +(((unsigned long)Data[40])<<8)
                    +(((unsigned long)Data[41])<<12)
                    +(((unsigned long)Data[42])<<16);
    GIOData.TMCount
                    = ((unsigned long)Data[43])
                    +(((unsigned long)Data[44])<<4)
                    +(((unsigned long)Data[45])<<8)
                    +(((unsigned long)Data[46])<<12)
                    +(((unsigned long)Data[47])<<16);
    IOMutex.unlock();
}

void    LEDControl16GPrnRasPi::ReadIOUpdate()
{
    ReadGIO(DipSW_GIO);

    if(LastWPoint<0 || memcmp(&GIOData.RealData,&RingBuffer[LastWPoint].RealData,sizeof(GIOData.RealData))!=0){
        if(TimingForm->GetSamplingMode()==true){
            RingBuffer[WPoint].CurrentMiliSec =::GetComputerMiliSec();
            RingBuffer[WPoint].RealData=GIOData.RealData;
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

void    LEDControl16GPrnRasPi::SlotTimeOut()
{
    ui->checkBoxGIN0 ->setChecked(GIOData.RealData.GIN0);
    ui->checkBoxGIN1 ->setChecked(GIOData.RealData.GIN1);
    ui->checkBoxGIN2 ->setChecked(GIOData.RealData.GIN2);
    ui->checkBoxGIN3 ->setChecked(GIOData.RealData.GIN3);
    
    ui->checkBoxTRGIN0 ->setChecked(GIOData.RealData.TRGIN0);
    ui->checkBoxTRGIN1 ->setChecked(GIOData.RealData.TRGIN1);
    ui->checkBoxTRGIN2 ->setChecked(GIOData.RealData.TRGIN2);
    ui->checkBoxTRGIN3 ->setChecked(GIOData.RealData.TRGIN3);
    
    ui->checkBoxPIOAIN0->setChecked(GIOData.RealData.PIOAIN0);
    ui->checkBoxPIOAIN1->setChecked(GIOData.RealData.PIOAIN1);
    ui->checkBoxPIOAIN2->setChecked(GIOData.RealData.PIOAIN2);
    ui->checkBoxPIOAIN3->setChecked(GIOData.RealData.PIOAIN3);
    
    ui->checkBoxPIOBIN0->setChecked(GIOData.RealData.PIOBIN0);
    ui->checkBoxPIOBIN1->setChecked(GIOData.RealData.PIOBIN1);
    ui->checkBoxPIOBIN2->setChecked(GIOData.RealData.PIOBIN2);
    ui->checkBoxPIOBIN3->setChecked(GIOData.RealData.PIOBIN3);
    
    ui->checkBoxPIOCIN0->setChecked(GIOData.RealData.PIOCIN0);
    ui->checkBoxPIOCIN1->setChecked(GIOData.RealData.PIOCIN1);
    ui->checkBoxPIOCIN2->setChecked(GIOData.RealData.PIOCIN2);
    ui->checkBoxPIOCIN3->setChecked(GIOData.RealData.PIOCIN3);
    
    ui->checkBoxPIODIN0->setChecked(GIOData.RealData.PIODIN0);
    ui->checkBoxPIODIN1->setChecked(GIOData.RealData.PIODIN1);
    ui->checkBoxPIODIN2->setChecked(GIOData.RealData.PIODIN2);
    ui->checkBoxPIODIN3->setChecked(GIOData.RealData.PIODIN3);

    if(ui->toolButtonTestMode->isChecked()==false){
        ui->checkBoxoGOUT0->setChecked(GIOData.RealData.GOUT0);
        ui->checkBoxoGOUT1->setChecked(GIOData.RealData.GOUT1);
        ui->checkBoxoGOUT2->setChecked(GIOData.RealData.GOUT2);
        ui->checkBoxoGOUT3->setChecked(GIOData.RealData.GOUT3);

        ui->checkBoxPIOAOUT0->setChecked(GIOData.RealData.PIOAOUT0);
        ui->checkBoxPIOAOUT1->setChecked(GIOData.RealData.PIOAOUT1);
        ui->checkBoxPIOAOUT2->setChecked(GIOData.RealData.PIOAOUT2);
        ui->checkBoxPIOAOUT3->setChecked(GIOData.RealData.PIOAOUT3);

        ui->checkBoxPIOBOUT0->setChecked(GIOData.RealData.PIOBOUT0);
        ui->checkBoxPIOBOUT1->setChecked(GIOData.RealData.PIOBOUT1);
        ui->checkBoxPIOBOUT2->setChecked(GIOData.RealData.PIOBOUT2);
        ui->checkBoxPIOBOUT3->setChecked(GIOData.RealData.PIOBOUT3);

        ui->checkBoxPIOCOUT0->setChecked(GIOData.RealData.PIOCOUT0);
        ui->checkBoxPIOCOUT1->setChecked(GIOData.RealData.PIOCOUT1);
        ui->checkBoxPIOCOUT2->setChecked(GIOData.RealData.PIOCOUT2);
        ui->checkBoxPIOCOUT3->setChecked(GIOData.RealData.PIOCOUT3);

        ui->checkBoxPIODOUT0->setChecked(GIOData.RealData.PIODOUT0);
        ui->checkBoxPIODOUT1->setChecked(GIOData.RealData.PIODOUT1);
        ui->checkBoxPIODOUT2->setChecked(GIOData.RealData.PIODOUT2);
        ui->checkBoxPIODOUT3->setChecked(GIOData.RealData.PIODOUT3);
    }
    else{
        GetGIODataFromWindow();
        WriteGIO(DipSW_GIO);
    }

    QString s=QString::number(GIOData.MotorPulseCounter);
    ui->labelMotorPulseCounter->setText(s);

    QString s2=QString::number(GIOData.MotorPulseCounter2);
    ui->labelMotorPulseCounter2->setText(s2);

    ui->labelTotalCount ->setText(QString::number(GIOData.TotalCount));
    ui->labelOKCount    ->setText(QString::number(GIOData.OKCount));
    ui->labelNGCount    ->setText(QString::number(GIOData.NGCount));
    ui->labelTMCount    ->setText(QString::number(GIOData.TMCount));

    IOMutex.lock();
    AddedAverage  +=GIOData.MotorPulseCounter;
    IOMutex.unlock();

    AverageCounter++;
    if(AverageCounter>=50){
        qint64 AvrCounter=AddedAverage/AverageCounter;
        AddedAverage=0;
        AverageCounter=0;
        if(AvrCounter>100){
            SubFrameTriggerCounter  =GIOData.GioFixedData.TriggerDelayParameter/AvrCounter;
            if(abs(LastSubFrameTriggerCounter-SubFrameTriggerCounter)>=10){
                LastSubFrameTriggerCounter=SubFrameTriggerCounter;
                ui->labelSubFrameTriggerCounter ->setText(QString::number(SubFrameTriggerCounter));
                SubResultOutCounter16     =(GIOData.GioFixedData.ResultOutParameter/AvrCounter)/16;
                ui->labelSubResultOutCounter    ->setText(QString::number(SubResultOutCounter16));
                WriteGIO(DipSW_GIO);
            }
        }
    }
    TimingForm->RepaintSignals();
}

void    LEDControl16GPrnRasPi::InitialSignal(void)
{
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
    pinMode(26,INPUT);
    pinMode(27,OUTPUT);

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

void    LEDControl16GPrnRasPi::SendLightInfo(SocketClient *s)
{
    BYTE    Data[100];
    Data[0]=LightBoardCount;
    s->SendOut(-1,'U',Data ,1);
}

void LEDControl16GPrnRasPi::on_toolButtonTestMode_clicked()
{
    GIOData.TestMode    =ui->toolButtonTestMode->isChecked();

    if(GIOData.TestMode==true){
        ui->widgetTestMode->setEnabled(true);
    }
    else{
        ui->widgetTestMode->setEnabled(false);
    }
}

struct  TimingData	*LEDControl16GPrnRasPi::FindTimingAhead(DWORD t)
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

struct  TimingData	*LEDControl16GPrnRasPi::GetTiming(int point)
{
    while(point<0){
        point+=AllocCount;
    }
    while(AllocCount<=point){
        point-=AllocCount;
    }
	return &RingBuffer[point];
}
int     LEDControl16GPrnRasPi::GetFirstTimingPoint(void)
{
    int     k=WPoint-PointCount;
    if(k<0)
        k+=AllocCount;
    return k;
}
int     LEDControl16GPrnRasPi::GetTimingCount(void)
{
    return PointCount;
}

void    LEDControl16GPrnRasPi::ClearTiming(void)
{
    PointCount  =0;
    WPoint      =0;
    LastWPoint  =-1;
}

void LEDControl16GPrnRasPi::on_pushButtonResetCounter_clicked()
{
    LightF->ResetCounter();
}
