#if        !defined(LightUnitStruct_h)
#define        LightUnitStruct_h


struct        LightLineUnit
{
	int		ColorType;        //1:Reg        2:Green       3:Blue       4:IR        5:UV        6:White        7:Other
	int		BoardID;
	int		LineNo;
	int		MaxValue;
	wchar_t	Comment[64];

	LightLineUnit(void){
		ColorType	=0;
		BoardID		=-1;
		LineNo		=-1;
		MaxValue	=0;
		Comment[0]	=0;
	}
};

#define DimCountOfLineData    128


#endif