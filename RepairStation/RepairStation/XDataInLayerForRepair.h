/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\XDataInLayerForRepair.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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
