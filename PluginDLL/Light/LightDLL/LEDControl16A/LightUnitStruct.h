#if        !defined(LightUnitStruct_h)
#define        LightUnitStruct_h


struct        LightLineUnit
{
	unsigned char	ColorType;        //0:Reg        1:Green        2:Blue        3:IR        4:UV        5:White        6:Other
	unsigned short	MaxCurrent;
};

#define DimCountOfLineData    128

struct        LightUnit
{
        unsigned char        UsageLines;
        struct        LightLineUnit        LineData[DimCountOfLineData];
};



#endif