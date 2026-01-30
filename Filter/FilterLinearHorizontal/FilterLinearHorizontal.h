/*
 * Copyright (C) 2016
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

#ifndef FILTERLINEARHORIZONTAL_H
#define FILTERLINEARHORIZONTAL_H

#include "filterlinearhorizontal_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterLinearHorizontal : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;	//Gain/Pixel
	bool	LeftSide;
	bool	RightSide;

	FilterLinearHorizontal(LayersBase *base);
	~FilterLinearHorizontal(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "ReverseLens";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterReverseLens.dat";	}
};
#endif // FILTERLINEARHORIZONTAL_H