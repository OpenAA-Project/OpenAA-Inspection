/*
 * Copyright (C) 2012
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

#ifndef FILTERSHRINKIMAGE_H
#define FILTERSHRINKIMAGE_H

#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class	FilterShrinkImage : public FilterClassBase
{
public:
	int			ShrinkRate;
	int			ShrinkMethod;	//�O�F�P���k��	�P�F���P�x�̗p	�Q�F���P�x�̗p	�R�F���ω��k��
	int			*IndexTable;
	int			AllocSize;

	FilterShrinkImage(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "Shrink";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterShrink.dat";	}
private:
	bool	ExecuteSimple(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteHighest(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteLowest(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteAverage(ImageBuffer *Buff[],int BufferDimCounts);
};

#endif // FILTERSHRINKIMAGE_H