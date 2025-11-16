/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoAlignment\XAutoAlignmentCommon.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XAUTOALIGNMENTCOMMON_H
#define XAUTOALIGNMENTCOMMON_H

#include "NList.h"
#include <QString>

class	AASheetInfoList : public NPList<AASheetInfoList>
{
public:
	int		ID;
	int		PicoShift;
	bool	CreatedManual;

	AASheetInfoList(void){}
	AASheetInfoList(int id ,int picosheet,bool createdManual);

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	AASheetInfos : public NPListPack<AASheetInfoList>
{
public:
	AASheetInfos(void){}
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	AAListAttr : public NPList<AAListAttr>
{
public:
	int		LibID;
	bool	CreatedManual;

	AAListAttr(void){}

	AAListAttr	&operator=(AAListAttr &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	AAListAttrContainer : public NPListPack<AAListAttr>
{
public:
	AAListAttrContainer(void){}

	void	Add(int libID, bool createdManual);
	AAListAttrContainer	&operator=(AAListAttrContainer &src);
	bool	IsInclude(int libID ,bool createdManual);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};


#endif

