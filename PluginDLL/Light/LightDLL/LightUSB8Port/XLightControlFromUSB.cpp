#include "XLightControlFromUSB.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "LightUSB8PortForm.h"
#include "LightUSB8PortFormSmall.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

void	LightControlFromUSB::LEDOnController::Transfer(DirectLightControl *d)
{
	d->OutputLED(BarNo,ColumnNo,LED);
}

bool	LightControlFromUSB::LEDOnController::Save(QIODevice *f)
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
bool	LightControlFromUSB::LEDOnController::Load(QIODevice *f)
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

//======================================================================

LightControlFromUSB::LEDBarOnController::LEDBarOnController(void)
{
	Bar			=NULL;
	ColumnCount	=0;
}
LightControlFromUSB::LEDBarOnController::~LEDBarOnController(void)
{
	if(Bar!=NULL){
		delete	[]Bar;
		Bar=NULL;
	}
	ColumnCount=0;
}
void	LightControlFromUSB::LEDBarOnController::Alloc(int barNo,int columnCount)
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
void	LightControlFromUSB::LEDBarOnController::SetMaxLevel(int MaxLevel)
{
	for(int i=0;i<ColumnCount;i++){
		Bar[i].MaxLevel	=MaxLevel;
	}
}

int		LightControlFromUSB::LEDBarOnController::GetLEDBrightness(int column)
{
	if(0<=column && column<ColumnCount){
		return Bar[column].LED;
	}
	return -1;
}
void	LightControlFromUSB::LEDBarOnController::SetLEDBrightness(int column ,int brightness)
{
	if(0<=column && column<ColumnCount){
		Bar[column].LED=brightness;
	}
}

LightControlFromUSB::LEDOnController	*LightControlFromUSB::LEDBarOnController::GetLED(int column)
{
	if(0<=column && column<ColumnCount){
		return &Bar[column];
	}
	return NULL;
}
void	LightControlFromUSB::LEDBarOnController::Transfer(DirectLightControl *d)
{
	for(int i=0;i<ColumnCount;i++){
		Bar[i].Transfer(d);
	}
}

bool	LightControlFromUSB::LEDBarOnController::Save(QIODevice *f)
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
bool	LightControlFromUSB::LEDBarOnController::Load(QIODevice *f)
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

LightControlFromUSB::LightControlFromUSB(LayersBase *base ,int boardCount, int LEDsPerPort ,int MaxLevel)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	BoardCount=boardCount;
	Board=new LEDBarOnController[BoardCount];
	for(int i=0;i<BoardCount;i++){
		Board[i].Alloc(i,LEDsPerPort);
		Board[i].SetMaxLevel(MaxLevel);
	}
	DirectAccessor=NULL;
}
LightControlFromUSB::~LightControlFromUSB(void)
{
	if(Board!=NULL){
		delete	[]Board;
		Board=NULL;
	}
	BoardCount=0;

	DirectAccessor->Release();
	delete	DirectAccessor;
	DirectAccessor=NULL;
}


int		LightControlFromUSB::GetLEDBrightness(int brd ,int column)
{
	if(0<=brd && brd<BoardCount){
		return Board[brd].GetLEDBrightness(column);
	}
	return -1;
}
void	LightControlFromUSB::SetLEDBrightness(int brd ,int column ,int brightness)
{
	if(0<=brd && brd<BoardCount){
		Board[brd].SetLEDBrightness(column,brightness);
	}
}

QString	LightControlFromUSB::GetBoardComment(int brd)
{
	if(0<=brd && brd<BoardCount){
		return Board[brd].Comment;
	}
	return QString();
}
void	LightControlFromUSB::SetBoardComment(int brd ,const QString &comment)
{
	if(0<=brd && brd<BoardCount){
		Board[brd].Comment=comment;
	}
}

LightControlFromUSB::LEDOnController	*LightControlFromUSB::GetLED(int brd ,int column)
{
	if(0<=brd && brd<BoardCount){
		return Board[brd].GetLED(column);
	}
	return NULL;
}
LightControlFromUSB	&LightControlFromUSB::operator=(LightControlFromUSB &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	DirectAccessor	=src.DirectAccessor;
	return *this;
}
void	LightControlFromUSB::BeginTranster(void)
{
	if(DirectAccessor!=NULL){
		DirectAccessor->Open();
	}
}
void	LightControlFromUSB::Transfer(void)
{
	for(int i=0;i<BoardCount;i++){
		Board[i].Transfer(DirectAccessor);
	}
}
void	LightControlFromUSB::EndTranster(void)
{
	if(DirectAccessor!=NULL){
		DirectAccessor->Close();
	}
}

bool	LightControlFromUSB::Save(QIODevice *f)
{
	if(::Save(f,BoardCount)==false)
		return false;
	for(int i=0;i<BoardCount;i++){
		if(Board[i].Save(f)==false)
			return false;
	}
	return true;
}
	
bool	LightControlFromUSB::Load(QIODevice *f)
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


bool	LightControlFromUSB::ShowSettingDialog(void)
{
	LightUSB8PortFormSmall	*LightForm=new LightUSB8PortFormSmall(this);
	bool	Ret=LightForm->exec();
	if(Ret==true){
		*this=*LightForm->GetBLight();
	}
	delete LightForm;

	return Ret;
}

	//Don't call directly

