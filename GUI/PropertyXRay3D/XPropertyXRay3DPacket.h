#pragma once

#include "XGUIPacketForDLL.h"
#include "XIntClass.h"

class	GUICmdLoadImages : public GUICmdPacketBase
{
public:
	QStringList	ImageFileNames;

	GUICmdLoadImages(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSetPointY : public GUICmdPacketBase
{
public:
	double	PointToDraw;

	GUICmdSetPointY(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqSmooth : public GUICmdPacketBase
{
public:

	GUICmdReqSmooth(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqEmphasize : public GUICmdPacketBase
{
public:

	GUICmdReqEmphasize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqMatchFile: public GUICmdPacketBase
{
public:
	QString	FileName;

	GUICmdReqMatchFile(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckMatchFile: public GUICmdPacketBase
{
public:
	int		RetFileNo;
	int		RetX,RetY;

	GUICmdAckMatchFile(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};