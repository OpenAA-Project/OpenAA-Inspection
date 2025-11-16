/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPacketAlignmentFlexArea.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XPACKETAlignmentFlexArea_H)
#define	XPACKETAlignmentFlexArea_H

#include <QIODevice>
#include "NList.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XDirectComm.h"
#include "NListComp.h"
#include "XYCross.h"
#include "XGeneralFunc.h"

class	AlignmentFlexAreaShiftList: public NPListSaveLoad<AlignmentFlexAreaShiftList>
{
public:
	int		GlobalPage;
	int		ItemID;
	bool	CalcDone;
	double	ShiftX,ShiftY;
    double	MasterX,MasterY;

	AlignmentFlexAreaShiftList(void){	CalcDone=false;	ShiftX=0;	ShiftY=0;	MasterX=0;	MasterY=0;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};
class	AlignmentFlexAreaShiftContainer : public NPListPackSaveLoad<AlignmentFlexAreaShiftList>
{
public:
	AlignmentFlexAreaShiftContainer(void)	{}
	virtual	AlignmentFlexAreaShiftList	*Create(void){	return new AlignmentFlexAreaShiftList();	}
};
//--------------------------------------------------------------------------------------------------------
class	ReqAlignmentFlexAreaAreaList : public NPList<ReqAlignmentFlexAreaAreaList>
{
public:
	int		AreaID;
	int		GlobalPage;

	ReqAlignmentFlexAreaAreaList(void){}

