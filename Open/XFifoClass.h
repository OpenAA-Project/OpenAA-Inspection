/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XFifoClass.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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




#endif
