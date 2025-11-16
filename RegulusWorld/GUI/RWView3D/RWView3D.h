#pragma once

#include "rwview3d_global.h"
#include "XDisplayImage3D.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	RWView3D : public GUIFormBase
{
	Q_OBJECT

	XDisplayImage3D	Panel;
public:
	RWView3D(LayersBase *Base ,QWidget *parent);
	~RWView3D(void){}

protected:
	virtual	void resizeEvent(QResizeEvent *event)	override;

};
