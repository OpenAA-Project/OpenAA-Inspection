#pragma once

#include "rwview5panels_global.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XDisplayImage3D.h"

class RWView5Panels : public GUIFormBase
{
    XDisplayImage3D5Panels     Panel;
public:
    RWView5Panels(LayersBase *Base ,QWidget *parent = 0);

protected:
	virtual	void resizeEvent(QResizeEvent *event)	override;
};
