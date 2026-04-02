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

//---------------------------------------------------------------------------

#ifndef XFifoClassH
#define XFifoClassH
//---------------------------------------------------------------------------

#include <QMutex>
#include "NList.h"
#include "XTypeDef.h"

class	NFifoIntLeaf : public NPList<NFifoIntLeaf>
{
  public:
    int   Data;

    NFifoIntLeaf(void);
	NFifoIntLeaf(const NFifoIntLeaf &src);
    ~NFifoIntLeaf(void);

	NFifoIntLeaf	&operator=(const NFifoIntLeaf &src);
    void    SetData(int data);
    int     PopData(void);
};

class   FifoIntPacket
{
    NPListPack<NFifoIntLeaf>    LData;
    QMutex            CSection;

  public:
    FifoIntPacket(void);
	FifoIntPacket(const FifoIntPacket &src);
    virtual ~FifoIntPacket(void);

	FifoIntPacket	&operator=(FifoIntPacket &src);

    void    Push(int data);
    int     Pop(void);
};

class FifoBuffer
{
    BYTE    *Data;
    int     WPoint;
    int     RPoint;
    int     Len;
    int     AllocatedLen;

public:
	FifoBuffer(int MaxLen=4096);
	virtual ~FifoBuffer(void);

    bool    Push(BYTE *buff ,int len);
    int     Pop(void);
    int     Pop(char *buff ,int maxlen);
    int     GetSize(void);
};

#endif