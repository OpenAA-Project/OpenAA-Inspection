#pragma once

#include "buttonreplaceimagelocally_global.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonReplaceImageLocally : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:

	ButtonReplaceImageLocally(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

