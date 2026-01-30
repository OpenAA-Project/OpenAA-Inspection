/*
 * Copyright (C) 2026
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
class	LayersBase;
class	ControlRememberer;


class ControlRemembererListContainer : public NPListPack<ControlRemembererList>
{
	ControlRememberer	*Rememberer;
public:
	ControlRemembererListContainer(ControlRememberer *rememberer):Rememberer(rememberer){}
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
	ControlRemembererList(ControlRememberer *rememberer);
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

	LayersBase	*Base;

	static	QString	FileName;
	static	bool	ReEntrant;
public:
	ControlRememberer(LayersBase *base):Base(base){}

	int			GetInt			(QWidget *W	,int defaultValue=0);
	double		GetDouble		(QWidget *W	,double defaultValue=0.0);
	QString		GetString		(QWidget *W ,const QString &defaultValue=/**/"");
	bool		GetBool			(QWidget *W	,bool defaultValue=true);
	QStringList	GetStringList	(QWidget *W ,const QStringList &defaultValue=QStringList());
	QDateTime	GetDateTime		(QWidget *W ,const QDateTime &defaultValue=QDateTime::currentDateTime());
	IntListContainer	GetIntListContainer(QTreeWidget *W);

	void	LoadValue(QSpinBox *W		,int defaultValue);
	void	LoadValue(QSlider *W		,int defaultValue);
	void	LoadValue(QDoubleSpinBox *W	,double defaultValue);
	void	LoadValue(QCheckBox *W		,bool defaultValue);
	void	LoadValue(QRadioButton *W	,bool defaultValue);
	void	LoadValue(QToolButton *W	,bool defaultValue);
	void	LoadValue(QLineEdit *W		,const QString &defaultValue);
	void	LoadValue(QTextEdit *W		,const QString &defaultValue);
	void	LoadValue(QDateTimeEdit *W	,const QDateTime &defaultValue);

	void	SetValue(QWidget *W ,int d);
	void	SetValue(QWidget *W ,const QString &d);
	void	SetValue(QWidget *W ,bool d);
	void	SetValue(QWidget *W ,double d);
	void	SetValue(QWidget *W ,const QStringList &d);
	void	SetValue(QWidget *W ,const QDateTime &d);
	void	SetValue(QTreeWidget *W ,const IntListContainer &d);

	int			SetValue(QSpinBox *W);
	int			SetValue(QSlider *W);
	double		SetValue(QDoubleSpinBox *W);
	bool		SetValue(QCheckBox *W);
	bool		SetValue(QRadioButton *W);
	bool		SetValue(QToolButton *W);
	QString		SetValue(QLineEdit *W);
	QString		SetValue(QTextEdit *W);
	QDateTime	SetValue(QDateTimeEdit *W);

	int			GetInt			(const QString &VariableName,int defaultValue=0);
	IntList		GetIntList		(const QString &VariableName,const IntList &defaultValue=IntList());
	double		GetDouble		(const QString &VariableName,double defaultValue=0.0);
	QString		GetString		(const QString &VariableName,const QString &defaultValue=/**/"");
	bool		GetBool			(const QString &VariableName,bool defaultValue=true);
	QStringList	GetStringList	(const QString &VariableName,const QStringList &defaultValue=QStringList());
	QDateTime	GetDateTime		(const QString &VariableName,const QDateTime &defaultValue=QDateTime::currentDateTime());
	QByteArray	GetByteArray	(const QString &VariableName);

	void	SetValue(const QString &VariableName,int Value);
	void	SetValue(const QString &VariableName,const IntList &Value);
	void	SetValue(const QString &VariableName,double Value);
	void	SetValue(const QString &VariableName,const QString &Value);
	void	SetValue(const QString &VariableName,bool Value);
	void	SetValue(const QString &VariableName,const QStringList &Value);
	void	SetValue(const QString &VariableName,const QDateTime &Value);
	void	SetValue(const QString &VariableName,const QByteArray &Value);

	void	SetRemembererDefaultFileName(const QString &filename);

	void	SaveForm	(QWidget *Form);
	void	RestoreForm	(QWidget *Form);
	void	SaveForm	(int ID,QWidget *Form);
	void	RestoreForm	(int ID,QWidget *Form);
private:
	QStringList	GetObjectNameList(QWidget *W);
	QStringList	GetObjectNameList(QObject *W);
	bool	LoadList	(ControlRemembererListContainer &Stocker);
	bool	SaveList	(ControlRemembererListContainer &Stocker);
	void	SaveFormChildren(QObject *Form,ControlRemembererList *p);
	void	LoadFormChildren(QObject *Form,ControlRemembererList *p);

protected:
	QString	GetRemembererFileName(void);
};

#endif