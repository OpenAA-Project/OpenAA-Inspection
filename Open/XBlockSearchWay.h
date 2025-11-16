/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBlockSearchWay.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XBOCKSEARCHWAY_H)
#define	XBOCKSEARCHWAY_H

#include "NList.h"
#include "XYCross.h"

class   SearchWay : public NPList<SearchWay>
{
  public:
    int SearchLen;
    NPListPack<XYClass> SWay;

    SearchWay(void);

    void    SetSearchWay(int searchlen);
    void    SetSearchWay(struct L3SwingProcess sw[] ,int swnumb);
    void    ToTop(XYClass *d);
};

class   SearchWayList
{
  public:
    NPListPack<SearchWay>   FreeWay;
    SearchWay               SWWay[100];
    SearchWay               SWWay2;

    SearchWayList(void);

    SearchWay   *SearchFreeWay(int searchlen);
    void    Clear(void){    FreeWay.RemoveAll();   }
};


#endif
