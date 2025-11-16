/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyLearning\XLearningPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XLEARNINGPACKET_H)
#define	XLEARNINGPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XLearning.h"
#include "XTypeDef.h"

class	GUICmdLearningAddFile : public GUICmdPacketBase
{
public:
	QString			FileName;
	int				Index;

	GUICmdLearningAddFile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLearningDelFile : public GUICmdPacketBase
{
public:
	int32			IndexNumber;

	GUICmdLearningDelFile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqStoredFileList : public GUICmdPacketBase
{
public:
	int MasterCode;
	int LotAutoCount;

	GUICmdReqStoredFileList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckStoredFileList : public GUICmdPacketBase
{
public:
	LearningFileListContainer	List;

	GUICmdAckStoredFileList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqPickedFileList : public GUICmdPacketBase
{
public:

	GUICmdReqPickedFileList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){		return true;	}
	virtual	bool	Save(QIODevice *f){		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckPickedFileList : public GUICmdPacketBase
{
public:
	LearningFileListContainer	List;

	GUICmdAckPickedFileList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdChangeLearningList : public GUICmdPacketBase
{
public:
	int	SelectedListNumber;

	GUICmdChangeLearningList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	AddLearningArea :  public GUIDirectMessage
{
public:
	FlexArea	Area;

	AddLearningArea(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdAddLearningArea : public GUICmdPacketBase
{
public:
	bool		Ok;			//true:ãïïÒîrèú		false:ÇmÇfî≠ïÒ
    int32		NGLevel;	//0:Most important NG 1,2,3...lighter
	FlexArea	Area;

	GUICmdAddLearningArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqLearningAreaListContainer : public GUICmdPacketBase
{
public:

	GUICmdReqLearningAreaListContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckLearningAreaListContainer : public GUICmdPacketBase
{
public:
	LearningAreaListContainer	List;

	GUICmdAckLearningAreaListContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif