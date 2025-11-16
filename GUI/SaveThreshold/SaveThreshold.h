#pragma once

#include "savethreshold_global.h"
#include "XGUIFormBase.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	SaveThreshold : public GUIFormBase
{
	Q_OBJECT

public:

	SaveThreshold(LayersBase *Base ,QWidget *parent);
	~SaveThreshold(void);

	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

};
