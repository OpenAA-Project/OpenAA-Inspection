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

#ifndef FILTERVERTICALREVERSE_H
#define FILTERVERTICALREVERSE_H

#include "filterverticalreverse_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XBoolList.h"

class	FilterVerticalReverse : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;
	double	Width;
	bool	TopSide;
	bool	BottomSide;
	BoolList	Layers;
	double	Gamma;

	FilterVerticalReverse(LayersBase *base);
	~FilterVerticalReverse(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "VerticalReverse";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterVerticalReverse.dat";	}
};

#endif // FILTERVERTICALREVERSE_H