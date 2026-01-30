/*
 * Copyright (C) 2012
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

#if	!defined(XLANGUAGEMANAGER_H)
#define	XLANGUAGEMANAGER_H

#include <QString>
#include <QStringList>
#include "NListComp.h"
#include <QIODevice>
#include "XLanguageStockerLoader.h"
#include "XLanguageCodec.h"
#include <QProgressBar>

class	DefaultParam
{
public:
	QString		DefaultLNGPath;

	DefaultParam(void);
};

class	ProjectLanguage : public NPListSaveLoad<ProjectLanguage>
{
	LanguagePackage		LPackage;
public:
	QString		ProjectName;
	QStringList	ExcelFiles;
	QString		OutputLNGFile;

	ProjectLanguage(void){}

	QString	GetLngFileName(void);
	bool	Execute(LanguagePack &LangPack,QProgressBar *Bar ,QString &ErrorMsg);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
private:
	bool	LoadExcel(const QString &ExcelFileName ,LanguagePack &LangPack ,LanguagePackage::LanguageComponent *DestL);
};

class	SolutionLanguage : public NPListPackSaveLoad<ProjectLanguage>
{
	static	QString	DefaultFileName;
public:

	SolutionLanguage(void){}

	int		Search(const QString &ProjName);
	ProjectLanguage	*Create(void)	{	return new ProjectLanguage();	}
	void	Clear(void);
	QString	GetDefaultFileName(void)	{	return DefaultFileName;	}

	bool	SaveDefault(void);
	bool	LoadDefault(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};



#endif