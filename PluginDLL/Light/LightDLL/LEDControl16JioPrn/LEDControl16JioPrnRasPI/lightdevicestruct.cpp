#if	!defined(CamTriggerStruct_H)
#define	CamTriggerStruct_h

#include <QBuffer>
#include <QIODevice>
#include "LightDeviceStruct.h"
#include "XGeneralFunc.h"
#include "LEDControl16JioPrnRasPIMain.h"

LightBoard::__LineInfo::__LineInfo(void)
{
    for(int i=0;i<sizeof(TargetValue)/sizeof(TargetValue[0]);i++){
        TargetValue[i]=4000;    //Max=5000  (==Base)
	}
}

bool    LightBoard::__LineInfo::Save(QIODevice *f)
{
    int	N=sizeof(TargetValue)/sizeof(TargetValue[0]);
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
    for(int i=0;i<sizeof(TargetValue)/sizeof(TargetValue[0]) && i<N;i++){
		if(::Load(f,TargetValue[i])==false){
			return false;
		}
	}
    for(int i=0;i<(N-sizeof(TargetValue)/sizeof(TargetValue[0]));i++){
        uint32	Dummy;
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
    int	N=sizeof(LineInfo)/sizeof(LineInfo[0]);
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
    for(int i=0;i<sizeof(LineInfo)/sizeof(LineInfo[0]) && i<N;i++){
		if(LineInfo[i].Load(f)==false){
			return false;
		}
	}
    for(int i=0;i<(N-sizeof(LineInfo)/sizeof(LineInfo[0]));i++){
		__LineInfo	Dummy;
		if(Dummy.Load(f)==false){
			return false;
		}
	}
	
	return true;
}

bool    LightBoard::SetTestLED(LEDControl16JioPrnRasPIMain *p,bool b)
{
    int Data[2];
    Data[0]=0xF0;
    Data[1]=(b==true)?1:0;
    //WriteRegister(DipSW ,Data ,2);
}

bool    LightBoard::SetAllON(LEDControl16JioPrnRasPIMain *p,bool b)
{
    AllON=b;
    p->SendLightBoardON(Brd,b);
}
bool    LightBoard::SetCurrentPatternNo(LEDControl16JioPrnRasPIMain *p,int n)
{
    int Data[2];
    Data[0]=0xF2;
    Data[1]=n;
    //WriteRegister(DipSW ,Data ,2);
}
bool    LightBoard::GetLightData(LEDControl16JioPrnRasPIMain *p,int PatternNo)
{
    //WriteRegisterData(0x00+PatternNo);
    
    int Data[MaxCountLines*8];
    //ReadRegister4Bit(DipSW ,Data ,MaxCountLines*8);
    for(int i=0;i<MaxCountLines;i++){
        LineInfo[PatternNo].TargetValue[i]  =((((uint32)Data[i*8+0]))&0x0FL)
                                            +((((uint32)Data[i*8+1])<<4)&0xF0L)
                                            +((((uint32)Data[i*8+2])<<8)&0xF00L)
                                            +((((uint32)Data[i*8+3])<<12)&0xF000L)
                                            +((((uint32)Data[i*8+4])<<16)&0xF0000L)
                                            +((((uint32)Data[i*8+5])<<20)&0xF00000L)
                                            +((((uint32)Data[i*8+6])<<24)&0xF000000L)
                                            +((((uint32)Data[i*8+7])<<28)&0xF0000000L);
    }
}

bool    LightBoard::SetLightData(LEDControl16JioPrnRasPIMain *p,int PatternNo)
{
    int Dim[MaxCountLines*4+4];
    Dim[0]=0x01;
    Dim[1]=PatternNo;
    for(int i=0;i<MaxCountLines;i++){
        Dim[2+i*4+0]= LineInfo[PatternNo].TargetValue[i] & 0xFF;
        Dim[2+i*4+1]=(LineInfo[PatternNo].TargetValue[i]>>8) & 0xFF;
        Dim[2+i*4+2]=(LineInfo[PatternNo].TargetValue[i]>>16) & 0xFF;
        Dim[2+i*4+3]=(LineInfo[PatternNo].TargetValue[i]>>24) & 0xFF;
    }
    //WriteRegister(DipSW ,Dim ,MaxCountLines*4+2);
}
bool    LightBoard::GetCurrentValue(LEDControl16JioPrnRasPIMain *p)
{
    //WriteRegisterData(0xFE);
    
    int Dim[MaxCountLines*4];
    //ReadRegister4Bit(DipSW ,Dim ,MaxCountLines*4);
    for(int i=0;i<MaxCountLines;i++){
        CurrentValue[i]=p->ReadLightCurrentValue(Brd,i);
    }
}

#endif
