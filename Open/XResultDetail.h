/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XResultDetail.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XResultDetailH
#define XResultDetailH

#include "NList.h"
#include "XIntClass.h"
#include<QIODevice>
#include<QStringList>
#include<QColor>

#define	ResultDetailVersion	1

class	ResultDetailStocker;

class	ResultDetailItem : public NPList<ResultDetailItem>
{
	ResultDetailStocker	*Parent;
protected:
	QString		AlgorithmName;
	int			MatchingCode;
	QStringList	DetailMessage;	//表示メッセージ　すべての言語対応
	QColor		Color;
	int			WaitMilisec;

public:
	ResultDetailItem(ResultDetailStocker *parent);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	const QString&	GetAlgorithmName(void)		{	return AlgorithmName;	}
	int			GetMatchingCode(void)	{	return MatchingCode;	}
	QString		GetDetailMessage(void);	//表示メッセージ　すべての言語対応
	QColor		GetColor(void)			{	return Color;		}
	int			GetWaitMilisec(void)	{	return WaitMilisec;	}
};

class	ResultDetailStocker : public NPListPack<ResultDetailItem>
{
	int		LanguageCode;
	int		DataVersion;
public:
	ResultDetailStocker(void){	DataVersion=ResultDetailVersion;	}

	void	SetLanguageCode(int code)	{	LanguageCode=code;		}
	int		GetLanguageCode(void)		{	return LanguageCode;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	ResultDetailItem	*Search(const QString &AlgorithmName ,int matchingcode);
	void				EnumAlgorithm	(QStringList &AlgorithmNames);
	void				EnumCodes		(const QString &AlgorithmName ,IntList &Codes);
};

#endif
