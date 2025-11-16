/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XFilterClass.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XFILTERCLASS_H)
#define	XFILTERCLASS_H

#include <QIODevice>
#include "XTypeDef.h"
#include "XParamBase.h"
#include "XServiceForLayers.h"

class	LayersBase;
class	DataInPage;
class	ImageBuffer;
class	GUIDirectMessage;
class	FilterInstanceList;

class	FilterClassBase : public ParamBase
						 ,public IdentifiedClass
						 ,public ServiceForLayers
{
	FilterInstanceList	*Holder;
	int				LoadedDLLVersion;
public:
	explicit	FilterClassBase(LayersBase *base)
					:ServiceForLayers(base)
					{	Holder=NULL;	LoadedDLLVersion=-1;	}

	void	SetPaernt(FilterInstanceList *p);
	int		GetDLLVersion(void)	const;

	int		GetPage(void)		const;
	int		GetPhaseCode(void)	const;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	;
	virtual	bool	Reallocate(int newLayerNumb)						;

	int		GetDotPerLine(void)		const;
	int		GetMaxLines(void)		const;
	DataInPage *GetPageData(void)	const;

	void	SetLoadedDLLVersion(int d)			{	LoadedDLLVersion=d;			}
	int		GetLoadedDLLVersion(void)	const	{	return LoadedDLLVersion;	}

	virtual	void	ExecuteBeforeScan	(void){}
	virtual	ExeResult	ExecuteInitialAfterEdit	(void)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteStartByInspection(void)	{	return _ER_true;	}
	virtual	ExeResult	ExecutePreAlignment		(void)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteAlignment		(void)	{	return _ER_true;	}
	virtual	ExeResult	ExecutePreProcessing	(void)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteProcessing		(void)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteProcessingRevived(void)	{	return _ER_true;	}
	virtual	ExeResult	ExecutePostProcessing	(void)	{	return _ER_true;	}

	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
};

#endif