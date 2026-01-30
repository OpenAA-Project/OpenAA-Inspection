/*
 * Copyright (C) 2024
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