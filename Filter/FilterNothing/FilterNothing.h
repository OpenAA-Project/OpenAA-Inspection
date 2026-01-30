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

#ifndef FILTERNOTHING_H
#define FILTERNOTHING_H

#include "filternothing_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterNothing : public FilterClassBase
{
public:

	FilterNothing(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override{	return true;	}
	virtual	bool	Load(QIODevice *f)	override{	return true;	}
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override{	return true;	}
	virtual	bool	Initial(void)		override{	return true;	}
	virtual	bool	Release(void)		override{	return true;	}

	virtual	QString	GetDataText(void)		override{	return "Nothing";			}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterNothing.dat";	}
};

#endif // FILTERNOTHING_H