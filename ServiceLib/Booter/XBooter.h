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

#if	!defined(XBOOTER_H)
#define	XBOOTER_H

#include "NListComp.h"
#include <QIODevice>

class	ExecuteApplicationList : public NPListSaveLoad<ExecuteApplicationList>
{
public:
	QString		Program;
	QString		Parameter;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ExecuteApplicationContainer : public NPListPackSaveLoad<ExecuteApplicationList>
{
public:
	ExecuteApplicationContainer(void){}

	virtual	ExecuteApplicationList	*Create(void){	return new ExecuteApplicationList();	}
};

class	BooterParameter
{
public:
	QString	WindowMessage;
	QString	ButtonMessage;
	QStringList		RemoteReceiver;
	ExecuteApplicationContainer	BeforeBoot;
	QString		ExecuteBeforeBooter;
	ExecuteApplicationContainer	AfterBoot;
	QString		ExecuteAfterBooter;

	QString		DefaultFileName;
	
	BooterParameter(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	QString	GetDefaultFileName(void){	return DefaultFileName;	}
};

#endif