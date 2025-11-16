#ifndef BUTTONTRANSFERSENDGLOBALPARAM_H
#define BUTTONTRANSFERSENDGLOBALPARAM_H

#include "buttontransfersendglobalparam_global.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralWidget.h"

class	ButtonTransferSendGlobalParam : public GUIFormBase
{
	Q_OBJECT

	QPushButtonWithRightClick	Button;

public:
	QString	Msg;

	ButtonTransferSendGlobalParam(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
	void	SlotRightClicked();
	void	SlotResetFixedHost();
	void	SlotEditHost();
};

#endif // BUTTONTRANSFERSENDGLOBALPARAM_H
