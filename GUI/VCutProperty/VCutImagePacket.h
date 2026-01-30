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


#if	!defined(VCUTIMAGEPACKET_H)
#define	VCUTIMAGEPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XVCutInspection.h"

class	GUICmdAddVCutInspectionArea : public GUICmdPacketBase
{
public:
	VectorLineBase	*Vector;
	int		ThresholdShift;
	double	ThresholdLevel;
	int		ThresholdLength;
	int		LibID;

	GUICmdAddVCutInspectionArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	VCutInspectionList : public NPList<VCutInspectionList>
{
public:
	int		Page;
	int		x1,y1,x2,y2;
	int		ThresholdShift;
	double	ThresholdLevel;
	int		ThresholdLength;

	VCutInspectionList(void){}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	VCutInspectionListForPacketPack: public NPListPack<VCutInspectionList>
{
public:
	VCutInspectionListForPacketPack(void){}

	VCutInspectionListForPacketPack	&operator+=(VCutInspectionListForPacketPack &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};


class	GUICmdReqVCutInspectionList : public GUICmdPacketBase
{
public:
	GUICmdReqVCutInspectionList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendVCutInspectionList : public GUICmdPacketBase
{
public:
	VCutInspectionListForPacketPack	VCutInfo;

	GUICmdSendVCutInspectionList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeVCutList(int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif