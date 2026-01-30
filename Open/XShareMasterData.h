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

#if	!defined(XShareMasterData_H)
#define	XShareMasterData_H

#include "NListComp.h"
#include "XServiceForLayers.h"
#include "XTypeDef.h"

class	ShareMasterFromSource : public NPListSaveLoad<ShareMasterFromSource>,public ServiceForLayers
{
public:
	int	SourceMachineID;
	int	Dx;
	int	Dy;
	double	MultiplyLayer[256];

	ShareMasterFromSource(LayersBase *base);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ShareMasterDestination : public NPListPackSaveLoad<ShareMasterFromSource> ,public ServiceForLayers
								,public NPList<ShareMasterDestination>
{
public:
	int		DestinationMachineID;

	ShareMasterDestination(LayersBase *base);

	virtual	ShareMasterFromSource	*Create(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	void	SortItems(void);
	ShareMasterFromSource	*GetSource(int machineID);
};

class	ShareMasterContainer : public NPListPack<ShareMasterDestination>,public ServiceForLayers
{
public:
	ShareMasterContainer(LayersBase *base);

	ShareMasterDestination	*FindDestination(int DestMachineID);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

#endif