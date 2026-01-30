/*
 * Copyright (C) 2022
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

#ifndef FILTERUDCOLORSHIFT_H
#define FILTERUDCOLORSHIFT_H

#include "filterudcolorshift_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"


class	ImageBuffer;

class	FilterUDColorShift : public FilterClassBase
{
public:
	bool	ShouldExecute;
	int		ShiftR;
	int		ShiftG;
	int		ShiftB;
	int		VShift;
	bool	CheckTime;
	int		TimeRange;
	int		ShiftOffset;

	FilterUDColorShift(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Release(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	QString	GetDataText(void)			override{	return "UDColorShift";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterUDColorShift.dat";	}
};
#endif // FILTERUDCOLORSHIFT_H