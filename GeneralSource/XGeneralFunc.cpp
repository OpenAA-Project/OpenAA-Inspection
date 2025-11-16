/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGeneralFunc.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
//#include <QtGui>
#include "XGeneralFunc.h"
#include <stdio.h>
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XYCross.h"
#include <omp.h>
#include "swap.h"
#include <QTextCodec>
#include "XIntClass.h"
#include "XDateTime.h"
#include <QMessageBox>
#include <QCheckBox>
#include <QApplication>
#include <QComboBox>
#include <QToolBox>
#include<QStackedWidget>
#include<QListWidget>
#include<QTableWidget>
#include<QTreeWidget>
#include<QHeaderView>
#include<QScrollBar>
#include <QSpinBox>
#include <QDoubleSpinBox>

bool	FuncCall	Save(QIODevice *f,const QColor &d)
{
	QRgb	c=d.rgba();
	if(f->write((const char *)&c,sizeof(c))!=sizeof(c)){
		return(false);
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,const QImage &d)
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

bool	FuncCall	Load(QIODevice *f,QColor &d)
{
	QRgb	c;
	if(f->read((char *)&c,sizeof(c))!=sizeof(c)){
		return(false);
	}
	d.setRgba(c);
	return true;
}

/*
bool	FuncCall	Load(QIODevice *f,QRgb &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return(false);
	}
	return true;
}
*/
bool	FuncCall	Load(QIODevice *f,QImage &d)
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


bool	FuncCall	Save(QIODevice *f,const QVariant &d)
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
	else if(h==QVariant::LongLong){
		int64	c=d.toLongLong();
		if(::Save(f,c)==false)
			return false;
	}
	else if(h==QVariant::Map){
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
	else if(h==QVariant::RegularExpression){
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
	else if(h==QVariant::ULongLong){
		qulonglong	c=d.toULongLong();
		int64	cd=c;
		if(::Save(f,cd)==false)
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

bool	FuncCall	Load(QIODevice *f,QVariant &d)
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
	else if(h==QVariant::LongLong){
		int64	c;
		if(::Load(f,c)==false)
			return false;
		d=c;
	}
	else if(h==QVariant::Map){
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
	else if(h==QVariant::RegularExpression){
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
	else if(h==QVariant::ULongLong){
		qulonglong	c;
		int64	cd;
		if(::Load(f,cd)==false)
			return false;
		c=cd;
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

void	FuncCall	ErrorOccurs(void)
{
	QMessageBox	MBox(QMessageBox::Critical,"Error","_CrtCheckMemory");
	MBox.exec();
}

bool	FuncCall	IsEqual(const QDateTime &d1 ,const QDateTime &d2)
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
bool	FuncCall	IsEqual(const QStringList &L1,const QStringList &L2)
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


void	FuncCall	SetWidgetCenter(QWidget *f)
{
	if(f!=NULL){
		if(f->parentWidget()==NULL || dynamic_cast<QDialog *>(f)!=NULL){
			QScreen *q=QGuiApplication::screens()[0];		
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

int	FuncCall	QString2Char(const QString &str ,char *buff ,int buffsize)
{
	static	QTextCodec	*h=NULL;
	if(h==NULL){
#if	QT_VERSION<0x050000
		QTextCodec	*hh=QTextCodec::codecForCStrings();
#else
		QTextCodec* hh = QTextCodec::codecForLocale();
#endif
		if(hh!=NULL){
			//char	*hs=hh->name().data();
			//if(strcmp(hs,"Shift-JIS")==0){
				h=hh;
			//}
		}
		if(h==NULL){
			h=QTextCodec::codecForName("Shift-JIS");
		}
	}
	char	*fp=buff;
	const QChar	*s =str.data();
	int i,j;
	if(h!=NULL){
		bool	LoopOk=true;
		for(i=j=0;j<buffsize-1 && i<str.size() && LoopOk==true;i++){
			if(s->unicode()<256){
				QByteArray	A=h->fromUnicode(s,1);
				*fp=*((char *)A.data());
				fp++;
			}
			else{
				QByteArray	A=h->fromUnicode(s,1);
				char	*cp=A.data();
				*fp=*cp;
				fp++;
				cp++;
				if(*cp!=0){
					j++;
					if(j<buffsize-1){
						*fp=*cp;
						fp++;
					}
					else{
						LoopOk=false;
					}
				}
			}
			j++;
			s++;
		}
	}
	else{
		bool	LoopOk=true;
		for(i=j=0;j<buffsize-1 && i<str.size() && LoopOk==true;i++){
			if(s->unicode()<256){
				*fp=*((char *)s);
				fp++;
			}
			else{
				*fp=*((char *)s);
				fp++;
				*fp=*(((char *)s)+1);
				fp++;
				j++;
				if(j>=buffsize-1){
					LoopOk=false;
				}
			}
			j++;
			s++;
		}
	}
	*fp=0;
	return(i);
}


//============================================================================

class	TmpThread : public QThread
{
public:
	void run (){}

	static	void	TmpGSleep(unsigned int milisec){	msleep(milisec);	}
};


void	FuncCall	GSleep(unsigned int milisec)
{
	TmpThread::TmpGSleep(milisec);
}

//============================================================================

QTableWidgetItem	*SetDataToTable(QTableWidget *W ,int col ,int row ,const QVariant &value ,Qt::ItemFlags flags)
{
	if(W!=NULL){
		QAbstractItemModel *m=W->model();
		if(m!=NULL){
			m->setData(m->index(row,col),value);

			QTableWidgetItem *L=W->item ( row, col);
			if(L!=NULL){
				L->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | flags);
			}
			return L;
		}
	}
	return NULL;
}

QString	FuncCall	GetDataToTable(QTableWidget *W ,int col ,int row)
{
	QAbstractItemModel *m=W->model();
	return(m->data(m->index(row,col)).toString());
}

CheckBoxInTable::CheckBoxInTable(int column ,int row)
	:Row(row),Column(column)
{
	connect(this,SIGNAL(checked(bool)),this,SLOT(SlotChecked(bool)));
}
void	CheckBoxInTable::SlotChecked(bool b)
{
	emit	SignalChecked(Column,Row ,b);
}

PushButtonInTable::PushButtonInTable(int column ,int row)
	:Row(row),Column(column)
{
	setAutoFillBackground(true);
	setFlat(true);
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}
void	PushButtonInTable::SlotClicked()
{
	emit	SignalClicked(Column,Row);
}


CheckBoxInTable		*FuncCall	SetDataToTableCheckable(QTableWidget *W ,int col ,int row ,const QVariant &value ,bool Checked)
{
	//W->model()->setData(W->model()->index(row,col),value);

	QTableWidgetItem *L=W->item ( row, col);
	if(L==NULL || dynamic_cast<QCheckBox *>(L)==NULL){
		CheckBoxInTable	*b=new CheckBoxInTable(col,row);
		b->setChecked(Checked);
		b->setText(value.toString());
		W->setCellWidget(row,col,b);
		return b;
	}
	else{
		CheckBoxInTable	*b=dynamic_cast<CheckBoxInTable *>(L);
		if(b!=NULL){
			b->setChecked(Checked);
			b->setText(value.toString());
			return b;
		}
	}
	return NULL;
}

PushButtonInTable	*SetDataColorToTable(QTableWidget* W, int col, int row, const QColor &Col)
{
	QTableWidgetItem *L=W->item ( row, col);
	if(L==NULL || dynamic_cast<QCheckBox *>(L)==NULL){
		PushButtonInTable	*b=new PushButtonInTable(col,row);
		b->setText(/**/"");
		QPalette	P=b->palette();
		P.setColor(QPalette::Button,Col);
		b->setPalette(P);
		W->setCellWidget(row,col,b);
		return b;
	}
	else{
		PushButtonInTable	*b=dynamic_cast<PushButtonInTable *>(L);
		if(b!=NULL){
			QPalette	P=b->palette();
			P.setColor(QPalette::Button,Col);
			b->setPalette(P);
			return b;
		}
	}
	return NULL;
}
bool	FuncCall	GetCheckedFromTable(QTableWidget *W ,int col ,int row)
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

QComboBox	*SetDataToTableComboBox(QTableWidget *W ,int col ,int row ,QStringList &List ,int CurrnetIndex)
{
	//W->model()->setData(W->model()->index(row,col),value);
	QTableWidgetItem *L=W->item ( row, col);
	if(L==NULL || dynamic_cast<QComboBox *>(L)==NULL){
		QComboBox	*b=new QComboBox();
		b->addItems(List);
		b->setCurrentIndex(CurrnetIndex);
		W->setCellWidget(row,col,b);
		return b;
	}
	else{
		QComboBox	*b=dynamic_cast<QComboBox *>(L);
		b->addItems(List);
		b->setCurrentIndex(CurrnetIndex);
		return b;
	}
}
bool	FuncCall	SetDataToTableComboBoxIndex(QTableWidget *W ,int col ,int row ,int Index)
{
	QWidget *w=W->cellWidget(row,col);
	if(w!=NULL){
		QComboBox	*b=dynamic_cast<QComboBox *>(w);
		if(b!=NULL){
			b->setCurrentIndex(Index);
			return true;
		}
	}
	return false;
}
int		FuncCall	GetDataToTableComboBoxIndex(QTableWidget *W ,int col ,int row)
{
	QWidget *w=W->cellWidget(row,col);
	if(w!=NULL){
		QComboBox	*b=dynamic_cast<QComboBox *>(w);
		if(b!=NULL){
			return b->currentIndex();
		}
	}
	return -1;
}
QSpinBox	*FuncCall	SetDataToTableSpinBox(QTableWidget* W, int col, int row, int value ,int MinValue ,int MaxValue)
{
	QWidget *L=W->cellWidget( row, col);
	if(L==NULL || dynamic_cast<QSpinBox *>(L)==NULL){
		QSpinBox	*b=new QSpinBox();
		b->setMinimum(MinValue);
		b->setMaximum(MaxValue);
		b->setValue(value);
		W->setCellWidget(row,col,b);
		return b;
	}
	else{
		QSpinBox	*b=dynamic_cast<QSpinBox *>(L);
		b->setMinimum(MinValue);
		b->setMaximum(MaxValue);
		b->setValue(value);
		return b;
	}
}
QDoubleSpinBox		*SetDataToTableDoubleSpinBox(QTableWidget* W, int col, int row, double value ,double MinValue,double MaxValue)
{
	QWidget *L=W->cellWidget( row, col);
	if(L==NULL || dynamic_cast<QDoubleSpinBox *>(L)==NULL){
		QDoubleSpinBox	*b=new QDoubleSpinBox();
		b->setMinimum(MinValue);
		b->setMaximum(MaxValue);
		b->setValue(value);
		W->setCellWidget(row,col,b);
		return b;
	}
	else{
		QDoubleSpinBox	*b=dynamic_cast<QDoubleSpinBox *>(L);
		b->setMinimum(MinValue);
		b->setMaximum(MaxValue);
		b->setValue(value);
		return b;
	}
}
int			FuncCall	GetDataToTableSpinBox(QTableWidget* W, int col, int row)
{
	QWidget *L=W->cellWidget( row, col);
	if(L!=NULL){
		QSpinBox	*b=dynamic_cast<QSpinBox *>(L);
		if(b!=NULL){
			return b->value();
		}
	}
	return -1;
}
double			GetDataToTableDoubleSpinBox(QTableWidget* W, int col, int row)
{
	QWidget *L=W->cellWidget( row, col);
	if(L!=NULL){
		QDoubleSpinBox	*b=dynamic_cast<QDoubleSpinBox *>(L);
		if(b!=NULL){
			return b->value();
		}
	}
	return -1;
}

void	FuncCall	SetTableColor(QTableWidget *W ,int col ,int row ,const QColor &Col)
{
	QTableWidgetItem	*t=W->item(row,col);
	if(t!=NULL){
		QBrush	b=t->background();
		b.setColor(Col);
		t->setBackground(b);
	}
}
QColor	FuncCall	GetTableColor(QTableWidget* W, int col, int row)
{
	QTableWidgetItem	*t=W->item(row,col);
	if(t!=NULL){
		QBrush	b=t->background();
		return b.color();
	}
	return Qt::white;
}

void	FuncCall	SetListColor(QListWidget *W ,int row ,const QColor &Col)
{
	QListWidgetItem	*t=W->item(row);
	if(t!=NULL){
		QBrush	b=t->background();
		b.setColor(Col);
	}
}

int		FuncCall	GetSelectedCurrentRow(QTableWidget *W)
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

int		FuncCall	GetSelectedRows(QTableWidget *W ,IntList &Rows)
{
	Rows.RemoveAll();
	QList<QTableWidgetItem *>	Q=W->selectedItems ();
	int	N=Q.count();
	int	Counter=0;
	for(int i=0;i<N;i++){
		int	r=Q[i]->row();
		if(Rows.IsInclude(r)==false){
			Rows.Add(r);
			Counter++;
		}
	}
	return Counter;
}
int		FuncCall	GetSelectedRows(QListWidget *W,IntList &Rows)
{
	Rows.RemoveAll();
	int	N=W->count();
	int	Counter=0;
	for(int i=0;i<N;i++){
		QListWidgetItem *q=W->item(i);
		if(q->isSelected()==true){
			Rows.Add(i);
			Counter++;
		}
	}
	return Counter;
}

void		FuncCall	SetSelectedRows(QTableWidget *W ,IntList &Rows)
{
	int	RowCount	=W->rowCount();
	int	ColumnCount	=W->columnCount();
	W->setUpdatesEnabled(false);
	for(int row=0;row<RowCount;row++){
		bool	B=(Rows.IsInclude(row)==true)?true:false;

		for(int column=0;column<ColumnCount;column++){
			QTableWidgetItem *c=W->item(row,column);
			if(c!=NULL){
				c->setSelected(B);
			}
		}
	}
	W->setUpdatesEnabled(true);
}
void	FuncCall	SetSelectedRows(QListWidget *W, IntList& Rows)
{
	int	RowCount	=W->count();
	W->setUpdatesEnabled(false);
	for(int row=0;row<RowCount;row++){
		bool	B=(Rows.IsInclude(row)==true)?true:false;
		QListWidgetItem *c=W->item(row);
		if(c!=NULL){
			c->setSelected(B);
		}
	}
	W->setUpdatesEnabled(true);
}

void	GetSelectedItemsInner(QTreeWidgetItem *W ,IntList &List ,IntListContainer &ItemNumber)
{
	IntList TmpList=List;
	int	N=W->childCount();
	for(int i=0;i<N;i++){
		TmpList.Add(i);
		QTreeWidgetItem *t=W->child(i);
		if(t->isSelected()==true){
			ItemNumber.Add(TmpList);
		}
		GetSelectedItemsInner(t, TmpList ,ItemNumber);
	}
}

void	FuncCall	GetSelectedItems(QTreeWidget *W, IntListContainer &ItemNumber)
{
	int	N=W->topLevelItemCount();
	for(int i=0;i<N;i++){
		IntList	List;
		List.Add(i);
		QTreeWidgetItem *t=W->topLevelItem(i);
		if(t->isSelected()==true){
			ItemNumber.Add(List);
		}
		GetSelectedItemsInner(t, List ,ItemNumber);
	}
}

void	SetSelectedItemsInner(QTreeWidgetItem *W ,IntList &List ,IntListContainer &ItemNumber)
{
	IntList TmpList=List;
	int	N=W->childCount();
	for(int i=0;i<N;i++){
		TmpList.Add(i);
		QTreeWidgetItem *t=W->child(i);
		if(ItemNumber.IsInclude(TmpList)==true){
			t->setSelected(true);
		}
		else{
			t->setSelected(false);
		}
		GetSelectedItemsInner(t, TmpList ,ItemNumber);
	}
}

void	FuncCall	SetSelectedItems(QTreeWidget *W, IntListContainer &ItemNumber)
{
	int	N=W->topLevelItemCount();
	for(int i=0;i<N;i++){
		IntList	List;
		List.Add(i);
		QTreeWidgetItem *t=W->topLevelItem(i);
		if(ItemNumber.IsInclude(List)==true){
			t->setSelected(true);
		}
		else{
			t->setSelected(false);
		}
		SetSelectedItemsInner(t, List ,ItemNumber);
	}
	QList<QTreeWidgetItem *> Q=W->selectedItems();
	if(Q.count()!=0){
		W->setCurrentItem(Q[0]);
	}
}

void	FuncCall	SetCurrentRow(QTableWidget *W ,int row)
{
	W->setCurrentCell(row,0);																																																																																																																																																																																																																																																				
}

bool	FuncCall	SetCurrentIndex(QStackedWidget *W ,const QString &TabName)
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
QStringList	FuncCall	GetDataFromListWidget(QListWidget *W)
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
void	SetColumnWidthInTable(QTableWidget *table ,int column, int Percentage)
{
	table->update();
	int	W=table->width();
	if(table->verticalHeader()!=NULL){
		if(table->verticalHeader()->isVisible()==true){
			int	VW=table->verticalHeader()->width();
			W -= VW;
		}
	}
	QScrollBar	*VBar=table->verticalScrollBar();
	if(VBar!=NULL){
		if(VBar->isVisible()==true && VBar->isHidden()==false){
			int	VW=table->verticalScrollBar()->width();
			W-=VW;
		}
	}
	int	t1=(table->columnCount()+1)*table->lineWidth();
	int	t2=table->autoScrollMargin();
	W-=2*table->frameWidth()+max(t1,t2)+4+8;
	table->setColumnWidth(column,W*Percentage/100);
}

char	* FuncCall	ToStr(char Text[] ,int N)
{
	char	*fp=Text;
	if(N<0){
		*fp='-';
		fp++;
		N=-N;
	}
	int	Base=0;
	if(N>1000000000)
		Base=1000000000;
	else if(N>100000000)
		Base=100000000;
	else if(N>10000000)
		Base=10000000;
	else if(N>1000000)
		Base=1000000;
	else if(N>100000)
		Base=100000;
	else if(N>10000)
		Base=10000;
	else if(N>1000)
		Base=1000;
	else if(N>100)
		Base=100;
	else if(N>10)
		Base=100;
	else
		Base=1;

	while(Base>0){
		int	k=N/Base;
		*fp='0'+k;
		fp++;
		N-=k*Base;
		Base/=10;
	}
	*fp=0;
	return fp;
}

char	* FuncCall	ToStr(char Text[] ,double N ,int Decimal)
{
	char	*fp=Text;
	if(N<0){
		*fp='-';
		fp++;
		N=-N;
	}
	int	Base=0;
	if(N>1000000000)
		Base=1000000000;
	else if(N>100000000)
		Base=100000000;
	else if(N>10000000)
		Base=10000000;
	else if(N>1000000)
		Base=1000000;
	else if(N>100000)
		Base=100000;
	else if(N>10000)
		Base=10000;
	else if(N>1000)
		Base=1000;
	else if(N>100)
		Base=100;
	else if(N>10)
		Base=100;
	else
		Base=1;

	while(Base>0){
		int	k=N/Base;
		*fp='0'+k;
		fp++;
		N-=k*Base;
		Base/=10;
	}
	if(N>0.0){
		double	dBase=0.1;
		for(int i=0;i<Decimal && N>0;i++){
			int	k=N/dBase;
			*fp='0'+k;
			fp++;
			N-=k*dBase;
			dBase*=0.1;
		}
	}

	*fp=0;
	return fp;
}
QColor	FuncCall	GetReverseColor(const QColor &c)
{
	QColor	Col(255-c.red(),255-c.green(),255-c.blue(),c.alpha());
	return Col;
}

inline	bool IsHideByRect(QRect &dest ,QRect &src)
{
	if(dest.left()>=src.left() && dest.right()<=src.right()
	&& dest.top()>=src.top() && dest.bottom()<=src.bottom())
		return true;
	return false;
}

bool	FuncCall	CheckHidden(QWidget *v)	//If v is overlapped by other widget or tab/stacked widget , it returns true
{
	QWidget	*p=v->parentWidget();
	if(p==NULL)
		return false;
	QStackedWidget	*s1=dynamic_cast<QStackedWidget *>(p);
	if(s1!=NULL){
		if(s1->currentWidget()==v)
			return false;
		else
			return true;
	}
	QTabWidget	*s2=dynamic_cast<QTabWidget *>(p);
	if(s2!=NULL){
		if(s2->currentWidget()==v)
			return false;
		else
			return true;
	}
	QToolBox	*s3=dynamic_cast<QToolBox *>(p);
	if(s3!=NULL){
		if(s3->currentWidget()==v)
			return false;
		else
			return true;
	}
	const QObjectList &Q=p->children ();
	int	N=Q.count();
	int	i;
	for(i=0;i<N;i++){
		QObject	*o=Q[i];
		QWidget	*w=dynamic_cast<QWidget *>(o);
		if(w==v){
			i++;
			break;
		}
	}
	QRect	VRect;
	if(i<N){
		VRect=v->geometry();
	}
	for(;i<N;i++){
		QObject	*o=Q[i];
		QWidget	*w=dynamic_cast<QWidget *>(o);
		if(w!=NULL){
			QRect	WRect=w->geometry();
			if(IsHideByRect(VRect,WRect)==true){
				return true;
			}
		}
	}
	return CheckHidden(p);
}
void	SetEnabledForChildren(QObject *b,bool flag)
{
	const QObjectList &Q=b->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QWidget *base=dynamic_cast<QWidget *>(Q[i]);
		if(base!=NULL){
			base->setEnabled(flag);
		}
		SetEnabledForChildren(Q[i],flag);
	}
}