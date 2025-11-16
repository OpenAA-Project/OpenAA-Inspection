#ifndef PANELSCROLLABLE_H
#define PANELSCROLLABLE_H

#include "panelscrollable_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include <QScrollBar>
#include <QColor>

class	PanelScrollable : public GUIFormBase
{
	Q_OBJECT

	QScrollBar	HBar;
public:
	QColor	BaseCol;
	bool	HBarTop;

	PanelScrollable(LayersBase *Base ,QWidget *parent);
	~PanelScrollable(void);

	virtual	void	Prepare(void) override;
	virtual	void	ReadyParam(void) override;
public slots:
	void	ResizeAction();
};

#endif // PANELSCROLLABLE_H
