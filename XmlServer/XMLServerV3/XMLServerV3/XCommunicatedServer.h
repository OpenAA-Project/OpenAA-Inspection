/*
 * Copyright (C) 2015
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

#if	!defined(XCommunicatedServer_H)
#define	XCommunicatedServer_H

#include "XFastComm.h"
#include "XDateTime.h"

class	CommunicatedServerComm;
class	XMLServerComm;

#define	CS_Command_WriteOut	1

class	CommunicatedServerLeaf : public FastCommLeaf
{
	CommunicatedServerComm	*Parent;
public:
	CommunicatedServerLeaf(int ID ,CommunicatedServerComm *parent);

};

class	CommunicatedServerComm : public FastComm
{
	Q_OBJECT

	XMLServerComm	*Parent;
	XDateTime		LastAccessTime;
public:
	CommunicatedServerComm(XMLServerComm *Parent);

	virtual	FastCommLeaf *CreateNewLeaf(int ID){		return new CommunicatedServerLeaf(ID ,this);	}

	//void	ExecuteWriteOut(void);
	void	SendCommandWriteOut(void);

private:
	void	SendCommandWriteOutInner(const QString &HostIP);
protected slots:
	virtual	void	SlotReceived(int,int);
	void	SlotExecuteWriteOut();
signals:
	void	SignalExecuteWriteOut();

};


#endif