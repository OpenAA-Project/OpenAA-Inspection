#ifndef PANELHIDABLE_H
#define PANELHIDABLE_H

#include "panelhidable_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include "XServiceForLayers.h"


class	PanelHidableInside : public GUIFormBase
{
	Q_OBJECT

public:
	PanelHidableInside(LayersBase *Base ,QWidget *parent);

private slots:
	void	ResizeAction();
};


class	PanelHidable : public GUIFormBase
{
	Q_OBJECT

	int		ButtonH;
	bool	Opened;
	PanelHidableInside	InsidePanel;
	QPushButton	HideButton;	
	int	StartX,StartY;
	int	StartWidth,StartHeight;

public:
	QString	ButtonLocation;
	bool	EnableHide;

	PanelHidable(LayersBase *Base ,QWidget *parent);
	~PanelHidable(void);

	virtual	void	Prepare(void)				override;
	virtual	GUIFormBase	*GetChild(int index)	const	override;
	virtual	GUIFormBase	*GetTopSurfaceWidget(int x ,int y)	override;
private slots:
	void	ResizeAction();
	void	ClickButton();
};

#endif // PANELHIDABLE_H
