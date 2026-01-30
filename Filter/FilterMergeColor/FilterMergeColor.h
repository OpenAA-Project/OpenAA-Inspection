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

#pragma once

#include "filtermergecolor_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class ColorPoint
{
public:
	QColor	SrcColor;
	QColor	TargetColor;

	ColorPoint(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};



class	FilterMergeColor : public FilterClassBase
{
	BYTE	TableR[256];
	BYTE	TableG[256];
	BYTE	TableB[256];
public:
	ColorPoint	P1,P2;
	int			dx,dy;
	double		R1,R2,B1,B2,Gain;

	FilterMergeColor(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override{	return true;	}

	virtual	QString	GetDataText(void)		override{	return "MergeColor";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterMergeColor.dat";	}
private:
};