/*
 * Copyright (C) 2012
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

#if	!defined(XPIOSIGNAL_H)
#define	XPIOSIGNAL_H
#include <QIODevice>
#include "XTypeDef.h"

class	SignalOne
{
public:
	DWORD	MicroSec;
	bool	Data;

	SignalOne(void){}
	SignalOne(DWORD _MicroSec ,bool data){	MicroSec=_MicroSec;	Data=data;	}

	void	Set(DWORD _MicroSec ,bool data){	MicroSec=_MicroSec;	Data=data;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	SignalData
{
public:
	SignalOne	*SignalDatas;
	int			AllocCount;
	int			CurrentPoint;

	SignalData(void);
	~SignalData(void);

	void	Alloc(int Count);
	void	Reset(void);
	void	Set(DWORD _MicroSec ,bool data);

	DWORD	GetLastMilisec(void);
	SignalOne	*GetSignalOnePointer(DWORD LaterMilisec ,int &Count);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#endif