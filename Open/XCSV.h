/*
 * Copyright (C) 2023
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