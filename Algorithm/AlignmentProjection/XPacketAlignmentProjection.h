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

#if	!defined(XPACKETAlignmentProjection_H)
#define	XPACKETAlignmentProjection_H

#include <QIODevice>
#include "NList.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XDirectComm.h"
#include "NListComp.h"
#include "XYCross.h"


class	AlignmentProjectionShiftList: public NPListSaveLoad<AlignmentProjectionShiftList>
{
public:
	int		GlobalPage;
	int		ItemID;
	bool	CalcDone;
	double	ShiftX,ShiftY;
    double	MasterX,MasterY;

	AlignmentProjectionShiftList(void){	CalcDone=false;	ShiftX=0;	ShiftY=0;	MasterX=0;	MasterY=0;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};
class	AlignmentProjectionShiftContainer : public NPListPackSaveLoad<AlignmentProjectionShiftList>
{
public:
	AlignmentProjectionShiftContainer(void)	{}
	virtual	AlignmentProjectionShiftList	*Create(void){	return new AlignmentProjectionShiftList();	}
};

//==================================================================================

class	AlignmentProjectionDrawAttr : public AlgorithmDrawAttr
{
public:
	AlignmentProjectionDrawAttr(void)
		: AlgorithmDrawAttr(Qt::green,100,Qt::yellow,100,Qt::red,100)
	{}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

//==================================================================================

class	CmdReqAlignmentProjectionShiftPacket : public GUIDirectMessage
{
public:		
	IntList					*ItemIDPoint;
	AlignmentProjectionShiftContainer	*ShiftDataPoint;

	CmdReqAlignmentProjectionShiftPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentProjectionShiftPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif