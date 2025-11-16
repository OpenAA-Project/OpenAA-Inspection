#include "ControlLightGForm.h"
#include "ui_ControlLightGForm.h"
#include <wiringPi.h>
#include "XGeneralFunc.h"

#define LEDControllerPort   17280


SocketClient::SocketClient(ControlLightGForm *parent ,QTcpSocket *s)
{
    Parent=parent;
    Socket=s;

    connect(s,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
    connect(s,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
}

SocketClient::~SocketClient(void)
{
}

void    SocketClient::SlotReadyRead()
{
    unsigned char   Cmd;

    if(Socket->read((char *)&Cmd,sizeof(Cmd))!=sizeof(Cmd))
        return;
    if(Cmd=='V'){
        if(Socket->write((const char *)&Cmd,sizeof(Cmd))!=sizeof(Cmd))
            return;
        QByteArray  Array;
        Array.append("LEDControl16E-Rev2, MEGATRADE");
        Socket->write(Array);
        Socket->flush();
    }
    if(Cmd=='A'){
        if(Socket->write((const char *)&Cmd,sizeof(Cmd))!=sizeof(Cmd))
            return;
        unsigned char	BoardCount=Parent->BoardCount;
        if(Socket->write((const char *)&BoardCount,sizeof(BoardCount))!=sizeof(BoardCount))
            return;
        Socket->flush();
    }
    else if(Cmd=='B'){
        struct  LightPacketData data;
        if(Socket->read((char *)&data,sizeof(data))==sizeof(data)){
            Parent->ReceiveData(data);
        }
        if(Socket->write((const char *)&Cmd,sizeof(Cmd))!=sizeof(Cmd))
            return;
        Socket->flush();
    }
    else if(Cmd=='I'){
        unsigned char   Param;
       if(Socket->read((char *)&Param,sizeof(Param))!=sizeof(Param))
            return;
        if(Param=='1'){
            Parent->AllON(true);
        }
        else if(Param=='0'){
            Parent->AllON(false);
        }
        if(Socket->write((const char *)&Cmd,sizeof(Cmd))!=sizeof(Cmd))
            return;
        Socket->flush();
    }
}

void    SocketClient::SlotDisconnected()
{
    Parent->DisconnectClient(this);
}

//-------------------------------------------------------------------
ControlLightGForm::ControlLightGForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlLightGForm),Server(NULL)
{
    ui->setupUi(this);

    BoardData   =new struct	LightBoard[16];
    //Server  =new QTcpServer(this);

    int data;
    BoardCount=0;
    for(int dsw=0;dsw<15;dsw++){
        data=ReadBoardID(dsw);
        if(data==1){
            DipSWTable[BoardCount]=dsw;
            BoardCount++;
        }
    }
    ui->tableWidget->setColumnWidth(0,72);
    ui->tableWidget->setColumnWidth(1,72);
    ui->tableWidget->setColumnWidth(2,72);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,100);
    ui->tableWidget->setColumnWidth(5,36);
    for(int i=0;i<BoardCount;i++){
        ui->comboBoxBoard   ->addItem(QString::number(i)+QString(" DipSW:")+QString::number(GetDipSW_InE(i)));
    }

    data=ReadBoardID(0);
    data=ReadBoardID(1);
    data=ReadBoardID(2);

    for(int Brd=0;Brd<BoardCount;Brd++){
        int DipSW=GetDipSW_InE(Brd);
        BoardData[Brd].TestLEDReg=true;
        WriteEForBit( DipSW,Brd);
        BoardData[Brd].TestLEDReg=false;
        WriteEForBit(DipSW ,Brd);
        BoardData[Brd].TestLEDReg=true;
        WriteEForBit(DipSW ,Brd);

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
    }
    AllON(true);

    if(Server!=NULL){
        connect(Server,SIGNAL(newConnection ()),this,SLOT(SlotNewConnection ()));
        Server->listen(QHostAddress::Any,LEDControllerPort);
    }
    else{
        AllON(true);
    }
}

ControlLightGForm::~ControlLightGForm()
{
    delete ui;
    delete  Server;
    Server=NULL;
}

void ControlLightGForm::on_comboBoxBoard_currentIndexChanged(int index)
{
    ShowCurrentData();
}

void ControlLightGForm::on_spinBoxPattern_valueChanged(int arg1)
{
    ShowCurrentData();
}

void    ControlLightGForm::SlotNewConnection()
{
    if(Server!=NULL){
        QTcpSocket *s=Server->nextPendingConnection ();
        SocketClient    *Sock=new SocketClient(this ,s);
        //AccessMutex.lock();
        ClientList.AppendList(Sock);
        //AccessMutex.unlock();

        //ui->checkBoxConnecting->setChecked(true);
    }
}


