/*
 * Copyright (C) 2025
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


#if	!defined(XAUTOSTART_H)
#define	XAUTOSTART_H

#include <QIODevice>
#include <QProcess>
#include <qprocess.h>
#include "NListComp.h"
#include "XTypeDef.h"

class	AutoStartExeList;
class	AutoStartExecution;

class	AutoStartExecution : public QObject ,public NPListSaveLoad<AutoStartExecution>
{
	Q_OBJECT

public:
	QProcess			Process;
	qint64				PID;
	qint64				PrID;
	qint64				mExitCode;
public:
	QString	ExeFilePath;
	QString	Parameter;
	QString	WorkingPath;
	int32	Location;
	int32	BootingWaitTime;
	int32	ExitCode;

	AutoStartExecution(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	void	SetParent(QObject *parent);
	bool	StartProgram(void);
	bool	IsFinished(void);
	void	Close(void);
	void	WaitForStarted(void);
	void	ResizeAlignment(QRect &Rect);
	int		GetExitCode(void);
public slots:
	void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
};

class	AutoStartExeList : public NPListPackSaveLoad<AutoStartExecution>
{
	QString FileName;
public:
	int32	LoopCount;
	bool	AllDesktopArea;
	int32	AreaLeft;
	int32	AreaTop;
	int32	AreaRight;
	int32	AreaBottom;
	bool	Tasktray;

	AutoStartExeList(const AutoStartExeList &src);
	AutoStartExeList(const QString &_FileName):FileName(_FileName){	LoopCount=30;	}

	virtual	AutoStartExecution	*Create(void)	{	return new AutoStartExecution();	}		
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	void	SetParent(QObject *parent);

	bool	SaveDefault(void);
	bool	LoadDefault(void);

	bool	IsFinishedAll(void);
	bool	StartImmediately(void);
	bool	ExecuteAll(void);
	void	CloseAll(void);
	void	WaitForStarted(void);
	void	ResizeAlignment(void);
};


#endif
