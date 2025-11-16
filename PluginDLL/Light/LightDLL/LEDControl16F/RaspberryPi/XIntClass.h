/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XIntClass.h
** Author : YYYYYYYYYY
****************************************************************************-**/
//---------------------------------------------------------------------------

#ifndef XIntClassH
#define XIntClassH
//---------------------------------------------------------------------------
#include <QIODevice>
#include "NListRPi.h"
#include "XTypeDef.h"

class   IntClass : public NPList<IntClass>
{
    int d;

  public:
    IntClass(void){ d=0;    }
    IntClass(int n){    d=n;    }
	IntClass(IntClass &src){	d=src.d;	}

    int		GetValue(void){  return(d);  }
    void	SetValue(int _d){  d=_d;  }

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
	IntClass	&operator=(IntClass &src)		{	d=src.d;	return(*this);	}
	IntClass	&operator=(const IntClass &src)	{	d=src.d;	return(*this);	}
	bool	operator==(IntClass &src){	return d==src.d;	}
	bool	operator!=(IntClass &src){	return d!=src.d;	}

	IntClass	&operator=(int _d){	d=_d;	return(*this);	}
	bool	operator==(int src){	return d==src;	}
	bool	operator!=(int src){	return d!=src;	}

	virtual	int	Compare(IntClass &src);
};

class	IntList	: public NPListPack<IntClass>
{
public:
	IntList(void);
	IntList(IntList &src);

	bool	IsInclude(int d);
	void	Add(int d)	{	AppendList(new IntClass(d));	}
	void	Remove(int d);
	void	Merge(IntList &src);	//異なる値だけをコピー

	IntList	&operator=(IntList &src);
	IntList	&operator=(const IntList &src);
	bool	operator==(IntList &src) const;
	bool	operator!=(IntList &src) const;

	int		operator[](int n);

	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};


class	IntListFast : public IntList
{
	BYTE	*Dim;
	int32	AllocatedByte;

public:
	IntListFast(void);
	~IntListFast(void);

	bool	IsInclude(int d);
	void	Add(int d)	;

	IntList	&operator=(IntListFast &src);
	IntList	&operator=(const IntListFast &src);
	bool	operator==(IntListFast &src) const;
	bool	operator!=(IntListFast &src) const;

	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};


//========================================================================
class	ListLayerIDLibName;

class	ListLayerAndID : public NPList<ListLayerAndID>
{
public:
	int32		Layer;
	int32		ID;

	ListLayerAndID(void){	Layer=0;	ID=0;	}
	ListLayerAndID(int layer ,int id){	Layer=layer;	ID=id;	}
	ListLayerAndID(ListLayerAndID &src);
	ListLayerAndID(ListLayerIDLibName &src);
	ListLayerAndID	&operator=(ListLayerAndID &src);
	ListLayerAndID	&operator=(ListLayerIDLibName &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListLayerAndIDPack : public NPListPack<ListLayerAndID>
{
public:
	ListLayerAndIDPack(void){}
	ListLayerAndIDPack(ListLayerAndIDPack &src);

	ListLayerAndIDPack	&operator=(ListLayerAndIDPack &src);
	ListLayerAndIDPack	&operator+=(ListLayerAndIDPack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//========================================================================

class	ListPageLayerID : public NPList<ListPageLayerID>
{
public:
	int32		Page;
	int32		Layer;
	int32		ID;

	ListPageLayerID(void){	Page=0;	Layer=0;	ID=0;	}
	ListPageLayerID(int page ,int layer ,int id){	Page=page;	Layer=layer;	ID=id;	}
	ListPageLayerID(ListPageLayerID &src);
	ListPageLayerID	&operator=(ListPageLayerID &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListPageLayerIDPack : public NPListPack<ListPageLayerID>
{
	int	MaxPage;
	int	MaxLayer;
	int	MaxID;
	int	MinPage;
	int	MinLayer;
	int	MinID;
	bool		*Table;

public:
	ListPageLayerIDPack(void){	Table=NULL;	}
	ListPageLayerIDPack(ListPageLayerIDPack &src);
	~ListPageLayerIDPack(void);

	ListPageLayerIDPack	&operator=(ListPageLayerIDPack &src);
	ListPageLayerIDPack	&operator+=(ListPageLayerIDPack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	IsInclude(int Page, int Layer ,int ID);
	void	Add		(int page ,int Layer ,int id);
	void	Merge	(int page ,int Layer ,int id);
	void	Move(ListPageLayerIDPack &src);

	void	MakeLinearDim(void);
	bool	IsIncludeByLinear(int Page, int Layer ,int ID);
};

//========================================================================

class	ListPageID : public NPList<ListPageID>
{
public:
	int32		Page;
	int32		ID;

	ListPageID(void){	Page=0;	ID=0;	}
	ListPageID(int page ,int layer ,int id)	{	Page=page;	ID=id;	}
	ListPageID(int page ,int id)			{	Page=page;	ID=id;	}
	ListPageID(const ListPageLayerID &src);
	ListPageID	&operator=(ListPageID &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListPageIDPack : public NPListPack<ListPageID>
{
public:
	ListPageIDPack(void){}
	ListPageIDPack(ListPageIDPack &src);

	ListPageIDPack	&operator=(ListPageIDPack &src);
	ListPageIDPack	&operator+=(ListPageIDPack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsInclude(int page,int id);
	void	Add		(int page ,int id);
	void	Merge	(int page ,int id);
	void	Merge	(ListPageIDPack &src);
};

//========================================================================

class	ListLayerIDLibName : public NPList<ListLayerIDLibName>
{
public:
	int32		Layer;
	int32		ID;
	int32		LibID;
	QString		ItemName;

	ListLayerIDLibName(void)							{	Layer=0;	ID=0;	LibID=0;	}
	ListLayerIDLibName(int layer ,int id ,int libid)	{	Layer=layer;	ID=id;	LibID=libid;	}
	ListLayerIDLibName(ListLayerIDLibName &src);
	ListLayerIDLibName	&operator=(ListLayerIDLibName &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListLayerIDLibNamePack : public NPListPack<ListLayerIDLibName>
{
public:
	ListLayerIDLibNamePack(void){}
	ListLayerIDLibNamePack(ListLayerIDLibNamePack &src);

	ListLayerIDLibNamePack	&operator= (ListLayerIDLibNamePack &src);
	ListLayerIDLibNamePack	&operator+=(ListLayerIDLibNamePack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
//========================================================================

class	ListPageLayerIDLibName : public NPList<ListPageLayerIDLibName>
{
public:
	int32		Page;
	int32		Layer;
	int32		ID;
	int32		LibID;
	QString		ItemName;

	ListPageLayerIDLibName(void)							{	Page=0;	Layer=0;	ID=0;	LibID=0;	}
	ListPageLayerIDLibName(ListPageLayerIDLibName &src);
	ListPageLayerIDLibName	&operator=(ListPageLayerIDLibName &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListPageLayerIDLibNamePack : public NPListPack<ListPageLayerIDLibName>
{
public:
	ListPageLayerIDLibNamePack(void){}
	ListPageLayerIDLibNamePack(ListPageLayerIDLibNamePack &src);

	ListPageLayerIDLibNamePack	&operator= (ListPageLayerIDLibNamePack &src);
	ListPageLayerIDLibNamePack	&operator+=(ListPageLayerIDLibNamePack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif
 