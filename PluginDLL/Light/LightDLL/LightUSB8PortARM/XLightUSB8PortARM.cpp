#include "XLightUSB8PortARM.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "LightUSB8PortForm.h"

void	LightUSB8PortARMPanel::LEDOnController::Transfer(LightUSB8PortARMPanel *d)
{
	//d->OutputLED(BarNo,ColumnNo,LED);
}

bool	LightUSB8PortARMPanel::LEDOnController::Save(QIODevice *f)
{
	if(::Save(f,BarNo)==false)
		return false;
	if(::Save(f,ColumnNo)==false)
		return false;
	if(::Save(f,LED)==false)
		return false;
	if(::Save(f,MaxLevel)==false)
		return false;
	return true;
}
bool	LightUSB8PortARMPanel::LEDOnController::Load(QIODevice *f)
{
	if(::Load(f,BarNo)==false)
		return false;
	if(::Load(f,ColumnNo)==false)
		return false;
	if(::Load(f,LED)==false)
		return false;
	if(::Load(f,MaxLevel)==false)
		return false;
	return true;
}

//============================================================================================

LightUSB8PortARMPanel::LEDBarOnController::LEDBarOnController(void)
{
	Bar			=NULL;
	ColumnCount	=0;
}
LightUSB8PortARMPanel::LEDBarOnController::~LEDBarOnController(void)
{
	if(Bar!=NULL){
		delete	[]Bar;
		Bar=NULL;
	}
	ColumnCount=0;
}
void	LightUSB8PortARMPanel::LEDBarOnController::Alloc(int barNo,int columnCount)
{
	BarNo=barNo;
	if(Bar!=NULL){
		delete	[]Bar;
	}
	ColumnCount	=columnCount;
	Bar=new LEDOnController[ColumnCount];
	for(int i=0;i<ColumnCount;i++){
		Bar[i].BarNo	=BarNo;
		Bar[i].ColumnNo	=i;
		Bar[i].LED		=0;
	}
}
void	LightUSB8PortARMPanel::LEDBarOnController::SetMaxLevel(int MaxLevel)
{
	for(int i=0;i<ColumnCount;i++){
		Bar[i].MaxLevel	=MaxLevel;
	}
}

int		LightUSB8PortARMPanel::LEDBarOnController::GetLEDBrightness(int column)
{
	if(0<=column && column<ColumnCount){
		return Bar[column].LED;
	}
	return -1;
}
void	LightUSB8PortARMPanel::LEDBarOnController::SetLEDBrightness(int column ,int brightness)
{
	if(0<=column && column<ColumnCount){
		Bar[column].LED=brightness;
	}
}

LightUSB8PortARMPanel::LEDOnController	*LightUSB8PortARMPanel::LEDBarOnController::GetLED(int column)
{
	if(0<=column && column<ColumnCount){
		return &Bar[column];
	}
	return NULL;
}
void	LightUSB8PortARMPanel::LEDBarOnController::Transfer(LightUSB8PortARMPanel *d)
{
	for(int i=0;i<ColumnCount;i+=32){
		//Bar[i].Transfer(d);
		int	LED[1000];
		for(int j=0;j<32 && (i+j)<ColumnCount;j++){
			LED[j]=Bar[i+j].LED;
		}
		d->OutputLED(BarNo,i,LED);
	}
}

bool	LightUSB8PortARMPanel::LEDBarOnController::Save(QIODevice *f)
{
	if(::Save(f,BarNo)==false)
		return false;
	if(::Save(f,ColumnCount)==false)
		return false;
	for(int i=0;i<ColumnCount;i++){
		if(Bar[i].Save(f)==false){
			return false;
		}
	if(::Save(f,Comment)==false)
		return false;
	}
	return true;
}
bool	LightUSB8PortARMPanel::LEDBarOnController::Load(QIODevice *f)
{
	if(::Load(f,BarNo)==false)
		return false;
	if(::Load(f,ColumnCount)==false)
		return false;
	Alloc(BarNo,ColumnCount);

	for(int i=0;i<ColumnCount;i++){
		if(Bar[i].Load(f)==false){
			return false;
		}
	if(::Load(f,Comment)==false)
		return false;
	}
	return true;
}

//=================================================================================
LightUSB8PortARMPanel::LightUSB8PortARMPanel(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	int	boardCount=8;
	int	LEDsPerPort=64;
	int	MaxLevel=63;

	Commander=HidCommand::Create((QWidget *)this);

	Opened=false;
	Param=LightParamStr;
	CurrentPattern	=0;

	BoardCount=boardCount;
	Board=new LEDBarOnController[BoardCount];
	for(int i=0;i<BoardCount;i++){
		Board[i].Alloc(i,LEDsPerPort);
		Board[i].SetMaxLevel(MaxLevel);
	}

	Number=0;
	if(LightParamStr.isNull()==false){
		Number=LightParamStr.toInt();
	}
	if(Open()==true){
		GetVersion();
	}
	CurrentON=false;
	WatchingTimer.setSingleShot(false);
	WatchingTimer.setInterval(2000);
	connect(&WatchingTimer,SIGNAL(timeout()),this,SLOT(WatchingFunc()));
	WatchingTimer.start();
}

