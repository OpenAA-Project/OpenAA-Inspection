#include "XDateTime.h"
#include <QDateTime>
#include <QSystemSemaphore>
#include <QStringList>

XDateTime::XDateTime(void)
{
	Locker	=NULL;
	Year	=0;
	Month	=0;
	Day		=0;
	Hour	=0;
	Minute	=0;
	Second	=0;
	MiliSec	=0;
}
XDateTime::XDateTime(const XDateTime &src)
{
	Locker	=NULL;
	Year	=src.Year;
	Month	=src.Month;
	Day		=src.Day;
	Hour	=src.Hour;
	Minute	=src.Minute;
	Second	=src.Second;
	MiliSec	=src.MiliSec;
}
XDateTime::XDateTime(const QDateTime &d)
{
	Locker	=NULL;
	Year	=d.date().year();
	Month	=d.date().month();
	Day		=d.date().day();
	Hour	=d.time().hour();
	Minute	=d.time().minute();
	Second	=d.time().second();
	MiliSec	=d.time().msec();
}
XDateTime::XDateTime(QDateTime &d)
{
	Locker	=NULL;
	Year	=d.date().year();
	Month	=d.date().month();
	Day		=d.date().day();
	Hour	=d.time().hour();
	Minute	=d.time().minute();
	Second	=d.time().second();
	MiliSec	=d.time().msec();
}
XDateTime::XDateTime(int year ,int month ,int day ,int hour, int minute ,int second ,int milisec)
{
	Locker	=NULL;
	Year	=year;
	Month	=month;
	Day		=day;
	Hour	=hour;
	Minute	=minute;
	Second	=second;
	MiliSec	=milisec;
}

XDateTime::~XDateTime(void)
{
	if(Locker!=NULL){
		delete	Locker;
		Locker=NULL;
	}
}

bool	XDateTime::IsAvailable(void)
{
	if(	Year	==0
	&& Month	==0
	&& Day		==0
	&& Hour		==0
	&& Minute	==0
	&& Second	==0
	&& MiliSec	==0){
		return false;
	}
	return true;
}

XDateTime	&XDateTime::operator=(XDateTime &src)
{
	Year	=src.Year;
	Month	=src.Month;
	Day		=src.Day;
	Hour	=src.Hour;
	Minute	=src.Minute;
	Second	=src.Second;
	MiliSec	=src.MiliSec;
	return *this;
}
XDateTime	&XDateTime::operator=(const XDateTime &src)
{
	Year	=src.Year;
	Month	=src.Month;
	Day		=src.Day;
	Hour	=src.Hour;
	Minute	=src.Minute;
	Second	=src.Second;
	MiliSec	=src.MiliSec;
	return *this;
}
void	XDateTime::set(int year ,int month ,int day ,int hour, int minute ,int second,int milisec)
{
	Year	=year;
	Month	=month;
	Day		=day;
	Hour	=hour;
	Minute	=minute;
	Second	=second;
	MiliSec	=milisec;
}
XDateTime	&XDateTime::operator=(QDateTime &d)
{
	lock();
	Year	=d.date().year();
	Month	=d.date().month();
	Day		=d.date().day();
	Hour	=d.time().hour();
	Minute	=d.time().minute();
	Second	=d.time().second();
	MiliSec	=d.time().msec();
	unlock();
	return *this;
}
bool	XDateTime::operator<(const XDateTime &src) const
{
	if(Year<src.Year){
		return true;
	}
	if(Year>src.Year){
		return false;
	}
	if(Month<src.Month){
		return true;
	}
	if(Month>src.Month){
		return false;
	}
	if(Day<src.Day){
		return true;
	}
	if(Day>src.Day){
		return false;
	}
	if(Hour<src.Hour){
		return true;
	}
	if(Hour>src.Hour){
		return false;
	}
	if(Minute<src.Minute){
		return true;
	}
	if(Minute>src.Minute){
		return false;
	}
	if(Second<src.Second){
		return true;
	}
	if(Second>src.Second){
		return false;
	}
	if(MiliSec<src.MiliSec){
		return true;
	}
	if(MiliSec>src.MiliSec){
		return false;
	}
	return false;
}

bool	XDateTime::operator<=(const XDateTime &src)	const
{
	if(Year<src.Year){
		return true;
	}
	if(Year>src.Year){
		return false;
	}
	if(Month<src.Month){
		return true;
	}
	if(Month>src.Month){
		return false;
	}
	if(Day<src.Day){
		return true;
	}
	if(Day>src.Day){
		return false;
	}
	if(Hour<src.Hour){
		return true;
	}
	if(Hour>src.Hour){
		return false;
	}
	if(Minute<src.Minute){
		return true;
	}
	if(Minute>src.Minute){
		return false;
	}
	if(Second<src.Second){
		return true;
	}
	if(Second>src.Second){
		return false;
	}
	if(MiliSec<src.MiliSec){
		return true;
	}
	if(MiliSec>src.MiliSec){
		return false;
	}
	return true;
}


bool	XDateTime::operator>(const XDateTime &src)	const
{
	if(Year<src.Year){
		return false;
	}
	if(Year>src.Year){
		return true;
	}
	if(Month<src.Month){
		return false;
	}
	if(Month>src.Month){
		return true;
	}
	if(Day<src.Day){
		return false;
	}
	if(Day>src.Day){
		return true;
	}
	if(Hour<src.Hour){
		return false;
	}
	if(Hour>src.Hour){
		return true;
	}
	if(Minute<src.Minute){
		return false;
	}
	if(Minute>src.Minute){
		return true;
	}
	if(Second<src.Second){
		return false;
	}
	if(Second>src.Second){
		return true;
	}
	if(MiliSec<src.MiliSec){
		return false;
	}
	if(MiliSec>src.MiliSec){
		return true;
	}
	return false;
}


