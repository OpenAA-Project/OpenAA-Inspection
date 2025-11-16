/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\XMainSchemeMemoryForRepair.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#if	!defined(XMAINSCHEMEMEMORYFORREPAIR)
#define	XMAINSCHEMEMEMORYFORREPAIR

#include "XMainSchemeMemory.h"

class ImageBufferForRepair : public ImageBuffer
{
public:
    ImageBufferForRepair(int idcode=ImageBufferOther);
    ImageBufferForRepair(int idcode ,int xlen ,int ylen ,bool noRelease=false);
    ImageBufferForRepair(BYTE **data,int idcode ,int xlen ,int ylen ,bool noRelease=false);

    ~ImageBufferForRepair(void);

    bool    Load(QIODevice *f);

	void	SetResolution(int Res)	{	Resolution=Res;		}
	int		GetResolution()			{	return(Resolution);	}

private:
	int		Resolution;
};

#endif
