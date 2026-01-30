/*
 * Copyright (C) 2025
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

#ifndef FILTERDIFFERENCIALHV_H
#define FILTERDIFFERENCIALHV_H

#include "filterdifferencialhv_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XBoolList.h"

class	FilterDifferencialHV : public FilterClassBase
{
public:
	BoolList	Layers;
	double	Gain;
	int		Length;
	bool	Vertical;
	bool	BPF;
	int		PassWidth;
	double	*MutBPF;
	double	A;
	double	AA;

	FilterDifferencialHV(LayersBase *base);
	~FilterDifferencialHV(void);

	bool	Initial(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;

	virtual	QString	GetDataText(void)		override{	return "FilterDifferencialHV";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterDifferencialHV.dat";	}
};


#endif // FILTERDIFFERENCIALHV_H