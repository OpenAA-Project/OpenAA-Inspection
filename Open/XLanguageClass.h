/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XLanguageClass.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XLANGUAGECLASS_H)
#define	XLANGUAGECLASS_H

#include <QString>
#include "XLanguageStockerLoader.h"
#include "XTypeDef.h"
/*
=============================================================================
	New version
=============================================================================
*/

class	LanguagePackage;


class	LangSolverNew
{
	const	char				*IDName;
	LanguagePackage				*LPackPointer;
	LanguagePackage::LanguageComponent	*CompPointer;

public:
	explicit	LangSolverNew(const char *IDName);

	bool	SetLanguage(LanguagePackage &Stocker ,int LangCode);
	QString	GetString(int FileID ,int LID);
	void	SetUI(QWidget *W);

	int		GetLanguageCode(void);
};


/*
=============================================================================
	Old version
=============================================================================
*/

#define	MAXLANGUAGECOUNT	10

struct	LSStringResource
{
	int		FileNameID;
	int		ID;
	char	*ListStrings1;	//先頭に２バイトでリスト数、その後文字列、文字列が変わる部分には\0
	char	*ListStrings2;
	char	*ListStrings3;
	char	*ListStrings4;
	char	*ListStrings5;
	char	*ListStrings6;
	char	*ListStrings7;
	char	*ListStrings8;
	char	*ListStrings9;
	char	*ListStrings10;
};

struct	LSUIResource
{
	char	*UIClassName;
	char	*ClassTypeName;
	char	*ControlName;
	char	*PropertyName;

	char	*ListStrings1;	//先頭に２バイトでリスト数、その後文字列、文字列が変わる部分には\0
	char	*ListStrings2;
	char	*ListStrings3;
	char	*ListStrings4;
	char	*ListStrings5;
	char	*ListStrings6;
	char	*ListStrings7;
	char	*ListStrings8;
	char	*ListStrings9;
	char	*ListStrings10;
};



class	QWidget;
const int	MaxLanguageCounts=100;

class	LangSolverClass
{
	struct LSStringResource *LSStrDictionary;
	struct LSUIResource *LSUIDictionary;
	char	*CodecList[MAXLANGUAGECOUNT];
	QTextCodec *FirstCodec;
	QTextCodec *CurrentCodec;

	int		LanguageCode;	//0～
	bool	InitializedCodec;

public:
	LangSolverClass(struct LSStringResource _LSStrDictionary[]
					,struct LSUIResource _LSUIDictionary[]
					,char	*_CodecList[]);

	bool	SetLanguage(int LangCode);
	QString	GetString(int FileID ,int LID);
	void	SetUI(QWidget *W);

	bool	CheckCodec(void);
	int		GetLanguageCode(void){	return 	LanguageCode;	}

private:
	void	SetUIInner(QWidget *W ,const QString &UIClassName);
	bool	InitialCodec(void);
	void	ErrorOut(void);
};



#endif