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

#include "fftw3.h"
#include <QThread>
#include "XServiceForLayers.h"

class RealtimeGraphMeasure1Form;

class	ThreadFocus : public ServiceForLayers
{
	int	AllocXLen;
	int	AllocYLen;
	int	AllocLayerNumb;
	fftw_complex *inx;
	fftw_complex *iny;
	fftw_complex *outx;
	fftw_complex *outy;
	fftw_plan	PlanX;
	fftw_plan	PlanY;

	RealtimeGraphMeasure1Form	*Parent;
	int		CamNo;
	int		Page;

public:
	int	XLen;
	int	YLen;
	int	XPos;
	int	YPos;

	volatile	bool	Terminated;
	volatile	bool	CalcDone;
	double	*Brightness;
	double	*FocusValue;


	ThreadFocus(LayersBase *base ,RealtimeGraphMeasure1Form *parent);
	~ThreadFocus(void);

	void	Calculate(void);


private:
	void	Realloc(void);
	void	CalcWidth(ImagePointerContainer &Images);
	void	CalcHeight(ImagePointerContainer &Images);

};