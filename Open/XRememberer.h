/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XRememberer.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XREMEMBERER_H)
#define	XREMEMBERER_H

#include <QString>
#include <QStringList>
#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QToolButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QTreeWidget>
#include <QTableWidget>
#include <QComboBox>
#include "NList.h"
#include "XIntClass.h"
#include "XTypeDef.h"

class	ControlRemembererList;


class ControlRemembererListContainer : public NPListPack<ControlRemembererList>
{
public:
	ControlRemembererListContainer(){}
	~ControlRemembererListContainer(){}

	void	SetValue(const QString &VariableName,int d);
	void	SetValue(const QString &VariableName,const IntList &d);
	void	SetValue(const QString &VariableName,const QString &d);
	void	SetValue(const QString &VariableName,bool d);
	void	SetValue(const QString &VariableName,double d);
	void	SetValue(const QString &VariableName,const QStringList &d);
	void	SetValue(const QString &VariableName,const QDateTime &d);
	void	SetValue(const QString &VariableName,const QByteArray &d);

	void	SetValue(QWidget *W ,int d);
	void	SetValue(QWidget *W ,const QString &d);
	void	SetValue(QWidget *W ,bool d);
	void	SetValue(QWidget *W ,double d);
	void	SetValue(QWidget *W ,const QStringList &d);
	void	SetValue(QWidget *W ,const QDateTime &d);
	void	SetValue(QWidget *W ,const IntListContainer &d);
	
	void	SetValue(QWidget *W);
	void	GetValue(QWidget *W);

	int			GetInt			(QWidget *W	,int defaultValue=0);
	double		GetDouble		(QWidget *W	,double defaultValue=0.0);
	QString		GetString		(QWidget *W ,const QString &defaultValue=/**/"");
	bool		GetBool			(QWidget *W	,bool defaultValue=true);
	QStringList	GetStringList	(QWidget *W ,const QStringList &defaultValue=QStringList());
	QDateTime	GetDateTime		(QWidget *W ,const QDateTime &defaultValue=QDateTime::currentDateTime());

	bool	GetValue(QWidget *W	,int		&Ret);
	bool	GetValue(QWidget *W	,double		&Ret);
	bool	GetValue(QWidget *W ,QString	&Ret);
	bool	GetValue(QWidget *W	,bool		&Ret);
	bool	GetValue(QWidget *W ,QStringList&Ret);
	bool	GetValue(QWidget *W ,QDateTime	&Ret);
	bool	GetValue(QWidget *W ,IntListContainer	&Ret);	//QTreeWidget

	int			GetInt			(const QString &VariableName,int defaultValue=0);
	IntList		GetIntList		(const QString &VariableName,const IntList &defaultValue=IntList());
	double		GetDouble		(const QString &VariableName,double defaultValue=0.0);
	QString		GetString		(const QString &VariableName,const QString &defaultValue=/**/"");
	bool		GetBool			(const QString &VariableName,bool defaultValue=true);
	QStringList	GetStringList	(const QString &VariableName,const QStringList &defaultValue=QStringList());
	QDateTime	GetDateTime		(const QString &VariableName,const QDateTime &defaultValue=QDateTime::currentDateTime());
	QByteArray	GetByteArray	(const QString &VariableName);

	bool		Save(QIODevice *f);
	bool		Load(QIODevice *f);
};

class	ControlRemembererList : public NPList<ControlRemembererList>
{
	void	*Value;
public:
	enum _RType{
		_Int			=1
		,_QString		=2
		,_Bool			=3
		,_Double		=4
		,_QStringList	=5
		,_QDateTime		=6
		,_QByteArray	=7
		,_QTreeWidget	=9
		,_IntList		=10
		,_Form			=20
	};
private:
	_RType	RType;
	QStringList	ObjectNameList;
	ControlRemembererListContainer	Children;

public:
	ControlRemembererList(void);
	~ControlRemembererList(void);

	void	ReleaseValue(void);

	_RType		GetRType(void)							{	return RType;			}
	QStringList	&GetObjectNameList(void)				{	return ObjectNameList;	}
	void		SetObjectNameList(const QStringList &L)	{	ObjectNameList=L;		}
	QString		GetRecogName(void)						{	return ObjectNameList[0];	}
	void		SetRecogName(const QString &name);

	int			GetInt(void);
	QString		GetString(void);
	bool		GetBool(void);
	double		GetDouble(void);
	QStringList	GetStringList(void);
	QDateTime	GetDateTime(void);
	QByteArray	GetByteArray(void);
	IntListContainer	GetTreeWidget(void);
	IntList		GetIntList(void);

	void		SetValue(int d);
	void		SetValue(const QString &d);
	void		SetValue(bool d);
	void		SetValue(double d);
	void		SetValue(const QStringList &d);
	void		SetValue(const QDateTime &d);
	void		SetValue(const QByteArray &d);
	void		SetValue(const IntListContainer &d);
	void		SetFormName(const QString &FormName);
	void		SetValue(const IntList &d);

