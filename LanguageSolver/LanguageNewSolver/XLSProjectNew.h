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



#if	!defined(XLSPROJECT_H)
#define	XLSPROJECT_H

#include "NListComp.h"
#include <QString>
#include <QIODevice>
#include "XLanguageCodec.h"

class	LSProjectClass;
class	LanguageStocker;

class	LSSourceFileItem : public NPListSaveLoad<LSSourceFileItem>
{
public:
	QString		FileName;

	bool	Save(QIODevice *File);
	bool	Load(QIODevice *File);
};

class	LSUIFileItem : public NPListSaveLoad<LSUIFileItem>
{
public:
	QString		FileName;

	bool	Save(QIODevice *File);
	bool	Load(QIODevice *File);
};

class	LSProjectItem : public NPListSaveLoad<LSProjectItem>
{
	LSProjectClass					*Parent;
public:
	QString							ProjectItemName;
	QString							ReferenceFolder;
	class	LSSourceFileContainer : public NPListPackSaveLoad<LSSourceFileItem>
	{
	public:
		LSSourceFileContainer(void){}
		LSSourceFileItem	*Create(void)	{	return new LSSourceFileItem();	}
	}SourceFiles;

	class	LSUIFileContainer : public NPListPackSaveLoad<LSUIFileItem>
	{
	public:
		LSUIFileContainer(void){}
		LSUIFileItem	*Create(void)	{	return new LSUIFileItem();	}
	}UIFiles;

	QString							ResourceFileName;
	QString							XLSXFileName;

	LSProjectItem(LSProjectClass *parent):Parent(parent){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	Execute(LanguageStocker &Stocker ,LanguagePack &LangPack ,QString &ErrMsg);

	int	Compare(LSProjectItem &src);
};

class	LSProjectClass : public NPListPackSaveLoad<LSProjectItem>
{
public:
	QString	KeywordForLangSolver;
	QString	XLSXFolder;
	QString	FileName;

	LSProjectClass(void){	KeywordForLangSolver="LangSolver";	}

	void	Clear(void);
	int		SearchRow(const QString &ProjName);
	LSProjectItem	*Create(void){	return new LSProjectItem(this);	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#endif