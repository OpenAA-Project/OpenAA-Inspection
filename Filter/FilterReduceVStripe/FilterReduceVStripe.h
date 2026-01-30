/*
 * Copyright (C) 2024
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

#include "filterreducevstripe_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterReduceVStripe : public FilterClassBase
{
public:
	bool	FirstMode;
	double	IdealBrightness[100][2][3];
	double	CurrentBrightness[100][2][3];
	int		AddBrightness[100][3];
	int		Step;	//=1024
	int		TopY;
	int		YLen;
	int		BoxSize;	//=50


	FilterReduceVStripe(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "ReduceVStripe";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterReduceVStripe.dat";	}

private:
	double	GetBoxBrightness(int x1 ,int y1 ,int x2,int y2, ImageBuffer *Buff);
};