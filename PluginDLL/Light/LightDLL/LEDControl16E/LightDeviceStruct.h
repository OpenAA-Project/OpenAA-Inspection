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
			int				ON;
		}LineData[16];
	}LightPatternData[128];

	struct	MotorPluseDecoder
	{
		unsigned short	CounterL;
		unsigned short	CounterH;
	}MotorPluseDecoderData[16];
};

#endif