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