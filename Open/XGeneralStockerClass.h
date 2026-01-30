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

#pragma once
#include <QtGui>
#include <QVariant>
#include <QIODevice>
#include <QLibrary>

#include "XTypeDef.h"

class	LayersBase;
class	GeneralStocker;
class	GeneralStockerContainer;
class	LanguagePackage;
class	GUIDirectMessage;
class	ResultInspection;
struct	PropertyGeneralStocker;
class	ListPhasePageLayerPack;
class	ExecuteInitialAfterEditInfo;
class	GuiAdditionalDatabase;
class	SpecifiedBroadcaster;


class	GeneralStockerItemBase :public IdentifiedClass
{
public:
	GeneralStockerItemBase(void){}
	virtual	~GeneralStockerItemBase(void){}

	virtual	void	InitialAfterParamLoaded(void)	{}
	virtual	bool	MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return true;	}

	virtual	bool	Save(QIODevice *f)	{	return true;	}
	virtual	bool	Load(QIODevice *f)	{	return true;	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v){}
};
