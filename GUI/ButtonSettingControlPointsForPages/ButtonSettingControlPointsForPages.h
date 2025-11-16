#pragma once

#include "buttonsettingcontrolpointsforpages_global.h"

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>

class	ShowSettingControlPointsForPagesForm;

class	ButtonSettingControlPointsForPages : public GUIFormBase
{
    Q_OBJECT

	ShowSettingControlPointsForPagesForm	*Window;
	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	Mastered;

	ButtonSettingControlPointsForPages(LayersBase *Base ,QWidget *parent = 0);
	~ButtonSettingControlPointsForPages();

	virtual void	Prepare(void)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};
