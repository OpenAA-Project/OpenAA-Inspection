/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGeneralFunc.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include <stdio.h>
#include <QtGui>
#include "XGeneralFunc.h"
#include <math.h>
#include "XYCross.h"
#include <omp.h>
#include "swap.h"
#include <QTextCodec>
#include "XIntClass.h"
#include "XDateTime.h"
#include <QMessageBox>
#include <QDesktopWidget>
#include <QCheckBox>
#include <QApplication>

QString	GetDynamicFileExt(void)
{
#ifdef _MSC_VER
	return("DLL");
#else
	return("so");
#endif
}

void	ErrorOccurs(void)
{
	QMessageBox	MBox(QMessageBox::Critical,"Error","_CrtCheckMemory");
	MBox.exec();
}
bool	Save(QIODevice *f,int8 d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,int32 d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,uint32 d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,WORD d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,short d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,DWORD d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,BYTE d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,char d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,float d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,double d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}

bool	Save(QIODevice *f,bool d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,bool3 d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}

bool	Save(QIODevice *file,const QString &d)
{
	int32	Len=d.length()*2;
	if(file->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(file->write((const char *)d.constData(),Len)!=Len){
		return(false);
	}
	return(true);
}

bool	Save(QIODevice *f,const XYData &d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return(false);
	}
	return(true);
}
bool	Save(QIODevice *f,const QDateTime &d)
{
	WORD	wyear	=d.date().year();
	BYTE	wmonth	=d.date().month();
	BYTE	wday	=d.date().day();
	BYTE	whour	=d.time().hour();
	BYTE	wminute	=d.time().minute();
	BYTE	wsec	=d.time().second();

	if(::Save(f,wyear)==false){
		return false;
	}
	if(::Save(f,wmonth)==false){
		return false;
	}
	if(::Save(f,wday)==false){
		return false;
	}
	if(::Save(f,whour)==false){
		return false;
	}
	if(::Save(f,wminute)==false){
		return false;
	}
	if(::Save(f,wsec)==false){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,const XDateTime &d)
{
	WORD	wyear	=d.year();
	BYTE	wmonth	=d.month();
	BYTE	wday	=d.day();
	BYTE	whour	=d.hour();
	BYTE	wminute	=d.minute();
	BYTE	wsec	=d.second();

	if(::Save(f,wyear)==false){
		return false;
	}
	if(::Save(f,wmonth)==false){
		return false;
	}
	if(::Save(f,wday)==false){
		return false;
	}
	if(::Save(f,whour)==false){
		return false;
	}
	if(::Save(f,wminute)==false){
		return false;
	}
	if(::Save(f,wsec)==false){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,const QPoint &d)
{
	int32	P[2];
	P[0]=d.x();
	P[1]=d.y();

	if(f->write((const char *)P,sizeof(P))!=sizeof(P)){
		return false;
	}
	return true;
}

bool	IsEqual(const QDateTime &d1 ,const QDateTime &d2)
{
	WORD	wyear1	=d1.date().year();
	BYTE	wmonth1	=d1.date().month();
	BYTE	wday1	=d1.date().day();
	BYTE	whour1	=d1.time().hour();
	BYTE	wminute1=d1.time().minute();
	BYTE	wsec1	=d1.time().second();
	WORD	wyear2	=d2.date().year();
	BYTE	wmonth2	=d2.date().month();
	BYTE	wday2	=d2.date().day();
	BYTE	whour2	=d2.time().hour();
	BYTE	wminute2=d2.time().minute();
	BYTE	wsec2	=d2.time().second();

	if(wyear1==wyear2
	&& wmonth1==wmonth2
	&& wday1==wday2
	&& whour1==whour2
	&& wminute1==wminute2
	&& wsec1==wsec2){
		return true;
	}
	return false;
}
bool	IsEqual(const QStringList &L1,const QStringList &L2)
{
	if(L1.count()!=L2.count()){
		return false;
	}
	for(int i=0;i<L1.count();i++){
		if(L1.value(i)!=L2.value(i)){
			return false;
		}
	}
	return true;
}

bool	Save(QIODevice *f,const QDate &d)
{
	WORD	wyear	=d.year();
	BYTE	wmonth	=d.month();
	BYTE	wday	=d.day();

	if(::Save(f,wyear)==false){
		return false;
	}
	if(::Save(f,wmonth)==false){
		return false;
	}
	if(::Save(f,wday)==false){
		return false;
	}
	return true;
}

bool	Save(QIODevice *f,const QTime &d)
{
	BYTE	whour	=d.hour();
	BYTE	wminute	=d.minute();
	BYTE	wsec	=d.second();

	if(::Save(f,whour)==false){
		return false;
	}
	if(::Save(f,wminute)==false){
		return false;
	}
	if(::Save(f,wsec)==false){
		return false;
	}
	return true;
}

bool	Save(QIODevice *f,const QChar &d)
{
	ushort	unicode=d.unicode();
	if(::Save(f,unicode)==false)
		return false;
	return true;
}

bool	Save(QIODevice *f,const QVariant &d)
{	
	short	int	h=d.type();
	if(::Save(f,h)==false)
		return false;

	if(h==QVariant::Invalid)
		return true;
	else if(h==QVariant::BitArray){
		QBitArray	A=d.toBitArray();
		int32	Len=A.count();
		if(::Save(f,Len)==false)
			return false;
		for(int i=0;i<Len;i++){
			bool	b=A.at(i);
			if(::Save(f,b)==false){
				return false;
			}
		}
	}
	else if(h==QVariant::Bitmap){
		return false;
	}
	else if(h==QVariant::Bool){
		bool	b=d.toBool();
		if(::Save(f,b)==false)
			return false;
	}
	else if(h==QVariant::Brush){
		return false;
	}
	else if(h==QVariant::ByteArray){
		QByteArray	A=d.toByteArray();
		if(::Save(f,A)==false)
			return false;
	}
	else if(h==QVariant::Char){
		QChar	c=d.toChar();
		if(::Save(f,c)==false)
			return false;
	}
	else if(h==QVariant::Color){
		return false;
	}
	else if(h==QVariant::Cursor){
		return false;
	}
	else if(h==QVariant::Date){
		QDate	c=d.toDate();
		if(::Save(f,c)==false)
			return false;
	}
	else if(h==QVariant::DateTime){
		QDateTime	c=d.toDateTime();
		if(::Save(f,c)==false)
			return false;
	}
	else if(h==QVariant::Double){
		double	c=d.toDouble();
		if(::Save(f,c)==false)
			return false;
	}
	else if(h==QVariant::EasingCurve){
		return false;
	}
	else if(h==QVariant::Font){
		return false;
	}
	else if(h==QVariant::Hash){
		return false;
	}
	else if(h==QVariant::Icon){
		return false;
	}
	else if(h==QVariant::Image){
		return false;
	}
	else if(h==QVariant::Int){
		int	c=d.toInt();
		if(::Save(f,c)==false)
			return false;
	}
	else if(h==QVariant::KeySequence){
		return false;
	}
	else if(h==QVariant::Line){
		QLine	L=d.toLine();
		if(::Save(f,L.x1())==false)
			return false;
		if(::Save(f,L.y1())==false)
			return false;
		if(::Save(f,L.x2())==false)
			return false;
		if(::Save(f,L.y2())==false)
			return false;
	}
	else if(h==QVariant::LineF){
		QLineF	L=d.toLineF();
		if(::Save(f,L.x1())==false)
			return false;
		if(::Save(f,L.y1())==false)
			return false;
		if(::Save(f,L.x2())==false)
			return false;
		if(::Save(f,L.y2())==false)
			return false;
	}
	else if(h==QVariant::List){
		QList<QVariant>		A=d.toList();
		int32	Len=A.count();
		if(::Save(f,Len)==false)
			return false;
		for(int i=0;i<Len;i++){
			QVariant	b=A[i];
			if(::Save(f,b)==false){
				return false;
			}
		}
	}
	else if(h==QVariant::Locale){
		return false;
	}
	else if(h==QVariant::Map){
		return false;
	}
	else if(h==QVariant::Matrix){
		return false;
	}
	else if(h==QVariant::Transform){
		return false;
	}
	else if(h==QVariant::Matrix4x4){
		return false;
	}
	else if(h==QVariant::Palette){
		return false;
	}
	else if(h==QVariant::Pen){
		return false;
	}
	else if(h==QVariant::Pixmap){
		return false;
	}
	else if(h==QVariant::Point){
		QPoint	L=d.toPoint();
		if(::Save(f,L.x())==false)
			return false;
		if(::Save(f,L.y())==false)
			return false;
	}
	//if(h==QVariant::PointArray)
	else if(h==QVariant::PointF){
		QPointF	L=d.toPointF();
		if(::Save(f,L.x())==false)
			return false;
		if(::Save(f,L.y())==false)
			return false;
	}
	else if(h==QVariant::Polygon){
		return false;
	}
	else if(h==QVariant::Quaternion){
		return false;
	}
	else if(h==QVariant::Rect){
		QRect	L=d.toRect();
		if(::Save(f,L.x())==false)
			return false;
		if(::Save(f,L.y())==false)
			return false;
		if(::Save(f,L.width())==false)
			return false;
		if(::Save(f,L.height())==false)
			return false;
	}
	else if(h==QVariant::RectF){
		QRectF	L=d.toRectF();
		if(::Save(f,L.x())==false)
			return false;
		if(::Save(f,L.y())==false)
			return false;
		if(::Save(f,L.width())==false)
			return false;
		if(::Save(f,L.height())==false)
			return false;
	}
	else if(h==QVariant::RegExp){
		return false;
	}
	else if(h==QVariant::Region){
		return false;
	}
	else if(h==QVariant::Size){
		QSize	L=d.toSize();
		if(::Save(f,L.width())==false)
			return false;
		if(::Save(f,L.height())==false)
			return false;
	}
	else if(h==QVariant::SizeF){
		QSizeF	L=d.toSizeF();
		if(::Save(f,L.width())==false)
			return false;
		if(::Save(f,L.height())==false)
			return false;
	}
	else if(h==QVariant::SizePolicy){
		return false;
	}
	else if(h==QVariant::String){
		QString	L=d.toString();
		if(::Save(f,L)==false)
			return false;
	}
	else if(h==QVariant::StringList){
		QStringList	L=d.toStringList();
		if(::Save(f,L)==false)
			return false;
	}
	else if(h==QVariant::TextFormat){
		return false;
	}
	else if(h==QVariant::TextLength){
		return false;
	}
	else if(h==QVariant::Time){
		QTime	c=d.toTime();
		if(::Save(f,c)==false)
			return false;
	}
	else if(h==QVariant::UInt){
		uint	c=d.toUInt();
		if(::Save(f,c)==false)
			return false;
	}
	else if(h==QVariant::Url){
		return false;
	}
	else if(h==QVariant::Vector2D){
		return false;
	}
	else if(h==QVariant::Vector3D){
		return false;
	}
	else if(h==QVariant::Vector4D){
		return false;
	}
	else if(h==QVariant::UserType){
		return false;
	}
	return true;	
}

bool	Load(QIODevice *f,QVariant &d)
{	
	short	int	h;
	if(::Load(f,h)==false)
		return false;

	if(h==QVariant::Invalid)
		return true;
	else if(h==QVariant::BitArray){
		int32	Len;
		if(::Load(f,Len)==false)
			return false;
		QBitArray	A(Len);
		for(int i=0;i<Len;i++){
			bool	b;
			if(::Load(f,b)==false){
				return false;
			}
			A.setBit(i,b);
			d=A;
		}
	}
	else if(h==QVariant::Bitmap){
		return false;
	}
	else if(h==QVariant::Bool){
		bool	b;
		if(::Load(f,b)==false)
			return false;
		d=b;
	}
	else if(h==QVariant::Brush){
		return false;
	}
	else if(h==QVariant::ByteArray){
		QByteArray	A;
		if(::Load(f,A)==false)
			return false;
		d=A;
	}
	else if(h==QVariant::Char){
		QChar	c;
		if(::Load(f,c)==false)
			return false;
		d=c;
	}
	else if(h==QVariant::Color){
		return false;
	}
	else if(h==QVariant::Cursor){
		return false;
	}
	else if(h==QVariant::Date){
		QDate	c;
		if(::Load(f,c)==false)
			return false;
		d=c;
	}
	else if(h==QVariant::DateTime){
		QDateTime	c;
		if(::Load(f,c)==false)
			return false;
		d=c;
	}
	else if(h==QVariant::Double){
		double	c;
		if(::Load(f,c)==false)
			return false;
		d=c;
	}
	else if(h==QVariant::EasingCurve){
		return false;
	}
	else if(h==QVariant::Font){
		return false;
	}
	else if(h==QVariant::Hash){
		return false;
	}
	else if(h==QVariant::Icon){
		return false;
	}
	else if(h==QVariant::Image){
		return false;
	}
	else if(h==QVariant::Int){
		int	c;
		if(::Load(f,c)==false)
			return false;
		d=c;
	}
	else if(h==QVariant::KeySequence){
		return false;
	}
	else if(h==QVariant::Line){
		int	x1,y1,x2,y2;
		if(::Load(f,x1)==false)
			return false;
		if(::Load(f,y1)==false)
			return false;
		if(::Load(f,x2)==false)
			return false;
		if(::Load(f,y2)==false)
			return false;
		d=QLine(x1,y1,x2,y2);
	}
	else if(h==QVariant::LineF){
		qreal	x1,y1,x2,y2;
		if(::Load(f,x1)==false)
			return false;
		if(::Load(f,y1)==false)
			return false;
		if(::Load(f,x2)==false)
			return false;
		if(::Load(f,y2)==false)
			return false;
		d=QLineF(x1,y1,x2,y2);
	}
	else if(h==QVariant::List){
		QList<QVariant>		A;
		int32	Len;
		if(::Load(f,Len)==false)
			return false;
		for(int i=0;i<Len;i++){
			QVariant	b;
			if(::Load(f,b)==false){
				return false;
			}
			A.append(b);
		}
		d=A;
	}
	else if(h==QVariant::Locale){
		return false;
	}
	else if(h==QVariant::Map){
		return false;
	}
	else if(h==QVariant::Matrix){
		return false;
	}
	else if(h==QVariant::Transform){
		return false;
	}
	else if(h==QVariant::Matrix4x4){
		return false;
	}
	else if(h==QVariant::Palette){
		return false;
	}
	else if(h==QVariant::Pen){
		return false;
	}
	else if(h==QVariant::Pixmap){
		return false;
	}
	else if(h==QVariant::Point){
		int	x,y;
		if(::Load(f,x)==false)
			return false;
		if(::Load(f,y)==false)
			return false;
		d=QPoint(x,y);
	}
	//if(h==QVariant::PointArray)
	else if(h==QVariant::PointF){
		qreal	x,y;
		if(::Load(f,x)==false)
			return false;
		if(::Load(f,y)==false)
			return false;
		d=QPointF(x,y);
	}
	else if(h==QVariant::Polygon){
		return false;
	}
	else if(h==QVariant::Quaternion){
		return false;
	}
	else if(h==QVariant::Rect){
		int	x,y,w,h;
		if(::Load(f,x)==false)
			return false;
		if(::Load(f,y)==false)
			return false;
		if(::Load(f,w)==false)
			return false;
		if(::Load(f,h)==false)
			return false;
		d=QRect(x,y,w,h);
	}
	else if(h==QVariant::RectF){
		int	x,y,w,h;
		if(::Load(f,x)==false)
			return false;
		if(::Load(f,y)==false)
			return false;
		if(::Load(f,w)==false)
			return false;
		if(::Load(f,h)==false)
			return false;
		d=QRect(x,y,w,h);
	}
	else if(h==QVariant::RegExp){
		return false;
	}
	else if(h==QVariant::Region){
		return false;
	}
	else if(h==QVariant::Size){
		int	w,h;
		if(::Load(f,w)==false)
			return false;
		if(::Load(f,h)==false)
			return false;
		d=QSize(w,h);
	}
	else if(h==QVariant::SizeF){
		qreal	w,h;
		if(::Load(f,w)==false)
			return false;
		if(::Load(f,h)==false)
			return false;
		d=QSize(w,h);
	}
	else if(h==QVariant::SizePolicy){
		return false;
	}
	else if(h==QVariant::String){
		QString	L;
		if(::Load(f,L)==false)
			return false;
		d=L;
	}
	else if(h==QVariant::StringList){
		QStringList	L;
		if(::Load(f,L)==false)
			return false;
		d=L;
	}
	else if(h==QVariant::TextFormat){
		return false;
	}
	else if(h==QVariant::TextLength){
		return false;
	}
	else if(h==QVariant::Time){
		QTime	c;
		if(::Load(f,c)==false)
			return false;
		d=c;
	}
	else if(h==QVariant::UInt){
		uint	c;
		if(::Load(f,c)==false)
			return false;
		d=c;
	}
	else if(h==QVariant::Url){
		return false;
	}
	else if(h==QVariant::Vector2D){
		return false;
	}
	else if(h==QVariant::Vector3D){
		return false;
	}
	else if(h==QVariant::Vector4D){
		return false;
	}
	else if(h==QVariant::UserType){
		return false;
	}
	return true;	
}
bool	Save(QIODevice *f,const QColor &d)
{
	QRgb	c=d.rgba();
	if(f->write((const char *)&c,sizeof(c))!=sizeof(c)){
		return(false);
	}
	return true;
}
bool	Save(QIODevice *f,const QImage &d)
{
	bool	Effective=!d.isNull();
	if(::Save(f,Effective)==false){
		return false;
	}
	if(Effective==true){
		QByteArray	Ba;
		QBuffer	Buff(&Ba);
		Buff.open(QIODevice::ReadWrite);
		if(d.save(&Buff,"PNG")==false){
			return false;
		}
		return ::Save(f,Ba);
	}
	return true;
}
/*
bool	Save(QIODevice *f,QRgb &d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d))
		return(false);
	return true;
}
*/

bool	Save(QIODevice *f,const QByteArray &d)
{
	int32	Len=d.size();
	if(::Save(f,Len)==false){
		return false;
	}
	if(f->write(d)!=Len){
		return false;
	}
	return true;
}
bool	Save(QIODevice *f,BYTE **Point ,int XLen ,int YLen)
{
	for(int y=0;y<YLen;y++){
		if(f->write((const char *)Point[y],XLen)!=XLen){
			return false;
		}
	}
	return true;
}
bool	SaveText(QIODevice *f,char *s)
{
	int	Len=strlen(s);
	if(f->write((const char *)s,Len)!=Len){
		return false;
	}
	return true;
}


bool	Load(QIODevice *file,QString &d)
{
	int32	Len=0;
	if(file->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	
	char	LocalBuff[2000];
	char	*Buff;
	if((Len+1)>=2000){
		Buff=new char[Len+10];
	}
	else{
		Buff=LocalBuff;
	}
	if(file->read((char *)Buff,Len)!=Len){
		if(Buff!=LocalBuff){
			delete	[]Buff;
		}
		return(false);
	}
	Buff[Len]=0;
	d=/**/"";
	QChar *p=(QChar *)Buff;
	for(int i=0;i<Len;i+=2,p++){ 
		d+=*p;
	}
	if(Buff!=LocalBuff){
		delete	[]Buff;
	}
	return(true);
}

bool	Save(QIODevice *file,char *d)
{
	int32	Len=strlen(d);
	if(file->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(file->write((const char *)d,Len)!=Len){
		return(false);
	}
	return true;
}
char	*LoadStringInQString(QIODevice *file)
{
	int32	Len=0;
	if(file->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return NULL;
	}
	
	char	*Buff=new char[Len+1];
	char	*RetBuff=new char[Len/2+1];
	if(file->read((char *)Buff,Len)!=Len){
		delete	[]Buff;
		delete	[]RetBuff;
		return NULL;
	}
	QChar *p=(QChar *)Buff;
	for(int i=0;i<Len;i+=2,p++){ 
		RetBuff[i/2]=p->cell();
	}
	delete	[]Buff;
	RetBuff[Len/2]=0;
	return RetBuff;
}
char	*LoadString(QIODevice *file)
{
	int32	Len=0;
	if(file->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return NULL;
	}
	
	char	*Buff=new char[Len+1];
	if(file->read((char *)Buff,Len)!=Len){
		delete	[]Buff;
		return NULL;
	}
	Buff[Len]=0;
	return Buff;
}

bool	Save(QIODevice *file,const QStringList &d)
{
	int32	N=d.count();
	if(file->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(int i=0;i<N;i++){
		QString	A=d.value(i);
		if(::Save(file,A)==false){
			return false;
		}
	}
	return(true);
}
bool	Load(QIODevice *file,QStringList &d)
{
	int32	N;
	if(file->read((char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	d.clear();
	for(int i=0;i<N;i++){
		QString	A;
		if(::Load(file,A)==false){
			return false;
		}
		d.append(A);
	}
	return(true);
}
bool	Load(QIODevice *f,int8 &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,int32 &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,long &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}

bool	Load(QIODevice *f,uint32 &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}

bool	Load(QIODevice *f,WORD &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,short &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,DWORD &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,float &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,double &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,BYTE &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,QChar &d)
{
	ushort	unicode;
	if(::Load(f,unicode)==false){
		return false;
	}
	d=QChar(unicode);
	return true;
}
bool	Load(QIODevice *f,char &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,bool &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,bool3 &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}

bool	Load(QIODevice *f,char *d,int32 &Len ,int32 maxbuffsize)
{
	if(f->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(Len>maxbuffsize){
		return false;
	}
	if(f->read((char *)d,Len)!=Len){
		return false;
	}
	if(Len+1<maxbuffsize){
		d[Len]=0;
	}
	return true;
}
bool	Load(QIODevice *f,XYData &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return(false);
	}
	return(true);
}
bool	Load(QIODevice *f,QDateTime &d)
{
	WORD	wyear	;
	BYTE	wmonth	;
	BYTE	wday	;
	BYTE	whour	;
	BYTE	wminute	;
	BYTE	wsec	;
	if(::Load(f,wyear)==false){
		return false;
	}
	if(::Load(f,wmonth)==false){
		return false;
	}
	if(::Load(f,wday)==false){
		return false;
	}
	if(::Load(f,whour)==false){
		return false;
	}
	if(::Load(f,wminute)==false){
		return false;
	}
	if(::Load(f,wsec)==false){
		return false;
	}
	QDate	D(wyear,wmonth,wday);
	QTime	T(whour,wminute,wsec);

	d.setDate(D);
	d.setTime(T);

	return true;
}
bool	Load(QIODevice *f,QDate &d)
{
	WORD	wyear	;
	BYTE	wmonth	;
	BYTE	wday	;

	if(::Load(f,wyear)==false){
		return false;
	}
	if(::Load(f,wmonth)==false){
		return false;
	}
	if(::Load(f,wday)==false){
		return false;
	}
	d.setDate(wyear,wmonth,wday);

	return true;
}
bool	Load(QIODevice *f,QTime &d)
{
	BYTE	whour	;
	BYTE	wminute	;
	BYTE	wsec	;

	if(::Load(f,whour)==false){
		return false;
	}
	if(::Load(f,wminute)==false){
		return false;
	}
	if(::Load(f,wsec)==false){
		return false;
	}
	d.setHMS(whour,wminute,wsec);

	return true;
}
bool	Load(QIODevice *f,XDateTime &d)
{
	WORD	wyear	;
	BYTE	wmonth	;
	BYTE	wday	;
	BYTE	whour	;
	BYTE	wminute	;
	BYTE	wsec	;
	if(::Load(f,wyear)==false){
		return false;
	}
	if(::Load(f,wmonth)==false){
		return false;
	}
	if(::Load(f,wday)==false){
		return false;
	}
	if(::Load(f,whour)==false){
		return false;
	}
	if(::Load(f,wminute)==false){
		return false;
	}
	if(::Load(f,wsec)==false){
		return false;
	}
	d.set(wyear,wmonth,wday,whour ,wminute,wsec);
	return true;
}


bool	Load(QIODevice *f,QColor &d)
{
	QRgb	c;
	if(f->read((char *)&c,sizeof(c))!=sizeof(c)){
		return(false);
	}
	d.setRgba(c);
	return true;
}
/*
bool	Load(QIODevice *f,QRgb &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return(false);
	}
	return true;
}
*/
bool	Load(QIODevice *f,QImage &d)
{
	bool	Effective;
	if(::Load(f,Effective)==false){
		return false;
	}
	if(Effective==true){
		QByteArray	Ba;
		if(::Load(f,Ba)==false){
			return false;
		}
		if(d.loadFromData(Ba,"PNG")==false){
			return false;
		}
		return true;
	}
	else{
		QImage	DummyImage;
		d=DummyImage;
		return true;
	}
}
bool	Load(QIODevice *f,QByteArray &d)
{
	int32	Len;
	if(::Load(f,Len)==false){
		return false;
	}
	d=f->read(Len);
	if(d.size()!=Len){
		return false;
	}
	return true;
}
bool	Load(QIODevice *f,BYTE **Point ,int XLen ,int YLen)
{
	for(int y=0;y<YLen;y++){
		if(f->read((char *)Point[y],XLen)!=XLen){
			return false;
		}
	}
	return true;
}
bool	Load(QIODevice *f,QPoint &d)
{
	int32	P[2];

	if(f->read((char *)P,sizeof(P))!=sizeof(P)){
		return false;
	}
	d.setX(P[0]);
	d.setY(P[1]);
	return true;
}

QString ForceDirectories( QString path )
{
	char delim = '/';
	QStringList dirs = (path).split(QRegularExpression("[/\\\\]"), QString::SkipEmptyParts);
	if(dirs.count()==0)
		return path;
	if(path.left(2)=="//" || path.left(2)=="\\\\"){
		QString	sDir=QString("//")+dirs[0];
		for(int i=1; i<dirs.count(); i++){
			QDir dir(sDir);
			sDir+=delim;
			sDir+=dirs[i];
			dir.mkdir(dirs[i]);
		}
		return sDir;
	}
	else{
		//QDir dir(dirs[0] + delim);
		QDir dir;
		for(int i=0; i<dirs.count(); i++){
			if(!dir.exists(dirs[i])){
				if(!dir.mkdir(dirs[i])){
					return dir.path();
				}
			}
			if(!dir.cd(dirs[i])){
				return dir.path();
			}
		}
		return dir.path();
	}
}

QStringList	FindFiles(const QString &dir ,const QString &FileFilter)
{
	QStringList	Ret;

	QString	NowCD;
	NowCD=QDir::currentPath();

	QDir	LDir(dir);
	LDir.cd(dir);

	QStringList	FileFilterList;
	FileFilterList.append(FileFilter);
	QStringList	List=LDir.entryList(FileFilterList,QDir::NoDotAndDotDot | QDir::Files);
	for(int i=0;i<List.count();i++){
		Ret+=dir+QDir::separator()+List[i];
	}

	QStringList	Filter;
	Filter.append("*");
	QStringList	DirList=LDir.entryList(Filter,QDir::NoDotAndDotDot | QDir::Dirs);
	for(int i=0;i<DirList.count();i++){
		QString	PathName=dir+QDir::separator()+DirList[i];
		QStringList	r=FindFiles(PathName,FileFilter);
		Ret.append(r);
	}
	QDir	CurrentDir(NowCD);
	CurrentDir.cd(NowCD);
	return Ret;
}

void	SetWidgetCenter(QWidget *f)
{
	if(f!=NULL){
		if(f->parentWidget()==NULL || dynamic_cast<QDialog *>(f)!=NULL){
			QDesktopWidget *q=QApplication::desktop();		
			if(f!=NULL){			
				QRect R=q->availableGeometry ();
				//f->setGeometry((R.width ()-f->width ())/2 ,(R.height()-f->height())/2,f->width() ,f->height());
				f->move((R.width ()-f->width ())/2 ,(R.height()-f->height())/2);
			}
		}
		else{
			QWidget	*s=f->parentWidget();
			//f->setGeometry((s->width ()-f->width ())/2 ,(s->height()-f->height())/2 ,f->width() ,f->height());
			f->move((s->width ()-f->width ())/2 ,(s->height()-f->height())/2);
		}
	}
}

//============================================================================

class	TmpThread : public QThread
{
public:
	void run (){}

	static	void	TmpGSleep(unsigned int milisec){	msleep(milisec);	}
};


void	GSleep(unsigned int milisec)
{
	TmpThread::TmpGSleep(milisec);
}

//============================================================================

QTableWidgetItem	*SetDataToTable(QTableWidget *W ,int col ,int row ,const QVariant &value ,Qt::ItemFlags flags)
{
	W->model()->setData(W->model()->index(row,col),value);

	QTableWidgetItem *L=W->item ( row, col);
	if(L!=NULL){
		L->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | flags);
	}
	return L;
}

QString	GetDataToTable(QTableWidget *W ,int col ,int row)
{
	return(W->model()->data(W->model()->index(row,col)).toString());
}

void	SetDataToTableCheckable(QTableWidget *W ,int col ,int row ,const QVariant &value ,bool Checked)
{
	//W->model()->setData(W->model()->index(row,col),value);

	QTableWidgetItem *L=W->item ( row, col);
	if(L==NULL || dynamic_cast<QCheckBox *>(L)==NULL){
		QCheckBox	*b=new QCheckBox();
		b->setChecked(Checked);
		b->setText(value.toString());
		W->setCellWidget(row,col,b);
	}
	else{
		QCheckBox	*b=dynamic_cast<QCheckBox *>(L);
		b->setChecked(Checked);
		b->setText(value.toString());
	}

	//QTableWidgetItem *L=W->item ( row, col);
	//if(L!=NULL){
	//	L->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
	//}
}

bool	GetCheckedFromTable(QTableWidget *W ,int col ,int row)
{
	QWidget *w=W->cellWidget(row,col);
	if(w!=NULL){
		QCheckBox	*b=dynamic_cast<QCheckBox *>(w);
		if(b!=NULL){
			return b->isChecked();
		}
	}
	QTableWidgetItem *L=W->item ( row, col);
	if(L!=NULL && L->checkState()==Qt::Checked){
		return true;
	}
	return false;
}


void	SetTableColor(QTableWidget *W ,int col ,int row ,const QColor &Col)
{
	QTableWidgetItem	*t=W->item(row,col);
	if(t!=NULL){
		t->setBackgroundColor(Col);
	}
}
void	SetListColor(QListWidget *W ,int row ,const QColor &Col)
{
    QListWidgetItem	*t=W->item(row);
    if(t!=NULL){
        t->setBackgroundColor(Col);
    }
}
int		GetSelectedCurrentRow(QTableWidget *W)
{
	if(W->selectedItems ().isEmpty()==true){
		return(-1);
	}
	QTableWidgetItem *f=W->selectedItems ().first();
	if(f==NULL){
		return(-1);
	}
	return(W->row(f));
}

int		GetSelectedRows(QTableWidget *W ,IntList &Rows)
{
	Rows.RemoveAll();
	QList<QTableWidgetItem *>	Q=W->selectedItems ();
	int	N=Q.count();
	int	Counter=0;
	for(int i=0;i<N;i++){
		if(Q[i]->column()==0){
			Rows.AppendList(new IntClass(Q[i]->row()));
			Counter++;
		}
	}
	return Counter;
}
int		GetSelectedRows(QListWidget *W,IntList &Rows)
{
	Rows.RemoveAll();
	int	N=W->count();
	int	Counter=0;
	for(int i=0;i<N;i++){
		QListWidgetItem *q=W->item(i);
		if(q->isSelected()==true){
			Rows.AppendList(new IntClass(i));
			Counter++;
		}
	}
	return Counter;
}

void		SetSelectedRows(QTableWidget *W ,IntList &Rows)
{
	int	RowCount	=W->rowCount();
	int	ColumnCount	=W->columnCount();
	for(int row=0;row<RowCount;row++){
		for(int column=0;column<ColumnCount;column++){
			QTableWidgetItem *c=W->item(row,column);
			if(Rows.IsInclude(row)==true){
				c->setSelected(true);
			}
			else{
				c->setSelected(false);
			}
		}
	}
}

bool	SetCurrentIndex(QStackedWidget *W ,const QString &TabName)
{
	int	N=W->count();
	for(int i=0;i<N;i++){
		QWidget *w=W->widget (i);
		if(w==NULL)
			continue;
		if(w->objectName()==TabName){
			W->setCurrentIndex(i);
			return true;
		}
	}
	return false;
}
QStringList	GetDataFromListWidget(QListWidget *W)
{
	QStringList	Str;
	for(int i=0;i<W->count();i++){
		QListWidgetItem	*q=W->item(i);
		if(q!=NULL){
			Str.append(q->text());
		}
	}
	return Str;
}