	ReqAlignmentFlexAreaAreaList	&operator=(ReqAlignmentFlexAreaAreaList &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ReqAlignmentFlexAreaAreaListPack : public NPListPack<ReqAlignmentFlexAreaAreaList>
{
public:
	ReqAlignmentFlexAreaAreaListPack(void){}

	ReqAlignmentFlexAreaAreaListPack &operator=(ReqAlignmentFlexAreaAreaListPack &src);
	ReqAlignmentFlexAreaAreaListPack &operator+=(ReqAlignmentFlexAreaAreaListPack &src);
	bool	LayerExists(int page);
	bool	ExistsAreaID(int areaID);
	bool	Exists(int page ,int areaID);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	GetAlignmentFlexAreaConclusion : public GUIDirectMessage
{
public:
	double	m[6];
	//	TargetX=m[0]*MasterX + m[1]*MasterY + m[2]
	//	TargetY=m[3]*MasterX + m[4]*MasterY + m[5]
	GetAlignmentFlexAreaConclusion(LayersBase *base):GUIDirectMessage(base){}
	GetAlignmentFlexAreaConclusion(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdIsModeItemEditingPacket : public GUIDirectMessage
{
public:
	enum{
		_ItemMode			=0
		,_AreaMode			=1
		,_GroupMode			=2
		,_WholeMatchMode	=3
	}ItemMode;

	CmdIsModeItemEditingPacket(LayersBase *base):GUIDirectMessage(base)
			{	ItemMode=_ItemMode;	}
	CmdIsModeItemEditingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ItemMode=_ItemMode;	}
};

class	CmdGetCurrentAreaIDPacket: public GUIDirectMessage
{
public:
	int	AreaID;

	CmdGetCurrentAreaIDPacket(LayersBase *base):GUIDirectMessage(base)			{	AreaID=-1;	}
	CmdGetCurrentAreaIDPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	AreaID=-1;	}
};

//他のページのアラインメントポイントを取得
class	SlaveCommReqAlignmentFlexAreaPoint : public DirectCommPacketBase
{
public:
	int		AreaID;
	QString	AreaName;
	int		Layer;

	SlaveCommReqAlignmentFlexAreaPoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckAlignmentFlexAreaPoint : public DirectCommPacketBase
{
public:

	AlignmentFlexAreaShiftContainer	AlignmentFlexAreaPointData;

	SlaveCommAckAlignmentFlexAreaPoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	CmdReqAlignmentFlexAreaPointPacket : public GUIDirectMessage
{
public:
	int				AreaID;
	QString			AreaName;
	AlignmentFlexAreaShiftContainer	AlignmentFlexAreaPointData;

	CmdReqAlignmentFlexAreaPointPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentFlexAreaPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	SlaveCommReqAlignmentFlexAreaShift : public DirectCommPacketBase
{
public:
	int		Layer;
	IntList	ItemID;

	SlaveCommReqAlignmentFlexAreaShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckAlignmentFlexAreaShift : public DirectCommPacketBase
{
public:
	AlignmentFlexAreaShiftContainer	ShiftData;

	SlaveCommAckAlignmentFlexAreaShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	CmdReqAlignmentFlexAreaShiftPacket : public GUIDirectMessage
{
public:		
	IntList					*ItemIDPoint;
	AlignmentFlexAreaShiftContainer	*ShiftDataPoint;

	CmdReqAlignmentFlexAreaShiftPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentFlexAreaShiftPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateAreaInMaskingArea : public GUIDirectMessage
{
public:
	int				Priority;

	CmdCreateAreaInMaskingArea(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateAreaInMaskingArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==================================================================================

class	AlignmentFlexAreaDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	DrawGeneratedArea;
	bool	DrawOutlineArea;
	bool	DrawWholeMatch;
	bool	DrawBaseMatch;
	IntList	SelectedArea;	//Use for item view
	IntList	SelectWholeMatch;
	int		CurrentBaseMatchRow;

	QColor		ColorPickup;
	QColor		AlignmentFlexAreaColor0;
	QColor		AlignmentFlexAreaColor1;
	QColor		AlignmentFlexAreaColor2;
	QColor		AlignmentFlexAreaColor3;
	QColor		AlignmentFlexAreaColor4;
	QColor		AlignmentFlexAreaColor5;
	QColor		AlignmentFlexAreaColor6;
	QColor		AlignmentFlexAreaColor7;

	AlignmentFlexAreaDrawAttr(void):ServiceForLayers(NULL){}
	AlignmentFlexAreaDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	AlignmentFlexAreaDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel
				, QColor &AlignmentFlexAreaColor0
				, QColor &AlignmentFlexAreaColor1
				, QColor &AlignmentFlexAreaColor2
				, QColor &AlignmentFlexAreaColor3
				, QColor &AlignmentFlexAreaColor4
				, QColor &AlignmentFlexAreaColor5
				, QColor &AlignmentFlexAreaColor6
				, QColor &AlignmentFlexAreaColor7);

	void	Initial(void);

	AlignmentFlexAreaDrawAttr	&operator=(AlignmentFlexAreaDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	AlignmentFlexAreaDrawAttr	&AlignmentFlexAreaDrawAttr::operator=(AlignmentFlexAreaDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	DrawGeneratedArea			=src.DrawGeneratedArea	;
	DrawOutlineArea				=src.DrawOutlineArea	;
	DrawWholeMatch				=src.DrawWholeMatch		;
	DrawBaseMatch				=src.DrawBaseMatch		;
	SelectedArea				=src.SelectedArea		;
	SelectWholeMatch			=src.SelectWholeMatch	;
	CurrentBaseMatchRow			=src.CurrentBaseMatchRow;

	ColorPickup					=src.ColorPickup;
	AlignmentFlexAreaColor0		=src.AlignmentFlexAreaColor0;
	AlignmentFlexAreaColor1		=src.AlignmentFlexAreaColor1;
	AlignmentFlexAreaColor2		=src.AlignmentFlexAreaColor2;
	AlignmentFlexAreaColor3		=src.AlignmentFlexAreaColor3;
	AlignmentFlexAreaColor4		=src.AlignmentFlexAreaColor4;
	AlignmentFlexAreaColor5		=src.AlignmentFlexAreaColor5;
	AlignmentFlexAreaColor6		=src.AlignmentFlexAreaColor6;
	AlignmentFlexAreaColor7		=src.AlignmentFlexAreaColor7;
	return *this;
}
inline	bool	AlignmentFlexAreaDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,DrawGeneratedArea)==false)
		return false;
	if(::Save(f,DrawOutlineArea)==false)
		return false;
	if(::Save(f,DrawWholeMatch)==false)
		return false;
	if(::Save(f,DrawBaseMatch)==false)
		return false;
	if(::Save(f,CurrentBaseMatchRow)==false)
		return false;

	if(::Save(f,ColorPickup)==false)
		return false;
	if(SelectedArea.Save(f)==false)
		return false;
	if(SelectWholeMatch.Save(f)==false)
		return false;

	return true;
}
inline	bool	AlignmentFlexAreaDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,DrawGeneratedArea)==false)
		return false;
	if(::Load(f,DrawOutlineArea)==false)
		return false;
	if(::Load(f,DrawWholeMatch)==false)
		return false;
	if(::Load(f,DrawBaseMatch)==false)
		return false;
	if(::Load(f,CurrentBaseMatchRow)==false)
		return false;

	if(::Load(f,ColorPickup)==false)
		return false;
	if(SelectedArea.Load(f)==false)
		return false;
	if(SelectWholeMatch.Load(f)==false)
		return false;

	return true;
}
inline	ReqAlignmentFlexAreaAreaList	&ReqAlignmentFlexAreaAreaList::operator=(ReqAlignmentFlexAreaAreaList &src)
{
	AreaID		=src.AreaID;
	GlobalPage	=src.GlobalPage;

	return *this;
}
inline	bool	ReqAlignmentFlexAreaAreaList::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;

	return true;
}
inline	bool	ReqAlignmentFlexAreaAreaList::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;

	return true;
}

inline	ReqAlignmentFlexAreaAreaListPack &ReqAlignmentFlexAreaAreaListPack::operator=(ReqAlignmentFlexAreaAreaListPack &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
inline	ReqAlignmentFlexAreaAreaListPack &ReqAlignmentFlexAreaAreaListPack::operator+=(ReqAlignmentFlexAreaAreaListPack &src)
{
	for(ReqAlignmentFlexAreaAreaList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ReqAlignmentFlexAreaAreaList *b=new ReqAlignmentFlexAreaAreaList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}
inline	bool	ReqAlignmentFlexAreaAreaListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(ReqAlignmentFlexAreaAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
inline	bool	ReqAlignmentFlexAreaAreaListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		ReqAlignmentFlexAreaAreaList *a=new ReqAlignmentFlexAreaAreaList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

class	LibraryEfectivity : public NPList<LibraryEfectivity>
{
public:
	int32	LibID;
	bool	IncludedInMask;

	LibraryEfectivity(void);
	LibraryEfectivity(int libID ,bool mask):LibID(libID),IncludedInMask(mask){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	LibraryEfectivityContainer : public NPListPack<LibraryEfectivity>
{
public:
	LibraryEfectivityContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsIncluded(int LibID);
};

//他のスレーブで限定マスクでライブラリを使用しているかどうか
class	SlaveCommReqLibraryInMaskOfBlock : public DirectCommPacketBase
{
public:
	IntList	UsedLibraries;

	SlaveCommReqLibraryInMaskOfBlock(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckLibraryInMaskOfBlock : public DirectCommPacketBase
{
public:
	LibraryEfectivityContainer	UsedLibraries;

	SlaveCommAckLibraryInMaskOfBlock(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//================================================================================
//他のスレーブでWholeMatchのSAreaを転送
class	SlaveCommReqSAreaInWholeMatch : public DirectCommPacketBase
{
public:
	int		SImageNo;

	SlaveCommReqSAreaInWholeMatch(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckSAreaInWholeMatch : public DirectCommPacketBase
{
public:
	FlexAreaImageListCoeff	SArea;

	SlaveCommAckSAreaInWholeMatch(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif