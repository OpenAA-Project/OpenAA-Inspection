/*
 * Copyright (C) 2025
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

#if	!defined(XLANGUAGECODEC_H)
#define	XLANGUAGECODEC_H

#include <QString>
#include <QStringList>
#include "NListComp.h"
#include <QIODevice>

class	QTextCodec;

class	LanguageClass : public NPListSaveLoad<LanguageClass>
{
public:
	int		ColumnNo;
	QString	LanguageName;
	QString	ExcelFont;
	QString	QtCotec;

	QTextCodec	*CurrentCodec;

	LanguageClass(void){	ColumnNo=0;	CurrentCodec=NULL;	}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	LanguagePack : public NPListPackSaveLoad<LanguageClass>
{
	static	QString	DefaultFileName;
public:
	LanguagePack(void){}

	LanguageClass	*Create(void)	{	return new LanguageClass();		}

	bool	SaveDefault(void);
	bool	LoadDefault(void);

	void	AllocCodec(void);
	void	SetCodec(int n);
};


#endif