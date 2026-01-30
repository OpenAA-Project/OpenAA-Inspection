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

#if	!defined(XRemoteLightLocalHost_H)
#define	XRemoteLightLocalHost_H

#include <QLocalSocket>
#include <QLocalServer>
#include <QObject>
#include "XTypeDef.h"

class	FromProgram;
class	RemoteLightController;

class	FromProgramInstance : public QObject
{
	Q_OBJECT

	FromProgram	*Parent;
	QLocalSocket	*Socket;
public:
	FromProgramInstance(FromProgram *parent ,QLocalSocket *s);

signals:
	void	SignalLightID(int lightID);
	void	SignalLightON(bool lightON);
	void	SignalLightRequest();

private slots:
	void	SlotReadyRead();
};

class	FromProgram : public QLocalServer
{
	Q_OBJECT
	RemoteLightController	*RParent;
public:
	BYTE					*ReqData;
	int						ReqDataLength;
public:
	FromProgram ( RemoteLightController * parent = 0 );
	~FromProgram(void);

	void	Start(void);
private slots:
	void	SlotNewConnection ();
	void	SlotLightID(int lightID);
	void	SlotLightON(bool lightON);
	void	SlotLightRequest();
};

#endif