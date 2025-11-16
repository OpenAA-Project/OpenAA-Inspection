#pragma once

#include "buttontransferrequireimagedata_global.h"
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralWidget.h"

class	ButtonTransferRequireImageData : public GUIFormBase
{
	Q_OBJECT

	QPushButtonWithRightClick	Button;

public:
	QString	Msg;
	bool	SrcMasterImage;
	bool	DstMasterImage;
	bool	ChangeXY;

	ButtonTransferRequireImageData(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
	void	SlotRightClicked();
	void	SlotResetFixedHost();
	void	SlotEditHost();
};
