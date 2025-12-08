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
#include "NList.h"
#include "XTypeDef.h"

class	ListLayerIDLibNamePack;

/*
class   IntClass : public NPList<IntClass>
{
    int d;

  public:
    IntClass(void)	:d(0)	{}
    IntClass(int n)	:d(n)	{}
	IntClass(const IntClass &src):d(src.d)	{}

    int		GetValue(void)	const	{  return(d);	}
    void	SetValue(int _d)		{  d=_d;		}

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
	IntClass	&operator=(const IntClass &src)		{	d=src.d;	return(*this);	}
	bool	operator==(const IntClass &src)	const	{	return d==src.d;	}
	bool	operator!=(const IntClass &src)	const	{	return d!=src.d;	}

	IntClass	&operator=(int _d)			{	d=_d;	return(*this);	}
	bool	operator==(int src)	const		{	return d==src;	}
	bool	operator!=(int src)	const		{	return d!=src;	}

	IntClass	operator+()	const;
	IntClass	operator-()	const;
	IntClass	operator+(const IntClass &src)	const;
	IntClass	operator-(const IntClass &src)	const;
	IntClass	operator*(const IntClass &src)	const;
	IntClass	operator/(const IntClass &src)	const;
	IntClass	operator*(int m)	const;
	IntClass	operator/(int m)	const;
	IntClass	operator*(double m)	const;
	IntClass	operator/(double m)	const;
	IntClass	&operator+=(const IntClass &src);
	IntClass	&operator-=(const IntClass &src);
	IntClass	&operator*=(const IntClass &src);
	IntClass	&operator/=(const IntClass &src);
	IntClass	&operator*=(int m);
	IntClass	&operator/=(int m);
	IntClass	&operator*=(double m);
	IntClass	&operator/=(double m);
	IntClass	&operator++(void);
	IntClass	&operator--(void);

	virtual	int	Compare(IntClass &src)	override;
};

class	IntList	: public NPListPack<IntClass>
{
public:
	IntList(void);
	IntList(const IntList &src);

	bool	IsInclude(int d)	const;
	void	Add(int d)	{	AppendList(new IntClass(d));	}
	void	Remove(int d);
	void	Merge(const IntList &src);	//異なる値だけをコピー
	void	Merge(int d);

	IntList	&operator=(IntList &src);
	IntList	&operator=(const IntList &src);
	IntList	&operator+=(const IntList &src);
	bool	operator==(IntList &src)		const;
	bool	operator==(const IntList& src)	const;
	bool	operator!=(IntList &src)		const;
	bool	operator!=(const IntList& src)	const;

	IntList	operator+()	const;
	IntList	operator-()	const;
	IntList	operator+(const IntList &src)	const;
	IntList	operator-(const IntList &src)	const;
	IntList	operator*(const IntList &src)	const;
	IntList	operator/(const IntList &src)	const;
	IntList	operator*(int m)	const;
	IntList	operator/(int m)	const;
	IntList	operator*(double m)	const;
	IntList	operator/(double m)	const;
	IntList	&operator-=(const IntList &src);
	IntList	&operator*=(const IntList &src);
	IntList	&operator/=(const IntList &src);
	IntList	&operator*=(int m);
	IntList	&operator/=(int m);
	IntList	&operator*=(double m);
	IntList	&operator/=(double m);
	IntList	&operator++(void);
	IntList	&operator--(void);

	int		operator[](int n)	const;

	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};
*/

class IntClass : public DataList<int>
{
public:
    IntClass(void)	{}
    IntClass(int n)	{	Value=n;	}
	IntClass(const IntClass &src)	{	Value=src.GetValue();	}

    //int		GetValue(void)	const	{  return(Value);	}
    //void	SetValue(int _d)		{  Value=_d;		}

	IntClass	*GetNext(void)	const	{	return (IntClass *)DataList<int>::GetNext();	}
	IntClass	*GetPrev(void)	const	{	return (IntClass *)DataList<int>::GetPrev();	}

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
	IntClass	&operator=(const IntClass &src)		{	Value=src.Value;	return(*this);	}
	bool	operator==(const IntClass &src)	const	{	return Value==src.Value;	}
	bool	operator!=(const IntClass &src)	const	{	return Value!=src.Value;	}

	IntClass	&operator=(int _d)			{	Value=_d;	return(*this);	}
	bool	operator==(int src)	const		{	return Value==src;	}
	bool	operator!=(int src)	const		{	return Value!=src;	}

