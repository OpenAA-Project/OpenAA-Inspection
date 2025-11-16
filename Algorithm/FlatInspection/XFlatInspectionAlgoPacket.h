#pragma once

#include "XFlatInspection.h"
#include "XGeneralFunc.h"

class	CmdSendAddManualFlatInspection : public GUIDirectMessage
{
public:
	int			LibID;
	FlexArea	Area;
	FlatInspectionItem::FlatInspectionType	FIType;

	CmdSendAddManualFlatInspection(LayersBase *base):GUIDirectMessage(base){}
	CmdSendAddManualFlatInspection(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

