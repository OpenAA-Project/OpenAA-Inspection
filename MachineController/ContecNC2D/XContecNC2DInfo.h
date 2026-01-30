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