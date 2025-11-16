#include "ControlFIOForm.h"
#include "ui_ControlFIOForm.h"
#include <wiringPi.h>
#include <QFile>
#include "XTypeDef.h"

IOSocketClient::IOSocketClient(ControlFIOForm *parent ,QTcpSocket *s)
{
    Parent=parent;
    Socket=s;

    connect(s,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
    connect(s,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
}

IOSocketClient::~IOSocketClient(void)
{
}

void    IOSocketClient::SlotReadyRead()
{
    //if(Socket->read((char *)&Data,sizeof(Data))==sizeof(Data)){
    //    Parent->ReceiveData(Data);
    //}
}

void    IOSocketClient::SlotDisconnected()
{
    Parent->DisconnectClient(this);
}

//-------------------------------------------------------------------

static  QString     SettingFIOFileName="MiconFIOSetting.dat";

ControlFIOForm::ControlFIOForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlFIOForm)
{
    ui->setupUi(this);
    connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
    Server.listen(QHostAddress::Any,12777);

    WriteInitial();

    AverageCounter  =0;
    AddedAverage    =0;
    SubFrameTriggerCounter  =0;

    TM.setInterval(100);
    TM.setSingleShot(false);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
    TM.start();
}

ControlFIOForm::~ControlFIOForm()
{
    delete ui;
}

void    ControlFIOForm::WriteInitial(void)
{
    DipSW_EIO=15;

    //TestWriteE(0);

    int data;
    for(int dipsw=0;dipsw<16;dipsw++){
        data=ReadBoardID(dipsw);
        if(data==10){
            DipSW_EIO=dipsw;
        }
    }
    EIOData.OutExt=0;
    EIOData.TestLEDReg=true;
    WriteEIO(DipSW_EIO);
    EIOData.TestLEDReg=false;
    WriteEIO(DipSW_EIO);
    EIOData.TestLEDReg=true;
    WriteEIO(DipSW_EIO);

    QFile   File(SettingFIOFileName);
    if(File.open(QIODevice::ReadOnly)==true){
        if(EIOData.Load(&File)==true){
            ui->spinBoxMulInput             ->setValue((int)EIOData.MulInput);
            ui->spinBoxDelayFrameTriggerA   ->setValue((int)EIOData.DelayFrameTriggerA);
            ui->spinBoxDelayFrameTriggerB   ->setValue((int)EIOData.DelayFrameTriggerB);
            ui->spinBoxFrameCycle           ->setValue((int)EIOData.FrameCycle);
            ui->spinBoxDropLength           ->setValue((int)EIOData.DropLength      );
            ui->spinBoxDropFlapONLength     ->setValue((int)EIOData.DropFlapONLength);
            ui->doubleSpinBoxTriggerDelayParameter  ->setValue(EIOData.TriggerDelayParameter);

            on_pushButtonSendFrameTrigger_clicked();
        }
    }

}

void    ControlFIOForm::SlotNewConnection()
{

    //QTcpSocket *s=Server.nextPendingConnection ();
    //IOSocketClient    *Sock=new IOSocketClient(this ,s);
    AccessMutex.lock();
    //ClientList.AppendList(Sock);
    AccessMutex.unlock();

    //ui->checkBoxConnecting->setChecked(true);
}


void    ControlFIOForm::DisconnectClient(IOSocketClient *s)
{
    AccessMutex.lock();
    ClientList.RemoveList(s);
    AccessMutex.unlock();
   // s->deleteLater();

    //ui->checkBoxConnecting->setChecked(false);
}

//void    MainWindow::ReceiveData(CamTriggerStruct &data)
//{
//}

void ControlFIOForm::WriteEIO(int DipSW)
{
    int	Data[50];

    Data[0]= (EIOData.RegLEDOut[0]==true?0x20:0)
            +(EIOData.RegLEDOut[1]==true?0x40:0)
            +(EIOData.TestLEDReg==true?0x10:0)
            +(EIOData.RMode&0x0F);
    Data[1]= EIOData.OutExt&0xFF;
    Data[2]= (EIOData.OutExt>>8)&0xFF;
    Data[3]= EIOData.Conveyer1Pulse & 0xFF;
    Data[4]=(EIOData.Conveyer1Pulse>>8) & 0xFF;
    Data[5]=(EIOData.Conveyer1Pulse>>16) & 0xFF;
    Data[6]= EIOData.MulInput & 0xFF;
    Data[7]=(EIOData.MulInput>>8) & 0xFF;
    Data[8]=(EIOData.MulInput>>16) & 0xFF;
    int DelayFrameTriggerA=EIOData.DelayFrameTriggerA-SubFrameTriggerCounter;
    if(DelayFrameTriggerA<=0)
        DelayFrameTriggerA=0;
    Data[9]= DelayFrameTriggerA & 0xFF;
    Data[10]=(DelayFrameTriggerA>>8) & 0xFF;
    Data[11]=(DelayFrameTriggerA>>16) & 0xFF;
    int DelayFrameTriggerB=EIOData.DelayFrameTriggerB-SubFrameTriggerCounter;
    if(DelayFrameTriggerB<=0)
        DelayFrameTriggerB=0;
    Data[12]= DelayFrameTriggerB & 0xFF;
    Data[13]=(DelayFrameTriggerB>>8) & 0xFF;
    Data[14]=(DelayFrameTriggerB>>16) & 0xFF;

    Data[15]=EIOData.DropFlapONLength&0xFF;
    Data[16]= EIOData.DropLength & 0xFF;
    Data[17]=(EIOData.DropLength>>8) & 0xFF;

    WriteRegister(DipSW ,Data,18);
}
void ControlFIOForm::ReadEIO(int DipSW)
{
    int	Data[50];

    EIOData.RMode=0;
    Data[0]= (EIOData.RegLEDOut[0]==true?0x20:0)
            +(EIOData.RegLEDOut[1]==true?0x40:0)
            +(EIOData.TestLEDReg==true?0x10:0)
            +(EIOData.RMode&0x0F);
    WriteRegister(DipSW ,Data,1);

    ReadRegister4Bit(DipSW ,Data ,6);
    EIOData.Conveyer1Pulse  = ((unsigned long)Data[1])
                            +(((unsigned long)Data[2])<<4)
                            +(((unsigned long)Data[3])<<8)
                            +(((unsigned long)Data[4])<<12)
                            +(((unsigned long)Data[5])<<16);

    EIOData.RMode=1;
    Data[0]= (EIOData.RegLEDOut[0]==true?0x20:0)
            +(EIOData.RegLEDOut[1]==true?0x40:0)
            +(EIOData.TestLEDReg==true?0x10:0)
            +(EIOData.RMode&0x0F);
    WriteRegister(DipSW ,Data,1);

    ReadRegister4Bit(DipSW ,Data ,6);
    EIOData.MulInput        = ((unsigned long)Data[1])
                            +(((unsigned long)Data[2])<<4)
                            +(((unsigned long)Data[3])<<8)
                            +(((unsigned long)Data[4])<<12)
                            +(((unsigned long)Data[5])<<16);

    EIOData.RMode=2;
    Data[0]= (EIOData.RegLEDOut[0]==true?0x20:0)
            +(EIOData.RegLEDOut[1]==true?0x40:0)
            +(EIOData.TestLEDReg==true?0x10:0)
            +(EIOData.RMode&0x0F);
    WriteRegister(DipSW ,Data,1);

    ReadRegister4Bit(DipSW ,Data ,7);
    EIOData.DelayFrameTriggerA=((unsigned long)Data[1])
                            +(((unsigned long)Data[2])<<4)
                            +(((unsigned long)Data[3])<<8)
                            +(((unsigned long)Data[4])<<12)
                            +(((unsigned long)Data[5])<<16)
                            +(((unsigned long)Data[6])<<20);

    EIOData.RMode=3;
    Data[0]= (EIOData.RegLEDOut[0]==true?0x20:0)
            +(EIOData.RegLEDOut[1]==true?0x40:0)
            +(EIOData.TestLEDReg==true?0x10:0)
            +(EIOData.RMode&0x0F);
    WriteRegister(DipSW ,Data,1);

    ReadRegister4Bit(DipSW ,Data ,7);
    EIOData.DelayFrameTriggerB=((unsigned long)Data[1])
                            +(((unsigned long)Data[2])<<4)
                            +(((unsigned long)Data[3])<<8)
                            +(((unsigned long)Data[4])<<12)
                            +(((unsigned long)Data[5])<<16)
                            +(((unsigned long)Data[6])<<20);

    EIOData.RMode=4;
    Data[0]= (EIOData.RegLEDOut[0]==true?0x20:0)
            +(EIOData.RegLEDOut[1]==true?0x40:0)
            +(EIOData.TestLEDReg==true?0x10:0)
            +(EIOData.RMode&0x0F);
    WriteRegister(DipSW ,Data,1);

    ReadRegister4Bit(DipSW ,Data ,6);
    EIOData.DropLength      = ((unsigned long)Data[1])
                            +(((unsigned long)Data[2])<<4)
                            +(((unsigned long)Data[3])<<8)
                            +(((unsigned long)Data[4])<<12)
                            +(((unsigned long)Data[5])<<16);

    EIOData.RMode=5;
    Data[0]= (EIOData.RegLEDOut[0]==true?0x20:0)
            +(EIOData.RegLEDOut[1]==true?0x40:0)
            +(EIOData.TestLEDReg==true?0x10:0)
            +(EIOData.RMode&0x0F);
    WriteRegister(DipSW ,Data,1);

    ReadRegister4Bit(DipSW ,Data ,6);
    EIOData.DropFlapONLength= ((unsigned long)Data[1])
                            +(((unsigned long)Data[2])<<4);


    EIOData.RMode=6;
    Data[0]= (EIOData.RegLEDOut[0]==true?0x20:0)
            +(EIOData.RegLEDOut[1]==true?0x40:0)
            +(EIOData.TestLEDReg==true?0x10:0)
            +(EIOData.RMode&0x0F);
    WriteRegister(DipSW ,Data,1);

    ReadRegister4Bit(DipSW ,Data ,6);
    EIOData.InExt           = ((unsigned long)Data[1])
                            +(((unsigned long)Data[2])<<4)
                            +(((unsigned long)Data[3])<<8)
                            +(((unsigned long)Data[4])<<12)
                            +(((unsigned long)Data[5])<<16);

}

void    ControlFIOForm::ReadInput(int DipSW ,unsigned int &tData)
{
    int	Data[50];
    EIOData.RMode=6;
    Data[0]= (EIOData.RegLEDOut[0]==true?0x20:0)
            +(EIOData.RegLEDOut[1]==true?0x40:0)
            +(EIOData.TestLEDReg==true?0x10:0)
            +(EIOData.RMode&0x0F);
    WriteRegister(DipSW ,Data,1);

    ReadRegister4Bit(DipSW ,Data ,6);
    EIOData.InExt           = ((unsigned long)Data[1])
                            +(((unsigned long)Data[2])<<4)
                            +(((unsigned long)Data[3])<<8)
                            +(((unsigned long)Data[4])<<12)
                            +(((unsigned long)Data[5])<<16);
    tData=EIOData.InExt;
}

void    ControlFIOForm::ReadMotorCounter(int DipSW,unsigned int &tData)
{
    int	Data[50];
    EIOData.RMode=8;
    Data[0]= (EIOData.RegLEDOut[0]==true?0x20:0)
            +(EIOData.RegLEDOut[1]==true?0x40:0)
            +(EIOData.TestLEDReg==true?0x10:0)
            +(EIOData.RMode&0x0F);
    WriteRegister(DipSW ,Data,1);

    ReadRegister4Bit(DipSW ,Data ,6);
    tData          = ((unsigned long)Data[1])
                    +(((unsigned long)Data[2])<<4)
                    +(((unsigned long)Data[3])<<8)
                    +(((unsigned long)Data[4])<<12)
                    +(((unsigned long)Data[5])<<16);
}

void    ControlFIOForm::SlotTimeOut()
{
    unsigned int Data;
    ReadInput(DipSW_EIO ,Data);
    ui->checkBoxIn0 ->setChecked(((Data&0x0001)!=0)?true:false);
    ui->checkBoxIn1 ->setChecked(((Data&0x0002)!=0)?true:false);
    ui->checkBoxIn2 ->setChecked(((Data&0x0004)!=0)?true:false);
    ui->checkBoxIn3 ->setChecked(((Data&0x0008)!=0)?true:false);
    ui->checkBoxIn4 ->setChecked(((Data&0x0010)!=0)?true:false);
    ui->checkBoxIn5 ->setChecked(((Data&0x0020)!=0)?true:false);
    ui->checkBoxIn6 ->setChecked(((Data&0x0040)!=0)?true:false);
    ui->checkBoxIn7 ->setChecked(((Data&0x0080)!=0)?true:false);
    ui->checkBoxIn8 ->setChecked(((Data&0x0100)!=0)?true:false);
    ui->checkBoxIn9 ->setChecked(((Data&0x0200)!=0)?true:false);
    ui->checkBoxIn10->setChecked(((Data&0x0400)!=0)?true:false);
    ui->checkBoxIn11->setChecked(((Data&0x0800)!=0)?true:false);
    ui->checkBoxIn12->setChecked(((Data&0x1000)!=0)?true:false);
    ui->checkBoxIn13->setChecked(((Data&0x2000)!=0)?true:false);
    ui->checkBoxIn14->setChecked(((Data&0x4000)!=0)?true:false);
    ui->checkBoxIn15->setChecked(((Data&0x8000)!=0)?true:false);

    ReadMotorCounter(DipSW_EIO,Data);
    QString s=QString::number(Data);
    ui->labelMotorPulseCounter->setText(s);

    AddedAverage  +=Data;
    AverageCounter++;
    if(AverageCounter>=10){
        int AvrCounter=AddedAverage/AverageCounter;
        AddedAverage=0;
        AverageCounter=0;
        if(AvrCounter>100){
            SubFrameTriggerCounter=EIOData.TriggerDelayParameter/AvrCounter;
            WriteEIO(DipSW_EIO);
        }
    }
}

int ControlFIOForm::ReadBoardID(int DipSW)
{
    digitalWrite(13 , ((DipSW&0x01)!=0)?1:0);
    digitalWrite(14 , ((DipSW&0x02)!=0)?1:0);
    digitalWrite(16 , ((DipSW&0x04)!=0)?1:0);
    digitalWrite(17 , ((DipSW&0x08)!=0)?1:0);

    digitalWrite(11 , 0);	//iRPiCmdW
    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();

    digitalWrite(15 , 1);	//iRPiStrobe

    int Data;
    ReadRegister4Bit(Data);

    digitalWrite(15 , 0);	//iRPiStrobe
    return Data;
}

void ControlFIOForm::WriteRegister(int DipSW ,int Data[] ,int DataLen)
{
    digitalWrite(13 , ((DipSW&0x01)!=0)?1:0);
    digitalWrite(14 , ((DipSW&0x02)!=0)?1:0);
    digitalWrite(16 , ((DipSW&0x04)!=0)?1:0);
    digitalWrite(17 , ((DipSW&0x08)!=0)?1:0);

    digitalWrite(11 , 1);	//iRPiCmdW
    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();

    digitalWrite(15 , 1);	//iRPiStrobe
    delay(1);
    for(int i=0;i<DataLen;i++){
        WriteRegister(Data[i]);
    }
    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();
    delay(1);
}
void ControlFIOForm::WriteRegister(int Data)
{
    digitalWrite(2 , ((Data&0x01)!=0)?1:0);
    digitalWrite(3 , ((Data&0x02)!=0)?1:0);
    digitalWrite(4 , ((Data&0x04)!=0)?1:0);
    digitalWrite(5 , ((Data&0x08)!=0)?1:0);
    digitalWrite(6 , ((Data&0x10)!=0)?1:0);
    digitalWrite(7 , ((Data&0x20)!=0)?1:0);
    digitalWrite(8 , ((Data&0x40)!=0)?1:0);
    digitalWrite(9 , ((Data&0x80)!=0)?1:0);

    delay(1);
    digitalWrite(12, 1);
    delay(1);
    digitalWrite(12, 0);
    delay(1);
}


void ControlFIOForm::ReadRegister4Bit(int DipSW ,int Data[] ,int DataLen)
{
    digitalWrite(13 , ((DipSW&0x01)!=0)?1:0);
    digitalWrite(14 , ((DipSW&0x02)!=0)?1:0);
    digitalWrite(16 , ((DipSW&0x04)!=0)?1:0);
    digitalWrite(17 , ((DipSW&0x08)!=0)?1:0);

    digitalWrite(11 , 0);	//iRPiCmdW
    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();
    digitalWrite(15 , 1);	//iRPiStrobe
    delay(1);

    for(int i=0;i<DataLen;i++){
        ReadRegister4Bit(Data[i]);
    }

    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();
    delay(1);
}

void ControlFIOForm::ReadRegister4Bit(int &Data)
{
    delay(1);
    digitalWrite(12, 1);
    delay(1);
    digitalWrite(12, 0);
    delay(1);
    int b1=digitalRead(23);
    int b2=digitalRead(24);
    int b4=digitalRead(25);
    int b8=digitalRead(26);
    Data=(b1&0x01) + ((b2&0x1)<<1) + ((b4&0x1)<<2) + ((b8&0x1)<<3);
}

void ControlFIOForm::DummyClock(void)
{
    delay(1);
    digitalWrite(12, 1);
    delay(1);
    digitalWrite(12, 0);
    delay(1);
}
void ControlFIOForm::on_pushButtonSendFrameTrigger_clicked()
{
    EIOData.DelayFrameTriggerA  =ui->spinBoxDelayFrameTriggerA  ->value();
    EIOData.DelayFrameTriggerB  =ui->spinBoxDelayFrameTriggerB  ->value();
    EIOData.MulInput =ui->spinBoxMulInput   ->value();
    EIOData.FrameCycle          =ui->spinBoxFrameCycle          ->value();
    EIOData.DropLength          =ui->spinBoxDropLength          ->value();
    EIOData.DropFlapONLength    =ui->spinBoxDropFlapONLength    ->value();
    EIOData.TriggerDelayParameter   =ui->doubleSpinBoxTriggerDelayParameter->value();

    WriteEIO(DipSW_EIO);
}

void ControlFIOForm::on_pushButtonSaveSetting_clicked()
{
    EIOData.MulInput            =ui->spinBoxMulInput   ->value();
    EIOData.DelayFrameTriggerA  =ui->spinBoxDelayFrameTriggerA  ->value();
    EIOData.DelayFrameTriggerB  =ui->spinBoxDelayFrameTriggerB  ->value();
    EIOData.FrameCycle          =ui->spinBoxFrameCycle          ->value();
    EIOData.DropLength          =ui->spinBoxDropLength          ->value();
    EIOData.DropFlapONLength    =ui->spinBoxDropFlapONLength    ->value();
    EIOData.TriggerDelayParameter   =ui->doubleSpinBoxTriggerDelayParameter->value();

    QFile   File(SettingFIOFileName);
    if(File.open(QIODevice::WriteOnly)==true){
        if(EIOData.Save(&File)==false){
            return;
        }
    }
}

void ControlFIOForm::on_pushButtonReset_clicked()
{
    digitalWrite(10, 1);    //Reset
    delay(1000);
    digitalWrite(10, 0);    //Reset Off

    WriteInitial();
}

void ControlFIOForm::on_toolButtonFlapOK_clicked()
{
    if(ui->toolButtonFlapOK->isChecked()==true)
        EIOData.OutExt |= 0x08;
    else
        EIOData.OutExt &= ~0x08;

    WriteEIO(DipSW_EIO);
}

void ControlFIOForm::on_toolButtonFlapNG_clicked()
{
    if(ui->toolButtonFlapNG->isChecked()==true)
        EIOData.OutExt |= 0x10;
    else
        EIOData.OutExt &= ~0x10;

    WriteEIO(DipSW_EIO);
}

void ControlFIOForm::on_pushButtonReceiveEIO_clicked()
{
    ReadEIO(DipSW_EIO);
    //ui->labelMulResult->setText(QString::number(EIOData.ClockInMotorPulse)
    //                          + ::GetSeparator()
    //                          + QString::number(EIOData.ResultMulH)
    //                          + QString("-")
    //                          + QString::number(EIOData.ResultMulL,16));
}


void ControlFIOForm::on_toolButtonTopOK_clicked()
{
    if(ui->toolButtonTopOK->isChecked()==true)
        EIOData.OutExt |= BitTopOK;
    else
        EIOData.OutExt &= ~BitTopOK;
}

void ControlFIOForm::on_toolButtonTopNG_clicked()
{
    if(ui->toolButtonTopNG->isChecked()==true)
        EIOData.OutExt |= BitTopNG;
    else
        EIOData.OutExt &= ~BitTopNG;
}

void ControlFIOForm::on_toolButtonBottomOK_clicked()
{
    if(ui->toolButtonBottomOK->isChecked()==true)
        EIOData.OutExt |= BitBottomOK;
    else
        EIOData.OutExt &= ~BitBottomOK;
}

void ControlFIOForm::on_toolButtonBottomNG_clicked()
{
    if(ui->toolButtonBottomNG->isChecked()==true)
        EIOData.OutExt |= BitBottomNG;
    else
        EIOData.OutExt &= ~BitBottomNG;
}
