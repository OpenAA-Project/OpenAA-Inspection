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



#ifndef FILTEREDGEEMPHASIZE_H
#define FILTEREDGEEMPHASIZE_H

#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterEdgeEmphasize : public FilterClassBase
{
	short	FilterTable[100][100];
	BYTE	**SourceBuffer;
	BYTE	*SourcePointer[100];
	int		SourceYLen;

public:
	int		Radius;
	double	Strength;

	FilterEdgeEmphasize(LayersBase *base);
	virtual	~FilterEdgeEmphasize(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;

	virtual	QString	GetDataText(void)		override{	return "EdgeEnphasize";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterEdgeEmphasize.dat";	}
};


#endif // FILTEREDGEEMPHASIZE_H