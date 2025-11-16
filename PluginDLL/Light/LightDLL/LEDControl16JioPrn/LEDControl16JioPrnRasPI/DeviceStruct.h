#if	!defined(DeviceStruct_h)
#define	DeviceStruct_h
#include "XTypeDef.h"

class   QIODevice;
#define MaxDipSW    4

#pragma pack(push, 1)

struct  StructBit8
{
    union{
        struct{
            bool    Bit0    :1;
            bool    Bit1    :1;
            bool    Bit2    :1;
            bool    Bit3    :1;
            bool    Bit4    :1;
            bool    Bit5    :1;
            bool    Bit6    :1;
            bool    Bit7    :1;
        };
        unsigned char   Data;
    };
};
struct  StructBit16
{
    union{
        struct{
            bool    Bit0    :1;
            bool    Bit1    :1;
            bool    Bit2    :1;
            bool    Bit3    :1;
            bool    Bit4    :1;
            bool    Bit5    :1;
            bool    Bit6    :1;
            bool    Bit7    :1;
        };
        unsigned char   Data0;
    };
    union{
        struct{
            bool    Bit8    :1;
            bool    Bit9    :1;
            bool    Bit10    :1;
            bool    Bit11    :1;
            bool    Bit12    :1;
            bool    Bit13    :1;
            bool    Bit14    :1;
            bool    Bit15    :1;
        };
        unsigned char   Data1;
    };
};
struct  JioRealStruct
{
    StructBit8    PIOAIN;
    StructBit8    PIOBIN;
    StructBit8    PIOCIN;
    StructBit8    PIODIN;
    struct  StructBit16    PIOAOUT;
    struct  StructBit16    PIOBOUT;
    struct  StructBit16    PIOCOUT;
    struct  StructBit16    PIODOUT;
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
    bool     TRGIN0     :1;
    bool     TRGIN1     :1;
    bool     TRGIN2     :1;
    bool     TRGIN3     :1;
    bool    OuterSW   :1;
    bool    ExtDirect :1;
};
#pragma pack(pop)

struct  JioFixedStruct
{
    unsigned long   ConveyerLength;
    unsigned long   GateOpenTerm;
    unsigned long   MulInputA;
    unsigned long   MulInputB;
    unsigned long   MulInputC;
    unsigned long   MulInputD;
    unsigned long   TriggerFilterMinOFF;
    unsigned long   TriggerFilterMinON;
    unsigned long   TriggerFilterWorkLen;
    unsigned long   DelayFrameTriggerA;
    unsigned long   DelayFrameTriggerB;
    unsigned long   DelayFrameTriggerC;
    unsigned long   DelayFrameTriggerD;
    unsigned long   ResultAAcceptStart;
    unsigned long   ResultBAcceptStart;
    unsigned long   ResultCAcceptStart;
    unsigned long   ResultDAcceptStart;
    unsigned long   ResultACloseAccept;
    unsigned long   ResultBCloseAccept;
    unsigned long   ResultCCloseAccept;
    unsigned long   ResultDCloseAccept;
    double          TriggerDelayParameter;
    bool            FlipFrameTriggerModeA;
    bool            FlipFrameTriggerModeB;
    bool            FlipFrameTriggerModeC;
    bool            FlipFrameTriggerModeD;
    unsigned char   SelectEncA;         //3bit
    unsigned char   SelectEncB;         //3bit
    unsigned char   SelectEncC;         //3bit
    unsigned char   SelectEncD;         //3bit
    unsigned char   SelectTriggerIn;    //3bit
    unsigned long   DelayedCountForStack;
    bool            ModeOutResultError;

    JioFixedStruct(void){
		ConveyerLength		=2500;
		GateOpenTerm		=300;
		MulInputA			=700;
		MulInputB			=700;
        MulInputC			=700;
        MulInputD			=700;
		TriggerFilterMinOFF	=10;
		TriggerFilterMinON	=10;
        TriggerFilterWorkLen=10;
		DelayFrameTriggerA	=16000;
		DelayFrameTriggerB	=700;
		DelayFrameTriggerC	=16000;
		DelayFrameTriggerD	=500;
		ResultAAcceptStart	=1000;
		ResultBAcceptStart	=1500;
		ResultCAcceptStart	=1000;
		ResultDAcceptStart	=1500;
		ResultACloseAccept	=1000;
		ResultBCloseAccept	=1500;
		ResultCCloseAccept	=0;
		ResultDCloseAccept	=0;
        TriggerDelayParameter   =400000;
        FlipFrameTriggerModeA   =false;
        FlipFrameTriggerModeB   =false;
        FlipFrameTriggerModeC   =false;
        FlipFrameTriggerModeD   =false;
        SelectEncA              =0; //3bit
        SelectEncB              =0; //3bit
        SelectEncC              =0; //3bit
        SelectEncD              =0; //3bit
        SelectTriggerIn         =0; //3bit
        DelayedCountForStack    =0;
        ModeOutResultError      =false;
	}
	
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};

#pragma pack(push, 1)
struct  TimingData
{
    DWORD   CurrentMiliSec;
    struct  JioRealStruct  RealData;
};
#pragma pack(pop)

struct	JioStruct
{
    struct  JioFixedStruct  JioFixedData;

    //Not saved
	unsigned char	RMode;
	bool			TestMode;
	bool			TestLEDReg;
	bool			RegLEDOut[2];
    struct  JioRealStruct  RealData;

    unsigned char	TRGAOUT :4;
    unsigned char	TRGBOUT :4;
    unsigned char	TRGCOUT :4;
    unsigned char	TRGDOUT :4;
    bool	ModePulseHalfA  :1;
    bool	ModePulseHalfB  :1;

	unsigned long   MotorPulseCounter;
    unsigned long   MotorPulseCounter2;
    int AllocateGOut[8];
    unsigned long   	TotalCount;
    unsigned long   	OKCount;
    unsigned long   	NGCount;
    unsigned long   	TMCount;	//TimeOut
    bool	ResetCounter    :1;

    JioStruct(void){
        TestLEDReg	=false;
        for(int i=0;i<sizeof(AllocateGOut)/sizeof(AllocateGOut[0]);i++){
            AllocateGOut[i]=i;
        }
        TotalCount=0;
        OKCount=0;
        NGCount=0;
        TMCount=0;
    }
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};

#define BitTopOK        0x01
#define BitTopNG        0x02
#define BitBottomOK     0x20
#define BitBottomNG     0x40

#endif
