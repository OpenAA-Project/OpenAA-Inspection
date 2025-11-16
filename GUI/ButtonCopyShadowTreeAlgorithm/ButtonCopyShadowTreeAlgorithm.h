#pragma once

#include "buttoncopyshadowtreealgorithm_global.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"


class  ButtonCopyShadowTreeAlgorithm: public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonCopyShadowTreeAlgorithm(LayersBase *Base ,QWidget *parent);
	~ButtonCopyShadowTreeAlgorithm(void);

	virtual	void	Prepare(void)		override;

private slots:
	void SlotClicked (int ButtonNumber);
	void	ResizeAction();
};