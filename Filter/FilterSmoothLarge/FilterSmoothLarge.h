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

#ifndef FILTERSMOOTHLARGE_H
#define FILTERSMOOTHLARGE_H

#include "filtersmoothlarge_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"


class	FilterSmoothLarge : public FilterClassBase
{
	int	**TmpBuff;
	int	AllocLines;
	int	*FormerLineSum;
	ImageBuffer	TmpImage;
public:
	int	WindowSize;

	FilterSmoothLarge(LayersBase *base);
	~FilterSmoothLarge(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "SmoothLarge";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterSmoothLarge.dat";	}

	void	MakeOneSum(int *TBuff ,BYTE *Source);
};

#endif // FILTERSMOOTHLARGE_H