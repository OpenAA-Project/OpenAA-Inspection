#ifndef GENERALPANEL_H
#define GENERALPANEL_H

#include "generalpanel_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"

class	GeneralPanel : public GUIFormBase
{
	Q_OBJECT

public:
	QColor	BaseCol;

	GeneralPanel(LayersBase *Base ,QWidget *parent);
	~GeneralPanel(void);

	virtual	void	Prepare(void)	override;
};


#endif // GENERALPANEL_H
