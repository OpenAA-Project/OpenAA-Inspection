/*
 * Copyright (C) 2025
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

#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XServiceForLayers.h"
#include "XTypeDef.h"
//#include "fftw3.h"

class	DisplayRealtimeGraph;

class	DisplayRealtimeGraphBrightness: public ServiceForLayers
{
	int	AllocLayerNumb;
	int	AllocXLen;
	volatile	int		CamNo;
	volatile	bool	Calclating;
	DisplayRealtimeGraph *Parent;
public:
	double	**LineData;

	mtLineGraph	GraphBase;
	mtGLine		*GraphLine;
	int			Page;

	DisplayRealtimeGraphBrightness(LayersBase *Base ,DisplayRealtimeGraph *p,QWidget *parent=nullptr);
	~DisplayRealtimeGraphBrightness(void);

	void	SetGeometry(int x, int y ,int w ,int h);
	void	Repaint(void);
};

class	DisplayRealtimeGraphFocus: public ServiceForLayers
{
	int	AllocXLen;
	int	AllocLayerNumb;
	volatile	int		CamNo;
	volatile	bool	Calclating;
	DisplayRealtimeGraph *Parent;
public:
	double	**LineData;

	mtLineGraph	GraphBase;
	mtGLine		*GraphLine;

	DisplayRealtimeGraphFocus(LayersBase *Base ,DisplayRealtimeGraph *p,QWidget *parent=nullptr);
	~DisplayRealtimeGraphFocus(void);

	void	SetGeometry(int x, int y ,int w ,int h);
	void	Repaint(void);

private:
	double	MakeFFTValue(double Brightness[] ,int XPos,int XLen);
};
