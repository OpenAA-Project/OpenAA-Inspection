#ifndef EXPANDMAININTAB_H
#define EXPANDMAININTAB_H

#include "expandmainintab_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"



class	ExpandMainInTab : public GUIFormBase
{
	Q_OBJECT

	int	SavedX1;
	int	SavedY1;
	int	SavedX2;
	int	SavedY2;

public:

	ExpandMainInTab(LayersBase *Base ,QWidget *parent);
	~ExpandMainInTab(void);

	virtual	void	Prepare(void)		override;
	virtual void	StartPage	(void)	override;
	virtual void	LeavePage	(void)	override;

private slots:
};
#endif // EXPANDMAININTAB_H
