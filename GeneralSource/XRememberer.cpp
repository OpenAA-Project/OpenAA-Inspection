/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XRememberer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XRememberer.h"
#include <QFile>
#include "XGeneralFunc.h"


int		ControlRemembererListContainer::GetInt(QWidget *W	,int defaultValue)
{
	int	Ret;
	if(GetValue(W,Ret)==true){
		return Ret;
	}
	return defaultValue;
}

QString	ControlRemembererListContainer::GetString(QWidget *W	,const QString &defaultValue)
{
	QString	Ret;
	if(GetValue(W,Ret)==true){
		return Ret;
	}
	return defaultValue;
}
bool	ControlRemembererListContainer::GetBool(QWidget *W	,bool defaultValue)
{
	bool	Ret;
	if(GetValue(W,Ret)==true){
		return Ret;
	}
	return defaultValue;
}
double	ControlRemembererListContainer::GetDouble(QWidget *W	,double defaultValue)
{
	double	Ret;
	if(GetValue(W,Ret)==true){
		return Ret;
	}
	return defaultValue;
}
QStringList	ControlRemembererListContainer::GetStringList(QWidget *W	,const QStringList &defaultValue)
{
	QStringList	Ret;
	if(GetValue(W,Ret)==true){
		return Ret;
	}
	return defaultValue;
}
QDateTime	ControlRemembererListContainer::GetDateTime		(QWidget *W,const QDateTime &defaultValue)
{
	QDateTime	Ret;
	if(GetValue(W,Ret)==true){
		return Ret;
	}
	return defaultValue;
}

bool	ControlRemembererListContainer::GetValue(QWidget *W	,int		&Ret)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Int && IsEqual(c->GetObjectNameList(),L)==true){
			Ret=c->GetInt();
			return true;
		}
	}
	return false;
}
bool	ControlRemembererListContainer::GetValue(QWidget *W	,double		&Ret)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Double && IsEqual(c->GetObjectNameList(),L)==true){
			Ret=c->GetDouble();
			return true;
		}
	}
	return false;
}
bool	ControlRemembererListContainer::GetValue(QWidget *W ,QString	&Ret)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QString && IsEqual(c->GetObjectNameList(),L)==true){
			Ret=c->GetString();
			return true;
		}
	}
	return false;
}
bool	ControlRemembererListContainer::GetValue(QWidget *W	,bool		&Ret)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Bool && IsEqual(c->GetObjectNameList(),L)==true){
			Ret=c->GetBool();
			return true;
		}
	}
	return false;
}
bool	ControlRemembererListContainer::GetValue(QWidget *W ,QStringList&Ret)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QStringList && IsEqual(c->GetObjectNameList(),L)==true){
			Ret=c->GetStringList();
			return true;
		}
	}
	return false;
}
bool	ControlRemembererListContainer::GetValue(QWidget *W ,QDateTime	&Ret)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QDateTime && IsEqual(c->GetObjectNameList(),L)==true){
			Ret=c->GetDateTime();
			return true;
		}
	}
	return false;
}
bool	ControlRemembererListContainer::GetValue(QWidget *W ,IntListContainer &Ret)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QTreeWidget && IsEqual(c->GetObjectNameList(),L)==true){
			Ret=c->GetTreeWidget();
			return true;
		}
	}
	return false;
}


ControlRemembererList::ControlRemembererList(void)
{
	RType=_Int;
	Value=NULL;
}
ControlRemembererList::~ControlRemembererList(void)
{
	ReleaseValue();
	Value=NULL;
}
void		ControlRemembererList::SetRecogName(const QString &name)
{
	if(ObjectNameList.count()==0){
		ObjectNameList.append(name);
	}
	else{
		ObjectNameList[0]=name;
	}
}

int		ControlRemembererList::GetInt(void)
{
	if(Value!=NULL && RType==_Int){
		return *((int *)Value);
	}
	return 0;
}
QString	ControlRemembererList::GetString(void)
{
	if(Value!=NULL && RType==_QString){
		return *((QString *)Value);
	}
	return "";
}
QDateTime	ControlRemembererList::GetDateTime(void)
{
	if(Value!=NULL && RType==_QDateTime){
		return *((QDateTime *)Value);
	}
	return QDateTime();
}
bool	ControlRemembererList::GetBool(void)
{
	if(Value!=NULL && RType==_Bool){
		return *((bool *)Value);
	}
	return true;
}
double	ControlRemembererList::GetDouble(void)
{
	if(Value!=NULL && RType==_Double){
		return *((double *)Value);
	}
	return true;
}
QStringList	ControlRemembererList::GetStringList(void)
{
	if(Value!=NULL && RType==_QStringList){
		return *((QStringList *)Value);
	}
	return QStringList();
}
QByteArray	ControlRemembererList::GetByteArray(void)
{
	if(Value!=NULL && RType==_QByteArray){
		return *((QByteArray *)Value);
	}
	return QByteArray();
}
IntListContainer		ControlRemembererList::GetTreeWidget(void)
{
	if(Value!=NULL && RType==_QTreeWidget){
		return *((IntListContainer *)Value);
	}
	return IntListContainer();
}
IntList	ControlRemembererList::GetIntList(void)
{
	if(Value!=NULL && RType==_IntList){
		return *((IntList *)Value);
	}
	return IntList();
}
void	ControlRemembererList::SetValue(int d)
{
	ReleaseValue();
	Value=new int;
	*((int *)Value)=d;
	RType=_Int;
}
void	ControlRemembererList::SetValue(const QString &d)
{
	ReleaseValue();
	Value=new QString;
	*((QString *)Value)=d;
	RType=_QString;
}
void	ControlRemembererList::SetValue(bool d)
{
	ReleaseValue();
	Value=new bool;
	*((bool *)Value)=d;
	RType=_Bool;
}
void	ControlRemembererList::SetValue(double d)
{
	ReleaseValue();
	Value=new double;
	*((double *)Value)=d;
	RType=_Double;
}
void	ControlRemembererList::SetValue(const QStringList &d)
{
	ReleaseValue();
	Value=new QStringList;
	*((QStringList *)Value)=d;
	RType=_QStringList;
}
void	ControlRemembererList::SetValue(const QDateTime &d)
{
	ReleaseValue();
	Value=new QDateTime;
	*((QDateTime *)Value)=d;
	RType=_QDateTime;
}
void	ControlRemembererList::SetValue(const QByteArray &d)
{
	ReleaseValue();
	Value=new QByteArray;
	*((QByteArray *)Value)=d;
	RType=_QByteArray;
}
void	ControlRemembererList::SetValue(const IntListContainer &d)
{
	ReleaseValue();
	Value=new IntListContainer;
	*((IntListContainer *)Value)=d;
	RType=_QTreeWidget;
}
void	ControlRemembererList::SetValue(const IntList &d)
{
	ReleaseValue();
	Value=new IntList;
	*((IntList *)Value)=d;
	RType=_IntList;
}
void	ControlRemembererList::SetFormName(const QString &FormName)
{
	ReleaseValue();
	Value=new QString;
	*((QString *)Value)=FormName;
	RType=_Form;
}

bool	ControlRemembererList::Save(QIODevice *f)
{
	BYTE	d=(BYTE)RType;
	if(::Save(f,d)==false){
		return false;
	}
	if(::Save(f,ObjectNameList)==false){
		return false;
	}
	if(Children.Save(f)==false){
		return false;
	}
	switch(RType){
		case _Int:
			if(Value==NULL){
				return false;
			}
			return ::Save(f,*((int *)Value));
		case _QString:
			if(Value==NULL){
				return false;
			}
			return ::Save(f,*((QString *)Value));
		case _Bool:
			if(Value==NULL){
				return false;
			}
			return ::Save(f,*((bool *)Value));
		case _Double:
			if(Value==NULL){
				return false;
			}
			return ::Save(f,*((double *)Value));
		case _QStringList:
			if(Value==NULL){
				return false;
			}
			return ::Save(f,*((QStringList *)Value));
		case _QDateTime:
			if(Value==NULL){
				return false;
			}
			return ::Save(f,*((QDateTime *)Value));
		case _QByteArray:
			if(Value==NULL){
				return false;
			}
			return ::Save(f,*((QByteArray *)Value));
		case _QTreeWidget:
			if(Value==NULL){
				return false;
			}
			return ((IntListContainer *)Value)->Save(f);
		case _IntList:
			if(Value==NULL){
				return false;
			}
			return ((IntList *)Value)->Save(f);
		case _Form:
			if(Value==NULL){
				return false;
			}
			return ::Save(f,*((QString *)Value));
	}
	return false;
}
void	ControlRemembererList::ReleaseValue(void)
{
	int	*Vi;
	QString	*Vs;
	bool	*Vb;
	double	*Vd;
	QStringList	*Vl;
	QDateTime	*Vt;
	QByteArray	*Va;
	IntListContainer		*Vm;
	IntList		*Vn;

	if(Value!=NULL){
		switch(RType){
			case _Int:
				Vi=(int *)Value;
				delete	Vi;
				Value=NULL;
				break;
			case _QString:
				Vs=(QString *)Value;
				delete	Vs;
				Value=NULL;
				break;
			case _Bool:
				Vb=(bool *)Value;
				delete	Vb;
				Value=NULL;
				break;
			case _Double:
				Vd=(double *)Value;
				delete	Vd;
				Value=NULL;
				break;
			case _QStringList:
				Vl=(QStringList *)Value;
				delete	Vl;
				Value=NULL;
				break;
			case _QDateTime:
				Vt=(QDateTime *)Value;
				delete	Vt;
				Value=NULL;
				break;
			case _QByteArray:
				Va=(QByteArray *)Value;
				delete	Va;
				Value=NULL;
				break;
			case _QTreeWidget:
				Vm=(IntListContainer *)Value;
				delete	Vm;
				Value=NULL;
				break;
			case _IntList:
				Vn=(IntList *)Value;
				delete	Vn;
				Value=NULL;
				break;
			case _Form:
				Vs=(QString *)Value;
				delete	Vs;
				Value=NULL;
				break;
		}
	}
}
bool	ControlRemembererList::Load(QIODevice *f)
{
	ReleaseValue();

	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	RType=(_RType)d;
	if(::Load(f,ObjectNameList)==false){
		return false;
	}
	if(Children.Load(f)==false){
		return false;
	}

	switch(RType){
		case _Int:
			Value=new int;
			return ::Load(f,*((int *)Value));
		case _QString:
			Value=new QString;
			return ::Load(f,*((QString *)Value));
		case _Bool:
			Value=new bool;
			return ::Load(f,*((bool *)Value));
		case _Double:
			Value=new double;
			return ::Load(f,*((double *)Value));
		case _QStringList:
			Value=new QStringList;
			return ::Load(f,*((QStringList *)Value));
		case _QDateTime:
			Value=new QDateTime;
			return ::Load(f,*((QDateTime *)Value));
		case _QByteArray:
			Value=new QByteArray;
			return ::Load(f,*((QByteArray *)Value));
		case _QTreeWidget:
			Value=new IntListContainer();
			return ((IntListContainer *)Value)->Load(f);
		case _IntList:
			Value=new IntList();
			return ((IntList *)Value)->Load(f);
		case _Form:
			Value=new QString;
			return ::Load(f,*((QString *)Value));
	}
	return false;
}

