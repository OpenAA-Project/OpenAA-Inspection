/*
 * Copyright (C) 2026
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

#if	!defined(XSERVICEFORLAYERS_H)
#define	XSERVICEFORLAYERS_H
#include <QString>
#include "XTypeDef.h"
#include "XRememberer.h"

class	LayersBase;
class	ParamGlobal;
class	ParamComm;
class	ParamGUI;
class	EntryPointBase;
class	QObject;

class	ServiceForLayers:public ControlRememberer
{
	LayersBase	*Base;
public:
	explicit	ServiceForLayers(LayersBase *base):ControlRememberer(base),Base(base){}
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
