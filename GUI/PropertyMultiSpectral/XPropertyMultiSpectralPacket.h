#pragma once

#include "XGUIPacketForDLL.h"
#include "XMultiSpectral.h"

class	CmdMultiSpectralDrawAttr: public GUIDirectMessage
{
public:
	CmdMultiSpectralDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdMultiSpectralDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdMultiSpectralDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	GUICmdMultiSpectralDrawEnd(LayersBase *base) :GUIDirectMessage(base) {}
	GUICmdMultiSpectralDrawEnd(GUICmdPacketBase *gbase) :GUIDirectMessage(gbase) {}
};

class GUICmdSendAddMultiSpectralUsageAreaItem : public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;
	int			LibID;

	GUICmdSendAddMultiSpectralUsageAreaItem(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName);
};
