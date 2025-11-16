/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterSmoothing\FilterSmoothing.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef FILTERSMOOTHING_H
#define FILTERSMOOTHING_H

#include "XFilterClass.h"
#include "XDLLType.h"

class	ImageBuffer;

class	FilterSmoothingClass : public FilterClassBase
{
public:
	ImageBuffer **TmpImage;
	int			AllocatedLayerCount;
	int	Length;
	int	MethodValue;

	FilterSmoothingClass(LayersBase *base);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);

	virtual	QString	GetDataText(void){	return "Smoothing";	}
	virtual	QString	GetDefaultFileName(void){	return "FilterSmoothing.dat";	}
};

#endif // FILTERSMOOTHING_H
