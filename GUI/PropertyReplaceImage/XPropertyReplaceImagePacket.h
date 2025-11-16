#pragma once

#include "XGUIPacketForDLL.h"
#include "XReplaceImage.h"
#include "XIntClass.h"
#include "XReplaceImage.h"

class	LayersBase;

class	CmdReplaceImageDrawAttr: public GUIDirectMessage
{
public:
	bool	ShowIsoMask;

	CmdReplaceImageDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceImageDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReplaceImageDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	GUICmdReplaceImageDrawEnd(LayersBase *base) :GUIDirectMessage(base) {}
	GUICmdReplaceImageDrawEnd(GUICmdPacketBase *gbase) :GUIDirectMessage(gbase) {}
};

class	GUICmdReplaceImageAddMaskArea : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdReplaceImageAddMaskArea(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageAckMaskArea : public GUICmdPacketBase
{
public:
	QColor	AverageColor;

	GUICmdReplaceImageAckMaskArea(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdReplaceImageAddMaskImage : public GUICmdPacketBase
{
public:
	QImage	Image;

	GUICmdReplaceImageAddMaskImage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageCalcMask: public GUICmdPacketBase
{
public:
	GUICmdReplaceImageCalcMask(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageMouseLDown : public GUICmdPacketBase
{
public:
	int	X,Y;

	GUICmdReplaceImageMouseLDown(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReplaceImageSetCompositeColor : public GUICmdPacketBase
{
public:
	QColor	Color;

	GUICmdReplaceImageSetCompositeColor(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageSetCompositeImage : public GUICmdPacketBase
{
public:
	QImage	Image;

	GUICmdReplaceImageSetCompositeImage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageSetCompositePage : public GUICmdPacketBase
{
public:
	int	CompPage;

	GUICmdReplaceImageSetCompositePage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageReqDraw : public GUICmdPacketBase
{
public:
	struct DataDrawInfo
	{
		int	movx;
		int	movy;
		double	ZoomRate;
		int		CanvasWidth;
		int		CanvasHeight;
		bool	ShowIsoMask;
	}Data;

	GUICmdReplaceImageReqDraw(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageAckDraw : public GUICmdPacketBase
{
public:
	QImage	Image;

	GUICmdReplaceImageAckDraw(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};


class	GUICmdReplaceImageProcessMode : public GUICmdPacketBase
{
public:
	ReplaceImageThreshold::OperateComposite	CompMode;
	bool	CompositeInside;

	GUICmdReplaceImageProcessMode(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplaceImageMaskMode : public GUICmdPacketBase
{
public:
	ReplaceImageThreshold::OperateIsolation	OpeMode;

	GUICmdReplaceImageMaskMode(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReplaceImageMakeAreaMask : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdReplaceImageMakeAreaMask(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
