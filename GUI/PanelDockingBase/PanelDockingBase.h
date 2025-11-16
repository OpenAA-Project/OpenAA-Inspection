#ifndef PANELDOCKINGBASE_H
#define PANELDOCKINGBASE_H

#include "paneldockingbase_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"

class	PanelDockingBase : public GUIFormBase
{
	Q_OBJECT

public:
	QColor	BaseCol;

	PanelDockingBase(LayersBase *Base ,QWidget *parent);
	~PanelDockingBase(void);

	virtual	void	Prepare(void)	override;
};

#endif // PANELDOCKINGBASE_H
