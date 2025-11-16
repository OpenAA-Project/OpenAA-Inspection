#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <wiringPi.h>

SocketClient::SocketClient(MainWindow *parent ,QTcpSocket *s)
{
    Parent=parent;
    //Socket=s;

    //connect(s,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
    //connect(s,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
}

SocketClient::~SocketClient(void)
{
}

void    SocketClient::SlotReadyRead()
{
    //if(Socket->read((char *)&Data,sizeof(Data))==sizeof(Data)){
    //    Parent->ReceiveData(Data);
    //}
}

void    SocketClient::SlotDisconnected()
{
    Parent->DisconnectClient(this);
}

//-------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (wiringPiSetupGpio() < 0) {
        printf("GPIO ERROR\n");
        return;
    }

    //connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
    //Server.listen(QHostAddress::Any,12777);

    InitialSignal();
    DipSW_EIO=7;
    int DipSW=1;
    int Brd=1;

    //TestWriteE(0);

    int data;
    data=ReadBOardID(0);
    data=ReadBOardID(1);
    data=ReadBOardID(2);
    data=ReadBOardID(DipSW_EIO);

    EIOData.TestLEDReg=true;
    WriteEIO(DipSW_EIO);
    EIOData.TestLEDReg=false;
    WriteEIO(DipSW_EIO);
    EIOData.TestLEDReg=true;
    WriteEIO(DipSW_EIO);

    BoardData[Brd].TestLEDReg=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].TestLEDReg=false;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].TestLEDReg=true;
    WriteEForBit(DipSW ,Brd);

    int Counter;
    Counter=ReadEForBit(DipSW,Brd);
    Counter=ReadEForBit(DipSW,Brd);
    Counter=ReadEForBit(DipSW,Brd);
    Counter=ReadEForBit(DipSW,Brd);


    BoardData[Brd].LightPatternData[0].SetAllON(false);
    WriteEOnOffData(DipSW ,Brd,0);
    BoardData[Brd].CmdSetLineOn=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdSetLineOn=false;
    WriteEForBit(DipSW ,Brd);

    BoardData[Brd].LightPatternData[0].DCEnable=true;
    WriteELightData(DipSW ,Brd,0);

    ReadELightData(DipSW,0 ,0);
    BoardData[Brd].CmdLoad=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdLoad=false;
    WriteEForBit(DipSW ,Brd);

    BoardData[Brd].LightPatternData[0].LineData[0].ON=true;
    BoardData[Brd].LightPatternData[0].LineData[1].ON=true;
    WriteEOnOffData(DipSW ,Brd,0);
    BoardData[Brd].CmdSetLineOn=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdSetLineOn=false;
    WriteEForBit(DipSW ,Brd);

    BoardData[Brd].LightPatternData[0].DCEnable=false;
    WriteELightData(DipSW ,Brd,0);
    BoardData[Brd].CmdLoad=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdLoad=false;
    WriteEForBit(DipSW ,Brd);

    BoardData[Brd].LightPatternData[0].SetAllON();
    WriteEOnOffData(DipSW ,Brd,0);
    BoardData[Brd].CmdSetLineOn=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdSetLineOn=false;
    WriteEForBit(DipSW ,Brd);

    BoardData[Brd].LightPatternData[0].DCEnable=true;
    WriteELightData(DipSW ,Brd,0);
    BoardData[Brd].CmdLoad=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdLoad=false;
    WriteEForBit(DipSW ,0);

    BoardData[Brd].CmdSetAnalog=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdSetAnalog=false;
    WriteEForBit(DipSW ,Brd);

    BoardData[Brd].LightPatternData[0].SetAllON();
    WriteEOnOffData(DipSW ,Brd,0);
    BoardData[Brd].CmdSetLineOn=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdSetLineOn=false;
    WriteEForBit(DipSW ,Brd);

    BoardData[Brd].LightPatternData[0].SetAllON(false);
    WriteEOnOffData(DipSW ,Brd,0);
    BoardData[Brd].CmdSetLineOn=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdSetLineOn=false;
    WriteEForBit(DipSW ,Brd);

    for(int t=0;t<16;t++){
        for(int i=0;i<16;i++){
            BoardData[Brd].LightPatternData[0].LineData[i].ON=((i==t)?true:false);
        }
        WriteEOnOffData(DipSW ,0,0);
        BoardData[Brd].CmdSetLineOn=true;
        WriteEForBit(DipSW ,Brd);
        BoardData[Brd].CmdSetLineOn=false;
        WriteEForBit(DipSW ,Brd);
    }


    BoardData[Brd].CmdSetLineOn=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdSetLineOn=false;
    WriteEForBit(DipSW ,Brd);

    BoardData[Brd].LightPatternData[0].LineData[15].ON=false;
    BoardData[Brd].LightPatternData[0].LineData[8].ON=false;
    WriteEOnOffData(DipSW ,Brd,0);

    BoardData[Brd].CmdSetLineOn=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdSetLineOn=false;
    WriteEForBit(DipSW ,Brd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void    MainWindow::SlotNewConnection()
{

    //QTcpSocket *s=Server.nextPendingConnection ();
    //SocketClient    *Sock=new SocketClient(this ,s);
    AccessMutex.lock();
    //ClientList.AppendList(Sock);
    AccessMutex.unlock();

    //ui->checkBoxConnecting->setChecked(true);
}


void    MainWindow::DisconnectClient(SocketClient *s)
{
    AccessMutex.lock();
    ClientList.RemoveList(s);
    AccessMutex.unlock();
   // s->deleteLater();

    //ui->checkBoxConnecting->setChecked(false);
}

void    MainWindow::InitialSignal(void)
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


//void    MainWindow::ReceiveData(CamTriggerStruct &data)
//{
//}

void MainWindow::WriteEIO(int DipSW)
{
	int	Data[10];
	
	Data[0]= EIOData.CamResolution & 0xFF;
	Data[1]=(EIOData.CamResolution>>8) & 0xFF;
	Data[2]=(EIOData.CamFrameTriggerL>>0) & 0xFF;
	Data[3]=(EIOData.CamFrameTriggerL>>8) & 0xFF;
	Data[4]=(EIOData.CamFrameTriggerL>>16) & 0xFF;
	Data[5]=(EIOData.CamFrameTriggerH>>0) & 0xFF;
	Data[6]=(EIOData.CamFrameTriggerH>>8) & 0xFF;
	Data[7]=(EIOData.CamFrameTriggerH>>16) & 0xFF;
	Data[8]= EIOData.OutExt;
    Data[9]= (EIOData.LEDOutToPanel[0]==true?0x04:0)
            +(EIOData.LEDOutToPanel[1]==true?0x08:0)
            +(EIOData.TestLEDReg==true?0x02:0)
            +(EIOData.CamOut==true?0x01:0);

    WriteRegister(DipSW ,Data,10);
}

void MainWindow::WriteEForBit(int DipSW ,int Brd)
{
    int	Data[10];

    digitalWrite(13 , ((DipSW&0x01)!=0)?1:0);
    digitalWrite(14 , ((DipSW&0x02)!=0)?1:0);
    digitalWrite(16 , ((DipSW&0x04)!=0)?1:0);
    digitalWrite(17 , ((DipSW&0x08)!=0)?1:0);

    digitalWrite(11 , 1);	//iRPiCmdW
    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();

    digitalWrite(15 , 1);	//iRPiStrobe
    delay(1);

    Data[0]= BoardData[Brd].CurrentPatternNo;
    Data[1]=
             (BoardData[Brd].CmdSetAnalog==true?0x08:0)
            +(BoardData[Brd].CmdLoad==true?     0x04:0)
            +(BoardData[Brd].CmdSetLineOn==true?0x02:0)
            +(BoardData[Brd].TestLEDReg==true?  0x01:0);

    WriteRegister(DipSW ,Data,2);

    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();
    delay(1);
}

int MainWindow::ReadEForBit(int DipSW ,int Brd)	//Return Motor counter
{
    int	Data[7];

    ReadRegister4Bit(DipSW ,Data ,4);
    int	Ret=Data[1] + (Data[2]<<4) + (Data[3]<<8);

    return Ret;
}
void MainWindow::WriteELightData(int DipSW ,int brd ,int PatternNoW)
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

    int	Data[10];
    Data[0]= BoardData[brd].CurrentPatternNo;
    Data[1]=
             (BoardData[brd].CmdSetAnalog==true?0x08:0)
            +(BoardData[brd].CmdLoad==true?     0x04:0)
            +(BoardData[brd].CmdSetLineOn==true?0x02:0)
            +(BoardData[brd].TestLEDReg==true?  0x01:0);
    for(int i=0;i<2;i++){
        WriteRegister(Data[i]);
    }

    WriteRegister(PatternNoW);

    for(int i=0;i<16;i++){
        int d=BoardData[brd].MotorPluseDecoderData[i].CounterL;
        WriteRegister(d&0xFF);
        WriteRegister((d>>8)&0xFF);
    }
    for(int i=0;i<16;i++){
        int d=BoardData[brd].MotorPluseDecoderData[i].CounterH;
        WriteRegister(d&0xFF);
        WriteRegister((d>>8)&0xFF);
    }

    //Write in memory from here
    WriteRegister(BoardData[brd].LightPatternData[PatternNoW].DCEnable==true?1:0);

    unsigned int  LightONL=0;
    for(int i=0;i<16;i++){
        LightONL    |=(BoardData[brd].LightPatternData[PatternNoW].LineData[i].ON==true)?(0x01<<i):0;
    }
    WriteRegister(LightONL&0xFF);
    WriteRegister((LightONL>>8)&0xFF);

    unsigned int    PGAChannel;
    for(int i=0;i<16;i++){
        int d=BoardData[brd].LightPatternData[PatternNoW].LineData[i].GetPGAChannel();
        PGAChannel    |=d<<i;
    }
    WriteRegister(PGAChannel&0xFF);
    WriteRegister((PGAChannel>>8)&0xFF);

    for(int i=0;i<16;i++){
        int d=BoardData[brd].LightPatternData[PatternNoW].LineData[i].GetDAValue();
        WriteRegister(d&0xFF);

        int g=BoardData[brd].LightPatternData[PatternNoW].LineData[i].GetPGAGain();
        int H=BoardData[brd].LightPatternData[PatternNoW].LineData[i].GetDAGainX2();
        WriteRegister((g<<5)+ ((H==0)?0:0x10) + ((d>>8)&0xFF));

        int C=BoardData[brd].LightPatternData[PatternNoW].LineData[i].GetDCClock();
        WriteRegister(C&0xFF);
    }

    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();
    delay(1);
}
void MainWindow::WriteEOnOffData(int DipSW ,int brd ,int PatternNoW)    //Execute after WriteEForBit
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

    int	Data[10];
    Data[0]= BoardData[brd].CurrentPatternNo;
    Data[1]=
             (BoardData[brd].CmdSetAnalog==true?0x08:0)
            +(BoardData[brd].CmdLoad==true?     0x04:0)
            +(BoardData[brd].CmdSetLineOn==true?0x02:0)
            +(BoardData[brd].TestLEDReg==true?  0x01:0);
    for(int i=0;i<2;i++){
        WriteRegister(Data[i]);
    }

    WriteRegister(PatternNoW);

    for(int i=0;i<16;i++){
        int d=BoardData[brd].MotorPluseDecoderData[i].CounterL;
        WriteRegister(d&0xFF);
        WriteRegister((d>>8)&0xFF);
    }
    for(int i=0;i<16;i++){
        int d=BoardData[brd].MotorPluseDecoderData[i].CounterH;
        WriteRegister(d&0xFF);
        WriteRegister((d>>8)&0xFF);
    }

    WriteRegister(BoardData[brd].LightPatternData[PatternNoW].DCEnable==true?1:0);

    unsigned int  LightONL=0;
    for(int i=0;i<16;i++){
        LightONL    |=(BoardData[brd].LightPatternData[PatternNoW].LineData[i].ON==true)?(0x01<<i):0;
    }
    WriteRegister(LightONL&0xFF);
    WriteRegister((LightONL>>8)&0xFF);

    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();
    delay(1);
}