void	ControlRemembererListContainer::SetValue(QWidget *W)
{
	{
		QSpinBox	*e=dynamic_cast<QSpinBox *>(W);
		if(e!=NULL){
			SetValue(W,e->value());
			return;
		}
	}
	{
		QSlider	*e=dynamic_cast<QSlider *>(W);
		if(e!=NULL){
			SetValue(W,e->value());
			return;
		}
	}
	{
		QDoubleSpinBox	*e=dynamic_cast<QDoubleSpinBox *>(W);
		if(e!=NULL){
			SetValue(W,e->value());
			return;
		}
	}
	{
		QCheckBox	*e=dynamic_cast<QCheckBox *>(W);
		if(e!=NULL){
			SetValue(W,e->isChecked());
			return;
		}
	}
	{
		QRadioButton	*e=dynamic_cast<QRadioButton *>(W);
		if(e!=NULL){
			SetValue(W,e->isChecked());
			return;
		}
	}
	{
		QToolButton	*e=dynamic_cast<QToolButton *>(W);
		if(e!=NULL){
			SetValue(W,e->isChecked());
			return;
		}
	}
	{
		QLineEdit	*e=dynamic_cast<QLineEdit *>(W);
		if(e!=NULL){
			SetValue(W,e->text());
			return;
		}
	}
	{
		QTextEdit	*e=dynamic_cast<QTextEdit *>(W);
		if(e!=NULL){
			SetValue(W,e->document()->toPlainText());
			return;
		}
	}
	{
		QDateTimeEdit	*e=dynamic_cast<QDateTimeEdit *>(W);
		if(e!=NULL){
			SetValue(W,e->dateTime());
			return;
		}
	}
	{
		QTreeWidget	*e=dynamic_cast<QTreeWidget *>(W);
		if(e!=NULL){
			IntListContainer ItemNumber;
			::GetSelectedItems(e, ItemNumber);
			SetValue(W,ItemNumber);
			return;
		}
	}
	{
		QTableWidget	*e=dynamic_cast<QTableWidget *>(W);
		if(e!=NULL){
			SetValue(W,e->currentRow());
			return;
		}
	}
	{
		QComboBox	*e=dynamic_cast<QComboBox *>(W);
		if(e!=NULL){
			SetValue(W,e->currentIndex());
			return;
		}
	}
}
void	ControlRemembererListContainer::GetValue(QWidget *W)
{
	{
		QSpinBox	*e=dynamic_cast<QSpinBox *>(W);
		if(e!=NULL){
			int	Ret;
			if(GetValue(W,Ret)==true){
				e->setValue(Ret);
			}
			return;
		}
	}
	{
		QSlider	*e=dynamic_cast<QSlider *>(W);
		if(e!=NULL){
			int	Ret;
			if(GetValue(W,Ret)==true){
				e->setValue(Ret);
			}
			return;
		}
	}
	{
		QDoubleSpinBox	*e=dynamic_cast<QDoubleSpinBox *>(W);
		if(e!=NULL){
			double	Ret;
			if(GetValue(W,Ret)==true){
				e->setValue(Ret);
			}
			return;
		}
	}
	{
		QCheckBox	*e=dynamic_cast<QCheckBox *>(W);
		if(e!=NULL){
			bool	Ret;
			if(GetValue(W,Ret)==true){
				e->setChecked(Ret);
			}
			return;
		}
	}
	{
		QRadioButton	*e=dynamic_cast<QRadioButton *>(W);
		if(e!=NULL){
			bool	Ret;
			if(GetValue(W,Ret)==true){
				e->setChecked(Ret);
			}
			return;
		}
	}
	{
		QToolButton	*e=dynamic_cast<QToolButton *>(W);
		if(e!=NULL){
			bool	Ret;
			if(GetValue(W,Ret)==true){
				e->setChecked(Ret);
			}
			return;
		}
	}
	{
		QLineEdit	*e=dynamic_cast<QLineEdit *>(W);
		if(e!=NULL){
			QString	Ret;
			if(GetValue(W,Ret)==true){
				e->setText(Ret);
			}
			return;
		}
	}
	{
		QTextEdit	*e=dynamic_cast<QTextEdit *>(W);
		if(e!=NULL){
			QString	Ret;
			if(GetValue(W,Ret)==true){
				e->document()->setPlainText(Ret);
			}
			return;
		}
	}
	{
		QDateTimeEdit	*e=dynamic_cast<QDateTimeEdit *>(W);
		if(e!=NULL){
			QDateTime	Ret;
			if(GetValue(W,Ret)==true){
				e->setDateTime(Ret);
			}
			return;
		}
	}
	{
		QTreeWidget	*e=dynamic_cast<QTreeWidget *>(W);
		if(e!=NULL){
			IntListContainer	Ret;
			if(GetValue(W,Ret)==true){
				::SetSelectedItems(e, Ret);
			}
			return;
		}
	}
	{
		QTableWidget	*e=dynamic_cast<QTableWidget *>(W);
		if(e!=NULL){
			int	Ret;
			if(GetValue(W,Ret)==true){
				if(Ret<e->rowCount()){
					::SetCurrentRow(e,Ret);
				}
			}
			return;
		}
	}
	{
		QComboBox	*e=dynamic_cast<QComboBox *>(W);
		if(e!=NULL){
			int	Ret;
			if(GetValue(W,Ret)==true){
				if(Ret<e->count()){
					e->setCurrentIndex(Ret);
				}
			}
			return;
		}
	}
}


