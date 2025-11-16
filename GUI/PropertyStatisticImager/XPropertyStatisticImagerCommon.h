#pragma once

#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XStatisticImager.h"


class	CmdGetDrawModeStatistic : public GUIDirectMessage
{
public:
	StatisticImagerDrawAttr::_DrawMode	DrawMode;
	CmdGetDrawModeStatistic(LayersBase *base):GUIDirectMessage(base){}
};

