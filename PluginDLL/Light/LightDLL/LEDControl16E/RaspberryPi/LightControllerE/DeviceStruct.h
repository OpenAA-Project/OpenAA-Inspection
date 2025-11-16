#if	!defined(DeviceStruct_h)
#define	DeviceStruct_h

struct	EOIStruct
{
	unsigned long	CamResolution;
	unsigned long	CamFrameTriggerL;
	unsigned long	CamFrameTriggerH;
	unsigned char	OutExt;
	bool	RESET;
	bool	TestLEDReg;
	bool	CamOut;
	bool	LEDOutToPanel[2];

    EOIStruct(void){
        CamResolution=10;
        CamFrameTriggerL=10;
        CamFrameTriggerH=20;
        OutExt=0;
        RESET=false;
        TestLEDReg=false;
        CamOut=false;
        LEDOutToPanel[0]=false;
        LEDOutToPanel[1]=false;
    }
};



#endif
