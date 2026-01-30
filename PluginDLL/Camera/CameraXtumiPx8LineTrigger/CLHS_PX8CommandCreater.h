/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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


	CLHS_PX8Setting();

public:

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	LoadFromCam(featureCtrl *f);
	bool	StoreToCam(featureCtrl *f);
	bool	SetQuickProperty(featureCtrl *f ,CameraQuickProperty Attr, double RelativeValue);
};