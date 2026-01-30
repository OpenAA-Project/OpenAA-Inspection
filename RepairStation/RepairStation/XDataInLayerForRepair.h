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



#ifndef XDATAINLAYERFORREPAIR_H
#define XDATAINLAYERFORREPAIR_H

#include "XDataInLayer.h"

class DataInLayerForRepair : public DataInLayer
{
public:
	DataInLayerForRepair(EntryPointBase	*pEntryPoint ,DataInPage *parent);
	~DataInLayerForRepair(void);

	void	Initial(void);

	void	SetResolution(int Res)	{	Resolution=Res;		}
	int		GetResolution()			{	return(Resolution);	}

private:
	int		Resolution;
};

class DataInPageForRepair : public DataInPage
{
public:
    DataInPageForRepair(int Page ,PageDataInOnePhase	*parent);
    ~DataInPageForRepair(void);

    void    Initial(void);
//    void    Release(void);

	void	SetResolution(int Res)	{	Resolution=Res;		}
	int		GetResolution()			{	return(Resolution);	}

private:
	int		Resolution;
};

class	PageDataInOnePhaseForRepair : public PageDataInOnePhase
{
public:
	PageDataInOnePhaseForRepair(void);
	~PageDataInOnePhaseForRepair(void);

	void	InitialCreate(LayersBase *Base ,bool EnabledImageMemoryAllocation=true);

	void	SetResolution(int Res)	{	Resolution=Res;		}
	int		GetResolution()			{	return(Resolution);	}

private:
	int		Resolution;
};

class LayersBaseForRepair : public LayersBase
{
	Q_OBJECT

public:
    LayersBaseForRepair(void);
    ~LayersBaseForRepair(void);

	void	InitialCreatePages(EntryPointBase *pEntryPoint);

	void	SetResolution(int Res)	{	Resolution=Res;		}
	int		GetResolution()			{	return(Resolution);	}

private:
	int		Resolution;
};

#endif // XDATAINLAYERFORREPAIR_H