	IntClass	operator+()	const;
	IntClass	operator-()	const;
	IntClass	operator+(const IntClass &src)	const;
	IntClass	operator-(const IntClass &src)	const;
	IntClass	operator*(const IntClass &src)	const;
	IntClass	operator/(const IntClass &src)	const;
	IntClass	operator*(int m)	const;
	IntClass	operator/(int m)	const;
	IntClass	operator*(double m)	const;
	IntClass	operator/(double m)	const;
	IntClass	&operator+=(const IntClass &src);
	IntClass	&operator-=(const IntClass &src);
	IntClass	&operator*=(const IntClass &src);
	IntClass	&operator/=(const IntClass &src);
	IntClass	&operator*=(int m);
	IntClass	&operator/=(int m);
	IntClass	&operator*=(double m);
	IntClass	&operator/=(double m);
	IntClass	&operator++(void);
	IntClass	&operator--(void);

	int		Compare(IntClass &src);

};

class IntList: public DataValueDimContainer<int>
{
public:
	IntList(void);
	IntList(const IntList &src);
	~IntList(void){}


	IntClass	*GetFirst(void)		const	{	return (IntClass *)DataValueDimContainer<int>::GetFirst();			}
	IntClass	*GetLast(void)		const	{	return (IntClass *)DataValueDimContainer<int>::GetLast();			}
	IntClass	*GetItem(int index)	const	{	return (IntClass *)DataValueDimContainer<int>::GetItem(index);	}

	bool	IsInclude(int d)	const;
	void	Remove(int d);
	void	Merge(const IntList &src);
	void	Merge(int d);

	IntList	&operator=(IntList &src);
	IntList	&operator=(const IntList &src);
	IntList	&operator+=(const IntList &src);
	bool	operator==(IntList &src)		const;
	bool	operator==(const IntList& src)	const;
	bool	operator!=(IntList &src)		const;
	bool	operator!=(const IntList& src)	const;

	IntList	operator+()	const;
	IntList	operator-()	const;
	IntList	operator+(const IntList &src)	const;
	IntList	operator-(const IntList &src)	const;
	IntList	operator*(const IntList &src)	const;
	IntList	operator/(const IntList &src)	const;
	IntList	operator*(int m)	const;
	IntList	operator/(int m)	const;
	IntList	operator*(double m)	const;
	IntList	operator/(double m)	const;
	IntList	&operator-=(const IntList &src);
	IntList	&operator*=(const IntList &src);
	IntList	&operator/=(const IntList &src);
	IntList	&operator*=(int m);
	IntList	&operator/=(int m);
	IntList	&operator*=(double m);
	IntList	&operator/=(double m);
	IntList	&operator++(void);
	IntList	&operator--(void);

	int		operator[](int n)	const;
	int		GetMaxValue(int *Point=NULL)	const;
	int		GetMinValue(int *Point=NULL)	const;

	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};


class	IntListPointer	: public NPList<IntListPointer> ,public IntList
{
public:
	IntListPointer(void);
	IntListPointer(const IntList &src);
};

class IntListContainer : public NPListPack<IntListPointer>
{
public:
	IntListContainer(void);
	IntListContainer(const IntListContainer &src);

	void	Add(const IntList &d);
	bool	IsInclude(const IntList &d);

	IntListContainer	&operator=(IntListContainer &src);
	IntListContainer	&operator=(const IntListContainer &src);
	IntListContainer	&operator+=(const IntListContainer &src);
	bool	operator==(IntListContainer &src)		const;
	bool	operator==(const IntListContainer& src) const;
	bool	operator!=(IntListContainer &src)		const;
	bool	operator!=(const IntListContainer& src) const;

	IntListContainer	operator+()	const;
	IntListContainer	operator-()	const;
	IntListContainer	operator+(const IntListContainer &src)	const;
	IntListContainer	operator-(const IntListContainer &src)	const;
	IntListContainer	operator*(const IntListContainer &src)	const;
	IntListContainer	operator/(const IntListContainer &src)	const;
	IntListContainer	operator*(int m)	const;
	IntListContainer	operator/(int m)	const;
	IntListContainer	operator*(double m)	const;
	IntListContainer	operator/(double m)	const;
	IntListContainer	&operator-=(const IntListContainer &src);
	IntListContainer	&operator*=(const IntListContainer &src);
	IntListContainer	&operator/=(const IntListContainer &src);
	IntListContainer	&operator*=(int m);
	IntListContainer	&operator/=(int m);
	IntListContainer	&operator*=(double m);
	IntListContainer	&operator/=(double m);

	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};


