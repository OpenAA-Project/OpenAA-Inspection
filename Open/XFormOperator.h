/*
 * Copyright (C) 2023
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