bool MainWindow::ReadELightData(int DipSW ,int brd ,int PatternNo)
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
	
	int Data1,Data2,Data3,Data4;
    ReadRegister4Bit(Data1);    //Read ID

    ReadRegister4Bit(Data1);
    ReadRegister4Bit(Data2);
    ReadRegister4Bit(Data3);

    Data1+(Data2<<4)+(Data3<<8)+(Data4<<12);

    digitalWrite(2 , ((PatternNo&0x01)!=0)?1:0);
    digitalWrite(3 , ((PatternNo&0x02)!=0)?1:0);
    digitalWrite(4 , ((PatternNo&0x04)!=0)?1:0);
    digitalWrite(5 , ((PatternNo&0x08)!=0)?1:0);
    digitalWrite(6 , ((PatternNo&0x10)!=0)?1:0);
    digitalWrite(7 , ((PatternNo&0x20)!=0)?1:0);
    digitalWrite(8 , ((PatternNo&0x40)!=0)?1:0);
    digitalWrite(9 , ((PatternNo&0x80)!=0)?1:0);
    ReadRegister4Bit(Data2);	//Dummy
    
    for(int i=0;i<16;i++){
        ReadRegister4Bit(Data1);
        ReadRegister4Bit(Data2);
        ReadRegister4Bit(Data3);
        ReadRegister4Bit(Data4);
        BoardData[brd].MotorPluseDecoderData[i].CounterL=Data1+(Data2<<4)+(Data3<<8)+(Data4<<12);
    }
    for(int i=0;i<16;i++){
        ReadRegister4Bit(Data1);
        ReadRegister4Bit(Data2);
        ReadRegister4Bit(Data3);
        ReadRegister4Bit(Data4);
        BoardData[brd].MotorPluseDecoderData[i].CounterH=Data1+(Data2<<4)+(Data3<<8)+(Data4<<12);
    }

    ReadRegister4Bit(Data1);    //
    ReadRegister4Bit(Data2);	//DCEN
    unsigned int    DCEN=Data1+(Data2<<4);
    if((DCEN&0x01)!=0)
        BoardData[brd].LightPatternData[PatternNo].DCEnable=true;
    else
        BoardData[brd].LightPatternData[PatternNo].DCEnable=false;

    ReadRegister4Bit(Data1);    //Memory address=1
    ReadRegister4Bit(Data2);
    ReadRegister4Bit(Data3);    //Memory address=2
    ReadRegister4Bit(Data4);

    unsigned int  LightON=Data1+(Data2<<4)+(Data3<<8)+(Data4<<12);
    for(int i=0;i<16;i++){
        BoardData[brd].LightPatternData[PatternNo].LineData[i].ON=((LightON & (0x01<<i))!=0)?true:false;
    }

    ReadRegister4Bit(Data1);
    ReadRegister4Bit(Data2);
    ReadRegister4Bit(Data3);
    ReadRegister4Bit(Data4);
   	unsigned int    PGAChannel=Data1+(Data2<<4)+(Data3<<8)+(Data4<<12);
    for(int i=0;i<16;i++){
        int	d=BoardData[brd].LightPatternData[PatternNo].LineData[i].GetPGAChannel();
        int	s=((PGAChannel & (0x01<<i))!=0)?1:0;
        if(d!=s)
        	return false;
    }

    for(int i=0;i<16;i++){
    	ReadRegister4Bit(Data1);
    	ReadRegister4Bit(Data2);
    	int	DAValue=Data1+(Data2<<4);
        int d=BoardData[brd].LightPatternData[PatternNo].LineData[i].GetDAValue();
        if(d!=DAValue)
        	return false;

        ReadRegister4Bit(Data1);
    	ReadRegister4Bit(Data2);
    	int	s=Data1+(Data2<<4);
		int g=BoardData[brd].LightPatternData[PatternNo].LineData[i].GetPGAGain();
        int H=BoardData[brd].LightPatternData[PatternNo].LineData[i].GetDAGainX2();
        if((s&0xFF)!=((d>>8)&0xFF))
        	return false;
        if(H!=((s>>4)&1))
        	return false;
        if(g!=((s>>5)&0x7))
        	return false;
        
        ReadRegister4Bit(Data1);
    	ReadRegister4Bit(Data2);
    	int	C=Data1+(Data2<<4);
        if(BoardData[brd].LightPatternData[PatternNo].LineData[i].GetDCClock()!=C)
        	return false;
    }
    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();
    delay(1);
    return true;
}

int MainWindow::ReadBOardID(int DipSW)
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

void MainWindow::WriteRegister(int DipSW ,int Data[] ,int DataLen)
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
void MainWindow::WriteRegister(int Data)
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


void MainWindow::ReadRegister4Bit(int DipSW ,int Data[] ,int DataLen)
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

void MainWindow::ReadRegister4Bit(int &Data)
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

void MainWindow::DummyClock(void)
{
    delay(1);
    digitalWrite(12, 1);
    delay(1);
    digitalWrite(12, 0);
    delay(1);
}
