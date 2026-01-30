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

#pragma once

#include "XFilterClass.h"
#include "XDLLType.h"
#include "NListComp.h"

class	ImageBuffer;


class VBandInfo : public NPListSaveLoad<VBandInfo>
{
public:
	int		XPos;
	int		ShiftY;

	VBandInfo(void){}
	VBandInfo(const VBandInfo &src);

	bool	Save(QIODevice *f)	override;
	bool	Load(QIODevice *f)	override;

	virtual	int	Compare(VBandInfo &src)	override;
};

class VBandInfoContainer : public NPListPackSaveLoad<VBandInfo>
{
public:
	VBandInfoContainer(void){}
	VBandInfoContainer(const VBandInfoContainer &src);

	virtual	VBandInfo	*Create(void)	override;
};



class	FilterShiftVBand : public FilterClassBase
{
public:
	VBandInfoContainer  VBands;

	FilterShiftVBand(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "ShiftVBand";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterShiftVBand.dat";	}

private:
	void	ExeShiftY(ImageBuffer *Buff,int LeftX,int RightX,int AddedShiftY);
};