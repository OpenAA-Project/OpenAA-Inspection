/*
 * Copyright (C) 2016
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

#if	!defined(XLANGUAGEMODIFIER_H)
#define	XLANGUAGEMODIFIER_H

#include <QObject>
class	GUIFormBase;

class	LangDialogModifier
{
public:
	LangDialogModifier(QObject *parent);

	static	void	Register(LangDialogModifier *ObjDialog ,GUIFormBase *RootInstance);

	void	Setup(void);
	void	Reset(void);
};

class	LangMessageModifier
{
public:
	LangMessageModifier(LangDialogModifier *parent	);
	LangMessageModifier(GUIFormBase *parent			);
	
	void	SetMessageString(int ID ,const QString &Str);
	QString	GetMessageString(int ID);
};


#endif