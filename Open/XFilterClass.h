/*
 * Copyright (C) 2025
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