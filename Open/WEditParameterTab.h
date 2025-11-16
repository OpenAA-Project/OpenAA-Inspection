/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\WEditParameterTab.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef WEDITPARAMETERTAB_H
#define WEDITPARAMETERTAB_H

#include <QtGui>
#include "XParamGlobal.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTabWidget>
#include <QByteArray>
#include <QSpinBox>
#include "mtPushButtonColored.h"

class	ParamFilePathButton;
class	ParamColorLogicButton;
class	mtNormalPushed;
class	mtByteArrayPushed;

class WEditParameterTab : public QTabWidget
{
	friend	class	ParamFilePathButton;
	friend	class	ParamColorLogicButton;
	friend	class	mtNormalPushed;
	friend	class	mtByteArrayPushed;
    Q_OBJECT

	int EnableCondition;
public:
    explicit	WEditParameterTab(ParamBase *pbase,int EnableCondition ,QWidget *parent);
    ~WEditParameterTab();

	void	Initial(int EnableCondition ,int MaxRowCount);
	void	Set(ParamBase *pbase,int EnableCondition);
	void	LoadFromWindow(void);
	void	ShowToWindow(void);

	QString	GetDataText(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

protected:
	virtual	void closeEvent ( QCloseEvent * event )	override;
	virtual	void resizeEvent(QResizeEvent *e)		override;
signals:
	void	SignalClose();

private:
	//--------------------------------------------------------
	class	EditParamLine : public NPList<EditParamLine>
	{
	public:
		QLabel		hLabel;
		ParamBase::ParamStruct	*DPoint;
		QSpinBox	*hSpinB;
		QLineEdit	*hEdit;
		QCheckBox	*hCheckBox;
		QComboBox	*hQComboBox;
		QLineEdit	*hPathFileEdit;
		ParamFilePathButton		*FilePathButton;
		mtPushButtonColored		*hColorButton;
		ParamColorLogicButton	*hColorLogicButton;
		mtNormalPushed			*hStringListButton;
		mtByteArrayPushed		*hByteArrayButton;

		int			YNumb;

		EditParamLine(void);
		~EditParamLine(void);
		void	SetYNumb(int Width,int ynumb);
		void	SetParent(QWidget *w);
	};

	//--------------------------------------------------------
	class	ParametersInTab : public NPList<ParametersInTab>
	{
	public:
		NPListPack<EditParamLine>	ParamData;
		QString						TabName;

		ParametersInTab(void){}
		~ParametersInTab(void);
	};

	//--------------------------------------------------------
	ParamBase						*PBase;
	NPListPack<ParametersInTab>		ParametersInTabData;

public:
	ParamBase						*GetParamBase(void){	return PBase;	}

private slots:
	void	FileButtonClicked		(WEditParameterTab::EditParamLine *Src);
	void	PathButtonClicked		(WEditParameterTab::EditParamLine *Src);
	void	ColorLogicButtonClicked	(WEditParameterTab::EditParamLine *Src);
	void	StringListButtonClicked	(WEditParameterTab::EditParamLine *Src);
	void	ByteArrayButtonClicked	(WEditParameterTab::EditParamLine *Src);
};
class	ParamFilePathButton : public QPushButton
{
    Q_OBJECT
public:
	WEditParameterTab::EditParamLine	*Source;

	explicit	ParamFilePathButton(WEditParameterTab::EditParamLine *src ,QWidget *parent=0);
signals:
	void	ClickedButton(WEditParameterTab::EditParamLine *Src);
private slots:
	void	SlotClicked();
};

class	ParamColorLogicButton : public QPushButton
{
    Q_OBJECT
public:
	WEditParameterTab::EditParamLine	*Source;

	explicit	ParamColorLogicButton(WEditParameterTab::EditParamLine *src ,QWidget *parent=0);
signals:
	void	ClickedButton(WEditParameterTab::EditParamLine *Src);
private slots:
	void	SlotClicked();
};

class	mtNormalPushed : public QPushButton
{
	Q_OBJECT
	WEditParameterTab::EditParamLine	*Line;
	QStringList		Str;
public:
	explicit	mtNormalPushed(WEditParameterTab::EditParamLine *Line ,QWidget *parent);

	void	SetStringList(const QStringList &s)	{	Str=s;		}
	QStringList	GetStringList(void)				{	return Str;	}

signals:
	void	ClickedButton(WEditParameterTab::EditParamLine *k);

private slots:
	void	SlotClicked();
};

class	mtByteArrayPushed : public QPushButton
{
	Q_OBJECT
	WEditParameterTab::EditParamLine	*Line;
	QByteArray		BArray;
public:
	explicit	mtByteArrayPushed(WEditParameterTab::EditParamLine *Line ,QWidget *parent);

	void		SetByteArray(const QByteArray &a)	{	BArray=a;	}
	QByteArray	GetByteArray(void)	{	return BArray;	}
signals:
	void	ClickedButton(WEditParameterTab::EditParamLine *k);

private slots:
	void	SlotClicked();
};

#endif