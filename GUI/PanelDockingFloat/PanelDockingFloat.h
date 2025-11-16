#ifndef PANELDOCKINGFLOAT_H
#define PANELDOCKINGFLOAT_H

#include "paneldockingfloat_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"

class	PanelDockingFloat : public GUIFormBase
{
	Q_OBJECT

public:
	QColor	BaseCol;

	PanelDockingFloat(LayersBase *Base ,QWidget *parent);
	~PanelDockingFloat(void);

	virtual	void	Prepare(void)	override;
};

#endif // PANELDOCKINGFLOAT_H
