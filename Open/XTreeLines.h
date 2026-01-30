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

#if	 !defined(XTREELINES_H)
#define XTREELINES_H

#include "XTypeDef.h"
#include "NList.h"
#include <QIODevice>
#include <QImage>
#include <QPainter>
#include "XVector.h"

class	TreePointList;

class	TreeLine :  public NPList<TreeLine>,public NPListPack<TreePointList>
{
public:
	TreeLine(void){}
	//TreeLine(TreeLine &src);
	//TreeLine(const TreeLine &src);

	void	DeleteNoise(int NoiseDot);

	TreeLine	&operator=(TreeLine &src);
	TreeLine	&operator=(const TreeLine &src);
	TreeLine	&operator=(VectorLineBase &src);
	TreeLine	&operator+=(TreeLine &src);

	double	GetMaxLength(void)						const;
	double	GetTotalLength(void)					const;
	double	GetDistance(double x ,double y)			const;
	bool	GetXY(int &x1,int &y1,int &x2,int &y2)	const;
	void	MoveTo(int dx ,int dy);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	bool	IsNull(void)							const;

	virtual	void	Draw(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate);
	virtual	void	DrawCircleOnLine(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate,int R);
};

class	TreePointList : public NPList<TreePointList>
{
protected:
  #pragma	pack(push,1)
	int32	X,Y;
	BYTE	Level;	//0:Ineffective
  #pragma	pack(pop)
	TreeLine	OtherNode;
public:
	TreePointList(void)						{	X=0;	Y=0;	Level=0xFF;		}
	TreePointList(const TreePointList &src);
	TreePointList(int32 x, int32 y):X(x),Y(y){	Level=0xFF;	}

	int		GetX(void)	const	{	return X;	}
	int		GetY(void)	const	{	return Y;	}
	void	SetXY(int x, int y)	{	X=x;	Y=y;	}
	TreeLine	&GetOtherNode(void){	return OtherNode;	}

	int		GetLevel(void)	const	{	return Level;	}
	void	SetLevel(int b)			{	Level=b;		}

	TreePointList	&operator=(const TreePointList &src);
	TreePointList	&operator=(const VectorItemBase &src);
	double	GetMaxLength(void)		const;
	double	GetTotalLength(void)	const;
	bool	GetXY(int &x1,int &y1,int &x2,int &y2)	const;
	void	MoveTo(int dx ,int dy);
	virtual	void	Draw(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate);
	virtual	void	DrawCircleOnLine(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate ,int R);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};


class	TreesContainer : public NPListPack<TreeLine>
{
public:
	TreesContainer(void){}

	TreesContainer	&operator=(const TreesContainer &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	double	GetTotalLength(void)					const;
	bool	GetXY(int &x1,int &y1,int &x2,int &y2)	const;
	void	MoveTo(int dx ,int dy);

	bool	IsNull(void)	const;

	virtual	void	Draw(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate);
	virtual	void	DrawCircleOnLine(QImage &IData ,QPainter &PData ,QRgb Col,int MovX ,int MovY ,double ZoomRate,int R);
};

#endif