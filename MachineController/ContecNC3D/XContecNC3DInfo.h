#if	!defined(XContecNC3DInfo_h)
#define	XContecNC3DInfo_h

#include <QIODevice>

class	ContecNCAxis
{
public:

	int		AccelRate;
	int		PulsePerRot;
	int		Pitch;
	int		MaxVelocity;
	int		JogVelocity;
	int		JogPulse;
	int		OriginVelocity;
	int		MaxLength;

	ContecNCAxis(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	int		GetPulseFromMM(double mm);
	double	GetMMFromPulse(double pulse);
};

class	ContecNC3DInfo
{
public:
	ContecNCAxis	AxisX;
	ContecNCAxis	AxisY;
	ContecNCAxis	AxisZ;

	int		StartPosX,StartPosY;
	int		StartVelocity;
	int		ScanLength;
	int		ScanVelocity;
	int		StepLength;
	int		StepVelocity;
	int		PulseZ;
	double	PosZ;
	int		VelocityZ;
	int		ScanCount;
	bool	EnableAreaSensor;
	bool	EnableDoorSensor;

	ContecNC3DInfo(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};



#endif