/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTreeMaster\TreeMasterPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(TREEMASTERPACKET_H)
#define	TREEMASTERPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XTreeMaster.h"
#include "NListComp.h"

class	GUICmdAddTreeMaster : public GUICmdPacketBase
{
public:
	int		TMItemID;
	QString	CatName;
	int		MasterCode;
	QString MasterName;
	bool	AlertMark;

	GUICmdAddTreeMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetAlertTreeMaster : public GUICmdPacketBase
{
public:
	int		TMItemID;
	int		MasterCode;
	bool	AlertMark;

	GUICmdSetAlertTreeMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqMaxTMItemID : public GUICmdPacketBase
{
public:

	GUICmdReqMaxTMItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckMaxTMItemID : public GUICmdPacketBase
{
public:
	int	TMItemID;

	GUICmdAckMaxTMItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdAddTreeMasterArea : public GUICmdPacketBase
{
public:
	int			TMItemID;
	int			MasterCode;
	QString		CatName;
	QString		MasterName;
	FlexArea	Area;
	QColor		TreeMasterColor;
	int			Selection;
	double		ThreShape;
	double		ThreColor;
	int			SearchDot;

	GUICmdAddTreeMasterArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdTreeMasterDrawEnd :public GUIDirectMessage
{
public:
	FlexArea	GlobalArea;

	CmdTreeMasterDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdTreeMasterColor :public GUIDirectMessage
{
public:
	QColor	TreeMasterColor;

	CmdTreeMasterColor(LayersBase *base):GUIDirectMessage(base){}
};

class GUICmdCopyTreeMasterItem : public GUICmdPacketBase
{
public:
	int MasterSrc;
	int MasterDst;

	GUICmdCopyTreeMasterItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class GUICmdSetCategoryName : public GUICmdPacketBase
{
public:
	QString CatName;
	int MasterCode;

	GUICmdSetCategoryName(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class GUICmdRemoveItem : public GUICmdPacketBase
{
public:
	int MasterCode;
	GUICmdRemoveItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class GUICmdSelectItem : public GUICmdPacketBase
{
public:
	int MasterCode;
	GUICmdSelectItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	TreeMasterList : public NPList<TreeMasterList>
{
public:
	int		Page;
	int		x1,y1,x2,y2;
	int		ItemID;
	QString	CatName;
	int		MasterCode;
	QString MasterName;
	bool	AlertMask;

	TreeMasterList(void){}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
	TreeMasterList	&operator=(TreeMasterList &src);
};

class	TreeMasterListForPacketPack: public NPListPack<TreeMasterList>
{
public:
	TreeMasterListForPacketPack(void){}

	TreeMasterList	*FindByItemID(int TMItemID);
	TreeMasterList *FindByMasterCode(int MasterCode);
	void decreaseID(int BaseID);
	TreeMasterListForPacketPack	&operator+=(TreeMasterListForPacketPack &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};


class	GUICmdReqTreeMasterList : public GUICmdPacketBase
{
public:
	GUICmdReqTreeMasterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendTreeMasterList : public GUICmdPacketBase
{
public:
	TreeMasterListForPacketPack	TreeMasterInfo;

	GUICmdSendTreeMasterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeTreeMasterList(int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================
class	TreeMasterResultList : public NPListSaveLoad<TreeMasterResultList>
{
public:
	int		Page;
	int		ItemID;
	QString	CatName;
	int		MasterCode;
	double	ResultE;

	TreeMasterResultList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	TreeMasterResultList	&operator=(TreeMasterResultList &src);
};

class	TreeMasterResultListForPacketPack: public NPListPackSaveLoad<TreeMasterResultList>
{
public:
	TreeMasterResultListForPacketPack(void){}

	TreeMasterResultList	*FindByItemID(int TMItemID);
	virtual	TreeMasterResultList	*Create(void)	{	return new TreeMasterResultList();	}
};

class	CmdTreeReqSelectedMasterCode :public GUIDirectMessage
{
public:
	int		SelectedMasterCode;

	CmdTreeReqSelectedMasterCode(LayersBase *base):GUIDirectMessage(base){}
};

//=======================================================================================

class	GUICmdReqLoadMasterImage : public GUICmdPacketBase
{
public:
	int		MasterCode;

	GUICmdReqLoadMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
