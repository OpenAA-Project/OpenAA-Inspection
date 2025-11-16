/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XVector.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XVECTOR_H)
#define	XVECTOR_H

#include <QIODevice>
#include <QPainter>
#include "NList.h"
#include "XTypeDef.h"

class	FlexArea;
class	TransformBase;

class	VectorItemBase : public NPList<VectorItemBase>
{
public:
	VectorItemBase(void){}
	~VectorItemBase(void){}

	virtual	VectorItemBase	*Clone(void)	=0;
	virtual VectorItemBase	*CreateItem(void)	=0;
	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;
	virtual	double	GetX(void)		const	=0;
	virtual	double	GetY(void)		const	=0;
	virtual	int		GetXInt(void)	const	=0;
	virtual	int		GetYInt(void)	const	=0;
	virtual	void	MoveTo(double dx ,double dy){}
	virtual	void	Copy(VectorItemBase *src)	=0;
	virtual	bool	IsEqual(VectorItemBase *src)	const;
	virtual	void	Transform(TransformBase & Param)	=0;
};

class	VectorLineBase : public NPList<VectorLineBase>
{
protected:
	NPListPack<VectorItemBase>	Items;
public:
	VectorLineBase(void){}
	VectorLineBase(VectorLineBase &src);
	virtual	~VectorLineBase(void){}

	virtual	VectorLineBase	*Clone(void)	=0;
	virtual	int	GetID(void)	const	=0;
	virtual	VectorItemBase	*CreateItem(void)	=0;
	virtual	VectorLineBase	*CreateDup(void);
	virtual	VectorLineBase	*CreateEmpty(void)	=0;
	static	VectorLineBase	*Create(int ID);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	void	AppendItemBase(VectorItemBase *item){	Items.AppendList(item);	}
	virtual	void	AppendMoveBase(VectorLineBase *base);
	virtual	void	RemoveItem(VectorItemBase *item)	{	Items.RemoveList(item);	}
	virtual	void	MoveTo(double dx ,double dy);

	VectorItemBase	*GetFirstItem(void)	{	return Items.GetFirst();	}
	VectorItemBase	*GetLastItem(void)	{	return Items.GetLast();		}
	VectorItemBase	*GetItemAt(int n)	{	return Items[n];			}

	VectorLineBase	&operator=(VectorLineBase &src);
	bool			operator==(VectorLineBase &src)	const;
	bool			operator!=(VectorLineBase &src)	const{	return !operator==(src);	}

	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate){}
	virtual	bool	CheckOverlapRectangle(double x1 ,double y1 ,double x2 ,double y2)	const{	return true;	}
	virtual	bool	CheckOverlap(FlexArea &area)	const;
	virtual	double	GetDistance(int x ,int y);
	virtual	bool	IsNull(void)	const	{	return (Items.GetFirst()==NULL)?true:false;	}
	virtual	bool	ClipArea(double x1, double y1 ,double x2, double y2){	return false;	}	//if clipped, return true
	virtual	void	Clear(void)	{	Items.RemoveAll();	}

	virtual	bool	GetXY(int &x1,int &y1,int &x2,int &y2)	const;
	virtual	bool	GetXY(double &x1,double &y1,double &x2,double &y2)	const;
	virtual	bool	GetCenter(int &cx ,int &cy)				const;
	virtual	bool	GetCenter(double &cx ,double &cy)		const;
	virtual	bool	DrawImage(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate);
	bool	DrawShift(int dx,int dy ,QImage &pnt ,QRgb Col	,double ZoomRate ,int movx ,int movy);

	double	GetLength(void);
	void	MakeMap(BYTE **MaskBitmap ,int XByte ,int YLen);
	virtual	void	Transform(TransformBase &Param);
};

//==============================================================

class		VectorItemInt : public VectorItemBase
{
	int	X,Y;
public:
	VectorItemInt(void)	{	X=0;	Y=0;	}
	VectorItemInt(const VectorItemInt &src);
	explicit	VectorItemInt(int x, int y):X(x),Y(y){}

	virtual	VectorItemBase	*Clone(void)	override;
	virtual VectorItemBase	*CreateItem(void)	override{	return new VectorItemInt();	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	double	GetX(void)		const	override	{	return X;	}
	virtual	double	GetY(void)		const	override	{	return Y;	}
	virtual	int		GetXInt(void)	const	override	{	return X;	}
	virtual	int		GetYInt(void)	const	override	{	return Y;	}
	virtual	void	MoveTo(double dx ,double dy)	override{	X+=dx;	Y+=dy;	}
	virtual	void	Copy(VectorItemBase *src)		override;
	void	SetXY(double x, double y){	X=x;	Y=y;	}
	virtual	void	Transform(TransformBase &Param)	override;

	VectorItemInt	&operator=(const VectorItemInt &src);
};

class	VectorLineInt : public VectorLineBase 
{
public:
	VectorLineInt(void){}
	VectorLineInt(const VectorLineInt &src);

	virtual	VectorLineBase	*Clone(void)	override;
	VectorLineInt	&operator=(const VectorLineInt &src);
	virtual	int	GetID(void)		const	override		{	return 1;	}
	virtual	VectorItemBase	*CreateItem(void)	override{	return new VectorItemInt();	}
	virtual	VectorLineBase	*CreateEmpty(void)	override{	return new VectorLineInt();	}
	virtual	bool	CheckOverlapRectangle(double x1 ,double y1 ,double x2 ,double y2)	const	override;
	virtual	bool	IsNull(void)	const	override;
	virtual	bool	ClipArea(double x1, double y1 ,double x2, double y2)		override;
	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate)	override;
};

//==============================================================

class		VectorItemDouble : public VectorItemBase
{
	double	X,Y;
public:
	VectorItemDouble(void)	{	X=0;	Y=0;	}
	VectorItemDouble(const VectorItemDouble &src);
	explicit	VectorItemDouble(double x, double y):X(x),Y(y){}

	virtual	VectorItemBase	*Clone(void)	override;
	virtual VectorItemBase	*CreateItem(void)	override{	return new VectorItemDouble();	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	double	GetX(void)		const	override	{	return X;	}
	virtual	double	GetY(void)		const	override	{	return Y;	}
	virtual	int		GetXInt(void)	const	override	{	return X;	}
	virtual	int		GetYInt(void)	const	override	{	return Y;	}
	virtual	void	MoveTo(double dx ,double dy)	override{	X+=dx;	Y+=dy;	}
	virtual	void	Copy(VectorItemBase *src)		override;
	void	SetXY(double x, double y){	X=x;	Y=y;	}
	virtual	void	Transform(TransformBase &Param)	override;

	VectorItemDouble	&operator=(const VectorItemDouble &src);
};

class	VectorLineDouble : public VectorLineBase 
{
public:
	VectorLineDouble(void){}
	VectorLineDouble(const VectorLineDouble &src);

	virtual	VectorLineBase	*Clone(void)	override;
	VectorLineDouble	&operator=(const VectorLineDouble &src);
	virtual	int	GetID(void)		const	override		{	return 1;	}
	virtual	VectorItemBase	*CreateItem(void)	override{	return new VectorItemDouble();	}
	virtual	VectorLineBase	*CreateEmpty(void)	override{	return new VectorLineDouble();	}
	virtual	bool	CheckOverlapRectangle(double x1 ,double y1 ,double x2 ,double y2)	const	override;
	virtual	bool	IsNull(void)	const	override;
	virtual	bool	ClipArea(double x1, double y1 ,double x2, double y2)		override;
	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate)	override;
};

//==============================================================

class		VectorItemVDouble : public VectorItemBase
{
	double	X,Y;
	double	Vx,Vy;	//法線ベクトル
public:
	VectorItemVDouble(void){	X=0.0;	Y=0.0;	Vx=0.0;	Vy=0.0;	}
	VectorItemVDouble(const VectorItemVDouble &src);

	virtual	VectorItemBase	*Clone(void)	override;
	virtual VectorItemBase	*CreateItem(void)	override{	return new VectorItemVDouble();	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	double	GetX(void)		const	override{	return X;	}
	virtual	double	GetY(void)		const	override{	return Y;	}
	virtual	int		GetXInt(void)	const	override{	return X;	}
	virtual	int		GetYInt(void)	const	override{	return Y;	}

	virtual	void	MoveTo(double dx ,double dy)	override	{	X+=dx;	Y=dy;	}
	virtual	void	Copy(VectorItemBase *src)		override;
	VectorItemVDouble	&operator=(const VectorItemVDouble &src);
	virtual	void	Transform(TransformBase &Param)	override;
};

class	VectorLineVDouble : public VectorLineBase 
{
public:
	VectorLineVDouble(void){}
	VectorLineVDouble(const VectorLineVDouble &src);

	virtual	VectorLineBase	*Clone(void)	override;
	virtual	int	GetID(void)	const	override	{	return 2;	}
	virtual	VectorItemBase	*CreateItem(void)	override{	return new VectorItemVDouble();	}
	virtual	VectorLineBase	*CreateEmpty(void)	override{	return new VectorLineVDouble();	}
	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate)override{}
};

