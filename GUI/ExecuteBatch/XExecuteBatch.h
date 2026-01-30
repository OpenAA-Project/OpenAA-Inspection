/*
 * Copyright (C) 2016
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

#if	!defined(XExecuteBatch_H)
#define	XExecuteBatch_H

#include <QString>
#include "NListComp.h"
#include "XDataInLayer.h"
#include <QTextStream>

class	BatchContainer;
class	BatchLine : public NPListSaveLoad<BatchLine>
{
	BatchContainer	*Parent;
public:
	enum	__DLLType
	{
		 _DLL_GUI			=1
		,_DLL_Algorithm		=2
		,_DLL_Result		=3
	}DLLType;

	QString		DLLRoot;
	QString		DLLName;
	QString		CommandStr;
	QStringList	ArgValues;

	BatchLine(BatchContainer *parent):Parent(parent){	DLLType=_DLL_GUI;	}

	bool	ExecuteLine(LayersBase *base);
	BatchLine	&operator=(BatchLine &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	SaveText(QTextStream &Txt);
	virtual	bool	LoadText(QTextStream &Txt);

	void	ReplaceParam(const QString &Keyword ,const QString &ReplacedStr);
};

class	BatchContainer : public NPListPackSaveLoad<BatchLine>
{
public:
	QStringList	ParamFromArg;	//@xx

	BatchContainer(void){}

	virtual	BatchLine	*Create(void)	{	return new BatchLine(this);	}

	virtual	bool	SaveText(QIODevice *f);
	virtual	bool	LoadText(QIODevice *f);
	virtual	bool	AppendText(QIODevice *f);

	void	ReplaceParam(const QString &Keyword ,const QString &ReplacedStr); 
};


#endif