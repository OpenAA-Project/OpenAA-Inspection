#ifndef GENERALDIVIDEDPANELS_H
#define GENERALDIVIDEDPANELS_H

#include "generaldividedpanels_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include <QSplitter>
#include "XServiceForLayers.h"

class	GeneralDividedPanels;

class	GDividedPanel : public GUIFormBase
{
	GeneralDividedPanels	*Parent;
	int	ID;
public:
	GDividedPanel(LayersBase *Base ,GeneralDividedPanels *p,int id ,QWidget *parent);
	~GDividedPanel(void);

	virtual	bool	IsShown(void);
};


class	GeneralDividedPanels : public GUIFormBase
{
	Q_OBJECT

	GDividedPanel	**Children;
	int			CountChildren;
	QSplitter	SplitterWidget;
public:
	int32	DividedCount;
	QString	Direction;
	int		CurrentMarkPanel;
	int		Mergin;
	bool	Movable;

	GeneralDividedPanels(LayersBase *Base ,QWidget *parent);
	~GeneralDividedPanels(void);

	virtual	void	Prepare(void)	override;

	virtual	int		GetChildCount()							override;
	virtual	GUIFormBase	*GetChild(int index)	const		override;
	virtual	GUIFormBase	*GetTopSurfaceWidget(int x ,int y)	override;

private slots:
	void	ResizeAction();

private:
	virtual	void	paintEvent ( QPaintEvent * event )	override;
};

#endif // GENERALDIVIDEDPANELS_H
