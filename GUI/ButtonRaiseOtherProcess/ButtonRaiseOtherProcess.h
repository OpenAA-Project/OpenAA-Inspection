#pragma once

#include "buttonraiseotherprocess_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonRaiseOtherProcess : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	QString		RaisedProcessName;

	ButtonRaiseOtherProcess(LayersBase *Base ,QWidget *parent);
	~ButtonRaiseOtherProcess(void);

	virtual	void	Prepare(void)	override;

public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

