/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\LogWriter\ThreadLogWriter.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(THREADLOGWRITER_H)
#define	THREADLOGWRITER_H


#include <QThread>
#include "XDateTime.h"
#include <QReadWriteLock>
#include "XTypeDef.h"

class ThreadLogWriter : public QThread
{
	Q_OBJECT

public:
	bool		OnWriteMode;
	XDateTime	OnWrittenTime;
	int64		OnInspectionID;
	bool		OnSignalOn;

	bool		OffWriteMode;
	XDateTime	OffWrittenTime;
	int64		OffInspectionID;
	bool		OffSignalOn;

	bool		PrintWriteMode;
	XDateTime	PrintWrittenTime;
	QString		PrintString;
	int			PrintNumber;

	char		FileName[256];

	ThreadLogWriter();

	void run();
};

#endif