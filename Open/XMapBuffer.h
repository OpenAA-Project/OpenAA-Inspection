/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XMapBuffer.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XMapBufferH
#define XMapBufferH
//---------------------------------------------------------------------------
#include "NList.h"
#include "XTypeDef.h"
#include "XPointer.h"
#include <QIODevice>

class	ConstMapBuffer;

class	MapBufferBase
{
public:
	enum EnumMapFormat
	{
		_BitMap		=0
		,_ByteMap	=1
		,_WordMap	=2
		,_DWordMap	=4
	};
	
protected:
	EnumMapFormat	MapFormat;
	BYTE			**Map;
	int				XByte;
	int				YLen;

public:
	MapBufferBase(void);
	explicit	MapBufferBase(int xbyte ,int ylen);
	explicit	MapBufferBase(int xlen ,int ylen ,EnumMapFormat e);
	explicit	MapBufferBase(BYTE **bitmap,int xbyte ,int ylen,EnumMapFormat e=MapBufferBase::_BitMap);	//delete bitmap in this instance
	MapBufferBase(const MapBufferBase &src);
	virtual	~MapBufferBase(void);

	int	GetXByte(void)	const			{	return XByte;	}
	int	GetXLen(void)	const 			;
	int	GetYLen(void)	const 			{	return YLen;	}
	EnumMapFormat	GetFormat(void)	{	return MapFormat;	}

	void	Copy(const MapBufferBase &src);
	bool	CopyPartial(const MapBufferBase &src ,int SrcX1 ,int SrcY1 ,int SrcX2 ,int SrcY2
						,int DstX1 ,int DstY1);

	void		Set  (BYTE **bitmap,int xbyte ,int ylen ,EnumMapFormat e=MapBufferBase::_BitMap);
	void		SetXY(BYTE **bitmap,int xlen  ,int ylen ,EnumMapFormat e=MapBufferBase::_BitMap);
	void		Alloc(int xbyte ,int ylen,EnumMapFormat e=MapBufferBase::_BitMap);
	
	MapBufferBase	&operator&=(const MapBufferBase &src);
	MapBufferBase	&operator|=(const MapBufferBase &src);
	MapBufferBase	&operator^=(const MapBufferBase &src);

	void	Not(void);
	void	ClearAll(void);
	void	SetAll(void);
	void	AndNot(const MapBufferBase &src);
	void	MoveFrom(MapBufferBase &src);

	bool	IsValid(void)			{	return (Map==NULL || XByte==0 || YLen==0)?false:true;	}
	bool	IsEmpty(void);		//Check in all data
	int		GetBit(int x,int y)	const	{	return (0<=x && x<(XByte<<3) && 0<=y && y<YLen)?GetBmpBit(Map,x,y):0;	}
	void	SetBit(int x,int y)			{	if(0<=x && x<(XByte<<3) && 0<=y && y<YLen){	SetBmpBit1(Map,x,y);	}	}
	void	ClearBit(int x,int y)		{	if(0<=x && x<(XByte<<3) && 0<=y && y<YLen){	SetBmpBit0(Map,x,y);	}	}

	BYTE	GetByte(int x,int y)const	{	return (0<=x && x<(XByte<<3) && 0<=y && y<YLen)?Map[y][x]:0;	}
	void	SetByte(int x,int y ,BYTE d){	if(0<=x && x<(XByte<<3) && 0<=y && y<YLen){	Map[y][x]=d;	}	}

	WORD	GetWord(int x,int y)const	{	return (0<=x && x<(XByte<<3) && 0<=y && y<YLen)?((WORD *)Map[y])[x]:0;	}
	void	SetWord(int x,int y ,WORD d){	if(0<=x && x<(XByte<<3) && 0<=y && y<YLen){	((WORD *)Map[y])[x]=d;	}	}

	DWORD	GetDWord(int x,int y)const	{	return (0<=x && x<(XByte<<3) && 0<=y && y<YLen)?((DWORD *)Map[y])[x]:0;	}
	void	SetDWord(int x,int y,DWORD d){	if(0<=x && x<(XByte<<3) && 0<=y && y<YLen){	((DWORD *)Map[y])[x]=d;	}	}

