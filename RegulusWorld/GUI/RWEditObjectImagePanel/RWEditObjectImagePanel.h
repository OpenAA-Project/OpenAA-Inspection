#pragma once

#include "rweditobjectimagepanel_global.h"
#include "XDisplayImage3D.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	RWEditObjectImagePanel : public GUIFormBase
{
	Q_OBJECT

	XDisplayImage3D5Panels	Panel;
public:
	RWEditObjectImagePanel(LayersBase *Base ,QWidget *parent);
	~RWEditObjectImagePanel(void){}

protected:
	virtual	void resizeEvent(QResizeEvent *event)	override;

};
