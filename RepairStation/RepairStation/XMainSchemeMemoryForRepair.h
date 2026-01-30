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