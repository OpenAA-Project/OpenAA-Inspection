#ifndef BUTTONTRANSFERLOADGUI_H
#define BUTTONTRANSFERLOADGUI_H

#include "buttontransferloadgui_global.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralWidget.h"

class	ButtonTransferLoadGUI : public GUIFormBase
{
	Q_OBJECT

	QPushButtonWithRightClick	Button;

public:
	QString	Msg;

	ButtonTransferLoadGUI(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
	void	SlotRightClicked();
	void	SlotResetFixedHost();
	void	SlotEditHost();
};

#endif // BUTTONTRANSFERLOADGUI_H
