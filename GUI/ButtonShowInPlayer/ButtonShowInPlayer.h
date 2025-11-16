#pragma once

#include "buttonshowinplayer_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>

class	ButtonShowInPlayer : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	int64	LastShownInspectionID;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QImage	ButtonIcon;
	QString	GUIInst;

	ButtonShowInPlayer(LayersBase *Base ,QWidget *parent);
	~ButtonShowInPlayer(void);
	virtual void	Prepare(void)	override;

	void	ShowInPlayer(int64 shownInspectionID)	override;

public slots:
	void SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};