bool	LightUSB8PortARMPanel::Open(void)
{
	if(Commander->OpenHid(0x1255, 0x0011,Number)==false){
		return false;
	}
	return true;
}

void	LightUSB8PortARMPanel::GetVersion(void)
{
	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		Commander->SendStr((BYTE *)"V",1);
		BYTE	RecData[256];
		int		ReceivedLen;
		GSleep(100);
		if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
			VersionStr=((char *)RecData);
		}
		Commander->CloseHid();
	}
}

LightUSB8PortARMPanel::~LightUSB8PortARMPanel(void)
{
	delete	Commander;
}


int		LightUSB8PortARMPanel::GetLEDBrightness(int brd ,int column)
{
	if(0<=brd && brd<BoardCount){
		return Board[brd].GetLEDBrightness(column);
	}
	return -1;
}
void	LightUSB8PortARMPanel::SetLEDBrightness(int brd ,int column ,int brightness)
{
	if(0<=brd && brd<BoardCount){
		Board[brd].SetLEDBrightness(column,brightness);
	}
}

QString	LightUSB8PortARMPanel::GetBoardComment(int brd)
{
	if(0<=brd && brd<BoardCount){
		return Board[brd].Comment;
	}
	return QString();
}
void	LightUSB8PortARMPanel::SetBoardComment(int brd ,const QString &comment)
{
	if(0<=brd && brd<BoardCount){
		Board[brd].Comment=comment;
	}
}

LightUSB8PortARMPanel::LEDOnController	*LightUSB8PortARMPanel::GetLED(int brd ,int column)
{
	if(0<=brd && brd<BoardCount){
		return Board[brd].GetLED(column);
	}
	return NULL;
}
LightUSB8PortARMPanel	&LightUSB8PortARMPanel::operator=(LightUSB8PortARMPanel &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

void	LightUSB8PortARMPanel::Transfer(void)
{
	for(int i=0;i<BoardCount;i++){
		Board[i].Transfer(this);
	}
	DoneTransfer();
}

bool	LightUSB8PortARMPanel::Save(QIODevice *f)
{
	if(::Save(f,BoardCount)==false)
		return false;
	for(int i=0;i<BoardCount;i++){
		if(Board[i].Save(f)==false)
			return false;
	}
	return true;
}
	
bool	LightUSB8PortARMPanel::Load(QIODevice *f)
{
	if(::Load(f,BoardCount)==false)
		return false;
	if(Board!=NULL){
		delete	[]Board;
		Board=NULL;
	}
	Board=new LEDBarOnController[BoardCount];
	for(int i=0;i<BoardCount;i++){
		if(Board[i].Load(f)==false)
			return false;
	}
	return true;
}


bool	LightUSB8PortARMPanel::ShowSettingDialog(void)
{
	LightUSB8PortForm	*LightForm=new LightUSB8PortForm(this);
	bool	Ret=LightForm->exec();
	if(Ret==true){
		*this=*LightForm->GetBLight();
	}
	delete LightForm;

	return Ret;
}


bool	LightUSB8PortARMPanel::SetOnOff(bool d)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	CurrentON=d;

	if(Commander->IsOpened()==false)
		Open();
	if(Commander->IsOpened()==true){
		TxBuff[0]='A';
		if(d==true)
			TxBuff[1]='1';
		else
			TxBuff[1]='0';

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
		Commander->CloseHid();
	}
	return true;
}


void	LightUSB8PortARMPanel::OutputLED(int BarNo,int ColumnNo
										,int LED[])
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Commander->IsOpened()==true){
		TxBuff[0]='B';
		TxBuff[1]=BarNo;
		TxBuff[2]=ColumnNo;
		for(int i=0;i<32;i++){
			TxBuff[3+i]=LED[i];
		}

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
	}
}

void	LightUSB8PortARMPanel::WatchingFunc()
{
	if(CurrentON==true){
		SetOnOff(true);
	}
}

void	LightUSB8PortARMPanel::DoneTransfer(void)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Commander->IsOpened()==true){
		TxBuff[0]='C';

		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
	}
}


	//Don't call directly
bool	LightUSB8PortARMPanel::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}
bool	LightUSB8PortARMPanel::ReflectPhysical(void)
{
	if(Commander->IsOpened()==false){
		Open();
	}
	Transfer();
	if(Commander!=NULL){
		Commander->CloseHid();
	}
	return true;
}
bool	LightUSB8PortARMPanel::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}