class	IntListFast : public IntList
{
	BYTE	*Dim;
	int32	AllocatedByte;

public:
	IntListFast(void);
	IntListFast(const IntListFast &src);
	~IntListFast(void);

	bool	IsInclude(int d)	const;
	void	Add(int d)	;

	IntListFast	&operator=(const IntList &src);
	IntListFast	&operator=(const IntListFast &src);
	IntListFast	&operator+=(const IntListFast &src);
	bool	operator==(IntListFast &src) const;
	bool	operator!=(IntListFast &src) const;

	bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};

class	IntDimClass : public DimList<IntDimClass>
{
    int d;

  public:
    IntDimClass(void):d(0)	{}
    IntDimClass(int n):d(n)	{}
	IntDimClass(const IntDimClass &src):d(src.d)	{}

    int		GetValue(void)	const	{  return(d);	}
    void	SetValue(int _d)		{  d=_d;		}

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
	IntDimClass	&operator=(const IntDimClass &src)		{	d=src.d;	return(*this);	}
	bool	operator==(const IntDimClass &src)	const	{	return d==src.d;	}
	bool	operator!=(const IntDimClass &src)	const	{	return d!=src.d;	}

	IntDimClass	&operator=(int _d)		{	d=_d;	return(*this);	}
	bool	operator==(int src)	const	{	return d==src;	}
	bool	operator!=(int src)	const	{	return d!=src;	}

	virtual	int	Compare(IntDimClass &src)	override	{	return d-src.d;	}
};
class	IntDimClassPack : public DimListPack<IntDimClass>
{
public:
	IntDimClassPack(void){}

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

	ListLayerAndID(void):Layer(0),ID(0)					{}
	ListLayerAndID(int layer ,int id):Layer(layer),ID(id){}
	ListLayerAndID(const ListLayerAndID &src);
	ListLayerAndID(const ListLayerIDLibName &src);

