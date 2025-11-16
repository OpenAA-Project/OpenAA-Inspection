#pragma once
#pragma once

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XWorld3D.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include <QColor>

class	World3DImagePanel;
class	CmdWorld3DDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	World3DImagePanel	*ImagePanelPoint;

	CmdWorld3DDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdWorld3DDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	GUICmdLoadStepFile : public GUICmdPacketBase
{
public:
	QByteArray	FArray;

	GUICmdLoadStepFile(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};