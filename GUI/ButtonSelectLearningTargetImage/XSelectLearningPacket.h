#if	!defined(XSELECTLEARNINGPACKET_H)
#define	XSELECTLEARNINGPACKET_H


#include "XGUIPacketForDLL.h"
#include "NList.h"
#include <QIODevice>
#include <QString>
#include "XDataAlgorithm.h"
#include "XDateTime.h"

class	LearningImageList : public NPList<LearningImageList>
{
public:
	XDateTime	CreateTime;

	LearningImageList(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	LearningImageList	&operator=(LearningImageList &src);
};

class	LearningImageListContainer : public NPListPack<LearningImageList>
{
public:
	LearningImageListContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//--------------------------------------------------------------------------
class	GUICmdReqLearningStockerList : public GUICmdPacketBase
{
public:

	GUICmdReqLearningStockerList(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}	
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendLearningStockerList : public GUICmdPacketBase
{
public:
	LearningImageListContainer	Stocker;

	GUICmdSendLearningStockerList(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeData(int localPage);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//--------------------------------------------------------------------------

class	GUICmdReqSetLearningImage : public GUICmdPacketBase
{
public:
	XDateTime	CreatedTime;
	bool		Mastered;

	GUICmdReqSetLearningImage(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendSetLearningImage : public GUICmdPacketBase
{
public:
	int			LocalX1 ,LocalY1 ,LocalX2 ,LocalY2;

	GUICmdSendSetLearningImage(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//--------------------------------------------------------------------------

class	GUICmdReqDeleteLearningImage : public GUICmdPacketBase
{
public:
	XDateTime	CreatedTime;

	GUICmdReqDeleteLearningImage(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
