/*
 * Copyright (C) 2019
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

#if	!defined(NLISTCOMP_H)
#define	NLISTCOMP_H

#include "NList.h"
#include <QIODevice>

template<class T>
class	NPListSaveLoad : public NPList<T>
{
public:
	NPListSaveLoad(void){}

	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;
	NPListSaveLoad<T>	&operator=(T &src);
	NPListSaveLoad<T>	&operator=(const T &src);
};

template<class T>
class	NPListPackSaveLoad : public NPListPack<T>
{
public:
	NPListPackSaveLoad(void){}

	virtual	T	*Create(void)=0;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Append(QIODevice *f);
	virtual	void	AppendListItem(T *additem);

	virtual	NPListPackSaveLoad<T>	&operator=(NPListPackSaveLoad<T> &src);
	virtual	NPListPackSaveLoad<T>	&operator=(const NPListPackSaveLoad<T> &src);
	virtual	NPListPackSaveLoad<T>	&operator+=(NPListPackSaveLoad<T> &src);
};

#include "NListComp.cpp"

#endif