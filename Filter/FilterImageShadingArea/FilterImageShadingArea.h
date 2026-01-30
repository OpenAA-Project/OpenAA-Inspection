/*
 * Copyright (C) 2018
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

#ifndef FILTERIMAGESHADINGAREA_H
#define FILTERIMAGESHADINGAREA_H

#include "filterimageshadingarea_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class	FilterImageShadingArea : public FilterClassBase
{
public:
	short	***MultiplePerDot;
	int32	LayerNumb;
	int32	XLen;
	int32	YLen;

	double	MagR;
	double	MagG;
	double	MagB;
	int		UsagePhaseNumber;
	int		UsagePageNumber;
	QStringList	FileList;

	FilterImageShadingArea(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "ImageShadingArea";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterImageShadingArea.dat";	}
private:
};
#endif // FILTERIMAGESHADINGAREA_H