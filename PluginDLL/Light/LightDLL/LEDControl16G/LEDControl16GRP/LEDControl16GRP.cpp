#include "LEDControl16GRP.h"
#include "ui_LEDControl16GRP.h"
#include <wiringPi.h>
#include <QFile>
#include "XTypeDef.h"
#include "XGeneralFunc.h"

SocketClient::SocketClient(LEDControl16GRP *parent ,QTcpSocket *s)
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
QString     SettingFileName="MiconSetting.dat";

LEDControl16GRP::LEDControl16GRP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LEDControl16GRP)
    ,Server(this)
{
    ui->setupUi(this);

    if (wiringPiSetupGpio() < 0) {
        printf("GPIO ERROR\n");
        return;
    }

    //connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
    //Server.listen(QHostAddress::Any,12777);

    InitialSignal();
    WriteInitial();
    Server.StartListen();
}

LEDControl16GRP::~LEDControl16GRP()
{
    delete ui;
}

void    LEDControl16GRP::WriteInitial(void)
{
    DipSW_EIO=-1;

    //TestWriteE(0);

    int data;
    int DipSWTable[MaxDipSW];
    WriteRegisterData(0xFF);
    BoardCount=0;
    for(int dipsw=0;dipsw<MaxDipSW;dipsw++){
        data=ReadBOardID(dipsw);
        if(data==1){
            BoardData[BoardCount].DipSW=dipsw;
            DipSWTable[BoardCount]=dipsw;
            BoardCount++;
        }
        else if(data==10){
            DipSWTable[dipsw]=-100;
            DipSW_EIO=dipsw;
        }
        else{
            DipSWTable[dipsw]=-1;
        }
    }
    if(DipSW_EIO>=0){
        EIOData.OutExt=0;
        EIOData.TestLEDReg=true;
        WriteEIO(DipSW_EIO);
        EIOData.TestLEDReg=false;
        WriteEIO(DipSW_EIO);
        EIOData.TestLEDReg=true;
        WriteEIO(DipSW_EIO);
    }

    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].SetTestLED(true);
        BoardData[Brd].SetTestLED(false);
        BoardData[Brd].SetTestLED(true);
    }

    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].SetAllON(false);
    }

    ui->listWidgetDipSW->clear();
    for(int Brd=0;Brd<BoardCount;Brd++){
        ui->listWidgetDipSW->addItem (QString::number(BoardData[Brd].DipSW));
    }

    QFile   File(SettingFileName);
    if(File.open(QIODevice::ReadOnly)==true){
        Load(&File);
    }

    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].SetAllON(BoardData[Brd].AllON);
        BoardData[Brd].GetCurrentValue();
    }
    for(int Brd=0;Brd<BoardCount;Brd++){
        if(BoardData[Brd].AllON==true)
            ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::red);
        else
            ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::white);
    }
    if(BoardCount>0){
        ui->listWidgetDipSW->setCurrentRow(0);
    }
}

void    LEDControl16GRP::SlotNewConnection()
{

    //QTcpSocket *s=Server.nextPendingConnection ();
    //SocketClient    *Sock=new SocketClient(this ,s);
    AccessMutex.lock();
    //ClientList.AppendList(Sock);
    AccessMutex.unlock();

    //ui->checkBoxConnecting->setChecked(true);
}


void    LEDControl16GRP::DisconnectClient(SocketClient *s)
{
    AccessMutex.lock();
    ClientList.RemoveList(s);
    AccessMutex.unlock();
   // s->deleteLater();

    //ui->checkBoxConnecting->setChecked(false);
}

void    LEDControl16GRP::InitialSignal(void)
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

void    LEDControl16GRP::WriteEIO()
{
    WriteEIO(DipSW_EIO);
}

void LEDControl16GRP::WriteEIO(int DipSW)
{
    int	Data[50];

    Data[0]=(EIOData.Conveyer1Pulse>>0) & 0xFF;
    Data[1]=(EIOData.Conveyer1Pulse>>8) & 0xFF;
    Data[2]=(EIOData.Conveyer1Pulse>>16) & 0xFF;
    Data[3]= EIOData.OutExt;
    Data[4]= (EIOData.LEDOutToPanel[0]==true?0x04:0)
            +(EIOData.LEDOutToPanel[1]==true?0x08:0)
            +(EIOData.TestLEDReg==true?0x02:0)
            +(EIOData.CamOut==true?0x01:0);
    Data[5 ]= EIOData.DelayFrameTriggerA & 0xFF;
    Data[6 ]=(EIOData.DelayFrameTriggerA>>8) & 0xFF;
    Data[7 ]=(EIOData.DelayFrameTriggerA>>16) & 0xFF;
    Data[8 ]= EIOData.DelayFrameTriggerB & 0xFF;
    Data[9 ]=(EIOData.DelayFrameTriggerB>>8) & 0xFF;
    Data[10]=(EIOData.DelayFrameTriggerB>>16) & 0xFF;
    Data[11]= EIOData.FrameCycle & 0xFF;
    Data[12]=(EIOData.FrameCycle>>8) & 0xFF;
    Data[13]=(EIOData.FrameCycle>>16) & 0xFF;

    Data[14]= EIOData.DropLength & 0xFF;
    Data[15]=(EIOData.DropLength>>8) & 0xFF;
    Data[16]= EIOData.DropFlapONLength & 0xFF;
    Data[17]=(EIOData.DropFlapONLength>>8) & 0xFF;

    WriteRegister(DipSW ,Data,20);
}
void LEDControl16GRP::ReadEIO(int DipSW)
{
    int	Data[50];

    ReadRegister4Bit(DipSW ,Data ,20);

    EIOData.InExt           =Data[1 ]+(Data[2 ]<<4);
    EIOData.TimeUpLatchA	=Data[4 ]+(Data[5 ]<<4)+(Data[6 ]<<8)+((Data[7]&0x03)<<12);
    EIOData.TimeUpLatchB	=Data[8 ]+(Data[9 ]<<4)+(Data[10]<<8)+((Data[11]&0x03)<<12);
    EIOData.ResultTimeLatchA=Data[12]+(Data[13]<<4)+(Data[14]<<8)+((Data[15]&0x03)<<12);
    EIOData.ResultTimeLatchB=Data[16]+(Data[17]<<4)+(Data[18]<<8)+((Data[19]&0x03)<<12);
}

