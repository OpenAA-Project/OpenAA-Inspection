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
            bool    Save(QIODevice *f);
            bool    Load(QIODevice *f);
        }LineData[16];
        bool    DCEnable;

        LightPattern(void){
            DCEnable=true;
        }
        void    SetAllON(bool ONMode=true);

        bool    Save(QIODevice *f);
        bool    Load(QIODevice *f);
    }LightPatternData[128];

	struct	MotorPluseDecoder
	{
		unsigned short	CounterL;
		unsigned short	CounterH;

        bool    Save(QIODevice *f);
        bool    Load(QIODevice *f);
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
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};

#endif
