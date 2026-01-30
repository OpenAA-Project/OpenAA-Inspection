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

#if	!defined(XMACROEXECUTER_H)
#define	XMACROEXECUTER_H

#include<QString>
#include<QStringList>
#include"NList.h"
#include <QIODevice>
#include "XTypeDef.h"

class	LayersBase;


class	MacroSentenseBase : public NPList<MacroSentenseBase>
{
public:
	MacroSentenseBase(void){}

	virtual	bool	LoadFromMacro(const QString &TextBuff)=0;
	virtual	QString	GetTextLine(void)=0;
	virtual	bool	ExecuteLine(LayersBase *Base,bool &ExeReturn)=0;

	bool	ExecuteMacro(LayersBase *Base);
};

class	MacroFunction : public MacroSentenseBase
{
	QString	DLLRoot;
	QString	DLLName;
	QString	InstName;
	QString	FuncName;

	QStringList	Args;

public:
	MacroFunction(void){}

	virtual	bool	LoadFromMacro(const QString &TextBuff)			override;
	virtual	QString	GetTextLine(void)								override;
	virtual	bool	ExecuteLine(LayersBase *Base,bool &ExeReturn)	override;
};

class	MacroWait : public MacroSentenseBase
{
	QString	WaitCount;
public:

	MacroWait(void){}
	virtual	bool	LoadFromMacro(const QString &TextBuff)			override;
	virtual	QString	GetTextLine(void)								override;
	virtual	bool	ExecuteLine(LayersBase *Base,bool &ExeReturn)	override;
};

class	MacroSentenseContainer : public NPListPack<MacroSentenseBase>
{
public:
	MacroSentenseContainer(void){}

	virtual	bool	LoadFromMacro(QIODevice &TextFile,QString &ErrorLine);
};


#endif