bool	XDateTime::operator>=(const XDateTime &src)	const
{
	if(Year<src.Year){
		return false;
	}
	if(Year>src.Year){
		return true;
	}
	if(Month<src.Month){
		return false;
	}
	if(Month>src.Month){
		return true;
	}
	if(Day<src.Day){
		return false;
	}
	if(Day>src.Day){
		return true;
	}
	if(Hour<src.Hour){
		return false;
	}
	if(Hour>src.Hour){
		return true;
	}
	if(Minute<src.Minute){
		return false;
	}
	if(Minute>src.Minute){
		return true;
	}
	if(Second<src.Second){
		return false;
	}
	if(Second>src.Second){
		return true;
	}
	if(MiliSec<src.MiliSec){
		return false;
	}
	if(MiliSec>src.MiliSec){
		return true;
	}
	return true;
}

bool	XDateTime::operator==(const XDateTime &src)	const
{
	if(Year		==src.Year
	&& Month	==src.Month
	&& Day		==src.Day
	&& Hour		==src.Hour
	&& Minute	==src.Minute
	&& Second	==src.Second){
	//&& MiliSec	==src.MiliSec){
		return true;
	}
	return false;
}

bool	XDateTime::operator!=(const	XDateTime &src)	const
{
	if(Year		==src.Year
	&& Month	==src.Month
	&& Day		==src.Day
	&& Hour		==src.Hour
	&& Minute	==src.Minute
	&& Second	==src.Second){
	//&& MiliSec	==src.MiliSec){
		return false;
	}
	return true;
}

XDateTime	XDateTime::currentDateTime(void)
{
	XDateTime	d(QDateTime::currentDateTime());
	return d;
}

QDateTime	XDateTime::GetQDateTime(void) const
{
	QDate	D(Year,Month,Day);
	QTime	T(Hour,Minute,Second);
	QDateTime	d;
	d.setDate(D);
	d.setTime(T);
	return d;
}

XDateTime	XDateTime::fromString(QString &str,const QString &format)
{
	QStringList	SList=format.split(QRegularExpression("[-/: ]"));
	if(SList.count()==1){
		QDateTime	d=QDateTime::fromString(str,format);
		XDateTime	e(d);
		return e;
	}
	else{
		QStringList	DList=str.split(QRegularExpression("[-/: ]"));
		int	year=0,month=0,day=0;
		int	hour=0,minute=0,sec=0;
		bool	ok;
		for(int i=0;i<SList.count() && i<DList.count();i++){
			if(SList[i]=="yy"){
				year=DList[i].toInt(&ok);
				if(ok==false)
					break;
				year+=1900;
			}
			else if(SList[i]=="yyyy"){
				year=DList[i].toInt(&ok);
				if(ok==false)
					break;
			}
			else if(SList[i]=="MM"){
				month=DList[i].toInt(&ok);
				if(ok==false)
					break;
			}
			else if(SList[i]=="dd"){
				day=DList[i].toInt(&ok);
				if(ok==false)
					break;
			}
			else if(SList[i]=="hh"){
				hour=DList[i].toInt(&ok);
				if(ok==false)
					break;
			}
			else if(SList[i]=="mm"){
				minute=DList[i].toInt(&ok);
				if(ok==false)
					break;
			}
			else if(SList[i]=="ss"){
				sec=DList[i].toInt(&ok);
				if(ok==false)
					break;
			}
		}
		XDateTime	e(year,month,day,hour,minute,sec);
		return e;
	}

}


QString	XDateTime::toString(const QString &format) const
{
	QDateTime	d=GetQDateTime();
	return d.toString(format);
}

QString	XDateTime::toString(Qt::DateFormat format)
{
	QDateTime	d=GetQDateTime();
	return d.toString(format);
}


time_t		XDateTime::toTime_t(void) const
{
	QDateTime	K=GetQDateTime();
	return K.toTime_t();
}
void		XDateTime::setTime_t(time_t t)
{
	QDateTime	K;
	K.setTime_t(t);
	operator=(K);
}

int XDateTime::secsTo ( const XDateTime & other ) const
{
	QDateTime	d=GetQDateTime();
	QDateTime	s=other.GetQDateTime();
	return d.secsTo(s);
}

XDateTime XDateTime::addSecs  ( int nsecs )	const
{
	QDateTime	d=GetQDateTime();
	return d.addSecs(nsecs);
}
XDateTime XDateTime::addMSecs ( qint64 msecs ) const
{
	QDateTime	d=GetQDateTime();
	return d.addMSecs(msecs);
}
XDateTime XDateTime::addMonths ( int nmonths ) const
{
	QDateTime	d=GetQDateTime();
	return d.addMonths(nmonths);
}
XDateTime XDateTime::addDays ( int ndays )		const
{
	QDateTime	d=GetQDateTime();
	return d.addDays(ndays);
}
XDateTime XDateTime::addYears ( int nyears )	const
{
	QDateTime	d=GetQDateTime();
	return d.addYears(nyears);
}

void	XDateTime::lock(void)
{
	if(Locker==NULL){
		Locker=new QSystemSemaphore ( "QDateTime", 1);
	}
	Locker->acquire();
}
void	XDateTime::unlock(void)
{
	if(Locker!=NULL){
		Locker->release();
	}
}
