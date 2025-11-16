/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyLinePattern\XLinePatternPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XLinePatternPACKET_H
#define XLinePatternPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XIntClass.h"
#include "NListComp.h"
#include "XLinePatternInspection.h"

class	LinePatternDrawAttr;

class AddLinePacket: public GUIDirectMessage
{
public:
	VectorLineBase	*Vector;
	IntList			LayerList;
	AddLinePacket(LayersBase *base):GUIDirectMessage(base){}
	AddLinePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLinePatternDrawEnd : public GUIDirectMessage
{
public:
	FlexArea		Area;
	IntList			LayerList;
	CmdLinePatternDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSendAddManualBlock : public GUICmdPacketBase
{
public:
	int			LibID;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdSendAddManualBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendAddManualLinePattern : public GUICmdPacketBase
{
public:
	QByteArray			BItem;
	VectorLineBase		*Vector;
	IntList		LayerList;
	int			SelectedLibID;
	QString		ItemName;
	FlexArea	Area;		//For MarkArea

	GUICmdSendAddManualLinePattern(LayersBase *Base ,const QString& EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendAddManualLinePattern(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIReqLinePatternListForPacketPack: public GUICmdPacketBase
{
public:

	GUIReqLinePatternListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIAckLinePatternListForPacketPack: public GUICmdPacketBase
{
public:
	LinePatternListForPacketPack	Data;

	GUIAckLinePatternListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUIReqGenerateLinePatternItems: public GUICmdPacketBase
{
public:
	IntList	LibList;
	IntList	LayerList;

	GUIReqGenerateLinePatternItems(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqSetButtonMode : public GUICmdPacketBase
{
public:
	enum	ButtonMode
	{
		_LibraryTest	=1
		,_CreateBlock	=2
	}Mode;
	QString	InstForm;

	GUICmdReqSetButtonMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdReqSetButtonMode : public GUIDirectMessage
{
public:
	GUICmdReqSetButtonMode::ButtonMode	Mode;

	CmdReqSetButtonMode(LayersBase *base):GUIDirectMessage(base){}
	CmdReqSetButtonMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


//==========================================================================
class	BlockInfoList : public NPList<BlockInfoList>
{
public:
	int		LibID;
	IntList	BlockCount;

	int		GetLibID(void){		return LibID;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	BlockInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(BlockCount.Save(f)==false)
		return false;
	return true;
}
inline	bool	BlockInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(BlockCount.Load(f)==false)
		return false;
	return true;
}



class	GUICmdReqBlockInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendBlockInfoList : public GUICmdPacketBase
{
public:
	NPListPack<BlockInfoList>	BlockInfos;

	GUICmdSendBlockInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Make(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqRemoveAllOriginal : public GUICmdPacketBase
{
public:
	int32		GeneratedOrigin;

	GUICmdReqRemoveAllOriginal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdChangeLinePatternThreshold : public GUICmdPacketBase
{
public:
	int			LinePatternLibID;
	QByteArray	InfosData;

	GUICmdChangeLinePatternThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif