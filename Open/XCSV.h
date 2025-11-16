/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XCSV.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XCSV_H)
#define	XCSV_H

#include <QStringList>
#include <QIODevice>
#include "XTypeDef.h"

class	QStringListListCSV :public QList<QStringList>
{
public:
	QStringListListCSV(void){}

	bool	LoadFromCSVFile(const QString &FileName);
	bool	SaveFromCSVFile(const QString &FileName);

	bool	LoadFromCSVFile(QIODevice *f);
	bool	SaveFromCSVFile(QIODevice *f);

	void	Set(int column, int row ,const QString &s);
	QString	Get(int column, int row)	const;

	int	GetRowCount(void)		const	{	return count();	}
	int	GetColumnCount(int row)	const	{	return at(row).count();	}
	int	GetMaxColumnCount(void)	const;

	bool	operator==(QStringListListCSV &src)	const;
	bool	operator!=(QStringListListCSV &src)	const;
};

class	QTableWidget;
bool	SaveCSV(QIODevice *f ,QTableWidget *W);

#endif