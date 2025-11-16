#include "XTypeDef.h"
#include <QBuffer>
#include <QIODevice>
#include "LightDeviceStruct.h"
#include "XGeneralFunc.h"
#include "LEDControl16H.h"

LightBoard::__LineInfo::__LineInfo(void)
{
	for(int i=0;i<MaxCountLEDPattern;i++){
		TargetValue[i]=0.0;
	}
	CurrentValue=0;
}

bool    LightBoard::__LineInfo::Save(QIODevice *f)
{
	int	N=MaxCountLEDPattern;
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(::Save(f,TargetValue[i])==false){
			return false;
		}
	}
	return true;
}
bool    LightBoard::__LineInfo::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<MaxCountLEDPattern && i<N;i++){
		if(::Load(f,TargetValue[i])==false){
			return false;
		}
	}
	for(int i=0;i<(N-MaxCountLEDPattern);i++){
		double	Dummy;
		if(::Load(f,Dummy)==false){
			return false;
		}
	}
	
	return true;
}

//=============================================================

LightBoard::LightBoard(void)
{
	DipSW=-1;
    AllON=false;
}

void	LightBoard::SetParent(LEDControl16HPanel *p)
{
	Parent=p;
}

bool    LightBoard::Save(QIODevice *f)
{
    if(::Save(f,AllON)==false)
        return false;
    int	N=MaxCountLines;
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(LineInfo[i].Save(f)==false){
			return false;
		}
	}
	return true;
}
bool    LightBoard::Load(QIODevice *f)
{
    if(::Load(f,AllON)==false)
        return false;
    int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<MaxCountLines && i<N;i++){
		if(LineInfo[i].Load(f)==false){
			return false;
		}
	}
	for(int i=0;i<(N-MaxCountLines);i++){
		__LineInfo	Dummy;
		if(Dummy.Load(f)==false){
			return false;
		}
	}
	
	return true;
}

bool    LightBoard::SetTestLED(bool b)
{
    BYTE Data[2];
    Data[0]=0xF0;
    Data[1]=(b==true)?1:0;
    return Parent->WriteRegister(DipSW ,Data ,2);
}

bool    LightBoard::SetAllON(bool b)
{
    AllON=b;
    BYTE Data[2];
    Data[0]=0xF1;
    Data[1]=(b==true)?1:0;
    return Parent->WriteRegister(DipSW ,Data ,2);
}
bool    LightBoard::SetCurrentPatternNo(int n)
{
    BYTE Data[2];
    Data[0]=0xF2;
    Data[1]=n;
    return Parent->WriteRegister(DipSW ,Data ,2);
}
bool    LightBoard::GetLightData(int PatternNo)
{
    BYTE Data[MaxCountLines*8];
	Data[0]=0xF3;
    Data[1]=PatternNo;
    
	int	DataLen;
    if(Parent->ReadRegister(DipSW ,Data ,2 ,DataLen,sizeof(Data))==false)
		return false;

	int	Len=DataLen/4;
    for(int i=0;i<MaxCountLines && i<Len;i++){
        LineInfo[i].TargetValue[PatternNo]  =((((uint32)Data[i*4+0]))	 &0xFFL)
                                            +((((uint32)Data[i*4+1])<<8) &0xFF00L)
                                            +((((uint32)Data[i*4+2])<<16)&0xFF0000L)
                                            +((((uint32)Data[i*4+3])<<24)&0xFF000000L);
    }
	return true;
}

bool    LightBoard::SetLightData(int PatternNo)
{
    BYTE Dim[MaxCountLines*4+4];
    Dim[0]=0xF4;
    Dim[1]=PatternNo;
    for(int i=0;i<MaxCountLines;i++){
        Dim[2+i*4+0]=LineInfo[i].TargetValue[PatternNo] & 0xFF;
        Dim[2+i*4+1]=(LineInfo[i].TargetValue[PatternNo]>>8) & 0xFF;
        Dim[2+i*4+2]=(LineInfo[i].TargetValue[PatternNo]>>16) & 0xFF;
        Dim[2+i*4+3]=(LineInfo[i].TargetValue[PatternNo]>>24) & 0xFF;
    }
    return Parent->WriteRegister(DipSW ,Dim ,MaxCountLines*4+2);
}
bool    LightBoard::GetCurrentValue(void)
{
    BYTE Data[MaxCountLines*4];
    Data[0]=0xF5;
    
	int	DataLen;
    if(Parent->ReadRegister(DipSW ,Data ,1,DataLen,sizeof(Data))==false)
		return false;

	int	Len=DataLen/4;
    for(int i=0;i<MaxCountLines && i<Len;i++){
        LineInfo[i].CurrentValue=((((uint32)Data[i*4+0])	)&0xFF)
                                +((((uint32)Data[i*4+1])<<8	)&0xFF00)
                                +((((uint32)Data[i*4+2])<<16)&0xFF0000)
                                +((((uint32)Data[i*4+3])<<24)&0xFF000000);
    }
	return true;
}
