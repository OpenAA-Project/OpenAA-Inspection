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



#ifndef FILTERSMOOTHING_H
#define FILTERSMOOTHING_H

#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class	FilterSmoothingClass : public FilterClassBase
{
public:
	ImageBuffer **TmpImage;
	int			AllocatedLayerCount;
	int	Length;
	int	MethodValue;

	FilterSmoothingClass(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "Smoothing";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterSmoothing.dat";	}
};

#endif // FILTERSMOOTHING_H