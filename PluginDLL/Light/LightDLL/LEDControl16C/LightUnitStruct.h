#if        !defined(LightUnitStruct_h)
#define        LightUnitStruct_h


struct        LightLineUnit
{
	unsigned char	ColorType;        //1:Reg        2:Green       3:Blue       4:IR        5:UV        6:White        7:Other
	unsigned short	MaxCurrent;
};

#define DimCountOfLineData    128

struct        LightUnit
{
        unsigned char        UsageLines;
        struct        LightLineUnit        LineData[DimCountOfLineData];
};



#endif