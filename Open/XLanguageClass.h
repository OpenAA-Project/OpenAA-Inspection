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

#if	!defined(XLANGUAGECLASS_H)
#define	XLANGUAGECLASS_H

#include <QString>
#include "XLanguageStockerLoader.h"
#include "XTypeDef.h"

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
	char	*ListStrings1;	//�擪�ɂQ�o�C�g�Ń��X�g���A���̌㕶�����A�����񂪕ς��镔���ɂ�\0
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

	char	*ListStrings1;	//�擪�ɂQ�o�C�g�Ń��X�g���A���̌㕶�����A�����񂪕ς��镔���ɂ�\0
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

	int		LanguageCode;	//0�`
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