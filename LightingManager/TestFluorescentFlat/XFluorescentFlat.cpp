
#include "XFluorescentFlat.h"
#include "XCriticalFunc.h"

OneLEDSheet::OneLEDSheet(void)
{
	for(int i=0;i<LEDCountInSheet;i++){
		Data[i]=0;
		OutEnable[i]=true;
	}
}
void	OneLEDSheet::SetAll(int n)
{
	for(int i=0;i<LEDCountInSheet;i++){
		Data[i]=n;
	}
}
bool	OneLEDSheet::Save(QIODevice *f)
{
	f->write((const char *)Data,sizeof(Data));
	f->write((const char *)OutEnable,sizeof(OutEnable));
	return true;
}

bool	OneLEDSheet::Load(QIODevice *f)
{
	f->read((char *)Data,sizeof(Data));
	f->read((char *)OutEnable,sizeof(OutEnable));
	return true;
}

//=======================================================
void	SystemLEDSheet::Initial(void)
{
	DirectLightControl::Initial();
	Reset(1);
	FlushFifo();
	Reset(0);
	FlushFifo();

	for(int sheet=0;sheet<SheetCountInSystem;sheet++){
		SetOn(sheet ,true);
	}
	SetOnTransfer();
	
	SetOn(false);
}

void	SystemLEDSheet::SetAll(int n)
{
	for(int i=0;i<SheetCountInSystem;i++){
		Sheet[i].SetAll(n);
	}
}

bool	SystemLEDSheet::Save(QIODevice *f)
{
	for(int i=0;i<SheetCountInSystem;i++){
		if(Sheet[i].Save(f)==false)
			return false;
	}
	return true;
}

bool	SystemLEDSheet::Load(QIODevice *f)
{
	for(int i=0;i<SheetCountInSystem;i++){
		if(Sheet[i].Load(f)==false)
			return false;
	}
	return true;
}

void	SystemLEDSheet::Transfer(void)
{
	SetEnableAddr(1);
	SetEnableLatch(0);
	for(int sheet=0;sheet<SheetCountInSystem;sheet++){
		for(int LED=0;LED<LEDCountInSheet;LED++){
			for(int i=0;i<12;i++){
				int	d=Sheet[sheet].Data[LED];
				if((d&(0x800>>i))!=0)
					SetShiftIn(1);
				else
					SetShiftIn(0);
				SetShftClk(1);
				SetShftClk(0);
			}
			FlushFifo();
		}
	}
	SetEnableLatch(1);
	SetEnableLatch(0);
	FlushFifo();
}

void	SystemLEDSheet::SetOn(bool d)
{
	if(d==true)
		OutEnable(1);
	else
		OutEnable(0);
	FlushFifo();
}

void	SystemLEDSheet::SetOn(int sheet ,bool d)
{
	for(int LED=0;LED<LEDCountInSheet;LED++){
		Sheet[sheet].OutEnable[LED]=d;
	}
}
void	SystemLEDSheet::SetOnTransfer(void)
{
	SetEnableAddr(0);
	SetEnableLatch(0);
	for(int sheet=0;sheet<SheetCountInSystem;sheet++){
		for(int LED=0;LED<LEDCountInSheet;LED++){
			if(Sheet[sheet].OutEnable[LED]=true)
				SetShiftIn(1);
			else
				SetShiftIn(0);
			SetShftClk(1);
			SetShftClk(0);
		}
		FlushFifo();
	}
	SetEnableLatch(1);
	SetEnableLatch(0);
	FlushFifo();
}
//=======================================================


int		DirectLightControl::LEDWaitTime=180;	//10000;
struct	InitializedMicrosecTimerStruct DirectLightControl::IWaitFunc;
int		FTWriteConter=0;

bool	DirectLightControl::Initial(void)
{
	if(Open()==false){
		return false;
	}

	return true;
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
	FT_STATUS ret=FT_Open (0, &Handle);
	if(ret!=FT_OK){
		Handle=0;
		return false;
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
	Opened=true;
	return true;
}
bool	DirectLightControl::Close(void)
{
	if(Opened==true){
		FT_STATUS ret=FT_Close (Handle);
		if(ret==FT_OK){
			Opened=false;
			return true;
		}
	}
	return false;
}
void	DirectLightControl::FlushFifo(void)
{
	DWORD BytesWriten;
	if(Handle!=0 && FifiCount!=0){
		FTWriteConter++;
		FT_STATUS	ret=FT_Write(Handle, FifiData, FifiCount, &BytesWriten);
		if(ret!=FT_OK || BytesWriten!=FifiCount){
			//GSleep(100);
			ret=FT_Write(Handle, &FifiData[BytesWriten], FifiCount-BytesWriten, &BytesWriten);
		}
	}
	FifiCount=0;
}

void	DirectLightControl::SetShftClk		(int n)
{
	if(n==0)
		Data &= 0xFE;
	else
		Data |= 0x01;
	PutFifo();
}
void	DirectLightControl::SetEnableAddr	(int n)
{
	if(n==0)
		Data &= 0xFD;
	else
		Data |= 0x02;
	PutFifo();
}
void	DirectLightControl::SetShiftIn		(int n)
{
	if(n==0)
		Data &= 0xFB;
	else
		Data |= 0x04;
	PutFifo();
}
void	DirectLightControl::SetEnableLatch	(int n)
{
	if(n==0)
		Data &= 0xF7;
	else
		Data |= 0x08;
	PutFifo();
}
void	DirectLightControl::OutEnable		(int n)
{
	if(n==0)
		Data &= 0xEF;
	else
		Data |= 0x10;
	PutFifo();
}
void	DirectLightControl::Reset			(int n)
{
	if(n==0)
		Data &= 0xDF;
	else
		Data |= 0x20;
	PutFifo();
}

void	DirectLightControl::PutFifo(void)
{
	FifiData[FifiCount]=Data;
	FifiCount++;

	FlushFifo();
}


