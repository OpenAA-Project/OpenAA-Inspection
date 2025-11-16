#if	!defined(XContecNC2DInfo_h)
#define	XContecNC2DInfo_h

#include <QIODevice>

class	ContecNC2DInfo
{
public:

	int		StartPosX,StartPosY;
	int		StartVelocity;
	int		AccelRate;
	int		ScanPulse;
	int		ScanVelocity;
	int		StepPulse;
	int		StepVelocity;
	int		ScanCount;
	int		CurentScan;
	int		OriginVelocity;
	int		MaxPulseX;
	int		MaxPulseY;

	ContecNC2DInfo(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif