/*
 * Copyright (C) 2021
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

#if	!defined(XALIGNOUTLINE_H)
#define	XALIGNOUTLINE_H

#include "XFlexAreaImage.h"
#include "XServiceForLayers.h"

class	XAlignment;

class	VectorOutlineNode : public FlexAreaImage ,public NPList<VectorOutlineNode>
{
	double	AddS,AddS2;
	double	Add2S,Add2S2;	//�Ԉ������l
	BYTE	XSep,YSep;
	float	Vx,Vy;	//�}�b�`���O�����̒P�ʃx�N�g��
	int32	Px,Py;	//�}�b�`���O�P�ʃx�N�g���̊��_���W�i�\���p�j

public:
	double	CurrentVLen;

	VectorOutlineNode(void);

	void	Initial(void);
	bool	CheckValidity(void);
	double	Match(ImageBuffer &Img ,int dx ,int dy, double VLen);
	double	MatchSep(ImageBuffer &Img ,int dx ,int dy, double VLen);

	VectorOutlineNode	&operator=(VectorOutlineNode &src);
	virtual	void	Draw(QImage &pnt,QRgb c ,int movx ,int movy ,double ZoomRate);
	virtual	void	Draw(int dx ,int dy,QImage &pnt,QRgb c ,int movx ,int movy ,double ZoomRate);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	SetPxy(int px,int py);
	void	SetVxy(double vx,double vy);
};

class	VectorAlignmentItem : public NPListPack<VectorOutlineNode> , public ServiceForLayers
{
	XAlignment	*Parent;
public:
	VectorAlignmentItem(XAlignment *parent,LayersBase *Base):ServiceForLayers(Base),Parent(parent){}

	bool	Set(FlexArea &Area
				,ImageBuffer &Img
				,int	DivCount=8
				,int	OutlineWidth=4);

	void	Initial(void);
	VectorAlignmentItem	&operator=(VectorAlignmentItem &src);
	void	SetRefereneFrom(LayersBase *Base,VectorAlignmentItem *src,int OffsetX,int OffsetY);

	double	Match(ImageBuffer &Img 
				,int &dx ,int &dy
				,int SearchArea=20
				,int EachSearchDot=4);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	virtual	void	Draw(QImage &pnt ,QRgb c, int movx ,int movy ,double ZoomRate);
	virtual	void	Draw(int dx ,int dy,QImage &pnt ,QRgb c, int movx ,int movy ,double ZoomRate);

private:

	double	MatchInside(ImageBuffer &Img
						,int dx ,int dy
						,int EachSearchDot
						,double VList[]);
	double	MatchSepInside(ImageBuffer &Img
						,int dx ,int dy
						,int EachSearchDot
						,double VList[]);
};

#endif