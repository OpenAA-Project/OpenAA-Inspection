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


#if	!defined(PROPERTYALIGNMENTPACKET_H)
#define	PROPERTYALIGNMENTPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XPacketAlignment.h"
#include "XAlignment.h"


//===========================================================================

class	GUICmdReqAlignmentAreaList : public GUICmdPacketBase
{
public:
	GUICmdReqAlignmentAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentAreaList : public GUICmdPacketBase
{
public:
	AlignmentAreaListPack	Area;

	GUICmdSendAlignmentAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeAreaList(int localPage,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdReqAlignmentPointList : public GUICmdPacketBase
{
public:
	int	GlobalPage;
	int	Layer;
	int	Number;

	GUICmdReqAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentPointList : public GUICmdPacketBase
{
public:
	AlignmentPointListPack	Points;

	GUICmdSendAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakePointList(LayersBase *PBase ,int Layer ,int Number);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	GUICmdReqAlignmentPutArea : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	FlexArea	Area;
	QString		AreaName;
	XAlignmentArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdReqAlignmentPutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentPutPoint : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	int			AreaID;
	FlexArea	PointArea;
	WORD		MoveDot;		
    WORD		Threshold;
	bool		AlignmentOnOutline;	//�֊s�ňʒu���킹�����Ƃ�true

	GUICmdReqAlignmentPutPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentModifyPoint : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	int			AreaID;
	int			ItemID;
	WORD		MoveDot;		
    WORD		Threshold;
	bool		AlignmentOnOutline;	//�֊s�ňʒu���킹�����Ƃ�true

	GUICmdReqAlignmentModifyPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentPutGroup : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	int			AreaID;
	int			GroupNumber;
	FlexArea	GroupArea;

	GUICmdReqAlignmentPutGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqAlignmentAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;

	GUICmdReqAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendAlignmentAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	XAlignmentArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdSendAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	Make(int localPage,int layer,int areaID,LayersBase *Base);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqModifyAlignmentAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	bool		DeleteMode;
	XAlignmentArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdReqModifyAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdSetActiveAreas : public GUICmdPacketBase
{
public:
	ReqAlignmentAreaListPack	ActiveAreas;
	QString						InstForm;

	GUICmdSetActiveAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	CmdSetActiveAreas : public GUIDirectMessage
{
public:
	ReqAlignmentAreaListPack	ActiveAreas;

	CmdSetActiveAreas(LayersBase *base):GUIDirectMessage(base){}
	CmdSetActiveAreas(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddArea: public GUIDirectMessage
{
public:
	CmdAddArea(LayersBase *base):GUIDirectMessage(base){}
	CmdAddArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//===========================================================================

class	GUICmdClickAreaButton : public GUICmdPacketBase
{
public:
	QString	InstName;

	GUICmdClickAreaButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdClickPointButton : public GUICmdPacketBase
{
public:
	QString	InstName;

	GUICmdClickPointButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdClickGroupButton : public GUICmdPacketBase
{
public:
	QString	InstName;

	GUICmdClickGroupButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif