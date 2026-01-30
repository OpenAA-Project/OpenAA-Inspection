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
	QStringList	DetailMessage;	//�\�����b�Z�[�W�@���ׂĂ̌����Ή�
	QColor		Color;
	int			WaitMilisec;

public:
	ResultDetailItem(ResultDetailStocker *parent);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	const QString&	GetAlgorithmName(void)		{	return AlgorithmName;	}
	int			GetMatchingCode(void)	{	return MatchingCode;	}
	QString		GetDetailMessage(void);	//�\�����b�Z�[�W�@���ׂĂ̌����Ή�
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