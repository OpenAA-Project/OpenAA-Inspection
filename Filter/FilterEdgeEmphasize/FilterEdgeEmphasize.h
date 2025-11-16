/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterEdgeEmphasize\FilterEdgeEmphasize.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef FILTEREDGEEMPHASIZE_H
#define FILTEREDGEEMPHASIZE_H

#include "XFilterClass.h"
#include "XDLLType.h"

class	FilterEdgeEmphasize : public FilterClassBase
{
	short	FilterTable[100][100];
	BYTE	**SourceBuffer;
	BYTE	*SourcePointer[100];
	int		SourceYLen;

public:
	int		Radius;
	double	Strength;

	FilterEdgeEmphasize(LayersBase *base);
	virtual	~FilterEdgeEmphasize(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool	Reallocate(int newLayerNumb)						override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Initial(void)		override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;

	virtual	QString	GetDataText(void)		override{	return "EdgeEnphasize";	}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterEdgeEmphasize.dat";	}
};


#endif // FILTEREDGEEMPHASIZE_H
