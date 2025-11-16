#pragma once

#include <QString>
#include <QIODevice>
#include "XCameraCommon.h"

class CameraCommand;
class	featureCtrl;

class CLHS_PX8Setting
{
public:
	double	LineRate;
	double	BrightValue;
	double	ExposureTime;	//Microsec
	bool	TDIDirection;

	double	GainRed;
	double	GainGreen;
	double	GainBlue;
	int		OffsetRed;
	int		OffsetGreen;
	int		OffsetBlue;

	double	GainRedL;
	double	GainGreenL;
	double	GainBlueL;
	int		OffsetRedL;
	int		OffsetGreenL;
	int		OffsetBlueL;

	double	GainRedR;
	double	GainGreenR;
	double	GainBlueR;
	int		OffsetRedR;
	int		OffsetGreenR;
	int		OffsetBlueR;

	double	MultipleRed		;
	double	MultipleGreen	;
	double	MultipleBlue	;
	int		OffsetXRed		;
	int		OffsetXGreen	;
	int		OffsetXBlue		;
	int		OffsetYRed		;
	int		OffsetYGreen	;
	int		OffsetYBlue		;

	//LUT
	static	const int	CamDepth=256;		//8bit
	int			RedCustomLut	[CamDepth];
	int			GreenCustomLut	[CamDepth];
	int			BlueCustomLut	[CamDepth];
	int			RedBrightness;			//Red
	int			RedContrast;
	int			RedGamma;
	int			RedFloor;
	int			RedCeiling;
	bool		RedApply;
	int			GreenBrightness;		//Green
	int			GreenContrast;
	int			GreenGamma;
	int			GreenFloor;
	int			GreenCeiling;
	bool		GreenApply;
	int			BlueBrightness;		//Blue
	int			BlueContrast;
	int			BlueGamma;
	int			BlueFloor;
	int			BlueCeiling;
	bool		BlueApply;

	//Binning
	int			HorizontalBinning;
	int			VerticalBinning;
	bool		LeftRight;		//Reverse left-right
	bool		CameraControl;

	bool		ExternalTrigger;
	bool		AutoBlackLevel;
	bool		CalibrateFPN;
	int			ROIOffset;

	int			LightOffMilisec;
	int			LightOnMilisec;

	bool		ColorMode;

	CLHS_PX8Setting(bool ColorMode);

public:

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	LoadFromCam(featureCtrl *f);
	bool	StoreToCam(featureCtrl *f);
	bool	SetQuickProperty(featureCtrl *f ,CameraQuickProperty Attr, double RelativeValue);
};
