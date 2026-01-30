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

#if	!defined(XOUTLINEOFFSET_H)
#define	XOUTLINEOFFSET_H

#include "XTypeDef.h"
#include <QIODevice>
#include "XServiceForLayers.h"

class	LayersBase;

typedef	struct	_OutlineOffsetInPage
{
	int32	Dx,Dy;
}OutlineOffsetInPage;

class	OutlineOffsetInBlobPage
{
	int32		OutlineOffsetInPageDimNumb;
	OutlineOffsetInPage	*OutlineOffsetInPageDim;
public:
	explicit	OutlineOffsetInBlobPage(void);
	virtual	~OutlineOffsetInBlobPage(void);

	void	Initial(int PageCount);

	void	SetData(int page ,OutlineOffsetInPage &Data);
	OutlineOffsetInPage	GetData(int page)	const;
	int		GetPageCount(void)	const	{	return OutlineOffsetInPageDimNumb;	}

	void	Copy(const OutlineOffsetInBlobPage &src);
	OutlineOffsetInBlobPage	&operator=(const OutlineOffsetInBlobPage &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	OutlineOffsetInBlob : public ServiceForLayers
{
	int32		OutlineOffsetInPhaseDimNumb;
	OutlineOffsetInBlobPage		*OutlineOffsetInPhaseDim;
public:
	OutlineOffsetInBlob(LayersBase *base);
	virtual	~OutlineOffsetInBlob(void);

	void	Initial(void);
	void	Reallocate(void);

	void	SetData(int phase ,int page ,OutlineOffsetInPage &Data);
	OutlineOffsetInPage	GetData(int phase,int page)	const;
	int		GetPageCount(int phase)	const;
	int		GetPhaseCount(void)		const	{	return OutlineOffsetInPhaseDimNumb;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

#endif