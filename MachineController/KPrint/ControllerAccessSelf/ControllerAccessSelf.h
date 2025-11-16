#pragma once

#include "controlleraccessself_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include <QImage>
#include <QString>
#include <QColor>
#include <QFont>
#include <QPushButton>

class	ControllerAccessSelfForm;

class  ButtonControllerAccessSelf: public GUIFormBase
{
	Q_OBJECT

	ControllerAccessSelfForm	*Window;
	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	explicit ButtonControllerAccessSelf(LayersBase *Base ,QWidget *parent = 0);

	virtual	void	Prepare(void)	override;
	void	OpenDialog(void);
private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};
