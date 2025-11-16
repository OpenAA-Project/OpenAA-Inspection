#pragma once

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlignmentBlock.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XAlignmentBlockCommon.h"
#include <QColor>

class	AlignmentBlockImagePanel;
class	CmdAlignmentBlockDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	AlignmentBlockImagePanel	*ImagePanelPoint;

	CmdAlignmentBlockDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdAlignmentBlockDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdSendAddManualAlignmentBlock : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			LibID;

	GUICmdSendAddManualAlignmentBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedAlignmentBlock : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	IntList		LayerList;

	GUICmdSendModifySelectedAlignmentBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdAutoGenerateAlignmentBlock : public GUICmdPacketBase
{
public:
	int		LibID ;

	GUICmdAutoGenerateAlignmentBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentBlockItemList : public GUICmdPacketBase
{
public:

	GUICmdReqAlignmentBlockItemList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdAckAlignmentBlockItemList : public GUICmdPacketBase
{
public:
	AlignmentBlockItemListContainer	Items;

	GUICmdAckAlignmentBlockItemList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

