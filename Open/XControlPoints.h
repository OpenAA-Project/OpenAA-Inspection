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

#pragma once

#include <QString>
#include <QIODevice>
#include <QByteArray>
#include "NListComp.h"

//========================================================================================
class XYPointWithName : public NPListSaveLoad<XYPointWithName>
{
public:
	int	X,Y;
	QString	Name;

	XYPointWithName(void){	X=Y=0;	}
	XYPointWithName(const XYPointWithName &src);
	XYPointWithName(int x ,int y,const QString &name);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	XYPointWithName	&operator=(const XYPointWithName &src);
};
class XYPointContainerWithName : public NPListPackSaveLoad<XYPointWithName>
{
public:
	XYPointContainerWithName(void){}
	XYPointContainerWithName(const XYPointContainerWithName &src);

	virtual	XYPointWithName	*Create(void);
	XYPointContainerWithName	&operator=(const XYPointContainerWithName &src);
	XYPointWithName	*Add(int x ,int y,const QString &name);
};

//==================================================================

class AlgoListArray : public NPListSaveLoad<AlgoListArray>
{
public:
	QString		DLLRoot;
	QString		DLLName;
	QByteArray	Array;

	AlgoListArray(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	AlgoListArray	&operator=(const AlgoListArray &src);
};

class AlgoListArrayContainer : public NPListPackSaveLoad<AlgoListArray>
{
public:
	AlgoListArrayContainer(void){}

	virtual	AlgoListArray	*Create(void)	{	return new AlgoListArray();	}

	AlgoListArrayContainer	&operator=(const AlgoListArrayContainer &src);
};

class AlgoListInPage : public NPListSaveLoad<AlgoListInPage>
{
public:
	int		Phase;
	int		Page;
	XYPointContainerWithName	ControlPointsForPages;
	AlgoListArrayContainer	AlgoList;

	AlgoListInPage(void){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;	
};

class AlgoListInPageContainer : public NPListPackSaveLoad<AlgoListInPage>
{
public:
	AlgoListInPageContainer(void){}

	virtual	AlgoListInPage	*Create(void)	{	return new AlgoListInPage();	}
};