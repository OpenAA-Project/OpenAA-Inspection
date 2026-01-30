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

#ifndef FILTERREPLACECOLOR_H
#define FILTERREPLACECOLOR_H

#include "filterreplacecolor_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class FilterReplaceColor : public FilterClassBase
{
public:
	short	SourceLayer;
	short	AdaptedLayer;
	short	ProcessType;	//0:Replace brightness , 1:Add brightness

	short	PickupBrightnessLToReplace;
	short	PickupBrightnessHToReplace;
	short	AdaptedBrightnessToReplace;

	short	PickupBrightnessLToShift;
	short	PickupBrightnessHToShift;
	short	AddedBrightnessToShift;

	FilterReplaceColor(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;

	virtual	QString	GetDataText(void)		override{	return "ReplaceColor";				}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterReplaceColor.dat";	}

private:
	bool	ExecuteReplace(ImageBuffer *Buff[],int BufferDimCounts);
	bool	ExecuteAdd(ImageBuffer *Buff[],int BufferDimCounts);
};

#endif // FILTERREPLACECOLOR_H