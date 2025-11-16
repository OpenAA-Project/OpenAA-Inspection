/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XBoolList.h
** Author : YYYYYYYYYY
****************************************************************************-**/
//---------------------------------------------------------------------------

#ifndef XBoolClassH
#define XBoolClassH
//---------------------------------------------------------------------------
#include <QIODevice>
#include "NList.h"
#include "XTypeDef.h"

class   BoolClass : public NPList<BoolClass>
{
    bool d;
  public:

    BoolClass(void)					{	d=true;		}
    explicit	BoolClass(bool n)	{   d=n;		}
	BoolClass(const BoolClass &src)	{	d=src.d;	}

    bool	GetValue(void)		{  return(d);  }
    void	SetValue(bool _d)	{  d=_d;		}

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
	BoolClass	&operator=(const BoolClass &src)		{	d=src.d;	return(*this);	}
	bool	operator==(const BoolClass &src)	const	{	return d==src.d;	}
	bool	operator!=(const BoolClass &src)	const	{	return d!=src.d;	}

	BoolClass	&operator=(bool _d)			{	d=_d;	return(*this);	}
	bool	operator==(bool src)	const	{	return d==src;	}
	bool	operator!=(bool src)	const	{	return d!=src;	}
	operator bool(void)	{	return d;	}
};

class	BoolList : public NPListPack<BoolClass>
{
public:
	BoolList(void);
	BoolList(const BoolList &src);

	bool	IsInclude(bool d);
	void	Add(bool d)	{	AppendList(new BoolClass(d));	}

	BoolList	&operator=(BoolList &src);
	BoolList	&operator=(const BoolList &src);
	BoolList	&operator+=(const BoolList &src);
	bool	operator==(const BoolList &src)	const;
	bool	operator!=(const BoolList &src)	const;
	bool	operator[](int n)	const;
	void	Merge(const BoolList &src);
	void	Merge(const BoolClass &src);
	void	Merge(bool s);

	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};

class   Bool3Class : public NPList<Bool3Class>
{
    bool3 d;
  public:

    Bool3Class(void)					{	d=true3;    }
    explicit	Bool3Class(bool3 n)		{	d=n;		}
	Bool3Class(const Bool3Class &src)	{	d=src.d;	}

    bool3	GetValue(void)	const	{  return(d);	}
    void	SetValue(bool3 _d)		{  d=_d;		}

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);

	Bool3Class	&operator=(const Bool3Class &src)		{	d=src.d;	return(*this);	}
	bool	operator==(const Bool3Class &src)	const	{	return d==src.d;	}
	bool	operator!=(const Bool3Class &src)	const	{	return d!=src.d;	}

	Bool3Class	&operator=(bool3 _d)		{	d=_d;	return(*this);	}
	bool	operator==(bool3 src)	const	{	return d==src;	}
	bool	operator!=(bool3 src)	const	{	return d!=src;	}
	operator bool3(void)	{	return d;	}
};

class	Bool3List : public NPListPack<Bool3Class>
{
public:
	Bool3List(void);
	Bool3List(const Bool3List &src);

	bool	IsInclude(bool3 d);
	void	Add(bool3 d)	{	AppendList(new Bool3Class(d));	}

	Bool3List	&operator=(Bool3List &src);
	Bool3List	&operator=(const Bool3List &src);
	Bool3List	&operator+=(const Bool3List &src);
	bool	operator==(const Bool3List &src)	const;
	bool	operator!=(const Bool3List &src)	const;
	bool3	operator[](int n)	const;
	void	Merge(const Bool3List &src);
	void	Merge(const Bool3Class &src);
	void	Merge(bool3 s);

	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};
#endif
