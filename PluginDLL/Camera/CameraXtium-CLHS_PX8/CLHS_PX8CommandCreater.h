/*
 * Copyright (C) 2018
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


class CameraCommand;
class	featureCtrl;

class CLHS_PX8Setting
{
public:
	double	LineRate;
	double	ExposureTime;	//Microsec
	bool	TDIDirection;

	double	GainRed;
	double	GainGreen;
	double	GainBlue;
	int		OffsetRed;
	int		OffsetGreen;
	int		OffsetBlue;

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

	CLHS_PX8Setting();

public:

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	LoadFromCam(featureCtrl *f);
	bool	StoreToCam(featureCtrl *f);
};