	bool		Save(QIODevice *f);
	bool		Load(QIODevice *f);

	ControlRemembererListContainer	&GetChildren(void){		return Children;	}
	void		AppendChildren(ControlRemembererList *Child);
};


class	ControlRememberer
{
	friend	class ControlRemembererListContainer;

	static	QString	FileName;
	static	bool	ReEntrant;
public:
	ControlRememberer(void){}

	static	int			GetInt			(QWidget *W	,int defaultValue=0);
	static	double		GetDouble		(QWidget *W	,double defaultValue=0.0);
	static	QString		GetString		(QWidget *W ,const QString &defaultValue=/**/"");
	static	bool		GetBool			(QWidget *W	,bool defaultValue=true);
	static	QStringList	GetStringList	(QWidget *W ,const QStringList &defaultValue=QStringList());
	static	QDateTime	GetDateTime		(QWidget *W ,const QDateTime &defaultValue=QDateTime::currentDateTime());
	static	IntListContainer	GetIntListContainer(QTreeWidget *W);

	static	void	LoadValue(QSpinBox *W		,int defaultValue);
	static	void	LoadValue(QSlider *W		,int defaultValue);
	static	void	LoadValue(QDoubleSpinBox *W	,double defaultValue);
	static	void	LoadValue(QCheckBox *W		,bool defaultValue);
	static	void	LoadValue(QRadioButton *W	,bool defaultValue);
	static	void	LoadValue(QToolButton *W	,bool defaultValue);
	static	void	LoadValue(QLineEdit *W		,const QString &defaultValue);
	static	void	LoadValue(QTextEdit *W		,const QString &defaultValue);
	static	void	LoadValue(QDateTimeEdit *W	,const QDateTime &defaultValue);

	static	void	SetValue(QWidget *W ,int d);
	static	void	SetValue(QWidget *W ,const QString &d);
	static	void	SetValue(QWidget *W ,bool d);
	static	void	SetValue(QWidget *W ,double d);
	static	void	SetValue(QWidget *W ,const QStringList &d);
	static	void	SetValue(QWidget *W ,const QDateTime &d);
	static	void	SetValue(QTreeWidget *W ,const IntListContainer &d);

	static	int			SetValue(QSpinBox *W);
	static	int			SetValue(QSlider *W);
	static	double		SetValue(QDoubleSpinBox *W);
	static	bool		SetValue(QCheckBox *W);
	static	bool		SetValue(QRadioButton *W);
	static	bool		SetValue(QToolButton *W);
	static	QString		SetValue(QLineEdit *W);
	static	QString		SetValue(QTextEdit *W);
	static	QDateTime	SetValue(QDateTimeEdit *W);

	static	int			GetInt			(const QString &VariableName,int defaultValue=0);
	static	IntList		GetIntList		(const QString &VariableName,const IntList &defaultValue=IntList());
	static	double		GetDouble		(const QString &VariableName,double defaultValue=0.0);
	static	QString		GetString		(const QString &VariableName,const QString &defaultValue=/**/"");
	static	bool		GetBool			(const QString &VariableName,bool defaultValue=true);
	static	QStringList	GetStringList	(const QString &VariableName,const QStringList &defaultValue=QStringList());
	static	QDateTime	GetDateTime		(const QString &VariableName,const QDateTime &defaultValue=QDateTime::currentDateTime());
	static	QByteArray	GetByteArray	(const QString &VariableName);

	static	void	SetValue(const QString &VariableName,int Value);
	static	void	SetValue(const QString &VariableName,const IntList &Value);
	static	void	SetValue(const QString &VariableName,double Value);
	static	void	SetValue(const QString &VariableName,const QString &Value);
	static	void	SetValue(const QString &VariableName,bool Value);
	static	void	SetValue(const QString &VariableName,const QStringList &Value);
	static	void	SetValue(const QString &VariableName,const QDateTime &Value);
	static	void	SetValue(const QString &VariableName,const QByteArray &Value);

	static	void	SetDefaultFileName(const QString &filename);

	static	void	SaveForm(QWidget *Form);
	static	void	RestoreForm(QWidget *Form);
	static	void	SaveForm(int ID,QWidget *Form);
	static	void	RestoreForm(int ID,QWidget *Form);
private:
	static	QStringList	GetObjectNameList(QWidget *W);
	static	QStringList	GetObjectNameList(QObject *W);
	static	bool	LoadList(ControlRemembererListContainer &Stocker);
	static	bool	SaveList(ControlRemembererListContainer &Stocker);
	static	void	SaveFormChildren(QObject *Form,ControlRemembererList *p);
	static	void	LoadFormChildren(QObject *Form,ControlRemembererList *p);
};

#endif