	ListLayerAndID	&operator=(const ListLayerAndID &src);
	ListLayerAndID	&operator=(const ListLayerIDLibName &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListLayerAndIDPack : public NPListPack<ListLayerAndID>
{
public:
	ListLayerAndIDPack(void){}
	ListLayerAndIDPack(const ListLayerAndIDPack &src);

	ListLayerAndIDPack	&operator=(const ListLayerAndIDPack &src);
	ListLayerAndIDPack	&operator+=(const ListLayerAndIDPack &src);
	ListLayerAndIDPack	&operator=(const ListLayerIDLibNamePack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	void	MakeIDList(int Layer ,IntList &IDList);
};

//========================================================================

class	ListPageLayerID : public NPList<ListPageLayerID>
{
public:
	int32		Page;
	int32		Layer;
	int32		ID;

	ListPageLayerID(void)	:Page(0),Layer(0),ID(0)		{}
	ListPageLayerID(int page ,int layer ,int id):Page(page),Layer(layer),ID(id){}
	ListPageLayerID(const ListPageLayerID &src);
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
	ListPageLayerIDPack(const ListPageLayerIDPack &src);
	~ListPageLayerIDPack(void);

	ListPageLayerIDPack	&operator=(ListPageLayerIDPack &src);
	ListPageLayerIDPack	&operator+=(ListPageLayerIDPack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	IsInclude(int Page, int Layer ,int ID);
	void	Add		(int page ,int Layer ,int id);
	void	Merge	(int page ,int Layer ,int id);
	void	Merge	(const ListPageLayerIDPack &src);
	void	Merge	(const ListPageLayerID &src);
	void	Move(ListPageLayerIDPack &src);

	void	MakeLinearDim(void);
	bool	IsIncludeByLinear(int Page, int Layer ,int ID);

	void	MakeIDList(int Layer ,IntList &IDList);
	void	MakeIDList(int Page,int Layer ,IntList &IDList);
};

//========================================================================

class	ListPageLayer: public NPList<ListPageLayer>
{
public:
	int32		Page;
	int32		Layer;

	ListPageLayer(void){	Page=0;	Layer=0;	}
	ListPageLayer(int page ,int layer){	Page=page;	Layer=layer;	}
	ListPageLayer(const ListPageLayer &src);

	ListPageLayer	&operator=(const ListPageLayer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListPageLayerPack : public NPListPack<ListPageLayer>
{
public:
	ListPageLayerPack(void){}
	ListPageLayerPack(const ListPageLayerPack &src);

	ListPageLayerPack	&operator=(const ListPageLayerPack &src);
	ListPageLayerPack	&operator+=(const ListPageLayerPack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	IsInclude(int Page, int Layer);
	void	Add		(int page ,int Layer);
	void	Merge	(int page ,int Layer);
	void	Merge	(const ListPageLayerPack &src);
	void	Merge	(const ListPageLayer &src);

	void	GetPageList(IntList &PageList);
	void	GetLayer(int page ,IntList &LayerList);
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
	ListPageID(const ListPageID &src);

	ListPageID	&operator=(const ListPageID &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListPageIDPack : public NPListPack<ListPageID>
{
public:
	ListPageIDPack(void){}
	ListPageIDPack(const ListPageIDPack &src);

	ListPageIDPack	&operator=(const ListPageIDPack &src);
	ListPageIDPack	&operator+=(const ListPageIDPack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsInclude(int page,int id);
	void	Add		(int page ,int id);
	void	Merge	(int page ,int id);
	void	Merge	(const ListPageIDPack &src);
	void	Merge	(const ListPageID &src);

	void	MakeIDList(int page ,IntList &IDList);
};
//========================================================================

class	ListPhasePageID : public NPList<ListPhasePageID>
{
public:
	int32		Phase;
	int32		Page;
	int32		ID;

	ListPhasePageID(void){	Page=0;	ID=0;	}
	ListPhasePageID(int phase,int page ,int layer ,int id)	{	Phase=phase;	Page=page;	ID=id;	}
	ListPhasePageID(int phase,int page ,int id)				{	Phase=phase;	Page=page;	ID=id;	}
	ListPhasePageID(const ListPageLayerID &src);
	ListPhasePageID(const ListPhasePageID &src);

	ListPhasePageID	&operator=(const ListPhasePageID &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListPhasePageIDPack : public NPListPack<ListPhasePageID>
{
public:
	ListPhasePageIDPack(void){}
	ListPhasePageIDPack(const ListPhasePageIDPack &src);

	ListPhasePageIDPack	&operator=(const ListPhasePageIDPack &src);
	ListPhasePageIDPack	&operator+=(const ListPhasePageIDPack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsInclude(int phase,int page,int id);
	void	Add		(int phase,int page ,int id);
	void	Merge	(int phase,int page ,int id);
	void	Merge	(const ListPhasePageIDPack &src);
	void	Merge	(const ListPhasePageID &src);

	void	MakeIDList(int phase,int page ,IntList &IDList);
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
	ListLayerIDLibName(const ListLayerIDLibName &src);

	ListLayerIDLibName	&operator=(const ListLayerIDLibName &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListLayerIDLibNamePack : public NPListPack<ListLayerIDLibName>
{
public:
	ListLayerIDLibNamePack(void){}
	ListLayerIDLibNamePack(const ListLayerIDLibNamePack &src);

	ListLayerIDLibNamePack	&operator= (const ListLayerIDLibNamePack &src);
	ListLayerIDLibNamePack	&operator+=(const ListLayerIDLibNamePack &src);
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

	ListPageLayerIDLibName(void)	{	Page=0;	Layer=0;	ID=0;	LibID=0;	}
	ListPageLayerIDLibName(const ListPageLayerIDLibName &src);

	ListPageLayerIDLibName	&operator=(const ListPageLayerIDLibName &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListPageLayerIDLibNamePack : public NPListPack<ListPageLayerIDLibName>
{
public:
	ListPageLayerIDLibNamePack(void){}
	ListPageLayerIDLibNamePack(const ListPageLayerIDLibNamePack &src);

	ListPageLayerIDLibNamePack	&operator= (const ListPageLayerIDLibNamePack &src);
	ListPageLayerIDLibNamePack	&operator+=(const ListPageLayerIDLibNamePack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
//========================================================================

class	ListPhasePageLayer : public NPList<ListPhasePageLayer>
{
public:
	int32		Phase;
	int32		Page;
	int32		Layer;

	ListPhasePageLayer(void)							{	Phase=0;	Page=0;	Layer=0;	}
	ListPhasePageLayer(int phase ,int page ,int layer)	{	Phase=phase;	Page=page;	Layer=layer;	}
	ListPhasePageLayer(const ListPhasePageLayer &src);

	ListPhasePageLayer	&operator=(const ListPhasePageLayer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListPhasePageLayerPack : public NPListPack<ListPhasePageLayer>
{
public:
	ListPhasePageLayerPack(void){}
	ListPhasePageLayerPack(const ListPhasePageLayerPack &src);

	ListPhasePageLayerPack	&operator=(const ListPhasePageLayerPack &src);
	ListPhasePageLayerPack	&operator+=(const ListPhasePageLayerPack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsInclude(int phase ,int page,int layer);
	void	Add		(int phase ,int page ,int layer);
	void	Merge	(int phase ,int page ,int id);
	void	Merge	(const ListPhasePageLayerPack &src);
	void	Merge	(const ListPhasePageLayer &src);

	void	GetPhaseList(IntList &PhaseList);
	void	GetPageLayer(int Phase,ListPageLayerPack &PageLayer);
};

//========================================================================
class	ListPhasePageLayerItem : public NPList<ListPhasePageLayerItem>
{
public:
	struct HPLIStruct
	{
		int32		Phase;
		int32		Page;
		int32		Layer;
		int32		ItemID;
	}Data;

	ListPhasePageLayerItem(void){	Data.Phase=0;	Data.Page=0;	Data.Layer=0;	Data.ItemID=0;	}
	ListPhasePageLayerItem(int phase ,int page ,int layer,int itemID)	{	Data.Phase=phase;	Data.Page=page;	Data.Layer=layer;	Data.ItemID=itemID;	}
	ListPhasePageLayerItem(const ListPhasePageLayerItem &src);

	ListPhasePageLayerItem	&operator=(const ListPhasePageLayerItem &src);
	bool	operator==(const ListPhasePageLayerItem &src)	const;
	bool	operator!=(const ListPhasePageLayerItem &src)	const;
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListPhasePageLayerItemPack : public NPListPack<ListPhasePageLayerItem>
{
public:
	ListPhasePageLayerItemPack(void){}
	ListPhasePageLayerItemPack(const ListPhasePageLayerItemPack &src);

	ListPhasePageLayerItemPack	&operator=(const ListPhasePageLayerItemPack &src);
	ListPhasePageLayerItemPack	&operator+=(const ListPhasePageLayerItemPack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsInclude(int phase ,int page,int layer,int itemID);
	void	Add		(int phase ,int page ,int layer,int itemID);
	void	Merge	(int phase ,int page ,int layer,int itemID);
	void	Merge	(const ListPhasePageLayerItemPack &src);
	void	Merge	(const ListPhasePageLayerItem &src);

	void	GetPhaseList(IntList &PhaseList);
	void	GetPageLayer(int Phase,ListPageLayerPack &PageLayer);
};

//========================================================================

class	ListPhasePageLayerLibID : public NPList<ListPhasePageLayerLibID>
{
public:
	struct HPLIStruct
	{
		int32		Phase;
		int32		Page;
		int32		Layer;
		int32		LibID;
	}Data;
	IntList			ItemIDs;

	ListPhasePageLayerLibID(void){	Data.Phase=0;	Data.Page=0;	Data.Layer=0;	Data.LibID=0;	}
	ListPhasePageLayerLibID(int phase ,int page ,int layer,int libID)	{	Data.Phase=phase;	Data.Page=page;	Data.Layer=layer;	Data.LibID=libID;	}
	ListPhasePageLayerLibID(const ListPhasePageLayerLibID &src);

	ListPhasePageLayerLibID	&operator=(const ListPhasePageLayerLibID &src);
	bool	operator==(const ListPhasePageLayerLibID &src)	const;
	bool	operator!=(const ListPhasePageLayerLibID &src)	const;
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ListPhasePageLayerLibIDPack : public NPListPack<ListPhasePageLayerLibID>
{
public:
	ListPhasePageLayerLibIDPack(void){}
	ListPhasePageLayerLibIDPack(const ListPhasePageLayerLibIDPack &src);

	ListPhasePageLayerLibIDPack	&operator=(const ListPhasePageLayerLibIDPack &src);
	ListPhasePageLayerLibIDPack	&operator+=(const ListPhasePageLayerLibIDPack &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsInclude(int phase ,int page,int layer,int libID);
	void	Add		(int phase ,int page ,int layer,int libID);
	void	Merge	(int phase ,int page ,int layer,int libID);
	void	Merge	(ListPhasePageLayerLibIDPack &src);

	void	GetPhaseList(IntList &PhaseList);
	void	GetPageLayer(int Phase,ListPageLayerPack &PageLayer);
};

//========================================================================



#endif
 