int		ControlRememberer::GetInt(QWidget *W	,int defaultValue)
{
	if(ReEntrant==true){
		return defaultValue;
	}
	ReEntrant=true;
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		int	Ret=Stocker.GetInt(W,defaultValue);
		ReEntrant=false;
		return Ret;
	}
	ReEntrant=false;
	return defaultValue;
}

QString	ControlRememberer::GetString(QWidget *W	,const QString &defaultValue)
{
	if(ReEntrant==true){
		return defaultValue;
	}
	ReEntrant=true;
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		QString	Ret=Stocker.GetString(W,defaultValue);
		ReEntrant=false;
		return Ret;
	}
	ReEntrant=false;
	return defaultValue;
}
bool	ControlRememberer::GetBool(QWidget *W	,bool defaultValue)
{
	if(ReEntrant==true){
		return defaultValue;
	}
	ReEntrant=true;
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		bool	Ret=Stocker.GetBool(W,defaultValue);
		ReEntrant=false;
		return Ret;
	}
	ReEntrant=false;
	return defaultValue;
}
double	ControlRememberer::GetDouble(QWidget *W	,double defaultValue)
{
	if(ReEntrant==true){
		return defaultValue;
	}
	ReEntrant=true;
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		double	Ret=Stocker.GetDouble(W,defaultValue);
		ReEntrant=false;
		return Ret;
	}
	ReEntrant=false;
	return defaultValue;
}
QStringList	ControlRememberer::GetStringList(QWidget *W	,const QStringList &defaultValue)
{
	if(ReEntrant==true){
		return defaultValue;
	}
	ReEntrant=true;
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		QStringList Ret=Stocker.GetStringList(W,defaultValue);
		ReEntrant=false;
		return Ret;
	}
	ReEntrant=false;
	return defaultValue;
}
QDateTime	ControlRememberer::GetDateTime		(QWidget *W,const QDateTime &defaultValue)
{
	if(ReEntrant==true){
		return defaultValue;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		QDateTime Ret=Stocker.GetDateTime(W,defaultValue);
		ReEntrant=false;
		return Ret;
	}
	ReEntrant=false;
	return defaultValue;
}
IntListContainer	ControlRememberer::GetIntListContainer(QTreeWidget *W)
{
	IntListContainer	Ret;
	if(ReEntrant==true){
		return Ret;
	}
	ReEntrant=true;
		
	ControlRemembererListContainer	Stocker;
	if(LoadList(Stocker)==true){
		Stocker.GetValue(W ,Ret);
	}
	ReEntrant=false;
	return Ret;
}

void	ControlRememberer::LoadValue(QSpinBox *W		,int defaultValue)
{
	W->setValue(GetInt(W,defaultValue));
}
void	ControlRememberer::LoadValue(QSlider *W		,int defaultValue)
{
	W->setValue(GetInt(W,defaultValue));
}
void	ControlRememberer::LoadValue(QDoubleSpinBox *W	,double defaultValue)
{
	W->setValue(GetDouble(W,defaultValue));
}
void	ControlRememberer::LoadValue(QCheckBox *W		,bool defaultValue)
{
	W->setChecked(GetBool(W,defaultValue));
}
void	ControlRememberer::LoadValue(QRadioButton *W		,bool defaultValue)
{
	W->setChecked(GetBool(W,defaultValue));
}
void	ControlRememberer::LoadValue(QToolButton *W		,bool defaultValue)
{
	W->setChecked(GetBool(W,defaultValue));
}
void	ControlRememberer::LoadValue(QLineEdit *W		,const QString &defaultValue)
{
	W->setText(GetString(W,defaultValue));
}
void	ControlRememberer::LoadValue(QTextEdit *W		,const QString &defaultValue)
{
	W->setPlainText(GetString(W,defaultValue));
}
void	ControlRememberer::LoadValue(QDateTimeEdit *W	,const QDateTime &defaultValue)
{
	W->setDateTime(GetDateTime(W,defaultValue));
}


bool	ControlRemembererListContainer::Save(QIODevice *f)
{
	int32	N=GetCount();

	if(::Save(f,N)==false)
		return false;
	for(ControlRemembererList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	ControlRemembererListContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		ControlRemembererList	*L=new ControlRemembererList();
		if(L->Load(f)==false){
			return false;
		}
		AppendList(L);
	}
	return true;
}


void	ControlRemembererListContainer::SetValue(QWidget *W ,int d)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Int && IsEqual(c->GetObjectNameList(),L)==true){
			c->SetValue(d);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetObjectNameList(L);
	e->SetValue(d);
	AppendList(e);
}
void	ControlRemembererListContainer::SetValue(QWidget *W ,const QString &d)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QString && IsEqual(c->GetObjectNameList(),L)==true){
			c->SetValue(d);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetObjectNameList(L);
	e->SetValue(d);
	AppendList(e);
}

void	ControlRemembererListContainer::SetValue(QWidget *W ,bool d)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Bool && IsEqual(c->GetObjectNameList(),L)==true){
			c->SetValue(d);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetObjectNameList(L);
	e->SetValue(d);
	AppendList(e);
}

void	ControlRemembererListContainer::SetValue(QWidget *W ,double d)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Double && IsEqual(c->GetObjectNameList(),L)==true){
			c->SetValue(d);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetObjectNameList(L);
	e->SetValue(d);
	AppendList(e);
}
void	ControlRemembererListContainer::SetValue(QWidget *W ,const QStringList &d)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QStringList && IsEqual(c->GetObjectNameList(),L)==true){
			c->SetValue(d);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetObjectNameList(L);
	e->SetValue(d);
	AppendList(e);
}
void	ControlRemembererListContainer::SetValue(QWidget *W ,const QDateTime &d)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QDateTime && IsEqual(c->GetObjectNameList(),L)==true){
			c->SetValue(d);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetObjectNameList(L);
	e->SetValue(d);
	AppendList(e);
}

void	ControlRemembererListContainer::SetValue(QWidget *W ,const IntListContainer &d)
{
	QStringList	L=ControlRememberer::GetObjectNameList(W);
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QTreeWidget && IsEqual(c->GetObjectNameList(),L)==true){
			c->SetValue(d);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetObjectNameList(L);
	e->SetValue(d);
	AppendList(e);
}
void	ControlRememberer::SetValue(QWidget *W ,int d)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	QStringList	L=GetObjectNameList(W);
	LoadList(Stocker);
	Stocker.SetValue(W ,d);
	SaveList(Stocker);
	ReEntrant=false;
}

void	ControlRememberer::SetValue(QWidget *W ,const QString &d)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	QStringList	L=GetObjectNameList(W);
	LoadList(Stocker);
	Stocker.SetValue(W ,d);
	SaveList(Stocker);
	ReEntrant=false;
}

void	ControlRememberer::SetValue(QWidget *W ,bool d)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	QStringList	L=GetObjectNameList(W);
	LoadList(Stocker);
	Stocker.SetValue(W ,d);
	SaveList(Stocker);
	ReEntrant=false;
}

