/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPacketAlignmentProjection.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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