#include "LightDeviceStruct.h"
#include "NListRPi.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"


int LightBoard::LightPattern::LightLine::GetPGAChannel(void)//1Bit
{
    if(MicroAmp<320000) //100mA
        return 1;
    else
        return 0;
}
int LightBoard::LightPattern::LightLine::GetDAGainX2(void)  //1Bit
{
    if(MicroAmp<2000)
        return 1;   //x2
    return 0;
}
int LightBoard::LightPattern::LightLine::GetPGAGain(void)   //3Bit
{
    if(MicroAmp<2000)
        return 7;   //x32
    if(MicroAmp<5000)
        return 7;
    if(MicroAmp<10000)
        return 6;   //X16
    if(MicroAmp<20000)
        return 4;   //X8
    if(MicroAmp<40000)
        return 2;   //x4
    if(MicroAmp<80000)
        return 1;   //x2
    if(MicroAmp<100000)
        return 0;
    if(MicroAmp<200000)
        return 4;   //x8
    if(MicroAmp<400000)
        return 2;   //x4
    if(MicroAmp<800000)
        return 1;   //x2
    if(MicroAmp<=1600000)
        return 0;   //x1
    return 0x5;
}
int LightBoard::LightPattern::LightLine::GetDAValue(void)   //12Bit
{
    if(MicroAmp<1215)
        return 1215;
    if(MicroAmp<2000)
        return 0.8*4096/1.32*2000.0/MicroAmp;
    if(MicroAmp<=5000)
        return 0.8*4096/3.2*5000.0/MicroAmp;
    if(MicroAmp<=10000)
        return 0.8*4096/3.2*10000.0/MicroAmp;
    if(MicroAmp<=20000)
        return 0.8*4096/3.2*20000.0/MicroAmp;
    if(MicroAmp<=40000)
        return 0.8*4096/3.2*40000.0/MicroAmp;
    if(MicroAmp<=80000)
        return 0.8*4096/3.2*80000.0/MicroAmp;
    if(MicroAmp<=100000)
        return 0.8*4096/3.2*100000.0/MicroAmp;
    if(MicroAmp<=200000)
        return 0.8*4096/3.2*200000.0/MicroAmp;
    if(MicroAmp<=400000)
        return 0.8*4096/3.2*400000.0/MicroAmp;
    if(MicroAmp<=800000)
        return 0.8*4096/3.2*800000.0/MicroAmp;
    if(MicroAmp<=1600000)
        return 0.8*4096/3.2*1600000.0/MicroAmp;
    return 1301;
}
int LightBoard::LightPattern::LightLine::GetDCClock(void)   //8Bit
{
    return 168;
}
bool    LightBoard::LightPattern::LightLine::Save(QIODevice *f)
{
    if(::Save(f,MicroAmp)==false)
        return false;
    if(::Save(f,ON)==false)
        return false;
    return true;
}

bool    LightBoard::LightPattern::LightLine::Load(QIODevice *f)
{
    if(::Load(f,MicroAmp)==false)
        return false;
    if(::Load(f,ON)==false)
        return false;
    return true;
}

void    LightBoard::LightPattern::SetAllON(bool ONMode)
{
    for(int i=0;i<16;i++){
        LineData[i].ON=ONMode;
    }
}
bool    LightBoard::LightPattern::Save(QIODevice *f)
{
    int32   Ver=1;

    if(::Save(f,Ver)==false)
        return false;
    int32   N=sizeof(LineData)/sizeof(LineData[0]);
    if(::Save(f,N)==false)
        return false;
    for(int i=0;i<N;i++){
        if(LineData[i].Save(f)==false){
            return false;
        }
    }
    if(::Save(f,DCEnable)==false)
        return false;
    return true;
}

bool    LightBoard::LightPattern::Load(QIODevice *f)
{
    int32   Ver;

    if(::Load(f,Ver)==false)
        return false;
    int32   N=sizeof(LineData)/sizeof(LineData[0]);
    int32   iN;
    if(::Load(f,iN)==false)
        return false;
    for(int i=0;i<N && i<iN;i++){
        if(LineData[i].Load(f)==false){
            return false;
        }
    }
    if(::Load(f,DCEnable)==false)
        return false;
    return true;
}

bool    LightBoard::MotorPluseDecoder::Save(QIODevice *f)
{
    int32   Ver=1;

    if(::Save(f,Ver)==false)
        return false;
    if(::Save(f,CounterL)==false)
        return false;
    if(::Save(f,CounterH)==false)
        return false;
    return true;
}

bool    LightBoard::MotorPluseDecoder::Load(QIODevice *f)
{
    int32   Ver;

    if(::Load(f,Ver)==false)
        return false;
    if(::Load(f,CounterL)==false)
        return false;
    if(::Load(f,CounterH)==false)
        return false;
    return true;
}

bool    LightBoard::Save(QIODevice *f)
{
    int32   Ver=1;

    if(::Save(f,Ver)==false)
        return false;

    int32   NP=sizeof(LightPatternData)/sizeof(LightPatternData[0]);
    if(::Save(f,NP)==false)
        return false;
    for(int i=0;i<NP;i++){
        if(LightPatternData[i].Save(f)==false){
           return false;
        }
    }
    int32   NK=sizeof(MotorPluseDecoderData)/sizeof(MotorPluseDecoderData[0]);
    if(::Save(f,NK)==false)
        return false;
    for(int i=0;i<NK;i++){
        if(MotorPluseDecoderData[i].Save(f)==false){
           return false;
        }
    }
    return true;
 }

bool    LightBoard::Load(QIODevice *f)
{
    int32   Ver;

    if(::Load(f,Ver)==false)
        return false;

    int32   NP=sizeof(LightPatternData)/sizeof(LightPatternData[0]);
    int32   iNP;
    if(::Load(f,NP)==false)
        return false;
    for(int i=0;i<NP && i<iNP;i++){
        if(LightPatternData[i].Load(f)==false){
           return false;
        }
    }
    int32   NK=sizeof(MotorPluseDecoderData)/sizeof(MotorPluseDecoderData[0]);
    int32   iNK;
    if(::Load(f,iNK)==false)
        return false;
    for(int i=0;i<NK && i<iNK;i++){
        if(MotorPluseDecoderData[i].Load(f)==false){
           return false;
        }
    }
    return true;
 }


