#ifndef STACKSTOSWITCHMASTERTARGET_H
#define STACKSTOSWITCHMASTERTARGET_H

#include "stackstoswitchmastertarget_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QStackedWidget>
#include <QTranslator>

class	StacksTabWizardPage : public GUIFormBase
{
public:
	StacksTabWizardPage(LayersBase *Base ,QWidget *parent);
	~StacksTabWizardPage(void);

	virtual void	Prepare(void)		override;
	virtual void	ResizeAction(void);
};

class	StacksToSwitchMasterTarget : public GUIFormBase
{
	Q_OBJECT
	QStackedWidget						MainTab;
public:
	StacksToSwitchMasterTarget(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)				override;
	virtual GUIFormBase	*GetTopSurfaceWidget(int x ,int y)	override;
	virtual	int	GetChildCount()					override;
	virtual	GUIFormBase	*GetChild(int index)	const	override;

	void	SwitchTab(bool Mastered);
	virtual void	ShowInPlayer(int64 n)		override;

private slots:
	void	ResizeAction();
private:
};

#endif // STACKSTOSWITCHMASTERTARGET_H
