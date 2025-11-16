#pragma once

#include "loadthreshold_global.h"
#include "XGUIFormBase.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	LoadThreshold : public GUIFormBase
{
	Q_OBJECT

public:

	LoadThreshold(LayersBase *Base ,QWidget *parent);
	~LoadThreshold(void);

	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

};
