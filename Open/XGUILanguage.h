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

#pragma once

#include "NListComp.h"
#include "XTypeDef.h"

class LanguageStringList : public NPListSaveLoad<LanguageStringList>
{
public:
	int32	LanguageCode;
	QString	Text;
	QStringList	TextList;

	LanguageStringList(void){}
	LanguageStringList(const LanguageStringList &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	LanguageStringList	&operator=(const LanguageStringList &src);
};

class LanguageStringContainer : public NPListPackSaveLoad<LanguageStringList>
{
public:
	LanguageStringContainer(void){}
	LanguageStringContainer(const LanguageStringContainer &src);

	virtual	LanguageStringList	*Create(void)	override;
	LanguageStringContainer	&operator=(const LanguageStringContainer &src);

	LanguageStringList	*FindLanguage(int LanguageCode)	const;
};

class GUILanguageList : public NPListSaveLoad<GUILanguageList>
{
public:
	QString	DLLRoot;
	QString	DLLName;
	QString	InstName;
	QString	MemberName;
	LanguageStringContainer	LanguageText;

	GUILanguageList(void){}
	GUILanguageList(const GUILanguageList &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	GUILanguageList	&operator=(const GUILanguageList &src);
};

class GUILanguageContainer : public NPListPackSaveLoad<GUILanguageList>
{
public:
	GUILanguageContainer(void){}
	GUILanguageContainer(const GUILanguageContainer &src);

	virtual	GUILanguageList	*Create(void)	override;
	GUILanguageContainer	&operator=(const GUILanguageContainer &src);

	GUILanguageList	*Find(const QString &FormRoot
						 ,const QString &FormName
						 ,const QString &InstName
						 ,const QString	&MemberName)	const;

};
