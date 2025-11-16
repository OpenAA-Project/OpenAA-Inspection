#if	!defined(CamTriggerStruct_H)
#define	CamTriggerStruct_h

#include <QBuffer>

struct	LightBoard
{
	struct	LightPattern
	{
		struct	LightLine
		{
			unsigned long	MicroAmp;
            bool			ON;

            int GetPGAChannel(void);//1Bit
            int GetDAGainX2(void);  //1Bit
            int GetPGAGain(void);   //3Bit
            int GetDAValue(void);   //12Bit
            int GetDCClock(void);   //8Bit
            
            LightLine(void){
                MicroAmp=100000;
            	ON=false;
            }
		}LineData[16];
        bool    DCEnable;

        LightPattern(void){
            DCEnable=true;
        }
        void    SetAllON(bool ONMode=true);

	}LightPatternData[128];

	struct	MotorPluseDecoder
	{
		unsigned short	CounterL;
		unsigned short	CounterH;
	}MotorPluseDecoderData[16];
	
	bool	CmdSetAnalog;
	bool	CmdLoad;
	bool	CmdSetLineOn;
	bool	TestLEDReg;
	int		CurrentPatternNo;
	
	LightBoard(void){
		CmdSetAnalog	=false;
		CmdLoad			=false;
		CmdSetLineOn	=false;
		TestLEDReg		=false;
		CurrentPatternNo=0;
	}
};

inline	int LightBoard::LightPattern::LightLine::GetPGAChannel(void)//1Bit
{
    if(MicroAmp<320000) //100mA
        return 1;
    else
        return 0;
}
inline	int LightBoard::LightPattern::LightLine::GetDAGainX2(void)  //1Bit
{
    if(MicroAmp<2000)
        return 1;   //x2
    return 0;
}
inline	int LightBoard::LightPattern::LightLine::GetPGAGain(void)   //3Bit
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
inline	int LightBoard::LightPattern::LightLine::GetDAValue(void)   //12Bit
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
inline	int LightBoard::LightPattern::LightLine::GetDCClock(void)   //8Bit
{
    return 168;
}
inline	void    LightBoard::LightPattern::SetAllON(bool ONMode)
{
    for(int i=0;i<16;i++){
        LineData[i].ON=ONMode;
    }
}

#endif
