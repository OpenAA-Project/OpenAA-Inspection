/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XServiceForLayers.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XSERVICEFORLAYERS_H)
#define	XSERVICEFORLAYERS_H
#include <QString>
#include "XTypeDef.h"

class	LayersBase;
class	ParamGlobal;
class	ParamComm;
class	ParamGUI;
class	EntryPointBase;
class	QObject;

class	ServiceForLayers
{
	LayersBase	*Base;
public:
	explicit	ServiceForLayers(LayersBase *base):Base(base){}
	virtual	~ServiceForLayers(void){	Base=NULL;	}

	void			Copy(const ServiceForLayers *src){	Base=src->Base;	}
	void			SetLayersBase(LayersBase *base){	Base=base;	}
	LayersBase		*GetLayersBase(void)		const	{	return Base;	}
	LayersBase		*GetTreeTopLayersBase(void)	const;
	EntryPointBase	*GetEntryPoint(void)		const;
	int				GetDotPerLine(int page)		const;
	int				GetMaxLines(int page)		const;
	int				GetPageNumb(void)			const;
	int				GetPhaseNumb(void)			const;
	int				GetLayerNumb(int page)		const;
	bool			IsValid(int page ,int layer)const;

	int				GetCountAllMasterBuff(void)		const;
	int				GetCountOnlyMasterBuff(void)	const;
	int				GetCountDispatchMasterBuff(void)const;

	ParamGlobal		*GetParamGlobal(void)		const;
	ParamComm		*GetParamComm(void)			const;
	ParamGUI		*GetParamGUI(void)			const;
	int				GetCurrentShadowLevel(void)	const;	//Top:0

	void			InstallOperationLog(QObject *window);			

	//----------- Unit-------------
	bool	IsUnitMode(void);
	double	TransformPixelToUnit	(int Page,double pixel);
	double	TransformUnitToPixel	(int Page,double unit);
	QString	TransformPixelToUnitStr	(int Page,double pixel);
	QString	GetUnitStr(double unit);
	double	TransformPixelToUnitSquare	(int Page,double pixel);
	double	TransformUnitToPixelSquare	(int Page,double unit);
	QString	TransformPixelToUnitSquareStr(int Page,double pixel);
	QString	GetUnitSquareStr(double unit);

};



#endif