void	ControlRememberer::SetValue(QWidget *W ,double d)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	QStringList	L=GetObjectNameList(W);
	LoadList(Stocker);
	Stocker.SetValue(W ,d);
	SaveList(Stocker);
	ReEntrant=false;
}
void	ControlRememberer::SetValue(QWidget *W ,const QStringList &d)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	QStringList	L=GetObjectNameList(W);
	LoadList(Stocker);
	Stocker.SetValue(W ,d);
	SaveList(Stocker);
	ReEntrant=false;
}
void	ControlRememberer::SetValue(QWidget *W ,const QDateTime &d)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	QStringList	L=GetObjectNameList(W);
	LoadList(Stocker);
	Stocker.SetValue(W ,d);
	SaveList(Stocker);
	ReEntrant=false;
}
void	ControlRememberer::SetValue(QTreeWidget *W ,const IntListContainer &d)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	QStringList	L=GetObjectNameList(W);
	LoadList(Stocker);
	Stocker.SetValue(W ,d);
	SaveList(Stocker);
	ReEntrant=false;
}

int		ControlRememberer::SetValue(QSpinBox *W)
{
	int	Ret=W->value();
	SetValue((QWidget *)W,Ret);
	return Ret;
}
int		ControlRememberer::SetValue(QSlider *W)
{
	int	Ret=W->value();
	SetValue((QWidget *)W,Ret);
	return Ret;
}
double	ControlRememberer::SetValue(QDoubleSpinBox *W)
{
	double	Ret=W->value();
	SetValue((QWidget *)W,Ret);
	return Ret;
}
bool	ControlRememberer::SetValue(QCheckBox *W)
{
	bool	Ret=W->isChecked();
	SetValue((QWidget *)W,Ret);
	return Ret;
}
bool	ControlRememberer::SetValue(QRadioButton *W)
{
	bool	Ret=W->isChecked();
	SetValue((QWidget *)W,Ret);
	return Ret;
}
bool	ControlRememberer::SetValue(QToolButton *W)
{
	bool	Ret=W->isChecked();
	SetValue((QWidget *)W,Ret);
	return Ret;
}
QString	ControlRememberer::SetValue(QLineEdit *W)
{
	QString	Ret=W->text();
	SetValue((QWidget *)W,Ret);
	return Ret;
}

QString	ControlRememberer::SetValue(QTextEdit *W)
{
	QString	Ret=W->toPlainText();
	SetValue((QWidget *)W,Ret);
	return Ret;
}
QDateTime	ControlRememberer::SetValue(QDateTimeEdit *W)
{
	QDateTime	Ret=W->dateTime();
	SetValue((QWidget *)W,Ret);
	return Ret;
}

QString	ControlRememberer::FileName="Rememberer.dat";
bool	ControlRememberer::ReEntrant=false;

void	ControlRememberer::SetDefaultFileName(const QString &filename)
{
	FileName=filename;
}


bool	ControlRememberer::LoadList(ControlRemembererListContainer &Stocker)
{
	Stocker.RemoveAll();
	QFile	F(QDir::tempPath ()+::GetSeparator()+FileName);
	if(F.open(QIODevice::ReadOnly)==true){
		if(Stocker.Load(&F)==false){
			return false;
		}

	}
	return true;
}
bool	ControlRememberer::SaveList(ControlRemembererListContainer &Stocker)
{
	QFile	F(QDir::tempPath ()+::GetSeparator()+FileName);
	if(F.open(QIODevice::WriteOnly)==true){
		if(Stocker.Save(&F)==false){
			return false;
		}
	}
	return true;
}

QStringList	ControlRememberer::GetObjectNameList(QWidget *W)
{
	QStringList	L;
	while(W!=NULL){
		QString	a=W->objectName();
		if(a!=""){
			L.append(a);
		}
		W=W->parentWidget();
	}
	return L;
}
QStringList	ControlRememberer::GetObjectNameList(QObject *W)
{
	QStringList	L;
	while(W!=NULL){
		QString	a=W->objectName();
		if(a!=""){
			L.append(a);
		}
		W=W->parent();
	}
	return L;
}



int		ControlRemembererListContainer::GetInt			(const QString &VariableName,int defaultValue)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Int && c->GetRecogName()==VariableName){
			return c->GetInt();
		}
	}
	return defaultValue;
}
IntList		ControlRemembererListContainer::GetIntList			(const QString &VariableName,const IntList &defaultValue)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_IntList && c->GetRecogName()==VariableName){
			return c->GetIntList();
		}
	}
	return defaultValue;
}
double		ControlRemembererListContainer::GetDouble		(const QString &VariableName,double defaultValue)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Double && c->GetRecogName()==VariableName){
			return c->GetDouble();
		}
	}
	return defaultValue;
}
QString		ControlRemembererListContainer::GetString		(const QString &VariableName,const QString &defaultValue)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QString && c->GetRecogName()==VariableName){
			return c->GetString();
		}
	}
	return defaultValue;
}
bool		ControlRemembererListContainer::GetBool			(const QString &VariableName,bool defaultValue)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Bool && c->GetRecogName()==VariableName){
			return c->GetBool();
		}
	}
	return defaultValue;
}
QStringList	ControlRemembererListContainer::GetStringList	(const QString &VariableName,const QStringList &defaultValue)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QStringList && c->GetRecogName()==VariableName){
			return c->GetStringList();
		}
	}
	return defaultValue;
}
QDateTime	ControlRemembererListContainer::GetDateTime		(const QString &VariableName,const QDateTime &defaultValue)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QDateTime && c->GetRecogName()==VariableName){
			return c->GetDateTime();
		}
	}
	return defaultValue;
}
QByteArray	ControlRemembererListContainer::GetByteArray	(const QString &VariableName)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QByteArray && c->GetRecogName()==VariableName){
			return c->GetByteArray();
		}
	}
	return QByteArray();
}



