/*
 * Copyright (C) 2013
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

#if	!defined(THREADLOGGER_H)
#define	THREADLOGGER_H

#include <QThread>
#include "XDateTime.h"
#include <QStringList>
#include <QMutex>
#include "XTypeDef.h"
#include "NList.h"

class	ThreadLogger;
class	XMLServerComm;

class	LogLeaf : public NPList<LogLeaf>
{
	ThreadLogger	*Parent;
	XDateTime		CurrentTime;
	int				OpeCode;
	QStringList		Messages;
	bool			Result;

public:
	LogLeaf(ThreadLogger *parent);

	bool	WriteLog(void);
	void	SetLog(int OpeCode ,QStringList &Msg,bool Result);
private:
	QString	GetFileName(void);
};

class ThreadLogger : public QThread
{
	Q_OBJECT
	XMLServerComm		*Parent;
	volatile	bool	CloseMode;

	NPListPack<LogLeaf>	LogQueue;
	QMutex				LogMutex;
public:
	ThreadLogger(XMLServerComm * parent);

	void run();
	XMLServerComm	*GetParent(void)	{	return Parent;	}
	void	Close(void);
	void	AddLog(int OpeCode ,QStringList &Msg);
	void	AddLog(int OpeCode ,QStringList &Msg,bool Result);
};

#endif