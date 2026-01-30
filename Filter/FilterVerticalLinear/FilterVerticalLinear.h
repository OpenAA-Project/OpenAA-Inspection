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

#ifndef FILTERVERTICALLINEAR_H
#define FILTERVERTICALLINEAR_H

#include "filterverticallinear_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XBoolList.h"

class	FilterVerticalLinear : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;
	bool	WholeImage;
	bool	TopSide;
	bool	BottomSide;
	BoolList	Layers;
	double	Gamma;

	FilterVerticalLinear(LayersBase *base);
	~FilterVerticalLinear(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "VerticalLinear";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterVerticalLinear.dat";	}
};

#endif // FILTERVERTICALLINEAR_H