int			ControlRememberer::GetInt			(const QString &VariableName,int defaultValue)
{
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		return Stocker.GetInt(VariableName,defaultValue);
	}
	return defaultValue;
}
IntList			ControlRememberer::GetIntList	(const QString &VariableName,const IntList &defaultValue)
{
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		return Stocker.GetIntList(VariableName,defaultValue);
	}
	return defaultValue;
}
double		ControlRememberer::GetDouble		(const QString &VariableName,double defaultValue)
{
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		return Stocker.GetDouble(VariableName,defaultValue);
	}
	return defaultValue;
}
QString		ControlRememberer::GetString		(const QString &VariableName,const QString &defaultValue)
{
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		return Stocker.GetString(VariableName,defaultValue);
	}
	return defaultValue;
}
bool		ControlRememberer::GetBool			(const QString &VariableName,bool defaultValue)
{
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		return Stocker.GetBool(VariableName,defaultValue);
	}
	return defaultValue;
}
QStringList	ControlRememberer::GetStringList	(const QString &VariableName,const QStringList &defaultValue)
{
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		return Stocker.GetStringList(VariableName,defaultValue);
	}
	return defaultValue;
}
QDateTime	ControlRememberer::GetDateTime		(const QString &VariableName,const QDateTime &defaultValue)
{
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		return Stocker.GetDateTime(VariableName,defaultValue);
	}
	return defaultValue;
}
QByteArray	ControlRememberer::GetByteArray	(const QString &VariableName)
{
	ControlRemembererListContainer	Stocker;

	if(LoadList(Stocker)==true){
		return Stocker.GetByteArray(VariableName);
	}
	return QByteArray();
}
void	ControlRemembererListContainer::SetValue(const QString &VariableName,int Value)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Int && c->GetRecogName()==VariableName){
			c->SetValue(Value);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetRecogName(VariableName);
	e->SetValue(Value);
	AppendList(e);
}
void	ControlRemembererListContainer::SetValue(const QString &VariableName,const IntList &Value)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_IntList && c->GetRecogName()==VariableName){
			c->SetValue(Value);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetRecogName(VariableName);
	e->SetValue(Value);
	AppendList(e);
}
void	ControlRemembererListContainer::SetValue(const QString &VariableName,double Value)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Double && c->GetRecogName()==VariableName){
			c->SetValue(Value);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetRecogName(VariableName);
	e->SetValue(Value);
	AppendList(e);
}

void	ControlRemembererListContainer::SetValue(const QString &VariableName,const QString &Value)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QString && c->GetRecogName()==VariableName){
			c->SetValue(Value);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetRecogName(VariableName);
	e->SetValue(Value);
	AppendList(e);
}
void	ControlRemembererListContainer::SetValue(const QString &VariableName,bool Value)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_Bool && c->GetRecogName()==VariableName){
			c->SetValue(Value);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetRecogName(VariableName);
	e->SetValue(Value);
	AppendList(e);
}
void	ControlRemembererListContainer::SetValue(const QString &VariableName,const QStringList &Value)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QStringList && c->GetRecogName()==VariableName){
			c->SetValue(Value);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetRecogName(VariableName);
	e->SetValue(Value);
	AppendList(e);
}
void	ControlRemembererListContainer::SetValue(const QString &VariableName,const QDateTime &Value)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QDateTime && c->GetRecogName()==VariableName){
			c->SetValue(Value);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetRecogName(VariableName);
	e->SetValue(Value);
	AppendList(e);
}
void	ControlRemembererListContainer::SetValue(const QString &VariableName,const QByteArray &Value)
{
	for(ControlRemembererList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetRType()==ControlRemembererList::_QByteArray && c->GetRecogName()==VariableName){
			c->SetValue(Value);
			return;
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetRecogName(VariableName);
	e->SetValue(Value);
	AppendList(e);
}

void	ControlRememberer::SetValue(const QString &VariableName,int Value)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	LoadList(Stocker);
	Stocker.SetValue(VariableName,Value);
	SaveList(Stocker);
	ReEntrant=false;
}
void	ControlRememberer::SetValue(const QString &VariableName,const IntList &Value)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	LoadList(Stocker);
	Stocker.SetValue(VariableName,Value);
	SaveList(Stocker);
	ReEntrant=false;
}

void	ControlRememberer::SetValue(const QString &VariableName,double Value)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	LoadList(Stocker);
	Stocker.SetValue(VariableName,Value);
	SaveList(Stocker);
	ReEntrant=false;
}

