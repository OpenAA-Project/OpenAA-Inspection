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

#ifndef FILTERREVERSELENS_H
#define FILTERREVERSELENS_H

#include "filterreverselens_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterReverseLens : public FilterClassBase
{
	int		*MultiplyTable;
public:
	double	Strength;
	double	Width;
	int32	StartX;
	int32	EndX;

	FilterReverseLens(LayersBase *base);
	~FilterReverseLens(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "ReverseLens";			}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterReverseLens.dat";	}
};

#endif // FILTERREVERSELENS_H