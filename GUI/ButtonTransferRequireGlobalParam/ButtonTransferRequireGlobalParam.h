#ifndef BUTTONTRANSFERREQUIREGLOBALPARAM_H
#define BUTTONTRANSFERREQUIREGLOBALPARAM_H

#include "buttontransferrequireglobalparam_global.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralWidget.h"

class	ButtonTransferRequireGlobalParam : public GUIFormBase
{
	Q_OBJECT

	QPushButtonWithRightClick	Button;

public:
	QString	Msg;

	ButtonTransferRequireGlobalParam(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
	void	SlotRightClicked();
	void	SlotResetFixedHost();
	void	SlotEditHost();
};

#endif // BUTTONTRANSFERREQUIREGLOBALPARAM_H
