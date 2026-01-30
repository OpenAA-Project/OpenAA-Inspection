/*
 * Copyright (C) 2016
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

#if	!defined(XDateTime_H)
#define	XDateTime_H

#include"XTypeDef.h"
#include<time.h>
#include<QString>

class	QDateTime;
class	QSystemSemaphore;

class	XDateTime
{
 #pragma	pack(push,1)
	WORD	Year;
	BYTE	Month;
	BYTE	Day;
	BYTE	Hour;
	BYTE	Minute;
	BYTE	Second;
	short	MiliSec;
#pragma	pack(pop)

public:
	XDateTime(void);
	XDateTime(const XDateTime &d);
	XDateTime(const QDateTime &d);
	XDateTime(QDateTime &d);
	XDateTime(int year ,int month ,int day ,int hour, int minute ,int second,int milisec=0);
	virtual	~XDateTime(void);

	void	set(int year ,int month ,int day ,int hour, int minute ,int second,int milisec=0);
	bool	IsAvailable(void);

	XDateTime	&operator=(XDateTime &src);
	XDateTime	&operator=(const XDateTime &src);
	XDateTime	&operator=(QDateTime &src);

	/*
	bool	operator<(XDateTime &src);
	bool	operator<=(XDateTime &src);
	bool	operator>(XDateTime &src);
	bool	operator>=(XDateTime &src);
	bool	operator==(XDateTime &src);
	bool	operator!=(XDateTime &src);
	*/

	bool	operator<(const XDateTime &src)	const;
	bool	operator<=(const XDateTime &src)const;
	bool	operator>(const XDateTime &src)	const;
	bool	operator>=(const XDateTime &src)const;
	bool	operator==(const XDateTime &src)const;
	bool	operator!=(const XDateTime &src)const;

	int		year(void)		const	{	return Year;	}
	int		month(void)		const	{	return Month;	}
	int		day(void)		const	{	return Day;		}
	int		hour(void)		const	{	return Hour;	}
	int		minute(void)	const	{	return Minute;	}
	int		second(void)	const	{	return Second;	}
	int		milisec(void)	const	{	return MiliSec;	}

	static	XDateTime	fromString(QString &str,const QString &format);
	QString	toString(const QString &format) const;
	QString	toString(Qt::DateFormat format = Qt::TextDate);

	static	XDateTime	currentDateTime(void);
	QDateTime	GetQDateTime(void)	const;

	time_t		toTime_t(void)	const;
	void		setTime_t(time_t t);

	int		secsTo ( const XDateTime & other ) const;

	XDateTime addSecs  ( int nsecs )	const;
	XDateTime addMSecs ( qint64 msecs ) const;
	XDateTime addMonths ( int nmonths ) const;
	XDateTime addDays ( int ndays )		const;
	XDateTime addYears ( int nyears )	const;

private:
	
	QSystemSemaphore	*Locker;
	static	QSystemSemaphore	*static_Locker;

	void	lock(void);
	void	unlock(void);

	static	void	static_lock(void);
	static	void	static_unlock(void);
};

#endif