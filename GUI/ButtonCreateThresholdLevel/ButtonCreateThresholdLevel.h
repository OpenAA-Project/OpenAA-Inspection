#pragma once

#include "buttoncreatethresholdlevel_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonCreateThresholdLevel : public GUIFormBase
{
    Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonCreateThresholdLevel(LayersBase *Base ,QWidget *parent = 0);
	~ButtonCreateThresholdLevel();

	virtual void	Prepare(void)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};