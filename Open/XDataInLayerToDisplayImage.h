#if	!defined(XDataInLayerToDisplayImage_h)
#define	XDataInLayerToDisplayImage_h

#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "SelectPasteForm.h"

class	GUICmdReqBmpForTopView : public GUICmdReqBmp
{
public:
	GUICmdReqBmpForTopView(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReqBmpForTopView(void);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendBmpForTopView : public GUICmdSendBmp
{
public:
	GUICmdSendBmpForTopView(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendBmpForTopView(void);

};

class	GUICmdReqCopiedList : public GUICmdPacketBase
{
public:

    GUICmdReqCopiedList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1)
		:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
		{}

    virtual	bool	Load(QIODevice *f);
    virtual	bool	Save(QIODevice *f);

    virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendCopiedList : public GUICmdPacketBase
{
public:
    NPListPack<SelectPasteForm::CopiedList>	Lists;

    GUICmdSendCopiedList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1)
		:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
		{}

    void	MakeLists(void);

    virtual	bool	Load(QIODevice *f);
    virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	GUICmdReqCopiedForSave : public GUICmdPacketBase
{
public:
    XDateTime	SelectTimeIndex;

    GUICmdReqCopiedForSave(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1)
		:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
		{}

    virtual	bool	Load(QIODevice *f);
    virtual	bool	Save(QIODevice *f);

    virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckCopiedForSave : public GUICmdPacketBase
{
public:
    QByteArray	Buff;

    GUICmdAckCopiedForSave(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1)
		:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
		{}

    virtual	bool	Load(QIODevice *f);
    virtual	bool	Save(QIODevice *f);

    virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
class	GUICmdReqCopiedForDelete : public GUICmdPacketBase
{
public:
    XDateTime	SelectTimeIndex;

    GUICmdReqCopiedForDelete(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1)
		:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
		{}

    virtual	bool	Load(QIODevice *f);
    virtual	bool	Save(QIODevice *f);

    virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
class	GUICmdSendCopiedForLoad : public GUICmdPacketBase
{
public:
    QByteArray	Buff;

    GUICmdSendCopiedForLoad(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1)
		:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
		{}

    virtual	bool	Load(QIODevice *f);
    virtual	bool	Save(QIODevice *f);

    virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//=============================================================================================================


#endif