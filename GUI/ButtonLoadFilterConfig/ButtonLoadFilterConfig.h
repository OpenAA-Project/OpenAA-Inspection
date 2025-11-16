#pragma once

#include "buttonloadfilterconfig_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIFormBase.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>

class	ButtonLoadFilterConfig : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QImage	ButtonIcon;

	ButtonLoadFilterConfig(LayersBase *Base ,QWidget *parent);
	~ButtonLoadFilterConfig(void);
	virtual void	Prepare(void)	override;

public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};