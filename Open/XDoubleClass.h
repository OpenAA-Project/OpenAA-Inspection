/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDoubleClass.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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
 