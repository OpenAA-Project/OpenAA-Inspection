#if        !defined(XLightInBoard_h)
#define        XLightInBoard_h


struct LightLineData
{
	unsigned short	BaseCounter;
	unsigned short  HighCounter;
	bool			Mask;
};

struct LightPattern
{
	struct LightLineData	LineData[16];
};

#endif