int LEDControl16GRP::ReadBOardID(int DipSW)
{
	WriteRegisterData(0xFF);
	
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

//-------------------------------------------------------------------
bool    LEDControl16GRP::Save(QIODevice *f)
{
    BYTE    Ver=1;

    if(::Save(f,Ver)==false)
        return false;
    if(EIOData.Save(f)==false){
        return false;
    }
    int32 N=sizeof(BoardData)/sizeof(BoardData[0]);

    if(::Save(f,N)==false)
        return false;
    for(int i=0;i<N;i++){
        if(BoardData[i].Save(f)==false){
            return false;
        }
    }
    return true;
}

bool    LEDControl16GRP::Load(QIODevice *f)
{
    BYTE    Ver;

    if(::Load(f,Ver)==false)
        return false;
    if(EIOData.Load(f)==false){
        return false;
    }
    int32 N=sizeof(BoardData)/sizeof(BoardData[0]);
    int32   iN;

    if(::Load(f,iN)==false)
        return false;
    for(int i=0;i<N && i<iN;i++){
        if(BoardData[i].Load(f)==false){
            return false;
        }
    }
    return true;
}
 void	LEDControl16GRP::ShowEIO(void)
 {
 }
//-------------------------------------------------------------------

void LEDControl16GRP::on_listWidgetDipSW_currentRowChanged(int currentRow)
{
    int Brd=ui->listWidgetDipSW->currentRow();
    if(Brd<0)
        return;
    ui->tableWidget->setRowCount(MaxCountLines);
    int PatternNo=ui->spinBoxPatternNo->value();
    BoardData[Brd].GetLightData(PatternNo);
    BoardData[Brd].GetCurrentValue();
    for(int Row=0;Row<MaxCountLines;Row++){
        long    int V=BoardData[Brd].LineInfo[Row].TargetValue[PatternNo];
        ::SetDataToTable(ui->tableWidget ,0 ,Row ,QString::number(V));
        long    int A=BoardData[Brd].LineInfo[Row].CurrentValue;
        ::SetDataToTable(ui->tableWidget ,1 ,Row ,QString::number(A));
    }
}

void LEDControl16GRP::on_spinBoxPatternNo_valueChanged(int arg1)
{
    int PatternNo=ui->spinBoxPatternNo->value();
    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].SetCurrentPatternNo(PatternNo);
    }
    on_listWidgetDipSW_currentRowChanged(0);
}

void LEDControl16GRP::on_listWidgetDipSW_doubleClicked(const QModelIndex &index)
{
    int Brd=ui->listWidgetDipSW->currentRow();

    BoardData[Brd].AllON=!BoardData[Brd].AllON;
    BoardData[Brd].SetAllON(BoardData[Brd].AllON);

    if(BoardData[Brd].AllON==true)
        ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::red);
    else
        ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::white);
}

void LEDControl16GRP::on_toolButtonAllON_clicked()
{
    bool    b=ui->toolButtonAllON->isChecked();
    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].AllON=b;
        BoardData[Brd].SetAllON(BoardData[Brd].AllON);
    }
    for(int Brd=0;Brd<BoardCount;Brd++){
        if(BoardData[Brd].AllON==true)
            ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::red);
        else
            ::SetListColor(ui->listWidgetDipSW ,Brd ,Qt::white);
    }
    for(int Brd=0;Brd<BoardCount;Brd++){
        BoardData[Brd].GetCurrentValue();
    }
    on_listWidgetDipSW_currentRowChanged(0);
}

void LEDControl16GRP::on_toolButtonSave_clicked()
{
    QFile   File(SettingFileName);
    if(File.open(QIODevice::WriteOnly)==true){
        Save(&File);
    }
}

void LEDControl16GRP::on_pushButtonUpdate_clicked()
{
    on_listWidgetDipSW_currentRowChanged(0);
}

//-------------------------------------------------------------------
void	LEDControl16GRP::ReqBoardName(void)
{
}
void	LEDControl16GRP::SetTestLED(int DipSW ,bool b)
{
	for(int brd=0;brd<BoardCount;brd++){
		if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].SetTestLED(b);
		}
	}
}
void	LEDControl16GRP::SetAllOn(int DipSW ,bool OnMode)
{
	for(int brd=0;brd<BoardCount;brd++){
		if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].AllON=OnMode;
            BoardData[brd].SetAllON(OnMode);
		}
	}
}
void	LEDControl16GRP::SetAllCurrentPattern(int DipSW ,int PatternNo)
{
	for(int brd=0;brd<BoardCount;brd++){
		if(BoardData[brd].DipSW==DipSW){
            BoardData[brd].SetCurrentPatternNo(PatternNo);
		}
	}
}
