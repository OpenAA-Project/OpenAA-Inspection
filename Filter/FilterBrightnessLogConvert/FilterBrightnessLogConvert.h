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

#ifndef FILTERBRIGHTNESSLOGCONVERT_H
#define FILTERBRIGHTNESSLOGCONVERT_H

#include "filterbrightnesslogconvert_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterBrightnessLogConvert : public FilterClassBase
{
	BYTE	TransTable[256];

public:
	int		Position;
	double	Strength;

	FilterBrightnessLogConvert(LayersBase *base);
	virtual	~FilterBrightnessLogConvert(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;

	virtual	QString	GetDataText(void)			override	{	return "BrightnessLogConvert";	}
	virtual	QString	GetDefaultFileName(void)	override	{	return "FilterBrightnessLogConvert.dat";	}
};


#endif // FILTERBRIGHTNESSLOGCONVERT_H