/*
 * Copyright (C) 2017
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

#if	!defined(XBlockManualExecuter_h)
#define	XBlockManualExecuter_h

#include "XManualExecuter.h"
#include "XBlockInspection.h"
#include "XGeneralFunc.h"

class	ManualExecuterBlockBBrightL : public ManualExecuterItem
{
public:
	int32	NewValue;

	ManualExecuterBlockBBrightL(int v) : ManualExecuterItem(1),NewValue(v){}

	virtual	ManualExecuterItem	*Create(void)	{	return new ManualExecuterBlockBBrightL(0);	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(AlgorithmItemRoot *item);
};
class	ManualExecuterBlockBBrightH : public ManualExecuterItem
{
public:
	int32	NewValue;

	ManualExecuterBlockBBrightH(int v) : ManualExecuterItem(2),NewValue(v){}

	virtual	ManualExecuterItem	*Create(void)	{	return new ManualExecuterBlockBBrightH(0);	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(AlgorithmItemRoot *item);
};

class	ManualExecuterBlockNBrightL : public ManualExecuterItem
{
public:
	int32	NewValue;

	ManualExecuterBlockNBrightL(int v) : ManualExecuterItem(3),NewValue(v){}

	virtual	ManualExecuterItem	*Create(void)	{	return new ManualExecuterBlockNBrightL(0);	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(AlgorithmItemRoot *item);
};
class	ManualExecuterBlockNBrightH : public ManualExecuterItem
{
public:
	int32	NewValue;

	ManualExecuterBlockNBrightH(int v) : ManualExecuterItem(4),NewValue(v){}

	virtual	ManualExecuterItem	*Create(void)	{	return new ManualExecuterBlockNBrightH(0);	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(AlgorithmItemRoot *item);
};


#endif