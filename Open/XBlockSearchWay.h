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