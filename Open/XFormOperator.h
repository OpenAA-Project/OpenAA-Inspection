/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XFormOperator.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XFORMOPERATOR_H)
#define	XFORMOPERATOR_H

#include<QWidget>
#include<QString>
#include "XTypeDef.h"

class	FormOperator
{
	QWidget	*MainForm;

public:
	FormOperator(QWidget *_MainForm):MainForm(_MainForm){}

	bool	ButtonPush	(const QString &FormName ,const QString &ControlName);
	bool	ButtonDown	(const QString &FormName ,const QString &ControlName);
	bool	ButtonUp	(const QString &FormName ,const QString &ControlName);

	bool	CheckboxChecked		(const QString &FormName ,const QString &ControlName);
	bool	CheckboxUnchecked	(const QString &FormName ,const QString &ControlName);
	bool	CheckboxToggle		(const QString &FormName ,const QString &ControlName);

	bool	TableSelect			(const QString &FormName ,const QString &ControlName,int row ,int column);
	bool	TableDoubleClick	(const QString &FormName ,const QString &ControlName,int row ,int column);
//	bool	TableSearchSelect(QString FormName ,QString ControlName,int column,QString SearchName);

	bool	InputEdit		(const QString &FormName ,const QString &ControlName ,const QString &Data);
	bool	InputValue		(const QString &FormName ,const QString &ControlName ,int value);

	bool	ExistForm		(const QString &FormName);

	bool	SetVisible		(const QString &FormName ,const QString &ControlName);
	bool	SetInvisible	(const QString &FormName ,const QString &ControlName);

	bool	SetEnabled		(const QString &FormName ,const QString &ControlName);
	bool	SetDisabled		(const QString &FormName ,const QString &ControlName);

	bool	TableItemSearchSelect(const QString &FormName ,const QString &ControlName
									,int column,const QString &SearchStr);

protected:
	QWidget	*SearchWidget	(const QString &FormName ,const QString &ControlName);
	QWidget	*SearchForm		(const QString &FormName);
};

#endif