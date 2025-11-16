#pragma once

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XFlatInspectionLibrary.h"
#include "XFlatInspection.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include <QColor>

class	FlatInspectionImagePanel;
class	CmdFlatInspectionDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	FlatInspectionImagePanel	*ImagePanelPoint;

	CmdFlatInspectionDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdFlatInspectionDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdSendAddManualFlatInspection : public GUICmdPacketBase
{
public:
	int			LibID;
	FlexArea	Area;
	FlatInspectionItem::FlatInspectionType	FIType;

	GUICmdSendAddManualFlatInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdReqFIT_Type: public GUIDirectMessage
{
public:
	FlatInspectionItem::FlatInspectionType	FIT_Type;
	bool									ShowMaskMap;

	CmdReqFIT_Type(LayersBase *base):GUIDirectMessage(base){}
	CmdReqFIT_Type(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