	BYTE	*GetY(int y)			const{	return (0<=y && y<YLen)?Map[y]:NULL;	}
	BYTE	*GetYDirectly(int y)	const{	return Map[y];	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	MapBuffer : public MapBufferBase
{
public:
	MapBuffer(void){}
	explicit	MapBuffer(int xbyte ,int ylen)
		:MapBufferBase(xbyte,ylen){}
	explicit	MapBuffer(int xlen ,int ylen,EnumMapFormat e)
		:MapBufferBase(xlen,ylen,e){}
	explicit	MapBuffer(BYTE **bitmap,int xbyte ,int ylen,EnumMapFormat e=MapBufferBase::_BitMap)
		:MapBufferBase(bitmap,xbyte,ylen,e){}
	MapBuffer(const MapBufferBase &src)
		:MapBufferBase(src){}

	MapBuffer	&operator=(MapBuffer &src)			{	Copy(src);	return *this;	}
	MapBuffer	&operator=(const MapBuffer &src)	{	Copy(src);	return *this;	}
	BYTE	*operator[](int y)	const{	return (BYTE *)Map[y];	}
	BYTE	**GetBitMap(void)	const{	return (BYTE **)Map;		}

};

class MapBufferList : public NPList<MapBufferList>
{
	MapBuffer	*MapPointer;
public:
	explicit	MapBufferList(MapBuffer *p) : MapPointer(p){}
	MapBufferList(void)	:MapPointer(NULL){}
	~MapBufferList(void);

	MapBuffer	*GetMapBuffer(void)	const	{	return MapPointer;	}
	void	Set(MapBuffer *p)				{	MapPointer=p;	}
};

class MapBufferListContainer : public NPListPack<MapBufferList>
{
public:
	MapBufferListContainer(void){}
	~MapBufferListContainer(void){}

	void	BindOr(MapBuffer &Map);
};

class	ConstMapBuffer : public MapBufferBase
{
public:
	ConstMapBuffer(void){}
	explicit	ConstMapBuffer(int xbyte ,int ylen)
		:MapBufferBase(xbyte,ylen){}
	explicit	ConstMapBuffer(int xlen ,int ylen,EnumMapFormat e)
		:MapBufferBase(xlen,ylen,e){}
	explicit	ConstMapBuffer(BYTE **bitmap,int xbyte ,int ylen,EnumMapFormat e=MapBufferBase::_BitMap)
		:MapBufferBase(bitmap,xbyte,ylen,e){}	//delete bitmap in this instance
	ConstMapBuffer(const MapBufferBase &src)
		:MapBufferBase(src){}

	ConstMapBuffer	&operator=(const ConstMapBuffer &src){	Copy(src);	return *this;	}
	const	BYTE	*operator[](int y)	const{	return (const	BYTE *)Map[y];	}
	const	BYTE	**GetBitMap(void)	const{	return (const	BYTE **)Map;		}
};

class ConstMapBufferList : public NPList<ConstMapBufferList>
{
	ConstMapBuffer	*MapPointer;
public:
	explicit	ConstMapBufferList(ConstMapBuffer *p) : MapPointer(p){}
	ConstMapBufferList(void)	:MapPointer(NULL){}
	~ConstMapBufferList(void);

	ConstMapBuffer	*GetMapBuffer(void)	const	{	return MapPointer;	}
	void	Set(ConstMapBuffer *p)				{	MapPointer=p;	}
};

class ConstMapBufferListContainer : public NPListPack<ConstMapBufferList>
{
public:
	ConstMapBufferListContainer(void){}
	~ConstMapBufferListContainer(void){}

	void	BindOr(ConstMapBuffer &Map);
	void	BindOr(MapBuffer &Map);

	const BYTE	**GetBitMap(int n){
		ConstMapBufferList	*m=GetItem(n);
		if(m!=NULL){
			ConstMapBuffer	*mp=m->GetMapBuffer();
			if(mp!=NULL){
				return mp->GetBitMap();
			}
		}
		return NULL;
	}
};

#endif
