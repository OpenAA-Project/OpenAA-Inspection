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

#if	!defined(XMERGEXLSX_H)
#define	XMERGEXLSX_H

#include "XExcelOperator.h"
#include <QFileInfo>
#include "XExcelOperator.h"
#include "XLanguageCodec.h"
#include "NList.h"

class	CombinedXLSX : public NPList<CombinedXLSX>
{
	QStringListListXLSX	Dest0;	//Sheet0
	QStringListListXLSX	Dest1;	//Sheet1
	QStringListListXLSX	Source;

	class	StringLine : public NPList<StringLine>
	{
	public:
		QString		FileLS;
		QString		ID;
		int			Row;
	};
	NPListPack<StringLine>	StringLineContainer;

	class	UILine : public NPList<UILine>
	{
	public:
		QString		ClassName;
		QString		TypeName;
		QString		ObjectName;
		QString		PropertyName;
		QString		Str1;
		int			Row;
	};
	NPListPack<UILine>	UILineContainer;

public:
	QFileInfo	DestFile;
	QFileInfo	SourceFile;
	bool		Result;

	CombinedXLSX(QFileInfo &Dest ,QFileInfo &Src);

	bool	Load(void);
	bool	Merge(int LangNo);
	bool	SaveToDest(LanguagePack &LangPack);

	QString	GetDestFileName(void);
	QString	GetSourceFileName(void);

private:
	StringLine	*SearchString(QString &FileLS ,QString &ID);
	UILine		*SearchUI( QString &ClassName
							,QString &TypeName
							,QString &ObjectName
							,QString &PropertyName
							,QString &Str1);
};

#endif