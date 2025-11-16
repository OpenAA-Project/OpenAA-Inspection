/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\XLSProject.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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