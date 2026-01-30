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

#if	!defined(XDustReducerAI_H)
#define	XDustReducerAI_H

#include "NListComp.h"
#include "XTypeDef.h"


enum	JudgeDust{
	 _Judge_None=0
	,_Judge_OK	=1
	,_Judge_NG	=2
};


class	DustRegList : public NPListSaveLoad<DustRegList>
{
	double	A[3];
	double	AA[3];
public:
	int32	ID;
	BYTE	*Pattern[3];
	int16	LayerNumb;
	int16	XLen;
	int16	YLen;
	QString	Comment;
	JudgeDust	JudgeDustValue;

	explicit	DustRegList(void);
	~DustRegList(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	void	CalcInitial(void);

	void	Set(BYTE *CurrentPattern[3],int LayerNumb ,int XLen ,int YLen ,const QString &Comment,JudgeDust OkNg);
	double	Calc(BYTE *SrcPattern[3],int SrcLayerNumb ,int SrcXLen ,int SrcYLen,IntList &AdaptedLayer);
};

class	DustRegListPointer : public NPList<DustRegListPointer>
{
public:
	DustRegList	*Point;
	double		Result;

	explicit	DustRegListPointer(DustRegList *p):Point(p){}

	virtual	int	Compare(DustRegListPointer &src)	override;
};

class	DustRegContainer : public NPListPackSaveLoad<DustRegList>
{
public:
	NPListPack<DustRegListPointer>	DustRegListPointerContainer;


	explicit	DustRegContainer(void){}

	int		GetMaxID(void);
	virtual	DustRegList	*Create(void)	{	return new DustRegList();	}
	DustRegList			*FindByID(int ID);
	DustRegListPointer	*FindPointer(int ID);

	DustRegListPointer	*Calc(BYTE *CurrentPattern[3] ,int LayerNumb ,int XLen ,int YLen,IntList &AdaptedLayer,JudgeDust Filter);
};

#endif