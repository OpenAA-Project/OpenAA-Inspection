#include <QIODevice>
#include "LightDeviceStruct.h"
#include "XGeneralFunc.h"


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
    int Data[2];
    Data[0]=0xF0;
    Data[1]=(b==true)?1:0;
    WriteRegister(DipSW ,Data ,2);
    return true;
}

bool    LightBoard::SetAllON(bool b)
{
    AllON=b;
    int Data[2];
    Data[0]=0xF1;
    Data[1]=(b==true)?1:0;
    WriteRegister(DipSW ,Data ,2);
    return true;
}
bool    LightBoard::SetCurrentPatternNo(int n)
{
    int Data[2];
    Data[0]=0xF2;
    Data[1]=n;
    WriteRegister(DipSW ,Data ,2);
    return true;
}
bool    LightBoard::GetLightData(int PatternNo)
{
    WriteRegisterData(0x00+PatternNo);
    
    int Data[MaxCountLines*8];
    ReadRegister4Bit(DipSW ,Data ,MaxCountLines*8);
    for(int i=0;i<MaxCountLines;i++){
        LineInfo[i].TargetValue[PatternNo]  =((((uint32)Data[i*8+0]))&0x0FL)
                                            +((((uint32)Data[i*8+1])<<4)&0xF0L)
                                            +((((uint32)Data[i*8+2])<<8)&0xF00L)
                                            +((((uint32)Data[i*8+3])<<12)&0xF000L)
                                            +((((uint32)Data[i*8+4])<<16)&0xF0000L)
                                            +((((uint32)Data[i*8+5])<<20)&0xF00000L)
                                            +((((uint32)Data[i*8+6])<<24)&0xF000000L)
                                            +((((uint32)Data[i*8+7])<<28)&0xF0000000L);
    }
    return true;
}

bool    LightBoard::SetLightData(int PatternNo)
{
    int Dim[MaxCountLines*4+4];
    Dim[0]=0x01;
    Dim[1]=PatternNo;
    for(int i=0;i<MaxCountLines;i++){
        Dim[2+i*4+0]=LineInfo[i].TargetValue[PatternNo] & 0xFF;
        Dim[2+i*4+1]=(LineInfo[i].TargetValue[PatternNo]>>8) & 0xFF;
        Dim[2+i*4+2]=(LineInfo[i].TargetValue[PatternNo]>>16) & 0xFF;
        Dim[2+i*4+3]=(LineInfo[i].TargetValue[PatternNo]>>24) & 0xFF;
    }
    WriteRegister(DipSW ,Dim ,MaxCountLines*4+2);
    return true;
}
bool    LightBoard::GetCurrentValue(void)
{
    WriteRegisterData(0xFE);
    
    int Dim[MaxCountLines*4];
    ReadRegister4Bit(DipSW ,Dim ,MaxCountLines*4);
    for(int i=0;i<MaxCountLines;i++){
        LineInfo[i].CurrentValue=((((uint32)Dim[i*4+0]))&0xF)
                                +((((uint32)Dim[i*4+1])<<4)&0xF0)
                                +((((uint32)Dim[i*4+2])<<8)&0xF00)
                                +((((uint32)Dim[i*4+3])<<12)&0xF000);
    }
    return true;
}
