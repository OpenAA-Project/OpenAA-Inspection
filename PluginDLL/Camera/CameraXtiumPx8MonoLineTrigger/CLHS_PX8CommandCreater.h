#pragma once

#include <QString>
#include <QIODevice>


class CameraCommand;
class	featureCtrl;

class CLHS_PX8Setting
{
public:
	double	LineRate;
	double	ExposureTime;	//Microsec
	bool	TDIDirection;

	double	GainRed;
	int		OffsetRed;

	double	GainRedL;
	int		OffsetRedL;

	double	GainRedR;
	int		OffsetRedR;

	double	MultipleRed		;
	int		OffsetXRed		;
	int		OffsetYRed		;

	//LUT
	static	const int	CamDepth=256;		//8bit
	int			RedCustomLut	[CamDepth];
	int			RedBrightness;			//Red
	int			RedContrast;
	int			RedGamma;
	int			RedFloor;
	int			RedCeiling;
	bool		RedApply;

	//Binning
	int			HorizontalBinning;
	int			VerticalBinning;
	bool		LeftRight;		//Reverse left-right

	bool		ExternalTrigger;
	bool		AutoBlackLevel;
	bool		CalibrateFPN;
	int			LightOffMilisec;
	int			LightOnMilisec;

	CLHS_PX8Setting();

public:

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	LoadFromCam(featureCtrl *f);
	bool	StoreToCam(featureCtrl *f);
};
