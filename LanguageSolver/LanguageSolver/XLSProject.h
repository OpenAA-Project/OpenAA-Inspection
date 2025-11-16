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

#include "NList.h"
#include <QString>
#include <QIODevice>
#include "XLanguageSolver.h"

class	LSProjectClass;

class	LSSourceFileItem : public NPList<LSSourceFileItem>
{
public:
	QString		FileName;

	bool	Save(QIODevice &File);
	bool	Load(QIODevice &File);
};

class	LSUIFileItem : public NPList<LSUIFileItem>
{
public:
	QString		FileName;

	bool	Save(QIODevice &File);
	bool	Load(QIODevice &File);
};

class	LSProjectItem : public NPList<LSProjectItem>
{
	LSProjectClass					*Parent;
public:
	QString							ProjectItemName;
	NPListPack<LSSourceFileItem>	SourceFiles;
	NPListPack<LSUIFileItem>		UIFiles;
	QString							ResourceFileName;
	QString							CSVFileName;
	QString							XLSXFileName;

	LanguageStocker					Stocker;


	LSProjectItem(LSProjectClass *parent,QString KeywordForLangSolver):Parent(parent),Stocker(KeywordForLangSolver){}

	bool	Save(QIODevice &File);
	bool	Load(QIODevice &File);

	bool	Execute(QString &ErrMsg);
};

class	LSProjectClass : public NPListPack<LSProjectItem>
{
public:
	QString	KeywordForLangSolver;
	QString	XLSXFolder;

	LSProjectClass(void){	KeywordForLangSolver="LangSolver";	}

	bool	Save(QIODevice &File);
	bool	Load(QIODevice &File);

	void	SetKeyword(QString _KeywordForLangSolver);
};

extern	LSProjectClass	LSProjectData;

#endif