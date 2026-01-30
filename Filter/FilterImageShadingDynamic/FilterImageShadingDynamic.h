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

#pragma once

#include "filterimageshadingdynamic_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class	FilterImageShadingDynamic : public FilterClassBase
{
	BYTE	*RefTableR;
	BYTE	*RefTableG;
	BYTE	*RefTableB;

	DWORD	SpanTime1;
	DWORD	SpanTime2;
	DWORD	SpanTime3;
	DWORD	SpanTime4;
	DWORD	SpanTime5;

public:
	int	RefStartX,RefEndX;
	int	RefStartY,RefEndY;
	int	Threshold;
	struct ShadingDynamicStruct
	{
		int	Ideal;
		int	BrightnessL;
		int	BrightnessH;
		int	Offset;

		int	*InsideDim;
		int	*InsideDimCount;
		int	*InsideDim16;
		int	*InsideDimCount16;
		int	MaxInsideDim16;
		int	*BrightTable;
		int	*BrL;
		int	*BrH;
		int	*DotL;
		int	*DotH;
		int	*HAvr;

		ShadingDynamicStruct(void);
		void	Initial(int DotPerLine,int MaxLines);
		void	Release(void);
	};
	struct ShadingDynamicStruct	DataR,DataG,DataB;
	
	FilterImageShadingDynamic(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Execute1(ImageBuffer &Buff ,struct ShadingDynamicStruct &Data);
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;

	virtual	QString	GetDataText(void)			override{	return "ImageShadingDynamic";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterImageShadingDynamic.dat";	}
private:
	void	MakeTable(ImageBuffer *Buff[],int BufferDimCounts);
};