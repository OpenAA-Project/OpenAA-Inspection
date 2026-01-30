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

//---------------------------------------------------------------------------

#ifndef XDoubleClassH
#define XDoubleClassH
//---------------------------------------------------------------------------
#include <QIODevice>
#include "XTypeDef.h"
#include "NList.h"

class   DoubleClass : public NPList<DoubleClass>
{
    double	d;

  public:
    DoubleClass(void){ d=0;    }
    explicit	DoubleClass(double n)	{    d=n;		}
	DoubleClass(const DoubleClass &src)	{	d=src.d;	}

    double	GetValue(void)		const	{  return(d);	}
    void	SetValue(double _d)			{  d=_d;		}

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
	DoubleClass	&operator=(const DoubleClass &src){	d=src.d;	return(*this);	}
	bool	operator==(const DoubleClass &src)	const	{	return d==src.d;	}
	bool	operator!=(const DoubleClass &src)	const	{	return d!=src.d;	}

	DoubleClass	&operator=(double _d){	d=_d;	return(*this);	}
	bool	operator==(double src){	return (d==src)?true:false;	}
	bool	operator!=(double src){	return (d!=src)?true:false;	}

	virtual	int	Compare(DoubleClass &src)	override;
};

class	DoubleList	: public NPListPack<DoubleClass>
{
public:
	DoubleList(void);
	DoubleList(const DoubleList &src);

	bool	IsInclude(double d);
	void	Add(double d)	{	AppendList(new DoubleClass(d));	}
	DoubleList	&operator=(const DoubleList &src);
	DoubleList	&operator+=(const DoubleList &src);
	bool	operator==(const DoubleList &src)	const;
	bool	operator!=(const DoubleList &src)	const;

	DoubleList	operator+()	const;
	DoubleList	operator-()	const;
	DoubleList	operator+(const DoubleList &src)	const;
	DoubleList	operator-(const DoubleList &src)	const;
	DoubleList	operator*(const DoubleList &src)	const;
	DoubleList	operator/(const DoubleList &src)	const;
	DoubleList	operator*(float m)	const;
	DoubleList	operator/(float m)	const;
	DoubleList	&operator-=(const DoubleList &src);
	DoubleList	&operator*=(const DoubleList &src);
	DoubleList	&operator/=(const DoubleList &src);
	DoubleList	&operator*=(float m);
	DoubleList	&operator/=(float m);

	double	operator[](int n)	const	{	return GetItem(n)->GetValue();	}

	void	Merge	(double d);
	void	Merge	(const DoubleList &src);
	void	Merge	(const DoubleClass &src);

	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};


#endif
 