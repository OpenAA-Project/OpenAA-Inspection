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

#if	!defined(XWatchdogRebooter_h)
#define	XWatchdogRebooter_h

#include "NListComp.h"
#include <QIODevice.h>
#include <QLocalSocket>
#include "XDateTime.h"

class	WatchdogPack;

class	WatchdogTarget : public QObject ,public NPListSaveLoad<WatchdogTarget>
{
	Q_OBJECT

	WatchdogPack	*Parent;
	qint64			PID;
	QLocalSocket	*Sock;
	QString			ArgStr;
public:
	QString		PathFileName;
	QString		Arguments;
	QString		WorkingPath;
	int			WatchTerm;
	XDateTime	LastAccessed;

	WatchdogTarget(WatchdogPack *p,QObject * parent=0);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	bool	StartUp(void);
	int		GetPID(void)	{	return PID;	}
	bool	IsAlive(void);
	void	TimerFunc(void);
	void	Kill(void);
	bool	IsOpen(void);
	bool	IsConnected(void);
	bool	TryConnection(DWORD ProcessID);

	WatchdogTarget	&operator=(WatchdogTarget &src);
private:
	bool	SearchProcess(void);

signals:
	void	SignalShow();
	void	SignalWatchdogEvent(const QString &ErrorType,const QString &FileName ,int pid);
private slots:
	
	void SlotReadyRead ();

};


class	WatchdogPack : public QObject ,public NPListPackSaveLoad<WatchdogTarget>
{
	Q_OBJECT
public:
	WatchdogPack(void){}

	virtual	WatchdogTarget	*Create(void);

signals:
	void	SignalShow();
	void	SignalWatchdogEvent(const QString &ErrorType,const QString &FileName ,int pid);

private slots:
	void	SlotShow();
	void	SlotWatchdogEvent(const QString &ErrorType,const QString &FileName ,int pid);
};


#endif