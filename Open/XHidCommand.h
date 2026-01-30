/*
 * Copyright (C) 2016
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

#if	!defined(XHidCommand_h)
#define	XHidCommand_h

#include "XTypeDef.h"
#include <QWidget>

class	HidCommand
{
protected:
	QWidget *Parent;

public:
	HidCommand(QWidget *parent);
	virtual	~HidCommand(void){}

	static	HidCommand	*Create(QWidget *parent);
	virtual	bool	OpenHid(int Vid, int Pid,int Number)=0;
	virtual	bool	CloseHid(void)=0;
	virtual	bool	IsOpened(void)=0;

	virtual	bool	SendStr(BYTE *Data ,int Len)=0;
	virtual	bool	ReceiveStr(BYTE *Data ,int &ReceivedLen ,int waitmilisec=1000)=0;
};


#endif