/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\XAutoStartThread.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XAUTOSTARTTHREADH)
#define	XAUTOSTARTTHREADH

#include <QThread>

class	ThreadAutoStart : public QThread
{
	Q_OBJECT

	volatile	bool	StartExecMode;
	volatile	bool	StopMode;
	volatile	bool	OnExecuting;

public:
	int	SpareSec;
	QString		SArg;
	QString		PlayerExe;

	ThreadAutoStart( QObject * parent = 0 );

    void run();

	void	SetExec();
	void	SetStop();
	void	SetRestart();
	bool	GetOnExecuting(void){	return OnExecuting;	}

signals:
	void	OnLoop(int N);
};

#endif