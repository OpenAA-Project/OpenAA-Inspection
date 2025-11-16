/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\XAutoStartThread.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XAUTOSTARTLISTTHREADH)
#define	XAUTOSTARTLISTTHREADH

#include <QThread>

class	AutoStartList;

class	ThreadAutoStartList : public QThread
{
	Q_OBJECT

	volatile	bool	OnExecuting;
	bool	Terminated;

	AutoStartList	*Parent;
public:

	ThreadAutoStartList(AutoStartList *aparent, QObject * parent = 0 );

    void run();

	bool	GetOnExecuting(void){	return OnExecuting;	}
	void	SetTerminate(bool b)	{	Terminated=b;	}
};

#endif