#pragma once

#include "buttonsaveguilanguage_global.h"
#include <QToolButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ButtonSaveGUILanguage : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
public:
    ButtonSaveGUILanguage(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare		(void)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};
