/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XOutlineOffset.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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