#ifndef BUTTONHELP_H
#define BUTTONHELP_H

#include "buttonhelp_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButton.h"

class	ButtonHelp : public GUIFormBase
{
	Q_OBJECT

	mtImageToolButton	Button;

public:
	ButtonHelp(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONHELP_H
