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

#ifndef FILTERONELAYER_H
#define FILTERONELAYER_H

#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterOneLayer : public FilterClassBase
{
public:
	ImageBuffer TmpImage;
	int	Layer;
	int	MethodValue;
	int	Param;

	FilterOneLayer(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "OneLayer";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterOneLayer.dat";	}

private:
	bool	ExecuteAverage(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteXAverage(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteMedian(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteMulAverage(ImageBuffer *Buff[],int BufferDimCounts);
};

#endif // FILTERONELAYER_H