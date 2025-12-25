#pragma once

#include "buttonupdateallbyhistogram_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>

class	ButtonUpdateAllByHistogram : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonUpdateAllByHistogram(LayersBase *Base ,QWidget *parent);
	~ButtonUpdateAllByHistogram(void);
	
	virtual void	Prepare(void)				override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};