void    ControlLightGForm::DisconnectClient(SocketClient *s)
{
    //AccessMutex.lock();
    ClientList.RemoveList(s);
    //AccessMutex.unlock();
   // s->deleteLater();

    //ui->checkBoxConnecting->setChecked(false);
}

void    ControlLightGForm::ReceiveData(struct  LightPacketData &data)
{
    int	Brd=data.BoardNo;
    int DipSW=GetDipSW_InE(data.BoardNo);

    BoardData[Brd].LightPatternData[data.PatternNo]=data.PatternData;

    WriteELightData(DipSW ,Brd,0);
    BoardData[Brd].CmdLoad=true;
    WriteEForBit(DipSW ,Brd);
    BoardData[Brd].CmdLoad=false;
    WriteEForBit(DipSW ,Brd);

    ShowCurrentData();
}


void ControlLightGForm::WriteEForBit(int DipSW ,int Brd)
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

int ControlLightGForm::ReadEForBit(int DipSW ,int Brd)	//Return Motor counter
{
    int	Data[7];

    ReadRegister4Bit(DipSW ,Data ,4);
    int	Ret=Data[1] + (Data[2]<<4) + (Data[3]<<8);

    return Ret;
}
void ControlLightGForm::WriteELightData(int DipSW ,int brd ,int PatternNoW)
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
void ControlLightGForm::WriteEOnOffData(int DipSW ,int brd ,int PatternNoW)    //Execute after WriteEForBit
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

bool ControlLightGForm::ReadELightData(int DipSW ,int brd ,int PatternNo)
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

    WriteRegister(PatternNo);

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

int ControlLightGForm::ReadBoardID(int DipSW)
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

void ControlLightGForm::WriteRegister(int DipSW ,int Data[] ,int DataLen)
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
void ControlLightGForm::WriteRegister(int Data)
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


void ControlLightGForm::ReadRegister4Bit(int DipSW ,int Data[] ,int DataLen)
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

void ControlLightGForm::ReadRegister4Bit(int &Data)
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

void ControlLightGForm::DummyClock(void)
{
    delay(1);
    digitalWrite(12, 1);
    delay(1);
    digitalWrite(12, 0);
    delay(1);
}

void	ControlLightGForm::AllON(bool ON)
{
    for(int Brd=0;Brd<BoardCount;Brd++){
        int	DipSW=GetDipSW_InE(Brd);
        BoardData[Brd].LightPatternData[0].SetAllON(ON);
        WriteEOnOffData(DipSW ,Brd,0);
        BoardData[Brd].CmdSetLineOn=true;
        WriteEForBit(DipSW ,Brd);
        BoardData[Brd].CmdSetLineOn=false;
        WriteEForBit(DipSW ,Brd);
    }
    ShowCurrentData();
}

int ControlLightGForm::GetDipSW_InE(int boardnumber)
{
    return DipSWTable[boardnumber];
}

void ControlLightGForm::ShowCurrentData(void)
{
    int BoardNo   =ui->comboBoxBoard  ->currentIndex();
    int PatternNoW=ui->spinBoxPattern ->value();

    if(0<=BoardNo && 0<=PatternNoW){
        for(int i=0;i<16;i++){
            int d1=BoardData[BoardNo].LightPatternData[PatternNoW].LineData[i].GetPGAChannel();
            int d2=BoardData[BoardNo].LightPatternData[PatternNoW].LineData[i].GetDAGainX2();
            int d3=BoardData[BoardNo].LightPatternData[PatternNoW].LineData[i].GetPGAGain();
            int d4=BoardData[BoardNo].LightPatternData[PatternNoW].LineData[i].GetDAValue();
            int d5=BoardData[BoardNo].LightPatternData[PatternNoW].LineData[i].GetDCClock();
            bool ON=BoardData[BoardNo].LightPatternData[PatternNoW].LineData[i].ON;
            ::SetDataToTable(ui->tableWidget ,0 ,i ,QString::number(d1));
            ::SetDataToTable(ui->tableWidget ,1 ,i ,QString::number(d2));
            ::SetDataToTable(ui->tableWidget ,2 ,i ,QString::number(d3));
            ::SetDataToTable(ui->tableWidget ,3 ,i ,QString::number(d4));
            ::SetDataToTable(ui->tableWidget ,4 ,i ,QString::number(d5));
            ::SetDataToTable(ui->tableWidget ,5 ,i ,(ON==true)?"ON":"");
        }
    }    
}
