/*
 * Copyright (C) 2014
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

#if	!defined(XChangeServerInfo_h)
#define	XChangeServerInfo_h

#include "NListComp.h"

class	ChangeServerInfo : public NPListSaveLoad<ChangeServerInfo>
{
public:

	QString	ServerName;
	QString	DBIPAddress;
	int32	DBPort;
	QString	DBFileName;
	QString	ImagePath;

	ChangeServerInfo(void) : DBPort(3051){}
	ChangeServerInfo	&operator=(ChangeServerInfo &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ChangeServerContainer : public NPListPackSaveLoad<ChangeServerInfo>
{
public:
	ChangeServerContainer(void){}

	virtual	ChangeServerInfo	*Create(void){	return new ChangeServerInfo();	}

	QString	GetFileName(void){		return "ChangeServerInfo.dat";	}
};

#endif