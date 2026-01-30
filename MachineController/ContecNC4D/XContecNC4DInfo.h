/*
 * Copyright (C) 2015
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

class	ContecNC4DInfo
{
public:
	ContecNCAxis	AxisX;
	ContecNCAxis	AxisY;
	ContecNCAxis	AxisZ;
	ContecNCAxis	AxisW;

	int		StartPosX,StartPosY;
	int		StartVelocity;
	int		ScanLength;
	int		ScanVelocity;
	int		StepLength;
	int		StepVelocity;
	int		PulseZ;
	double	PosZ;
	int		VelocityZ;
	int		PulseW;
	double	PosW;
	int		VelocityW;
	int		ScanCount;
	bool	EnableAreaSensor;
	bool	EnableDoorSensor;

	ContecNC4DInfo(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};



#endif