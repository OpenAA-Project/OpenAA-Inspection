/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDualIntList.h
** Author : YYYYYYYYYY
****************************************************************************-**/
//---------------------------------------------------------------------------

#ifndef XDualIntListH
#define XDualIntListH
//---------------------------------------------------------------------------
#include <QIODevice>
#include "NList.h"
#include "XTypeDef.h"

class   DualIntClass : public NPList<DualIntClass>
{
    int32	D[2];

  public:
    DualIntClass(void){ D[0]=0;	D[1]=0;    }
    explicit	DualIntClass(int d1 ,int d2)	{   D[0]=d1;	D[1]=d2;	}
	DualIntClass(const DualIntClass &src)	{	D[0]=src.D[0];	D[1]=src.D[1];	}

    int		GetValue(int n)			const	{  return(D[n]);  }
    void	SetValue(int n ,int _d)			{  D[n]=_d;  }

	int		GetX(void)			const	{	return D[0];	}
	int		GetY(void)			const	{	return D[1];	}
	void	SetXY(int x ,int y)			{	D[0]=x;	D[1]=y;	}

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
	DualIntClass	&operator=(const DualIntClass &src)	{	D[0]=src.D[0];	D[1]=src.D[1];	return(*this);	}
	bool	operator==(const DualIntClass &src)	const	{	return (D[0]==src.D[0]) & (D[1]==src.D[1]);	}
	bool	operator!=(const DualIntClass &src)	const	{	return (D[0]!=src.D[0]) | (D[1]!=src.D[1]);	}
};

class	DualIntList	: public NPListPack<DualIntClass>
{
public:
	DualIntList(void){}
	DualIntList(const DualIntList &src);

	bool	IsInclude(int d1,int d2);
	void	Add(int d1, int d2)	{	AppendList(new DualIntClass(d1,d2));	}

	DualIntList	&operator=(const DualIntList &src);
	bool	operator==(const DualIntList &src)	const;
	bool	operator!=(const DualIntList &src)	const;
	void	Merge	(int d1, int d2);
	void	Merge	(const DualIntList &src);
	void	Merge	(const DualIntClass &src);

	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};

//========================================================================
#endif