void	ControlRememberer::SetValue(const QString &VariableName,const QString &Value)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	LoadList(Stocker);
	Stocker.SetValue(VariableName,Value);
	SaveList(Stocker);
	ReEntrant=false;
}
void	ControlRememberer::SetValue(const QString &VariableName,bool Value)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	LoadList(Stocker);
	Stocker.SetValue(VariableName,Value);
	SaveList(Stocker);
	ReEntrant=false;
}
void	ControlRememberer::SetValue(const QString &VariableName,const QStringList &Value)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	LoadList(Stocker);
	Stocker.SetValue(VariableName,Value);
	SaveList(Stocker);
	ReEntrant=false;
}
void	ControlRememberer::SetValue(const QString &VariableName,const QDateTime &Value)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	LoadList(Stocker);
	Stocker.SetValue(VariableName,Value);
	SaveList(Stocker);
	ReEntrant=false;
}
void	ControlRememberer::SetValue(const QString &VariableName,const QByteArray &Value)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	ControlRemembererListContainer	Stocker;

	LoadList(Stocker);
	Stocker.SetValue(VariableName,Value);
	SaveList(Stocker);
	ReEntrant=false;
}

void	ControlRememberer::SaveForm(QWidget *Form)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	QStringList	PStrList=GetObjectNameList(Form);
	QString	FormName=PStrList.join(/**/"\\");

	ControlRemembererListContainer	Stocker;
	if(LoadList(Stocker)==true){
		for(ControlRemembererList *c=Stocker.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetRType()==ControlRemembererList::_Form && c->GetRecogName()==FormName){
				SaveFormChildren(Form,c);
				SaveList(Stocker);
				ReEntrant=false;
				return;
			}
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetRecogName(FormName);
	e->SetFormName(FormName);
	SaveFormChildren(Form,e);
	Stocker.AppendList(e);
	SaveList(Stocker);
	ReEntrant=false;
}

void	ControlRememberer::SaveForm(int ID,QWidget *Form)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	QStringList	PStrList=GetObjectNameList(Form);
	QString	FormName=PStrList.join(/**/"\\")+QString(/**/"@")+QString::number(ID);

	ControlRemembererListContainer	Stocker;
	if(LoadList(Stocker)==true){
		for(ControlRemembererList *c=Stocker.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetRType()==ControlRemembererList::_Form && c->GetRecogName()==FormName){
				SaveFormChildren(Form,c);
				SaveList(Stocker);
				ReEntrant=false;
				return;
			}
		}
	}
	ControlRemembererList	*e=new ControlRemembererList();
	e->SetRecogName(FormName);
	e->SetFormName(FormName);
	SaveFormChildren(Form,e);
	Stocker.AppendList(e);
	SaveList(Stocker);
	ReEntrant=false;
}

void	ControlRememberer::SaveFormChildren(QObject *Form,ControlRemembererList *p)
{
	const	QObjectList &Children=Form->children();
	int	N=Children.count();
	for(int i=0;i<N;i++){
		QObject	*Obj=Children[i];
		QWidget	*W=dynamic_cast<QWidget	*>(Obj);
		if(W!=NULL){
			p->GetChildren().SetValue(W);
		}
		SaveFormChildren(Obj,p);
	}
}

void	ControlRememberer::RestoreForm(QWidget *Form)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	QStringList	PStrList=GetObjectNameList(Form);
	QString	FormName=PStrList.join(/**/"\\");

	ControlRemembererListContainer	Stocker;
	if(LoadList(Stocker)==true){
		for(ControlRemembererList *c=Stocker.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetRType()==ControlRemembererList::_Form && c->GetRecogName()==FormName){
				LoadFormChildren(Form,c);
				ReEntrant=false;
				return;
			}
		}
	}
	ReEntrant=false;
}

void	ControlRememberer::RestoreForm(int ID,QWidget *Form)
{
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	
	QStringList	PStrList=GetObjectNameList(Form);
	QString	FormName=PStrList.join(/**/"\\")+QString(/**/"@")+QString::number(ID);

	ControlRemembererListContainer	Stocker;
	if(LoadList(Stocker)==true){
		for(ControlRemembererList *c=Stocker.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetRType()==ControlRemembererList::_Form && c->GetRecogName()==FormName){
				LoadFormChildren(Form,c);
				ReEntrant=false;
				return;
			}
		}
	}
	ReEntrant=false;
}
void	ControlRememberer::LoadFormChildren(QObject *Form,ControlRemembererList *p)
{
	const	QObjectList &Children=Form->children();
	int	N=Children.count();
	for(int i=0;i<N;i++){
		QObject	*Obj=Children[i];
		QWidget	*W=dynamic_cast<QWidget	*>(Obj);
		if(W!=NULL){
			p->GetChildren().GetValue(W);
		}
		LoadFormChildren(Obj,p);
	}
}
