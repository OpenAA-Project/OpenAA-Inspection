/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XApplication.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XAPPLICATION_H)
#define	XAPPLICATION_H

#include <QApplication>

class	MainApplication : public QApplication
{
	Q_OBJECT
public:
	MainApplication( int & argc, char ** argv )
		:QApplication( argc, argv ){}

private slots:
	void	QuitProcess();
};


#endif