//==============================================================
class		VectorItemArc : public VectorItemBase
{
	double	X,Y;
public:
	VectorItemArc(void)	{	X=0;	Y=0;	}
	VectorItemArc(const VectorItemArc &src);
	explicit	VectorItemArc(double x, double y):X(x),Y(y){}

	virtual	VectorItemBase	*Clone(void)	override;
	virtual VectorItemBase	*CreateItem(void)	override{	return new VectorItemArc();	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	double	GetX(void)		const	override{	return X;	}
	virtual	double	GetY(void)		const	override{	return Y;	}
	virtual	int		GetXInt(void)	const	override{	return X;	}
	virtual	int		GetYInt(void)	const	override{	return Y;	}
	virtual	void	MoveTo(double dx ,double dy)	override{	X+=dx;	Y+=dy;	}
	virtual	void	Copy(VectorItemBase *src)		override;
	void	SetXY(double x, double y){	X=x;	Y=y;	}
	VectorItemArc	&operator=(const VectorItemArc &src);
	virtual	void	Transform(TransformBase &Param)	override;
};

class	VectorLineArc : public VectorLineBase 
	//３点で円弧を表す
	//最初の点は始点
	//２番目は中間点（ちょうど中央でなくても構わない）
	//３番目の点は終点
{
public:
	VectorLineArc(void){}

	virtual	VectorLineBase	*Clone(void)	override;
	void	SetPoints(double x1, double y1 ,double x2, double y2 ,double x3, double y3);
	virtual	int	GetID(void)		const	override{	return 3;	}
	virtual	VectorItemBase	*CreateItem(void)	override{	return new VectorItemArc();	}
	virtual	VectorLineBase	*CreateEmpty(void)	override{	return new VectorLineArc();	}
	virtual	bool	CheckOverlapRectangle(double x1 ,double y1 ,double x2 ,double y2)	const	override;
	virtual	bool	IsNull(void)	const	override;
	virtual	bool	ClipArea(double x1, double y1 ,double x2, double y2)	override;
	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate)override;

	void	SetArc(	 double Cx, double Cy ,double R
					,double StartS ,double EndS);
	bool	GetArc(	 double &Cx, double &Cy ,double &R
					,double &StartS ,double &EndS);
};

//==============================================================
class		VectorItemEllipse : public VectorItemBase
{
	double	X,Y;
public:
	VectorItemEllipse(void)	{	X=0;	Y=0;	}
	VectorItemEllipse(const VectorItemEllipse &src);
	explicit	VectorItemEllipse(double x, double y):X(x),Y(y){}

	virtual	VectorItemBase	*Clone(void)	override;
	virtual VectorItemBase	*CreateItem(void)	override	{	return new VectorItemEllipse();	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	double	GetX(void)		const	override{	return X;	}
	virtual	double	GetY(void)		const	override{	return Y;	}
	virtual	int		GetXInt(void)	const	override{	return X;	}
	virtual	int		GetYInt(void)	const	override{	return Y;	}
	virtual	void	MoveTo(double dx ,double dy)	override	{	X+=dx;	Y+=dy;	}
	virtual	void	Copy(VectorItemBase *src)		override;
	void	SetXY(double x, double y){	X=x;	Y=y;	}
	VectorItemEllipse	&operator=(const VectorItemEllipse &src);
	virtual	void	Transform(TransformBase &Param)	override;
};

class	VectorLineEllipse : public VectorLineBase 
	//４点で楕円を表す
	//４点はＸ軸方向の上頂点、下頂点、Ｙ軸方向の右頂点、左頂点
{
public:
	VectorLineEllipse(void){}

	virtual	VectorLineBase	*Clone(void)	override;
	void	SetPoints(double x1, double y1 ,double x2, double y2 ,double x3, double y3 ,double x4, double y4);
	virtual	int	GetID(void)		const	override{	return 4;	}
	virtual	VectorItemBase	*CreateItem(void)	override{	return new VectorItemEllipse();	}
	virtual	VectorLineBase	*CreateEmpty(void)	override{	return new VectorLineEllipse();	}
	virtual	bool	CheckOverlapRectangle(double x1 ,double y1 ,double x2 ,double y2)	const	override;
	virtual	bool	IsNull(void)	const	override;
	virtual	bool	ClipArea(double x1, double y1 ,double x2, double y2)	override;
	virtual	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate)override;

	void	SetEllipse(	double Cx, double Cy ,double Rx ,double Ry);
	bool	GetEllipse(	double &Cx, double &Cy ,double &Rx ,double &Ry);
};

#endif