bool	LightControlFromUSB::InitialPhysical(const QString &Param)
{
	if(DirectAccessor==NULL){
		DirectAccessor=new DirectLightControl(Param);
	}
	Initial(DirectAccessor);
	bool	Ret=DirectAccessor->Initial(true);
	return Ret;
}

bool	LightControlFromUSB::ReflectPhysical(void)
{
	BeginTranster();
	Transfer();
	EndTranster();
	return true;
}

bool	LightControlFromUSB::ReflectPhysicalTurnOn(bool LightOn)
{
	if(DirectAccessor!=NULL){
		BeginTranster();
		DirectAccessor->OutputLighting(LightOn);
		EndTranster();
	}
	return true;
}

//======================================================================================

int		DirectLightControl::LEDWaitTime=180;	//10000;
struct	InitializedMicrosecTimerStruct DirectLightControl::IWaitFunc;
int		FTWriteConter=0;
DirectLightControl::DirectLightControl(const QString &LightParamStr)
{	
	Data=0;	
	FifiCount=0;	
	Handle=0;	
	Opened		=false;
	TurnedOn	=false;
	Param	=LightParamStr;
}

bool	DirectLightControl::Initial(bool OutputMode)
{
	/*
	for(int i=0;i<8;i++){
		OutBit(i, true);
		OutBit(i, false);
	}
	*/
	if(OutputMode==false)
		return true;

	if(Open()==true){
		Start();
		FlushFifo();
		return true;
	}

	return false;
}
bool	DirectLightControl::Release(void)
{
	return true;
}
bool	DirectLightControl::Open(void)
{
	if(Opened==true){
		return true;
	}
	bool	ok;
	int	PortNumber=Param.toInt(&ok);
	if(ok==false)
		PortNumber=0;
	FT_STATUS ret;
	if(Handle==0){
		ret=FT_Open (PortNumber, &Handle);
		if(ret!=FT_OK){
			Handle=0;
			return false;
		}
	}
	ret=FT_SetBitMode(Handle, 0xFF, 0xFF);
	if(ret!=FT_OK){
		Handle=0;
		return false;
	}
	ret=FT_SetBaudRate(Handle, 19200);
	if(ret!=FT_OK){
		Handle=0;
		return false;
	}
	OutBit(7, true);
	FlushFifo();
	Opened=true;
	return true;
}
bool	DirectLightControl::Close(void)
{
	if(Opened==true){
		OutBit(7, false);
		FlushFifo();

		FT_STATUS ret=FT_Close (Handle);
		if(ret==FT_OK){
			Opened=false;
			Handle=0;
			return true;
		}
	}
	return false;
}

bool	DirectLightControl::OutputLED(int brd ,int colum ,int value)
{
	WaitLoop();
	Enable(false);
	Reset(true);
	WaitLoop();
	Reset(false);
	WaitLoop();
	Clock(false);
	WaitLoop();
	Strobe(true);
	WaitLoop();
	OutBits(brd,8);

	WaitLoop();
	OutBits((BYTE)colum,8);
	WaitLoop();
	OutBits((BYTE)value,8);

	WaitLoop();
	Clock(false);
	WaitLoop();
	Strobe(false);
	WaitLoop();

	Reset(false);
	Enable(true);
	WaitLoop();
	
	FlushFifo();

	return true;
}

bool	DirectLightControl::OutputLighting(bool modeOn)
{
	if(TurnedOn!=modeOn){
		Enable(modeOn);
		FlushFifo();
		TurnedOn=modeOn;
	}
	return true;
}

void	DirectLightControl::OutBit(int bit, bool data)
{
	if(data==false){
		Data &= ~(0x01<<bit);
	}
	else{
		Data |= (0x01<<bit);
	}
	FifiData[FifiCount]=Data;
	FifiCount++;
}
void	DirectLightControl::FlushFifo(void)
{
	DWORD BytesWriten;
	if(Handle!=0){
		FTWriteConter++;
		FT_STATUS	ret=FT_Write(Handle, FifiData, FifiCount, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=FifiCount){
			GSleep(100);
			ret=FT_Write(Handle, &FifiData[BytesWriten], FifiCount-BytesWriten, &BytesWriten);
		}
	}
	FifiCount=0;
}

void    DirectLightControl::WaitLoop(void)
{
	//WaitMicrosec(IWaitFunc,LEDWaitTime);
}
void	DirectLightControl::Start(void)
{
    Strobe(false);
    Clock(false);
    Enable(true);
    Enable(false);
    Enable(true);
    Reset(true);
    WaitLoop();
    Reset(false);
    Enable(false);
    Enable(true);
}

void    __fastcall DirectLightControl::Strobe(bool H)
{
	OutBit(2, H);
}

void    __fastcall DirectLightControl::Clock(bool H)
{
	OutBit(0, H);
}

void    __fastcall DirectLightControl::Reset(bool H)
{
	OutBit(4, H);
}

void    __fastcall DirectLightControl::Enable(bool H)
{
	OutBit(3, H);
}

void    __fastcall DirectLightControl::Din(bool H)
{
	OutBit(1, H);
}

void    __fastcall DirectLightControl::OutBits(BYTE d,int bitnumb)
{
	WaitLoop();
	for(int i=bitnumb-1;i>=0;i--){
		if((d&(((BYTE)0x01)<<i))!=0)
			Din(true);
		else
			Din(false);
		WaitLoop();
			WaitLoop();
		Clock(true);
			WaitLoop();
		WaitLoop();
		Clock(false);
		WaitLoop();
	}
}
