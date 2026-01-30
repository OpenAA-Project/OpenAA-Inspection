/*
 * Copyright (C) 2020
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

#if	!defined(PropertyResultBinderPacket_h)
#define	PropertyResultBinderPacket_h


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResultBinder.h"
#include"XFlexAreaImageBuffer.h"
#include"NListComp.h"
#include "XRuleOfBinderCommon.h"

class	CmdCreateResultBinderManualPacket : public GUIDirectMessage
{
public:
	IntList		LayerList;
	FlexArea	Area;
	VectorLineBase	*Vect;
	double		ZoomRate;
	CmdCreateResultBinderManualPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdDoubleClickedPacket : public GUIDirectMessage
{
public:
	double		ZoomRate;
	int			GlobalX ,GlobalY;
	CmdDoubleClickedPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateDrawAttrPacket : public GUIDirectMessage
{
public:
	ResultBinderDrawAttr	*Attr;
	CmdCreateDrawAttrPacket(LayersBase *base):GUIDirectMessage(base){	Attr=NULL;	}
};


//----------------------------------------------------------------------------------

class	GUICmdAddAreaManual : public GUICmdPacketBase
{
public:
	int			ResultBinderItemID;
	FlexArea	Area;
	int			RuleType;

	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Page;
	int		Layer;
	int		ItemID;
	ConditionListContainer	ConditionData;
	QString	ItemName;
	QString	RuleName;
	QString	RuleRemark;
	bool	Conclusion;
	bool	NGOthers;

	GUICmdAddAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//----------------------------------------------------------------------------------

class	GUICmdChangeAreaManual : public GUICmdPacketBase
{
public:
	int			ResultBinderItemID;
	int			RuleType;

	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Page;
	int		Layer;
	int		ItemID;
	QString	ItemName;
	ConditionListContainer	ConditionData;
	QString	RuleName;
	QString	RuleRemark;
	bool	Conclusion;
	int		RuleID;
	bool	NGOthers;
	bool	DeleteMode;

	GUICmdChangeAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//----------------------------------------------------------------------------------


class	GUICmdReqItemList : public GUICmdPacketBase
{
public:
	int	LibType;
	int	Layer;

	GUICmdReqItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckItemList : public GUICmdPacketBase
{
public:
	int					Layer;
	ItemIDNameContainer	Data;

	GUICmdAckItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

//----------------------------------------------------------------------------------
class	GUICmdReqResultBinderItemAdd : public GUICmdPacketBase
{
public:
	int		GlobalPage;
	QString	ItemName;

	GUICmdReqResultBinderItemAdd(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckResultBinderItemAdd : public GUICmdPacketBase
{
public:
	int	ItemID;

	GUICmdAckResultBinderItemAdd(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};


class	GUICmdReqResultBinderItemInfo : public GUICmdPacketBase
{
public:
	int		ItemID;

	GUICmdReqResultBinderItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendResultBinderItemInfo : public GUICmdPacketBase
{
public:
	QString	ItemName;

	GUICmdSendResultBinderItemInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqResultBinderItemMod : public GUICmdPacketBase
{
public:
	QString	ItemName;
	int		ItemID;

	GUICmdReqResultBinderItemMod(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqResultBinderItemEnum : public GUICmdPacketBase
{
public:
	GUICmdReqResultBinderItemEnum(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckResultBinderItemEnum : public GUICmdPacketBase
{
public:
	ItemIDNameContainer		Items;

	GUICmdAckResultBinderItemEnum(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdReqResultBinderItemDel: public GUICmdPacketBase
{
public:
	int	ItemID;

	GUICmdReqResultBinderItemDel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//----------------------------------------------------------------------------------

class	GUICmdReqRuleOnXY : public GUICmdPacketBase
{
public:
	double	ZoomRate;
	int		PosX ,PosY;
	int		ResultBinderItemID;

	GUICmdReqRuleOnXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckRuleOnXY : public GUICmdPacketBase
{
public:
	int			ResultBinderItemID;
	int			RuleType;

	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Page;
	int		Layer;
	int		ItemID;
	ConditionListContainer	ConditionData;
	QString	ItemName;
	QString	RuleName;
	QString	RuleRemark;
	bool	Conclusion;
	int		RuleID;
	bool	NGOthers;
	int		InputNumb;

	GUICmdAckRuleOnXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//----------------------------------------------------------------------------------

class	GUICmdReqAddConnection : public GUICmdPacketBase
{
public:
	int		ParentRuleID;
	int		ChildRuleID;
	int		ResultBinderItemID;

	GUICmdReqAddConnection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//----------------------------------------------------------------------------------

class	GUICmdReqClosedConnectionOnXY : public GUICmdPacketBase
{
public:
	double	ZoomRate;
	int		PosX ,PosY;
	int		ResultBinderItemID;

	GUICmdReqClosedConnectionOnXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckClosedConnectionOnXY : public GUICmdPacketBase
{
public:
	int		ParentRuleID;
	int		ChildRuleID;

	GUICmdAckClosedConnectionOnXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
//----------------------------------------------------------------------------------

class	GUICmdDelConnection : public GUICmdPacketBase
{
public:
	int		ParentRuleID;
	int		ChildRuleID;
	int		ResultBinderItemID;

	GUICmdDelConnection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif