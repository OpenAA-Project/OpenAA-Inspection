#if	!defined(DeviceStruct_h)
#define	DeviceStruct_h
#include "XTypeDef.h"

class   QIODevice;

#pragma pack(push, 1)
struct  GioRealStruct
{
    bool     PIOAIN0  :1;
    bool     PIOAIN1  :1;
    bool     PIOAIN2  :1;
    bool     PIOAIN3  :1;
    bool     PIOBIN0  :1;
    bool     PIOBIN1  :1;
    bool     PIOBIN2  :1;
    bool     PIOBIN3  :1;
    bool     PIOCIN0  :1;
    bool     PIOCIN1  :1;
    bool     PIOCIN2  :1;
    bool     PIOCIN3  :1;
    bool     PIODIN0  :1;
    bool     PIODIN1  :1;
    bool     PIODIN2  :1;
    bool     PIODIN3  :1;
    bool     PIOAOUT0 :1;
    bool     PIOAOUT1 :1;
    bool     PIOAOUT2 :1;
    bool     PIOAOUT3 :1;
    bool     PIOBOUT0 :1;
    bool     PIOBOUT1 :1;
    bool     PIOBOUT2 :1;
    bool     PIOBOUT3 :1;
    bool     PIOCOUT0 :1;
    bool     PIOCOUT1 :1;
    bool     PIOCOUT2 :1;
    bool     PIOCOUT3 :1;
    bool     PIODOUT0 :1;
    bool     PIODOUT1 :1;
    bool     PIODOUT2 :1;
    bool     PIODOUT3 :1;
    bool     GIN0     :1;
    bool     GIN1     :1;
    bool     GIN2     :1;
    bool     GIN3     :1;
    bool     GOUT0    :1;
    bool     GOUT1    :1;
    bool     GOUT2    :1;
    bool     GOUT3    :1;
    bool     GOUT4    :1;
    bool     GOUT5    :1;
    bool     GOUT6    :1;
    bool     GOUT7    :1;
    bool     TRGIN0   :1;
    bool     TRGIN1   :1;
    bool     TRGIN2   :1;
    bool     TRGIN3   :1;
    bool    OuterSW   :1;
    bool    ExtDirect :1;
};
#pragma pack(pop)

struct  GioFixedStruct
{
    unsigned long   ConveyerLength;
    unsigned long   GateOpenTerm;
    unsigned long   MulInputA;
    unsigned long   MulInputB;
    unsigned long   TriggerFilterMinOFF;
    unsigned long   TriggerFilterMinON;
    unsigned long   DelayFrameTriggerA;
    unsigned long   DelayFrameTriggerB;
    unsigned long   DelayFrameTriggerC;
    unsigned long   DelayFrameTriggerD;
    unsigned long   DefDelayedCount;
    double          TriggerDelayParameter;
    bool            FlipFrameTriggerModeA;
    bool            FlipFrameTriggerModeB;
    bool            FlipFrameTriggerModeC;
    bool            FlipFrameTriggerModeD;
    double          ResultOutParameter;

	GioFixedStruct(void){
		ConveyerLength		=2500;
		GateOpenTerm		=300;
		MulInputA			=700;
		MulInputB			=700;
		TriggerFilterMinOFF	=10;
		TriggerFilterMinON	=10;
		DelayFrameTriggerA	=16000;
		DelayFrameTriggerB	=700;
		DelayFrameTriggerC	=16000;
		DelayFrameTriggerD	=500;
        DefDelayedCount     =350;
        TriggerDelayParameter   =400000;
        FlipFrameTriggerModeA   =false;
        FlipFrameTriggerModeB   =false;
        FlipFrameTriggerModeC   =false;
        FlipFrameTriggerModeD   =false;
        ResultOutParameter      =400000;
	}
	
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};

#pragma pack(push, 1)
struct  TimingData
{
    DWORD   CurrentMiliSec;
    struct  GioRealStruct  RealData;
};
#pragma pack(pop)

struct	GioStruct
{
    struct  GioFixedStruct  GioFixedData;

    //Not saved
	unsigned char	RMode;
	bool			TestMode;
	bool			TestLEDReg;
	bool			RegLEDOut[2];
    struct  GioRealStruct  RealData;

    unsigned char	TRGAOUT :4;
    unsigned char	TRGBOUT :4;
    unsigned char	TRGCOUT :4;
    unsigned char	TRGDOUT :4;
    bool	ModePulseHalfA  :1;
    bool	ModePulseHalfB  :1;
    bool	AD_CS           :1;
    bool	AD_DIN          :1;
    bool	AD_CLK          :1;
    bool	AD_DOUT         :1;
	unsigned long   MotorPulseCounter;
    unsigned long   MotorPulseCounter2;

    unsigned long   	TotalCount;
    unsigned long   	OKCount;
    unsigned long   	NGCount;
    unsigned long   	TMCount;	//TimeOut
    bool	ResetCounter    :1;

    GioStruct(void){
        TestLEDReg	=false;
    }
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};

#define BitTopOK        0x01
#define BitTopNG        0x02
#define BitBottomOK     0x20
#define BitBottomNG     0x40

#endif
